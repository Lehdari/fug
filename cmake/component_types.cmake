#
# Project: fug
# File: component_types.cmake
#
# Copyright (c) 2019 Miika 'Lehdari' Lehtimäki
# You may use, distribute and modify this code under the terms
# of the licence specified in file LICENSE which is distributed
# with this source code package.
#
# This file populates FUG_COMPONENT_TYPES and FUG_COMPONENT_FORWARD_DECLARATIONS macros
# required by the fug type id system.
# Inputs are given via FUG_COMPONENT_TYPES and FUG_APP_COMPONENT_TYPES. The former lists
# internal fug component types and the latter component types provided by the application.
#
# Example of the format the macros are to be provided:
# Inputs:
# FUG_COMPONENT_TYPES: AComponent BComponent
# FUG_APP_COMPONENT_TYPES: AppAComponent AppBComponent
# Outputs:
# FUG_COMPONENT_TYPES: fug::AComponent, fug::BComponent, AppAComponent, AppBComponent
# FUG_COMPONENT_FORWARD_DECLARATIONS:
# namespace fug { class AComponent; class BComponent; } class AppAComponent; class AppBComponent;
#
# If one wishes to use the auto-scan feature, list of headers are to be provided
# via FUG_HEADERS and FUG_APP_HEADERS variables. Component types are detected using *Component.hpp
# file name postfix.
#

#Scan components or use manually provided lists depending on the FUG_SCAN_TYPES option
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

    message(STATUS "Provided fug component types: ${FUG_COMPONENT_TYPES}")
    message(STATUS "Provided application component types: ${FUG_APP_COMPONENT_TYPES}")
endif()

#Parse definitions for component types and forward declarations
#Internal component types
string(STRIP "${FUG_COMPONENT_TYPES}" FUG_COMPONENT_TYPES)
if (NOT "${FUG_COMPONENT_TYPES}" STREQUAL "")
    string(REGEX REPLACE "([^ ]+)" "class \\1;" FUG_COMPONENT_FORWARD_DECLARATIONS "${FUG_COMPONENT_TYPES}")
    string(REPLACE ";" "\\\; " FUG_COMPONENT_FORWARD_DECLARATIONS "${FUG_COMPONENT_FORWARD_DECLARATIONS}")
    string(REGEX REPLACE "([^ ]+)" "fug::\\1" FUG_COMPONENT_TYPES "${FUG_COMPONENT_TYPES}")
    string(REPLACE " " ", " FUG_COMPONENT_TYPES ${FUG_COMPONENT_TYPES})
endif()

#Application component types
string(STRIP "${FUG_APP_COMPONENT_TYPES}" FUG_APP_COMPONENT_TYPES)
if (NOT "${FUG_APP_COMPONENT_TYPES}" STREQUAL "")
    string(REGEX REPLACE "([^ ]+)" "class \\1;"
        FUG_APP_COMPONENT_FORWARD_DECLARATIONS "${FUG_APP_COMPONENT_TYPES}")
    string(REPLACE ";" "\\\; " FUG_APP_COMPONENT_FORWARD_DECLARATIONS
        "${FUG_APP_COMPONENT_FORWARD_DECLARATIONS}")
    string(REPLACE " " ", " FUG_APP_COMPONENT_TYPES ${FUG_APP_COMPONENT_TYPES})
endif()

#Compile to single list
if (NOT "${FUG_COMPONENT_TYPES}" STREQUAL "" AND NOT "${FUG_APP_COMPONENT_TYPES}" STREQUAL "")
    set(FUG_COMPONENT_TYPES "${FUG_COMPONENT_TYPES}, ${FUG_APP_COMPONENT_TYPES}")
else()
    set(FUG_COMPONENT_TYPES "${FUG_COMPONENT_TYPES}${FUG_APP_COMPONENT_TYPES}")
endif()
set(FUG_COMPONENT_FORWARD_DECLARATIONS "namespace fug { \
${FUG_COMPONENT_FORWARD_DECLARATIONS}} \
${FUG_APP_COMPONENT_FORWARD_DECLARATIONS}")