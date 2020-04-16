cmake_minimum_required(VERSION 3.15)
project(MiniDictionary)

set(CMAKE_CXX_STANDARD 17)

add_executable(Main
        Main.cpp
        Args/Args.cpp
        MiniDictionary/MiniDictionary.cpp
        CommandLine/CommandLine.cpp)