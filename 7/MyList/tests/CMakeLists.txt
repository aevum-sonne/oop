# see https://cmake.org/cmake/help/latest/module/FindBoost.html
set (Boost_USE_STATIC_LIBS OFF)
find_package (Boost REQUIRED COMPONENTS unit_test_framework)

include_directories(${Boost_INCLUDE_DIR})

add_executable(MyListTests
        MyListTests.cpp
        ../include/MyList/MyList.h)

target_link_libraries(MyListTests ${Boost_LIBRARIES})
target_include_directories(MyListTests PRIVATE ../include)