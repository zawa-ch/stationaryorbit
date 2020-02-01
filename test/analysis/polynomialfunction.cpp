#include <iostream>
#include "stationaryorbit/analysis/mathematic"
using namespace zawa_ch::StationaryOrbit;

void Test_PolynomialFunction()
{
	const double x_min = -1.0;
	const double x_max = 1.0;
	const size_t x_div = 20;
	Analysis::PolynomialFunction func1 = Analysis::PolynomialFunction(std::vector<double>{ 0.0, 0.0, 1.0 });
	Analysis::PolynomialFunction func2 = Analysis::PolynomialFunction(std::vector<double>{ -1.0, 0.0, -7.0, -5.0 });
	for(size_t i = 0; i <= x_div; i++)
	{
		double x = x_min + ((x_max - x_min) * i / x_div);
		std::cout << "x= " << x << ", f1(x)= " << func1(x) << ", f2(x)= " << func2(x) << std::endl;
	}
	return;
}
