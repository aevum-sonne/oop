cmake_minimum_required(VERSION 3.15)
project(Shapes)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
add_subdirectory(tests/ShapesControllerTests)
add_subdirectory(tests/ShapesTests)

enable_testing()