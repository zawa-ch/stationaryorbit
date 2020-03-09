#ifndef __stationaryorbit_graphics_core_pixelreference__
#define __stationaryorbit_graphics_core_pixelreference__
#include "point.hpp"
#include "rgbcolor.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{

	/// @a Bitmap 上のピクセルへの読取り専用の参照を表す基本クラスです。
	class ConstPixelReference
	{
	public:
		///	参照先の値を @a RGBColor で取得します。
		virtual RGBColor GetRGBValue() const = 0;
		///	このオブジェクトの参照先が存在するかを取得します。
		virtual bool HasValue() const noexcept = 0;
		///	この参照にオフセットを加えた先に、参照先が存在するかを取得します。
		virtual bool HasOffset(const Point& offset) const noexcept = 0;
		///	この参照にオフセットを加えた先の値を @a RGBColor で取得します。
		virtual RGBColor GetOffsetRGBValue(const Point& offset) const = 0;
		virtual ~ConstPixelReference() = default;
	};
	/// @a Bitmap 上のピクセルへの参照を表す基本クラスです。
	class PixelReference
		: virtual public ConstPixelReference
	{
	public:
		///	参照先に @a RGBColor の値を設定します。
		virtual void SetValue(const RGBColor& value) = 0;
		///	参照先の値に @a BitmapPixelGetter の参照先の値を設定します。
		virtual void SetValue(const PixelReference& value) = 0;
		///	この参照にオフセットを加えた先に @a RGBColor の値を設定します。
		virtual void SetOffsetRGBValue(const Point& offset, const RGBColor& value) = 0;
		///	この参照にオフセットを加えた先の値に @a BitmapPixelGetter の参照先の値を設定します。
		virtual void SetOffsetRGBValue(const Point& offset, const PixelReference& value) = 0;
		virtual ~PixelReference() = default;
	};

}
#endif // __stationaryorbit_graphics_core_pixelreference__