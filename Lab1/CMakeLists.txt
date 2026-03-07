cmake_minimum_required(VERSION 3.10)

project(Lab1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(
        app.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h
        SortedBag.cpp
        ShortTest.h
        SortedBagIterator.h
        SortedBagIterator.cpp
)