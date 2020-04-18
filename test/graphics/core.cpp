#include "stationaryorbit/graphics-core/bitmap"
using namespace zawa_ch::StationaryOrbit;

void Test_Core()
{
	auto fbitmap1 = Graphics::BitmapF32(10, 10, 1);
	auto fbitmap2 = Graphics::BitmapConverter<float>::FripVertical(fbitmap1);
	auto fbitmap3 = Graphics::BitmapConverter<float>::FripHorizonal(fbitmap2);
	auto ibitmap = Graphics::Bitmap8(fbitmap1);
	auto rgbbitmap = Graphics::RGBBitmapImage(10, 10);
	auto graybitmap = rgbbitmap;
	graybitmap.Monotone();
	auto bbitmap1 = Graphics::BinaryBitmap(fbitmap1, (
		[](const Graphics::BitmapF32::ConstRefType & value) -> bool { return (value[0] > 0.5)?true:false; }
	));
	auto bbitmap2 = rgbbitmap.Binalize(
		[](const Graphics::RGBColor& color) -> bool { return ((color.R() > 0.5)&&(color.G() > 0.5)&&(color.B() > 0.5))?true:false; }
	);
}
