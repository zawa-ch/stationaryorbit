#include <cmath>
#include <climits>
#include <limits>
#include "stationaryorbit/mathematics/differencial.hpp"
using namespace zawa_ch::StationaryOrbit::Mathematics;

double Differencial::Diff(const double& value, const double& h) const
{
	return func.Calc(value + h) - func.Calc(value);
}

double Differencial::DefaultH(const double& value) const
{
	const double epsilon = std::numeric_limits<double>::epsilon();
	double h = epsilon;
	if (0.0 < std::abs(value)) h *= std::abs(value);
	double i = (epsilon * 1048576) / Diff(value, h);
	return h * i;
}

Differencial::Differencial(const IMathematicFunction<double>& function)
	: func(function)
{}

double Differencial::Calc(const double& value, const double& h) const
{
	return Diff(value, h) / h;
}

double Differencial::Calc(const double& value) const
{
	return Calc(value, DefaultH(value));
}
