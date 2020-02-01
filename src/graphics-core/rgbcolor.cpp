#include "Graphics/Structure/RGBColor.hpp"

StationaryOrbit::Graphics::RGBColor::RGBColor(float r, float g, float b, float alpha = 1.0f)
	: _a(alpha), _r(r), _g(g), _b(b)
{}

float StationaryOrbit::Graphics::RGBColor::getAlpha() const
{ return _a; }

float StationaryOrbit::Graphics::RGBColor::getR() const
{ return _r; }

float StationaryOrbit::Graphics::RGBColor::getG() const
{ return _g; }

float StationaryOrbit::Graphics::RGBColor::getB() const
{ return _b; }

bool StationaryOrbit::Graphics::RGBColor::IsNormalized() const
{ return (0.0f <= _a)&&(_a <= 1.0f)&&(0.0f <= _r)&&(_r <= 1.0f)&&(0.0f <= _g)&&(_g <= 1.0f)&&(0.0f <= _b)&&(_b <= 1.0f); }

StationaryOrbit::Graphics::RGBColor StationaryOrbit::Graphics::RGBColor::Normalize() const
{
	float A = _a;
	A = (0.0f <= A)?(A):(0.0f);
	A = (A <= 1.0f)?(A):(1.0f);
	float R = _r;
	R = (0.0f <= R)?(R):(0.0f);
	R = (R <= 1.0f)?(R):(1.0f);
	float G = _g;
	G = (0.0f <= G)?(G):(0.0f);
	G = (G <= 1.0f)?(G):(1.0f);
	float B = _b;
	B = (0.0f <= B)?(B):(0.0f);
	B = (B <= 1.0f)?(B):(1.0f);
	return RGBColor(R, G, B, A);
}

StationaryOrbit::Graphics::RGBColor StationaryOrbit::Graphics::RGBColor::Add(const RGBColor& value) const
{ return RGBColor(_r + value._r * value._a, _g + value._g * value._a, _b + value._b * value._a, _a); }

StationaryOrbit::Graphics::RGBColor StationaryOrbit::Graphics::RGBColor::Sub(const RGBColor& value) const
{ return RGBColor(_r - value._r * value._a, _g - value._g * value._a, _b - value._b * value._a, _a); }

StationaryOrbit::Graphics::RGBColor StationaryOrbit::Graphics::RGBColor::Multiple(const RGBColor& value) const
{ return RGBColor(_r * value._r * value._a, _g * value._g * value._a, _b * value._b * value._a, _a); }

StationaryOrbit::Graphics::RGBColor StationaryOrbit::Graphics::RGBColor::Multiple(const float& value) const
{ return RGBColor(_r, _g, _b, _a * value); }

StationaryOrbit::Graphics::RGBColor StationaryOrbit::Graphics::RGBColor::Invert() const
{ return RGBColor(1.0f - _r, 1.0f - _g, 1.0f - _b, _a); }

bool StationaryOrbit::Graphics::RGBColor::Equals(const RGBColor& value) const
{ return (_a == value._a)&&(_r == value._r)&&(_g && value._g)&&(_b == value._b); }
