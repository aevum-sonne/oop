cmake_minimum_required(VERSION 3.15)
project(MiniDictionary)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)
include_directories(src/MiniDictionary)
include_directories(src/MiniDictionaryUtils)
include_directories(src/Args)
include_directories(tests)

add_executable(MiniDictionary
        src/Args/Args.cpp src/Args/Args.h
        src/MiniDictionary/MiniDictionary.cpp src/MiniDictionary/MiniDictionary.h
        src/MiniDictionaryUtils/MiniDictionaryUtils.cpp src/MiniDictionaryUtils/MiniDictionaryUtils.h
        tests/Tests.cpp tests/Tests.h)

#src/Main.cpp
#tests/Tests.cpp tests/Tests.h