cmake_minimum_required(VERSION 3.15)
project(Car)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory (src)
add_subdirectory (tests/CarTests)
add_subdirectory (tests/CarControllerTests)

enable_testing ()