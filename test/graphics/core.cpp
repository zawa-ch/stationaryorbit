#include "stationaryorbit/graphics-core/bitmap"
using namespace zawa_ch::StationaryOrbit;

void Test_Core()
{
	auto fbitmap1 = Graphics::BitmapF32(10, 10, 1);
	auto fbitmap2 = Graphics::BitmapConverter<float>::FripVertical(fbitmap1);
	auto fbitmap3 = Graphics::BitmapConverter<float>::FripHorizonal(fbitmap2);
	auto rgbbitmap = Graphics::RGBBitmapImage(10, 10);
}
