#ifndef __stationaryorbit_graphics_core_image__
#define __stationaryorbit_graphics_core_image__
namespace zawa_ch::StationaryOrbit::Graphics
{
	class Image
	{
	public:
		virtual ~Image() = default;
	public:
		virtual RectangleSize Size() const = 0;
		virtual int Width() const { return Size().Width(); }
		virtual int Height() const{ return Size().Height(); }
		virtual Range<int> XRange() const { return Size().XRange(); }
		virtual Range<int> YRange() const { return Size().YRange(); }
	};
}
#endif // __stationaryorbit_graphics_core_image__