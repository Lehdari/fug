cmake_minimum_required(VERSION 3.1)
project(fug)

file(GLOB_RECURSE SRC_FILES src/*.cpp src/*/*.cpp)
include_directories(include)

find_package(Eigen3 REQUIRED)
find_package(SFML 2 REQUIRED system window graphics network audio)

include_directories(
    ${EIGEN3_INCLUDE_DIR}
    ${SFML_INCLUDE_DIRS}
)

link_libraries (
    ${SFML_LIBRARIES}
)

add_executable(fug ${SRC_FILES})
set_property(TARGET fug PROPERTY CXX_STANDARD 14)
