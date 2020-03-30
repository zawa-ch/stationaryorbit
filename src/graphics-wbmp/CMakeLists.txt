cmake_minimum_required(VERSION 3.0)
project(stationaryorbit CXX)

set(AssemblyName stationaryorbit.graphics-wbmp)
set(Include_Dir ${PROJECT_SOURCE_DIR}/../../include/stationaryorbit/graphics-wbmp)

add_library(${AssemblyName} SHARED
    ${Include_Dir}/ciexyz.hpp
    ${Include_Dir}/colormask.hpp
    ${Include_Dir}/dibbitmap.hpp
    ${Include_Dir}/dibheaders.hpp
    ${Include_Dir}/fileheader.hpp
    ${Include_Dir}/invaliddibformat.hpp
    ${Include_Dir}/rgbquad.hpp
    ${Include_Dir}/rgbtriple.hpp
    dibbitmap.cpp
    fileheader.cpp
    invaliddibformat.cpp
)

set_property(TARGET ${AssemblyName} PROPERTY CXX_STANDARD 20)

target_link_libraries(${AssemblyName}
    stationaryorbit.core
    stationaryorbit.graphics-core
)

target_include_directories(${AssemblyName} PUBLIC ${PROJECT_SOURCE_DIR}/include/stationaryorbit/graphics-wbmp)
