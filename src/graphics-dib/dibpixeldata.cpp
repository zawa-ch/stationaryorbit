//	stationaryorbit.graphics-dib:/dibpixeldata
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
#include "stationaryorbit/graphics-dib/dibpixeldata.hpp"
using namespace zawa_ch::StationaryOrbit::Graphics::DIB;

template struct
zawa_ch::StationaryOrbit::Graphics::DIB::DIBPixelData<zawa_ch::StationaryOrbit::Graphics::DIB::BitDepth::Bit1>;
template struct
zawa_ch::StationaryOrbit::Graphics::DIB::DIBPixelData<zawa_ch::StationaryOrbit::Graphics::DIB::BitDepth::Bit4>;
template struct
zawa_ch::StationaryOrbit::Graphics::DIB::DIBPixelData<zawa_ch::StationaryOrbit::Graphics::DIB::BitDepth::Bit8>;
template struct
zawa_ch::StationaryOrbit::Graphics::DIB::DIBPixelData<zawa_ch::StationaryOrbit::Graphics::DIB::BitDepth::Bit16>;
template struct
zawa_ch::StationaryOrbit::Graphics::DIB::DIBPixelData<zawa_ch::StationaryOrbit::Graphics::DIB::BitDepth::Bit24>;
template struct
zawa_ch::StationaryOrbit::Graphics::DIB::DIBPixelData<zawa_ch::StationaryOrbit::Graphics::DIB::BitDepth::Bit32>;

static_assert(sizeof(DIBPixelData<BitDepth::Bit1>) == 1, "sizeof(DIBPixelData<BitDepth::Bit1>) が 1 ではありません。");
static_assert(sizeof(DIBPixelData<BitDepth::Bit4>) == 1, "sizeof(DIBPixelData<BitDepth::Bit4>) が 1 ではありません。");
static_assert(sizeof(DIBPixelData<BitDepth::Bit8>) == 1, "sizeof(DIBPixelData<BitDepth::Bit8>) が 1 ではありません。");
static_assert(sizeof(DIBPixelData<BitDepth::Bit16>) == 2, "sizeof(DIBPixelData<BitDepth::Bit16>) が 2 ではありません。");
static_assert(sizeof(DIBPixelData<BitDepth::Bit24>) == 3, "sizeof(DIBPixelData<BitDepth::Bit24>) が 3 ではありません。");
static_assert(sizeof(DIBPixelData<BitDepth::Bit32>) == 4, "sizeof(DIBPixelData<BitDepth::Bit32>) が 4 ではありません。");
