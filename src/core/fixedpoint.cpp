//	stationaryorbit.core:/fixedpoint
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
#include "stationaryorbit/core/fixedpoint.hpp"
using namespace zawa_ch::StationaryOrbit;

template class zawa_ch::StationaryOrbit::FixedPoint<uint8_t, 7>;
template class zawa_ch::StationaryOrbit::FixedPoint<uint16_t, 8>;
template class zawa_ch::StationaryOrbit::FixedPoint<uint16_t, 15>;
template class zawa_ch::StationaryOrbit::FixedPoint<uint32_t, 16>;
template class zawa_ch::StationaryOrbit::FixedPoint<uint32_t, 31>;
template class zawa_ch::StationaryOrbit::FixedPoint<uint64_t, 32>;
template class zawa_ch::StationaryOrbit::FixedPoint<uint64_t, 63>;
