#include "Battery.h"
#include "BatteryState.h"
#include <optional>

double Battery::state_of_charge(double energy_remaining) const{
return energy_remaining/ energy_capacity;
}



double Battery::current_voltage(double state_of_charge) const{
    return ((max_voltage-min_voltage)*state_of_charge)+min_voltage;
}

	std::optional<double> Battery::power_loss(double net_power_demanded, double state_of_charge) const {
    double v = current_voltage(state_of_charge);  

   
    if ((std::pow(v, 2)) + 4 * pack_resistance * net_power_demanded < 0) {
        return std::nullopt;
    }

    
    double I = (-v + std::sqrt(std::pow(v, 2) + (4 * pack_resistance * net_power_demanded))) / (2 * pack_resistance);

    return std::optional<double>(std::pow(I, 2) * pack_resistance);
}




