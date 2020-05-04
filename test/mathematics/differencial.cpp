#include <iostream>
#include "stationaryorbit/mathematics/mathematic"
using namespace zawa_ch::StationaryOrbit;

void Test_Differencial()
{
	const double x_min = -0.5;
	const double x_max = 0.5;
	const size_t x_div = 10;

	Analysis::MathematicFunction<double> func = Analysis::MathematicFunction<double>(exp);
	Analysis::Differencial diff = Analysis::Differencial(func);
	for(size_t i = 0; i <= x_div; i++)
	{
		double x = x_min + ((x_max - x_min) * i / x_div);
		std::cout << "x= " << x << ", f(x)" << exp(x) << ", f'(x)= " << diff(x) << std::endl;
	}
	return;
}
