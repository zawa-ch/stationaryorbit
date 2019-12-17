#include "Graphics/Logic/Color.hpp"

StationaryOrbit::Graphics::RGBColor StationaryOrbit::Graphics::Color::ctorRGBColor() const
{
	if (colorsys == ColorSystem::RGB) { return RGBColor(elements[0], elements[1], elements[2]); }
	else { throw InvalidOperationException("内部の色空間はRGBではありません。"); }
}

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
		return ctorRGBColor();
	default:
		throw InvalidOperationException("到達できないコードに到達しました。");
	}
}

bool StationaryOrbit::Graphics::Color::IsNormalized() const
{
	switch (colorsys)
	{
	case ColorSystem::RGB:
		return ctorRGBColor().IsNormalized();
	default:
		throw InvalidOperationException("到達できないコードに到達しました。");
	}
}

StationaryOrbit::Graphics::Color StationaryOrbit::Graphics::Color::Normalize() const
{
	switch (colorsys)
	{
	case ColorSystem::RGB:
		return Color(ctorRGBColor().Normalize());
	default:
		throw InvalidOperationException("到達できないコードに到達しました。");
	}
}
