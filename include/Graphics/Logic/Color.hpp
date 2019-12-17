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

	public:

		Color() = default;

		explicit Color(const RGBColor& value);

		Color(const RGBColor& value, float alpha = 1.0f);

		///	このオブジェクトの不透明度を取得します。
		float getAlpha() const;

		///	このオブジェクトの表色系を取得します。
		ColorSystem getColorSystem() const;

		///	このオブジェクトのRGB値を示すRGBColorオブジェクトを取得します。
		RGBColor getRGB() const;

	};

}
#endif // __StationaryOrbit_Graphics_Color__