#include "Graphics/Logic/RelativeColor.hpp"

StationaryOrbit::Graphics::RelativeColor::RelativeColor(const RGBColor& value, float alpha)
	: color(value), alpha(alpha)
{}

float StationaryOrbit::Graphics::RelativeColor::getAlpha() const
{ return alpha; }

StationaryOrbit::Graphics::RGBColor StationaryOrbit::Graphics::RelativeColor::getRGB() const
{ return color; }

bool StationaryOrbit::Graphics::RelativeColor::IsNormalized() const
{ return color.IsNormalized(); }

StationaryOrbit::Graphics::RelativeColor StationaryOrbit::Graphics::RelativeColor::Normalize() const
{ return RelativeColor(color.Normalize(), alpha); }

StationaryOrbit::Graphics::RelativeColor StationaryOrbit::Graphics::RelativeColor::Add(const RelativeColor& value) const
{ return RelativeColor(color + (value.color * value.alpha), alpha); }

StationaryOrbit::Graphics::RelativeColor StationaryOrbit::Graphics::RelativeColor::Sub(const RelativeColor& value) const
{ return RelativeColor(color - (value.color * value.alpha), alpha); }

StationaryOrbit::Graphics::RelativeColor StationaryOrbit::Graphics::RelativeColor::Multiple(const RelativeColor& value) const
{ return RelativeColor(color * ~(~value.color * value.alpha), alpha); }
