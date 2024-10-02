#include "TimeTools.h"

namespace {
	// helper function for parse_time
	date::sys_time<std::chrono::milliseconds> parse(const std::string s) {
		std::istringstream ss(s);
		std::istream& is(ss);
		std::string save;
		is >> save;
		std::istringstream in{save};
		date::sys_time<std::chrono::milliseconds> tp;
		in >> date::parse("%FT%TZ", tp);
		if (in.fail()) {
			in.clear();
			in.exceptions(std::ios::failbit);
			in.str(save);
			in >> date::parse("%FT%T%Ez", tp);
		}
		return tp;
	}

	// helper function for format_time_for_file
	std::string to_format(const int number) {
		std::stringstream ss;
		ss << std::setw(2) << std::setfill('0') << number;
		return ss.str();
	}
}  // namespace

int parse_time(const std::string s) {
	auto time = parse(s);
	auto duration = time.time_since_epoch() / std::chrono::milliseconds(1);

	// convert millis (what time_since_epoch() returns) to seconds
	duration /= 1000;
	int64_t seconds = duration;

	return seconds;
}

// overloaded function
SplitTime split_time(double time) {
	return split_time(time_t(time));
}

// returns the GMT split_time
SplitTime split_time(time_t t) {
	SplitTime ret;
	// get the year, month, day, hour, minute, and second

	tm ltm;              // Actual storage for struct tm
	gmtime_r(&t, &ltm);  // Pointer to a time_t, pointer to a struct tm
	// tm_year shows years after 1900
	ret.year = ltm.tm_year + 1900;
	// month is given in the range of 0-11 that represent the number of months since January
	ret.month = ltm.tm_mon + 1;
	ret.day = ltm.tm_mday;
	ret.hour = ltm.tm_hour;
	ret.minute = ltm.tm_min;
	ret.second = ltm.tm_sec;

	return ret;
}

std::string format_time_for_file(SplitTime s) {
	// Format: YYYY-MM-DD_HH.MM.SS
	std::stringstream formatted_time;
	formatted_time << std::to_string(s.year) << "-" << to_format(s.month) << "-" << to_format(s.day) << "_"
				   << to_format(s.hour) << "." << to_format(s.minute) << "." << to_format(s.second);
	return formatted_time.str();
}