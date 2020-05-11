# see https://cmake.org/cmake/help/latest/module/FindBoost.html
set (Boost_USE_STATIC_LIBS OFF)
find_package (Boost REQUIRED COMPONENTS unit_test_framework)

include_directories(${Boost_INCLUDE_DIR})

add_executable(ShapesTests
        ShapesTests.cpp
        ../../src/Shapes/Triangle.cpp
        ../../src/Shapes/Rectangle.cpp
        ../../src/Shapes/Circle.cpp
        ../../src/Shapes/LineSegment.cpp
        ../../src/ShapesController/ShapesController.cpp
        ../../src/Point/Point.cpp
        ../../../include/Shapes/Triangle.h
        ../../../include/Shapes/Rectangle.h
        ../../../include/Shapes/Circle.h
        ../../../include/Interfaces/ISolidShape.h
        ../../../include/Interfaces/IShape.h
        ../../../include/Shapes/LineSegment.h
        ../../../include/ShapesController/ShapesController.h
        ../../../include/Constants/Constants.h
        )

target_link_libraries (ShapesTests ${Boost_LIBRARIES})
target_include_directories(ShapesTests PRIVATE ../../include)