#include "RaceSegmentRunner.h"
#include "RaceConfig/Route/RouteSegment.h"
#include "SolarCar/Aerobody/Aerobody.h"
#include "SolarCar/Aerobody/VelocityVector.h"
#include <cmath>
#include <optional>
#include <iostream>

double RaceSegmentRunner::calculate_resistive_force(
    const RouteSegment& route_segment, const WeatherDataPoint& weather_data, double speed) const {
    VelocityVector car_velocity = VelocityVector::from_polar_components(speed,  route_segment.heading);
    ApparentWindVector wind = Aerobody::get_wind(weather_data.wind, car_velocity);
    double car_f_g = car.mass * route_segment.gravity;
    double const aero_res_f = car.aerobody.aerodynamic_drag(wind, weather_data.air_density);
    double tire_res_f = car.tire.rolling_resistance(car_f_g, speed);
    double grav_res_f = route_segment.gravity_times_sine_road_incline_angle * car.mass;
    return aero_res_f + tire_res_f + grav_res_f;
}

double RaceSegmentRunner::calculate_power_out(
    const RouteSegment& route_segment, const WeatherDataPoint& weather_data, double speed) const {
    const double angular_speed = speed/car.wheel_radius;
    const double torque = car.wheel_radius* calculate_resistive_force(route_segment, weather_data,  speed);
    return car.motor.power_consumed(angular_speed, torque);
}




double RaceSegmentRunner::calculate_power_in(
    const RouteSegment& route_segment, const WeatherDataPoint& weather_data) const {
    double irradiance = weather_data.irradiance;
    double power_in = car.array.power_in(irradiance);
    static_cast<void>(route_segment);
    return power_in;
}



std::optional<double> RaceSegmentRunner::calculate_power_net(
    const RouteSegment& route_segment, const WeatherDataPoint& weather_data,
    double state_of_charge, double speed) const {
    double power_out = calculate_power_out(route_segment, weather_data, speed);
    double power_in = calculate_power_in(route_segment, weather_data);
    double net_power = power_in - power_out;
    std::optional<double> power_loss = car.battery.power_loss(-net_power, state_of_charge);
    if (!power_loss.has_value()){
        return std::nullopt;
    }

    
    double adjusted_net_power = net_power -*power_loss;
    return adjusted_net_power; 
}

