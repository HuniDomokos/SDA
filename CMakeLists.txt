cmake_minimum_required(VERSION 4.1)
project(Lab4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab4
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h
        SMIterator.cpp
        SMIterator.h
        SortedMap.cpp
        SortedMap.h)
