#include "stationaryorbit/graphics-core/bitmappixelsetter.hpp"
using namespace zawa_ch::StationaryOrbit;

bool Graphics::BitmapPixelSetter::HasValue(const IBitmapBuffer& buffer, const Point& position)
{
	if ((0 <= position.getX())&&(buffer.getSize().getX() > position.getX())&&(0 <= position.getY())&&(buffer.getSize().getY() > position.getY()))
	{ return true; }
	else
	{ return false; }
}

Graphics::BitmapPixelSetter::BitmapPixelSetter(IBitmapBuffer& buffer, const IImageInfomation& infomation, const Point& position)
    : buf(buffer), info(infomation), pos(position)
{
	if (!HasValue(buffer, position)) { throw std::invalid_argument("Argument 'position' is out of boundary of buffer."); }
}

uint Graphics::BitmapPixelSetter::getChannelCount() const
{
	return buf.getChannel();
}

void Graphics::BitmapPixelSetter::setChannel(const uint& channel, const float& value)
{
	if (getChannelCount() <= channel) { throw std::out_of_range("指定された'channel'が参照先のbitmapのチャンネル数を超えています。"); }
	return buf.setPixel(pos, channel, value);
}

void Graphics::BitmapPixelSetter::setRGBValue(const RGBColor& value)
{
	switch (info.getColorSystem())
	{
	case ColorSystem::RGB:
		if (buf.getChannel() != Graphics::GetChannelFromColorSpace(ColorSystem::RGB)) throw InvalidOperationException("Buffer format no match.");
		buf.setPixel(pos, 0, value.getR());
		buf.setPixel(pos, 1, value.getG());
		buf.setPixel(pos, 2, value.getB());
		buf.setPixel(pos, 3, value.getAlpha());
		break;

	default:
		throw InvalidOperationException("Value 'ColorSystem' is not valid.");
		break;
	}
}

void Graphics::BitmapPixelSetter::setValue(const BitmapPixelGetter& reference)
{
	switch (info.getColorSystem())
	{
	case ColorSystem::RGB:
		setRGBValue(reference.getRGBValue());
		break;

	default:
		throw InvalidOperationException("Value 'ColorSystem' is not valid.");
		break;
	}
}

bool Graphics::BitmapPixelSetter::HasOffset(const Point& offset) const
{
	return HasValue(buf, pos + offset);
}

Graphics::BitmapPixelSetter Graphics::BitmapPixelSetter::Offset(const Point& offset) const
{
	return BitmapPixelSetter(buf, info, pos + offset);
}
