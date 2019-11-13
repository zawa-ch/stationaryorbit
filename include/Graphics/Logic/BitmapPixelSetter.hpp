#ifndef __StationaryOrbit_Graphics_BitmapPixelSetter__
#define __StationaryOrbit_Graphics_BitmapPixelSetter__
#include "General/Exception"
#include "../Structure/Point.hpp"
#include "../Interface/IBitmapBuffer.hpp"
#include "../Interface/IImageInfomation.hpp"
#include "../Logic/Graphics.hpp"
#include "../Logic/Color.hpp"
#include "../Logic/BitmapPixelGetter.hpp"
namespace StationaryOrbit::Graphics
{

	///	Bitmapのピクセルへの書き込み専用の参照を表します。
	class BitmapPixelSetter
	{
	protected:

		IBitmapBuffer& buf;
		const IImageInfomation& info;
		Point pos;

		static bool HasValue(const IBitmapBuffer& buffer, const Point& position);

	public:

		BitmapPixelSetter(IBitmapBuffer& buffer, const IImageInfomation& infomation, const Point& position);

		IBitmapBuffer& Buffer() { return buf; }

		void setValue(const Color& value);

		void setValue(const BitmapPixelGetter& reference);

		bool HasOffset(const Point& offset) const;

		BitmapPixelSetter Offset(const Point& offset) const;

	};

}
#endif // __StationaryOrbit_Graphics_BitmapPixelSetter__