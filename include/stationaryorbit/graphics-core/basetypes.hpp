#ifndef __stationaryorbit_graphics_core_basetypes__
#define __stationaryorbit_graphics_core_basetypes__
#include <cstddef>
#include "channelvalue.hpp"
#include "point.hpp"
#include "rgbcolor.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{

	///	ビットマップ画像のデータ構造として用いる色空間を表します。
	enum class BitmapColorSpace
	{
		///	グレースケール。
		GrayScale,
		///	RGB(+アルファ)色空間。
		ARGB,
		///	CMYK色空間。
		CMYK,
		///	XYZ(+アルファ)色空間。
		AXYZ
	};

	///	画像の大きさを取得するためのメソッドを実装します。
	class IImageSize
	{
	public:
		///	このバッファの幅を取得します。
		virtual size_t GetHorizonalSize() const = 0;
		///	このバッファの高さを取得します。
		virtual size_t GetVerticalSize() const = 0;
		///	バッファに使用されている色空間を取得します。
		virtual BitmapColorSpace GetColorSpace() const = 0;
	};

	///	ビットマップ画像を表します。
	///	このクラスは抽象クラスです。
	class Bitmap
		: virtual public IImageSize
	{
	public:
		///	指定されたピクセルの値をRGBで取得します。
		virtual RGBColor GetRGB(const size_t& x, const size_t& y) const = 0;
		///	指定されたピクセルの値をRGBで設定します。
		virtual void SetRGB(const size_t& x, const size_t& y, const RGBColor& value) = 0;
	};

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
#endif // __stationaryorbit_graphics_core_basetypes__