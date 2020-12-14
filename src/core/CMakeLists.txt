# stationaryorbit:/src/core/CMakeLists.txt
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

set(AssemblyName stationaryorbit.core)
set(Include_Dir ${PROJECT_SOURCE_DIR}/../../include)

add_library(${AssemblyName} SHARED
    ${Include_Dir}/stationaryorbit/core.bitoperation.hpp
    ${Include_Dir}/stationaryorbit/core.delegate.hpp
    ${Include_Dir}/stationaryorbit/core.numeral.hpp
    ${Include_Dir}/stationaryorbit/core.property.hpp
    algorithms.cpp
    bitmask.cpp
    fixedpoint.cpp
    multiplelong.cpp
    proportion.cpp
    real.cpp
    rotation.cpp
    traits.cpp
    vector2d.cpp
)

set_property(TARGET ${AssemblyName} PROPERTY CXX_STANDARD 17)

target_link_libraries(${AssemblyName}
    stationaryorbit.exception
)
