cmake_minimum_required(VERSION 3.15)
project(FindMaxEx)

set(CMAKE_CXX_STANDARD 17)

add_executable(FindMaxEx
        Main.cpp
        ../include/FindMaxEx/FindMaxEx.h
        ../include/Less/Less.h
        FindMaxExController/FindMaxExController.cpp
        ../include/FindMaxExController/FindMaxExController.h
        ../include/Sportsman/Sportsman.h)

target_include_directories(FindMaxEx PRIVATE ../include)

# see https://cmake.org/cmake/help/latest/module/FindBoost.html
#set (Boost_USE_STATIC_LIBS_OFF)
include_directories(${Boost_INCLUDE_DIR})
# Note: a target should be already defined using 'add_executable' or 'add_library' 
target_link_libraries(FindMaxEx ${Boost_LIBRARIES})

