#ifndef __stationaryorbit_graphics_dib_colormask__
#define __stationaryorbit_graphics_dib_colormask__
#include <optional>
#include "stationaryorbit/core/bitoperation"
namespace zawa_ch::StationaryOrbit::Graphics::DIB
{

	struct ColorMask final
	{
		BitMask<uint32_t> RedMask;
		BitMask<uint32_t> GreenMask;
		BitMask<uint32_t> BlueMask;
		std::optional<BitMask<uint32_t>> AlphaMask;
	};

}
#endif // __stationaryorbit_graphics_dib_colormask__