//	stationaryorbit/graphics-dib/dibcolorspace
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
#ifndef __stationaryorbit_graphics_dib_dibcolorspace__
#define __stationaryorbit_graphics_dib_dibcolorspace__
#include "stationaryorbit/graphics-core.colorspace.hpp"
#include "ciexyz.hpp"
namespace zawa_ch::StationaryOrbit::Graphics::DIB
{
	struct DIBColorSpace
	{
		CIEXYZTriple_t Matrix;
		uint32_t GammaR;
		uint32_t GammaG;
		uint32_t GammaB;

		explicit operator XYZMatrixRGBColorSpace() const;
		static DIBColorSpace FromXYZMatrixRGBColorSpace(const XYZMatrixRGBColorSpace& value);
	};
}
#endif // __stationaryorbit_graphics_dib_dibcolorspace__