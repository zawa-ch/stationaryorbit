#ifndef __StationaryOrbit_Graphics_BitmapSimpleConvert__
#define __StationaryOrbit_Graphics_BitmapSimpleConvert__
#include "../Structure/Point.hpp"
#include "../Structure/PointF.hpp"
#include "../Structure/Rectangle.hpp"
#include "../Logic/BitmapFrame.hpp"
#include "../Logic/Bitmap.hpp"
namespace StationaryOrbit::Graphics
{

	class BitmapSimpleConvert final
	{
	private:

		BitmapSimpleConvert() = delete;
		BitmapSimpleConvert(const BitmapSimpleConvert&) = delete;
		BitmapSimpleConvert(BitmapSimpleConvert&&) = delete;
		~BitmapSimpleConvert() = delete;
		BitmapSimpleConvert operator=(const BitmapSimpleConvert&) = delete;
		BitmapSimpleConvert operator=(BitmapSimpleConvert&&) = delete;

	public:

		static Bitmap FripVertical(const BitmapFrame& bitmap);

		static Bitmap FripHorizonal(const BitmapFrame& bitmap);

		static Bitmap Resize(const BitmapFrame& bitmap, const Point& size);

		static Bitmap Rescale(const BitmapFrame& bitmap, const PointF& magnification);

		static Bitmap Crop(const BitmapFrame& bitmap, const Rectangle& area);

	};

}
#endif // __StationaryOrbit_Graphics_BitmapSimpleConvert__