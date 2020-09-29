//	stationaryorbit.graphics-core:/colorspace
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
#include "stationaryorbit/graphics-core/colorspace.hpp"
#include <cmath>
using namespace zawa_ch::StationaryOrbit::Graphics;

const XYZMatrixRGBColorSpace ColorSpace::sRGB =
XYZMatrixRGBColorSpace
(
	XYZColor(0.6069f, 0.2989f, 0.0000f),
	XYZColor(0.1735f, 0.5866f, 0.0661f),
	XYZColor(0.2003f, 0.1144f, 1.1157f),
	RGBColor(1.f, 1.f, 1.f)
);

XYZMatrixRGBColorSpace::XYZMatrixRGBColorSpace() : _r(), _g(), _b() {}
XYZMatrixRGBColorSpace::XYZMatrixRGBColorSpace(const XYZColor& redpoint, const XYZColor& greenpoint, const XYZColor& bluepoint, const RGBColor& gamma)
	: _r(redpoint), _g(greenpoint), _b(bluepoint), _gamma(gamma)
{}
XYZColor XYZMatrixRGBColorSpace::ConvertXYZ(const RGBColor& color) const
{
	auto r = powf(color.R(), _gamma.R());
	auto g = powf(color.G(), _gamma.G());
	auto b = powf(color.B(), _gamma.B());
	return XYZColor
	(
		r * _r.X() + g * _g.X() + b * _b.X(),
		r * _r.Y() + g * _g.Y() + b * _b.Y(),
		r * _r.Z() + g * _g.Z() + b * _b.Z()
	);
}
std::unique_ptr<RGBColorSpace> XYZMatrixRGBColorSpace::Clone() const
{
	return std::unique_ptr<RGBColorSpace>(new XYZMatrixRGBColorSpace(*this));
}
XYZColor& XYZMatrixRGBColorSpace::RedPoint() { return _r; }
const XYZColor& XYZMatrixRGBColorSpace::RedPoint() const { return _r; }
XYZColor& XYZMatrixRGBColorSpace::GreenPoint() { return _g; }
const XYZColor& XYZMatrixRGBColorSpace::GreenPoint() const { return _g; }
XYZColor& XYZMatrixRGBColorSpace::BluePoint() { return _b; }
const XYZColor& XYZMatrixRGBColorSpace::BluePoint() const { return _b; }
RGBColor& XYZMatrixRGBColorSpace::Gamma() { return _gamma; }
const RGBColor& XYZMatrixRGBColorSpace::Gamma() const { return _gamma; }
RGBMatrixXYZColorSpace XYZMatrixRGBColorSpace::Invert() const
{
	float factor = (_r.X() * _g.Y() * _b.Z()) + (_g.X() * _b.Y() * _r.Z()) + (_b.X() * _r.Y() * _g.Z()) - (_r.X() * _b.Y() * _g.Z()) - (_g.X() * _r.Y() * _b.Z()) - (_b.X() * _g.Y() * _r.Z());
	auto x = RGBColor((_g.Y() * _b.Z() - _g.Z() * _b.Y()) / factor, -(_r.Y() * _b.Z() - _r.Z() * _b.Y()) / factor, (_r.Y() * _g.Z() - _r.Z() * _g.Y()) / factor);
	auto y = RGBColor(-(_g.X() * _b.Z() - _g.Z() * _b.X()) / factor, (_r.X() * _b.Z() - _r.Z() * _b.X()) / factor, -(_r.X() * _g.Z() - _r.Z() * _g.X()) / factor);
	auto z = RGBColor((_g.X() * _b.Y() - _g.Y() * _b.X()) / factor, -(_r.X() * _b.Y() - _r.Y() * _b.X()) / factor, (_r.X() * _g.Y() - _r.Y() * _g.X()) / factor);
	return RGBMatrixXYZColorSpace(x, y, z, RGBColor(1.f/_gamma.R(), 1.f/_gamma.G(), 1.f/_gamma.B()));
}
bool XYZMatrixRGBColorSpace::Equals(const XYZMatrixRGBColorSpace& other) const
{
	return (_r == other._r)&&(_g == other._g)&&(_b == other._b)&&(_gamma == other._gamma);
}

RGBMatrixXYZColorSpace::RGBMatrixXYZColorSpace() : _x(), _y(), _z() {}
RGBMatrixXYZColorSpace::RGBMatrixXYZColorSpace(const RGBColor& xpoint, const RGBColor& ypoint, const RGBColor& zpoint, const RGBColor& gamma)
	: _x(xpoint), _y(ypoint), _z(zpoint), _gamma(gamma)
{}
RGBColor RGBMatrixXYZColorSpace::ConvertRGB(const XYZColor& color) const
{
	return RGBColor
	(
		powf(color.X() * _x.R() + color.Y() * _y.R() + color.Z() * _z.R(), _gamma.R()),
		powf(color.X() * _x.G() + color.Y() * _y.G() + color.Z() * _z.G(), _gamma.G()),
		powf(color.X() * _x.B() + color.Y() * _y.B() + color.Z() * _z.B(), _gamma.B())
	);
}
std::unique_ptr<RGBInvertedColorSpace> RGBMatrixXYZColorSpace::Clone() const
{
	return std::unique_ptr<RGBInvertedColorSpace>(new RGBMatrixXYZColorSpace(*this));
}
RGBColor& RGBMatrixXYZColorSpace::XPoint() { return _x; }
const RGBColor& RGBMatrixXYZColorSpace::XPoint() const { return _x; }
RGBColor& RGBMatrixXYZColorSpace::YPoint() { return _y; }
const RGBColor& RGBMatrixXYZColorSpace::YPoint() const { return _y; }
RGBColor& RGBMatrixXYZColorSpace::ZPoint() { return _z; }
const RGBColor& RGBMatrixXYZColorSpace::ZPoint() const { return _z; }
RGBColor& RGBMatrixXYZColorSpace::Gamma() { return _gamma; }
const RGBColor& RGBMatrixXYZColorSpace::Gamma() const { return _gamma; }
XYZMatrixRGBColorSpace RGBMatrixXYZColorSpace::Invert() const
{
	float factor = (_x.R() * _y.G() * _z.B()) + (_y.R() * _z.G() * _x.B()) + (_z.R() * _x.G() * _y.B()) - (_x.R() * _z.G() * _y.B()) - (_y.R() * _x.G() * _z.B()) - (_z.R() * _y.G() * _x.B());
	auto r = XYZColor((_y.G() * _z.B() - _y.B() * _z.G()) / factor, -(_x.G() * _z.B() - _x.B() * _z.G()) / factor, (_x.G() * _y.B() - _x.B() * _y.G()) / factor);
	auto g = XYZColor(-(_y.R() * _z.B() - _y.B() * _z.R()) / factor, (_x.R() * _z.B() - _x.B() * _z.R()) / factor, -(_x.R() * _y.B() - _x.B() * _y.R()) / factor);
	auto b = XYZColor((_y.R() * _z.G() - _y.G() * _z.R()) / factor, -(_x.R() * _z.G() - _x.G() * _z.R()) / factor, (_x.R() * _y.G() - _x.G() * _y.R()) / factor);
	return XYZMatrixRGBColorSpace(r, g, b, RGBColor(1.f/_gamma.R(), 1.f/_gamma.G(), 1.f/_gamma.B()));
}
bool RGBMatrixXYZColorSpace::Equals(const RGBMatrixXYZColorSpace& other) const
{
	return (_x == other._x)&&(_y == other._y)&&(_z == other._z)&&(_gamma == other._gamma);
}
