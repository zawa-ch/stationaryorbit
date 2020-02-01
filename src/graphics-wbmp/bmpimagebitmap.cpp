#include "Graphics/BMP/Logic/BMPImageBitmap.hpp"

StationaryOrbit::Graphics::BMP::BMPImageBitmap::BMPImageBitmap(const BMPImageInfomation& infomation)
    : buf(infomation), info(infomation)
{}

StationaryOrbit::Graphics::BMP::BMPImageBitmap& StationaryOrbit::Graphics::BMP::BMPImageBitmap::Assign(const BMPImageBitmap& value)
{
	buf = value.buf;
    info = value.info;
	return *this;
}

StationaryOrbit::Graphics::BitmapFrame& StationaryOrbit::Graphics::BMP::BMPImageBitmap::Assign(const BitmapFrame& value)
{
	buf = BitmapByteBuffer(value.getBuffer());
	info = BMPImageInfomation(value.getInfomation());
	return *this;
}
