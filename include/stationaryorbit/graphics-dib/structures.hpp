//	stationaryorbit/graphics-dib/structures
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
#ifndef __stationaryorbit_graphics_dib_structures__
#define __stationaryorbit_graphics_dib_structures__
#include <optional>
#include "stationaryorbit/core.bitoperation.hpp"
#include "stationaryorbit/graphics-core.color.hpp"
namespace zawa_ch::StationaryOrbit::Graphics::DIB
{
	struct RGBTriple_t
	{
		ChannelValue<Proportion8_t> Red;
		ChannelValue<Proportion8_t> Green;
		ChannelValue<Proportion8_t> Blue;
	};
	struct RGBQuad_t
	{
		ChannelValue<Proportion8_t> Red;
		ChannelValue<Proportion8_t> Green;
		ChannelValue<Proportion8_t> Blue;
		ChannelValue<Proportion8_t> Reserved;
	};
	struct CIEXYZ_t
	{
		ChannelValue<FixedPoint32q16_t> X;
		ChannelValue<FixedPoint32q16_t> Y;
		ChannelValue<FixedPoint32q16_t> Z;
	};
	struct CIEXYZTriple_t
	{
		CIEXYZ_t Red;
		CIEXYZ_t Green;
		CIEXYZ_t Blue;
	};
	struct ColorMask final
	{
		BitMask<uint32_t> RedMask;
		BitMask<uint32_t> GreenMask;
		BitMask<uint32_t> BlueMask;
		std::optional<BitMask<uint32_t>> AlphaMask;
	};
	struct DIBColorSpace
	{
		CIEXYZTriple_t Matrix;
		FixedPoint32q16_t GammaR;
		FixedPoint32q16_t GammaG;
		FixedPoint32q16_t GammaB;
	};
}
#endif // __stationaryorbit_graphics_dib_structures__
