# stationaryorbit:/CMakeLists.txt
# Copyright 2020-2021 zawa-ch.
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
cmake_minimum_required(VERSION 3.16)
project(stationaryorbit)
cmake_policy(VERSION 3.13)

enable_testing()

add_subdirectory(stationaryorbit.core)
add_subdirectory(stationaryorbit.graphics-core)
add_subdirectory(stationaryorbit.graphics-dib)
add_subdirectory(stationaryorbit.mathematics)
