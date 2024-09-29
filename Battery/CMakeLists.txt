add_library(battery STATIC)

target_sources(
	battery
	PUBLIC
		Battery.h
		BatteryState.h
	PRIVATE
		Battery.cpp
		BatteryState.cpp
)

add_executable(battery_tests BatteryTests.cpp)
target_link_libraries(
	battery_tests
	PRIVATE
		battery
		Catch2::Catch2WithMain
)

catch_discover_tests(battery_tests)
