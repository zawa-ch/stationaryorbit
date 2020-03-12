#ifndef __stationaryorbit_graphics_wbmp_ciexyztriple__
#define __stationaryorbit_graphics_wbmp_ciexyztriple__
#include "ciexyz.hpp"
namespace zawa_ch::StationaryOrbit::Graphics::WBMP
{

    struct CIEXYZTriple_t
    {
        CIEXYZ_t Red;
        CIEXYZ_t Green;
        CIEXYZ_t Blue;
    };

}
#endif // __stationaryorbit_graphics_wbmp_ciexyztriple__