cmake_minimum_required(VERSION 3.0)
project(stationaryorbit CXX)

set(AssemblyName stationaryorbit.graphics-core)
set(Include_Dir ${PROJECT_SOURCE_DIR}/../../include/stationaryorbit/graphics-core)

add_library(${AssemblyName} SHARED
    ${Include_Dir}/bitmap.hpp
    ${Include_Dir}/bitmapbuffer.hpp
    ${Include_Dir}/bitmapsimpleconvert.hpp
    ${Include_Dir}/bufferbindbitmap.hpp
    ${Include_Dir}/bufferedbitmap.hpp
    ${Include_Dir}/channelvalue.hpp
    ${Include_Dir}/cmykcolor.hpp
    ${Include_Dir}/pixelreference.hpp
    ${Include_Dir}/point.hpp
    ${Include_Dir}/pointf.hpp
    ${Include_Dir}/rectangle.hpp
    ${Include_Dir}/rectanglef.hpp
    ${Include_Dir}/rgbcolor.hpp
    ${Include_Dir}/ycrcbcolor.hpp
    point.cpp
    pointf.cpp
    rectangle.cpp
    rectanglef.cpp
    rgbcolor.cpp
    ycrcbcolor.cpp
)

set_property(TARGET ${AssemblyName} PROPERTY CXX_STANDARD 20)

target_link_libraries(${AssemblyName}
    stationaryorbit.core
)

target_include_directories(${AssemblyName} PUBLIC ${PROJECT_SOURCE_DIR}/include/stationaryorbit/graphics-core)
