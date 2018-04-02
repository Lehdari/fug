cmake_minimum_required(VERSION 3.8)
project(TemplateECS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(LIBRARY_SOURCES src/Ecs.hpp src/Ecs.cpp src/System.hpp)

set(DEMO_SOURCES src/main.cpp)

add_library(TemplateECS ${LIBRARY_SOURCES})

add_executable(TemplateECSDemo ${DEMO_SOURCES})

target_link_libraries(TemplateECSDemo TemplateECS)
target_include_directories(TemplateECSDemo PRIVATE src)
