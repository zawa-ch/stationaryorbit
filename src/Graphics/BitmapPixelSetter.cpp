#include "Graphics/Logic/BitmapPixelSetter.hpp"

StationaryOrbit::Graphics::BitmapPixelSetter::BitmapPixelSetter(IBitmapBuffer& buffer, const IImageInfomation& infomation, const Point& position)
    : buf(buffer), info(infomation), pos(position)
{
	if (!HasValue(buffer, position)) { throw std::invalid_argument("Argument 'position' is out of boundary of buffer."); }
}

bool StationaryOrbit::Graphics::BitmapPixelSetter::HasValue(const IBitmapBuffer& buffer, const Point& position)
{
	if ((0 <= position.getX())&&(buffer.getSize().getX() > position.getX())&&(0 <= position.getY())&&(buffer.getSize().getY() > position.getY()))
	{ return true; }
	else
	{ return false; }
}

void StationaryOrbit::Graphics::BitmapPixelSetter::setValue(const Color& value)
{
	RGBColor rgb;
	switch (info.getColorSystem())
	{
	case ColorSystem::RGB:
		if (buf.getChannel() != Graphics::GetChannelFromColorSpace(ColorSystem::RGB)) throw InvalidOperationException("Buffer format no match.");
		rgb = value.getRGB();
		buf.setPixel(pos, 0, rgb.getR());
		buf.setPixel(pos, 1, rgb.getG());
		buf.setPixel(pos, 2, rgb.getB());
		buf.setPixel(pos, 3, value.getAlpha());
		break;
	
	default:
		throw InvalidOperationException("Value 'ColorSystem' is not valid.");
		break;
	}
}

void StationaryOrbit::Graphics::BitmapPixelSetter::setValue(const BitmapPixelGetter& reference)
{
	setValue(reference.getValue());
}

bool StationaryOrbit::Graphics::BitmapPixelSetter::HasOffset(const Point& offset) const
{
	return HasValue(buf, pos + offset);
}

StationaryOrbit::Graphics::BitmapPixelSetter StationaryOrbit::Graphics::BitmapPixelSetter::Offset(const Point& offset) const
{
	return BitmapPixelSetter(buf, info, pos + offset);
}
