#ifndef __stationaryorbit_graphics_wbmp_wbmpbuffer__
#define __stationaryorbit_graphics_wbmp_wbmpbuffer__
#include "stationaryorbit/graphics-core/bitmap"
namespace zawa_ch::StationaryOrbit::Graphics::WBMP
{

	class WbmpBufferBase
		: virtual public BitmapBufferBase<uint8_t>
	{
	public:
		virtual ~WbmpBufferBase() = default;
	};

	class WbmpBuffer
		: virtual public BitmapBuffer<uint8_t>
		, virtual public WbmpBufferBase
	{
	public:
		WbmpBuffer() : BitmapBuffer<uint8_t>() {}
		WbmpBuffer(const size_t& x, const size_t& y) : BitmapBuffer<uint8_t>(x, y, BitmapColorSpace::ARGB) {}
		explicit WbmpBuffer(const Point& size) : BitmapBuffer<uint8_t>(size, BitmapColorSpace::ARGB) {}
		explicit WbmpBuffer(const WbmpBufferBase& bitmap) : BitmapBuffer<uint8_t>(bitmap) {}
	};

}
#endif // __stationaryorbit_graphics_wbmp_wbmpbuffer__