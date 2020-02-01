#ifndef __StationaryOrbit_Graphics_ColorSystem__
#define __StationaryOrbit_Graphics_ColorSystem__
namespace StationaryOrbit::Graphics
{

	///	イメージの表現に用いられている表色系。
	enum class ColorSystem
	{
		Gray,	///< グレースケール。
		RGB,	///< RGB色空間。
		CMYK,	///< CMYK色空間。
		HSV,
		HSL,
		XYZ,
		Lab,
		IndexedColor,	///< インデックスカラー。
	};

}
#endif // __StationaryOrbit_Graphics_ColorSystem__