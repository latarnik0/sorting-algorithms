cmake_minimum_required(VERSION 3.10)

project(SortingAlgorithms CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES src/main.cpp src/DataManage.cpp)

add_executable(sort ${SOURCES})

target_include_directories(sort PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)