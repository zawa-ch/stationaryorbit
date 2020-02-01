cmake_minimum_required(VERSION 3.0)
project(stationaryorbit CXX)

set(AssemblyName stationaryorbit.graphics-wbmp)

add_library(${AssemblyName} SHARED
    bmpimage.cpp
    bmpimagebitmap.cpp
    bmpimageinfomation.cpp
    coreheader.cpp
    fileheader.cpp
    infoheader.cpp
    invalidformatexception.cpp
    rgb24bmp.cpp
)

set_property(TARGET ${AssemblyName} PROPERTY CXX_STANDARD 20)

target_link_libraries(${AssemblyName}
    stationaryorbit.core
    stationaryorbit.graphics-core
)

target_include_directories(${AssemblyName} PUBLIC ${PROJECT_SOURCE_DIR}/include/stationaryorbit/graphics-wbmp)
