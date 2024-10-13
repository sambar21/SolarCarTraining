add_library(racerunner STATIC
    RaceRunner.cpp
    RaceRunner.h
)

target_link_libraries(
    racerunner
    PUBLIC
        race_segment_runner
        solarcar
        weather
        route
        weather_stations
)

add_executable(racerunner_tests RaceRunnerTests.cpp)
target_link_libraries(
	racerunner_tests
	PRIVATE
		racerunner
		raceschedule
		solarcar
		weather
		route
		weather_stations
		root_tool
		Catch2::Catch2WithMain
)

catch_discover_tests(racerunner_tests)
