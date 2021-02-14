cmake_minimum_required(VERSION 3.0.0)
set (CMAKE_CXX_STANDARD 17)
project(Email-Spam-Filter VERSION 0.1.0)

set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)

include_directories(${LIB_DIR}/hash-table)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/hash-table)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
