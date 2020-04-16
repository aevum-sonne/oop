cmake_minimum_required(VERSION 3.15)
project(MultVectorOnMin)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
include_directories(src/VectorUtils)
include_directories(src/Args)
include_directories(tests)

add_executable(MultVectorOnMin
        src/VectorUtils/VectorUtils.cpp
        src/Args/Args.cpp
        tests/Tests.cpp
        )
