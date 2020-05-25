# see https://cmake.org/cmake/help/latest/module/FindBoost.html
set (Boost_USE_STATIC_LIBS OFF)
find_package (Boost REQUIRED COMPONENTS unit_test_framework)

include_directories(${Boost_INCLUDE_DIR})

add_executable(ComplexTests
        ComplexTests.cpp
        ../src/Complex/Complex.cpp
        ../src/Complex/Complex.h)

target_link_libraries (ComplexTests ${Boost_LIBRARIES})