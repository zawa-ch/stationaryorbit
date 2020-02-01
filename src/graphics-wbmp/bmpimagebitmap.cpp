#include "stationaryorbit/graphics-wbmp/bmpimagebitmap.hpp"
using namespace zawa_ch::StationaryOrbit;

Graphics::BMP::BMPImageBitmap::BMPImageBitmap(const BMPImageInfomation& infomation)
    : buf(infomation), info(infomation)
{}

Graphics::BMP::BMPImageBitmap& Graphics::BMP::BMPImageBitmap::Assign(const BMPImageBitmap& value)
{
	buf = value.buf;
    info = value.info;
	return *this;
}

Graphics::BitmapFrame& Graphics::BMP::BMPImageBitmap::Assign(const BitmapFrame& value)
{
	buf = BitmapByteBuffer(value.getBuffer());
	info = BMPImageInfomation(value.getInfomation());
	return *this;
}
