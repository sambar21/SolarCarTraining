#include "Tire.h"
#include <cmath>

double Tire::rolling_resistance(double tire_load, double vehicle_speed, std::optional<double> tire_pressure) const {

   vehicle_speed *= 3.6;

    double pressure = tire_pressure.value_or(tire_pressure_at_stc);
    
   

    double rolling_resistance = pow(pressure, alpha) * pow(tire_load, beta) *
                                (a + b * vehicle_speed + c * pow(vehicle_speed, 2));

    return rolling_resistance;
}
