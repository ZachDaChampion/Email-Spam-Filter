cmake_minimum_required(VERSION 3.0.0)
set (CMAKE_CXX_STANDARD 17)
project(Email-Spam-Filter VERSION 0.1.0)

include(CTest)
enable_testing()

set(LIBRARY_OUTPUT_PATH lib)

add_library(hashtable STATIC hashtable.hpp hash.cpp hash.hpp)
