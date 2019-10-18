#ifndef __StationaryOrbit_Graphics_BMP_CompressionMethod__
#define __StationaryOrbit_Graphics_BMP_CompressionMethod__
#include <cstdint>
namespace StationaryOrbit::Graphics::BMP
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

}
#endif // __StationaryOrbit_Graphics_BMP_CompressionMethod__