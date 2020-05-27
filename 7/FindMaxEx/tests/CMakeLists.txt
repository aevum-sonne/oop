# see https://cmake.org/cmake/help/latest/module/FindBoost.html
set (Boost_USE_STATIC_LIBS OFF)
find_package (Boost REQUIRED COMPONENTS unit_test_framework)

include_directories(${Boost_INCLUDE_DIR})

add_executable(FindMaxExTests
        FindMaxExTests.cpp
        ../include/FindMaxEx/FindMaxEx.h
        ../include/Less/Less.h
        ../src/FindMaxExController/FindMaxExController.cpp
        ../include/FindMaxExController/FindMaxExController.h
        ../include/Sportsman/Sportsman.h)

target_link_libraries(FindMaxExTests ${Boost_LIBRARIES})
target_include_directories(FindMaxExTests PRIVATE ../include)