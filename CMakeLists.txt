cmake_minimum_required(VERSION 3.10)

# Project name
project(AStarLib)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add library source files
add_library(AStarLib src/AStar.cpp)

# Specify include directory for the library
target_include_directories(AStarLib PUBLIC ${PROJECT_SOURCE_DIR}/include)

# Add the test executable
add_executable(AStarTest test/test_main.cpp)

# Link the test executable with the library
target_link_libraries(AStarTest AStarLib)
