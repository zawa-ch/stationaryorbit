//	stationaryorbit.core:/rectanglesize
//	Copyright 2020 zawa-ch.
//	GPLv3 (or later) license
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//	See the GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program.
//	If not, see <http://www.gnu.org/licenses/>.
//
#include "stationaryorbit/core/rectanglesize.hpp"
using namespace zawa_ch::StationaryOrbit;

template struct
zawa_ch::StationaryOrbit::Rect2DSize<uint8_t>;
template struct
zawa_ch::StationaryOrbit::Rect2DSize<uint16_t>;
template struct
zawa_ch::StationaryOrbit::Rect2DSize<uint32_t>;
template struct
zawa_ch::StationaryOrbit::Rect2DSize<uint64_t>;
template struct
zawa_ch::StationaryOrbit::Rect2DSize<int8_t>;
template struct
zawa_ch::StationaryOrbit::Rect2DSize<int16_t>;
template struct
zawa_ch::StationaryOrbit::Rect2DSize<int32_t>;
template struct
zawa_ch::StationaryOrbit::Rect2DSize<int64_t>;
template struct
zawa_ch::StationaryOrbit::Rect2DSize<float>;
template struct
zawa_ch::StationaryOrbit::Rect2DSize<double>;
