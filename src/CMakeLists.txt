cmake_minimum_required(VERSION 3.0.0)
set (CMAKE_CXX_STANDARD 17)

set(EXECUTABLE_OUTPUT_PATH ${BUILD_DIR}/bin)

add_executable(Email-Spam-Filter main.cpp)
target_link_libraries(Email-Spam-Filter hashtable)
