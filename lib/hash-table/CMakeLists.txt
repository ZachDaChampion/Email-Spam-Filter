cmake_minimum_required(VERSION 3.0.0)
set (CMAKE_CXX_STANDARD 17)

set(LIBRARY_OUTPUT_PATH ${BUILD_DIR}/lib)

add_library(hashtable STATIC hashtable.hpp hash.cpp hash.hpp)
