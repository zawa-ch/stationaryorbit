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
#include <cstdint>
#include <optional>
#include "stationaryorbit/core.bitoperation.hpp"
namespace zawa_ch::StationaryOrbit::Graphics::DIB
{
	struct RGBTriple_t
	{
		uint8_t Red;
		uint8_t Green;
		uint8_t Blue;
	};
	struct RGBQuad_t
	{
		uint8_t Red;
		uint8_t Green;
		uint8_t Blue;
		uint8_t Reserved;
	};
	struct CIEXYZ_t
	{
		uint32_t X;
		uint32_t Y;
		uint32_t Z;
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
		uint32_t GammaR;
		uint32_t GammaG;
		uint32_t GammaB;
	};
}
#endif // __stationaryorbit_graphics_dib_structures__
