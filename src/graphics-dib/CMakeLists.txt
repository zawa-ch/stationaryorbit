# stationaryorbit:/src/graphics-dib/CMakeLists.txt
# Copyright 2020 zawa-ch.
# GPLv3 (or later) license
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# any later version.
#
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.
# If not, see <http://www.gnu.org/licenses/>.
#
cmake_minimum_required(VERSION 3.0)
project(stationaryorbit CXX)

set(AssemblyName stationaryorbit.graphics-dib)
set(Include_Dir ${PROJECT_SOURCE_DIR}/../../include/stationaryorbit/graphics-dib)

add_library(${AssemblyName} SHARED
    ${Include_Dir}/dibheaders.hpp
    ${Include_Dir}/dibloader.hpp
    ${Include_Dir}/invaliddibformat.hpp
    dibcorebitmap.cpp
    dibheaders.cpp
    dibinfobitmap.cpp
    dibloader.cpp
    dibpixeldata.cpp
    dibv4bitmap.cpp
    invaliddibformat.cpp
    rgbdecoder.cpp
)

set_property(TARGET ${AssemblyName} PROPERTY CXX_STANDARD 17)

target_link_libraries(${AssemblyName}
    stationaryorbit.core
    stationaryorbit.graphics-core
)

target_include_directories(${AssemblyName} PUBLIC ${PROJECT_SOURCE_DIR}/include/stationaryorbit/graphics-dib)
