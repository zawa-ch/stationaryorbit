#include <cmath>
#include <iostream>
#include "stationaryorbit/mathematics/mathematic"
using namespace zawa_ch::StationaryOrbit;

void Test_NewtonCoef()
{
	const double x_min = -0.5;
	const double x_max = 0.5;
	const size_t x_div = 10;
    const size_t m_div = 7;
    std::vector<double> mpt = std::vector<double>();
    for(size_t i = 0; i <= m_div; i++)
    {
		double x = x_min + ((x_max - x_min) * i / m_div);
        mpt.push_back(x);
    }
    Analysis::NewtonCoef comp = Analysis::NewtonCoef(Analysis::MathematicFunction<double>(exp), mpt);
	for(size_t i = 0; i <= x_div; i++)
	{
		double x = x_min + ((x_max - x_min) * i / x_div);
		std::cout << "x= " << x << ", f(x)" << exp(x) << ", comp(x)= " << comp(x) << std::endl;
	}
	return;
}
