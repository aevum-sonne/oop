cmake_minimum_required(VERSION 3.15)
project(Car)

set(CMAKE_CXX_STANDARD 17)

add_executable(Main
        Main.cpp
        ../src/Car/Car.cpp
        CarController/CarController.cpp CarController/CarController.h Car/Gear.h Car/Direction.h)