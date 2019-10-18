#ifndef __StationaryOrbit_Graphics_BMP_CoreHeader__
#define __StationaryOrbit_Graphics_BMP_CoreHeader__
#include <cstddef>
#include <cstdint>
#include "../Enumration/BitDepth.hpp"
namespace StationaryOrbit::Graphics::BMP
{

	#pragma pack(1)
	struct CoreHeader
	{

		uint32_t HeaderSize;	///< ヘッダサイズ
		uint16_t ImageWidth;	///< ビットマップの横幅
		uint16_t ImageHeight;	///< ビットマップの縦幅
		uint16_t PlaneCount;	///< プレーン数
		BitDepth BitCount;	///< 1ピクセルあたりのビット数

	};
	#pragma pack()

}
#endif // __StationaryOrbit_Graphics_BMP_CoreHeader__