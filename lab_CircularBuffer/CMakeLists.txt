cmake_minimum_required(VERSION 3.10)

project(Lab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")

include_directories("${CMAKE_SOURCE_DIR}/../googletest/googletest/include")
link_directories("${CMAKE_SOURCE_DIR}/../googletest/build/lib")

add_executable(run test.cpp Cbuff.h Cbuff.cpp)
target_link_libraries(run gtest gtest_main)
