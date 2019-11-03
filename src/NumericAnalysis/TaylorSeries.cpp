#include <climits>
#include "NumericAnalysis/Structure/CompensatedFloat.hpp"
#include "NumericAnalysis/Logic/TaylorSeries.hpp"

StationaryOrbit::NumericAnalysis::TaylorSeries::TaylorSeries(BaseFunction func, const double& basep)
	: func(func), base(basep)
{}

double StationaryOrbit::NumericAnalysis::TaylorSeries::Calc(const double& value, size_t ceiling) const
{
	if (func == NULL) throw NullReferenceException("");
	CompensatedDouble sum = CompensatedDouble();
	double x = value - base;
	double exp = 1.0;
	double fraction = 1.0;
	double buffer = double();
	for(size_t i = 0; i < ceiling; i++)
	{
		buffer = double(sum);
		sum += func(i) * exp / fraction;
		if (buffer == double(sum)) break;
		exp *= x;
		fraction *= i + 1;
	}
	return double(sum);
}

double StationaryOrbit::NumericAnalysis::TaylorSeries::Calc(const double& value) const
{
	return Calc(value, UINT_MAX);
}
