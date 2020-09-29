# stationaryorbit:/src/mathematics/CMakeLists.txt
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

set(AssemblyName stationaryorbit.mathematics)
set(Include_Dir ${PROJECT_SOURCE_DIR}/../../include/stationaryorbit/mathematics)

add_library(${AssemblyName} SHARED
    ${Include_Dir}/compensatedfloat.hpp
    ${Include_Dir}/crispset.hpp
    ${Include_Dir}/differencial.hpp
    ${Include_Dir}/fuzzybool.hpp
    ${Include_Dir}/fuzzyreasoning.hpp
    ${Include_Dir}/fuzzyrelation.hpp
    ${Include_Dir}/fuzzyset.hpp
    ${Include_Dir}/integral.hpp
    ${Include_Dir}/mathematicfunction.hpp
    ${Include_Dir}/newtoncoef.hpp
    ${Include_Dir}/polynomialfunction.hpp
    ${Include_Dir}/taylorseries.hpp
    differencial.cpp
    fuzzybool.cpp
    integral.cpp
    newtoncoef.cpp
    polynomialfunction.cpp
    taylorseries.cpp
)

set_property(TARGET ${AssemblyName} PROPERTY CXX_STANDARD 17)

target_link_libraries(${AssemblyName}
    stationaryorbit.core
    stationaryorbit.exception
)
