#include "NumericAnalysis/Logic/PolynomialFunction.hpp"
#include "NumericAnalysis/Structure/CompensatedFloat.hpp"

StationaryOrbit::NumericAnalysis::PolynomialFunction::PolynomialFunction(const std::vector<double>& numerator)
	: PolynomialFunction(numerator, std::vector<double> {1})
{}

StationaryOrbit::NumericAnalysis::PolynomialFunction::PolynomialFunction(const std::vector<double>& numerator, const std::vector<double>& denominator)
	: num(numerator), denom(denominator)
{}

double StationaryOrbit::NumericAnalysis::PolynomialFunction::Calc(const double& value) const
{
	if (num.empty() || denom.empty()) throw InvalidOperationException("");
	CompensatedDouble numvalue = CompensatedDouble();
	CompensatedDouble denvalue = CompensatedDouble();
	for(size_t i = num.size() - 1; 0 < i; i--)
	{
		numvalue += num[i];
		numvalue *= value;
	}
	numvalue += num[0];
	for(size_t i = denom.size() - 1; 0 < i; i--)
	{
		denvalue += denom[i];
		denvalue *= value;
	}
	denvalue += denom[0];
	return double(numvalue)/double(denvalue);
}