#ifndef __STATIONARYORBIT_GRAPHICS_RELATIVECOLOR__
#define __STATIONARYORBIT_GRAPHICS_RELATIVECOLOR__
#include "../Structure/RGBColor.hpp"
namespace StationaryOrbit::Graphics
{

    class RelativeColor
    {
    private:

        RGBColor color;
        float alpha;

    public:

		RelativeColor() = default;

        RelativeColor(const RGBColor& color, float alpha = 1.0f);

		///	このオブジェクトの不透明度を取得します。
		float getAlpha() const;

		///	このオブジェクトのRGB値を示す @a RGBColor オブジェクトを取得します。
		RGBColor getRGB() const;

		///	このオブジェクトが正規化されているかを取得します。
		///
		///	@return
		///	正規化されている場合 @a true が返ります。
		///	正規化されていない場合 @a false が返ります。
		bool IsNormalized() const;

		///	このオブジェクトを正規化した @a RelativeColor を取得します。
		///
		///	@return
		///	正規化された @a RelativeColor オブジェクトが返ります。
		///	内部の色空間は正規化される前の @a RelativeColor オブジェクトの色空間に依存します。
		RelativeColor Normalize() const;

    };

}
#endif // __STATIONARYORBIT_GRAPHICS_RELATIVECOLOR__