#include "stationaryorbit/graphics-core/colorspace.hpp"
using namespace zawa_ch::StationaryOrbit::Graphics;

const XYZMatrixRGBColorSpace ColorSpace::sRGB =
XYZMatrixRGBColorSpace
(
	XYZColor(0.6069f, 0.2989f, 0.0000f),
	XYZColor(0.1735f, 0.5866f, 0.0661f),
	XYZColor(0.2003f, 0.1144f, 1.1157f)
);

XYZMatrixRGBColorSpace::XYZMatrixRGBColorSpace() : _r(), _g(), _b() {}
XYZMatrixRGBColorSpace::XYZMatrixRGBColorSpace(const XYZColor& redpoint, const XYZColor& greenpoint, const XYZColor& bluepoint)
	: _r(redpoint), _g(greenpoint), _b(bluepoint)
{}
XYZColor XYZMatrixRGBColorSpace::ConvertXYZ(const RGBColor& color) const
{
	return XYZColor
	(
		color.R() * _r.X() + color.G() * _g.X() + color.B() * _b.X(),
		color.R() * _r.Y() + color.G() * _g.Y() + color.B() * _b.Y(),
		color.R() * _r.Z() + color.G() * _g.Z() + color.B() * _b.Z()
	);
}
std::unique_ptr<RGBColorSpace> XYZMatrixRGBColorSpace::Clone() const
{
	return std::unique_ptr<RGBColorSpace>(new XYZMatrixRGBColorSpace(*this));
}
RGBMatrixXYZColorSpace XYZMatrixRGBColorSpace::Invert() const
{
	float factor = (_r.X() * _g.Y() * _b.Z()) + (_g.X() * _b.Y() * _r.Z()) + (_b.X() * _r.Y() * _g.Z()) - (_r.X() * _b.Y() * _g.Z()) - (_g.X() * _r.Y() * _b.Z()) - (_b.X() * _g.Y() * _r.Z());
	auto x = RGBColor((_g.Y() * _b.Z() - _g.Z() * _b.Y()) / factor, -(_r.Y() * _b.Z() - _r.Z() * _b.Y()) / factor, (_r.Y() * _g.Z() - _r.Z() * _g.Y()) / factor);
	auto y = RGBColor(-(_g.X() * _b.Z() - _g.Z() * _b.X()) / factor, (_r.X() * _b.Z() - _r.Z() * _b.X()) / factor, -(_r.X() * _g.Z() - _r.Z() * _g.X()) / factor);
	auto z = RGBColor((_g.X() * _b.Y() - _g.Y() * _b.X()) / factor, -(_r.X() * _b.Y() - _r.Y() * _b.X()) / factor, (_r.X() * _g.Y() - _r.Y() * _g.X()) / factor);
	return RGBMatrixXYZColorSpace(x, y, z);
}
bool XYZMatrixRGBColorSpace::Equals(const XYZMatrixRGBColorSpace& other) const
{
	return (_r == other._r)&&(_g == other._g)&&(_b == other._b);
}

RGBMatrixXYZColorSpace::RGBMatrixXYZColorSpace() : _x(), _y(), _z() {}
RGBMatrixXYZColorSpace::RGBMatrixXYZColorSpace(const RGBColor& xpoint, const RGBColor& ypoint, const RGBColor& zpoint)
	: _x(xpoint), _y(ypoint), _z(zpoint)
{}
RGBColor RGBMatrixXYZColorSpace::ConvertRGB(const XYZColor& color) const
{
	return RGBColor
	(
		color.X() * _x.R() + color.Y() * _y.R() + color.Z() * _z.R(),
		color.X() * _x.G() + color.Y() * _y.G() + color.Z() * _z.G(),
		color.X() * _x.B() + color.Y() * _y.B() + color.Z() * _z.B()
	);
}
std::unique_ptr<RGBInvertedColorSpace> RGBMatrixXYZColorSpace::Clone() const
{
	return std::unique_ptr<RGBInvertedColorSpace>(new RGBMatrixXYZColorSpace(*this));
}
XYZMatrixRGBColorSpace RGBMatrixXYZColorSpace::Invert() const
{
	float factor = (_x.R() * _y.G() * _z.B()) + (_y.R() * _z.G() * _x.B()) + (_z.R() * _x.G() * _y.B()) - (_x.R() * _z.G() * _y.B()) - (_y.R() * _x.G() * _z.B()) - (_z.R() * _y.G() * _x.B());
	auto r = XYZColor((_y.G() * _z.B() - _y.B() * _z.G()) / factor, -(_x.G() * _z.B() - _x.B() * _z.G()) / factor, (_x.G() * _y.B() - _x.B() * _y.G()) / factor);
	auto g = XYZColor(-(_y.R() * _z.B() - _y.B() * _z.R()) / factor, (_x.R() * _z.B() - _x.B() * _z.R()) / factor, -(_x.R() * _y.B() - _x.B() * _y.R()) / factor);
	auto b = XYZColor((_y.R() * _z.G() - _y.G() * _z.R()) / factor, -(_x.R() * _z.G() - _x.G() * _z.R()) / factor, (_x.R() * _y.G() - _x.G() * _y.R()) / factor);
	return XYZMatrixRGBColorSpace(r, g, b);
}
bool RGBMatrixXYZColorSpace::Equals(const RGBMatrixXYZColorSpace& other) const
{
	return (_x == other._x)&&(_y == other._y)&&(_z == other._z);
}
