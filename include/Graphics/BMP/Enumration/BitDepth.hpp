#ifndef __StationaryOrbit_Graphics_BMP_BitDepth__
#define __StationaryOrbit_Graphics_BMP_BitDepth__
#include <cstdint>
namespace StationaryOrbit::Graphics::BMP
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

}
#endif // __StationaryOrbit_Graphics_BMP_BitDepth__