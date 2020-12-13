# stationaryorbit:/test/core/CMakeLists.txt
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

#アセンブリ名
set(AssemblyName stationaryorbit.test.core)

# 依存するライブラリ
set(DEPENDS_LIB)
set(DEPENDS_LIB ${DEPENDS_LIB} stationaryorbit.core)

# ビルドするソースファイル
set(BUILD_SOURCES)
set(BUILD_SOURCES ${BUILD_SOURCES} bitoperation.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} delegate.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} iteration.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} numeral.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} property.cpp)
set(BUILD_SOURCES ${BUILD_SOURCES} test-general.cpp)

# ビルドおよびリンク
add_executable(${AssemblyName} ${BUILD_SOURCES})
set_property(TARGET ${AssemblyName} PROPERTY CXX_STANDARD 17)
target_link_libraries(${AssemblyName} ${DEPENDS_LIB})
