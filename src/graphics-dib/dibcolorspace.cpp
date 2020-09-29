//	stationaryorbit.graphics-dib:/dibcolorspace
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
#include "stationaryorbit/graphics-dib/dibcolorspace.hpp"
using namespace zawa_ch::StationaryOrbit::Graphics::DIB;

DIBColorSpace::operator XYZMatrixRGBColorSpace() const
{
    return XYZMatrixRGBColorSpace(
        XYZColor(float(Matrix.Red.X) / 0x1.p30, float(Matrix.Red.Y) / 0x1.p30, float(Matrix.Red.Z) / 0x1.p30),
        XYZColor(float(Matrix.Green.X) / 0x1.p30, float(Matrix.Green.Y) / 0x1.p30, float(Matrix.Green.Z) / 0x1.p30),
        XYZColor(float(Matrix.Blue.X) / 0x1.p30, float(Matrix.Blue.Y) / 0x1.p30, float(Matrix.Blue.Z) / 0x1.p30),
        RGBColor(float(GammaR) / 0x1.p16, float(GammaG) / 0x1.p16, float(GammaB) / 0x1.p16)
    );
}
DIBColorSpace DIBColorSpace::FromXYZMatrixRGBColorSpace(const XYZMatrixRGBColorSpace& value)
{
    return DIBColorSpace
    {
        {
            { uint32_t(value.RedPoint().X() * 0x1.p30), uint32_t(value.RedPoint().Y() * 0x1.p30), uint32_t(value.RedPoint().Z() * 0x1.p30) },
            { uint32_t(value.GreenPoint().X() * 0x1.p30), uint32_t(value.GreenPoint().Y() * 0x1.p30), uint32_t(value.GreenPoint().Z() * 0x1.p30) },
            { uint32_t(value.BluePoint().X() * 0x1.p30), uint32_t(value.BluePoint().Y() * 0x1.p30), uint32_t(value.BluePoint().Z() * 0x1.p30) }
        },
        uint32_t(value.Gamma().R() * 0x1.p16),
        uint32_t(value.Gamma().G() * 0x1.p16),
        uint32_t(value.Gamma().B() * 0x1.p16)
    };
}
