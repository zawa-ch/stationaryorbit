#include "stationaryorbit/graphics-core/bitmappixelgetter.hpp"
using namespace zawa_ch::StationaryOrbit;

Graphics::BitmapPixelGetter::BitmapPixelGetter(const IBitmapBuffer& buffer, const IImageInfomation& infomation, const Point& position)
    : buf(buffer), info(infomation), pos(position)
{
	if (!HasValue(buffer, position)) { throw std::invalid_argument("Argument 'position' is out of boundary of buffer."); }
}

bool Graphics::BitmapPixelGetter::HasValue(const IBitmapBuffer& buffer, const Point& position)
{
	if ((0 <= position.getX())&&(buffer.getSize().getX() > position.getX())&&(0 <= position.getY())&&(buffer.getSize().getY() > position.getY()))
	{ return true; }
	else
	{ return false; }
}

uint Graphics::BitmapPixelGetter::getChannelCount() const
{
	return buf.getChannel();
}

float Graphics::BitmapPixelGetter::getChannel(const uint& channel) const
{
	if (getChannelCount() <= channel) { throw std::out_of_range("指定された'channel'が参照先のbitmapのチャンネル数を超えています。"); }
	return buf.getPixel(pos, channel);
}

Graphics::RGBColor Graphics::BitmapPixelGetter::getRGBValue() const
{
	RGBColor Result;

	switch (info.getColorSystem())
	{
	case ColorSystem::RGB:
		if (buf.getChannel() != Graphics::GetChannelFromColorSpace(ColorSystem::RGB)) throw InvalidOperationException("Buffer format no match.");
		Result = RGBColor(getChannel(0), getChannel(1), getChannel(2), getChannel(3));
		break;
	
	default:
		throw InvalidOperationException("Value 'ColorSystem' is not valid.");
		break;
	}
	return Result;
}

bool Graphics::BitmapPixelGetter::HasOffset(const Point& offset) const
{
	return HasValue(buf, pos + offset);
}

Graphics::BitmapPixelGetter Graphics::BitmapPixelGetter::Offset(const Point& offset) const
{
	return BitmapPixelGetter(buf, info, pos + offset);
}
