cmake_minimum_required(VERSION 3.1)
project(fug)

file(GLOB_RECURSE SRC_FILES src/*.cpp src/*/*.cpp)
include_directories(include)

find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

add_executable(fug ${SRC_FILES})
set_property(TARGET fug PROPERTY CXX_STANDARD 14)
