cmake_minimum_required(VERSION 3.8)
project(ContainerTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(LIBRARY_SOURCES src/Container.hpp src/Container.cpp)

set(DEMO_SOURCES src/main.cpp)

add_library(ContainerTest ${LIBRARY_SOURCES})

add_executable(ContainerTestDemo ${DEMO_SOURCES})

target_link_libraries(ContainerTestDemo ContainerTest)
target_include_directories(ContainerTestDemo PRIVATE src)
