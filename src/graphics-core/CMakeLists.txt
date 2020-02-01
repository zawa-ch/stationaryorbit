cmake_minimum_required(VERSION 3.0)
project(stationaryorbit CXX)

set(AssemblyName stationaryorbit.graphics-core)

add_library(${AssemblyName} SHARED
    bitmap.cpp
    bitmapbuffer.cpp
    bitmapbytebuffer.cpp
    bitmappixelgetter.cpp
    bitmappixelreference.cpp
    bitmappixelsetter.cpp
    bitmapsimpleconvert.cpp
    graphicscore.cpp
    imageinfomation.cpp
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
