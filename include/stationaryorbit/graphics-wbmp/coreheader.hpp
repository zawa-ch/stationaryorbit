#ifndef __StationaryOrbit_Graphics_BMP_CoreHeader__
#define __StationaryOrbit_Graphics_BMP_CoreHeader__
#include <cstddef>
#include <cstdint>
namespace zawa_ch::StationaryOrbit::Graphics::BMP
{

	enum class BitDepth : uint16_t
	{
		Null = 0,
		Bit1 = 1,
		Bit4 = 4,
		Bit8 = 8,
		Bit16 = 16,
		Bit24 = 24,
		Bit32 = 32,
	};

	#pragma pack(1)
	struct CoreHeader
	{

		uint32_t HeaderSize;	///< ヘッダサイズ
		uint16_t ImageWidth;	///< ビットマップの横幅
		uint16_t ImageHeight;	///< ビットマップの縦幅
		uint16_t PlaneCount;	///< プレーン数
		BitDepth BitCount;	///< 1ピクセルあたりのビット数

		static const size_t Size;

	};
	#pragma pack()

}
#endif // __StationaryOrbit_Graphics_BMP_CoreHeader__