cmake_minimum_required(VERSION 3.0.0)
set (CMAKE_CXX_STANDARD 17)
project(Email-Spam-Filter VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(lib/hash-table)

add_subdirectory(lib/hash-table)

set(EXECUTABLE_OUTPUT_PATH bin)

add_executable(Email-Spam-Filter main.cpp)

target_link_libraries(Email-Spam-Filter hashtable)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
