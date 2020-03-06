#include <iostream>
#include "stationaryorbit/core/numeral"
using namespace zawa_ch::StationaryOrbit;

void Test_Range()
{
    for(auto i : Range(0, 10))
    {
        std::cout << i << std::endl;
    }
    auto frange = Range(0.0f, 1.0f);
    std::cout << frange.isIncluded(0.5f) << std::endl;
}
