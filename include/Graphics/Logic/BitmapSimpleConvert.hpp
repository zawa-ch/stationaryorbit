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
	public:

		typedef void (*ResizeMethod)(BitmapPixelReference, const BitmapFrame&);

	private:

		BitmapSimpleConvert() = delete;
		BitmapSimpleConvert(const BitmapSimpleConvert&) = delete;
		BitmapSimpleConvert(BitmapSimpleConvert&&) = delete;
		~BitmapSimpleConvert() = delete;
		BitmapSimpleConvert operator=(const BitmapSimpleConvert&) = delete;
		BitmapSimpleConvert operator=(BitmapSimpleConvert&&) = delete;

	public:

		///	指定されたBitmapの上下を入れ替えます。
		static Bitmap FripVertical(const BitmapFrame& bitmap);

		///	指定されたBitmapの左右を入れ替えます。
		static Bitmap FripHorizonal(const BitmapFrame& bitmap);

		static void Nearest(BitmapPixelReference dst, const BitmapFrame& src);

		static Bitmap Resize(const BitmapFrame& bitmap, const Point& size, ResizeMethod resizer);

		///	指定されたBitmapをareaで指定された範囲で切り抜きます。
		static Bitmap Crop(const BitmapFrame& bitmap, const Rectangle& area);

	};

}
#endif // __StationaryOrbit_Graphics_BitmapSimpleConvert__