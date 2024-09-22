# Almost all CMake files should start with this
# You should always specify a range with the newest
# and oldest tested versions of CMake. This will ensure
# you pick up the best policies.
cmake_minimum_required(VERSION 3.20...3.29)

# This is your project statement. You should always list languages;
# Listing the version is nice here since it sets lots of useful variables
project(minisim VERSION 0.1 LANGUAGES CXX)

# If you set any CMAKE_ variables, that can go here.
# (But usually don't do this, except maybe for C++ standard)
# We Use C++20 Whenever Possible
set(CMAKE_CXX_STANDARD 20)
# honestly idek
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# We don't want compiler-specific extensions be be accessible
set(CMAKE_CXX_EXTENSIONS OFF)
# This allows you to use clangd with CMake
set(CMAKE_EXPORT_COMPILE_COMMANDS YES)

# Package Manager
include(cmake/CPM.cmake)

# Find packages go here.
include(cmake/catch2.cmake) # Testing
include(CTest)
include(Catch)

add_subdirectory(Aerobody)
add_subdirectory(Array)
add_subdirectory(Tire)

enable_testing()
add_executable(minisim minisim.cpp)
