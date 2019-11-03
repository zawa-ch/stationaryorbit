#include <iostream>
#include "NumericAnalysis/Mathmatic"

double exp0(const size_t& n);

void Test_TaylorSeries()
{
	const double x_min = -1.0;
	const double x_max = 1.0;
	const size_t x_div = 20;
    StationaryOrbit::NumericAnalysis::TaylorSeries func1 = StationaryOrbit::NumericAnalysis::TaylorSeries(exp0, 0.0);
	for(size_t i = 0; i <= x_div; i++)
	{
		double x = x_min + ((x_max - x_min) * i / x_div);
		std::cout << "x= " << x << ", f1(x)= " << func1(x) << std::endl;
	}
	return;
}

double exp0(const size_t& n)
{
    return 1.0;
}
