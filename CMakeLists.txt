cmake_minimum_required(VERSION 2.8)
project(fug)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}")
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(CMAKE_MACOSX_RPATH ON)
    list(APPEND CMAKE_MODULE_PATH "~/cmake_modules")
endif()

find_package(Eigen3 REQUIRED)
find_package(SFML 2 REQUIRED system window graphics network audio)
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE CORE_SRC_FILES src/Core/*.cpp)
file(GLOB_RECURSE CORE_INCLUDE_FILES include/Core/*.{hpp,tcc})
file(GLOB_RECURSE LOGIC_SRC_FILES src/Logic/*.cpp)
file(GLOB_RECURSE LOGIC_INCLUDE_FILES include/Logic/*.{hpp,tcc})
file(GLOB_RECURSE GRAPHICS_SRC_FILES ext/glLoadGen/gl_core_3_3.c src/Graphics/*.cpp)
file(GLOB_RECURSE GRAPHICS_INCLUDE_FILES ext/glLoadGen/gl_core_3_3.h src/Graphics/*.cpp)
# TODO Make this scale better for multiple demos
file(GLOB_RECURSE GAME_SRC_FILES demo/GameJam2017/*)
file(GLOB_RECURSE TEST_SRC_FILES src/Test/*.cpp src/test_main.cpp)

include_directories(include ext/)


add_library(fug-core
    SHARED
    ${CORE_SRC_FILES}
    ${CORE_INCLUDE_FILES}
)
target_include_directories(fug-core PRIVATE ${EIGEN3_INCLUDE_DIR})
set_property(TARGET fug-core PROPERTY CXX_STANDARD 14)

add_library(fug-logic
    SHARED
    ${LOGIC_SRC_FILES}
    ${LOGIC_INCLUDE_FILES}
)
target_link_libraries(fug-logic
    fug-core
)
target_include_directories(fug-logic PRIVATE ${EIGEN3_INCLUDE_DIR})
set_property(TARGET fug-logic PROPERTY CXX_STANDARD 14)

add_library(fug-graphics
    SHARED
    ${GRAPHICS_SRC_FILES}
    ${GRAPHICS_INCLUDE_FILES}
)
target_link_libraries(fug-graphics
    fug-core
    ${OPENGL_LIBRARIES}
    ${SFML_LIBRARIES}
)
target_include_directories(fug-graphics PRIVATE ${EIGEN3_INCLUDE_DIR})
set_property(TARGET fug-graphics PROPERTY CXX_STANDARD 14)


add_executable(fug ${TEST_SRC_FILES})
target_include_directories(fug
    PRIVATE ${EIGEN3_INCLUDE_DIR}
    PRIVATE ${SFML_INCLUDE_DIRS}
)
target_link_libraries(fug
    fug-graphics
    fug-core
    ${OPENGL_LIBRARIES}
    ${SFML_LIBRARIES}
)
set_property(TARGET fug PROPERTY CXX_STANDARD 14)

add_executable(fgj ${GAME_SRC_FILES})
target_include_directories(fgj
    PRIVATE ${EIGEN3_INCLUDE_DIR}
    PRIVATE ${SFML_INCLUDE_DIRS}
)
target_link_libraries(fgj
    fug-graphics
    fug-logic
    fug-core
    ${OPENGL_LIBRARIES}
    ${SFML_LIBRARIES}
)
set_property(TARGET fgj PROPERTY CXX_STANDARD 14)
