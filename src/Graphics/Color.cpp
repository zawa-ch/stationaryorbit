#include "Graphics/Logic/Color.hpp"

StationaryOrbit::Graphics::Color::Color(const RGBColor& value, float alpha)
	: colorsys(ColorSystem::RGB), elements{ value.getR(), value.getG(), value.getB() }, alpha(alpha)
{}

float StationaryOrbit::Graphics::Color::getAlpha() const
{ return alpha; }

StationaryOrbit::Graphics::ColorSystem StationaryOrbit::Graphics::Color::getColorSystem() const
{ return colorsys; }

StationaryOrbit::Graphics::RGBColor StationaryOrbit::Graphics::Color::getRGB() const
{
	switch (colorsys)
	{
	case ColorSystem::RGB:
		return RGBColor(elements[0], elements[1], elements[2]);
	default:
		throw InvalidOperationException("到達できないコードに到達しました。");
	}
}
