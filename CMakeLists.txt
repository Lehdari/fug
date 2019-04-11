cmake_minimum_required(VERSION 2.8)
project(ECSTestGame)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(ext)

add_library(engine SHARED ${ENGINE_HEADERS} ${ENGINE_SOURCES})

add_executable(ECSTestGame ${GAME_HEADERS} ${GAME_SOURCES})

target_include_directories(engine
        PUBLIC
        include
        ext/TemplateECS/src
        )

target_include_directories(ECSTestGame
    PUBLIC
        include
        ext/TemplateECS/src
)

# Find and link SFML
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

target_link_libraries(engine
        PUBLIC
        TemplateECS)

target_link_libraries(ECSTestGame
    PUBLIC
        engine
        TemplateECS
        sfml-system
        sfml-window
        sfml-graphics
        vecmat)
