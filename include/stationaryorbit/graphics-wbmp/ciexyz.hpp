#ifndef __stationaryorbit_graphics_wbmp_ciexyz__
#define __stationaryorbit_graphics_wbmp_ciexyz__
#include <cstdint>
namespace zawa_ch::StationaryOrbit::Graphics::WBMP
{
    struct CIEXYZ_t
    {
        uint32_t X;
        uint32_t Y;
        uint32_t Z;
    };
    struct CIEXYZTriple_t
    {
        CIEXYZ_t Red;
        CIEXYZ_t Green;
        CIEXYZ_t Blue;
    };
}
#endif // __stationaryorbit_graphics_wbmp_ciexyz__