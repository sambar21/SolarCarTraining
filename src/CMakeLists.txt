add_subdirectory(ConfigFile)
add_subdirectory(DataClasses)
add_subdirectory(RaceConfig)
add_subdirectory(SolarCar)
add_subdirectory(Tools)

add_library(tools INTERFACE)
target_link_libraries(
	tools
	INTERFACE
		config_file
		dataclasses
		external_tools
		internal_tools
)

target_include_directories(
	tools
	INTERFACE
		${PROJECT_SOURCE_DIR}/src
		${PROJECT_SOURCE_DIR}/external
)

add_library(simulator_dependencies INTERFACE)
target_link_libraries(
	simulator_dependencies
	INTERFACE
		solarcar
		raceconfig
)

add_executable(minisim minisim.cpp)
target_link_libraries(
	minisim
	PRIVATE
		tools
		simulator_dependencies
)

# Create a Symbolic Link to the Simulator executable
add_custom_target(
	MinisimLink
	ALL
	COMMAND
		${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_BINARY_DIR}/minisim
		${CMAKE_BINARY_DIR}/minisim
	COMMAND
		${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_BINARY_DIR}/minisim
		${CMAKE_BINARY_DIR}/minisim.exe
	DEPENDS
		minisim
	COMMENT "Creating symbolic link to minisim executable"
	VERBATIM
)
