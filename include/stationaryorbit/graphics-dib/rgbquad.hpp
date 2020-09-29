//	stationaryorbit/graphics-dib/rgbquad
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
#ifndef __stationaryorbit_graphics_dib_rgbquad__
#define __stationaryorbit_graphics_dib_rgbquad__
#include <cstdint>
namespace zawa_ch::StationaryOrbit::Graphics::DIB
{

    struct RGBQuad_t
    {
        uint8_t Red;
        uint8_t Green;
        uint8_t Blue;
        uint8_t Reserved;
    };

}
#endif // __stationaryorbit_graphics_dib_rgbquad__