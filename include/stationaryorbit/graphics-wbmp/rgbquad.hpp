#ifndef __stationaryorbit_graphics_wbmp_rgbquad__
#define __stationaryorbit_graphics_wbmp_rgbquad__
#include <cstdint>
namespace zawa_ch::StationaryOrbit::Graphics::WBMP
{

    struct RGBQuad_t
    {
        uint8_t Red;
        uint8_t Green;
        uint8_t Blue;
        uint8_t Reserved;
    };

}
#endif // __stationaryorbit_graphics_wbmp_rgbquad__