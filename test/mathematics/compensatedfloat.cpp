#include <iostream>
#include "stationaryorbit/analysis/numerals"
using namespace zawa_ch::StationaryOrbit;

void Test_CompensatedFloat()
{
    float sum1 = float();
    Analysis::CompensatedSingle sum2 = Analysis::CompensatedSingle();
    for(int i = 0; i < 10000; i++)
    {
        sum1 += 0.1f;
        sum2 += 0.1f;
    }
    std::cout << float(sum1) << ", " << float(sum2) << std::endl;
    return;
}
