cmake_minimum_required(VERSION 3.20)
project(SortedIndexedList)

set(CMAKE_CXX_STANDARD 17)

add_executable(SortedIndexedList
        SortedIndexedList.cpp
        ListIterator.cpp
        App.cpp
        ExtendedTest.h
        ExtendedTest.cpp
        ShortTest.h
        ShortTest.cpp
        SortedIndexedList.h
        ListIterator.h
)