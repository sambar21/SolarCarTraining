#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <cmath>
#include <numbers>

#include "RaceSegmentRunner.h"

#include "RaceConfig/Route/Route.h"
#include "RaceConfig/Route/RouteSegment.h"
#include "RaceConfig/Weather/WeatherDataPoint.h"
#include "SolarCar/SolarCar.h"
#include "SolarCar/Aerobody/Aerobody.h"
#include "SolarCar/Array/Array.h"
#include "SolarCar/Battery/Battery.h"
#include "SolarCar/Motor/Motor.h"
#include "SolarCar/Tire/Tire.h"

constexpr double EPSILON = 0.001; // %

using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

TEST_CASE("RaceSegmentRunner: calculate_resistive_force", "[RaceSegmentRunner]") {
	SECTION("Random Test 0") {
		constexpr double drag_coefficient = 0.00620866;
		constexpr double frontal_area = 4.94087;
		constexpr double array_area = 7.76468;
		constexpr double array_efficiency = 29.049;
		constexpr double energy_capacity = 6292.61;
		constexpr double min_voltage = 143.512;
		constexpr double max_voltage = 160.485;
		constexpr double resistance = 0.77682;
		constexpr double hysteresis_loss = 3.00149;
		constexpr double eddy_current_loss_coefficient = 0.0168015;
		constexpr double alpha = -6.55598;
		constexpr double beta = 9.97137;
		constexpr double a = 1.95749;
		constexpr double b = 3.30015e-06;
		constexpr double c = 0.272546;
		constexpr double pressure_at_stc = 157.506;
		constexpr double mass = 632.158;
		constexpr double wheel_radius = 0.145815;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		const auto runner = RaceSegmentRunner(car);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {-72.5317, 147.263};
			constexpr GeographicalCoordinate end_coordinate = {-45.8742, -25.0114};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 98.5179;
			constexpr double weather_station = 9.87363;
			constexpr double distance = 63.2248;
			constexpr double heading = 2.93659;
			constexpr double elevation = 386.465;
			constexpr double grade = 0.714595;
			constexpr double road_incline_angle = -1.07733;
			constexpr double sine_road_incline_angle = -0.880695;
			constexpr double gravity = 9.78132;
			constexpr double gravity_times_sine_road_incline_angle = -8.61436;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 41.769;
			constexpr double wind_direction = 5.50586;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 772.068;
			constexpr double air_temp = -10.4746;
			constexpr double pressure = 977.677;
			constexpr double air_density = 1.08267;
			constexpr double reciprocal_speed_of_sound = 0.00296359;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 15.0823;

			const double result = runner.calculate_resistive_force(route_segment, weather_data, speed);
			constexpr double expected = 2.01507e+26;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {-39.7734, -80.2078};
			constexpr GeographicalCoordinate end_coordinate = {-89.4676, -43.6262};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 23.7233;
			constexpr double weather_station = 0.783849;
			constexpr double distance = 40.9054;
			constexpr double heading = 1.52355;
			constexpr double elevation = -456.521;
			constexpr double grade = -0.657431;
			constexpr double road_incline_angle = 0.696444;
			constexpr double sine_road_incline_angle = 0.641493;
			constexpr double gravity = 9.81881;
			constexpr double gravity_times_sine_road_incline_angle = 6.2987;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 41.2174;
			constexpr double wind_direction = 3.81085;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 65.4031;
			constexpr double air_temp = 34.519;
			constexpr double pressure = 996.682;
			constexpr double air_density = 1.13954;
			constexpr double reciprocal_speed_of_sound = 0.00309409;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 0.35556;

			const double result = runner.calculate_resistive_force(route_segment, weather_data, speed);
			constexpr double expected = 6.24833e+23;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {32.1601, -7.59978};
			constexpr GeographicalCoordinate end_coordinate = {-29.5714, -10.2207};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 138.701;
			constexpr double weather_station = 9.70972;
			constexpr double distance = 41.5252;
			constexpr double heading = 4.09611;
			constexpr double elevation = 178.331;
			constexpr double grade = 0.142852;
			constexpr double road_incline_angle = 0.222523;
			constexpr double sine_road_incline_angle = 0.220691;
			constexpr double gravity = 9.78924;
			constexpr double gravity_times_sine_road_incline_angle = 2.1604;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 18.6186;
			constexpr double wind_direction = 3.78778;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 229.9;
			constexpr double air_temp = -5.00108;
			constexpr double pressure = 960.799;
			constexpr double air_density = 1.29481;
			constexpr double reciprocal_speed_of_sound = 0.00309909;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 14.0975;

			const double result = runner.calculate_resistive_force(route_segment, weather_data, speed);
			constexpr double expected = 1.77539e+26;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 1") {
		constexpr double drag_coefficient = 0.000177374;
		constexpr double frontal_area = 8.17814;
		constexpr double array_area = 5.74687;
		constexpr double array_efficiency = 28.5397;
		constexpr double energy_capacity = 2702.16;
		constexpr double min_voltage = 93.3064;
		constexpr double max_voltage = 156.589;
		constexpr double resistance = 0.700782;
		constexpr double hysteresis_loss = 3.02409;
		constexpr double eddy_current_loss_coefficient = 0.00341592;
		constexpr double alpha = -6.86392;
		constexpr double beta = -6.70522;
		constexpr double a = -1.50063;
		constexpr double b = -4.2195e-06;
		constexpr double c = -0.704212;
		constexpr double pressure_at_stc = 160.576;
		constexpr double mass = 630.479;
		constexpr double wheel_radius = 0.136128;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		const auto runner = RaceSegmentRunner(car);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {-47.2924, -91.4223};
			constexpr GeographicalCoordinate end_coordinate = {73.9262, -3.21929};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 167.054;
			constexpr double weather_station = 4.6206;
			constexpr double distance = 30.0533;
			constexpr double heading = 0.496368;
			constexpr double elevation = -323.887;
			constexpr double grade = -0.245809;
			constexpr double road_incline_angle = 0.571036;
			constexpr double sine_road_incline_angle = 0.540504;
			constexpr double gravity = 9.80167;
			constexpr double gravity_times_sine_road_incline_angle = 5.29784;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 14.9191;
			constexpr double wind_direction = 2.42335;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 593.609;
			constexpr double air_temp = 6.72887;
			constexpr double pressure = 1008.53;
			constexpr double air_density = 1.11935;
			constexpr double reciprocal_speed_of_sound = 0.00307096;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 23.8884;

			const double result = runner.calculate_resistive_force(route_segment, weather_data, speed);
			constexpr double expected = 3340.46;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {-60.9472, -156.527};
			constexpr GeographicalCoordinate end_coordinate = {-76.0715, -32.8195};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 60.1465;
			constexpr double weather_station = 0.521674;
			constexpr double distance = 43.992;
			constexpr double heading = 0.541875;
			constexpr double elevation = 337.275;
			constexpr double grade = -0.233332;
			constexpr double road_incline_angle = -0.392109;
			constexpr double sine_road_incline_angle = -0.382138;
			constexpr double gravity = 9.78099;
			constexpr double gravity_times_sine_road_incline_angle = -3.73769;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 38.0162;
			constexpr double wind_direction = 3.85596;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 208.055;
			constexpr double air_temp = 39.7845;
			constexpr double pressure = 1003.45;
			constexpr double air_density = 1.01308;
			constexpr double reciprocal_speed_of_sound = 0.00296076;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 6.0014;

			const double result = runner.calculate_resistive_force(route_segment, weather_data, speed);
			constexpr double expected = -2355.81;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {29.3378, -162.891};
			constexpr GeographicalCoordinate end_coordinate = {43.7643, 134.173};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 23.9189;
			constexpr double weather_station = 5.54629;
			constexpr double distance = 88.1711;
			constexpr double heading = 4.79511;
			constexpr double elevation = 160.855;
			constexpr double grade = -0.306825;
			constexpr double road_incline_angle = -1.22832;
			constexpr double sine_road_incline_angle = -0.941926;
			constexpr double gravity = 9.81527;
			constexpr double gravity_times_sine_road_incline_angle = -9.24526;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 49.1485;
			constexpr double wind_direction = 2.22802;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 385.329;
			constexpr double air_temp = 16.1052;
			constexpr double pressure = 932.144;
			constexpr double air_density = 1.27845;
			constexpr double reciprocal_speed_of_sound = 0.00305726;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 24.1073;

			const double result = runner.calculate_resistive_force(route_segment, weather_data, speed);
			constexpr double expected = -5828.67;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 2") {
		constexpr double drag_coefficient = 0.00508121;
		constexpr double frontal_area = 3.69328;
		constexpr double array_area = 7.22128;
		constexpr double array_efficiency = 19.2306;
		constexpr double energy_capacity = 370.568;
		constexpr double min_voltage = 107.706;
		constexpr double max_voltage = 151.162;
		constexpr double resistance = 0.629805;
		constexpr double hysteresis_loss = 3.86715;
		constexpr double eddy_current_loss_coefficient = 0.0208373;
		constexpr double alpha = 9.84545;
		constexpr double beta = 6.52527;
		constexpr double a = -5.24307;
		constexpr double b = 8.42994e-06;
		constexpr double c = 0.20256;
		constexpr double pressure_at_stc = 160.97;
		constexpr double mass = 570.008;
		constexpr double wheel_radius = 0.294572;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		const auto runner = RaceSegmentRunner(car);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {40.1037, -145.163};
			constexpr GeographicalCoordinate end_coordinate = {-81.6748, 100.38};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 120.29;
			constexpr double weather_station = 4.80183;
			constexpr double distance = 79.6964;
			constexpr double heading = 2.94999;
			constexpr double elevation = 253.325;
			constexpr double grade = 0.159485;
			constexpr double road_incline_angle = -0.599526;
			constexpr double sine_road_incline_angle = -0.564251;
			constexpr double gravity = 9.78019;
			constexpr double gravity_times_sine_road_incline_angle = -5.51848;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 30.44;
			constexpr double wind_direction = 2.81119;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 333.979;
			constexpr double air_temp = -13.393;
			constexpr double pressure = 970.145;
			constexpr double air_density = 1.14949;
			constexpr double reciprocal_speed_of_sound = 0.0030527;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 15.1674;

			const double result = runner.calculate_resistive_force(route_segment, weather_data, speed);
			constexpr double expected = 8.8871e+48;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {-7.11268, -142.394};
			constexpr GeographicalCoordinate end_coordinate = {-2.8087, -70.6879};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 130.463;
			constexpr double weather_station = 6.41477;
			constexpr double distance = 44.4679;
			constexpr double heading = 4.98285;
			constexpr double elevation = 338.513;
			constexpr double grade = 0.602755;
			constexpr double road_incline_angle = 0.578819;
			constexpr double sine_road_incline_angle = 0.547036;
			constexpr double gravity = 9.808;
			constexpr double gravity_times_sine_road_incline_angle = 5.36533;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 20.8154;
			constexpr double wind_direction = 6.14154;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 316.18;
			constexpr double air_temp = -30.8992;
			constexpr double pressure = 994.962;
			constexpr double air_density = 1.20683;
			constexpr double reciprocal_speed_of_sound = 0.00301725;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 14.715;

			const double result = runner.calculate_resistive_force(route_segment, weather_data, speed);
			constexpr double expected = 8.51664e+48;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {53.6204, 89.0005};
			constexpr GeographicalCoordinate end_coordinate = {-15.8739, -9.97141};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 145.983;
			constexpr double weather_station = 2.92404;
			constexpr double distance = 42.2941;
			constexpr double heading = 1.65157;
			constexpr double elevation = 88.769;
			constexpr double grade = -0.684405;
			constexpr double road_incline_angle = 0.197563;
			constexpr double sine_road_incline_angle = 0.19628;
			constexpr double gravity = 9.81684;
			constexpr double gravity_times_sine_road_incline_angle = 1.92685;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 21.5034;
			constexpr double wind_direction = 3.81796;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 702.942;
			constexpr double air_temp = -29.3149;
			constexpr double pressure = 922.1;
			constexpr double air_density = 1.26716;
			constexpr double reciprocal_speed_of_sound = 0.00301008;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 22.8587;

			const double result = runner.calculate_resistive_force(route_segment, weather_data, speed);
			constexpr double expected = 2.07857e+49;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 3") {
		constexpr double drag_coefficient = 0.0097444;
		constexpr double frontal_area = 2.3341;
		constexpr double array_area = 3.33464;
		constexpr double array_efficiency = 23.6518;
		constexpr double energy_capacity = 1267.24;
		constexpr double min_voltage = 77.2134;
		constexpr double max_voltage = 137.058;
		constexpr double resistance = 0.463117;
		constexpr double hysteresis_loss = 4.82454;
		constexpr double eddy_current_loss_coefficient = 0.0276347;
		constexpr double alpha = -8.54475;
		constexpr double beta = 4.02513;
		constexpr double a = -7.66044;
		constexpr double b = -9.55414e-06;
		constexpr double c = -0.666903;
		constexpr double pressure_at_stc = 176.976;
		constexpr double mass = 879.388;
		constexpr double wheel_radius = 0.173392;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		const auto runner = RaceSegmentRunner(car);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {-56.5341, 179.365};
			constexpr GeographicalCoordinate end_coordinate = {-33.5191, -161.909};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 93.4372;
			constexpr double weather_station = 8.44176;
			constexpr double distance = 9.97845;
			constexpr double heading = 1.24461;
			constexpr double elevation = -195.804;
			constexpr double grade = -0.614971;
			constexpr double road_incline_angle = -0.432792;
			constexpr double sine_road_incline_angle = -0.419407;
			constexpr double gravity = 9.78729;
			constexpr double gravity_times_sine_road_incline_angle = -4.10486;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 38.711;
			constexpr double wind_direction = 3.93639;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 375.794;
			constexpr double air_temp = -11.8257;
			constexpr double pressure = 1086.65;
			constexpr double air_density = 1.00086;
			constexpr double reciprocal_speed_of_sound = 0.0029917;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 21.0662;

			const double result = runner.calculate_resistive_force(route_segment, weather_data, speed);
			constexpr double expected = -3609.24;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {-57.1577, 151.534};
			constexpr GeographicalCoordinate end_coordinate = {-87.4792, 169.334};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 12.3765;
			constexpr double weather_station = 0.00219256;
			constexpr double distance = 67.1066;
			constexpr double heading = 1.9094;
			constexpr double elevation = 409.782;
			constexpr double grade = 0.440812;
			constexpr double road_incline_angle = 0.324025;
			constexpr double sine_road_incline_angle = 0.318384;
			constexpr double gravity = 9.80409;
			constexpr double gravity_times_sine_road_incline_angle = 3.12147;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 8.45616;
			constexpr double wind_direction = 3.75273;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 512.42;
			constexpr double air_temp = 44.3877;
			constexpr double pressure = 1007.91;
			constexpr double air_density = 1.11625;
			constexpr double reciprocal_speed_of_sound = 0.0029776;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 22.4543;

			const double result = runner.calculate_resistive_force(route_segment, weather_data, speed);
			constexpr double expected = 2748.27;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {47.9712, -71.652};
			constexpr GeographicalCoordinate end_coordinate = {6.33426, 101.781};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 59.8011;
			constexpr double weather_station = 0.600526;
			constexpr double distance = 6.06344;
			constexpr double heading = 4.14961;
			constexpr double elevation = 271.254;
			constexpr double grade = -0.740868;
			constexpr double road_incline_angle = 1.26769;
			constexpr double sine_road_incline_angle = 0.954415;
			constexpr double gravity = 9.78312;
			constexpr double gravity_times_sine_road_incline_angle = 9.33716;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 15.9599;
			constexpr double wind_direction = 0.856818;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 762.288;
			constexpr double air_temp = -11.1398;
			constexpr double pressure = 1077.56;
			constexpr double air_density = 1.08731;
			constexpr double reciprocal_speed_of_sound = 0.00297774;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 10.6438;

			const double result = runner.calculate_resistive_force(route_segment, weather_data, speed);
			constexpr double expected = 8210.89;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 4") {
		constexpr double drag_coefficient = 0.00690226;
		constexpr double frontal_area = 4.88565;
		constexpr double array_area = 6.52666;
		constexpr double array_efficiency = 20.6273;
		constexpr double energy_capacity = 6107.11;
		constexpr double min_voltage = 141.357;
		constexpr double max_voltage = 169.458;
		constexpr double resistance = 0.47068;
		constexpr double hysteresis_loss = 1.05045;
		constexpr double eddy_current_loss_coefficient = 0.0358586;
		constexpr double alpha = 5.88377;
		constexpr double beta = -6.66771;
		constexpr double a = 2.21029;
		constexpr double b = -8.31457e-06;
		constexpr double c = 0.0177383;
		constexpr double pressure_at_stc = 131.885;
		constexpr double mass = 271.691;
		constexpr double wheel_radius = 0.292695;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		const auto runner = RaceSegmentRunner(car);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {-4.90352, -55.4226};
			constexpr GeographicalCoordinate end_coordinate = {54.6431, -41.266};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 33.7354;
			constexpr double weather_station = 6.24758;
			constexpr double distance = 34.2411;
			constexpr double heading = 4.52485;
			constexpr double elevation = 67.8146;
			constexpr double grade = -0.647793;
			constexpr double road_incline_angle = -0.674736;
			constexpr double sine_road_incline_angle = -0.624691;
			constexpr double gravity = 9.78064;
			constexpr double gravity_times_sine_road_incline_angle = -6.10988;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 49.3551;
			constexpr double wind_direction = 5.88961;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 750.819;
			constexpr double air_temp = 8.28084;
			constexpr double pressure = 1092.52;
			constexpr double air_density = 1.0233;
			constexpr double reciprocal_speed_of_sound = 0.00290265;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 19.5246;

			const double result = runner.calculate_resistive_force(route_segment, weather_data, speed);
			constexpr double expected = -1644.86;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {-45.3682, -45.7174};
			constexpr GeographicalCoordinate end_coordinate = {-27.96, -88.9449};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 140.457;
			constexpr double weather_station = 5.0109;
			constexpr double distance = 81.1052;
			constexpr double heading = 1.12793;
			constexpr double elevation = -47.5205;
			constexpr double grade = 0.0132465;
			constexpr double road_incline_angle = 0.926183;
			constexpr double sine_road_incline_angle = 0.799332;
			constexpr double gravity = 9.80742;
			constexpr double gravity_times_sine_road_incline_angle = 7.83939;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 37.7315;
			constexpr double wind_direction = 3.14344;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 569.724;
			constexpr double air_temp = 46.2972;
			constexpr double pressure = 1019.61;
			constexpr double air_density = 1.05993;
			constexpr double reciprocal_speed_of_sound = 0.0029306;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 12.5024;

			const double result = runner.calculate_resistive_force(route_segment, weather_data, speed);
			constexpr double expected = 2130.14;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {-9.82045, 121.921};
			constexpr GeographicalCoordinate end_coordinate = {24.1274, -37.5229};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 155.26;
			constexpr double weather_station = 5.04713;
			constexpr double distance = 86.856;
			constexpr double heading = 0.999759;
			constexpr double elevation = 232.676;
			constexpr double grade = 0.822711;
			constexpr double road_incline_angle = 0.0134556;
			constexpr double sine_road_incline_angle = 0.0134552;
			constexpr double gravity = 9.78487;
			constexpr double gravity_times_sine_road_incline_angle = 0.131658;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 10.3941;
			constexpr double wind_direction = 2.18045;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 178.301;
			constexpr double air_temp = -39.5177;
			constexpr double pressure = 979.878;
			constexpr double air_density = 1.07245;
			constexpr double reciprocal_speed_of_sound = 0.00303813;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 4.37863;

			const double result = runner.calculate_resistive_force(route_segment, weather_data, speed);
			constexpr double expected = 37.0254;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 5") {
		constexpr double drag_coefficient = 0.00570436;
		constexpr double frontal_area = 8.39522;
		constexpr double array_area = 2.45502;
		constexpr double array_efficiency = 29.7876;
		constexpr double energy_capacity = 4309.09;
		constexpr double min_voltage = 114.196;
		constexpr double max_voltage = 114.886;
		constexpr double resistance = 0.291425;
		constexpr double hysteresis_loss = 1.90134;
		constexpr double eddy_current_loss_coefficient = 0.0211406;
		constexpr double alpha = -5.28969;
		constexpr double beta = -5.98392;
		constexpr double a = 1.90297;
		constexpr double b = 3.09175e-07;
		constexpr double c = -0.698806;
		constexpr double pressure_at_stc = 126.248;
		constexpr double mass = 258.602;
		constexpr double wheel_radius = 0.428088;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		const auto runner = RaceSegmentRunner(car);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {-28.3566, 25.5182};
			constexpr GeographicalCoordinate end_coordinate = {10.8026, 13.3132};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 157.471;
			constexpr double weather_station = 1.50262;
			constexpr double distance = 41.894;
			constexpr double heading = 1.59768;
			constexpr double elevation = 486.384;
			constexpr double grade = 0.727858;
			constexpr double road_incline_angle = -0.175337;
			constexpr double sine_road_incline_angle = -0.17444;
			constexpr double gravity = 9.81502;
			constexpr double gravity_times_sine_road_incline_angle = -1.71213;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 34.2757;
			constexpr double wind_direction = 3.78993;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 905.857;
			constexpr double air_temp = -40.0204;
			constexpr double pressure = 911.139;
			constexpr double air_density = 1.10038;
			constexpr double reciprocal_speed_of_sound = 0.00308156;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 20.0371;

			const double result = runner.calculate_resistive_force(route_segment, weather_data, speed);
			constexpr double expected = -442.761;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {35.4466, -61.3417};
			constexpr GeographicalCoordinate end_coordinate = {37.6607, 109.545};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 27.6106;
			constexpr double weather_station = 2.29754;
			constexpr double distance = 47.3395;
			constexpr double heading = 2.25121;
			constexpr double elevation = 173.887;
			constexpr double grade = 0.327032;
			constexpr double road_incline_angle = -0.573549;
			constexpr double sine_road_incline_angle = -0.542617;
			constexpr double gravity = 9.78715;
			constexpr double gravity_times_sine_road_incline_angle = -5.31067;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 47.8919;
			constexpr double wind_direction = 6.05837;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 559.914;
			constexpr double air_temp = 6.06619;
			constexpr double pressure = 945.463;
			constexpr double air_density = 1.07023;
			constexpr double reciprocal_speed_of_sound = 0.00290397;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 2.97138;

			const double result = runner.calculate_resistive_force(route_segment, weather_data, speed);
			constexpr double expected = -1342.5;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {-45.0106, 73.8484};
			constexpr GeographicalCoordinate end_coordinate = {-41.8044, -125.901};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 65.0957;
			constexpr double weather_station = 7.59401;
			constexpr double distance = 30.0751;
			constexpr double heading = 2.09456;
			constexpr double elevation = -441.873;
			constexpr double grade = -0.857753;
			constexpr double road_incline_angle = 0.945143;
			constexpr double sine_road_incline_angle = 0.810581;
			constexpr double gravity = 9.79755;
			constexpr double gravity_times_sine_road_incline_angle = 7.94171;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 40.3161;
			constexpr double wind_direction = 2.72791;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 909.115;
			constexpr double air_temp = 39.3147;
			constexpr double pressure = 1011.76;
			constexpr double air_density = 1.29601;
			constexpr double reciprocal_speed_of_sound = 0.00306039;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 12.8835;

			const double result = runner.calculate_resistive_force(route_segment, weather_data, speed);
			constexpr double expected = 2117.65;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 6") {
		constexpr double drag_coefficient = 0.00994225;
		constexpr double frontal_area = 3.76998;
		constexpr double array_area = 7.10473;
		constexpr double array_efficiency = 23.7002;
		constexpr double energy_capacity = 3291.74;
		constexpr double min_voltage = 75.6667;
		constexpr double max_voltage = 151.632;
		constexpr double resistance = 0.999295;
		constexpr double hysteresis_loss = 4.98507;
		constexpr double eddy_current_loss_coefficient = 0.0416582;
		constexpr double alpha = -2.97403;
		constexpr double beta = -4.42737;
		constexpr double a = -8.17578;
		constexpr double b = 2.30675e-06;
		constexpr double c = -0.650122;
		constexpr double pressure_at_stc = 196.785;
		constexpr double mass = 498.114;
		constexpr double wheel_radius = 0.115404;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		const auto runner = RaceSegmentRunner(car);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {-64.2257, -100.617};
			constexpr GeographicalCoordinate end_coordinate = {33.4165, -169.17};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 2.48776;
			constexpr double weather_station = 0.516414;
			constexpr double distance = 22.5122;
			constexpr double heading = 4.33622;
			constexpr double elevation = 272.494;
			constexpr double grade = -0.0252916;
			constexpr double road_incline_angle = -1.25064;
			constexpr double sine_road_incline_angle = -0.949188;
			constexpr double gravity = 9.78665;
			constexpr double gravity_times_sine_road_incline_angle = -9.28936;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 10.9464;
			constexpr double wind_direction = 0.751459;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 876.041;
			constexpr double air_temp = -37.9523;
			constexpr double pressure = 1069.91;
			constexpr double air_density = 1.02531;
			constexpr double reciprocal_speed_of_sound = 0.00306773;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 0.176364;

			const double result = runner.calculate_resistive_force(route_segment, weather_data, speed);
			constexpr double expected = -4625.35;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {-41.8114, 41.7851};
			constexpr GeographicalCoordinate end_coordinate = {-22.3228, 43.0319};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 180.601;
			constexpr double weather_station = 9.76238;
			constexpr double distance = 99.1377;
			constexpr double heading = 1.76942;
			constexpr double elevation = -398.431;
			constexpr double grade = -0.362796;
			constexpr double road_incline_angle = 0.210133;
			constexpr double sine_road_incline_angle = 0.20859;
			constexpr double gravity = 9.80775;
			constexpr double gravity_times_sine_road_incline_angle = 2.0458;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 9.39931;
			constexpr double wind_direction = 2.06872;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 790.279;
			constexpr double air_temp = -34.5093;
			constexpr double pressure = 1008.85;
			constexpr double air_density = 1.29507;
			constexpr double reciprocal_speed_of_sound = 0.00300518;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 29.2317;

			const double result = runner.calculate_resistive_force(route_segment, weather_data, speed);
			constexpr double expected = 1054.48;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {82.2699, 160.278};
			constexpr GeographicalCoordinate end_coordinate = {52.6964, -130.993};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 124.15;
			constexpr double weather_station = 6.08744;
			constexpr double distance = 99.3688;
			constexpr double heading = 4.13247;
			constexpr double elevation = -394.99;
			constexpr double grade = 0.485542;
			constexpr double road_incline_angle = 0.836626;
			constexpr double sine_road_incline_angle = 0.742387;
			constexpr double gravity = 9.79631;
			constexpr double gravity_times_sine_road_incline_angle = 7.27266;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 0.107344;
			constexpr double wind_direction = 4.51585;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 590.996;
			constexpr double air_temp = 15.4632;
			constexpr double pressure = 987.861;
			constexpr double air_density = 1.25824;
			constexpr double reciprocal_speed_of_sound = 0.00295937;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 22.3047;

			const double result = runner.calculate_resistive_force(route_segment, weather_data, speed);
			constexpr double expected = 3634.45;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 7") {
		constexpr double drag_coefficient = 0.00276085;
		constexpr double frontal_area = 5.67178;
		constexpr double array_area = 6.38864;
		constexpr double array_efficiency = 21.8467;
		constexpr double energy_capacity = 4346.66;
		constexpr double min_voltage = 96.0137;
		constexpr double max_voltage = 131.421;
		constexpr double resistance = 0.684682;
		constexpr double hysteresis_loss = 2.18817;
		constexpr double eddy_current_loss_coefficient = 0.0395594;
		constexpr double alpha = 3.50509;
		constexpr double beta = -8.19097;
		constexpr double a = -5.73584;
		constexpr double b = 3.08101e-06;
		constexpr double c = -0.645935;
		constexpr double pressure_at_stc = 178.623;
		constexpr double mass = 587.262;
		constexpr double wheel_radius = 0.404461;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		const auto runner = RaceSegmentRunner(car);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {-16.6952, 129.56};
			constexpr GeographicalCoordinate end_coordinate = {-36.47, 132.2};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 82.3751;
			constexpr double weather_station = 9.93272;
			constexpr double distance = 54.894;
			constexpr double heading = 4.68399;
			constexpr double elevation = 298.56;
			constexpr double grade = 0.32822;
			constexpr double road_incline_angle = 1.01347;
			constexpr double sine_road_incline_angle = 0.848673;
			constexpr double gravity = 9.80201;
			constexpr double gravity_times_sine_road_incline_angle = 8.3187;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 37.3595;
			constexpr double wind_direction = 5.87177;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 612.999;
			constexpr double air_temp = -12.7799;
			constexpr double pressure = 1095.42;
			constexpr double air_density = 1.11427;
			constexpr double reciprocal_speed_of_sound = 0.0030836;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 8.57126;

			const double result = runner.calculate_resistive_force(route_segment, weather_data, speed);
			constexpr double expected = 4889.69;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {30.5615, 154.872};
			constexpr GeographicalCoordinate end_coordinate = {-56.0858, 2.85783};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 51.5685;
			constexpr double weather_station = 3.13274;
			constexpr double distance = 9.25465;
			constexpr double heading = 4.86704;
			constexpr double elevation = 343.616;
			constexpr double grade = -0.792709;
			constexpr double road_incline_angle = 0.681738;
			constexpr double sine_road_incline_angle = 0.630144;
			constexpr double gravity = 9.80817;
			constexpr double gravity_times_sine_road_incline_angle = 6.18056;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 33.935;
			constexpr double wind_direction = 4.08733;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 271.347;
			constexpr double air_temp = 24.7793;
			constexpr double pressure = 948.122;
			constexpr double air_density = 1.06651;
			constexpr double reciprocal_speed_of_sound = 0.00303582;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 19.2837;

			const double result = runner.calculate_resistive_force(route_segment, weather_data, speed);
			constexpr double expected = 3645.34;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {63.0109, -2.35421};
			constexpr GeographicalCoordinate end_coordinate = {7.37281, 10.095};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 40.7606;
			constexpr double weather_station = 4.22673;
			constexpr double distance = 55.3989;
			constexpr double heading = 2.98492;
			constexpr double elevation = 245.645;
			constexpr double grade = 0.64982;
			constexpr double road_incline_angle = 1.50732;
			constexpr double sine_road_incline_angle = 0.997986;
			constexpr double gravity = 9.79383;
			constexpr double gravity_times_sine_road_incline_angle = 9.77411;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 22.1719;
			constexpr double wind_direction = 2.10784;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 740.264;
			constexpr double air_temp = -20.0816;
			constexpr double pressure = 1012.4;
			constexpr double air_density = 1.22158;
			constexpr double reciprocal_speed_of_sound = 0.00302094;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 18.0438;

			const double result = runner.calculate_resistive_force(route_segment, weather_data, speed);
			constexpr double expected = 5749.89;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 8") {
		constexpr double drag_coefficient = 0.00861489;
		constexpr double frontal_area = 9.02406;
		constexpr double array_area = 4.54133;
		constexpr double array_efficiency = 20.894;
		constexpr double energy_capacity = 4861.38;
		constexpr double min_voltage = 105.714;
		constexpr double max_voltage = 154.164;
		constexpr double resistance = 0.843364;
		constexpr double hysteresis_loss = 4.15101;
		constexpr double eddy_current_loss_coefficient = 0.00123561;
		constexpr double alpha = -3.65178;
		constexpr double beta = -1.44692;
		constexpr double a = 6.3926;
		constexpr double b = 4.26756e-06;
		constexpr double c = -0.609932;
		constexpr double pressure_at_stc = 118.543;
		constexpr double mass = 631.558;
		constexpr double wheel_radius = 0.150288;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		const auto runner = RaceSegmentRunner(car);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {10.9502, 44.2105};
			constexpr GeographicalCoordinate end_coordinate = {-16.6115, -82.956};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 72.2628;
			constexpr double weather_station = 2.37904;
			constexpr double distance = 97.7468;
			constexpr double heading = 3.0448;
			constexpr double elevation = 1.75857;
			constexpr double grade = -0.919187;
			constexpr double road_incline_angle = -0.762036;
			constexpr double sine_road_incline_angle = -0.690396;
			constexpr double gravity = 9.8099;
			constexpr double gravity_times_sine_road_incline_angle = -6.77272;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 14.4551;
			constexpr double wind_direction = 3.31347;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 617.37;
			constexpr double air_temp = -22.7766;
			constexpr double pressure = 1090.89;
			constexpr double air_density = 1.18546;
			constexpr double reciprocal_speed_of_sound = 0.00309122;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 13.8185;

			const double result = runner.calculate_resistive_force(route_segment, weather_data, speed);
			constexpr double expected = -4241.87;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {-68.4092, -115.824};
			constexpr GeographicalCoordinate end_coordinate = {-52.2369, 111.392};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 90.3016;
			constexpr double weather_station = 0.374111;
			constexpr double distance = 0.539683;
			constexpr double heading = 5.78786;
			constexpr double elevation = -36.5526;
			constexpr double grade = -0.290604;
			constexpr double road_incline_angle = 0.666353;
			constexpr double sine_road_incline_angle = 0.618123;
			constexpr double gravity = 9.78572;
			constexpr double gravity_times_sine_road_incline_angle = 6.04878;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 14.0838;
			constexpr double wind_direction = 2.79877;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 889.78;
			constexpr double air_temp = -27.3256;
			constexpr double pressure = 977.859;
			constexpr double air_density = 1.13107;
			constexpr double reciprocal_speed_of_sound = 0.00302213;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 21.7987;

			const double result = runner.calculate_resistive_force(route_segment, weather_data, speed);
			constexpr double expected = 3822.89;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {-66.4261, -16.179};
			constexpr GeographicalCoordinate end_coordinate = {10.1693, 166.834};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 170.401;
			constexpr double weather_station = 4.5071;
			constexpr double distance = 29.6154;
			constexpr double heading = 0.796743;
			constexpr double elevation = 368.991;
			constexpr double grade = 0.806632;
			constexpr double road_incline_angle = 0.543378;
			constexpr double sine_road_incline_angle = 0.51703;
			constexpr double gravity = 9.81244;
			constexpr double gravity_times_sine_road_incline_angle = 5.07333;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 30.2928;
			constexpr double wind_direction = 5.34655;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 267.66;
			constexpr double air_temp = 31.2053;
			constexpr double pressure = 919.401;
			constexpr double air_density = 1.04405;
			constexpr double reciprocal_speed_of_sound = 0.00291586;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 14.9889;

			const double result = runner.calculate_resistive_force(route_segment, weather_data, speed);
			constexpr double expected = 3208.23;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 9") {
		constexpr double drag_coefficient = 0.0079485;
		constexpr double frontal_area = 9.49838;
		constexpr double array_area = 1.54978;
		constexpr double array_efficiency = 20.1868;
		constexpr double energy_capacity = 1082.51;
		constexpr double min_voltage = 101.707;
		constexpr double max_voltage = 157.026;
		constexpr double resistance = 0.387687;
		constexpr double hysteresis_loss = 2.08802;
		constexpr double eddy_current_loss_coefficient = 0.0109292;
		constexpr double alpha = -8.94504;
		constexpr double beta = 3.03434;
		constexpr double a = 3.74879;
		constexpr double b = -7.10527e-06;
		constexpr double c = 0.529032;
		constexpr double pressure_at_stc = 121.846;
		constexpr double mass = 539.451;
		constexpr double wheel_radius = 0.248818;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		const auto runner = RaceSegmentRunner(car);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {-19.1053, 25.5888};
			constexpr GeographicalCoordinate end_coordinate = {52.3677, -1.47039};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 101.864;
			constexpr double weather_station = 5.67732;
			constexpr double distance = 30.8911;
			constexpr double heading = 0.395498;
			constexpr double elevation = -379.84;
			constexpr double grade = -0.156746;
			constexpr double road_incline_angle = -0.998481;
			constexpr double sine_road_incline_angle = -0.840649;
			constexpr double gravity = 9.79242;
			constexpr double gravity_times_sine_road_incline_angle = -8.232;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 28.2199;
			constexpr double wind_direction = 0.977125;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 518.651;
			constexpr double air_temp = 47.799;
			constexpr double pressure = 1047.61;
			constexpr double air_density = 1.22014;
			constexpr double reciprocal_speed_of_sound = 0.00303471;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 23.2792;

			const double result = runner.calculate_resistive_force(route_segment, weather_data, speed);
			constexpr double expected = -4339.63;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {-54.7477, 85.9914};
			constexpr GeographicalCoordinate end_coordinate = {-45.0708, -4.84212};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 164.193;
			constexpr double weather_station = 7.20117;
			constexpr double distance = 15.0531;
			constexpr double heading = 0.870671;
			constexpr double elevation = 110.501;
			constexpr double grade = -0.809102;
			constexpr double road_incline_angle = -1.12781;
			constexpr double sine_road_incline_angle = -0.903477;
			constexpr double gravity = 9.8102;
			constexpr double gravity_times_sine_road_incline_angle = -8.86329;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 42.764;
			constexpr double wind_direction = 2.3675;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 480.859;
			constexpr double air_temp = -41.2563;
			constexpr double pressure = 914.316;
			constexpr double air_density = 1.21411;
			constexpr double reciprocal_speed_of_sound = 0.00297251;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 2.4668;

			const double result = runner.calculate_resistive_force(route_segment, weather_data, speed);
			constexpr double expected = -4779.86;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {49.4224, 153.265};
			constexpr GeographicalCoordinate end_coordinate = {-32.5317, 22.6842};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 94.6678;
			constexpr double weather_station = 1.6617;
			constexpr double distance = 65.8819;
			constexpr double heading = 4.62451;
			constexpr double elevation = 209.275;
			constexpr double grade = -0.637275;
			constexpr double road_incline_angle = -0.0458057;
			constexpr double sine_road_incline_angle = -0.0457897;
			constexpr double gravity = 9.80666;
			constexpr double gravity_times_sine_road_incline_angle = -0.449044;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 16.7566;
			constexpr double wind_direction = 0.270857;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 868.221;
			constexpr double air_temp = 10.1453;
			constexpr double pressure = 1020.57;
			constexpr double air_density = 1.24814;
			constexpr double reciprocal_speed_of_sound = 0.00292019;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 25.4073;

			const double result = runner.calculate_resistive_force(route_segment, weather_data, speed);
			constexpr double expected = -224.277;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
	}
}
TEST_CASE("RaceSegmentRunner: calculate_power_out", "[RaceSegmentRunner]") {
	SECTION("Random Test 0") {
		constexpr double drag_coefficient = 0.00746297;
		constexpr double frontal_area = 5.1091;
		constexpr double array_area = 5.40217;
		constexpr double array_efficiency = 15.6878;
		constexpr double energy_capacity = 1012.3;
		constexpr double min_voltage = 89.9017;
		constexpr double max_voltage = 153.062;
		constexpr double resistance = 0.521814;
		constexpr double hysteresis_loss = 1.18665;
		constexpr double eddy_current_loss_coefficient = 0.0359297;
		constexpr double alpha = -4.1364;
		constexpr double beta = 4.15235;
		constexpr double a = -4.35732;
		constexpr double b = -6.99593e-06;
		constexpr double c = -0.328451;
		constexpr double pressure_at_stc = 112.999;
		constexpr double mass = 853.88;
		constexpr double wheel_radius = 0.123933;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		const auto runner = RaceSegmentRunner(car);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {13.3021, 106.958};
			constexpr GeographicalCoordinate end_coordinate = {-87.0224, 6.62966};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 40.7638;
			constexpr double weather_station = 8.79722;
			constexpr double distance = 56.6406;
			constexpr double heading = 3.73463;
			constexpr double elevation = 489.448;
			constexpr double grade = -0.931428;
			constexpr double road_incline_angle = -0.748361;
			constexpr double sine_road_incline_angle = -0.680439;
			constexpr double gravity = 9.80223;
			constexpr double gravity_times_sine_road_incline_angle = -6.66982;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 5.06959;
			constexpr double wind_direction = 0.786268;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 316.24;
			constexpr double air_temp = 21.1189;
			constexpr double pressure = 947.987;
			constexpr double air_density = 1.17286;
			constexpr double reciprocal_speed_of_sound = 0.00292415;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 6.89735;

			const double result = runner.calculate_power_out(route_segment, weather_data, speed);
			constexpr double expected = -8.92391e+10;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {13.577, -10.2254};
			constexpr GeographicalCoordinate end_coordinate = {66.9022, -80.339};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 139.321;
			constexpr double weather_station = 4.52488;
			constexpr double distance = 46.6454;
			constexpr double heading = 3.85446;
			constexpr double elevation = -163.715;
			constexpr double grade = -0.222073;
			constexpr double road_incline_angle = -1.17431;
			constexpr double sine_road_incline_angle = -0.922426;
			constexpr double gravity = 9.78397;
			constexpr double gravity_times_sine_road_incline_angle = -9.02499;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 37.5463;
			constexpr double wind_direction = 6.04476;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 969.443;
			constexpr double air_temp = 1.12007;
			constexpr double pressure = 944.143;
			constexpr double air_density = 1.08935;
			constexpr double reciprocal_speed_of_sound = 0.00304727;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 13.3761;

			const double result = runner.calculate_power_out(route_segment, weather_data, speed);
			constexpr double expected = -6.35875e+11;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {18.0252, -141.744};
			constexpr GeographicalCoordinate end_coordinate = {-51.3472, 130.092};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 37.9502;
			constexpr double weather_station = 1.9856;
			constexpr double distance = 59.3442;
			constexpr double heading = 3.57962;
			constexpr double elevation = 53.4015;
			constexpr double grade = 0.843773;
			constexpr double road_incline_angle = 0.0766383;
			constexpr double sine_road_incline_angle = 0.0765633;
			constexpr double gravity = 9.80966;
			constexpr double gravity_times_sine_road_incline_angle = 0.75106;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 27.6338;
			constexpr double wind_direction = 4.96911;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 149.426;
			constexpr double air_temp = 42.1505;
			constexpr double pressure = 911.976;
			constexpr double air_density = 1.07993;
			constexpr double reciprocal_speed_of_sound = 0.00293743;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 21.3918;

			const double result = runner.calculate_power_out(route_segment, weather_data, speed);
			constexpr double expected = -2.62023e+12;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 1") {
		constexpr double drag_coefficient = 0.00822896;
		constexpr double frontal_area = 6.24257;
		constexpr double array_area = 3.35435;
		constexpr double array_efficiency = 18.2807;
		constexpr double energy_capacity = 586.797;
		constexpr double min_voltage = 87.7673;
		constexpr double max_voltage = 89.6944;
		constexpr double resistance = 0.967146;
		constexpr double hysteresis_loss = 4.84592;
		constexpr double eddy_current_loss_coefficient = 0.0465566;
		constexpr double alpha = -4.42387;
		constexpr double beta = -3.75346;
		constexpr double a = 0.531361;
		constexpr double b = 9.62294e-06;
		constexpr double c = 0.241877;
		constexpr double pressure_at_stc = 161.454;
		constexpr double mass = 466.003;
		constexpr double wheel_radius = 0.443411;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		const auto runner = RaceSegmentRunner(car);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {0.649605, -118.741};
			constexpr GeographicalCoordinate end_coordinate = {86.6571, 108.538};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 193.637;
			constexpr double weather_station = 8.73149;
			constexpr double distance = 18.2765;
			constexpr double heading = 4.10751;
			constexpr double elevation = 356.31;
			constexpr double grade = 0.874101;
			constexpr double road_incline_angle = 1.30934;
			constexpr double sine_road_incline_angle = 0.966016;
			constexpr double gravity = 9.79213;
			constexpr double gravity_times_sine_road_incline_angle = 9.45935;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 8.33291;
			constexpr double wind_direction = 1.75391;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 728.482;
			constexpr double air_temp = 8.6983;
			constexpr double pressure = 1078.34;
			constexpr double air_density = 1.06892;
			constexpr double reciprocal_speed_of_sound = 0.00301323;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 1.83735;

			const double result = runner.calculate_power_out(route_segment, weather_data, speed);
			constexpr double expected = 8105.06;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {84.8274, 27.8099};
			constexpr GeographicalCoordinate end_coordinate = {12.8398, -174.353};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 35.2894;
			constexpr double weather_station = 4.09195;
			constexpr double distance = 75.9369;
			constexpr double heading = 0.837439;
			constexpr double elevation = -280.977;
			constexpr double grade = 0.287238;
			constexpr double road_incline_angle = 1.06508;
			constexpr double sine_road_incline_angle = 0.874829;
			constexpr double gravity = 9.80932;
			constexpr double gravity_times_sine_road_incline_angle = 8.58148;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 3.08268;
			constexpr double wind_direction = 2.19017;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 927.234;
			constexpr double air_temp = -3.03507;
			constexpr double pressure = 911.556;
			constexpr double air_density = 1.12239;
			constexpr double reciprocal_speed_of_sound = 0.00291453;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 6.44615;

			const double result = runner.calculate_power_out(route_segment, weather_data, speed);
			constexpr double expected = 25793;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {79.2523, -51.5849};
			constexpr GeographicalCoordinate end_coordinate = {-42.0448, -100.149};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 80.7169;
			constexpr double weather_station = 4.28191;
			constexpr double distance = 17.8414;
			constexpr double heading = 3.85503;
			constexpr double elevation = 213.389;
			constexpr double grade = 0.209108;
			constexpr double road_incline_angle = -0.847524;
			constexpr double sine_road_incline_angle = -0.749644;
			constexpr double gravity = 9.79724;
			constexpr double gravity_times_sine_road_incline_angle = -7.34445;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 46.2392;
			constexpr double wind_direction = 2.00731;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 289.974;
			constexpr double air_temp = -33.605;
			constexpr double pressure = 1060.85;
			constexpr double air_density = 1.12921;
			constexpr double reciprocal_speed_of_sound = 0.00297444;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 13.4911;

			const double result = runner.calculate_power_out(route_segment, weather_data, speed);
			constexpr double expected = -46167.2;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 2") {
		constexpr double drag_coefficient = 0.00428097;
		constexpr double frontal_area = 4.77764;
		constexpr double array_area = 4.64112;
		constexpr double array_efficiency = 28.1064;
		constexpr double energy_capacity = 360.481;
		constexpr double min_voltage = 75.4928;
		constexpr double max_voltage = 134.486;
		constexpr double resistance = 0.300851;
		constexpr double hysteresis_loss = 4.81612;
		constexpr double eddy_current_loss_coefficient = 0.0177575;
		constexpr double alpha = -3.09273;
		constexpr double beta = 2.66311;
		constexpr double a = -9.08956;
		constexpr double b = 2.91502e-06;
		constexpr double c = 0.356394;
		constexpr double pressure_at_stc = 140.215;
		constexpr double mass = 704.11;
		constexpr double wheel_radius = 0.335318;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		const auto runner = RaceSegmentRunner(car);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {3.23598, -50.0702};
			constexpr GeographicalCoordinate end_coordinate = {-64.5085, -161.614};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 52.7213;
			constexpr double weather_station = 3.81775;
			constexpr double distance = 33.9613;
			constexpr double heading = 0.0685211;
			constexpr double elevation = 243.333;
			constexpr double grade = 0.702326;
			constexpr double road_incline_angle = -0.328008;
			constexpr double sine_road_incline_angle = -0.322158;
			constexpr double gravity = 9.81048;
			constexpr double gravity_times_sine_road_incline_angle = -3.16052;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 34.6654;
			constexpr double wind_direction = 5.50835;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 918.152;
			constexpr double air_temp = 30.9509;
			constexpr double pressure = 956.939;
			constexpr double air_density = 1.1037;
			constexpr double reciprocal_speed_of_sound = 0.00292771;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 14.4503;

			const double result = runner.calculate_power_out(route_segment, weather_data, speed);
			constexpr double expected = 5.30757e+07;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {-48.8556, -140.404};
			constexpr GeographicalCoordinate end_coordinate = {74.9718, 78.8452};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 145.884;
			constexpr double weather_station = 6.70295;
			constexpr double distance = 12.1995;
			constexpr double heading = 1.40018;
			constexpr double elevation = -244.498;
			constexpr double grade = 0.630706;
			constexpr double road_incline_angle = -0.324844;
			constexpr double sine_road_incline_angle = -0.319161;
			constexpr double gravity = 9.79221;
			constexpr double gravity_times_sine_road_incline_angle = -3.12529;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 3.52674;
			constexpr double wind_direction = 3.12897;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 870.176;
			constexpr double air_temp = -13.2605;
			constexpr double pressure = 962.863;
			constexpr double air_density = 1.27754;
			constexpr double reciprocal_speed_of_sound = 0.00291465;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 3.44997;

			const double result = runner.calculate_power_out(route_segment, weather_data, speed);
			constexpr double expected = 598374;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {-81.2049, 136.105};
			constexpr GeographicalCoordinate end_coordinate = {-70.5265, 28.4219};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 21.6158;
			constexpr double weather_station = 3.96986;
			constexpr double distance = 80.5136;
			constexpr double heading = 2.56784;
			constexpr double elevation = 108.45;
			constexpr double grade = 0.409559;
			constexpr double road_incline_angle = -0.202102;
			constexpr double sine_road_incline_angle = -0.200729;
			constexpr double gravity = 9.78202;
			constexpr double gravity_times_sine_road_incline_angle = -1.96354;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 47.9917;
			constexpr double wind_direction = 0.887432;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 486.19;
			constexpr double air_temp = 23.5007;
			constexpr double pressure = 986.543;
			constexpr double air_density = 1.10699;
			constexpr double reciprocal_speed_of_sound = 0.00305494;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 24.9255;

			const double result = runner.calculate_power_out(route_segment, weather_data, speed);
			constexpr double expected = 2.72134e+08;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 3") {
		constexpr double drag_coefficient = 0.00416075;
		constexpr double frontal_area = 3.58499;
		constexpr double array_area = 9.05132;
		constexpr double array_efficiency = 22.3566;
		constexpr double energy_capacity = 2107.26;
		constexpr double min_voltage = 149.457;
		constexpr double max_voltage = 165.889;
		constexpr double resistance = 0.809561;
		constexpr double hysteresis_loss = 1.36035;
		constexpr double eddy_current_loss_coefficient = 0.00318731;
		constexpr double alpha = -0.503661;
		constexpr double beta = -8.9966;
		constexpr double a = -8.65356;
		constexpr double b = -2.74546e-06;
		constexpr double c = -0.262665;
		constexpr double pressure_at_stc = 168.313;
		constexpr double mass = 971.368;
		constexpr double wheel_radius = 0.257415;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		const auto runner = RaceSegmentRunner(car);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {-3.15304, -3.82435};
			constexpr GeographicalCoordinate end_coordinate = {-52.2102, 62.3279};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 97.315;
			constexpr double weather_station = 7.17611;
			constexpr double distance = 17.0179;
			constexpr double heading = 4.02613;
			constexpr double elevation = 372.768;
			constexpr double grade = 0.450124;
			constexpr double road_incline_angle = -0.687427;
			constexpr double sine_road_incline_angle = -0.634551;
			constexpr double gravity = 9.81623;
			constexpr double gravity_times_sine_road_incline_angle = -6.2289;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 30.189;
			constexpr double wind_direction = 5.50267;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 637.438;
			constexpr double air_temp = -39.1973;
			constexpr double pressure = 1095.05;
			constexpr double air_density = 1.0348;
			constexpr double reciprocal_speed_of_sound = 0.00303911;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 18.1221;

			const double result = runner.calculate_power_out(route_segment, weather_data, speed);
			constexpr double expected = -109586;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {-29.8004, 10.0262};
			constexpr GeographicalCoordinate end_coordinate = {-55.3079, -98.7343};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 119.905;
			constexpr double weather_station = 3.32154;
			constexpr double distance = 92.7094;
			constexpr double heading = 3.20625;
			constexpr double elevation = 290.51;
			constexpr double grade = 0.918583;
			constexpr double road_incline_angle = -0.849651;
			constexpr double sine_road_incline_angle = -0.75105;
			constexpr double gravity = 9.80024;
			constexpr double gravity_times_sine_road_incline_angle = -7.36047;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 30.984;
			constexpr double wind_direction = 5.15072;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 790.889;
			constexpr double air_temp = -28.807;
			constexpr double pressure = 1037.82;
			constexpr double air_density = 1.11584;
			constexpr double reciprocal_speed_of_sound = 0.00300264;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 22.3246;

			const double result = runner.calculate_power_out(route_segment, weather_data, speed);
			constexpr double expected = -159591;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {22.6028, -107.302};
			constexpr GeographicalCoordinate end_coordinate = {2.83738, 66.3401};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 3.13798;
			constexpr double weather_station = 6.99709;
			constexpr double distance = 51.8619;
			constexpr double heading = 3.71038;
			constexpr double elevation = 12.0794;
			constexpr double grade = 0.147524;
			constexpr double road_incline_angle = -0.52302;
			constexpr double sine_road_incline_angle = -0.499499;
			constexpr double gravity = 9.81659;
			constexpr double gravity_times_sine_road_incline_angle = -4.90337;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 18.2648;
			constexpr double wind_direction = 4.36335;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 39.5447;
			constexpr double air_temp = 42.1395;
			constexpr double pressure = 1083.55;
			constexpr double air_density = 1.00328;
			constexpr double reciprocal_speed_of_sound = 0.00301483;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 29.7953;

			const double result = runner.calculate_power_out(route_segment, weather_data, speed);
			constexpr double expected = -141475;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 4") {
		constexpr double drag_coefficient = 0.0081395;
		constexpr double frontal_area = 6.92965;
		constexpr double array_area = 3.02668;
		constexpr double array_efficiency = 27.364;
		constexpr double energy_capacity = 5470.57;
		constexpr double min_voltage = 141.068;
		constexpr double max_voltage = 151.758;
		constexpr double resistance = 0.618756;
		constexpr double hysteresis_loss = 1.06705;
		constexpr double eddy_current_loss_coefficient = 0.0114172;
		constexpr double alpha = -3.68597;
		constexpr double beta = 6.62292;
		constexpr double a = -7.05431;
		constexpr double b = -4.37053e-06;
		constexpr double c = -0.932735;
		constexpr double pressure_at_stc = 176.239;
		constexpr double mass = 140.447;
		constexpr double wheel_radius = 0.373824;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		const auto runner = RaceSegmentRunner(car);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {89.2051, 163.593};
			constexpr GeographicalCoordinate end_coordinate = {-78.9887, -80.9881};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 38.8986;
			constexpr double weather_station = 4.93156;
			constexpr double distance = 93.1558;
			constexpr double heading = 4.52094;
			constexpr double elevation = -343.594;
			constexpr double grade = 0.705994;
			constexpr double road_incline_angle = -0.374665;
			constexpr double sine_road_incline_angle = -0.365961;
			constexpr double gravity = 9.79673;
			constexpr double gravity_times_sine_road_incline_angle = -3.58522;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 43.0024;
			constexpr double wind_direction = 3.56556;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 735.779;
			constexpr double air_temp = 46.5992;
			constexpr double pressure = 980.405;
			constexpr double air_density = 1.22949;
			constexpr double reciprocal_speed_of_sound = 0.00295389;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 18.9584;

			const double result = runner.calculate_power_out(route_segment, weather_data, speed);
			constexpr double expected = -2.65495e+17;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {-88.0798, -93.7901};
			constexpr GeographicalCoordinate end_coordinate = {-63.859, -95.2171};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 171.869;
			constexpr double weather_station = 5.49269;
			constexpr double distance = 9.08875;
			constexpr double heading = 5.17891;
			constexpr double elevation = 177.578;
			constexpr double grade = -0.375827;
			constexpr double road_incline_angle = -0.642914;
			constexpr double sine_road_incline_angle = -0.59953;
			constexpr double gravity = 9.80313;
			constexpr double gravity_times_sine_road_incline_angle = -5.87727;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 10.3049;
			constexpr double wind_direction = 4.34364;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 559.747;
			constexpr double air_temp = 0.581198;
			constexpr double pressure = 1054.11;
			constexpr double air_density = 1.23912;
			constexpr double reciprocal_speed_of_sound = 0.00293625;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 8.10719;

			const double result = runner.calculate_power_out(route_segment, weather_data, speed);
			constexpr double expected = -2.10026e+16;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {-2.17353, 116.937};
			constexpr GeographicalCoordinate end_coordinate = {8.74867, -42.1876};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 132.022;
			constexpr double weather_station = 1.04164;
			constexpr double distance = 47.9234;
			constexpr double heading = 0.398962;
			constexpr double elevation = 243.221;
			constexpr double grade = 0.909136;
			constexpr double road_incline_angle = 1.03707;
			constexpr double sine_road_incline_angle = 0.860919;
			constexpr double gravity = 9.80301;
			constexpr double gravity_times_sine_road_incline_angle = 8.43959;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 44.7359;
			constexpr double wind_direction = 0.819245;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 432.629;
			constexpr double air_temp = 24.7032;
			constexpr double pressure = 1099.26;
			constexpr double air_density = 1.24111;
			constexpr double reciprocal_speed_of_sound = 0.00304404;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 10.8864;

			const double result = runner.calculate_power_out(route_segment, weather_data, speed);
			constexpr double expected = -5.06488e+16;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 5") {
		constexpr double drag_coefficient = 0.0016312;
		constexpr double frontal_area = 6.62753;
		constexpr double array_area = 7.84111;
		constexpr double array_efficiency = 28.4826;
		constexpr double energy_capacity = 6896.06;
		constexpr double min_voltage = 101.065;
		constexpr double max_voltage = 157.163;
		constexpr double resistance = 0.625517;
		constexpr double hysteresis_loss = 3.19042;
		constexpr double eddy_current_loss_coefficient = 0.0355659;
		constexpr double alpha = 5.75521;
		constexpr double beta = -9.71237;
		constexpr double a = 5.42152;
		constexpr double b = -8.67313e-06;
		constexpr double c = -0.0709159;
		constexpr double pressure_at_stc = 179.106;
		constexpr double mass = 700.438;
		constexpr double wheel_radius = 0.147559;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		const auto runner = RaceSegmentRunner(car);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {-51.6665, 36.9635};
			constexpr GeographicalCoordinate end_coordinate = {-83.4846, 69.4062};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 190.002;
			constexpr double weather_station = 3.63323;
			constexpr double distance = 99.6735;
			constexpr double heading = 4.46862;
			constexpr double elevation = -182.7;
			constexpr double grade = -0.169835;
			constexpr double road_incline_angle = 0.957;
			constexpr double sine_road_incline_angle = 0.817467;
			constexpr double gravity = 9.81504;
			constexpr double gravity_times_sine_road_incline_angle = 8.02348;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 37.9484;
			constexpr double wind_direction = 5.33333;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 767.085;
			constexpr double air_temp = -24.5908;
			constexpr double pressure = 934.509;
			constexpr double air_density = 1.20288;
			constexpr double reciprocal_speed_of_sound = 0.00292077;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 28.1513;

			const double result = runner.calculate_power_out(route_segment, weather_data, speed);
			constexpr double expected = 158729;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {-55.0105, -48.7891};
			constexpr GeographicalCoordinate end_coordinate = {-8.2705, 74.0566};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 96.7855;
			constexpr double weather_station = 5.36951;
			constexpr double distance = 80.3194;
			constexpr double heading = 2.10953;
			constexpr double elevation = -488.958;
			constexpr double grade = -0.104055;
			constexpr double road_incline_angle = -0.461227;
			constexpr double sine_road_incline_angle = -0.445047;
			constexpr double gravity = 9.81416;
			constexpr double gravity_times_sine_road_incline_angle = -4.36777;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 30.6441;
			constexpr double wind_direction = 0.0825749;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 281.412;
			constexpr double air_temp = -23.8027;
			constexpr double pressure = 1014.3;
			constexpr double air_density = 1.13351;
			constexpr double reciprocal_speed_of_sound = 0.00292869;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 27.275;

			const double result = runner.calculate_power_out(route_segment, weather_data, speed);
			constexpr double expected = -83402.2;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {-71.7764, 4.4919};
			constexpr GeographicalCoordinate end_coordinate = {82.8064, -116.972};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 82.409;
			constexpr double weather_station = 9.08896;
			constexpr double distance = 75.9198;
			constexpr double heading = 1.48801;
			constexpr double elevation = -74.2103;
			constexpr double grade = -0.117676;
			constexpr double road_incline_angle = 0.523222;
			constexpr double sine_road_incline_angle = 0.499673;
			constexpr double gravity = 9.78701;
			constexpr double gravity_times_sine_road_incline_angle = 4.89031;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 26.959;
			constexpr double wind_direction = 5.09198;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 412.598;
			constexpr double air_temp = -22.407;
			constexpr double pressure = 1074.47;
			constexpr double air_density = 1.18608;
			constexpr double reciprocal_speed_of_sound = 0.00296726;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 8.82534;

			const double result = runner.calculate_power_out(route_segment, weather_data, speed);
			constexpr double expected = 30248.5;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 6") {
		constexpr double drag_coefficient = 0.00404933;
		constexpr double frontal_area = 5.93752;
		constexpr double array_area = 9.48162;
		constexpr double array_efficiency = 17.4624;
		constexpr double energy_capacity = 4626.56;
		constexpr double min_voltage = 107.699;
		constexpr double max_voltage = 153.868;
		constexpr double resistance = 0.0214718;
		constexpr double hysteresis_loss = 2.80061;
		constexpr double eddy_current_loss_coefficient = 0.00931331;
		constexpr double alpha = 3.59221;
		constexpr double beta = -2.47528;
		constexpr double a = -8.14182;
		constexpr double b = 3.43781e-07;
		constexpr double c = -0.283041;
		constexpr double pressure_at_stc = 179.632;
		constexpr double mass = 681.167;
		constexpr double wheel_radius = 0.427753;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		const auto runner = RaceSegmentRunner(car);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {44.543, 154.979};
			constexpr GeographicalCoordinate end_coordinate = {-80.077, -118.651};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 66.8501;
			constexpr double weather_station = 9.55517;
			constexpr double distance = 82.2382;
			constexpr double heading = 5.09815;
			constexpr double elevation = -308.148;
			constexpr double grade = 0.295819;
			constexpr double road_incline_angle = 0.779486;
			constexpr double sine_road_incline_angle = 0.702914;
			constexpr double gravity = 9.8123;
			constexpr double gravity_times_sine_road_incline_angle = 6.89721;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 34.3116;
			constexpr double wind_direction = 5.16914;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 997.985;
			constexpr double air_temp = 25.3447;
			constexpr double pressure = 995.52;
			constexpr double air_density = 1.28738;
			constexpr double reciprocal_speed_of_sound = 0.00294293;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 13.6429;

			const double result = runner.calculate_power_out(route_segment, weather_data, speed);
			constexpr double expected = 64180.7;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {41.6621, -156.485};
			constexpr GeographicalCoordinate end_coordinate = {-6.86258, 24.5053};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 81.8179;
			constexpr double weather_station = 2.46182;
			constexpr double distance = 78.6428;
			constexpr double heading = 1.78904;
			constexpr double elevation = 251.624;
			constexpr double grade = 0.978651;
			constexpr double road_incline_angle = 0.329728;
			constexpr double sine_road_incline_angle = 0.323786;
			constexpr double gravity = 9.79426;
			constexpr double gravity_times_sine_road_incline_angle = 3.17124;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 22.3022;
			constexpr double wind_direction = 2.8954;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 580.586;
			constexpr double air_temp = 38.6107;
			constexpr double pressure = 950.805;
			constexpr double air_density = 1.20621;
			constexpr double reciprocal_speed_of_sound = 0.00294448;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 7.08194;

			const double result = runner.calculate_power_out(route_segment, weather_data, speed);
			constexpr double expected = 15272.6;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {-81.4665, -34.4946};
			constexpr GeographicalCoordinate end_coordinate = {7.39874, -51.7562};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 97.548;
			constexpr double weather_station = 0.877433;
			constexpr double distance = 46.462;
			constexpr double heading = 2.55008;
			constexpr double elevation = -483.768;
			constexpr double grade = -0.960438;
			constexpr double road_incline_angle = -1.30528;
			constexpr double sine_road_incline_angle = -0.964957;
			constexpr double gravity = 9.79851;
			constexpr double gravity_times_sine_road_incline_angle = -9.45515;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 0.703201;
			constexpr double wind_direction = 2.01222;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 501.922;
			constexpr double air_temp = -20.3891;
			constexpr double pressure = 1034.18;
			constexpr double air_density = 1.02938;
			constexpr double reciprocal_speed_of_sound = 0.00305464;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 25.9791;

			const double result = runner.calculate_power_out(route_segment, weather_data, speed);
			constexpr double expected = -169852;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 7") {
		constexpr double drag_coefficient = 0.00725254;
		constexpr double frontal_area = 5.33225;
		constexpr double array_area = 7.32884;
		constexpr double array_efficiency = 24.235;
		constexpr double energy_capacity = 4808.26;
		constexpr double min_voltage = 82.0146;
		constexpr double max_voltage = 152.291;
		constexpr double resistance = 0.220019;
		constexpr double hysteresis_loss = 3.05464;
		constexpr double eddy_current_loss_coefficient = 0.0331547;
		constexpr double alpha = -3.1146;
		constexpr double beta = 4.77573;
		constexpr double a = 7.78589;
		constexpr double b = -1.29827e-06;
		constexpr double c = -0.0697427;
		constexpr double pressure_at_stc = 172.711;
		constexpr double mass = 897.269;
		constexpr double wheel_radius = 0.385731;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		const auto runner = RaceSegmentRunner(car);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {-24.1021, 117.412};
			constexpr GeographicalCoordinate end_coordinate = {-37.9414, 125.011};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 82.2082;
			constexpr double weather_station = 5.92073;
			constexpr double distance = 61.6031;
			constexpr double heading = 3.54395;
			constexpr double elevation = 125.372;
			constexpr double grade = -0.550702;
			constexpr double road_incline_angle = 0.80993;
			constexpr double sine_road_incline_angle = 0.724239;
			constexpr double gravity = 9.78373;
			constexpr double gravity_times_sine_road_incline_angle = 7.08575;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 18.3859;
			constexpr double wind_direction = 0.95044;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 438.479;
			constexpr double air_temp = 18.4112;
			constexpr double pressure = 960.143;
			constexpr double air_density = 1.26362;
			constexpr double reciprocal_speed_of_sound = 0.00292813;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 29.8282;

			const double result = runner.calculate_power_out(route_segment, weather_data, speed);
			constexpr double expected = -1.7384e+16;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {77.4754, 161.13};
			constexpr GeographicalCoordinate end_coordinate = {-6.57299, 133.693};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 155.724;
			constexpr double weather_station = 6.17719;
			constexpr double distance = 97.1502;
			constexpr double heading = 6.2496;
			constexpr double elevation = 288.123;
			constexpr double grade = -0.190608;
			constexpr double road_incline_angle = 0.44308;
			constexpr double sine_road_incline_angle = 0.428724;
			constexpr double gravity = 9.81826;
			constexpr double gravity_times_sine_road_incline_angle = 4.20932;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 2.83814;
			constexpr double wind_direction = 0.019774;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 388.234;
			constexpr double air_temp = 39.0813;
			constexpr double pressure = 1000.14;
			constexpr double air_density = 1.00064;
			constexpr double reciprocal_speed_of_sound = 0.00292119;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 12.8078;

			const double result = runner.calculate_power_out(route_segment, weather_data, speed);
			constexpr double expected = -1.33905e+15;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {-73.8617, -114.873};
			constexpr GeographicalCoordinate end_coordinate = {14.8127, -174.099};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 107.126;
			constexpr double weather_station = 2.3113;
			constexpr double distance = 88.2747;
			constexpr double heading = 5.94608;
			constexpr double elevation = -4.68194;
			constexpr double grade = -0.181052;
			constexpr double road_incline_angle = 0.481645;
			constexpr double sine_road_incline_angle = 0.463238;
			constexpr double gravity = 9.79764;
			constexpr double gravity_times_sine_road_incline_angle = 4.53864;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 30.694;
			constexpr double wind_direction = 3.89712;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 175.882;
			constexpr double air_temp = 17.5866;
			constexpr double pressure = 1056.93;
			constexpr double air_density = 1.25581;
			constexpr double reciprocal_speed_of_sound = 0.00297988;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 11.3277;

			const double result = runner.calculate_power_out(route_segment, weather_data, speed);
			constexpr double expected = -9.03006e+14;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 8") {
		constexpr double drag_coefficient = 0.00584694;
		constexpr double frontal_area = 6.22716;
		constexpr double array_area = 7.17651;
		constexpr double array_efficiency = 19.1463;
		constexpr double energy_capacity = 3697.82;
		constexpr double min_voltage = 96.9945;
		constexpr double max_voltage = 102.175;
		constexpr double resistance = 0.55222;
		constexpr double hysteresis_loss = 4.54566;
		constexpr double eddy_current_loss_coefficient = 0.0324538;
		constexpr double alpha = 3.46171;
		constexpr double beta = 6.64462;
		constexpr double a = 9.73146;
		constexpr double b = 1.1069e-06;
		constexpr double c = 0.676239;
		constexpr double pressure_at_stc = 138.079;
		constexpr double mass = 455.849;
		constexpr double wheel_radius = 0.16782;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		const auto runner = RaceSegmentRunner(car);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {7.22194, 178.303};
			constexpr GeographicalCoordinate end_coordinate = {-24.6001, -96.6607};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 124.357;
			constexpr double weather_station = 4.41548;
			constexpr double distance = 48.2566;
			constexpr double heading = 0.633689;
			constexpr double elevation = -464.404;
			constexpr double grade = 0.2742;
			constexpr double road_incline_angle = 1.23757;
			constexpr double sine_road_incline_angle = 0.944992;
			constexpr double gravity = 9.8112;
			constexpr double gravity_times_sine_road_incline_angle = 9.27151;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 26.6332;
			constexpr double wind_direction = 2.9126;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 367.981;
			constexpr double air_temp = 5.06165;
			constexpr double pressure = 966.056;
			constexpr double air_density = 1.21034;
			constexpr double reciprocal_speed_of_sound = 0.00292433;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 1.1268;

			const double result = runner.calculate_power_out(route_segment, weather_data, speed);
			constexpr double expected = 1.08675e+33;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {-5.28647, 8.36124};
			constexpr GeographicalCoordinate end_coordinate = {7.19833, 98.5221};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 139.887;
			constexpr double weather_station = 3.4513;
			constexpr double distance = 3.28349;
			constexpr double heading = 5.53981;
			constexpr double elevation = -287.976;
			constexpr double grade = 0.661677;
			constexpr double road_incline_angle = -0.684201;
			constexpr double sine_road_incline_angle = -0.632054;
			constexpr double gravity = 9.80588;
			constexpr double gravity_times_sine_road_incline_angle = -6.19784;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 34.738;
			constexpr double wind_direction = 0.798141;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 648.806;
			constexpr double air_temp = -39.8864;
			constexpr double pressure = 990.65;
			constexpr double air_density = 1.25608;
			constexpr double reciprocal_speed_of_sound = 0.003058;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 11.9909;

			const double result = runner.calculate_power_out(route_segment, weather_data, speed);
			constexpr double expected = 7.01497e+35;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {-6.62528, 95.1781};
			constexpr GeographicalCoordinate end_coordinate = {-7.03041, -155.5};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 137.857;
			constexpr double weather_station = 2.50335;
			constexpr double distance = 80.7571;
			constexpr double heading = 5.57104;
			constexpr double elevation = -50.3863;
			constexpr double grade = -0.893763;
			constexpr double road_incline_angle = 0.208985;
			constexpr double sine_road_incline_angle = 0.207467;
			constexpr double gravity = 9.78507;
			constexpr double gravity_times_sine_road_incline_angle = 2.03008;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 1.33921;
			constexpr double wind_direction = 5.9584;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 381.233;
			constexpr double air_temp = -17.6678;
			constexpr double pressure = 1045.42;
			constexpr double air_density = 1.24432;
			constexpr double reciprocal_speed_of_sound = 0.00294203;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 6.6598;

			const double result = runner.calculate_power_out(route_segment, weather_data, speed);
			constexpr double expected = 1.20537e+35;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 9") {
		constexpr double drag_coefficient = 0.00320646;
		constexpr double frontal_area = 6.40977;
		constexpr double array_area = 9.19932;
		constexpr double array_efficiency = 27.5782;
		constexpr double energy_capacity = 438.927;
		constexpr double min_voltage = 97.0887;
		constexpr double max_voltage = 149.201;
		constexpr double resistance = 0.970564;
		constexpr double hysteresis_loss = 4.35098;
		constexpr double eddy_current_loss_coefficient = 0.0328035;
		constexpr double alpha = 9.78429;
		constexpr double beta = 4.82942;
		constexpr double a = -3.894;
		constexpr double b = -4.99932e-06;
		constexpr double c = 0.599073;
		constexpr double pressure_at_stc = 111.695;
		constexpr double mass = 955.98;
		constexpr double wheel_radius = 0.238824;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		const auto runner = RaceSegmentRunner(car);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {-5.23374, 117.795};
			constexpr GeographicalCoordinate end_coordinate = {62.4328, -151.519};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 159.448;
			constexpr double weather_station = 1.29619;
			constexpr double distance = 86.8526;
			constexpr double heading = 1.59681;
			constexpr double elevation = 43.4967;
			constexpr double grade = 0.550935;
			constexpr double road_incline_angle = -0.183253;
			constexpr double sine_road_incline_angle = -0.182229;
			constexpr double gravity = 9.80642;
			constexpr double gravity_times_sine_road_incline_angle = -1.78701;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 20.3353;
			constexpr double wind_direction = 6.16586;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 832.885;
			constexpr double air_temp = 34.0079;
			constexpr double pressure = 1012.16;
			constexpr double air_density = 1.17316;
			constexpr double reciprocal_speed_of_sound = 0.00306649;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 0.446789;

			const double result = runner.calculate_power_out(route_segment, weather_data, speed);
			constexpr double expected = -1.74145e+39;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {-27.2079, -61.6831};
			constexpr GeographicalCoordinate end_coordinate = {50.7394, 100.352};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 192.294;
			constexpr double weather_station = 5.61004;
			constexpr double distance = 34.8588;
			constexpr double heading = 4.75488;
			constexpr double elevation = 383.849;
			constexpr double grade = -0.798841;
			constexpr double road_incline_angle = 0.0225139;
			constexpr double sine_road_incline_angle = 0.022512;
			constexpr double gravity = 9.81595;
			constexpr double gravity_times_sine_road_incline_angle = 0.220977;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 35.8304;
			constexpr double wind_direction = 5.14943;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 680.507;
			constexpr double air_temp = -49.7779;
			constexpr double pressure = 934.7;
			constexpr double air_density = 1.14412;
			constexpr double reciprocal_speed_of_sound = 0.00303473;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 16.241;

			const double result = runner.calculate_power_out(route_segment, weather_data, speed);
			constexpr double expected = 5.54573e+43;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {-15.4246, -23.8092};
			constexpr GeographicalCoordinate end_coordinate = {-7.36933, 114.54};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 182.889;
			constexpr double weather_station = 6.19476;
			constexpr double distance = 86.77;
			constexpr double heading = 1.06007;
			constexpr double elevation = 229.11;
			constexpr double grade = 0.947212;
			constexpr double road_incline_angle = 0.985705;
			constexpr double sine_road_incline_angle = 0.833662;
			constexpr double gravity = 9.79732;
			constexpr double gravity_times_sine_road_incline_angle = 8.16765;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 39.5222;
			constexpr double wind_direction = 2.07786;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 681.375;
			constexpr double air_temp = -26.2395;
			constexpr double pressure = 906.646;
			constexpr double air_density = 1.18368;
			constexpr double reciprocal_speed_of_sound = 0.00302669;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double speed = 26.8592;

			const double result = runner.calculate_power_out(route_segment, weather_data, speed);
			constexpr double expected = 2.48848e+44;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
	}
}
TEST_CASE("RaceSegmentRunner: calculate_power_in", "[RaceSegmentRunner]") {
	SECTION("Random Test 0") {
		constexpr double drag_coefficient = 0.00269547;
		constexpr double frontal_area = 8.94251;
		constexpr double array_area = 5.83918;
		constexpr double array_efficiency = 22.2167;
		constexpr double energy_capacity = 2213.06;
		constexpr double min_voltage = 116.184;
		constexpr double max_voltage = 163.976;
		constexpr double resistance = 0.393295;
		constexpr double hysteresis_loss = 4.11512;
		constexpr double eddy_current_loss_coefficient = 0.0236372;
		constexpr double alpha = -7.77495;
		constexpr double beta = -3.29638;
		constexpr double a = -3.75342;
		constexpr double b = -4.84301e-06;
		constexpr double c = 0.221647;
		constexpr double pressure_at_stc = 136.74;
		constexpr double mass = 157.992;
		constexpr double wheel_radius = 0.428201;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {30.5773, 158.919};
			constexpr GeographicalCoordinate end_coordinate = {-43.9513, 106.767};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 134.838;
			constexpr double weather_station = 9.43193;
			constexpr double distance = 16.0668;
			constexpr double heading = 1.16366;
			constexpr double elevation = -462.289;
			constexpr double grade = 0.511305;
			constexpr double road_incline_angle = 1.39254;
			constexpr double sine_road_incline_angle = 0.984154;
			constexpr double gravity = 9.7917;
			constexpr double gravity_times_sine_road_incline_angle = 9.63654;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 18.1841;
			constexpr double wind_direction = 4.56106;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 162.669;
			constexpr double air_temp = -12.9492;
			constexpr double pressure = 985.21;
			constexpr double air_density = 1.00645;
			constexpr double reciprocal_speed_of_sound = 0.00304823;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			const auto runner = RaceSegmentRunner(car);
			const double result = runner.calculate_power_in(route_segment, weather_data);
			constexpr double expected = 211.027;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {-51.1568, -146.301};
			constexpr GeographicalCoordinate end_coordinate = {-85.9334, -95.1628};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 58.8832;
			constexpr double weather_station = 3.23867;
			constexpr double distance = 47.1379;
			constexpr double heading = 0.614341;
			constexpr double elevation = -430.55;
			constexpr double grade = -0.494786;
			constexpr double road_incline_angle = -0.182916;
			constexpr double sine_road_incline_angle = -0.181898;
			constexpr double gravity = 9.79102;
			constexpr double gravity_times_sine_road_incline_angle = -1.78097;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 30.6953;
			constexpr double wind_direction = 4.54843;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 359.912;
			constexpr double air_temp = -16.0166;
			constexpr double pressure = 935.562;
			constexpr double air_density = 1.2351;
			constexpr double reciprocal_speed_of_sound = 0.00308601;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			const auto runner = RaceSegmentRunner(car);
			const double result = runner.calculate_power_in(route_segment, weather_data);
			constexpr double expected = 466.905;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {-27.2299, -44.1347};
			constexpr GeographicalCoordinate end_coordinate = {78.0729, -174.267};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 52.6613;
			constexpr double weather_station = 6.48685;
			constexpr double distance = 42.0578;
			constexpr double heading = 2.90471;
			constexpr double elevation = 312.534;
			constexpr double grade = -0.776156;
			constexpr double road_incline_angle = 0.790629;
			constexpr double sine_road_incline_angle = 0.710796;
			constexpr double gravity = 9.78333;
			constexpr double gravity_times_sine_road_incline_angle = 6.95395;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 28.852;
			constexpr double wind_direction = 0.4088;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 511.123;
			constexpr double air_temp = -8.37362;
			constexpr double pressure = 956.05;
			constexpr double air_density = 1.1599;
			constexpr double reciprocal_speed_of_sound = 0.00290737;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			const auto runner = RaceSegmentRunner(car);
			const double result = runner.calculate_power_in(route_segment, weather_data);
			constexpr double expected = 663.067;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 1") {
		constexpr double drag_coefficient = 0.00619359;
		constexpr double frontal_area = 6.19358;
		constexpr double array_area = 9.95952;
		constexpr double array_efficiency = 24.3915;
		constexpr double energy_capacity = 4721.99;
		constexpr double min_voltage = 96.9929;
		constexpr double max_voltage = 111.972;
		constexpr double resistance = 0.144961;
		constexpr double hysteresis_loss = 3.40429;
		constexpr double eddy_current_loss_coefficient = 0.0424191;
		constexpr double alpha = 4.6636;
		constexpr double beta = -7.58728;
		constexpr double a = -5.75032;
		constexpr double b = -1.55303e-07;
		constexpr double c = -0.790608;
		constexpr double pressure_at_stc = 157.89;
		constexpr double mass = 570.958;
		constexpr double wheel_radius = 0.221476;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {42.4325, 161.53};
			constexpr GeographicalCoordinate end_coordinate = {-68.4112, -24.0797};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 49.5352;
			constexpr double weather_station = 1.4943;
			constexpr double distance = 5.74583;
			constexpr double heading = 2.89517;
			constexpr double elevation = 265.97;
			constexpr double grade = 0.143529;
			constexpr double road_incline_angle = 0.731322;
			constexpr double sine_road_incline_angle = 0.667854;
			constexpr double gravity = 9.80301;
			constexpr double gravity_times_sine_road_incline_angle = 6.54698;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 18.0797;
			constexpr double wind_direction = 3.39872;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 602.725;
			constexpr double air_temp = 34.0768;
			constexpr double pressure = 906.011;
			constexpr double air_density = 1.24942;
			constexpr double reciprocal_speed_of_sound = 0.00291926;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			const auto runner = RaceSegmentRunner(car);
			const double result = runner.calculate_power_in(route_segment, weather_data);
			constexpr double expected = 1464.18;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {-38.5363, -0.808379};
			constexpr GeographicalCoordinate end_coordinate = {-39.6965, 161.354};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 139.506;
			constexpr double weather_station = 4.76088;
			constexpr double distance = 85.3885;
			constexpr double heading = 1.90825;
			constexpr double elevation = 231.535;
			constexpr double grade = -0.890007;
			constexpr double road_incline_angle = 1.27342;
			constexpr double sine_road_incline_angle = 0.956109;
			constexpr double gravity = 9.78336;
			constexpr double gravity_times_sine_road_incline_angle = 9.35396;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 40.1519;
			constexpr double wind_direction = 1.71094;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 667.635;
			constexpr double air_temp = 30.2206;
			constexpr double pressure = 982.146;
			constexpr double air_density = 1.01613;
			constexpr double reciprocal_speed_of_sound = 0.00296814;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			const auto runner = RaceSegmentRunner(car);
			const double result = runner.calculate_power_in(route_segment, weather_data);
			constexpr double expected = 1621.87;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {-74.1975, 107.297};
			constexpr GeographicalCoordinate end_coordinate = {-61.9675, 170.294};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 86.3457;
			constexpr double weather_station = 8.05601;
			constexpr double distance = 45.0446;
			constexpr double heading = 2.30133;
			constexpr double elevation = -194.546;
			constexpr double grade = 0.113909;
			constexpr double road_incline_angle = -0.345623;
			constexpr double sine_road_incline_angle = -0.338783;
			constexpr double gravity = 9.80703;
			constexpr double gravity_times_sine_road_incline_angle = -3.32246;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 18.582;
			constexpr double wind_direction = 1.02043;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 126.229;
			constexpr double air_temp = -43.254;
			constexpr double pressure = 1034.34;
			constexpr double air_density = 1.1055;
			constexpr double reciprocal_speed_of_sound = 0.00294416;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			const auto runner = RaceSegmentRunner(car);
			const double result = runner.calculate_power_in(route_segment, weather_data);
			constexpr double expected = 306.644;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 2") {
		constexpr double drag_coefficient = 0.00695682;
		constexpr double frontal_area = 6.24638;
		constexpr double array_area = 7.03212;
		constexpr double array_efficiency = 27.1348;
		constexpr double energy_capacity = 1870.67;
		constexpr double min_voltage = 76.7755;
		constexpr double max_voltage = 94.0775;
		constexpr double resistance = 0.91249;
		constexpr double hysteresis_loss = 3.34192;
		constexpr double eddy_current_loss_coefficient = 0.0108542;
		constexpr double alpha = -8.59011;
		constexpr double beta = 6.71347;
		constexpr double a = 2.0271;
		constexpr double b = 6.32532e-06;
		constexpr double c = 0.877672;
		constexpr double pressure_at_stc = 171.316;
		constexpr double mass = 797.487;
		constexpr double wheel_radius = 0.281718;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {69.968, -134.355};
			constexpr GeographicalCoordinate end_coordinate = {15.1598, 55.2607};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 175.374;
			constexpr double weather_station = 2.8517;
			constexpr double distance = 24.0429;
			constexpr double heading = 4.22478;
			constexpr double elevation = 87.6119;
			constexpr double grade = -0.922908;
			constexpr double road_incline_angle = 1.50642;
			constexpr double sine_road_incline_angle = 0.997929;
			constexpr double gravity = 9.79696;
			constexpr double gravity_times_sine_road_incline_angle = 9.77666;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 24.6892;
			constexpr double wind_direction = 3.15233;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 921.217;
			constexpr double air_temp = -39.3097;
			constexpr double pressure = 919.556;
			constexpr double air_density = 1.05159;
			constexpr double reciprocal_speed_of_sound = 0.00294483;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			const auto runner = RaceSegmentRunner(car);
			const double result = runner.calculate_power_in(route_segment, weather_data);
			constexpr double expected = 1757.82;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {54.6406, -135.316};
			constexpr GeographicalCoordinate end_coordinate = {17.036, -9.76632};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 160.23;
			constexpr double weather_station = 4.86073;
			constexpr double distance = 35.5467;
			constexpr double heading = 2.47648;
			constexpr double elevation = -329.972;
			constexpr double grade = -0.628454;
			constexpr double road_incline_angle = -1.31799;
			constexpr double sine_road_incline_angle = -0.968214;
			constexpr double gravity = 9.78637;
			constexpr double gravity_times_sine_road_incline_angle = -9.47531;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 27.8615;
			constexpr double wind_direction = 4.39719;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 798.947;
			constexpr double air_temp = -8.4431;
			constexpr double pressure = 1074.82;
			constexpr double air_density = 1.04444;
			constexpr double reciprocal_speed_of_sound = 0.00292257;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			const auto runner = RaceSegmentRunner(car);
			const double result = runner.calculate_power_in(route_segment, weather_data);
			constexpr double expected = 1524.51;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {-77.9669, 171.689};
			constexpr GeographicalCoordinate end_coordinate = {40.6705, 150.749};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 55.2699;
			constexpr double weather_station = 3.29561;
			constexpr double distance = 49.5874;
			constexpr double heading = 0.260324;
			constexpr double elevation = -397.597;
			constexpr double grade = -0.90624;
			constexpr double road_incline_angle = 1.33661;
			constexpr double sine_road_incline_angle = 0.972704;
			constexpr double gravity = 9.78112;
			constexpr double gravity_times_sine_road_incline_angle = 9.51413;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 19.2195;
			constexpr double wind_direction = 1.98137;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 586.174;
			constexpr double air_temp = 24.6973;
			constexpr double pressure = 1073.19;
			constexpr double air_density = 1.01148;
			constexpr double reciprocal_speed_of_sound = 0.00309526;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			const auto runner = RaceSegmentRunner(car);
			const double result = runner.calculate_power_in(route_segment, weather_data);
			constexpr double expected = 1118.51;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 3") {
		constexpr double drag_coefficient = 0.00112224;
		constexpr double frontal_area = 4.41458;
		constexpr double array_area = 9.72694;
		constexpr double array_efficiency = 18.0652;
		constexpr double energy_capacity = 3194.73;
		constexpr double min_voltage = 121.375;
		constexpr double max_voltage = 126.728;
		constexpr double resistance = 0.958865;
		constexpr double hysteresis_loss = 4.28739;
		constexpr double eddy_current_loss_coefficient = 0.0072395;
		constexpr double alpha = -6.27919;
		constexpr double beta = 5.85371;
		constexpr double a = 4.44062;
		constexpr double b = 4.14297e-06;
		constexpr double c = 0.639102;
		constexpr double pressure_at_stc = 177.09;
		constexpr double mass = 173.532;
		constexpr double wheel_radius = 0.307244;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {83.0391, 9.35306};
			constexpr GeographicalCoordinate end_coordinate = {-9.30218, -57.8015};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 75.316;
			constexpr double weather_station = 4.50157;
			constexpr double distance = 29.5963;
			constexpr double heading = 0.931819;
			constexpr double elevation = -387.868;
			constexpr double grade = -0.166859;
			constexpr double road_incline_angle = 0.87388;
			constexpr double sine_road_incline_angle = 0.766825;
			constexpr double gravity = 9.80156;
			constexpr double gravity_times_sine_road_incline_angle = 7.51608;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 29.0051;
			constexpr double wind_direction = 5.09029;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 242.291;
			constexpr double air_temp = -17.0914;
			constexpr double pressure = 1043.73;
			constexpr double air_density = 1.1529;
			constexpr double reciprocal_speed_of_sound = 0.00294625;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			const auto runner = RaceSegmentRunner(car);
			const double result = runner.calculate_power_in(route_segment, weather_data);
			constexpr double expected = 425.753;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {-46.6653, -44.4079};
			constexpr GeographicalCoordinate end_coordinate = {31.7505, -173.756};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 90.5299;
			constexpr double weather_station = 8.31477;
			constexpr double distance = 98.6902;
			constexpr double heading = 5.47013;
			constexpr double elevation = -220.18;
			constexpr double grade = -0.142941;
			constexpr double road_incline_angle = -1.20464;
			constexpr double sine_road_incline_angle = -0.933709;
			constexpr double gravity = 9.7911;
			constexpr double gravity_times_sine_road_incline_angle = -9.14204;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 25.5679;
			constexpr double wind_direction = 1.27842;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 938.928;
			constexpr double air_temp = 2.5005;
			constexpr double pressure = 1009.77;
			constexpr double air_density = 1.20201;
			constexpr double reciprocal_speed_of_sound = 0.00290634;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			const auto runner = RaceSegmentRunner(car);
			const double result = runner.calculate_power_in(route_segment, weather_data);
			constexpr double expected = 1649.88;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {68.5839, -108.949};
			constexpr GeographicalCoordinate end_coordinate = {-43.8581, -152.236};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 67.2451;
			constexpr double weather_station = 6.80332;
			constexpr double distance = 19.3095;
			constexpr double heading = 5.58518;
			constexpr double elevation = 66.5738;
			constexpr double grade = 0.133188;
			constexpr double road_incline_angle = 1.12274;
			constexpr double sine_road_incline_angle = 0.901292;
			constexpr double gravity = 9.79993;
			constexpr double gravity_times_sine_road_incline_angle = 8.8326;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 1.38893;
			constexpr double wind_direction = 6.08674;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 90.5314;
			constexpr double air_temp = 35.4646;
			constexpr double pressure = 1014.24;
			constexpr double air_density = 1.01861;
			constexpr double reciprocal_speed_of_sound = 0.00297263;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			const auto runner = RaceSegmentRunner(car);
			const double result = runner.calculate_power_in(route_segment, weather_data);
			constexpr double expected = 159.081;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 4") {
		constexpr double drag_coefficient = 0.00140973;
		constexpr double frontal_area = 5.72405;
		constexpr double array_area = 8.90408;
		constexpr double array_efficiency = 27.2082;
		constexpr double energy_capacity = 3861.22;
		constexpr double min_voltage = 104.485;
		constexpr double max_voltage = 116.819;
		constexpr double resistance = 0.501969;
		constexpr double hysteresis_loss = 3.42058;
		constexpr double eddy_current_loss_coefficient = 0.0463178;
		constexpr double alpha = -0.413047;
		constexpr double beta = 0.131494;
		constexpr double a = -8.25099;
		constexpr double b = -4.13145e-06;
		constexpr double c = 0.6355;
		constexpr double pressure_at_stc = 137.324;
		constexpr double mass = 810.267;
		constexpr double wheel_radius = 0.380097;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {-7.64713, 148.552};
			constexpr GeographicalCoordinate end_coordinate = {-20.2329, 168.632};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 140.5;
			constexpr double weather_station = 4.28459;
			constexpr double distance = 64.5458;
			constexpr double heading = 0.97581;
			constexpr double elevation = -80.6501;
			constexpr double grade = -0.690385;
			constexpr double road_incline_angle = -0.911933;
			constexpr double sine_road_incline_angle = -0.790689;
			constexpr double gravity = 9.78308;
			constexpr double gravity_times_sine_road_incline_angle = -7.73537;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 44.6927;
			constexpr double wind_direction = 0.536879;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 156.348;
			constexpr double air_temp = 31.5647;
			constexpr double pressure = 964.555;
			constexpr double air_density = 1.25891;
			constexpr double reciprocal_speed_of_sound = 0.00294039;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			const auto runner = RaceSegmentRunner(car);
			const double result = runner.calculate_power_in(route_segment, weather_data);
			constexpr double expected = 378.775;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {48.9047, -121.718};
			constexpr GeographicalCoordinate end_coordinate = {-16.784, -159.914};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 34.7688;
			constexpr double weather_station = 5.26298;
			constexpr double distance = 16.1107;
			constexpr double heading = 4.27765;
			constexpr double elevation = 452.608;
			constexpr double grade = -0.685411;
			constexpr double road_incline_angle = 1.15618;
			constexpr double sine_road_incline_angle = 0.915272;
			constexpr double gravity = 9.81688;
			constexpr double gravity_times_sine_road_incline_angle = 8.98512;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 12.7105;
			constexpr double wind_direction = 2.04626;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 635.035;
			constexpr double air_temp = -26.7908;
			constexpr double pressure = 999.198;
			constexpr double air_density = 1.12763;
			constexpr double reciprocal_speed_of_sound = 0.00290117;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			const auto runner = RaceSegmentRunner(car);
			const double result = runner.calculate_power_in(route_segment, weather_data);
			constexpr double expected = 1538.46;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {-77.9792, 155.405};
			constexpr GeographicalCoordinate end_coordinate = {-66.0056, -62.9517};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 11.8395;
			constexpr double weather_station = 3.44256;
			constexpr double distance = 11.3729;
			constexpr double heading = 1.49351;
			constexpr double elevation = 55.9497;
			constexpr double grade = 0.174587;
			constexpr double road_incline_angle = -0.906823;
			constexpr double sine_road_incline_angle = -0.78755;
			constexpr double gravity = 9.81019;
			constexpr double gravity_times_sine_road_incline_angle = -7.72601;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 8.65512;
			constexpr double wind_direction = 2.85451;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 890.231;
			constexpr double air_temp = -34.709;
			constexpr double pressure = 962.942;
			constexpr double air_density = 1.2131;
			constexpr double reciprocal_speed_of_sound = 0.00299639;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			const auto runner = RaceSegmentRunner(car);
			const double result = runner.calculate_power_in(route_segment, weather_data);
			constexpr double expected = 2156.71;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 5") {
		constexpr double drag_coefficient = 0.00106953;
		constexpr double frontal_area = 1.23423;
		constexpr double array_area = 3.11762;
		constexpr double array_efficiency = 16.06;
		constexpr double energy_capacity = 7639.06;
		constexpr double min_voltage = 73.3395;
		constexpr double max_voltage = 98.042;
		constexpr double resistance = 0.720856;
		constexpr double hysteresis_loss = 1.36319;
		constexpr double eddy_current_loss_coefficient = 0.00743732;
		constexpr double alpha = 7.08398;
		constexpr double beta = -5.07326;
		constexpr double a = -5.4636;
		constexpr double b = -4.77515e-06;
		constexpr double c = -0.154235;
		constexpr double pressure_at_stc = 176.337;
		constexpr double mass = 793.496;
		constexpr double wheel_radius = 0.388722;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {-27.6249, 47.5185};
			constexpr GeographicalCoordinate end_coordinate = {29.4173, 173.98};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 196.463;
			constexpr double weather_station = 9.73371;
			constexpr double distance = 18.5627;
			constexpr double heading = 5.71421;
			constexpr double elevation = -59.979;
			constexpr double grade = -0.74188;
			constexpr double road_incline_angle = -1.39125;
			constexpr double sine_road_incline_angle = -0.983925;
			constexpr double gravity = 9.78903;
			constexpr double gravity_times_sine_road_incline_angle = -9.63168;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 23.6489;
			constexpr double wind_direction = 3.37456;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 10.2504;
			constexpr double air_temp = -22.7997;
			constexpr double pressure = 1081.44;
			constexpr double air_density = 1.29162;
			constexpr double reciprocal_speed_of_sound = 0.00309644;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			const auto runner = RaceSegmentRunner(car);
			const double result = runner.calculate_power_in(route_segment, weather_data);
			constexpr double expected = 5.13227;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {7.85798, 101.174};
			constexpr GeographicalCoordinate end_coordinate = {33.2031, 161.792};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 81.5863;
			constexpr double weather_station = 4.26367;
			constexpr double distance = 68.0974;
			constexpr double heading = 1.59502;
			constexpr double elevation = 420.527;
			constexpr double grade = -0.782165;
			constexpr double road_incline_angle = 0.116424;
			constexpr double sine_road_incline_angle = 0.116161;
			constexpr double gravity = 9.81493;
			constexpr double gravity_times_sine_road_incline_angle = 1.14012;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 12.1222;
			constexpr double wind_direction = 3.95165;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 965.431;
			constexpr double air_temp = 3.17703;
			constexpr double pressure = 1063.8;
			constexpr double air_density = 1.13007;
			constexpr double reciprocal_speed_of_sound = 0.00303539;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			const auto runner = RaceSegmentRunner(car);
			const double result = runner.calculate_power_in(route_segment, weather_data);
			constexpr double expected = 483.38;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {61.9508, -95.2518};
			constexpr GeographicalCoordinate end_coordinate = {-21.2534, 94.007};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 131.734;
			constexpr double weather_station = 5.05324;
			constexpr double distance = 44.2493;
			constexpr double heading = 1.24918;
			constexpr double elevation = -213.878;
			constexpr double grade = -0.822127;
			constexpr double road_incline_angle = -1.32569;
			constexpr double sine_road_incline_angle = -0.970112;
			constexpr double gravity = 9.8099;
			constexpr double gravity_times_sine_road_incline_angle = -9.51669;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 46.8354;
			constexpr double wind_direction = 0.238768;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 200.218;
			constexpr double air_temp = -44.3601;
			constexpr double pressure = 1054.81;
			constexpr double air_density = 1.11597;
			constexpr double reciprocal_speed_of_sound = 0.00306484;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			const auto runner = RaceSegmentRunner(car);
			const double result = runner.calculate_power_in(route_segment, weather_data);
			constexpr double expected = 100.247;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 6") {
		constexpr double drag_coefficient = 0.00707462;
		constexpr double frontal_area = 4.0059;
		constexpr double array_area = 1.45968;
		constexpr double array_efficiency = 22.2318;
		constexpr double energy_capacity = 4015.71;
		constexpr double min_voltage = 77.9815;
		constexpr double max_voltage = 167.775;
		constexpr double resistance = 0.277071;
		constexpr double hysteresis_loss = 2.90835;
		constexpr double eddy_current_loss_coefficient = 0.0469992;
		constexpr double alpha = 4.96882;
		constexpr double beta = -3.34831;
		constexpr double a = 7.5499;
		constexpr double b = 9.60417e-06;
		constexpr double c = 0.427894;
		constexpr double pressure_at_stc = 171.773;
		constexpr double mass = 970.779;
		constexpr double wheel_radius = 0.194728;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {11.982, 166.983};
			constexpr GeographicalCoordinate end_coordinate = {-67.3369, -89.5209};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 173.494;
			constexpr double weather_station = 1.0582;
			constexpr double distance = 32.5707;
			constexpr double heading = 1.1772;
			constexpr double elevation = 317.434;
			constexpr double grade = 0.486168;
			constexpr double road_incline_angle = 1.01713;
			constexpr double sine_road_incline_angle = 0.8506;
			constexpr double gravity = 9.81885;
			constexpr double gravity_times_sine_road_incline_angle = 8.35191;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 45.4182;
			constexpr double wind_direction = 0.351953;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 800.841;
			constexpr double air_temp = 3.31743;
			constexpr double pressure = 989.081;
			constexpr double air_density = 1.27026;
			constexpr double reciprocal_speed_of_sound = 0.00292932;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			const auto runner = RaceSegmentRunner(car);
			const double result = runner.calculate_power_in(route_segment, weather_data);
			constexpr double expected = 259.884;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {-43.9631, 4.73051};
			constexpr GeographicalCoordinate end_coordinate = {-23.9546, 114.381};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 29.1392;
			constexpr double weather_station = 4.78204;
			constexpr double distance = 46.8005;
			constexpr double heading = 4.55861;
			constexpr double elevation = -88.1265;
			constexpr double grade = -0.159559;
			constexpr double road_incline_angle = 1.09019;
			constexpr double sine_road_incline_angle = 0.886713;
			constexpr double gravity = 9.80653;
			constexpr double gravity_times_sine_road_incline_angle = 8.69558;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 13.2918;
			constexpr double wind_direction = 4.24323;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 946.353;
			constexpr double air_temp = 7.92057;
			constexpr double pressure = 911.231;
			constexpr double air_density = 1.2488;
			constexpr double reciprocal_speed_of_sound = 0.00298269;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			const auto runner = RaceSegmentRunner(car);
			const double result = runner.calculate_power_in(route_segment, weather_data);
			constexpr double expected = 307.104;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {-42.1988, -142.807};
			constexpr GeographicalCoordinate end_coordinate = {15.5031, -138.497};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 37.2354;
			constexpr double weather_station = 7.18023;
			constexpr double distance = 79.4724;
			constexpr double heading = 4.57308;
			constexpr double elevation = -484.774;
			constexpr double grade = -0.719501;
			constexpr double road_incline_angle = -0.33147;
			constexpr double sine_road_incline_angle = -0.325433;
			constexpr double gravity = 9.78074;
			constexpr double gravity_times_sine_road_incline_angle = -3.18298;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 43.4177;
			constexpr double wind_direction = 0.918744;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 5.24533;
			constexpr double air_temp = -0.556422;
			constexpr double pressure = 1002.28;
			constexpr double air_density = 1.03693;
			constexpr double reciprocal_speed_of_sound = 0.00305;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			const auto runner = RaceSegmentRunner(car);
			const double result = runner.calculate_power_in(route_segment, weather_data);
			constexpr double expected = 1.70218;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 7") {
		constexpr double drag_coefficient = 0.00728635;
		constexpr double frontal_area = 4.38598;
		constexpr double array_area = 8.90649;
		constexpr double array_efficiency = 18.859;
		constexpr double energy_capacity = 6794.28;
		constexpr double min_voltage = 128.467;
		constexpr double max_voltage = 139.482;
		constexpr double resistance = 0.258499;
		constexpr double hysteresis_loss = 3.72368;
		constexpr double eddy_current_loss_coefficient = 0.0306822;
		constexpr double alpha = -5.62943;
		constexpr double beta = 5.94647;
		constexpr double a = -4.46172;
		constexpr double b = 8.64608e-06;
		constexpr double c = 0.790872;
		constexpr double pressure_at_stc = 152.21;
		constexpr double mass = 848.593;
		constexpr double wheel_radius = 0.349232;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {-47.5665, 126.219};
			constexpr GeographicalCoordinate end_coordinate = {7.84333, 91.5759};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 52.7788;
			constexpr double weather_station = 4.82243;
			constexpr double distance = 21.1311;
			constexpr double heading = 4.23129;
			constexpr double elevation = 54.2604;
			constexpr double grade = -0.247232;
			constexpr double road_incline_angle = -0.98374;
			constexpr double sine_road_incline_angle = -0.832575;
			constexpr double gravity = 9.80587;
			constexpr double gravity_times_sine_road_incline_angle = -8.16412;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 34.2263;
			constexpr double wind_direction = 2.92841;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 625.273;
			constexpr double air_temp = 45.4859;
			constexpr double pressure = 1050.35;
			constexpr double air_density = 1.0505;
			constexpr double reciprocal_speed_of_sound = 0.00309197;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			const auto runner = RaceSegmentRunner(car);
			const double result = runner.calculate_power_in(route_segment, weather_data);
			constexpr double expected = 1050.26;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {-9.67374, -132.134};
			constexpr GeographicalCoordinate end_coordinate = {59.8543, -174.168};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 80.0487;
			constexpr double weather_station = 3.54564;
			constexpr double distance = 67.1213;
			constexpr double heading = 0.468764;
			constexpr double elevation = -20.7161;
			constexpr double grade = -0.561366;
			constexpr double road_incline_angle = 0.800646;
			constexpr double sine_road_incline_angle = 0.717806;
			constexpr double gravity = 9.78326;
			constexpr double gravity_times_sine_road_incline_angle = 7.02249;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 26.6116;
			constexpr double wind_direction = 5.26277;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 439.142;
			constexpr double air_temp = 21.2373;
			constexpr double pressure = 996.321;
			constexpr double air_density = 1.21469;
			constexpr double reciprocal_speed_of_sound = 0.00309151;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			const auto runner = RaceSegmentRunner(car);
			const double result = runner.calculate_power_in(route_segment, weather_data);
			constexpr double expected = 737.616;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {-20.4329, -27.87};
			constexpr GeographicalCoordinate end_coordinate = {-61.69, -120.026};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 60.7092;
			constexpr double weather_station = 4.81463;
			constexpr double distance = 69.107;
			constexpr double heading = 3.3782;
			constexpr double elevation = -102.416;
			constexpr double grade = 0.423022;
			constexpr double road_incline_angle = -0.968523;
			constexpr double sine_road_incline_angle = -0.82405;
			constexpr double gravity = 9.8138;
			constexpr double gravity_times_sine_road_incline_angle = -8.08705;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 48.516;
			constexpr double wind_direction = 1.17183;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 71.6528;
			constexpr double air_temp = -24.5055;
			constexpr double pressure = 1035.01;
			constexpr double air_density = 1.17598;
			constexpr double reciprocal_speed_of_sound = 0.00299892;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			const auto runner = RaceSegmentRunner(car);
			const double result = runner.calculate_power_in(route_segment, weather_data);
			constexpr double expected = 120.354;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 8") {
		constexpr double drag_coefficient = 0.00398785;
		constexpr double frontal_area = 6.12665;
		constexpr double array_area = 2.41855;
		constexpr double array_efficiency = 26.3434;
		constexpr double energy_capacity = 6095.43;
		constexpr double min_voltage = 111.108;
		constexpr double max_voltage = 144.594;
		constexpr double resistance = 0.342506;
		constexpr double hysteresis_loss = 2.26985;
		constexpr double eddy_current_loss_coefficient = 0.0134123;
		constexpr double alpha = -3.17973;
		constexpr double beta = 8.08507;
		constexpr double a = 9.15215;
		constexpr double b = -4.0981e-06;
		constexpr double c = -0.740325;
		constexpr double pressure_at_stc = 193.145;
		constexpr double mass = 345.045;
		constexpr double wheel_radius = 0.268005;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {-28.9297, -109.568};
			constexpr GeographicalCoordinate end_coordinate = {30.0381, -30.1503};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 163.856;
			constexpr double weather_station = 6.24981;
			constexpr double distance = 45.7418;
			constexpr double heading = 2.70909;
			constexpr double elevation = 480.435;
			constexpr double grade = -0.875212;
			constexpr double road_incline_angle = -0.603682;
			constexpr double sine_road_incline_angle = -0.567677;
			constexpr double gravity = 9.80682;
			constexpr double gravity_times_sine_road_incline_angle = -5.56711;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 37.083;
			constexpr double wind_direction = 1.66566;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 365.817;
			constexpr double air_temp = 33.2588;
			constexpr double pressure = 1092.93;
			constexpr double air_density = 1.07391;
			constexpr double reciprocal_speed_of_sound = 0.00299229;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			const auto runner = RaceSegmentRunner(car);
			const double result = runner.calculate_power_in(route_segment, weather_data);
			constexpr double expected = 233.072;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {-75.1979, 177.874};
			constexpr GeographicalCoordinate end_coordinate = {31.9936, 115.769};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 97.8653;
			constexpr double weather_station = 3.54724;
			constexpr double distance = 85.3519;
			constexpr double heading = 4.54435;
			constexpr double elevation = -46.9167;
			constexpr double grade = -0.230225;
			constexpr double road_incline_angle = 0.672428;
			constexpr double sine_road_incline_angle = 0.622887;
			constexpr double gravity = 9.80014;
			constexpr double gravity_times_sine_road_incline_angle = 6.10438;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 46.3606;
			constexpr double wind_direction = 0.00910533;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 599.318;
			constexpr double air_temp = -8.05855;
			constexpr double pressure = 1002.35;
			constexpr double air_density = 1.08817;
			constexpr double reciprocal_speed_of_sound = 0.00293305;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			const auto runner = RaceSegmentRunner(car);
			const double result = runner.calculate_power_in(route_segment, weather_data);
			constexpr double expected = 381.843;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {43.767, 18.2161};
			constexpr GeographicalCoordinate end_coordinate = {-28.5637, 26.5958};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 10.1961;
			constexpr double weather_station = 5.5232;
			constexpr double distance = 87.2999;
			constexpr double heading = 2.80151;
			constexpr double elevation = 123.305;
			constexpr double grade = -0.0634655;
			constexpr double road_incline_angle = -0.206881;
			constexpr double sine_road_incline_angle = -0.205408;
			constexpr double gravity = 9.81705;
			constexpr double gravity_times_sine_road_incline_angle = -2.0165;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 4.90919;
			constexpr double wind_direction = 1.17468;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 217.781;
			constexpr double air_temp = 26.5154;
			constexpr double pressure = 923.489;
			constexpr double air_density = 1.1762;
			constexpr double reciprocal_speed_of_sound = 0.00302447;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			const auto runner = RaceSegmentRunner(car);
			const double result = runner.calculate_power_in(route_segment, weather_data);
			constexpr double expected = 138.754;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 9") {
		constexpr double drag_coefficient = 0.00845813;
		constexpr double frontal_area = 4.81854;
		constexpr double array_area = 2.6616;
		constexpr double array_efficiency = 28.8755;
		constexpr double energy_capacity = 4611.02;
		constexpr double min_voltage = 70.4557;
		constexpr double max_voltage = 116.798;
		constexpr double resistance = 0.00497603;
		constexpr double hysteresis_loss = 2.65106;
		constexpr double eddy_current_loss_coefficient = 0.0462534;
		constexpr double alpha = -3.69918;
		constexpr double beta = 9.11168;
		constexpr double a = -9.87299;
		constexpr double b = -7.41922e-06;
		constexpr double c = 0.531573;
		constexpr double pressure_at_stc = 115.268;
		constexpr double mass = 991.195;
		constexpr double wheel_radius = 0.23418;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {-27.9246, 4.76317};
			constexpr GeographicalCoordinate end_coordinate = {72.0903, 159.524};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 43.7304;
			constexpr double weather_station = 8.83236;
			constexpr double distance = 94.1149;
			constexpr double heading = 0.974368;
			constexpr double elevation = 377.762;
			constexpr double grade = -0.935008;
			constexpr double road_incline_angle = 1.40133;
			constexpr double sine_road_incline_angle = 0.985674;
			constexpr double gravity = 9.80203;
			constexpr double gravity_times_sine_road_incline_angle = 9.66161;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 47.6954;
			constexpr double wind_direction = 5.22271;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 897.716;
			constexpr double air_temp = 36.5862;
			constexpr double pressure = 962.32;
			constexpr double air_density = 1.00012;
			constexpr double reciprocal_speed_of_sound = 0.00306646;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			const auto runner = RaceSegmentRunner(car);
			const double result = runner.calculate_power_in(route_segment, weather_data);
			constexpr double expected = 689.94;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {-15.3694, 109.641};
			constexpr GeographicalCoordinate end_coordinate = {61.5131, 150.834};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 191.899;
			constexpr double weather_station = 1.7898;
			constexpr double distance = 18.6902;
			constexpr double heading = 1.5872;
			constexpr double elevation = 57.7455;
			constexpr double grade = -0.0185118;
			constexpr double road_incline_angle = -0.585459;
			constexpr double sine_road_incline_angle = -0.552582;
			constexpr double gravity = 9.80017;
			constexpr double gravity_times_sine_road_incline_angle = -5.4154;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 35.6704;
			constexpr double wind_direction = 2.37721;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 237.407;
			constexpr double air_temp = -4.50803;
			constexpr double pressure = 1011.21;
			constexpr double air_density = 1.2355;
			constexpr double reciprocal_speed_of_sound = 0.00294081;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			const auto runner = RaceSegmentRunner(car);
			const double result = runner.calculate_power_in(route_segment, weather_data);
			constexpr double expected = 182.459;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {-4.69723, 123.648};
			constexpr GeographicalCoordinate end_coordinate = {44.7412, 167.945};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 192.981;
			constexpr double weather_station = 0.6941;
			constexpr double distance = 85.8045;
			constexpr double heading = 4.46833;
			constexpr double elevation = 290.17;
			constexpr double grade = -0.348972;
			constexpr double road_incline_angle = -1.15965;
			constexpr double sine_road_incline_angle = -0.916663;
			constexpr double gravity = 9.78924;
			constexpr double gravity_times_sine_road_incline_angle = -8.97343;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 3.7941;
			constexpr double wind_direction = 1.59472;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 761.872;
			constexpr double air_temp = -40.1065;
			constexpr double pressure = 1089.34;
			constexpr double air_density = 1.27651;
			constexpr double reciprocal_speed_of_sound = 0.00304779;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			const auto runner = RaceSegmentRunner(car);
			const double result = runner.calculate_power_in(route_segment, weather_data);
			constexpr double expected = 585.537;
			REQUIRE_THAT(result, WithinRel(expected, EPSILON));
		}
	}
}
TEST_CASE("RaceSegmentRunner: calculate_power_net", "[RaceSegmentRunner]") {
	SECTION("Random Test 0") {
		constexpr double drag_coefficient = 0.00478134;
		constexpr double frontal_area = 8.11634;
		constexpr double array_area = 6.84089;
		constexpr double array_efficiency = 24.9139;
		constexpr double energy_capacity = 3541.06;
		constexpr double min_voltage = 112.294;
		constexpr double max_voltage = 152.167;
		constexpr double resistance = 0.582171;
		constexpr double hysteresis_loss = 4.95928;
		constexpr double eddy_current_loss_coefficient = 0.00141462;
		constexpr double alpha = -6.61967;
		constexpr double beta = 8.82183;
		constexpr double a = -9.43696;
		constexpr double b = 7.8817e-06;
		constexpr double c = 0.531821;
		constexpr double pressure_at_stc = 139.279;
		constexpr double mass = 503.682;
		constexpr double wheel_radius = 0.227503;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		const auto runner = RaceSegmentRunner(car);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {17.0896, -169.125};
			constexpr GeographicalCoordinate end_coordinate = {48.3989, -119.13};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 85.1263;
			constexpr double weather_station = 3.18048;
			constexpr double distance = 3.89814;
			constexpr double heading = 2.43882;
			constexpr double elevation = 289.744;
			constexpr double grade = -0.926165;
			constexpr double road_incline_angle = 0.515131;
			constexpr double sine_road_incline_angle = 0.492649;
			constexpr double gravity = 9.79607;
			constexpr double gravity_times_sine_road_incline_angle = 4.82602;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 18.3174;
			constexpr double wind_direction = 2.01478;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 87.3047;
			constexpr double air_temp = -38.0313;
			constexpr double pressure = 983.149;
			constexpr double air_density = 1.16106;
			constexpr double reciprocal_speed_of_sound = 0.00303844;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double state_of_charge = 0.431736;
			constexpr double speed = 17.9708;

			const auto result = runner.calculate_power_net(route_segment, weather_data, state_of_charge, speed);
			constexpr double expected = -1.95128e+23;
			REQUIRE(result.has_value());
			REQUIRE_THAT(result.value(), WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {84.3725, -62.0612};
			constexpr GeographicalCoordinate end_coordinate = {37.6157, -167.325};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 191.503;
			constexpr double weather_station = 4.09073;
			constexpr double distance = 80.3352;
			constexpr double heading = 4.26834;
			constexpr double elevation = 51.3853;
			constexpr double grade = -0.672044;
			constexpr double road_incline_angle = 0.352955;
			constexpr double sine_road_incline_angle = 0.345672;
			constexpr double gravity = 9.80445;
			constexpr double gravity_times_sine_road_incline_angle = 3.38912;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 3.71928;
			constexpr double wind_direction = 2.05514;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 230.522;
			constexpr double air_temp = -12.1769;
			constexpr double pressure = 960.921;
			constexpr double air_density = 1.25786;
			constexpr double reciprocal_speed_of_sound = 0.00307708;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double state_of_charge = 0.370989;
			constexpr double speed = 20.6447;

			const auto result = runner.calculate_power_net(route_segment, weather_data, state_of_charge, speed);
			constexpr double expected = -2.98379e+23;
			REQUIRE(result.has_value());
			REQUIRE_THAT(result.value(), WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {1.38153, -57.1756};
			constexpr GeographicalCoordinate end_coordinate = {-11.2163, -30.95};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 41.3155;
			constexpr double weather_station = 2.11114;
			constexpr double distance = 37.5984;
			constexpr double heading = 2.71927;
			constexpr double elevation = 282.962;
			constexpr double grade = 0.928775;
			constexpr double road_incline_angle = 0.862063;
			constexpr double sine_road_incline_angle = 0.759187;
			constexpr double gravity = 9.79147;
			constexpr double gravity_times_sine_road_incline_angle = 7.43356;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 14.8767;
			constexpr double wind_direction = 2.18166;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 226.181;
			constexpr double air_temp = 22.1308;
			constexpr double pressure = 917.681;
			constexpr double air_density = 1.06788;
			constexpr double reciprocal_speed_of_sound = 0.00291376;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double state_of_charge = 0.863048;
			constexpr double speed = 1.54541;

			const auto result = runner.calculate_power_net(route_segment, weather_data, state_of_charge, speed);
			constexpr double expected = -5.29585e+19;
			REQUIRE(result.has_value());
			REQUIRE_THAT(result.value(), WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 1") {
		constexpr double drag_coefficient = 0.00190636;
		constexpr double frontal_area = 8.45271;
		constexpr double array_area = 6.49736;
		constexpr double array_efficiency = 25.0395;
		constexpr double energy_capacity = 7294.68;
		constexpr double min_voltage = 108.055;
		constexpr double max_voltage = 137.042;
		constexpr double resistance = 0.473203;
		constexpr double hysteresis_loss = 3.27523;
		constexpr double eddy_current_loss_coefficient = 0.0337318;
		constexpr double alpha = 0.884214;
		constexpr double beta = 4.77419;
		constexpr double a = -4.03948;
		constexpr double b = -1.45932e-06;
		constexpr double c = -0.123339;
		constexpr double pressure_at_stc = 199.868;
		constexpr double mass = 655.208;
		constexpr double wheel_radius = 0.393174;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		const auto runner = RaceSegmentRunner(car);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {4.33479, 69.1908};
			constexpr GeographicalCoordinate end_coordinate = {64.8404, 108.452};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 181.158;
			constexpr double weather_station = 5.10383;
			constexpr double distance = 46.3882;
			constexpr double heading = 2.497;
			constexpr double elevation = 314.766;
			constexpr double grade = -0.0913186;
			constexpr double road_incline_angle = -1.4994;
			constexpr double sine_road_incline_angle = -0.997452;
			constexpr double gravity = 9.79703;
			constexpr double gravity_times_sine_road_incline_angle = -9.77207;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 15.5238;
			constexpr double wind_direction = 5.57893;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 271.037;
			constexpr double air_temp = 45.4173;
			constexpr double pressure = 942.092;
			constexpr double air_density = 1.01229;
			constexpr double reciprocal_speed_of_sound = 0.00293374;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double state_of_charge = 0.337539;
			constexpr double speed = 28.8662;

			const auto result = runner.calculate_power_net(route_segment, weather_data, state_of_charge, speed);
			REQUIRE_FALSE(result.has_value());
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {-18.4201, 99.5253};
			constexpr GeographicalCoordinate end_coordinate = {-60.7212, 43.0711};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 42.1229;
			constexpr double weather_station = 2.85169;
			constexpr double distance = 60.4818;
			constexpr double heading = 5.42846;
			constexpr double elevation = -325.57;
			constexpr double grade = -0.0190179;
			constexpr double road_incline_angle = -1.017;
			constexpr double sine_road_incline_angle = -0.850532;
			constexpr double gravity = 9.78685;
			constexpr double gravity_times_sine_road_incline_angle = -8.32403;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 3.85978;
			constexpr double wind_direction = 1.72546;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 932.278;
			constexpr double air_temp = 20.503;
			constexpr double pressure = 992.063;
			constexpr double air_density = 1.23593;
			constexpr double reciprocal_speed_of_sound = 0.0029789;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double state_of_charge = 0.547472;
			constexpr double speed = 15.9268;

			const auto result = runner.calculate_power_net(route_segment, weather_data, state_of_charge, speed);
			REQUIRE_FALSE(result.has_value());
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {10.6521, -138.904};
			constexpr GeographicalCoordinate end_coordinate = {-56.9235, 101.296};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 21.4211;
			constexpr double weather_station = 7.71503;
			constexpr double distance = 57.287;
			constexpr double heading = 4.60275;
			constexpr double elevation = -241.865;
			constexpr double grade = 0.684307;
			constexpr double road_incline_angle = -1.49071;
			constexpr double sine_road_incline_angle = -0.996795;
			constexpr double gravity = 9.81406;
			constexpr double gravity_times_sine_road_incline_angle = -9.78261;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 19.2415;
			constexpr double wind_direction = 1.97632;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 114.154;
			constexpr double air_temp = 45.1243;
			constexpr double pressure = 1046.18;
			constexpr double air_density = 1.21775;
			constexpr double reciprocal_speed_of_sound = 0.00300408;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double state_of_charge = 0.195472;
			constexpr double speed = 1.91139;

			const auto result = runner.calculate_power_net(route_segment, weather_data, state_of_charge, speed);
			REQUIRE_FALSE(result.has_value());
		}
	}
	SECTION("Random Test 2") {
		constexpr double drag_coefficient = 0.00862029;
		constexpr double frontal_area = 3.79417;
		constexpr double array_area = 7.41743;
		constexpr double array_efficiency = 25.4149;
		constexpr double energy_capacity = 5106.03;
		constexpr double min_voltage = 91.3073;
		constexpr double max_voltage = 115.626;
		constexpr double resistance = 0.86839;
		constexpr double hysteresis_loss = 2.97901;
		constexpr double eddy_current_loss_coefficient = 0.0046227;
		constexpr double alpha = 1.83719;
		constexpr double beta = -7.32939;
		constexpr double a = -6.19527;
		constexpr double b = -9.82932e-06;
		constexpr double c = 0.475401;
		constexpr double pressure_at_stc = 134.891;
		constexpr double mass = 697.35;
		constexpr double wheel_radius = 0.434368;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		const auto runner = RaceSegmentRunner(car);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {-72.7563, 49.5861};
			constexpr GeographicalCoordinate end_coordinate = {-63.6866, 164.698};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 139.924;
			constexpr double weather_station = 0.798457;
			constexpr double distance = 6.15313;
			constexpr double heading = 4.80089;
			constexpr double elevation = 425.006;
			constexpr double grade = 0.779879;
			constexpr double road_incline_angle = -1.23571;
			constexpr double sine_road_incline_angle = -0.944383;
			constexpr double gravity = 9.79753;
			constexpr double gravity_times_sine_road_incline_angle = -9.25262;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 1.18128;
			constexpr double wind_direction = 2.04633;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 168.021;
			constexpr double air_temp = 18.2182;
			constexpr double pressure = 1084.77;
			constexpr double air_density = 1.04132;
			constexpr double reciprocal_speed_of_sound = 0.00297581;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double state_of_charge = 0.547465;
			constexpr double speed = 2.38883;

			const auto result = runner.calculate_power_net(route_segment, weather_data, state_of_charge, speed);
			REQUIRE_FALSE(result.has_value());
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {-3.6583, 161.337};
			constexpr GeographicalCoordinate end_coordinate = {4.06834, 74.0937};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 106.489;
			constexpr double weather_station = 0.51622;
			constexpr double distance = 7.36061;
			constexpr double heading = 2.47586;
			constexpr double elevation = 155.692;
			constexpr double grade = 0.668876;
			constexpr double road_incline_angle = 0.558598;
			constexpr double sine_road_incline_angle = 0.529998;
			constexpr double gravity = 9.78985;
			constexpr double gravity_times_sine_road_incline_angle = 5.1886;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 37.6294;
			constexpr double wind_direction = 0.819954;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 791.778;
			constexpr double air_temp = -21.7846;
			constexpr double pressure = 966.933;
			constexpr double air_density = 1.01645;
			constexpr double reciprocal_speed_of_sound = 0.00309904;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double state_of_charge = 0.146986;
			constexpr double speed = 9.99077;

			const auto result = runner.calculate_power_net(route_segment, weather_data, state_of_charge, speed);
			constexpr double expected = -54864.8;
			REQUIRE(result.has_value());
			REQUIRE_THAT(result.value(), WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {-78.2753, 177.154};
			constexpr GeographicalCoordinate end_coordinate = {22.6186, 145.331};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 195.995;
			constexpr double weather_station = 1.94486;
			constexpr double distance = 60.5979;
			constexpr double heading = 0.930267;
			constexpr double elevation = -7.19599;
			constexpr double grade = -0.911772;
			constexpr double road_incline_angle = 0.849318;
			constexpr double sine_road_incline_angle = 0.75083;
			constexpr double gravity = 9.79401;
			constexpr double gravity_times_sine_road_incline_angle = 7.35363;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 34.7444;
			constexpr double wind_direction = 2.18798;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 820.127;
			constexpr double air_temp = -2.33595;
			constexpr double pressure = 925.117;
			constexpr double air_density = 1.03422;
			constexpr double reciprocal_speed_of_sound = 0.00304369;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double state_of_charge = 0.497384;
			constexpr double speed = 26.9609;

			const auto result = runner.calculate_power_net(route_segment, weather_data, state_of_charge, speed);
			constexpr double expected = -239295;
			REQUIRE(result.has_value());
			REQUIRE_THAT(result.value(), WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 3") {
		constexpr double drag_coefficient = 0.00592518;
		constexpr double frontal_area = 3.99403;
		constexpr double array_area = 6.83385;
		constexpr double array_efficiency = 19.2383;
		constexpr double energy_capacity = 816.35;
		constexpr double min_voltage = 85.0976;
		constexpr double max_voltage = 151.932;
		constexpr double resistance = 0.0115715;
		constexpr double hysteresis_loss = 1.53358;
		constexpr double eddy_current_loss_coefficient = 0.0272206;
		constexpr double alpha = -8.02265;
		constexpr double beta = -6.34215;
		constexpr double a = 4.55537;
		constexpr double b = 4.55176e-06;
		constexpr double c = -0.000382384;
		constexpr double pressure_at_stc = 196.894;
		constexpr double mass = 962.322;
		constexpr double wheel_radius = 0.378762;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		const auto runner = RaceSegmentRunner(car);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {40.5518, -13.6993};
			constexpr GeographicalCoordinate end_coordinate = {34.3462, -113.477};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 198.567;
			constexpr double weather_station = 4.86427;
			constexpr double distance = 60.6869;
			constexpr double heading = 3.14572;
			constexpr double elevation = -50.6678;
			constexpr double grade = -0.254025;
			constexpr double road_incline_angle = 1.3395;
			constexpr double sine_road_incline_angle = 0.973371;
			constexpr double gravity = 9.78695;
			constexpr double gravity_times_sine_road_incline_angle = 9.52634;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 37.5097;
			constexpr double wind_direction = 0.580462;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 531.433;
			constexpr double air_temp = -45.2899;
			constexpr double pressure = 937.145;
			constexpr double air_density = 1.15434;
			constexpr double reciprocal_speed_of_sound = 0.00305737;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double state_of_charge = 0.0317579;
			constexpr double speed = 8.50323;

			const auto result = runner.calculate_power_net(route_segment, weather_data, state_of_charge, speed);
			constexpr double expected = -84746.6;
			REQUIRE(result.has_value());
			REQUIRE_THAT(result.value(), WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {-19.6899, 2.32235};
			constexpr GeographicalCoordinate end_coordinate = {-1.80857, 3.39652};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 66.6256;
			constexpr double weather_station = 1.21012;
			constexpr double distance = 82.3881;
			constexpr double heading = 4.68552;
			constexpr double elevation = 345.269;
			constexpr double grade = -0.794471;
			constexpr double road_incline_angle = -1.49243;
			constexpr double sine_road_incline_angle = -0.996931;
			constexpr double gravity = 9.79891;
			constexpr double gravity_times_sine_road_incline_angle = -9.76884;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 11.7038;
			constexpr double wind_direction = 3.07598;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 964.977;
			constexpr double air_temp = 41.6419;
			constexpr double pressure = 1082.23;
			constexpr double air_density = 1.11708;
			constexpr double reciprocal_speed_of_sound = 0.00305497;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double state_of_charge = 0.0150801;
			constexpr double speed = 6.31492;

			const auto result = runner.calculate_power_net(route_segment, weather_data, state_of_charge, speed);
			constexpr double expected = 53453.6;
			REQUIRE(result.has_value());
			REQUIRE_THAT(result.value(), WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {-11.4052, -0.987663};
			constexpr GeographicalCoordinate end_coordinate = {-29.162, 177.962};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 39.2994;
			constexpr double weather_station = 4.14194;
			constexpr double distance = 58.8776;
			constexpr double heading = 1.8574;
			constexpr double elevation = -237.351;
			constexpr double grade = -0.70448;
			constexpr double road_incline_angle = 1.11741;
			constexpr double sine_road_incline_angle = 0.89897;
			constexpr double gravity = 9.788;
			constexpr double gravity_times_sine_road_incline_angle = 8.79912;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 41.8527;
			constexpr double wind_direction = 4.99027;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 118.311;
			constexpr double air_temp = 26.8401;
			constexpr double pressure = 1043.82;
			constexpr double air_density = 1.03006;
			constexpr double reciprocal_speed_of_sound = 0.00302075;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double state_of_charge = 0.89334;
			constexpr double speed = 10.4828;

			const auto result = runner.calculate_power_net(route_segment, weather_data, state_of_charge, speed);
			constexpr double expected = -92702.3;
			REQUIRE(result.has_value());
			REQUIRE_THAT(result.value(), WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 4") {
		constexpr double drag_coefficient = 0.00700623;
		constexpr double frontal_area = 7.99156;
		constexpr double array_area = 8.15596;
		constexpr double array_efficiency = 21.2604;
		constexpr double energy_capacity = 349.479;
		constexpr double min_voltage = 74.7494;
		constexpr double max_voltage = 160.438;
		constexpr double resistance = 0.320127;
		constexpr double hysteresis_loss = 4.45575;
		constexpr double eddy_current_loss_coefficient = 0.0272854;
		constexpr double alpha = -4.70906;
		constexpr double beta = -0.736132;
		constexpr double a = 0.728361;
		constexpr double b = -7.60101e-07;
		constexpr double c = -0.631788;
		constexpr double pressure_at_stc = 129.199;
		constexpr double mass = 401.787;
		constexpr double wheel_radius = 0.239047;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		const auto runner = RaceSegmentRunner(car);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {6.94659, 168.959};
			constexpr GeographicalCoordinate end_coordinate = {-87.6408, 34.9422};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 91.7483;
			constexpr double weather_station = 3.33139;
			constexpr double distance = 71.3732;
			constexpr double heading = 4.93346;
			constexpr double elevation = 361.144;
			constexpr double grade = -0.787459;
			constexpr double road_incline_angle = -1.38702;
			constexpr double sine_road_incline_angle = -0.983161;
			constexpr double gravity = 9.7855;
			constexpr double gravity_times_sine_road_incline_angle = -9.62072;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 42.7051;
			constexpr double wind_direction = 0.0546119;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 793.724;
			constexpr double air_temp = -22.9487;
			constexpr double pressure = 914.53;
			constexpr double air_density = 1.09607;
			constexpr double reciprocal_speed_of_sound = 0.00300491;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double state_of_charge = 0.312824;
			constexpr double speed = 12.5463;

			const auto result = runner.calculate_power_net(route_segment, weather_data, state_of_charge, speed);
			REQUIRE_FALSE(result.has_value());
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {-73.6652, 94.5612};
			constexpr GeographicalCoordinate end_coordinate = {-62.6269, -173.285};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 129.842;
			constexpr double weather_station = 9.32067;
			constexpr double distance = 74.1915;
			constexpr double heading = 4.28744;
			constexpr double elevation = -232.852;
			constexpr double grade = -0.968797;
			constexpr double road_incline_angle = -1.26524;
			constexpr double sine_road_incline_angle = -0.953678;
			constexpr double gravity = 9.80814;
			constexpr double gravity_times_sine_road_incline_angle = -9.35381;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 39.6346;
			constexpr double wind_direction = 3.07429;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 212.761;
			constexpr double air_temp = 27.2788;
			constexpr double pressure = 1084.85;
			constexpr double air_density = 1.25273;
			constexpr double reciprocal_speed_of_sound = 0.00303513;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double state_of_charge = 0.693573;
			constexpr double speed = 22.9937;

			const auto result = runner.calculate_power_net(route_segment, weather_data, state_of_charge, speed);
			REQUIRE_FALSE(result.has_value());
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {33.9953, 22.0611};
			constexpr GeographicalCoordinate end_coordinate = {82.7086, 68.6094};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 151.251;
			constexpr double weather_station = 1.65156;
			constexpr double distance = 94.9767;
			constexpr double heading = 1.64207;
			constexpr double elevation = -192.046;
			constexpr double grade = -0.281472;
			constexpr double road_incline_angle = -0.00442458;
			constexpr double sine_road_incline_angle = -0.00442457;
			constexpr double gravity = 9.81998;
			constexpr double gravity_times_sine_road_incline_angle = -0.0434492;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 36.8469;
			constexpr double wind_direction = 2.74236;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 698.999;
			constexpr double air_temp = -7.4191;
			constexpr double pressure = 995.737;
			constexpr double air_density = 1.07093;
			constexpr double reciprocal_speed_of_sound = 0.00307099;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double state_of_charge = 0.569201;
			constexpr double speed = 18.3505;

			const auto result = runner.calculate_power_net(route_segment, weather_data, state_of_charge, speed);
			constexpr double expected = 834.078;
			REQUIRE(result.has_value());
			REQUIRE_THAT(result.value(), WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 5") {
		constexpr double drag_coefficient = 0.0015432;
		constexpr double frontal_area = 2.65154;
		constexpr double array_area = 5.31246;
		constexpr double array_efficiency = 15.845;
		constexpr double energy_capacity = 1431.55;
		constexpr double min_voltage = 102.207;
		constexpr double max_voltage = 139.599;
		constexpr double resistance = 0.264847;
		constexpr double hysteresis_loss = 3.08124;
		constexpr double eddy_current_loss_coefficient = 0.00544423;
		constexpr double alpha = 1.10488;
		constexpr double beta = 9.62674;
		constexpr double a = -6.66843;
		constexpr double b = 5.1872e-06;
		constexpr double c = 0.971193;
		constexpr double pressure_at_stc = 128.716;
		constexpr double mass = 687.135;
		constexpr double wheel_radius = 0.352807;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		const auto runner = RaceSegmentRunner(car);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {-5.8494, 57.611};
			constexpr GeographicalCoordinate end_coordinate = {57.6526, -17.3432};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 77.6056;
			constexpr double weather_station = 4.44356;
			constexpr double distance = 0.212458;
			constexpr double heading = 5.42455;
			constexpr double elevation = -220.702;
			constexpr double grade = -0.448675;
			constexpr double road_incline_angle = -1.35218;
			constexpr double sine_road_incline_angle = -0.976199;
			constexpr double gravity = 9.78743;
			constexpr double gravity_times_sine_road_incline_angle = -9.55448;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 5.76563;
			constexpr double wind_direction = 4.37607;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 979.094;
			constexpr double air_temp = 14.4306;
			constexpr double pressure = 1006.53;
			constexpr double air_density = 1.17023;
			constexpr double reciprocal_speed_of_sound = 0.00307624;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double state_of_charge = 0.528339;
			constexpr double speed = 1.17494;

			const auto result = runner.calculate_power_net(route_segment, weather_data, state_of_charge, speed);
			constexpr double expected = -3.80193e+40;
			REQUIRE(result.has_value());
			REQUIRE_THAT(result.value(), WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {-41.3225, 139.375};
			constexpr GeographicalCoordinate end_coordinate = {-8.64132, -55.7236};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 64.3703;
			constexpr double weather_station = 6.61779;
			constexpr double distance = 21.7686;
			constexpr double heading = 2.78568;
			constexpr double elevation = -462.481;
			constexpr double grade = 0.81775;
			constexpr double road_incline_angle = -0.53607;
			constexpr double sine_road_incline_angle = -0.510761;
			constexpr double gravity = 9.78589;
			constexpr double gravity_times_sine_road_incline_angle = -4.99825;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 35.3468;
			constexpr double wind_direction = 2.01715;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 433.193;
			constexpr double air_temp = -19.535;
			constexpr double pressure = 964.397;
			constexpr double air_density = 1.21747;
			constexpr double reciprocal_speed_of_sound = 0.00307235;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double state_of_charge = 0.845209;
			constexpr double speed = 16.3738;

			const auto result = runner.calculate_power_net(route_segment, weather_data, state_of_charge, speed);
			constexpr double expected = -1.66397e+44;
			REQUIRE(result.has_value());
			REQUIRE_THAT(result.value(), WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {-4.05869, 80.1854};
			constexpr GeographicalCoordinate end_coordinate = {32.5429, 175.227};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 114.448;
			constexpr double weather_station = 4.24446;
			constexpr double distance = 18.1624;
			constexpr double heading = 0.355123;
			constexpr double elevation = 498.624;
			constexpr double grade = 0.762728;
			constexpr double road_incline_angle = 0.513821;
			constexpr double sine_road_incline_angle = 0.491509;
			constexpr double gravity = 9.81303;
			constexpr double gravity_times_sine_road_incline_angle = 4.82319;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 32.9596;
			constexpr double wind_direction = 5.51884;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 550.358;
			constexpr double air_temp = 1.26731;
			constexpr double pressure = 956.063;
			constexpr double air_density = 1.29356;
			constexpr double reciprocal_speed_of_sound = 0.00292702;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double state_of_charge = 0.00820812;
			constexpr double speed = 14.469;

			const auto result = runner.calculate_power_net(route_segment, weather_data, state_of_charge, speed);
			constexpr double expected = -1.17857e+44;
			REQUIRE(result.has_value());
			REQUIRE_THAT(result.value(), WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 6") {
		constexpr double drag_coefficient = 0.0087334;
		constexpr double frontal_area = 6.79608;
		constexpr double array_area = 7.08935;
		constexpr double array_efficiency = 19.6278;
		constexpr double energy_capacity = 4978.73;
		constexpr double min_voltage = 135.273;
		constexpr double max_voltage = 153.271;
		constexpr double resistance = 0.0594918;
		constexpr double hysteresis_loss = 2.62256;
		constexpr double eddy_current_loss_coefficient = 0.0454957;
		constexpr double alpha = 6.81892;
		constexpr double beta = -8.5195;
		constexpr double a = -0.698848;
		constexpr double b = -4.8456e-06;
		constexpr double c = 0.207999;
		constexpr double pressure_at_stc = 165.194;
		constexpr double mass = 721.558;
		constexpr double wheel_radius = 0.228934;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		const auto runner = RaceSegmentRunner(car);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {-3.15139, 8.75234};
			constexpr GeographicalCoordinate end_coordinate = {-51.4343, -42.8137};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 123.726;
			constexpr double weather_station = 7.1651;
			constexpr double distance = 21.0567;
			constexpr double heading = 6.12645;
			constexpr double elevation = 279.747;
			constexpr double grade = -0.913569;
			constexpr double road_incline_angle = -0.511349;
			constexpr double sine_road_incline_angle = -0.489354;
			constexpr double gravity = 9.78982;
			constexpr double gravity_times_sine_road_incline_angle = -4.79068;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 40.0214;
			constexpr double wind_direction = 5.69587;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 95.6887;
			constexpr double air_temp = -10.8088;
			constexpr double pressure = 1042.19;
			constexpr double air_density = 1.09055;
			constexpr double reciprocal_speed_of_sound = 0.00305802;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double state_of_charge = 0.477362;
			constexpr double speed = 1.4305;

			const auto result = runner.calculate_power_net(route_segment, weather_data, state_of_charge, speed);
			constexpr double expected = 4934.73;
			REQUIRE(result.has_value());
			REQUIRE_THAT(result.value(), WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {-33.6082, -142.76};
			constexpr GeographicalCoordinate end_coordinate = {-84.764, -88.7516};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 155.619;
			constexpr double weather_station = 0.387374;
			constexpr double distance = 31.2923;
			constexpr double heading = 2.57691;
			constexpr double elevation = 424.958;
			constexpr double grade = -0.97355;
			constexpr double road_incline_angle = 0.562984;
			constexpr double sine_road_incline_angle = 0.533712;
			constexpr double gravity = 9.78002;
			constexpr double gravity_times_sine_road_incline_angle = 5.21972;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 23.8338;
			constexpr double wind_direction = 5.91844;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 586.563;
			constexpr double air_temp = -13.3505;
			constexpr double pressure = 1058.56;
			constexpr double air_density = 1.17341;
			constexpr double reciprocal_speed_of_sound = 0.00298283;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double state_of_charge = 0.385141;
			constexpr double speed = 4.1011;

			const auto result = runner.calculate_power_net(route_segment, weather_data, state_of_charge, speed);
			constexpr double expected = -15271.3;
			REQUIRE(result.has_value());
			REQUIRE_THAT(result.value(), WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {40.3926, 23.6748};
			constexpr GeographicalCoordinate end_coordinate = {23.6942, -112.938};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 167.725;
			constexpr double weather_station = 4.00114;
			constexpr double distance = 92.7342;
			constexpr double heading = 2.09531;
			constexpr double elevation = -121.311;
			constexpr double grade = 0.542405;
			constexpr double road_incline_angle = 0.44683;
			constexpr double sine_road_incline_angle = 0.432109;
			constexpr double gravity = 9.80389;
			constexpr double gravity_times_sine_road_incline_angle = 4.23635;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 19.0563;
			constexpr double wind_direction = 3.76658;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 835.651;
			constexpr double air_temp = 49.5977;
			constexpr double pressure = 1062.04;
			constexpr double air_density = 1.2311;
			constexpr double reciprocal_speed_of_sound = 0.00297761;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double state_of_charge = 0.0814053;
			constexpr double speed = 18.3903;

			const auto result = runner.calculate_power_net(route_segment, weather_data, state_of_charge, speed);
			constexpr double expected = -62550.8;
			REQUIRE(result.has_value());
			REQUIRE_THAT(result.value(), WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 7") {
		constexpr double drag_coefficient = 0.00705445;
		constexpr double frontal_area = 3.60776;
		constexpr double array_area = 1.94779;
		constexpr double array_efficiency = 15.1406;
		constexpr double energy_capacity = 2706.57;
		constexpr double min_voltage = 77.7529;
		constexpr double max_voltage = 151.996;
		constexpr double resistance = 0.981157;
		constexpr double hysteresis_loss = 4.04611;
		constexpr double eddy_current_loss_coefficient = 0.00251885;
		constexpr double alpha = 4.82937;
		constexpr double beta = 3.73381;
		constexpr double a = -8.21873;
		constexpr double b = 3.05667e-06;
		constexpr double c = 0.414908;
		constexpr double pressure_at_stc = 104.694;
		constexpr double mass = 532.223;
		constexpr double wheel_radius = 0.206152;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		const auto runner = RaceSegmentRunner(car);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {19.664, -105.148};
			constexpr GeographicalCoordinate end_coordinate = {2.14487, 148.659};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 146.556;
			constexpr double weather_station = 7.22517;
			constexpr double distance = 7.97552;
			constexpr double heading = 1.4537;
			constexpr double elevation = 438.536;
			constexpr double grade = -0.260111;
			constexpr double road_incline_angle = 0.315953;
			constexpr double sine_road_incline_angle = 0.310722;
			constexpr double gravity = 9.81704;
			constexpr double gravity_times_sine_road_incline_angle = 3.05037;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 36.8834;
			constexpr double wind_direction = 4.81248;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 626.681;
			constexpr double air_temp = 38.8277;
			constexpr double pressure = 1056.12;
			constexpr double air_density = 1.15027;
			constexpr double reciprocal_speed_of_sound = 0.00298049;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double state_of_charge = 0.558569;
			constexpr double speed = 6.65612;

			const auto result = runner.calculate_power_net(route_segment, weather_data, state_of_charge, speed);
			constexpr double expected = -1.32905e+27;
			REQUIRE(result.has_value());
			REQUIRE_THAT(result.value(), WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {74.6555, -109.419};
			constexpr GeographicalCoordinate end_coordinate = {54.2542, -104.16};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 3.57119;
			constexpr double weather_station = 5.48787;
			constexpr double distance = 12.508;
			constexpr double heading = 4.7499;
			constexpr double elevation = 448.525;
			constexpr double grade = 0.176971;
			constexpr double road_incline_angle = 0.0457305;
			constexpr double sine_road_incline_angle = 0.0457146;
			constexpr double gravity = 9.79945;
			constexpr double gravity_times_sine_road_incline_angle = 0.447978;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 46.0889;
			constexpr double wind_direction = 0.0922046;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 218.678;
			constexpr double air_temp = -26.4233;
			constexpr double pressure = 1058.33;
			constexpr double air_density = 1.13066;
			constexpr double reciprocal_speed_of_sound = 0.00297953;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double state_of_charge = 0.210559;
			constexpr double speed = 8.1361;

			const auto result = runner.calculate_power_net(route_segment, weather_data, state_of_charge, speed);
			constexpr double expected = -2.43961e+27;
			REQUIRE(result.has_value());
			REQUIRE_THAT(result.value(), WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {6.49218, -124.559};
			constexpr GeographicalCoordinate end_coordinate = {30.2344, 90.6781};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 145.939;
			constexpr double weather_station = 6.89765;
			constexpr double distance = 35.3074;
			constexpr double heading = 2.84847;
			constexpr double elevation = 301.43;
			constexpr double grade = 0.443395;
			constexpr double road_incline_angle = 0.515955;
			constexpr double sine_road_incline_angle = 0.493365;
			constexpr double gravity = 9.80253;
			constexpr double gravity_times_sine_road_incline_angle = 4.83623;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 26.2132;
			constexpr double wind_direction = 1.54721;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 646.27;
			constexpr double air_temp = -20.3389;
			constexpr double pressure = 1034.94;
			constexpr double air_density = 1.2576;
			constexpr double reciprocal_speed_of_sound = 0.00295574;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double state_of_charge = 0.967934;
			constexpr double speed = 19.8354;

			const auto result = runner.calculate_power_net(route_segment, weather_data, state_of_charge, speed);
			constexpr double expected = -3.60876e+28;
			REQUIRE(result.has_value());
			REQUIRE_THAT(result.value(), WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 8") {
		constexpr double drag_coefficient = 0.00348841;
		constexpr double frontal_area = 7.1209;
		constexpr double array_area = 9.48758;
		constexpr double array_efficiency = 18.0379;
		constexpr double energy_capacity = 559.736;
		constexpr double min_voltage = 107.746;
		constexpr double max_voltage = 141.335;
		constexpr double resistance = 0.28953;
		constexpr double hysteresis_loss = 4.51794;
		constexpr double eddy_current_loss_coefficient = 0.0103321;
		constexpr double alpha = -6.07131;
		constexpr double beta = 2.63107;
		constexpr double a = 5.37227;
		constexpr double b = -6.96226e-06;
		constexpr double c = 0.462575;
		constexpr double pressure_at_stc = 196.436;
		constexpr double mass = 400.264;
		constexpr double wheel_radius = 0.380006;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		const auto runner = RaceSegmentRunner(car);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {67.2495, -83.2076};
			constexpr GeographicalCoordinate end_coordinate = {-59.7305, -75.1597};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 160.197;
			constexpr double weather_station = 2.04314;
			constexpr double distance = 56.333;
			constexpr double heading = 6.03751;
			constexpr double elevation = -373.33;
			constexpr double grade = 0.320263;
			constexpr double road_incline_angle = 0.609077;
			constexpr double sine_road_incline_angle = 0.572111;
			constexpr double gravity = 9.79443;
			constexpr double gravity_times_sine_road_incline_angle = 5.6035;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 24.618;
			constexpr double wind_direction = 2.30267;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 201.247;
			constexpr double air_temp = -45.9829;
			constexpr double pressure = 983.309;
			constexpr double air_density = 1.19159;
			constexpr double reciprocal_speed_of_sound = 0.00300826;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double state_of_charge = 0.0137528;
			constexpr double speed = 12.2634;

			const auto result = runner.calculate_power_net(route_segment, weather_data, state_of_charge, speed);
			constexpr double expected = -35743.9;
			REQUIRE(result.has_value());
			REQUIRE_THAT(result.value(), WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {56.3838, 8.60309};
			constexpr GeographicalCoordinate end_coordinate = {52.4863, -83.526};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 190.633;
			constexpr double weather_station = 9.6873;
			constexpr double distance = 64.8835;
			constexpr double heading = 5.7586;
			constexpr double elevation = -434.395;
			constexpr double grade = 0.952612;
			constexpr double road_incline_angle = -0.709578;
			constexpr double sine_road_incline_angle = -0.651514;
			constexpr double gravity = 9.7918;
			constexpr double gravity_times_sine_road_incline_angle = -6.3795;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 2.35916;
			constexpr double wind_direction = 3.57257;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 744.961;
			constexpr double air_temp = -42.0827;
			constexpr double pressure = 976.184;
			constexpr double air_density = 1.10458;
			constexpr double reciprocal_speed_of_sound = 0.00306353;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double state_of_charge = 0.931782;
			constexpr double speed = 2.18451;

			const auto result = runner.calculate_power_net(route_segment, weather_data, state_of_charge, speed);
			constexpr double expected = 5949.55;
			REQUIRE(result.has_value());
			REQUIRE_THAT(result.value(), WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {-66.0459, -154.471};
			constexpr GeographicalCoordinate end_coordinate = {76.3392, -63.6314};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 135.839;
			constexpr double weather_station = 8.073;
			constexpr double distance = 92.6931;
			constexpr double heading = 6.15746;
			constexpr double elevation = 204.683;
			constexpr double grade = -0.975845;
			constexpr double road_incline_angle = -0.0990739;
			constexpr double sine_road_incline_angle = -0.0989119;
			constexpr double gravity = 9.81351;
			constexpr double gravity_times_sine_road_incline_angle = -0.970672;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 5.53173;
			constexpr double wind_direction = 5.13292;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 158.633;
			constexpr double air_temp = -9.47893;
			constexpr double pressure = 1088.16;
			constexpr double air_density = 1.03752;
			constexpr double reciprocal_speed_of_sound = 0.00298774;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double state_of_charge = 0.402508;
			constexpr double speed = 22.3691;

			const auto result = runner.calculate_power_net(route_segment, weather_data, state_of_charge, speed);
			constexpr double expected = 6268.98;
			REQUIRE(result.has_value());
			REQUIRE_THAT(result.value(), WithinRel(expected, EPSILON));
		}
	}
	SECTION("Random Test 9") {
		constexpr double drag_coefficient = 0.00775139;
		constexpr double frontal_area = 8.41014;
		constexpr double array_area = 2.72045;
		constexpr double array_efficiency = 25.2267;
		constexpr double energy_capacity = 6980.89;
		constexpr double min_voltage = 123.902;
		constexpr double max_voltage = 153.87;
		constexpr double resistance = 0.072864;
		constexpr double hysteresis_loss = 3.21383;
		constexpr double eddy_current_loss_coefficient = 0.03918;
		constexpr double alpha = -8.23468;
		constexpr double beta = 1.53144;
		constexpr double a = 8.73472;
		constexpr double b = 7.66391e-07;
		constexpr double c = 0.711462;
		constexpr double pressure_at_stc = 120.806;
		constexpr double mass = 135.16;
		constexpr double wheel_radius = 0.155177;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		const auto runner = RaceSegmentRunner(car);
		{ // Input Set 0
			constexpr GeographicalCoordinate start_coordinate = {-52.214, 78.5165};
			constexpr GeographicalCoordinate end_coordinate = {-81.0342, -80.5995};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 162.866;
			constexpr double weather_station = 6.80159;
			constexpr double distance = 73.6924;
			constexpr double heading = 3.64171;
			constexpr double elevation = 450.762;
			constexpr double grade = 0.472894;
			constexpr double road_incline_angle = 1.06772;
			constexpr double sine_road_incline_angle = 0.876102;
			constexpr double gravity = 9.81425;
			constexpr double gravity_times_sine_road_incline_angle = 8.59828;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 16.3999;
			constexpr double wind_direction = 5.58903;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 977.094;
			constexpr double air_temp = 48.2011;
			constexpr double pressure = 901.313;
			constexpr double air_density = 1.26629;
			constexpr double reciprocal_speed_of_sound = 0.00295023;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double state_of_charge = 0.580076;
			constexpr double speed = 19.5464;

			const auto result = runner.calculate_power_net(route_segment, weather_data, state_of_charge, speed);
			constexpr double expected = -23756.5;
			REQUIRE(result.has_value());
			REQUIRE_THAT(result.value(), WithinRel(expected, EPSILON));
		}
		{ // Input Set 1
			constexpr GeographicalCoordinate start_coordinate = {-72.2768, 106.597};
			constexpr GeographicalCoordinate end_coordinate = {53.1162, 146.096};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 84.3084;
			constexpr double weather_station = 5.41786;
			constexpr double distance = 44.1338;
			constexpr double heading = 0.900947;
			constexpr double elevation = 443.627;
			constexpr double grade = -0.73556;
			constexpr double road_incline_angle = 1.4684;
			constexpr double sine_road_incline_angle = 0.994762;
			constexpr double gravity = 9.79974;
			constexpr double gravity_times_sine_road_incline_angle = 9.74841;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 10.697;
			constexpr double wind_direction = 2.23954;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 608.395;
			constexpr double air_temp = -10.8936;
			constexpr double pressure = 963.638;
			constexpr double air_density = 1.10742;
			constexpr double reciprocal_speed_of_sound = 0.00296283;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double state_of_charge = 0.546046;
			constexpr double speed = 15.26;

			const auto result = runner.calculate_power_net(route_segment, weather_data, state_of_charge, speed);
			constexpr double expected = -21148.9;
			REQUIRE(result.has_value());
			REQUIRE_THAT(result.value(), WithinRel(expected, EPSILON));
		}
		{ // Input Set 2
			constexpr GeographicalCoordinate start_coordinate = {11.8066, 162.276};
			constexpr GeographicalCoordinate end_coordinate = {87.6016, -138.646};
			constexpr SegmentEndCondition end_condition = SegmentEndCondition::END_OF_RACE;
			constexpr SegmentType type = SegmentType::RACE;
			constexpr double speed_limit = 121.75;
			constexpr double weather_station = 2.74769;
			constexpr double distance = 7.32372;
			constexpr double heading = 0.608135;
			constexpr double elevation = 181.198;
			constexpr double grade = 0.831763;
			constexpr double road_incline_angle = 0.0204063;
			constexpr double sine_road_incline_angle = 0.0204049;
			constexpr double gravity = 9.7947;
			constexpr double gravity_times_sine_road_incline_angle = 0.199859;
			const RouteSegment route_segment{
						.coordinate_start = start_coordinate,
						.coordinate_end = end_coordinate,
						.end_condition = end_condition,
						.type = type,
						.speed_limit = speed_limit,
						.weather_station = weather_station,
						.distance = distance,
						.heading = heading,
						.elevation = elevation,
						.grade = grade,
						.road_incline_angle = road_incline_angle,
						.sine_road_incline_angle = sine_road_incline_angle,
						.gravity = gravity,
						.gravity_times_sine_road_incline_angle = gravity_times_sine_road_incline_angle,
			};
			constexpr double wind_speed = 34.5983;
			constexpr double wind_direction = 3.20855;
			const auto wind = VelocityVector::from_polar_components(wind_speed, wind_direction);
			constexpr double irradiance = 449.79;
			constexpr double air_temp = -26.3568;
			constexpr double pressure = 1000.05;
			constexpr double air_density = 1.1028;
			constexpr double reciprocal_speed_of_sound = 0.00290958;
			const WeatherDataPoint weather_data{
						.wind = wind,
						.irradiance = irradiance,
						.air_temp = air_temp,
						.pressure = pressure,
						.air_density = air_density,
						.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
			};
			constexpr double state_of_charge = 0.470424;
			constexpr double speed = 1.01369;

			const auto result = runner.calculate_power_net(route_segment, weather_data, state_of_charge, speed);
			constexpr double expected = 247.704;
			REQUIRE(result.has_value());
			REQUIRE_THAT(result.value(), WithinRel(expected, EPSILON));
		}
	}
}
