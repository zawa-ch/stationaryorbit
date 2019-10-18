#ifndef __StationaryOrbit_Graphics_Color__
#define __StationaryOrbit_Graphics_Color__
#include "../Structure/RGBColor.hpp"
namespace StationaryOrbit::Graphics
{

	class Color
	{
	private:

		RGBColor _color;
		float _alpha;

	public:

		Color() = default;

		explicit Color(const RGBColor& value);

		Color(const RGBColor& value, const float& alpha);

		///	このオブジェクトの不透明度を取得します。
		float getAlpha() const;

		///	このオブジェクトのRGB値を示すRGBColorオブジェクトを取得します。
		RGBColor getRGB() const;

	};

}
#endif // __StationaryOrbit_Graphics_Color__