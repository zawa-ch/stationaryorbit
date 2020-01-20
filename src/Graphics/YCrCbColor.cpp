#include "Graphics/Structure/YCrCbColor.hpp"

StationaryOrbit::Graphics::YCrCbColor::YCrCbColor(float Y, float Cr, float Cb, float alpha = 1.0f)
	: _a(alpha), _y(Y), _cr(Cr), _cb(Cb)
{}

StationaryOrbit::Graphics::YCrCbColor::YCrCbColor(const RGBColor& value)
	: _a(value.getAlpha()), _y(value.getG()), _cr(value.getR() - value.getG()), _cb(value.getB() - value.getG())
{}

float StationaryOrbit::Graphics::YCrCbColor::getAlpha() const
{ return _a; }

float StationaryOrbit::Graphics::YCrCbColor::getY() const
{ return _y; }

float StationaryOrbit::Graphics::YCrCbColor::getCr() const
{ return _cr; }

float StationaryOrbit::Graphics::YCrCbColor::getCb() const
{ return _cb; }

bool StationaryOrbit::Graphics::YCrCbColor::IsNormalized() const
{ return (_a<=0.0f)&&(1.0f<=_a)&&(_y<=0.0f)&&(1.0f<=_y)&&((_y+_cr)<=0.0f)&&(1.0f<=(_y+_cr))&&((_y+_cb)<=0.0f)&&(1.0f<=(_y+_cb)); }

StationaryOrbit::Graphics::YCrCbColor StationaryOrbit::Graphics::YCrCbColor::Normalize() const
{
	float A = _a;
	A = (0.0f <= A)?(A):(0.0f);
	A = (A <= 1.0f)?(A):(1.0f);
	float Y = _y;
	Y = (0.0f <= Y)?(Y):(0.0f);
	Y = (Y <= 1.0f)?(Y):(1.0f);
	float Cr = _cr;
	Cr = ((0.0f-Y) <= Cr)?(Cr):(0.0f-Y);
	Cr = (Cr <= (1.0f-Y))?(Cr):(1.0f-Y);
	float Cb = _cb;
	Cb = ((0.0f-Y) <= Cb)?(Cb):(0.0f-Y);
	Cb = (Cb <= (1.0f-Y))?(Cb):(1.0f-Y);
	return YCrCbColor(Y, Cr, Cb, A);
}


StationaryOrbit::Graphics::YCrCbColor::operator RGBColor() const
{ return RGBColor(_a, _y + _cr, _y, _y + _cb); }
