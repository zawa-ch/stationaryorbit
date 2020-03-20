#include "stationaryorbit/graphics-core/bitmap"
using namespace zawa_ch::StationaryOrbit;

void Test_Core()
{
	auto buf = Graphics::BitmapBuffer(10, 10, Graphics::BitmapColorSpace::ARGB);
	auto bbuf = buf.ConvertTo<uint8_t>();
	auto vfbuf = Graphics::BitmapSimpleConvert<uint8_t>::FripVertical(bbuf);
	auto bitmap = Graphics::BufferedBitmap<uint8_t>(Graphics::BitmapSimpleConvert<uint8_t>::FripHorizonal(vfbuf));
}
