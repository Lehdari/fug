cmake_minimum_required(VERSION 3.1)
project(fug)

file(GLOB_RECURSE SRC_FILES lib/glLoadGen/gl_core_3_3.c src/*.cpp src/*/*.cpp)
include_directories(include lib/glLoadGen)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(CMAKE_MODULE_PATH "~/cmake_modules")
    set(CLANG_COVERAGE_LINK_FLAGS "-framework OpenGL")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(CLANG_COVERAGE_LINK_FLAGS "-lGL")
endif()
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${CLANG_COVERAGE_LINK_FLAGS}")

find_package(Eigen3 REQUIRED)
find_package(SFML 2 REQUIRED system window graphics network audio)

include_directories(
    ${EIGEN3_INCLUDE_DIR}
    ${SFML_INCLUDE_DIRS}
)

link_libraries (
    ${SFML_LIBRARIES}
)

# Xcode-project shizz
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    file(GLOB_RECURSE INCLUDE_FILES include/*/*.hpp include/*/*.tcc)
    add_executable(fug ${SRC_FILES} ${INCLUDE_FILES})
else()
    add_executable(fug ${SRC_FILES})
endif()

set_property(TARGET fug PROPERTY CXX_STANDARD 14)
