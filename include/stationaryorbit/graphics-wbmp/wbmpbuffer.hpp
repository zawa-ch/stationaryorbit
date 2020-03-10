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
		WbmpBuffer();
		WbmpBuffer(const size_t& x, const size_t& y);
		explicit WbmpBuffer(const Point& size);
		explicit WbmpBuffer(const WbmpBufferBase& bitmap);
	};

}
#endif // __stationaryorbit_graphics_wbmp_wbmpbuffer__