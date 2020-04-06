#ifndef __stationaryorbit_graphics_core_bitmapcolorconverter__
#define __stationaryorbit_graphics_core_bitmapcolorconverter__
#include "stationaryorbit/exception/soexcept"
#include "stationaryorbit/core/numeral"
#include "fundamental.hpp"
#include "bitmap.hpp"
#include "colorspace.hpp"
#include "graybitmapimage.hpp"
#include "rgbbitmapimage.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	template<class channelT>
	class BitmapColorConverter
	{
	private:
		BitmapColorConverter() = delete;
		~BitmapColorConverter() = delete;
	public:
		static GrayBitmapImageBase<channelT> Monotone(const RGBBitmapImageBase<channelT>& bitmap)
		{
            auto result = GrayBitmapImageBase<channelT>(bitmap.Size());
            auto space = ColorSpace::sRGB;
            for (auto y : bitmap.YRange()) for (auto x : bitmap.XRange())
            {
                result.Index(x, y) = GrayColor(space.ConvertXYZ(bitmap.Index(x, y).get()).Y());
            }
            return result;
		}
	};
}
#endif // __stationaryorbit_graphics_core_bitmapcolorconverter__