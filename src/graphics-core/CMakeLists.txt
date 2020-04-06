cmake_minimum_required(VERSION 3.0)
project(stationaryorbit CXX)

set(AssemblyName stationaryorbit.graphics-core)
set(Include_Dir ${PROJECT_SOURCE_DIR}/../../include/stationaryorbit/graphics-core)

add_library(${AssemblyName} SHARED
    ${Include_Dir}/bitmap.hpp
    ${Include_Dir}/bitmapconverter.hpp
    ${Include_Dir}/bitmapcolorconverter.hpp
    ${Include_Dir}/cmykcolor.hpp
    ${Include_Dir}/colorspace.hpp
    ${Include_Dir}/graybitmapimage.hpp
    ${Include_Dir}/graycolor.hpp
    ${Include_Dir}/image.hpp
    ${Include_Dir}/rgbbitmapimage.hpp
    ${Include_Dir}/rgbcolor.hpp
    ${Include_Dir}/yuvcolor.hpp
    ${Include_Dir}/xyzcolor.hpp
    bitmap.cpp
    color.cpp
    colorspace.cpp
    fundamental.cpp
)

set_property(TARGET ${AssemblyName} PROPERTY CXX_STANDARD 17)

target_link_libraries(${AssemblyName}
    stationaryorbit.core
)

target_include_directories(${AssemblyName} PUBLIC ${PROJECT_SOURCE_DIR}/include/stationaryorbit/graphics-core)
