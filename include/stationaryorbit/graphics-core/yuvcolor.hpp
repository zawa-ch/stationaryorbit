#ifndef __stationaryorbit_graphics_core_ycrcbcolor__
#define __stationaryorbit_graphics_core_ycrcbcolor__
#include "rgbcolor.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{

	struct YCrCbColor final
	{
	private:

		float _a;
		float _y;
		float _cr;
		float _cb;

	public:

		/// 既定の @a YCrCbColor を初期化します。
		YCrCbColor() = default;

		/// 値を指定してYCrCbオブジェクトを初期化します。
		YCrCbColor(float Y, float Cr, float Cb, float alpha);

		///	@a RGBColor オブジェクトをこの型に変換します。
		explicit YCrCbColor(const RGBColor& value);

		~YCrCbColor() = default;

		///	このオブジェクトの不透明度を取得します。
		float getAlpha() const;

		///	このオブジェクトの輝度成分を取得します。
		float getY() const;

		///	このオブジェクトの赤色差成分を取得します。
		float getCr() const;

		///	このオブジェクトの青色差成分を取得します。
		float getCb() const;

		///	このオブジェクトが正規化されているかを取得します。
		bool IsNormalized() const;

		///	このオブジェクトを正規化した @a YCrCbColor を取得します。
		YCrCbColor Normalize() const;

		explicit operator RGBColor() const;

	};

}
#endif // __stationaryorbit_graphics_core_ycrcbcolor__