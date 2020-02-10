cmake_minimum_required(VERSION 3.0)
project(stationaryorbit CXX)

set(AssemblyName stationaryorbit.analysis)
set(Include_Dir ${PROJECT_SOURCE_DIR}/../../include/stationaryorbit/analysis)

add_library(${AssemblyName} SHARED
    ${Include_Dir}/compensatedfloat.hpp
    ${Include_Dir}/crispset.hpp
    ${Include_Dir}/differencial.hpp
    ${Include_Dir}/fuzzybool.hpp
    ${Include_Dir}/fuzzyreasoning.hpp
    ${Include_Dir}/fuzzyrelation.hpp
    ${Include_Dir}/fuzzyset.hpp
    ${Include_Dir}/integral.hpp
    ${Include_Dir}/mathematicfunction.hpp
    ${Include_Dir}/midpointintegral.hpp
    ${Include_Dir}/newtoncoef.hpp
    ${Include_Dir}/polynomialfunction.hpp
    ${Include_Dir}/simpsonintegral.hpp
    ${Include_Dir}/taylorseries.hpp
    ${Include_Dir}/trapeziumintegral.hpp
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
