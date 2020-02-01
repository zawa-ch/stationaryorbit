cmake_minimum_required(VERSION 3.0)
project(stationaryorbit CXX)

set(AssemblyName stationaryorbit.analysis)

add_library(${AssemblyName} SHARED
    compensatedfloat.cpp
    differencial.cpp
    midpointintegral.cpp
    newtoncoef.cpp
    polynomialfunction.cpp
    simpsonintegral.cpp
    taylorseries.cpp
    trapeziumintegral.cpp
)

set_property(TARGET ${AssemblyName} PROPERTY CXX_STANDARD 20)

target_link_libraries(${AssemblyName}
    stationaryorbit.core
    stationaryorbit.exception
)

target_include_directories(${AssemblyName} PUBLIC ${PROJECT_SOURCE_DIR}/include/stationaryorbit/analysis)