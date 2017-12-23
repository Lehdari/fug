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
find_package(GLEW REQUIRED)

add_subdirectory(ext/imgui-fug)

file(GLOB_RECURSE CORE_SRC_FILES src/Core/*.cpp)
file(GLOB_RECURSE CORE_INCLUDE_FILES
    include/Core/*.hpp
    include/Core/*.tcc
)

file(GLOB_RECURSE LOGIC_SRC_FILES src/Logic/*.cpp)
file(GLOB_RECURSE LOGIC_INCLUDE_FILES
    include/Logic/*.hpp
    include/Logic/*.tcc
)

file(GLOB_RECURSE GRAPHICS_SRC_FILES
    src/Graphics/*.cpp
)
file(GLOB_RECURSE GRAPHICS_INCLUDE_FILES
    include/Graphics/*.hpp
    include/Graphics/*.tcc
)

file(GLOB_RECURSE ENGINE_SRC_FILES src/Engine/*.cpp)
file(GLOB_RECURSE ENGINE_INCLUDE_FILES
    include/Engine/*.hpp
    include/Engine/*.tcc
)

# TODO Make this scale better for multiple demos
file(GLOB_RECURSE GAME_SRC_FILES demo/GameJam2017/*.cpp)
file(GLOB_RECURSE GAME_INCLUDE_FILES include/GameJam2017/*.hpp)

file(GLOB_RECURSE TEXTURED_CUBE_SRC_FILES demo/TexturedCube/*.cpp)
file(GLOB_RECURSE PRIMITIVES_SRC_FILES demo/Primitives/*.cpp)
file(GLOB_RECURSE DRAW_TEST_SRC_FILES demo/TexturedCube/*.cpp)
file(GLOB_RECURSE CUBE_DEMO_SRC_FILES demo/CubeDemo/*.cpp)

file(GLOB_RECURSE TEST_SRC_FILES src/Test/*.cpp src/test_main.cpp)
file(GLOB_RECURSE TEST_INCLUDE_FILES include/Test/*.hpp)

include_directories(include ext/)

# Definition for res/ directory
add_definitions(-DFUG_RES_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}/res/")

# Libraries
add_library(fug-core
    SHARED
    ${CORE_SRC_FILES}
    ${CORE_INCLUDE_FILES}
)
target_include_directories(fug-core
    PUBLIC
    ${EIGEN3_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
)
set_property(TARGET fug-core PROPERTY CXX_STANDARD 14)

add_library(fug-logic
    SHARED
    ${LOGIC_SRC_FILES}
    ${LOGIC_INCLUDE_FILES}
)
target_link_libraries(fug-logic
    fug-core
)
set_property(TARGET fug-logic PROPERTY CXX_STANDARD 14)

add_library(fug-graphics
    SHARED
    ${GRAPHICS_SRC_FILES}
    ${GRAPHICS_INCLUDE_FILES}
)
target_include_directories(fug-graphics
    PUBLIC
    ${SFML_INCLUDE_DIR}
    ${GLEW_INCLUDE_DIR}
)
target_link_libraries(fug-graphics
    fug-core
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    ${SFML_LIBRARIES}
)
set_property(TARGET fug-graphics PROPERTY CXX_STANDARD 14)

add_library(fug-engine
    SHARED
    ${ENGINE_SRC_FILES}
    ${ENGINE_INCLUDE_FILES}
)
target_link_libraries(fug-engine
    fug-logic
    fug-graphics
)
set_property(TARGET fug-engine PROPERTY CXX_STANDARD 14)

# Applications
add_executable(fug_test
    ${TEST_SRC_FILES}
    ${TEST_INCLUDE_FILES}
)
target_include_directories(fug_test
    PRIVATE ${EIGEN3_INCLUDE_DIR}
    PRIVATE ${SFML_INCLUDE_DIRS}
)
target_link_libraries(fug_test
    fug-engine
    ${OPENGL_LIBRARIES}
    ${SFML_LIBRARIES}
)
set_property(TARGET fug_test PROPERTY CXX_STANDARD 14)

add_executable(fgj
    ${GAME_SRC_FILES}
    ${GAME_INCLUDE_FILES}
)
target_include_directories(fgj
    PRIVATE ${EIGEN3_INCLUDE_DIR}
)
target_link_libraries(fgj
    fug-engine
    ${OPENGL_LIBRARIES}
    ${SFML_LIBRARIES}
)
set_property(TARGET fgj PROPERTY CXX_STANDARD 14)

add_executable(textured_cube ${TEXTURED_CUBE_SRC_FILES})
target_include_directories(textured_cube
    PRIVATE ${EIGEN3_INCLUDE_DIR}
    PRIVATE ${SFML_INCLUDE_DIRS}
)
target_link_libraries(textured_cube
    fug-engine
    imgui-fug
    ${OPENGL_LIBRARIES}
    ${SFML_LIBRARIES}
)
set_property(TARGET textured_cube PROPERTY CXX_STANDARD 14)

add_executable(primitives ${PRIMITIVES_SRC_FILES})
target_include_directories(primitives
    PRIVATE ${EIGEN3_INCLUDE_DIR}
    PRIVATE ${SFML_INCLUDE_DIRS}
)
target_link_libraries(primitives
    fug-engine
    ${OPENGL_LIBRARIES}
    ${SFML_LIBRARIES}
)
set_property(TARGET primitives PROPERTY CXX_STANDARD 14)

add_executable(cube_demo ${CUBE_DEMO_SRC_FILES})
target_include_directories(cube_demo 
    PRIVATE ${EIGEN3_INCLUDE_DIR}
    PRIVATE ${SFML_INCLUDE_DIRS}
)
target_link_libraries(cube_demo 
    fug-engine
    ${OPENGL_LIBRARIES}
    ${SFML_LIBRARIES}
)
set_property(TARGET cube_demo PROPERTY CXX_STANDARD 14)

