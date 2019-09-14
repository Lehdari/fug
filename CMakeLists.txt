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

#Set error message for failed type id query
if(FUG_SCAN_TYPES)
    set(FUG_TYPE_ID_ERROR_MESSAGE "Type auto-scan was unable to find the queried type.")
else()
    set(FUG_TYPE_ID_ERROR_MESSAGE "Queried type not registered in CMakeLists.txt.")
endif()

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


#Scan components or use manually provided lists depending on the preference
if(FUG_SCAN_TYPES)
    message(STATUS "Scanning component types from file names")

    #Scan internal components
    set(FUG_COMPONENT_TYPES "${FUG_HEADERS}")
    string(REPLACE ";" " " FUG_COMPONENT_TYPES "${FUG_COMPONENT_TYPES}")
    string(REGEX MATCHALL "[a-zA-Z0-9]+Component.hpp" FUG_COMPONENT_TYPES "${FUG_COMPONENT_TYPES}")
    string(REPLACE ".hpp" " " FUG_COMPONENT_TYPES "${FUG_COMPONENT_TYPES}")
    string(REPLACE ";" "" FUG_COMPONENT_TYPES "${FUG_COMPONENT_TYPES}")

    #Scan application components
    set(FUG_APP_COMPONENT_TYPES "${FUG_APP_HEADERS}")
    string(REPLACE ";" " " FUG_APP_COMPONENT_TYPES "${FUG_APP_COMPONENT_TYPES}")
    string(REGEX MATCHALL "[a-zA-Z0-9]+Component.hpp" FUG_APP_COMPONENT_TYPES "${FUG_APP_COMPONENT_TYPES}")
    string(REPLACE ".hpp" " " FUG_APP_COMPONENT_TYPES "${FUG_APP_COMPONENT_TYPES}")
    string(REPLACE ";" "" FUG_APP_COMPONENT_TYPES "${FUG_APP_COMPONENT_TYPES}")

    message(STATUS "Detected fug component types: ${FUG_COMPONENT_TYPES}")
    message(STATUS "Detected application component types: ${FUG_APP_COMPONENT_TYPES}")
else()
    message(STATUS "Component types provided manually")

    #List component types below
    #set(FUG_COMPONENT_TYPES "${FUG_COMPONENT_TYPES}")

    message(STATUS "Provided fug component types: ${FUG_COMPONENT_TYPES}")
    message(STATUS "Provided application component types: ${FUG_APP_COMPONENT_TYPES}")
endif()

#Parse definitions for component types and forward declarations
#Internal component types
string(STRIP "${FUG_COMPONENT_TYPES}" FUG_COMPONENT_TYPES)
if ("${FUG_COMPONENT_TYPES}" STREQUAL "")
    message(FATAL_ERROR "No fug component types provided")
endif()
string(REGEX REPLACE "([^ ]+)" "class \\1;" FUG_COMPONENT_FORWARD_DECLARATIONS "${FUG_COMPONENT_TYPES}")
string(REPLACE ";" "\\\; " FUG_COMPONENT_FORWARD_DECLARATIONS "${FUG_COMPONENT_FORWARD_DECLARATIONS}")
string(REGEX REPLACE "([^ ]+)" "fug::\\1" FUG_COMPONENT_TYPES "${FUG_COMPONENT_TYPES}")
string(REPLACE " " ", " FUG_COMPONENT_TYPES ${FUG_COMPONENT_TYPES})

#Application component types
string(STRIP "${FUG_APP_COMPONENT_TYPES}" FUG_APP_COMPONENT_TYPES)
if (NOT "${FUG_APP_COMPONENT_TYPES}" STREQUAL "")
    string(REGEX REPLACE "([^ ]+)" "class \\1;"
        FUG_APP_COMPONENT_FORWARD_DECLARATIONS "${FUG_APP_COMPONENT_TYPES}")
    string(REPLACE ";" "\\\; " FUG_APP_COMPONENT_FORWARD_DECLARATIONS
        "${FUG_APP_COMPONENT_FORWARD_DECLARATIONS}")
    string(REPLACE " " ", " FUG_APP_COMPONENT_TYPES ${FUG_APP_COMPONENT_TYPES})
    set(FUG_APP_COMPONENT_TYPES ", ${FUG_APP_COMPONENT_TYPES}")
endif()

#Compile to single list
set(FUG_COMPONENT_TYPES "${FUG_COMPONENT_TYPES}${FUG_APP_COMPONENT_TYPES}")
set(FUG_COMPONENT_FORWARD_DECLARATIONS "namespace fug { \
${FUG_COMPONENT_FORWARD_DECLARATIONS}} \
${FUG_APP_COMPONENT_FORWARD_DECLARATIONS}")


#Scan singletons or use manually provided lists depending on the preference
if(FUG_SCAN_TYPES)
    message(STATUS "Scanning singleton types from file names")

    #Scan internal singletons
    set(FUG_SINGLETON_TYPES "${FUG_HEADERS}")
    string(REPLACE ";" " " FUG_SINGLETON_TYPES "${FUG_SINGLETON_TYPES}")
    string(REGEX MATCHALL "[a-zA-Z0-9]+Singleton.hpp" FUG_SINGLETON_TYPES "${FUG_SINGLETON_TYPES}")
    string(REPLACE ".hpp" " " FUG_SINGLETON_TYPES "${FUG_SINGLETON_TYPES}")
    string(REPLACE ";" "" FUG_SINGLETON_TYPES "${FUG_SINGLETON_TYPES}")

    #Scan application singletons
    set(FUG_APP_SINGLETON_TYPES "${FUG_APP_HEADERS}")
    string(REPLACE ";" " " FUG_APP_SINGLETON_TYPES "${FUG_APP_SINGLETON_TYPES}")
    string(REGEX MATCHALL "[a-zA-Z0-9]+Singleton.hpp" FUG_APP_SINGLETON_TYPES "${FUG_APP_SINGLETON_TYPES}")
    string(REPLACE ".hpp" " " FUG_APP_SINGLETON_TYPES "${FUG_APP_SINGLETON_TYPES}")
    string(REPLACE ";" "" FUG_APP_SINGLETON_TYPES "${FUG_APP_SINGLETON_TYPES}")

    message(STATUS "Detected fug singleton types: ${FUG_SINGLETON_TYPES}")
    message(STATUS "Detected application singleton types: ${FUG_APP_SINGLETON_TYPES}")
else()
    message(STATUS "Singleton types provided manually")

    #List singleton types below
    #set(FUG_SINGLETON_TYPES "${FUG_SINGLETON_TYPES}")

    message(STATUS "Provided fug singleton types: ${FUG_SINGLETON_TYPES}")
    message(STATUS "Provided application singleton types: ${FUG_APP_SINGLETON_TYPES}")
endif()

#Parse definitions for singleton types and forward declarations
#Internal singleton types
string(STRIP "${FUG_SINGLETON_TYPES}" FUG_SINGLETON_TYPES)
if (NOT "${FUG_SINGLETON_TYPES}" STREQUAL "")
    string(REGEX REPLACE "([^ ]+)" "class \\1;" FUG_SINGLETON_FORWARD_DECLARATIONS "${FUG_SINGLETON_TYPES}")
    string(REPLACE ";" "\\\; " FUG_SINGLETON_FORWARD_DECLARATIONS "${FUG_SINGLETON_FORWARD_DECLARATIONS}")
    string(REGEX REPLACE "([^ ]+)" "fug::\\1" FUG_SINGLETON_TYPES "${FUG_SINGLETON_TYPES}")
    string(REPLACE " " ", " FUG_SINGLETON_TYPES ${FUG_SINGLETON_TYPES})
endif()

#Application singleton types
string(STRIP "${FUG_APP_SINGLETON_TYPES}" FUG_APP_SINGLETON_TYPES)
if (NOT "${FUG_APP_SINGLETON_TYPES}" STREQUAL "")
    string(REGEX REPLACE "([^ ]+)" "class \\1;"
        FUG_APP_SINGLETON_FORWARD_DECLARATIONS "${FUG_APP_SINGLETON_TYPES}")
    string(REPLACE ";" "\\\; " FUG_APP_SINGLETON_FORWARD_DECLARATIONS
        "${FUG_APP_SINGLETON_FORWARD_DECLARATIONS}")
    string(REPLACE " " ", " FUG_APP_SINGLETON_TYPES ${FUG_APP_SINGLETON_TYPES})
    set(FUG_APP_SINGLETON_TYPES "${FUG_APP_SINGLETON_TYPES}")
endif()

#Compile to single list
if (NOT "${FUG_SINGLETON_TYPES}" STREQUAL "" AND NOT "${FUG_APP_SINGLETON_TYPES}" STREQUAL "")
    set(FUG_SINGLETON_TYPES "${FUG_SINGLETON_TYPES}, ${FUG_APP_SINGLETON_TYPES}")
else()
    set(FUG_SINGLETON_TYPES "${FUG_SINGLETON_TYPES}${FUG_APP_SINGLETON_TYPES}")
endif()
set(FUG_SINGLETON_FORWARD_DECLARATIONS "namespace fug { \
${FUG_SINGLETON_FORWARD_DECLARATIONS}} \
${FUG_APP_SINGLETON_FORWARD_DECLARATIONS}")

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
add_library(fug_engine SHARED ${ENGINE_SOURCES})
target_include_directories(fug_engine
    PUBLIC
        include/
    PRIVATE
        include/engine/
)
target_link_libraries(fug_engine
    PUBLIC
        fug_ecs
)
