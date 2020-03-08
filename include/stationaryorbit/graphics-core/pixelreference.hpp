#ifndef __stationaryorbit_graphics_core_pixelreference__
#define __stationaryorbit_graphics_core_pixelreference__
#include "point.hpp"
#include "rgbcolor.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{

	/// 画像上のピクセルへの参照を表します。
	/// このクラスは抽象クラスです。
	class PixelReference
	{
	public:
		///	参照先の値を @a RGBColor で取得します。
		virtual RGBColor GetRGBValue() const = 0;
		///	参照先に @a RGBColor の値を設定します。
		virtual void SetValue(const RGBColor& value) = 0;
		///	参照先の値に @a BitmapPixelGetter の参照先の値を設定します。
		virtual void SetValue(const PixelReference& value) = 0;
		///	このオブジェクトの参照先が存在するかを取得します。
		virtual bool HasValue() const noexcept = 0;
		///	この参照にオフセットを加えた先に、参照先が存在するかを取得します。
		virtual bool HasOffset(const Point& offset) const noexcept = 0;
		///	この参照にオフセットを加えた先の値を @a RGBColor で取得します。
		virtual RGBColor GetOffsetRGBValue(const Point& offset) const = 0;
		///	この参照にオフセットを加えた先に @a RGBColor の値を設定します。
		virtual void SetOffsetRGBValue(const Point& offset, const RGBColor& value) = 0;
		///	この参照にオフセットを加えた先の値に @a BitmapPixelGetter の参照先の値を設定します。
		virtual void SetOffsetRGBValue(const Point& offset, const PixelReference& value) = 0;
	};

}
#endif // __stationaryorbit_graphics_core_pixelreference__