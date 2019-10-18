#include "General/Exception"
#include "Graphics/Logic/Canvas.hpp"

float StationaryOrbit::Graphics::Canvas::getChannel(const Point& pos, size_t ch) const
{
	union
	{
		uint8_t I8;
		uint16_t I16;
		float F32;
	} rawvalue;
	float result;

	switch (buffer.getInfomation().getColorDepth())
	{
	case ColorDepth::Binary:
		buffer.getPixel(&rawvalue.I8, pos, ch);
		result = (rawvalue.I8 != 0)?(1.0f):(0.0f);
		break;

	case ColorDepth::I8:
		buffer.getPixel(&rawvalue.I8, pos, ch);
		result = float(rawvalue.I8) / UINT8_MAX;
		break;

	case ColorDepth::I16:
		buffer.getPixel(&rawvalue.I16, pos, ch);
		result = float(rawvalue.I16) / UINT16_MAX;
		break;

	case ColorDepth::F16:
		break;

	case ColorDepth::F32:
		buffer.getPixel(&rawvalue.F32, pos, ch);
		result = rawvalue.F32;
		break;
	
	default:
		throw InvalidOperationException("Value 'ColorDepth' is not valid.");
		break;
	}

	return result;
}

void StationaryOrbit::Graphics::Canvas::setChannel(const Point& pos, size_t ch, const float& value)
{
	union
	{
		uint8_t I8;
		uint16_t I16;
		float F32;
	} rawvalue;

	switch (buffer.getInfomation().getColorDepth())
	{
	case ColorDepth::Binary:
		rawvalue.I8 = (0.5f <= value)?(1):(0);
		buffer.setPixel(&rawvalue.I8, pos, ch);
		break;

	case ColorDepth::I8:
		if (value <= 0.0f) rawvalue.I8 = 0;
		else if (1.0f <= value) rawvalue.I8 = UINT8_MAX;
		else rawvalue.I8 = uint8_t(value * UINT8_MAX);
		buffer.getPixel(&rawvalue.I8, pos, ch);
		break;

	case ColorDepth::I16:
		if (value <= 0.0f) rawvalue.I16 = 0;
		else if (1.0f <= value) rawvalue.I16 = UINT16_MAX;
		else rawvalue.I16 = uint8_t(value * UINT16_MAX);
		buffer.getPixel(&rawvalue.I16, pos, ch);
		break;

	case ColorDepth::F16:
		break;

	case ColorDepth::F32:
		rawvalue.F32 = value;
		buffer.getPixel(&rawvalue.F32, pos, ch);
		break;
	
	default:
		throw InvalidOperationException("Value 'ColorDepth' is not valid.");
		break;
	}
}

StationaryOrbit::Graphics::Canvas::Canvas(ICanvasBuffer& buffer)
	: buffer(buffer)
{}

StationaryOrbit::Graphics::ICanvasBuffer& StationaryOrbit::Graphics::Canvas::GetBuffer()
{ return buffer; }

StationaryOrbit::Graphics::Color StationaryOrbit::Graphics::Canvas::getPixel(const Point& pos) const
{
	Color Result;

	switch (buffer.getInfomation().getColorSystem())
	{
	case ColorSystem::RGB:
		Result = Color(RGBColor(getChannel(pos, 0), getChannel(pos, 1), getChannel(pos, 2)), getChannel(pos, 3));
		break;
	
	default:
		throw InvalidOperationException("Value 'ColorSystem' is not valid.");
		break;
	}
	return Result;
}

void StationaryOrbit::Graphics::Canvas::setPixel(const Point& pos, const Color& value)
{
	RGBColor rgb;
	switch (buffer.getInfomation().getColorSystem())
	{
	case ColorSystem::RGB:
		rgb = value.getRGB();
		setChannel(pos, 0, rgb.getR());
		setChannel(pos, 1, rgb.getG());
		setChannel(pos, 2, rgb.getB());
		setChannel(pos, 3, value.getAlpha());
		break;
	
	default:
		throw InvalidOperationException("Value 'ColorSystem' is not valid.");
		break;
	}
}
