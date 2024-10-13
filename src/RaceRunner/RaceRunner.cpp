#include "RaceRunner.h"
#include "RaceSegmentRunner/RaceSegmentRunner.h"
#include "Tools/Conversions.h"
#include <vector>
#include <optional>
#include <cassert>

using namespace std;

double RaceRunner::calculate_static_charging_gain(
    const SolarCar& car, const Weather& weather, double weather_station, double start_time, double end_time) {

        //car is not moving

        const double increment = 300;
        double solar_car_energy = 0;

        for (double time = start_time; time < end_time; time += increment) {
            solar_car_energy += car.array.power_in(weather.get_weather_during(weather_station, time, time+increment).irradiance);
        }


        return solar_car_energy * (3.0/36.0);
}


std::optional<double> RaceRunner::calculate_racetime( 
        const SolarCar& car, const Route& route, const Weather& weather, const RaceSchedule& schedule, double speed) {

    RaceSegmentRunner RSR = RaceSegmentRunner(car);

    double total_time = 0;
    double energy_remaining = car.battery.get_capacity(); 
    double stateOfCharge = car.battery.state_of_charge(energy_remaining); 
    size_t segment_idx = 0;
    size_t num_segments = route.get_num_segments();

    for (size_t day = 0; day < schedule.size(); ++day) {
        const SingleDaySchedule& daily_schedule = schedule[day];

        double morningChargeStart = daily_schedule.morning_charging_start_time;
        double morningChargeEnd = daily_schedule.morning_charging_end_time;
        double eveningChargeStart = daily_schedule.evening_charging_start_time;
        double eveningChargeEnd = daily_schedule.evening_charging_end_time;

        double raceStartTime = daily_schedule.race_start_time;
        double raceEndTime = daily_schedule.race_end_time;

        if (day > 0) {
            double weather_station = route.get_segment(segment_idx).weather_station;
            double morning_charge_gain = calculate_static_charging_gain(
                car, weather, weather_station, morningChargeStart, morningChargeEnd
            );
            energy_remaining += morning_charge_gain;
        }

        double current_time = raceStartTime;

        while (current_time < raceEndTime && segment_idx < num_segments) {
            const RouteSegment & segment = route.get_segment(segment_idx);
            double time_required = segment.distance / speed;

            WeatherDataPoint weather_data = weather.get_weather_during(segment.weather_station, current_time, current_time + time_required);

            stateOfCharge = car.battery.state_of_charge(energy_remaining);
            std::optional<double> segment_net_power = RSR.calculate_power_net(
                segment, weather_data, stateOfCharge, speed 
            ); 

            if (!segment_net_power.has_value()) {
                return std::nullopt;
            }

            energy_remaining += segment_net_power.value() * seconds_to_hours(time_required);//this is joules rn
            //seconds to hours unde tools
            // seconds_to_days( seconds);

            if (energy_remaining < 0) {
                return std::nullopt;
            }

            current_time += time_required;
            total_time += time_required;

            if (segment.end_condition == 0) {
                double checkpoint_time = 1800;
                energy_remaining += calculate_static_charging_gain(
                    car, weather, segment.weather_station, current_time, current_time + checkpoint_time
                );
                current_time += checkpoint_time;
                total_time += checkpoint_time;
            } else if (segment.end_condition == 1) {
                return total_time;  // Race completed
            }

            segment_idx++;
        }

        if (segment_idx >= num_segments) {
            return total_time;  // Race completed
        }

        double evening_charge_gain = calculate_static_charging_gain(
            car, weather, route.get_segment(segment_idx).weather_station, eveningChargeStart, eveningChargeEnd
        );
        energy_remaining += evening_charge_gain;
    }

    return std::nullopt;  // Race not completed within the schedule
}





