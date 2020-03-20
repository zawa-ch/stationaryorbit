cmake_minimum_required(VERSION 3.0)
project(stationaryorbit CXX)

set(AssemblyName stationaryorbit.graphics-wbmp)
set(Include_Dir ${PROJECT_SOURCE_DIR}/../../include/stationaryorbit/graphics-wbmp)

add_library(${AssemblyName} SHARED
    ${Include_Dir}/ciexyz.hpp
    ${Include_Dir}/colormask.hpp
    ${Include_Dir}/fileheader.hpp
    ${Include_Dir}/invalidwbmpformatexception.hpp
    ${Include_Dir}/rgb24bmp.hpp
    ${Include_Dir}/rgbquad.hpp
    ${Include_Dir}/rgbtriple.hpp
    ${Include_Dir}/wbmpbuffer.hpp
    ${Include_Dir}/wbmpheaders.hpp
    ${Include_Dir}/wbmploader.hpp
    ${Include_Dir}/wbmpsaver.hpp
    fileheader.cpp
    invalidwbmpformatexception.cpp
    wbmpbuffer.cpp
    wbmploader.cpp
    wbmpsaver.cpp
)

set_property(TARGET ${AssemblyName} PROPERTY CXX_STANDARD 20)

target_link_libraries(${AssemblyName}
    stationaryorbit.core
    stationaryorbit.graphics-core
)

target_include_directories(${AssemblyName} PUBLIC ${PROJECT_SOURCE_DIR}/include/stationaryorbit/graphics-wbmp)
