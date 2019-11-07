#include <iostream>
#include "General/Numeral"

void Test_FractionalDec()
{
    StationaryOrbit::FractionalDec fr1 = StationaryOrbit::FractionalDec(1, 5);
    StationaryOrbit::FractionalDec fr2 = StationaryOrbit::FractionalDec(3, 4);
    std::cout.precision(16);
    std::cout << "fr1 = " << double(fr1) << std::endl;
    std::cout << "fr2 = " << double(fr2) << std::endl;
    std::cout << "fr1 + fr2 = " << double(fr1 + fr2) << std::endl;
    std::cout << "fr2 - fr1 = " << double(fr2 - fr1) << std::endl;
    std::cout << "fr1 * fr1 = " << double(fr1 * fr1) << std::endl;
    std::cout << "fr2 * fr2 = " << double(fr2 * fr2) << std::endl;
    std::cout << "~fr2 = " << double(StationaryOrbit::FractionalDec::Max() - fr2) << std::endl;
    std::cout << "sqrt(fr1^2) = " << double((fr1 * fr1).Sqrt()) << std::endl;
    std::cout << "sqrt(fr1) = " << double((fr1).Sqrt()) << std::endl;
    std::cout << "epsiron = " << double(StationaryOrbit::FractionalDec::Epsiron()) << std::endl;
}
