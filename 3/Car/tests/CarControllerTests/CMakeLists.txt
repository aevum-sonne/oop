cmake_minimum_required(VERSION 3.15)
project(Car)

set(CMAKE_CXX_STANDARD 17)

add_executable(RemoteControlTests
        CarControllerTests.cpp CarControllerTests.h
        ../../src/CarController/CarController.cpp
        ../../src/Car/Car.cpp)