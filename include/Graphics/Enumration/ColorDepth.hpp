#ifndef __StationaryOrbit_Graphics_ColorDepth__
#define __StationaryOrbit_Graphics_ColorDepth__
namespace StationaryOrbit::Graphics
{

	///	イメージの各チャネルの色深度。
	enum class ColorDepth
	{
		Binary,	///< 二値。
		I8,	///< 8ビット。
		I16,	///< 16ビット。
		F16,	///< 16ビット浮動小数点数。
		F32,	///< 32ビット浮動小数点数。
	};

}
#endif // __StationaryOrbit_Graphics_ColorDepth__