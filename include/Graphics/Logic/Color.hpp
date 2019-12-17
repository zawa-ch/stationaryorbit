#ifndef __StationaryOrbit_Graphics_Color__
#define __StationaryOrbit_Graphics_Color__
#include <vector>
#include "General/Exception"
#include "../Enumration/ColorSystem.hpp"
#include "../Structure/RGBColor.hpp"
namespace StationaryOrbit::Graphics
{

	class Color
	{
	private:

		ColorSystem colorsys;
		float elements[3];
		float alpha;

		///	内部の情報から @a RGBColor を構築します。
		///	このメソッドを実行するには @a colorsys が @a ColorSystem::RGB である必要があります。
		RGBColor ctorRGBColor() const;

	public:

		Color() = default;

		Color(const RGBColor& value, float alpha = 1.0f);

		///	このオブジェクトの不透明度を取得します。
		float getAlpha() const;

		///	このオブジェクトの表色系を取得します。
		ColorSystem getColorSystem() const;

		///	このオブジェクトのRGB値を示す @a RGBColor オブジェクトを取得します。
		RGBColor getRGB() const;

		///	このオブジェクトが正規化されているかを取得します。
		///
		///	@return
		///	正規化されている場合 @a true が返ります。
		///	正規化されていない場合 @a false が返ります。
		bool IsNormalized() const;

		///	このオブジェクトを正規化した @a Color を取得します。
		///
		///	@return
		///	正規化された @a Color オブジェクトが返ります。
		///	内部の色空間は正規化される前の @a Color オブジェクトの色空間に依存します。
		Color Normalize() const;

	};

}
#endif // __StationaryOrbit_Graphics_Color__