cmake_minimum_required(VERSION 3.0)
project(stationaryorbit CXX)

set(AssemblyName stationaryorbit.core)
set(Include_Dir ${PROJECT_SOURCE_DIR}/../../include/stationaryorbit/core)

add_library(${AssemblyName} SHARED
    ${Include_Dir}/bitreference.hpp
    ${Include_Dir}/delegate.hpp
    ${Include_Dir}/endians.hpp
    ${Include_Dir}/fractionaldec.hpp
    ${Include_Dir}/real.hpp
    ${Include_Dir}/rotation.hpp
    ${Include_Dir}/vector2d.hpp
    real.cpp
    rotation.cpp
    vector2d.cpp
)

set_property(TARGET ${AssemblyName} PROPERTY CXX_STANDARD 17)

target_link_libraries(${AssemblyName}
    stationaryorbit.exception
)
