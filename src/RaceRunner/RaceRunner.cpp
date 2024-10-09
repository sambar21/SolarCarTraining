#include "RaceRunner.h"
#include "SolarCar/Aerobody/VelocityVector.h"
#include "../RaceConfig/Weather/Weather.h"
#include "../RaceConfig/RaceSchedule/RaceSchedule.h"
#include <cmath>
#include <algorithm>
#include <iostream>

namespace RaceRunner {

constexpr double FIVE_MINUTES_IN_SECONDS = 300.0;
constexpr double CONTROL_STOP_TIME = 1800.0; // 30 minutes control stop

double calculate_static_charging_gain(
    const SolarCar& car, const Weather& weather, double weather_station, 
    double start_time, double end_time) {
    
    double total_energy_gain = 0.0;
    double current_time = start_time;

    while (current_time < end_time) {
        double time_increment = std::min(FIVE_MINUTES_IN_SECONDS, end_time - current_time);
        WeatherDataPoint weather_data = weather.get_weather_at(weather_station, current_time);
        double solar_power = car.array.power_in(weather_data.irradiance);
        double energy_gain = solar_power * (time_increment / 3600.0);
        total_energy_gain += energy_gain;
        current_time += time_increment;
    }

    return total_energy_gain;
}

double calculate_resistive_force(
    const SolarCar& car, const RouteSegment& route_segment, const WeatherDataPoint& weather_data, double speed) {
    VelocityVector car_velocity = VelocityVector::from_polar_components(speed, route_segment.heading);
    ApparentWindVector wind = Aerobody::get_wind(weather_data.wind, car_velocity);
    double car_f_g = car.mass * route_segment.gravity;
    double aero_res_f = car.aerobody.aerodynamic_drag(wind, weather_data.air_density);
    double tire_res_f = car.tire.rolling_resistance(car_f_g, speed);
    double grav_res_f = route_segment.gravity_times_sine_road_incline_angle * car.mass;
    return aero_res_f + tire_res_f + grav_res_f;
}

double calculate_power_out(
    const SolarCar& car, const RouteSegment& route_segment, const WeatherDataPoint& weather_data, double speed) {
    double resistive_force = calculate_resistive_force(car, route_segment, weather_data, speed);
    return resistive_force * speed;
}

double calculate_power_in(const SolarCar& car, const WeatherDataPoint& weather_data) {
    return car.array.power_in(weather_data.irradiance);
}

std::optional<double> calculate_power_net(
    const SolarCar& car, const RouteSegment& route_segment, const WeatherDataPoint& weather_data,
    double state_of_charge, double speed) {
    
    double power_out = calculate_power_out(car, route_segment, weather_data, speed);
    double power_in = calculate_power_in(car, weather_data);
    double net_power = power_in - power_out;

    std::optional<double> power_loss = car.battery.power_loss(-net_power, state_of_charge);
    
    if (!power_loss) {
        return std::nullopt;
    }
    
    return net_power - *power_loss;
}
std::optional<double> calculate_racetime(
    const SolarCar& car, const Route& route, const Weather& weather, 
    const RaceSchedule& schedule, double speed) {

    double total_time = 0.0;
    double distance_traveled = 0.0;
    double energy_remaining = car.battery.energy_capacity;
    int current_day = 0;

    while (distance_traveled < route.get_total_distance()) {
        const SingleDaySchedule& day_schedule = schedule[current_day];

        // Get the weather station index for the current segment
        size_t weather_station_index = std::min(static_cast<size_t>(distance_traveled), route.weather_stations.size() - 1);
        GeographicalCoordinate weather_station_coord = route.weather_stations[weather_station_index];

        // Morning charging
        if (current_day > 0) {
            double morning_charge = calculate_static_charging_gain(
                car, weather, weather_station_index,
                day_schedule.morning_charging_start_time, day_schedule.morning_charging_end_time);
            energy_remaining = std::min(energy_remaining + morning_charge, car.battery.energy_capacity);
        }

        // Racing
        double race_start = std::max(total_time, day_schedule.race_start_time);
        double race_end = day_schedule.race_end_time;

        while (race_start < race_end && distance_traveled < route.get_total_distance()) {
            RouteSegment route_segment = route.get_segment(static_cast<size_t>(distance_traveled));
            double segment_distance = std::min(speed * (race_end - race_start), 
                                               route.get_total_distance() - distance_traveled);
            double segment_time = segment_distance / speed;
            
            WeatherDataPoint weather_data = weather.get_weather_at(weather_station_index, race_start);
            
            double state_of_charge = car.battery.state_of_charge(energy_remaining);
            auto net_power = calculate_power_net(car, route_segment, weather_data, state_of_charge, speed);
            
            if (!net_power) {
                return std::nullopt; // Battery cannot supply the required power
            }
            
            double energy_change = *net_power * (segment_time / 3600.0);
            energy_remaining += energy_change;
            
            if (energy_remaining <= 0) {
                return std::nullopt; // Car ran out of energy
            }
            
            distance_traveled += segment_distance;
            total_time += segment_time;
            race_start += segment_time;

            // Check for control stop
            auto control_stop = route.get_control_stop(distance_traveled);
            if (control_stop.has_value() && race_start < race_end) {
                double checkpoint_time = std::min(CONTROL_STOP_TIME, race_end - race_start); // 30 minutes or until end of day
                double checkpoint_gain = calculate_static_charging_gain(
                    car, weather, weather_station_index,
                    race_start, race_start + checkpoint_time);
                energy_remaining = std::min(energy_remaining + checkpoint_gain, car.battery.energy_capacity);
                total_time += checkpoint_time;
                race_start += checkpoint_time;
            }
        }

        // Evening charging
        double evening_charge = calculate_static_charging_gain(
            car, weather, weather_station_index,
            day_schedule.evening_charging_start_time, day_schedule.evening_charging_end_time);
        energy_remaining = static_cast<double>(std::min(
            static_cast<size_t>(energy_remaining + evening_charge),
            static_cast<size_t>(car.battery.getEnergyCapacity())));

        current_day++;
        total_time = current_day * 24 * 3600; // Move to next day
    }

    return total_time;
}


} // namespace RaceRunner
