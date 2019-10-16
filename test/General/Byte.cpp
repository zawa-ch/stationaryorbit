#include <iostream>
#include "General/General"

using namespace StationaryOrbit;

int Test_Byte()
{
    StationaryOrbit::Byte b1 = StationaryOrbit::Byte(0x55);
    StationaryOrbit::Byte b2 = StationaryOrbit::Byte(0xAA);

    std::cout << "b1: " << b1 << std::endl;
    std::cout << "b2: " << b2 << std::endl;
    std::cout << "b1[1]: " << b1[1] << std::endl;
    std::cout << "b2[3]: " << b2[3] << std::endl;
    std::cout << "b1 | b2: " << (b1 | b2) << std::endl;
    std::cout << "b1 & b2: " << (b1 & b2) << std::endl;
    std::cout << "~b1: " << (~b1) << std::endl;

    return 0;
}
