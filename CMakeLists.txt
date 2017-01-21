cmake_minimum_required(VERSION 2.8)
project(fug)

file(GLOB_RECURSE CORE_SRC_FILES lib/glLoadGen/gl_core_3_3.c src/Core/*.cpp)
file(GLOB_RECURSE LOGIC_SRC_FILES src/Logic/*.cpp)
file(GLOB_RECURSE GRAPHICS_SRC_FILES src/Graphics/*.cpp)
file(GLOB_RECURSE GAME_SRC_FILES src/GameJam2017/*.cpp src/game_main.cpp)
file(GLOB_RECURSE TEST_SRC_FILES src/Test/*.cpp src/test_main.cpp)

include_directories(include lib/glLoadGen)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(CMAKE_MODULE_PATH "~/cmake_modules")
    set(CLANG_COVERAGE_LINK_FLAGS "-framework OpenGL -lbox2d")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CLANG_COVERAGE_LINK_FLAGS "-lGL -lBox2D")
endif()
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${CLANG_COVERAGE_LINK_FLAGS}")

find_package(Eigen3 REQUIRED)
find_package(SFML 2 REQUIRED system window graphics network audio)
find_package(GLEW REQUIRED)

include_directories(
    ${EIGEN3_INCLUDE_DIR}
    ${SFML_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
)

link_libraries (
    ${SFML_LIBRARIES}
    ${GLEW_LIBRARIES}
)

add_definitions(-DFUG_UNIT_TEST=2)

# Xcode-project shizz
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    file(GLOB_RECURSE INCLUDE_FILES include/*/*.hpp include/*/*.tcc)
    add_executable(fgj ${CORE_SRC_FILES} ${LOGIC_SRC_FILES} ${GRAPHICS_SRC_FILES} ${GAME_SRC_FILES} ${INCLUDE_FILES})
    add_executable(fug ${CORE_SRC_FILES} ${GRAPHICS_SRC_FILES} ${TEST_SRC_FILES} ${INCLUDE_FILES})
else()
    add_executable(fgj ${CORE_SRC_FILES} ${LOGIC_SRC_FILES} ${GRAPHICS_SRC_FILES} ${GAME_SRC_FILES})
    add_executable(fug ${CORE_SRC_FILES} ${GRAPHICS_SRC_FILES} ${TEST_SRC_FILES})
endif()

set_property(TARGET fug PROPERTY CXX_STANDARD 14)
set_property(TARGET fgj PROPERTY CXX_STANDARD 14)
