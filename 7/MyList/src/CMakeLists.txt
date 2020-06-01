cmake_minimum_required(VERSION 3.15)
project(MyList)

set(CMAKE_CXX_STANDARD 17)

add_executable(MyList
        Main.cpp
        ../include/MyList/MyList.h)

target_include_directories(MyList PRIVATE ../include)