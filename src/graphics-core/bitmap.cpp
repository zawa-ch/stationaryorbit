#include "Graphics/Logic/Bitmap.hpp"

StationaryOrbit::Graphics::Bitmap::Bitmap(const ImageInfomation& infoamtion)
	: buf(infoamtion), info(infoamtion)
{}

StationaryOrbit::Graphics::Bitmap& StationaryOrbit::Graphics::Bitmap::Assign(const Bitmap& value)
{
	buf = value.buf;
	info = value.info;
	return *this;
}

StationaryOrbit::Graphics::BitmapFrame& StationaryOrbit::Graphics::Bitmap::Assign(const BitmapFrame& value)
{
	buf = BitmapBuffer(value.getBuffer());
	info = ImageInfomation(value.getInfomation());
	return *this;
}
