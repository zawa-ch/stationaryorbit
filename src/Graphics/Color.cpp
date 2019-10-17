#include "Graphics/Logic/Color.hpp"

StationaryOrbit::Graphics::Color::Color(const RGBColor& value)
	: _color(value), _alpha(1.0f)
{}

StationaryOrbit::Graphics::Color::Color(const RGBColor& value, const float& alpha)
	: _color(value), _alpha(alpha)
{}

float StationaryOrbit::Graphics::Color::getAlpha() const
{ return _alpha; }

StationaryOrbit::Graphics::RGBColor StationaryOrbit::Graphics::Color::getRGB() const
{ return _color; }
