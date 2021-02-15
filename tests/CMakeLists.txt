cmake_minimum_required(VERSION 3.0.0)
set (CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_OUTPUT_PATH ${BUILD_DIR}/test)

add_library(catch IMPORTED INTERFACE)
target_include_directories(catch INTERFACE ${LIB_DIR}/catch)

add_executable(tests test.cpp test-hash.cpp test-hash-table.cpp)
target_link_libraries(tests catch hashtable)

include(CTest)
include(${LIB_DIR}/catch/Catch.cmake)
catch_discover_tests(tests)
