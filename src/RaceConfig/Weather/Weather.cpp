#include "Weather.h"

#include <exception>
#include <filesystem>
#include <fstream>
#include <set>
#include <span>
#include <string>
#include <vector>

#include "RaceConfig/RaceConfigConstants.h"
#include "Tools/TimeTools.h"
#include "alglib/ap.h"
#include "alglib/interpolation.h"
#include "csv/csv.h"

using namespace race_config::weather;

Weather::Weather(std::string_view weather_file, const WeatherStations& weather_stations)
	: Weather(std::array<const std::string, 1>{std::string(weather_file.data())}, weather_stations) {}

Weather::Weather(std::span<const std::string> weather_files, const WeatherStations& weather_stations)
	: num_weather_groups(weather_stations.size()) {
	for (const auto& file : weather_files) {
		std::string cache_location = file + ".cache";

		// check if the cache file exists
		if (std::filesystem::exists(cache_location)) {
			// if it does, load the cache file
			SplineAndStartTime spline_and_start_time;

			std::fstream cache_file(cache_location);
			alglib::spline2dunserialize(cache_file, spline_and_start_time.weather_spline);

			std::fstream start_time_file(file);
			// first line is just the header
			std::string line;
			std::getline(start_time_file, line);
			char junk;
			start_time_file >> spline_and_start_time.start_time >> junk >> spline_and_start_time.start_time;
			weather_splines.push_back(std::move(spline_and_start_time));
			continue;
		}

		// process for reading csv and building splines
		io::CSVReader<WEATHER_FILE_NUMBER_OF_COLUMNS> csv(file);
		csv.read_header(io::ignore_extra_column,
			CN_WEATHER_STATION.data(),     // 0
			CN_UNIX_PERIOD.data(),         // 1
			CN_DHI.data(),                 // 2
			CN_DNI.data(),                 // 3
			CN_GHI.data(),                 // 4
			CN_WIND_VELOCITY_NS.data(),    // 5
			CN_WIND_VELOCITY_EW.data(),    // 6
			CN_AIR_TEMPERATURE_2M.data(),  // 7
			CN_SURFACE_PRESSURE.data(),    // 8
			CN_AIR_DENSITY.data()          // 9
		);

		std::vector<double> weather_station_vec, time_vec, dhi_vec, dni_vec, ghi_vec, wind_vel_ns_vec, wind_vel_ew_vec,
			air_temp_vec, pressure_vec, air_density_vec;
		double weather_station, time, dhi, dni, ghi, wind_vel_ns, wind_vel_ew, air_temp, pressure, air_density;

		int number_of_rows = 0;
		while (csv.read_row(weather_station,  // 0
			time,                             // 1
			dhi,                              // 2
			dni,                              // 3
			ghi,                              // 4
			wind_vel_ns,                      // 5
			wind_vel_ew,                      // 6
			air_temp,                         // 7
			pressure,                         // 8
			air_density                       // 9
			)) {
			weather_station_vec.push_back(weather_station);
			time_vec.push_back(time);
			dhi_vec.push_back(dhi);
			dni_vec.push_back(dni);
			ghi_vec.push_back(ghi);
			wind_vel_ns_vec.push_back(wind_vel_ns);
			wind_vel_ew_vec.push_back(wind_vel_ew);
			air_temp_vec.push_back(air_temp);
			pressure_vec.push_back(pressure);
			air_density_vec.push_back(air_density);
			number_of_rows++;
		}

		// We define a vector-valued spline with two inputs (time and weather station) and 9 outputs (the weather data).
		// The abscissa and ordinate arrays are the coordinates of the grid points.
		// The abscissa array represents the time values.
		// The ordinate array represents the weather station values.

		const int abscissas_dim = static_cast<int>(weather_station_vec.size()) / num_weather_groups;
		const int spline_vector_dim = WEATHER_FILE_NUMBER_OF_COLUMNS - 2;

		const int number_of_values_per_weather_group = number_of_rows / num_weather_groups;

		alglib::real_1d_array abscissas_array;
		alglib::real_1d_array ordinates_array;
		alglib::real_1d_array function_values_array;
		abscissas_array.setlength(abscissas_dim);

		ordinates_array.setlength(num_weather_groups);
		function_values_array.setlength(abscissas_dim * num_weather_groups * spline_vector_dim);

		for (int i = 0; i < number_of_values_per_weather_group; ++i) {
			abscissas_array[i] = time_vec[i];
		}

		for (int i = 0; i < num_weather_groups; ++i) {
			ordinates_array[i] = weather_station_vec[i * number_of_values_per_weather_group];
		}

		for (int i = 0; i < abscissas_dim * num_weather_groups; ++i) {
			function_values_array[i * spline_vector_dim + CO_DHI] = dhi_vec[i];                       // 1
			function_values_array[i * spline_vector_dim + CO_DNI] = dni_vec[i];                       // 2
			function_values_array[i * spline_vector_dim + CO_GHI] = ghi_vec[i];                       // 3
			function_values_array[i * spline_vector_dim + CO_WIND_VELOCITY_NS] = wind_vel_ns_vec[i];  // 4
			function_values_array[i * spline_vector_dim + CO_WIND_VELOCITY_EW] = wind_vel_ew_vec[i];  // 5
			function_values_array[i * spline_vector_dim + CO_AIR_TEMPERATURE_2M] = air_temp_vec[i];   // 6
			function_values_array[i * spline_vector_dim + CO_SURFACE_PRESSURE] = pressure_vec[i];     // 7
			function_values_array[i * spline_vector_dim + CO_AIR_DENSITY] = air_density_vec[i];       // 8
		}

		SplineAndStartTime spline_and_start_time{
			.start_time = time_vec[0],
			.weather_spline = {},
		};

		try {
			alglib::spline2dbuildbilinearv(abscissas_array, abscissas_dim, ordinates_array, num_weather_groups,
				function_values_array, spline_vector_dim, spline_and_start_time.weather_spline);
		} catch (alglib::ap_error& error) {
			throw std::exception();
		}

		// save the spline to a cache file
		std::fstream cache_file(cache_location, std::ios::out);
		alglib::spline2dserialize(spline_and_start_time.weather_spline, cache_file);

		alglib::spline2dbuildbilinearv(abscissas_array, abscissas_dim, ordinates_array, num_weather_groups,
			function_values_array, spline_vector_dim, spline_and_start_time.weather_spline);

		weather_splines.push_back(std::move(spline_and_start_time));
	}

	std::sort(weather_splines.begin(), weather_splines.end(),
		[](const SplineAndStartTime& lhs, const SplineAndStartTime& rhs) { return lhs.start_time < rhs.start_time; });
}

WeatherDataPoint Weather::get_weather_at(double weather_station, double time) const {
	// get the last element of weather_splines such that the start time is less than or equal to the time
	auto weather_spline = std::upper_bound(weather_splines.begin(), weather_splines.end(), time,
		[](double time, const SplineAndStartTime& spline_and_start_time) {
			return time < spline_and_start_time.start_time;
		});

	if (weather_spline == weather_splines.begin()) {
		throw std::exception();
	}
	weather_spline = std::prev(weather_spline);

	const alglib::spline2dinterpolant& weather_spline_interpolant = weather_spline->weather_spline;

	alglib::real_1d_array weather_data;
	alglib::spline2dcalcv(weather_spline_interpolant, time, weather_station, weather_data);

	const double ghi = weather_data[CO_GHI];
	const double wind_ns = weather_data[CO_WIND_VELOCITY_NS];
	const double wind_ew = weather_data[CO_WIND_VELOCITY_EW];
	const double air_temp = weather_data[CO_AIR_TEMPERATURE_2M];
	const double pressure = weather_data[CO_SURFACE_PRESSURE];
	const double air_density = weather_data[CO_AIR_DENSITY];
	constexpr double reciprocal_speed_of_sound = 0.0029154519; // s / m


	return {
		.wind = VelocityVector::from_cartesian_components(wind_ns, wind_ew),
		.irradiance = ghi,
		.air_temp = air_temp,
		.pressure = pressure,
		.air_density = air_density,
		.reciprocal_speed_of_sound = reciprocal_speed_of_sound,
	};
}

WeatherDataPoint Weather::get_weather_during(double weather_station, double start_time, double end_time) const {
	const WeatherDataPoint start_data = get_weather_at(weather_station, start_time);
	const WeatherDataPoint end_data = get_weather_at(weather_station, end_time);
	return WeatherDataPoint::average(start_data, end_data);
}
