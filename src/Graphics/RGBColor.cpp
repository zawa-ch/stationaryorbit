#include "Graphics/Structure/RGBColor.hpp"

StationaryOrbit::Graphics::RGBColor::RGBColor(const float& r, const float& g, const float& b)
	: _r(r), _g(g), _b(b)
{}

float StationaryOrbit::Graphics::RGBColor::getR() const
{ return _r; }

float StationaryOrbit::Graphics::RGBColor::getG() const
{ return _g; }

float StationaryOrbit::Graphics::RGBColor::getB() const
{ return _b; }

bool StationaryOrbit::Graphics::RGBColor::IsNormalized() const
{ return (0.0f <= _r)&&(_r <= 1.0f)&&(0.0f <= _g)&&(_g <= 1.0f)&&(0.0f <= _b)&&(_b <= 1.0f); }

StationaryOrbit::Graphics::RGBColor StationaryOrbit::Graphics::RGBColor::Normalize() const
{
	float R = _r;
	R = (0.0f <= R)?(R):(0.0f);
	R = (R <= 1.0f)?(R):(1.0f);
	float G = _g;
	G = (0.0f <= G)?(G):(0.0f);
	G = (G <= 1.0f)?(G):(1.0f);
	float B = _b;
	B = (0.0f <= B)?(B):(0.0f);
	B = (B <= 1.0f)?(B):(1.0f);
	return RGBColor(R, G, B);
}

StationaryOrbit::Graphics::RGBColor StationaryOrbit::Graphics::RGBColor::Add(const RGBColor& value) const
{ return RGBColor(_r + value._r, _g + value._g, _b + value._b); }

StationaryOrbit::Graphics::RGBColor StationaryOrbit::Graphics::RGBColor::Sub(const RGBColor& value) const
{ return RGBColor(_r - value._r, _g - value._g, _b - value._b); }

bool StationaryOrbit::Graphics::RGBColor::Equals(const RGBColor& value) const
{ return (_r == value._r)&&(_g && value._g)&&(_b == value._b); }
