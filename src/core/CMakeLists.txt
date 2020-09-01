cmake_minimum_required(VERSION 3.0)
project(stationaryorbit CXX)

set(AssemblyName stationaryorbit.core)
set(Include_Dir ${PROJECT_SOURCE_DIR}/../../include)

add_library(${AssemblyName} SHARED
    ${Include_Dir}/stationaryorbit/core.bitoperation.hpp
    ${Include_Dir}/stationaryorbit/core.delegate.hpp
    ${Include_Dir}/stationaryorbit/core.numeral.hpp
    ${Include_Dir}/stationaryorbit/core.property.hpp
    fixedpoint.cpp
    proportion.cpp
    real.cpp
    rotation.cpp
    vector2d.cpp
)

set_property(TARGET ${AssemblyName} PROPERTY CXX_STANDARD 17)

target_link_libraries(${AssemblyName}
    stationaryorbit.exception
)
