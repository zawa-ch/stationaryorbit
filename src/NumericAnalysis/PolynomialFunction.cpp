#include "NumericAnalysis/Logic/PolynomialFunction.hpp"
#include "NumericAnalysis/Structure/CompensatedFloat.hpp"

StationaryOrbit::NumericAnalysis::PolynomialFunction::PolynomialFunction(const std::vector<double>& value)
	: num(value)
{}

double StationaryOrbit::NumericAnalysis::PolynomialFunction::Calc(const double& value) const
{
	if (num.empty()) throw InvalidOperationException("");
	CompensatedDouble numvalue = CompensatedDouble();
	for(size_t i = num.size() - 1; 0 < i; i--)
	{
		numvalue += num[i];
		numvalue *= value;
	}
	numvalue += num[0];
	return double(numvalue);
}