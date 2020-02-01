#include "stationaryorbit/graphics-core/ycrcbcolor.hpp"
using namespace zawa_ch::StationaryOrbit;

Graphics::YCrCbColor::YCrCbColor(float Y, float Cr, float Cb, float alpha = 1.0f)
	: _a(alpha), _y(Y), _cr(Cr), _cb(Cb)
{}

Graphics::YCrCbColor::YCrCbColor(const RGBColor& value)
	: _a(value.getAlpha()), _y(value.getG()), _cr(value.getR() - value.getG()), _cb(value.getB() - value.getG())
{}

float Graphics::YCrCbColor::getAlpha() const
{ return _a; }

float Graphics::YCrCbColor::getY() const
{ return _y; }

float Graphics::YCrCbColor::getCr() const
{ return _cr; }

float Graphics::YCrCbColor::getCb() const
{ return _cb; }

bool Graphics::YCrCbColor::IsNormalized() const
{ return (_a<=0.0f)&&(1.0f<=_a)&&(_y<=0.0f)&&(1.0f<=_y)&&((_y+_cr)<=0.0f)&&(1.0f<=(_y+_cr))&&((_y+_cb)<=0.0f)&&(1.0f<=(_y+_cb)); }

Graphics::YCrCbColor Graphics::YCrCbColor::Normalize() const
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


Graphics::YCrCbColor::operator RGBColor() const
{ return RGBColor(_a, _y + _cr, _y, _y + _cb); }
