#
# Project: fug
# File: singleton_types.cmake
#
# Copyright (c) 2019 Miika 'Lehdari' Lehtimäki
# You may use, distribute and modify this code under the terms
# of the licence specified in file LICENSE which is distributed
# with this source code package.
#
# This file populates FUG_SINGLETON_TYPES and FUG_SINGLETON_FORWARD_DECLARATIONS macros
# required by the fug type id system.
# Inputs are given via FUG_SINGLETON_TYPES and FUG_APP_SINGLETON_TYPES. The former lists
# internal fug singleton types and the latter singleton types provided by the application.
#
# Example of the format the macros are to be provided:
# Inputs:
# FUG_SINGLETON_TYPES: ASingleton BSingleton
# FUG_APP_SINGLETON_TYPES: AppASingleton AppBSingleton
# Outputs:
# FUG_SINGLETON_TYPES: fug::ASingleton, fug::BSingleton, AppASingleton, AppBSingleton
# FUG_SINGLETON_FORWARD_DECLARATIONS:
# namespace fug { class ASingleton; class BSingleton; } class AppASingleton; class AppBSingleton;
#
# If one wishes to use the auto-scan feature, list of headers are to be provided
# via FUG_HEADERS and FUG_APP_HEADERS variables. Singleton types are detected using *Singleton.hpp
# file name postfix.
#

#Scan singletons or use manually provided lists depending on the FUG_SCAN_TYPES option
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