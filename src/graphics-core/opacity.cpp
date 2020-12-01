//	stationaryorbit.graphics-core:/opacity
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
#include "stationaryorbit/graphics-core/opacity.hpp"

template struct
zawa_ch::StationaryOrbit::Graphics::Opacity<zawa_ch::StationaryOrbit::Proportion1_t>;
template struct
zawa_ch::StationaryOrbit::Graphics::Opacity<zawa_ch::StationaryOrbit::Proportion8_t>;
template struct
zawa_ch::StationaryOrbit::Graphics::Opacity<zawa_ch::StationaryOrbit::Proportion16_t>;
template struct
zawa_ch::StationaryOrbit::Graphics::Opacity<zawa_ch::StationaryOrbit::Proportion32_t>;
template struct
zawa_ch::StationaryOrbit::Graphics::Opacity<zawa_ch::StationaryOrbit::Proportion64_t>;
template struct
zawa_ch::StationaryOrbit::Graphics::Opacity<zawa_ch::StationaryOrbit::FixedPoint16q15_t>;
template struct
zawa_ch::StationaryOrbit::Graphics::Opacity<zawa_ch::StationaryOrbit::FixedPoint32q31_t>;
template struct
zawa_ch::StationaryOrbit::Graphics::Opacity<zawa_ch::StationaryOrbit::FixedPoint64q63_t>;
template struct
zawa_ch::StationaryOrbit::Graphics::Opacity<float>;
template struct
zawa_ch::StationaryOrbit::Graphics::Opacity<double>;
