cmake_minimum_required(VERSION 3.0)
project(fug)


#Option for using component type auto-scan
option(FUG_SCAN_TYPES "Scan type-id types from file names automatically" ON)


#Set required C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Output libraries to same directory with binaries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


#External dependencies
add_subdirectory(ext)


#Scan directories for header and source files
add_subdirectory(include)
add_subdirectory(src)
set(FUG_HEADERS ${FUG_HEADERS}
    ${UTILS_HEADERS}
    ${ECS_HEADERS}
    ${ENGINE_HEADERS}
)
set(FUG_SOURCES ${FUG_SOURCES}
    ${ECS_SOURCES}
    ${ENGINE_SOURCES}
)


#Type id system preprocessing
if(FUG_SCAN_TYPES)
    set(FUG_TYPE_ID_ERROR_MESSAGE "Type auto-scan was unable to find the queried type.")
else()
    set(FUG_TYPE_ID_ERROR_MESSAGE "Queried type not registered in CMakeLists.txt.")

    #List fug internal component types below
    set(FUG_COMPONENT_TYPES "EventComponent LogicComponent")

    #List fug internal singleton types below
    set(FUG_SINGLETON_TYPES "")
endif()

#Process macros (see the files for more information)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/component_types.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/singleton_types.cmake)


#Utils library target (utils is header-only library)
add_library(fug_utils INTERFACE)
target_include_directories(fug_utils
    INTERFACE
        include/
)
target_compile_definitions(fug_utils
    INTERFACE
        FUG_COMPONENT_TYPES=${FUG_COMPONENT_TYPES}
        FUG_COMPONENT_FORWARD_DECLARATIONS=${FUG_COMPONENT_FORWARD_DECLARATIONS}
        FUG_SINGLETON_TYPES=${FUG_SINGLETON_TYPES}
        FUG_SINGLETON_FORWARD_DECLARATIONS=${FUG_SINGLETON_FORWARD_DECLARATIONS}
        FUG_TYPE_ID_ERROR_MESSAGE="${FUG_TYPE_ID_ERROR_MESSAGE}"
)


#Ecs library target
add_library(fug_ecs SHARED ${ECS_SOURCES})
target_include_directories(fug_ecs
    PUBLIC
        include/
    PRIVATE
        include/ecs/
)
target_link_libraries(fug_ecs
    PUBLIC
        fug_utils
)

#Engine library target
add_library(fug_engine SHARED ${ENGINE_HEADERS} ${ENGINE_SOURCES})
target_include_directories(fug_engine
    PUBLIC
        include/
        ${CMAKE_CURRENT_SOURCE_DIR}/ext/rapidjson/include/
    PRIVATE
        include/engine/
)
target_link_libraries(fug_engine
    PUBLIC
        fug_ecs
)
