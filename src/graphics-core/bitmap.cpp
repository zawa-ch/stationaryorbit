#include "stationaryorbit/graphics-core/bitmap.hpp"
using namespace zawa_ch::StationaryOrbit;

Graphics::Bitmap::Bitmap(const ImageInfomation& infoamtion)
	: buf(infoamtion), info(infoamtion)
{}

Graphics::Bitmap& Graphics::Bitmap::Assign(const Bitmap& value)
{
	buf = value.buf;
	info = value.info;
	return *this;
}

Graphics::BitmapFrame& Graphics::Bitmap::Assign(const BitmapFrame& value)
{
	buf = BitmapBuffer(value.getBuffer());
	info = ImageInfomation(value.getInfomation());
	return *this;
}
