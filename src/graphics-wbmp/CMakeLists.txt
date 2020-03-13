cmake_minimum_required(VERSION 3.0)
project(stationaryorbit CXX)

set(AssemblyName stationaryorbit.graphics-wbmp)
set(Include_Dir ${PROJECT_SOURCE_DIR}/../../include/stationaryorbit/graphics-wbmp)

add_library(${AssemblyName} SHARED
    ${Include_Dir}/bmpimage.hpp
    ${Include_Dir}/bmpimagebitmap.hpp
    ${Include_Dir}/bmpimageinfomation.hpp
    ${Include_Dir}/ciexyz_t.hpp
    ${Include_Dir}/ciexyztriple_t.hpp
    ${Include_Dir}/coreheader.hpp
    ${Include_Dir}/fileheader.hpp
    ${Include_Dir}/infoheader.hpp
    ${Include_Dir}/invalidformatexception.hpp
    ${Include_Dir}/rgb24bmp.hpp
    ${Include_Dir}/v4header.hpp
    ${Include_Dir}/v5header.hpp
    ${Include_Dir}/wbmpbuffer.hpp
    bmpimage.cpp
    bmpimagebitmap.cpp
    bmpimageinfomation.cpp
    coreheader.cpp
    fileheader.cpp
    infoheader.cpp
    invalidwbmpformatexception.cpp
    rgb24bmp.cpp
    wbmpbuffer.cpp
)

set_property(TARGET ${AssemblyName} PROPERTY CXX_STANDARD 20)

target_link_libraries(${AssemblyName}
    stationaryorbit.core
    stationaryorbit.graphics-core
)

target_include_directories(${AssemblyName} PUBLIC ${PROJECT_SOURCE_DIR}/include/stationaryorbit/graphics-wbmp)
