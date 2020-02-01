#include "stationaryorbit/graphics-core/bitmappixelreference.hpp"
using namespace zawa_ch::StationaryOrbit;

Graphics::BitmapPixelReference::BitmapPixelReference(const BitmapPixelGetter& getter, const BitmapPixelSetter& setter)
	: BitmapPixelGetter(getter), BitmapPixelSetter(setter)
{}

Graphics::BitmapPixelReference::BitmapPixelReference(IBitmapBuffer& buffer, const IImageInfomation& infomation, const Point& position)
	: BitmapPixelGetter(buffer, infomation, position), BitmapPixelSetter(buffer, infomation, position)
{
	if (!BitmapPixelGetter::HasValue(buffer, position)) { throw std::invalid_argument("Argument 'position' is out of boundary of buffer."); }
}

Graphics::BitmapPixelReference Graphics::BitmapPixelReference::Offset(const Point& offset)
{
	return BitmapPixelReference(BitmapPixelGetter(*this).Offset(offset), BitmapPixelSetter(*this).Offset(offset));
}
