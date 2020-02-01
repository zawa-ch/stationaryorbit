cmake_minimum_required(VERSION 3.0)
project(stationaryorbit CXX)

set(AssemblyName stationaryorbit.core)

add_library(${AssemblyName} SHARED
    bitreference.cpp
    fractionaldec.cpp
    quantumbit.cpp
    real.cpp
    rotation.cpp
    tristateboolean.cpp
    vector2d.cpp
)

set_property(TARGET ${AssemblyName} PROPERTY CXX_STANDARD 20)

target_link_libraries(${AssemblyName}
    stationaryorbit.exception
)

target_include_directories(${AssemblyName} PUBLIC ${PROJECT_SOURCE_DIR}/include/stationaryorbit/core)
