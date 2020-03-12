#ifndef __stationaryorbit_graphics_wbmp_ciexyz__
#define __stationaryorbit_graphics_wbmp_ciexyz__
#include <cstddef>
#include <cstdint>
namespace zawa_ch::StationaryOrbit::Graphics::WBMP
{

    struct CIEXYZ_t
    {
        uint32_t X;
        uint32_t Y;
        uint32_t Z;
    };

}
#endif // __stationaryorbit_graphics_wbmp_ciexyz__