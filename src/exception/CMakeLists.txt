cmake_minimum_required(VERSION 3.0)
project(stationaryorbit CXX)

set(AssemblyName stationaryorbit.exception)
set(Include_Dir ${PROJECT_SOURCE_DIR}/../../include/stationaryorbit/exception)

add_library(${AssemblyName} SHARED
    ${Include_Dir}/invalidoperation.hpp
    ${Include_Dir}/nullreference.hpp
    invalidoperation.cpp
    nullreference.cpp
)

set_property(TARGET ${AssemblyName} PROPERTY CXX_STANDARD 20)

target_include_directories(${AssemblyName} PUBLIC ${PROJECT_SOURCE_DIR}/include/stationaryorbit/exception)
