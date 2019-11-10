#ifndef __StationaryOrbit_Graphics_BitmapPixelGetter__
#define __StationaryOrbit_Graphics_BitmapPixelGetter__
#include "General/Exception"
#include "../Structure/Point.hpp"
#include "../Interface/IBitmapBuffer.hpp"
#include "../Interface/IImageInfomation.hpp"
#include "../Logic/Graphics.hpp"
#include "../Logic/Color.hpp"
namespace StationaryOrbit::Graphics
{

	///	Bitmapのピクセルへの読み取り専用の参照を表します。
	class BitmapPixelGetter
	{
	protected:

		const IBitmapBuffer& buf;
		const IImageInfomation& info;
		Point pos;

		static bool HasValue(const IBitmapBuffer& buffer, const Point& position);

	public:

		BitmapPixelGetter(const IBitmapBuffer& buffer, const IImageInfomation& infomation, const Point& position);

		Color getValue() const;

		bool HasOffset(const Point& offset) const;

		BitmapPixelGetter Offset(const Point& offset) const;

	};

}
#endif // __StationaryOrbit_Graphics_BitmapPixelGetter__