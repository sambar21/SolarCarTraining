add_library(race_segment_runner STATIC)

target_sources(
	race_segment_runner
	PUBLIC
		RaceSegmentRunner.h
	PRIVATE
		RaceSegmentRunner.cpp
)

# TODO Finish This
target_link_libraries(race_segment_runner 
    PUBLIC 
        battery  
        aerobody
		tire 
		array
		motor
)

add_executable(race_segment_runner_tests RaceSegmentRunnerTests.cpp)
target_link_libraries(
	race_segment_runner_tests
	PRIVATE
		race_segment_runner
		Catch2::Catch2WithMain
)

catch_discover_tests(race_segment_runner_tests)
