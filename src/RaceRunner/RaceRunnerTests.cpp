#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <cmath>
#include <numbers>
#include <string>

#include "ConfigFile/ConfigFile.h"
#include "RaceConfig/RaceSchedule/RaceSchedule.h"
#include "RaceConfig/Route/Route.h"
#include "RaceConfig/Weather/Weather.h"
#include "RaceConfig/WeatherStations/WeatherStations.h"
#include "RaceRunner.h"
#include "Tools/RootDirectory.h"

using Catch::Matchers::WithinAbs;
using Catch::Matchers::WithinRel;

constexpr double EPSILON = 0.001;  // %
constexpr double RT_DELTA = 500;   // seconds

namespace {
	const std::string root_directory = get_root_directory();
	const std::string route_file = root_directory + "/data/Route/route.csv";
	const std::string weather_file = root_directory + "/data/Weather/Australia/August/2007.csv";
	const std::string schedule_file = root_directory + "/data/Schedule/August/Schedule2007.toml";
	const std::string weather_stations_file = root_directory + "/data/Stations/australia_stations.csv";
}  // namespace

TEST_CASE("RaceSegmentRunner: calculate_static_charging_gain", "[RaceSegmentRunner]") {
	const WeatherStations weather_stations(weather_stations_file);
	const RaceSchedule schedule((ConfigFile::from_path(schedule_file).value()));
	const Route route(route_file, weather_stations);
	const Weather weather(weather_file, weather_stations);
	SECTION("Random Test 0") {
		constexpr double drag_coefficient = 0.00932387;
		constexpr double frontal_area = 7.56004;
		constexpr double array_area = 9.72033;
		constexpr double array_efficiency = 27.021;
		constexpr double energy_capacity = 3593.31;
		constexpr double min_voltage = 117.525;
		constexpr double max_voltage = 133.326;
		constexpr double resistance = 0.290695;
		constexpr double hysteresis_loss = 2.73242;
		constexpr double eddy_current_loss_coefficient = 0.00267144;
		constexpr double alpha = -5.04613;
		constexpr double beta = -8.61768;
		constexpr double a = -4.40408;
		constexpr double b = 9.908e-06;
		constexpr double c = 0.430338;
		constexpr double pressure_at_stc = 135.383;
		constexpr double mass = 173.125;
		constexpr double wheel_radius = 0.23653;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		constexpr double start_time = 1187940600.00000;
		constexpr double end_time = 1187955000.00000;
		constexpr double expected = 375.89;
		const double result = RaceRunner::calculate_static_charging_gain(
			car, weather, route.get_segment(12).weather_station, start_time, end_time);
		REQUIRE_THAT(result, WithinRel(expected, EPSILON));
	}
	SECTION("Random Test 1") {
		constexpr double drag_coefficient = 0.0075296;
		constexpr double frontal_area = 4.1176;
		constexpr double array_area = 1.5178;
		constexpr double array_efficiency = 28.914;
		constexpr double energy_capacity = 6796.1;
		constexpr double min_voltage = 85.243;
		constexpr double max_voltage = 135.9;
		constexpr double resistance = 0.62945;
		constexpr double hysteresis_loss = 2.8723;
		constexpr double eddy_current_loss_coefficient = 0.005802;
		constexpr double alpha = 2.3499;
		constexpr double beta = -8.9002;
		constexpr double a = -2.5204;
		constexpr double b = -1.5688e-06;
		constexpr double c = -0.26485;
		constexpr double pressure_at_stc = 140.73;
		constexpr double mass = 261.17;
		constexpr double wheel_radius = 0.36636;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		constexpr double start_time = 1187940600.00000;
		constexpr double end_time = 1187955000.00000;
		constexpr double expected = 62.806;
		const double result = RaceRunner::calculate_static_charging_gain(
			car, weather, route.get_segment(12).weather_station, start_time, end_time);
		REQUIRE_THAT(result, WithinRel(expected, EPSILON));
	}
	SECTION("Random Test 2") {
		constexpr double drag_coefficient = 0.003803;
		constexpr double frontal_area = 4.6303;
		constexpr double array_area = 1.7037;
		constexpr double array_efficiency = 25.465;
		constexpr double energy_capacity = 3153.9;
		constexpr double min_voltage = 83.524;
		constexpr double max_voltage = 124.11;
		constexpr double resistance = 0.36135;
		constexpr double hysteresis_loss = 1.6239;
		constexpr double eddy_current_loss_coefficient = 0.043002;
		constexpr double alpha = 4.9673;
		constexpr double beta = 5.9797;
		constexpr double a = 9.5613;
		constexpr double b = 5.4223e-06;
		constexpr double c = 0.96365;
		constexpr double pressure_at_stc = 131.33;
		constexpr double mass = 204.93;
		constexpr double wheel_radius = 0.15428;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		constexpr double start_time = 1187940600.00000;
		constexpr double end_time = 1187955000.00000;
		constexpr double expected = 62.086;
		const double result = RaceRunner::calculate_static_charging_gain(
			car, weather, route.get_segment(12).weather_station, start_time, end_time);
		REQUIRE_THAT(result, WithinRel(expected, EPSILON));
	}
	SECTION("Random Test 3") {
		constexpr double drag_coefficient = 0.0033219;
		constexpr double frontal_area = 1.9044;
		constexpr double array_area = 7.0401;
		constexpr double array_efficiency = 21.64;
		constexpr double energy_capacity = 4763.4;
		constexpr double min_voltage = 95.654;
		constexpr double max_voltage = 125.62;
		constexpr double resistance = 0.92516;
		constexpr double hysteresis_loss = 2.7105;
		constexpr double eddy_current_loss_coefficient = 0.0027431;
		constexpr double alpha = 4.6751;
		constexpr double beta = -9.1222;
		constexpr double a = 2.4448;
		constexpr double b = -8.0057e-06;
		constexpr double c = -0.24451;
		constexpr double pressure_at_stc = 109.96;
		constexpr double mass = 182.5;
		constexpr double wheel_radius = 0.49588;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		constexpr double start_time = 1187940600.00000;
		constexpr double end_time = 1187955000.00000;
		constexpr double expected = 218.03;
		const double result = RaceRunner::calculate_static_charging_gain(
			car, weather, route.get_segment(12).weather_station, start_time, end_time);
		REQUIRE_THAT(result, WithinRel(expected, EPSILON));
	}
	SECTION("Random Test 4") {
		constexpr double drag_coefficient = 0.00034941;
		constexpr double frontal_area = 7.5536;
		constexpr double array_area = 2.9238;
		constexpr double array_efficiency = 26.958;
		constexpr double energy_capacity = 2559.7;
		constexpr double min_voltage = 106.53;
		constexpr double max_voltage = 116.92;
		constexpr double resistance = 0.46084;
		constexpr double hysteresis_loss = 1.6749;
		constexpr double eddy_current_loss_coefficient = 0.0040324;
		constexpr double alpha = 2.9553;
		constexpr double beta = 2.7408;
		constexpr double a = -1.6194;
		constexpr double b = 2.8555e-06;
		constexpr double c = -0.62353;
		constexpr double pressure_at_stc = 150.8;
		constexpr double mass = 274.5;
		constexpr double wheel_radius = 0.15428;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		constexpr double start_time = 1187940600.00000;
		constexpr double end_time = 1187955000.00000;
		constexpr double expected = 112.8;
		const double result = RaceRunner::calculate_static_charging_gain(
			car, weather, route.get_segment(12).weather_station, start_time, end_time);
		REQUIRE_THAT(result, WithinRel(expected, EPSILON));
	}
	SECTION("Random Test 5") {
		constexpr double drag_coefficient = 0.0020106;
		constexpr double frontal_area = 4.8222;
		constexpr double array_area = 3.7177;
		constexpr double array_efficiency = 26.964;
		constexpr double energy_capacity = 6212.2;
		constexpr double min_voltage = 71.359;
		constexpr double max_voltage = 132.13;
		constexpr double resistance = 0.17264;
		constexpr double hysteresis_loss = 2.7711;
		constexpr double eddy_current_loss_coefficient = 0.0090637;
		constexpr double alpha = -9.2022;
		constexpr double beta = -7.4399;
		constexpr double a = -7.8173;
		constexpr double b = -8.4451e-06;
		constexpr double c = 0.072332;
		constexpr double pressure_at_stc = 100.22;
		constexpr double mass = 214.13;
		constexpr double wheel_radius = 0.4666;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		constexpr double start_time = 1187940600.00000;
		constexpr double end_time = 1187955000.00000;
		constexpr double expected = 143.46;
		const double result = RaceRunner::calculate_static_charging_gain(
			car, weather, route.get_segment(12).weather_station, start_time, end_time);
		REQUIRE_THAT(result, WithinRel(expected, EPSILON));
	}
	SECTION("Random Test 6") {
		constexpr double drag_coefficient = 0.00053207;
		constexpr double frontal_area = 2.2597;
		constexpr double array_area = 7.6983;
		constexpr double array_efficiency = 29.835;
		constexpr double energy_capacity = 5626.9;
		constexpr double min_voltage = 103.86;
		constexpr double max_voltage = 144.85;
		constexpr double resistance = 0.84442;
		constexpr double hysteresis_loss = 1.785;
		constexpr double eddy_current_loss_coefficient = 0.047004;
		constexpr double alpha = 8.843;
		constexpr double beta = -4.1558;
		constexpr double a = 5.3359;
		constexpr double b = -5.7155e-06;
		constexpr double c = 0.42846;
		constexpr double pressure_at_stc = 123.95;
		constexpr double mass = 234.73;
		constexpr double wheel_radius = 0.49125;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		constexpr double start_time = 1187940600.00000;
		constexpr double end_time = 1187955000.00000;
		constexpr double expected = 328.7;
		const double result = RaceRunner::calculate_static_charging_gain(
			car, weather, route.get_segment(12).weather_station, start_time, end_time);
		REQUIRE_THAT(result, WithinRel(expected, EPSILON));
	}
	SECTION("Random Test 7") {
		constexpr double drag_coefficient = 0.0062226;
		constexpr double frontal_area = 2.5459;
		constexpr double array_area = 2.1532;
		constexpr double array_efficiency = 28.105;
		constexpr double energy_capacity = 6862.1;
		constexpr double min_voltage = 94.868;
		constexpr double max_voltage = 103.86;
		constexpr double resistance = 0.34491;
		constexpr double hysteresis_loss = 4.8361;
		constexpr double eddy_current_loss_coefficient = 0.045987;
		constexpr double alpha = 0.89664;
		constexpr double beta = -6.6737;
		constexpr double a = 4.3843;
		constexpr double b = -6.8684e-06;
		constexpr double c = 0.46365;
		constexpr double pressure_at_stc = 117.27;
		constexpr double mass = 200.85;
		constexpr double wheel_radius = 0.25526;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		constexpr double start_time = 1187940600.00000;
		constexpr double end_time = 1187955000.00000;
		constexpr double expected = 86.605;
		const double result = RaceRunner::calculate_static_charging_gain(
			car, weather, route.get_segment(12).weather_station, start_time, end_time);
		REQUIRE_THAT(result, WithinRel(expected, EPSILON));
	}
	SECTION("Random Test 8") {
		constexpr double drag_coefficient = 0.0095144;
		constexpr double frontal_area = 5.7972;
		constexpr double array_area = 3.8087;
		constexpr double array_efficiency = 21.174;
		constexpr double energy_capacity = 3114.9;
		constexpr double min_voltage = 120.52;
		constexpr double max_voltage = 135.32;
		constexpr double resistance = 0.57761;
		constexpr double hysteresis_loss = 1.6175;
		constexpr double eddy_current_loss_coefficient = 0.036072;
		constexpr double alpha = 7.3176;
		constexpr double beta = -7.5555;
		constexpr double a = -4.2153;
		constexpr double b = 2.7979e-06;
		constexpr double c = 0.26837;
		constexpr double pressure_at_stc = 158.35;
		constexpr double mass = 243.56;
		constexpr double wheel_radius = 0.2616;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		constexpr double start_time = 1187940600.00000;
		constexpr double end_time = 1187955000.00000;
		constexpr double expected = 115.41;
		const double result = RaceRunner::calculate_static_charging_gain(
			car, weather, route.get_segment(12).weather_station, start_time, end_time);
		REQUIRE_THAT(result, WithinRel(expected, EPSILON));
	}
	SECTION("Random Test 9") {
		constexpr double drag_coefficient = 0.0060233;
		constexpr double frontal_area = 9.565;
		constexpr double array_area = 1.8751;
		constexpr double array_efficiency = 29.869;
		constexpr double energy_capacity = 4104;
		constexpr double min_voltage = 147.03;
		constexpr double max_voltage = 147.65;
		constexpr double resistance = 0.9132;
		constexpr double hysteresis_loss = 4.9263;
		constexpr double eddy_current_loss_coefficient = 0.022846;
		constexpr double alpha = 5.6082;
		constexpr double beta = -3.1654;
		constexpr double a = -5.3657;
		constexpr double b = 1.9458e-06;
		constexpr double c = 0.40604;
		constexpr double pressure_at_stc = 112.28;
		constexpr double mass = 263.34;
		constexpr double wheel_radius = 0.46706;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		constexpr double start_time = 1187940600.00000;
		constexpr double end_time = 1187955000.00000;
		constexpr double expected = 80.151;
		const double result = RaceRunner::calculate_static_charging_gain(
			car, weather, route.get_segment(12).weather_station, start_time, end_time);
		REQUIRE_THAT(result, WithinRel(expected, EPSILON));
	}
}
TEST_CASE("RaceSegmentRunner: calculate_racetime", "[RaceSegmentRunner]") {
	const WeatherStations weather_stations(weather_stations_file);
	const RaceSchedule schedule((ConfigFile::from_path(schedule_file).value()));
	const Route route(route_file, weather_stations);
	const Weather weather(weather_file, weather_stations);
	SECTION("Random Test 0") {
		constexpr double drag_coefficient = 0.0022513;
		constexpr double frontal_area = 2.3893;
		constexpr double array_area = 6.4406;
		constexpr double array_efficiency = 27.408;
		constexpr double energy_capacity = 6185.8;
		constexpr double min_voltage = 122.02;
		constexpr double max_voltage = 132.43;
		constexpr double resistance = 0.074918;
		constexpr double hysteresis_loss = 4.3515;
		constexpr double eddy_current_loss_coefficient = 0.030323;
		constexpr double alpha = -6.5802;
		constexpr double beta = -5.3657;
		constexpr double a = -6.822;
		constexpr double b = -9.936e-06;
		constexpr double c = 0.81013;
		constexpr double pressure_at_stc = 129.65;
		constexpr double mass = 275.27;
		constexpr double wheel_radius = 0.32892;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		constexpr double speed = 19.053;
		const double expected = 175041.86133;
		const auto result = RaceRunner::calculate_racetime(car, route, weather, schedule, speed);
		REQUIRE_THAT(result.value(), WithinAbs(expected, RT_DELTA));
	}
	SECTION("Random Test 1") {
		constexpr double drag_coefficient = 0.0095331;
		constexpr double frontal_area = 5.702;
		constexpr double array_area = 3.6878;
		constexpr double array_efficiency = 23.202;
		constexpr double energy_capacity = 3047.7;
		constexpr double min_voltage = 139.79;
		constexpr double max_voltage = 145.96;
		constexpr double resistance = 0.29043;
		constexpr double hysteresis_loss = 2.1865;
		constexpr double eddy_current_loss_coefficient = 0.045093;
		constexpr double alpha = -2.2844;
		constexpr double beta = 8.874;
		constexpr double a = 8.0591;
		constexpr double b = -4.0601e-06;
		constexpr double c = -0.4155;
		constexpr double pressure_at_stc = 151.29;
		constexpr double mass = 281.6;
		constexpr double wheel_radius = 0.2834;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		constexpr double speed = 19.488;
		const auto result = RaceRunner::calculate_racetime(car, route, weather, schedule, speed);
		REQUIRE_FALSE(result.has_value());
	}
	SECTION("Random Test 2") {
		constexpr double drag_coefficient = 0.0021056;
		constexpr double frontal_area = 9.0935;
		constexpr double array_area = 3.4687;
		constexpr double array_efficiency = 28.459;
		constexpr double energy_capacity = 3284.9;
		constexpr double min_voltage = 92.232;
		constexpr double max_voltage = 116.55;
		constexpr double resistance = 0.84902;
		constexpr double hysteresis_loss = 2.3721;
		constexpr double eddy_current_loss_coefficient = 0.025697;
		constexpr double alpha = 0.47283;
		constexpr double beta = -2.1283;
		constexpr double a = 5.0865;
		constexpr double b = 5.5746e-06;
		constexpr double c = 0.37307;
		constexpr double pressure_at_stc = 155.93;
		constexpr double mass = 132;
		constexpr double wheel_radius = 0.3461;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		constexpr double speed = 19.299;
		const double expected = 173023.75004;
		const auto result = RaceRunner::calculate_racetime(car, route, weather, schedule, speed);
		REQUIRE_THAT(result.value(), WithinAbs(expected, RT_DELTA));
	}
	SECTION("Random Test 3") {
		constexpr double drag_coefficient = 0.0092327;
		constexpr double frontal_area = 8.0011;
		constexpr double array_area = 6.3692;
		constexpr double array_efficiency = 23.497;
		constexpr double energy_capacity = 4732.1;
		constexpr double min_voltage = 72.054;
		constexpr double max_voltage = 163.61;
		constexpr double resistance = 0.11598;
		constexpr double hysteresis_loss = 2.9673;
		constexpr double eddy_current_loss_coefficient = 0.034726;
		constexpr double alpha = 5.9543;
		constexpr double beta = -5.5927;
		constexpr double a = -0.072507;
		constexpr double b = 1.4613e-06;
		constexpr double c = 0.77485;
		constexpr double pressure_at_stc = 148.95;
		constexpr double mass = 170.62;
		constexpr double wheel_radius = 0.3158;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		constexpr double speed = 10.12;
		const auto result = RaceRunner::calculate_racetime(car, route, weather, schedule, speed);
		REQUIRE_FALSE(result.has_value());
	}
	SECTION("Random Test 4") {
		constexpr double drag_coefficient = 0.0050837;
		constexpr double frontal_area = 1.7497;
		constexpr double array_area = 2.1945;
		constexpr double array_efficiency = 15.77;
		constexpr double energy_capacity = 3188.6;
		constexpr double min_voltage = 100.06;
		constexpr double max_voltage = 122.65;
		constexpr double resistance = 0.4577;
		constexpr double hysteresis_loss = 3.4825;
		constexpr double eddy_current_loss_coefficient = 0.048346;
		constexpr double alpha = -0.85611;
		constexpr double beta = -7.667;
		constexpr double a = 5.8159;
		constexpr double b = -7.2606e-06;
		constexpr double c = 0.019934;
		constexpr double pressure_at_stc = 168.22;
		constexpr double mass = 139.97;
		constexpr double wheel_radius = 0.10139;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		constexpr double speed = 15.214;
		const double expected = 215126.69965;
		const auto result = RaceRunner::calculate_racetime(car, route, weather, schedule, speed);
		REQUIRE_THAT(result.value(), WithinAbs(expected, RT_DELTA));
	}
	SECTION("Random Test 5") {
		constexpr double drag_coefficient = 0.0086246;
		constexpr double frontal_area = 3.9298;
		constexpr double array_area = 1.5193;
		constexpr double array_efficiency = 24.316;
		constexpr double energy_capacity = 7057.7;
		constexpr double min_voltage = 151.47;
		constexpr double max_voltage = 153.65;
		constexpr double resistance = 0.045367;
		constexpr double hysteresis_loss = 3.7455;
		constexpr double eddy_current_loss_coefficient = 0.039478;
		constexpr double alpha = -6.0668;
		constexpr double beta = 8.339;
		constexpr double a = 6.3206;
		constexpr double b = 9.9702e-06;
		constexpr double c = 0.52954;
		constexpr double pressure_at_stc = 189.43;
		constexpr double mass = 151.27;
		constexpr double wheel_radius = 0.46288;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		constexpr double speed = 12.59;
		const auto result = RaceRunner::calculate_racetime(car, route, weather, schedule, speed);
		REQUIRE_FALSE(result.has_value());
	}
	SECTION("Random Test 6") {
		constexpr double drag_coefficient = 0.0034429;
		constexpr double frontal_area = 5.1689;
		constexpr double array_area = 8.0002;
		constexpr double array_efficiency = 27.868;
		constexpr double energy_capacity = 5103.6;
		constexpr double min_voltage = 118.39;
		constexpr double max_voltage = 166.62;
		constexpr double resistance = 0.14844;
		constexpr double hysteresis_loss = 2.1799;
		constexpr double eddy_current_loss_coefficient = 0.019311;
		constexpr double alpha = -7.6921;
		constexpr double beta = -2.8735;
		constexpr double a = -5.6458;
		constexpr double b = -1.8894e-07;
		constexpr double c = 0.95123;
		constexpr double pressure_at_stc = 118.69;
		constexpr double mass = 265.04;
		constexpr double wheel_radius = 0.3016;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		constexpr double speed = 19.362;
		const double expected = 172514.29241;
		const auto result = RaceRunner::calculate_racetime(car, route, weather, schedule, speed);
		REQUIRE_THAT(result.value(), WithinAbs(expected, RT_DELTA));
	}
	SECTION("Random Test 7") {
		constexpr double drag_coefficient = 0.0075457;
		constexpr double frontal_area = 5.8706;
		constexpr double array_area = 1.0034;
		constexpr double array_efficiency = 23.768;
		constexpr double energy_capacity = 6248.1;
		constexpr double min_voltage = 83.621;
		constexpr double max_voltage = 127.38;
		constexpr double resistance = 0.30577;
		constexpr double hysteresis_loss = 3.8356;
		constexpr double eddy_current_loss_coefficient = 0.03249;
		constexpr double alpha = 7.9339;
		constexpr double beta = 8.0756;
		constexpr double a = -9.7284;
		constexpr double b = 6.9517e-06;
		constexpr double c = -0.66467;
		constexpr double pressure_at_stc = 137.8;
		constexpr double mass = 151.1;
		constexpr double wheel_radius = 0.34473;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		constexpr double speed = 10.995;
		const auto result = RaceRunner::calculate_racetime(car, route, weather, schedule, speed);
		REQUIRE_FALSE(result.has_value());
	}
	SECTION("Random Test 8") {
		constexpr double drag_coefficient = 0.0044685;
		constexpr double frontal_area = 3.5303;
		constexpr double array_area = 7.3371;
		constexpr double array_efficiency = 27.713;
		constexpr double energy_capacity = 7437.5;
		constexpr double min_voltage = 78.83;
		constexpr double max_voltage = 140.86;
		constexpr double resistance = 0.97458;
		constexpr double hysteresis_loss = 3.7425;
		constexpr double eddy_current_loss_coefficient = 0.044996;
		constexpr double alpha = -1.5011;
		constexpr double beta = -1.7554;
		constexpr double a = 6.0941;
		constexpr double b = -4.5582e-06;
		constexpr double c = -0.64689;
		constexpr double pressure_at_stc = 147.26;
		constexpr double mass = 158.66;
		constexpr double wheel_radius = 0.38662;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		constexpr double speed = 14.585;
		const double expected = 223702.97313;
		const auto result = RaceRunner::calculate_racetime(car, route, weather, schedule, speed);
		REQUIRE_THAT(result.value(), WithinAbs(expected, RT_DELTA));
	}
	SECTION("Random Test 9") {
		constexpr double drag_coefficient = 0.0040172;
		constexpr double frontal_area = 1.9695;
		constexpr double array_area = 9.6884;
		constexpr double array_efficiency = 26.985;
		constexpr double energy_capacity = 5860.7;
		constexpr double min_voltage = 114.49;
		constexpr double max_voltage = 124.87;
		constexpr double resistance = 0.26308;
		constexpr double hysteresis_loss = 4.2436;
		constexpr double eddy_current_loss_coefficient = 0.046834;
		constexpr double alpha = 6.3138;
		constexpr double beta = -6.0322;
		constexpr double a = -7.292;
		constexpr double b = -9.6917e-06;
		constexpr double c = 0.70307;
		constexpr double pressure_at_stc = 128.97;
		constexpr double mass = 187.93;
		constexpr double wheel_radius = 0.2585;
		const auto aerobody = Aerobody(drag_coefficient, frontal_area);
		const auto array = Array(array_area, array_efficiency);
		const auto battery = Battery(energy_capacity, resistance, min_voltage, max_voltage);
		const auto motor = Motor(hysteresis_loss, eddy_current_loss_coefficient);
		const auto tire = Tire(SaeJ2452Coefficients{alpha, beta, a, b, c}, pressure_at_stc);
		const SolarCar car(aerobody, array, battery, motor, tire, mass, wheel_radius);
		constexpr double speed = 10.522;
		const auto result = RaceRunner::calculate_racetime(car, route, weather, schedule, speed);
		REQUIRE_FALSE(result.has_value());
	}
}
