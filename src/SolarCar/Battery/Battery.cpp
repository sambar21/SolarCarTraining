#include "Battery.h"

#include <optional>
using namespace std;
double Battery::state_of_charge(double energy_remaining) const{
return energy_remaining/ energy_capacity;
}



double Battery::current_voltage(double state_of_charge) const{
    return ((max_voltage-min_voltage)*state_of_charge)+min_voltage;
}

	std::optional<double> Battery::power_loss(double net_power_demanded, double state_of_charge) const { //NOLINT
    const double vol = current_voltage(state_of_charge);  

   
    if ((std::pow(vol, 2)) + 4 * pack_resistance * net_power_demanded < 0) {
        return std::nullopt;
    }

    
    const double cur = (-vol + std::sqrt(std::pow(vol, 2) + (4 * pack_resistance * net_power_demanded))) / (2 * pack_resistance);

    return optional<double>(std::pow(cur, 2) * pack_resistance);
}




