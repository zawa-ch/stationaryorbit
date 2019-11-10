#include "Graphics/Logic/BitmapPixelReference.hpp"

StationaryOrbit::Graphics::BitmapPixelReference::BitmapPixelReference(IBitmapBuffer& buffer, const IImageInfomation& infomation, const Point& position)
	: BitmapPixelGetter(buffer, infomation, position), BitmapPixelSetter(buffer, infomation, position)
{
	if (!BitmapPixelGetter::HasValue(buffer, position)) { throw std::invalid_argument("Argument 'position' is out of boundary of buffer."); }
}

StationaryOrbit::Graphics::BitmapPixelReference StationaryOrbit::Graphics::BitmapPixelReference::Offset(const Point& offset)
{
	return BitmapPixelReference(BitmapPixelGetter(*this).Offset(offset), BitmapPixelSetter(*this).Offset(offset));
}
