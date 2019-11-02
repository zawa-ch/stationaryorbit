#include <iostream>
#include "NumericAnalysis/General"

void Test_CompensatedFloat()
{
    float sum1 = float();
    StationaryOrbit::NumericAnalysis::CompensatedSingle sum2 = StationaryOrbit::NumericAnalysis::CompensatedSingle();
    for(int i = 0; i < 10000; i++)
    {
        sum1 += 0.1f;
        sum2 += 0.1f;
    }
    std::cout << float(sum1) << ", " << float(sum2) << std::endl;
    return;
}
