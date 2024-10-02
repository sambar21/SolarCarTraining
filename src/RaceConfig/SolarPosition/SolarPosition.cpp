#include "SolarPosition.h"

#include <stdexcept>

#include "DataClasses/GeographicalCoordinate.h"
#include "Tools/Conversions.h"
#include "Tools/TimeTools.h"
#include "solpos/solpos.h"

SolarPosition::SolarPositionData SolarPosition::solpos::calculate(const SolarPositionConfig& config) {
	const double latitude = config.coordinate.latitude;
	const double longitude = config.coordinate.longitude;
	const SplitTime time_data = split_time(config.timestamp);

	posdata output_data = {};

	S_init(&output_data);

	// We want the Zenith (S_REFRAC), Azimuth (S_SOLAZM), and want to use month / day instead of day of year (~S_DOY)
	output_data.function = (S_REFRAC & ~S_DOY) | S_SOLAZM;  // NOLINT

	// Set the time data
	output_data.year = time_data.year;
	output_data.month = time_data.month;
	output_data.day = time_data.day;
	output_data.hour = time_data.hour;
	output_data.minute = time_data.minute;
	output_data.second = time_data.second;

	// Set the location data
	output_data.latitude = static_cast<float>(latitude);
	output_data.longitude = static_cast<float>(longitude);

	// Sets temperature and pressure
	output_data.temp = static_cast<float>(config.temperature);
	output_data.press = static_cast<float>(config.pressure);

	// Sets the timezone
	output_data.timezone = internal::TIMEZONE_OFFSET;

	// Calculate
	const long result = S_solpos(&output_data);
	S_decode(result, &output_data);

	return {
		deg_to_rad(static_cast<double>(output_data.azim)),
		deg_to_rad(static_cast<double>(output_data.zenref)),
	};
}
