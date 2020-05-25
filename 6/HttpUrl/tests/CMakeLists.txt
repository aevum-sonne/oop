# see https://cmake.org/cmake/help/latest/module/FindBoost.html
set (Boost_USE_STATIC_LIBS OFF)
find_package (Boost REQUIRED COMPONENTS unit_test_framework)

include_directories(${Boost_INCLUDE_DIR})

add_executable(HttpUrlTests
        HttpUrlTests.cpp
        ../src/HttpUrl/HttpUrl.cpp
        ../src/UrlParsingError/UrlParsingError.cpp
        ../include/HttpUrl/HttpUrl.h
        ../include/UrlParsingError/UrlParsingError.h
        ../include/Protocol/Protocol.h
        ../include/ParsingMessages/ParsingMessages.h)

target_link_libraries(HttpUrlTests ${Boost_LIBRARIES})
target_include_directories(HttpUrlTests PRIVATE ../include)