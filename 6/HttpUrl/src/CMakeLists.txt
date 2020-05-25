cmake_minimum_required(VERSION 3.15)
project(HttpUrl)

set(CMAKE_CXX_STANDARD 17)

add_executable(HttpUrl
        Main.cpp
        HttpUrl/HttpUrl.cpp
        UrlParsingError/UrlParsingError.cpp
        ../include/HttpUrl/HttpUrl.h
        ../include/UrlParsingError/UrlParsingError.h
        ../include/Protocol/Protocol.h
        ../include/ParsingMessages/ParsingMessages.h)

target_include_directories(HttpUrl PRIVATE ../include)