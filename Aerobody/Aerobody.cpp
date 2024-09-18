#include <iostream>  
#include <cmath>     
#include <numbers>   
#include "VelocityVector.hpp"

// f_drag = 0.5 * density * (air speed of vehicle)^2 * Area * drag coefficient

// Definition of the get_wind function
ApparentWindVector Aerobody::get_wind(const VelocityVector& reported_wind, const VelocityVector& car_velocity) {
    // Calculate the apparent wind vector by subtracting the car's velocity from the reported wind
    VelocityVector apparent_wind_vector(
        reported_wind.get_north_south() + car_velocity.get_north_south(),
        reported_wind.get_east_west() + car_velocity.get_east_west()

    );

    // Find the magnitude and heading of the apparent wind vector
    double apparent_wind_speed = apparent_wind_vector.get_magnitude();
    double apparent_wind_angle = apparent_wind_vector.get_heading();

    // Return the apparent wind vector (speed and angle)
    return ApparentWindVector{apparent_wind_speed, apparent_wind_angle};
}

// Definition of the aerodynamic_drag function
double Aerobody::aerodynamic_drag(const ApparentWindVector& apparent_wind, double air_density) {
    // calc cda
    double CdA = drag_coefficient * frontal_area;

//output formula
    double fDrag = 0.5 * air_density * std::pow(apparent_wind.speed, 2) * CdA;

    return fDrag;
}
