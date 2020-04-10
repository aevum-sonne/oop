cmake_minimum_required(VERSION 3.15)
project(HTMLDecode)

set(CMAKE_CXX_STANDARD 17)

add_executable(HTMLDecode
        src/DecodeUtils/DecodeUtils.cpp
        src/DecodeUtils/DecodeUtils.h tests/Tests.cpp
        tests/Tests.h src/Args/Args.cpp src/Args/Args.h)