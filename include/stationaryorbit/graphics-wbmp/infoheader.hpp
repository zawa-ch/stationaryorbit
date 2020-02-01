#ifndef __StationaryOrbit_Graphics_BMP_InfoHeader__
#define __StationaryOrbit_Graphics_BMP_InfoHeader__
#include <cstddef>
#include <cstdint>
#include "coreheader.hpp"
namespace zawa_ch::StationaryOrbit::Graphics::BMP
{

	enum class CompressionMethod : uint32_t
	{
		RGB,
		RLE8,
		RLE4,
		BITFIELDS,
		JPEG,
		PNG,
		ALPHABITFIELDS,
	};

	#pragma pack(1)
	struct InfoHeader
	{

		uint32_t HeaderSize;	///< ヘッダサイズ
		int32_t ImageWidth;	///< ビットマップの横幅
		int32_t ImageHeight;	///< ビットマップの縦幅
		uint16_t PlaneCount;	///< プレーン数
		BitDepth BitCount;	///< 1ピクセルあたりのビット数
		CompressionMethod ComplessionMethod;	///< 圧縮形式
		uint32_t ImageSize;	///< 画像データサイズ (単位はバイト)
		uint32_t ResolutionHolizonal;	///< 水平方向の解像度 (単位はピクセル/m)
		uint32_t ResolutionVertical;	///< 垂直方向の解像度 (単位はピクセル/m)
		uint32_t IndexedColorCount;	///< 使用する色数 ビットマップで実際に使用するカラーパレット内のカラーインデックスの数。
		uint32_t ImportantColorCount;	///< 重要な色数 ビットマップを表示するために必要なカラーインデックスの数。

		static const size_t Size;

	};
	#pragma pack()

}
#endif // __StationaryOrbit_Graphics_BMP_InfoHeader__