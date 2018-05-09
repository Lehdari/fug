cmake_minimum_required(VERSION 3.8)
project(TemplateECS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src)
add_subdirectory(test)

add_library(TemplateECS ${LIBRARY_SOURCES})
add_executable(TemplateECS_Test ${TEST_SOURCES})

target_link_libraries(TemplateECS_Test TemplateECS)
target_include_directories(TemplateECS_Test PRIVATE src)
