#include "Graphics/Logic/BitmapPixelGetter.hpp"

StationaryOrbit::Graphics::BitmapPixelGetter::BitmapPixelGetter(IBitmapBuffer& buffer, const IImageInfomation& infomation, const Point& position)
    : buf(buffer), info(infomation), pos(position)
{
	if (!HasValue(buffer, position)) { throw std::invalid_argument("Argument 'position' is out of boundary of buffer."); }
}

bool StationaryOrbit::Graphics::BitmapPixelGetter::HasValue(const IBitmapBuffer& buffer, const Point& position)
{
	if ((0 <= position.getX())&&(buffer.getSize().getX() > position.getX())&&(0 <= position.getY())&&(buffer.getSize().getY() > position.getY()))
	{ return true; }
	else
	{ return false; }
}

StationaryOrbit::Graphics::Color StationaryOrbit::Graphics::BitmapPixelGetter::getValue() const
{
	Color Result;

	switch (info.getColorSystem())
	{
	case ColorSystem::RGB:
		if (buf.getChannel() != Graphics::GetChannelFromColorSpace(ColorSystem::RGB)) throw InvalidOperationException("Buffer format no match.");
		Result = Color(RGBColor(buf.getPixel(pos, 0), buf.getPixel(pos, 1), buf.getPixel(pos, 2)), buf.getPixel(pos, 3));
		break;
	
	default:
		throw InvalidOperationException("Value 'ColorSystem' is not valid.");
		break;
	}
	return Result;
}

bool StationaryOrbit::Graphics::BitmapPixelGetter::HasOffset(const Point& offset) const
{
	return HasValue(buf, pos + offset);
}

StationaryOrbit::Graphics::BitmapPixelGetter StationaryOrbit::Graphics::BitmapPixelGetter::Offset(const Point& offset)
{
	return BitmapPixelGetter(buf, info, pos + offset);
}
