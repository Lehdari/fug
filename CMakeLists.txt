cmake_minimum_required(VERSION 3.0)
project(fug)


#Option for using component type auto-scan
option(FUG_SCAN_COMPONENTS "Scan component types from file names automatically" ON)


#Set required C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Output libraries to same directory with binaries
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


#Scan directories for header and source files
add_subdirectory(include)
add_subdirectory(src)
set(FUG_HEADERS ${FUG_HEADERS}
    ${ECS_HEADERS}
    ${ENGINE_HEADERS}
)
set(FUG_SOURCES ${FUG_SOURCES}
    ${ECS_SOURCES}
    ${ENGINE_SOURCES}
)


#Scan components or use manually provided lists depending on the preference
if(FUG_SCAN_COMPONENTS)
    message(STATUS "Scanning component types from file names")

    #Set error message for failed type id query
    set(FUG_COMPONENT_TYPE_ERROR_MESSAGE "Component auto-scan was unable to find the component type.\
 Please make sure that component types are defined individually in headers with *Component.hpp postfix.")

    #Scan components
    set(FUG_COMPONENT_TYPES "${FUG_HEADERS}")
    string(REPLACE ";" " " FUG_COMPONENT_TYPES "${FUG_COMPONENT_TYPES}")
    string(REGEX MATCHALL "[a-zA-Z0-9]+Component.hpp" FUG_COMPONENT_TYPES "${FUG_COMPONENT_TYPES}")
    string(REPLACE ".hpp" " " FUG_COMPONENT_TYPES "${FUG_COMPONENT_TYPES}")
    string(REPLACE ";" "" FUG_COMPONENT_TYPES "${FUG_COMPONENT_TYPES}")

    message(STATUS "Detected component types: ${FUG_COMPONENT_TYPES}")
else()
    message(STATUS "Component types provided manually")

    #Set error message for failed type id query
    set(FUG_COMPONENT_TYPE_ERROR_MESSAGE "Component type not registered in CMakeLists.txt.\
 Please make sure that all components are listed in FUG_COMPONENT_TYPES variable.")

    #List component types below
    #set(FUG_COMPONENT_TYPES "${FUG_COMPONENT_TYPES}")

    message(STATUS "Provided component types: ${FUG_COMPONENT_TYPES}")
endif()

#Parse definitions for component types and forward declarations
string(STRIP "${FUG_COMPONENT_TYPES}" FUG_COMPONENT_TYPES)
if ("${FUG_COMPONENT_TYPES}" STREQUAL "")
    message(FATAL_ERROR "No component types provided")
endif()
string(REGEX REPLACE "([^ ]+)" "class \\1;" FUG_COMPONENT_FORWARD_DECLARATIONS "${FUG_COMPONENT_TYPES}")
string(REPLACE ";" "\\\;" FUG_COMPONENT_FORWARD_DECLARATIONS "${FUG_COMPONENT_FORWARD_DECLARATIONS}")
string(REPLACE " " ", " FUG_COMPONENT_TYPES ${FUG_COMPONENT_TYPES})


#Ecs library target
add_library(fug_ecs SHARED ${ECS_SOURCES})
target_compile_definitions(fug_ecs
    PUBLIC
        FUG_COMPONENT_TYPES=${FUG_COMPONENT_TYPES}
        FUG_COMPONENT_FORWARD_DECLARATIONS=${FUG_COMPONENT_FORWARD_DECLARATIONS}
        FUG_COMPONENT_TYPE_ERROR_MESSAGE="${FUG_COMPONENT_TYPE_ERROR_MESSAGE}"
)
target_include_directories(fug_ecs
    PUBLIC
        include/
)
target_include_directories(fug_ecs
    PRIVATE
        include/ecs/
)

#Engine library target
add_library(fug_engine SHARED ${ENGINE_SOURCES})
target_include_directories(fug_engine
    PUBLIC
        include/
)
target_include_directories(fug_engine
    PRIVATE
        include/engine/
)
target_link_libraries(fug_engine
    PUBLIC
        fug_ecs
)
