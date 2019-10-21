#include "General/Exception"
#include "Graphics/Logic/Graphics.hpp"
#include "Graphics/Logic/BitmapFrame.hpp"

StationaryOrbit::Graphics::BitmapFrame::BitmapFrame(IBitmapBuffer& buffer, IImageInfomation& info)
	: _buffer(buffer), _info(info)
{}

StationaryOrbit::Graphics::Color StationaryOrbit::Graphics::BitmapFrame::getPixel(const Point& pos) const
{
	Color Result;

	switch (_info.getColorSystem())
	{
	case ColorSystem::RGB:
		if (_buffer.getChannel() != Graphics::GetChannelFromColorSpace(ColorSystem::RGB)) throw InvalidOperationException("Buffer format no match.");
		Result = Color(RGBColor(_buffer.getPixel(pos, 0), _buffer.getPixel(pos, 1), _buffer.getPixel(pos, 2)), _buffer.getPixel(pos, 3));
		break;
	
	default:
		throw InvalidOperationException("Value 'ColorSystem' is not valid.");
		break;
	}
	return Result;
}

void StationaryOrbit::Graphics::BitmapFrame::setPixel(const Point& pos, const Color& value)
{
	RGBColor rgb;
	switch (_info.getColorSystem())
	{
	case ColorSystem::RGB:
		if (_buffer.getChannel() != Graphics::GetChannelFromColorSpace(ColorSystem::RGB)) throw InvalidOperationException("Buffer format no match.");
		rgb = value.getRGB();
		_buffer.setPixel(pos, 0, rgb.getR());
		_buffer.setPixel(pos, 1, rgb.getG());
		_buffer.setPixel(pos, 2, rgb.getB());
		_buffer.setPixel(pos, 3, value.getAlpha());
		break;
	
	default:
		throw InvalidOperationException("Value 'ColorSystem' is not valid.");
		break;
	}
}
