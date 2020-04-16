cmake_minimum_required(VERSION 3.15)
project(MiniDictionary)

set(CMAKE_CXX_STANDARD 17)

add_executable(Tests
        Tests.cpp
        ../src/Args/Args.cpp
        ../src/MiniDictionary/MiniDictionary.cpp
        ../src/CommandLine/CommandLine.cpp)
