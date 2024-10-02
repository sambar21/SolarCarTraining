#include "SolarCar.h"

#include "ConfigFile/ConfigFile.h"
#include "SolarCar/Aerobody/Aerobody.h"
#include "SolarCar/Array/Array.h"
#include "SolarCar/Battery/Battery.h"
#include "SolarCar/Motor/Motor.h"
#include "SolarCar/Tire/Tire.h"

// Sample car_config.toml
// mass = 243 # kg
//
// [aerobody]
// drag-coefficient = 0.10583
// frontal-area = 0.6802
//
// [array]
// area = 4.0 # m^2
// efficiency = 24 # %
//
// [battery]
// capacity = 3000
// pack-resistance = 0.2
// max-voltage = 10
// min-voltage = 3
//
// [motor]
// hysteresis-loss = 2.08064
// eddy-current-loss-coefficient = 0.0364
//
// [tire]
// name = "Bridgestone Enliten (2023)"
// wheel-radius = 0.27635
// alpha = -0.477792358183247
// beta = 1.13554135884356
// a = 0.0100701943060431
// b = 4.36050341473975e-5
// c = 1.67047322589584e-7

SolarCar::SolarCar(const ConfigFile& car_config)
	: aerobody(0, 0), array(0, 0), battery(0, 0, 0, 0), motor(0, 0), tire({}, 0), mass(0), wheel_radius(0) {
	mass = car_config.get_force<double>("mass");                       // NOLINT
	wheel_radius = car_config.get_force<double>("tire.wheel-radius");  // NOLINT

	const auto aerobody_config = car_config.get_force<ConfigFile>("aerobody");
	aerobody = Aerobody(
		aerobody_config.get_force<double>("drag-coefficient"), aerobody_config.get_force<double>("frontal-area"));

	const auto array_config = car_config.get_force<ConfigFile>("array");
	array = Array(array_config.get_force<double>("area"), array_config.get_force<double>("efficiency"));

	const auto battery_config = car_config.get_force<ConfigFile>("battery");
	battery = Battery(battery_config.get_force<double>("capacity"), battery_config.get_force<double>("pack-resistance"),
		battery_config.get_force<double>("min-voltage"), battery_config.get_force<double>("max-voltage"));

	const auto motor_config = car_config.get_force<ConfigFile>("motor");
	motor = Motor(motor_config.get_force<double>("hysteresis-loss"),
		motor_config.get_force<double>("eddy-current-loss-coefficient"));

	const auto tire_config = car_config.get_force<ConfigFile>("tire");
	tire = Tire(
		{
			.alpha = tire_config.get_force<double>("alpha"),
			.beta = tire_config.get_force<double>("beta"),
			.a = tire_config.get_force<double>("a"),
			.b = tire_config.get_force<double>("b"),
			.c = tire_config.get_force<double>("c"),
		},
		tire_config.get_force<double>("pressure"));
}
