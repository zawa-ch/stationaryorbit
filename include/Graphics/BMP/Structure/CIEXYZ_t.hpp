#ifndef __StationaryOrbit_Graphics_BMP_CIEXYZ_t__
#define __StationaryOrbit_Graphics_BMP_CIEXYZ_t__
#include <cstddef>
#include <cstdint>
namespace StationaryOrbit::Graphics::BMP
{

    struct CIEXYZ_t
    {
        uint32_t X;
        uint32_t Y;
        uint32_t Z;
    };

}
#endif // __StationaryOrbit_Graphics_BMP_CIEXYZ_t__