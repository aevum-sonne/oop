cmake_minimum_required(VERSION 3.15)
project(Shapes)

set(CMAKE_CXX_STANDARD 17)

add_executable(Shapes
        Main.cpp
        Shapes/Triangle.cpp
        Shapes/Rectangle.cpp
        Shapes/Circle.cpp
        Shapes/LineSegment.cpp
        ShapesController/ShapesController.cpp
        ../include/Shapes/Triangle.h
        ../include/Shapes/Rectangle.h
        ../include/Shapes/Circle.h
        ../include/Interfaces/ISolidShape.h
        ../include/Interfaces/IShape.h
        ../include/Shapes/LineSegment.h
        ../include/ShapesController/ShapesController.h
        ../include/Constants/Constants.h Point/Point.cpp)

target_include_directories(Shapes PRIVATE ../include)
