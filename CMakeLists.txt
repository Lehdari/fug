cmake_minimum_required(VERSION 3.0)
project(fug)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


add_subdirectory(include)
add_subdirectory(src)


add_library(fug_ecs SHARED ${ECS_SOURCES})
target_include_directories(fug_ecs
    PUBLIC
        include/
        include/ecs/
)

add_library(fug_engine SHARED ${ENGINE_SOURCES})
target_include_directories(fug_engine
    PUBLIC
        include/
        include/ecs/
        )
target_link_libraries(fug_engine
    PUBLIC
        fug_ecs)
