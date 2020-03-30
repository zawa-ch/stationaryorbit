#ifndef __stationaryorbit_graphics_dib_rgbquad__
#define __stationaryorbit_graphics_dib_rgbquad__
#include <cstdint>
namespace zawa_ch::StationaryOrbit::Graphics::DIB
{

    struct RGBQuad_t
    {
        uint8_t Red;
        uint8_t Green;
        uint8_t Blue;
        uint8_t Reserved;
    };

}
#endif // __stationaryorbit_graphics_dib_rgbquad__