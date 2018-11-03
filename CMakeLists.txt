cmake_minimum_required(VERSION 2.8)
project(ECSTestGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(include)
add_subdirectory(src)

add_executable(ECSTestGame ${EXECUTABLE_HEADERS} ${EXECUTABLE_SOURCES})

target_include_directories(ECSTestGame PUBLIC include)

# Find and link SFML
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
target_link_libraries(ECSTestGame sfml-system sfml-window sfml-graphics)
