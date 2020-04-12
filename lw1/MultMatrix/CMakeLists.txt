cmake_minimum_required(VERSION 3.15)
project(MultMatrix)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
include_directories(Matrix3x3)
include_directories(Multiplier)

add_executable(MultMatrix
        main.cpp
        Matrix3x3/Matrix3x3.cpp
        Matrix3x3/Matrix3x3.h
        Multiplier/Multiplier.cpp
        Multiplier/Multiplier.h
        )
