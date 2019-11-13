#ifndef __StationaryOrbit_Graphics_BitmapPixelReference__
#define __StationaryOrbit_Graphics_BitmapPixelReference__
#include "General/Exception"
#include "../Structure/Point.hpp"
#include "../Interface/IBitmapBuffer.hpp"
#include "../Interface/IImageInfomation.hpp"
#include "../Logic/Color.hpp"
#include "../Logic/BitmapPixelGetter.hpp"
#include "../Logic/BitmapPixelSetter.hpp"
namespace StationaryOrbit::Graphics
{

	///	Bitmapのピクセルへの参照を表します。
	class BitmapPixelReference
		: private BitmapPixelGetter
		, private BitmapPixelSetter
	{
	private:

		BitmapPixelReference(const BitmapPixelGetter& getter, const BitmapPixelSetter& setter);

	public:

		BitmapPixelReference(IBitmapBuffer& buffer, const IImageInfomation& infomation, const Point& position);

		IBitmapBuffer& Buffer() { return ((BitmapPixelSetter)*this).Buffer(); }

		const IBitmapBuffer& getBuffer() const { return ((BitmapPixelGetter)*this).getBuffer(); }

		const IImageInfomation& getInfomation() const { return ((BitmapPixelGetter)*this).getInfomation(); }

		Point getPosition() const { return ((BitmapPixelGetter)*this).getPosition(); }

		Color getValue() const { return ((BitmapPixelGetter)*this).getValue(); }

		void setValue(const Color& value) { ((BitmapPixelSetter)*this).setValue(value); }

		void setValue(const BitmapPixelGetter& value) { ((BitmapPixelSetter)*this).setValue(value); }

		bool HasOffset(const Point& offset) const { return ((BitmapPixelGetter)*this).HasOffset(offset); }

		BitmapPixelReference Offset(const Point& offset);

	};

}
#endif // __StationaryOrbit_Graphics_BitmapPixelReference__