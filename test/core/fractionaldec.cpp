#include <iostream>
#include "stationaryorbit/core/numeral"
using namespace zawa_ch::StationaryOrbit;

void Test_FractionalDec()
{
    FractionalDec fr1 = FractionalDec(1, 5);
    FractionalDec fr2 = FractionalDec(3, 4);
    std::cout.precision(16);
    std::cout << "fr1 = " << double(fr1) << std::endl;
    std::cout << "fr2 = " << double(fr2) << std::endl;
    std::cout << "fr1 + fr2 = " << double(fr1 + fr2) << std::endl;
    std::cout << "fr2 - fr1 = " << double(fr2 - fr1) << std::endl;
    std::cout << "fr1 * fr1 = " << double(fr1 * fr1) << std::endl;
    std::cout << "fr2 * fr2 = " << double(fr2 * fr2) << std::endl;
    std::cout << "~fr2 = " << double(FractionalDec::Max() - fr2) << std::endl;
    std::cout << "sqrt(fr1^2) = " << double((fr1 * fr1).Sqrt()) << std::endl;
    std::cout << "sqrt(fr1) = " << double((fr1).Sqrt()) << std::endl;
    std::cout << "epsiron = " << double(FractionalDec::Epsiron()) << std::endl;
    std::cout << "~epsiron = " << double(FractionalDec::Max() - FractionalDec::Epsiron()) << std::endl;
    std::cout << "1 == ~epsiron = " << bool((FractionalDec::Max())==(FractionalDec::Max() - FractionalDec::Epsiron())) << std::endl;
}
