#ifndef __StationaryOrbit_Graphics_ImageFormat__
#define __StationaryOrbit_Graphics_ImageFormat__
namespace StationaryOrbit
{
namespace Graphics
{

	///	イメージの各チャネルの割当を定めるフォーマット情報。
	enum class ImageFormat
	{
		Binary,	///< 二値。
		Index8,	///< 8ビット インデックス。
		Tone8,	///< 8ビット。
		Tone16,	///< 16ビット。
		ColorF16,	///< 16ビット浮動小数点数。
		ColorF32,	///< 32ビット浮動小数点数。
	};

}
}
#endif // __StationaryOrbit_Graphics_ImageFormat__