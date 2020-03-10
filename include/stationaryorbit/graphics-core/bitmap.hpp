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

	///	ビットマップの基本となるメソッドを実装します。
	class BitmapBase
	{
	public:
		///	このバッファの幅を取得します。
		virtual size_t GetHorizonalSize() const = 0;
		///	このバッファの高さを取得します。
		virtual size_t GetVerticalSize() const = 0;
		///	バッファに使用されている色空間を取得します。
		virtual BitmapColorSpace GetColorSpace() const = 0;
		virtual ~BitmapBase() = default;
	};

	///	ビットマップ画像を表す基本クラスです。
	class Bitmap
		: virtual public BitmapBase
	{
	public:
		///	指定されたピクセルの値をRGBで取得します。
		virtual RGBColor GetRGB(const size_t& x, const size_t& y) const = 0;
		///	指定されたピクセルの値をRGBで設定します。
		virtual void SetRGB(const size_t& x, const size_t& y, const RGBColor& value) = 0;
		virtual ~Bitmap() = default;
	};

}
#endif // __stationaryorbit_graphics_core_basetypes__