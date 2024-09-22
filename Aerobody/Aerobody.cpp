#include <iostream>  
#include <cmath>     
#include <numbers>   
#include "VelocityVector.hpp"
#include "Aerobody.h"

// f_drag = 0.5 * density * (air speed of vehicle)^2 * Area * drag coefficient

ApparentWindVector Aerobody::get_wind(const VelocityVector& reported_wind, const VelocityVector& car_velocity) {
    double ns_sum = -reported_wind.get_north_south() - car_velocity.get_north_south();
    double ew_sum = -reported_wind.get_east_west() - car_velocity.get_east_west();

    VelocityVector rel_vec = VelocityVector::from_cartesian_components(-ns_sum, -ew_sum);

    double yaw = car_velocity.angle_between(rel_vec);

    double speed = rel_vec.get_magnitude();

    return ApparentWindVector{speed, yaw};
}

    
double Aerobody::aerodynamic_drag(const ApparentWindVector& apparent_wind, double air_density)const {
    double v = apparent_wind.speed * std::abs(std::cos(apparent_wind.yaw));

    double CdA = drag_coefficient * frontal_area;

    return 0.5 * air_density * std::pow(v, 2) * CdA;
}
