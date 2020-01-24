#include "NumericAnalysis/Structure/CompensatedFloat.hpp"
#include "NumericAnalysis/Logic/MidpointIntegral.hpp"

StationaryOrbit::NumericAnalysis::MidpointIntegral::MidpointIntegral(const IMathmaticFunction<double>& function, const Range<double, true, true>& integrationrange)
	: _func(function), _irange(integrationrange)
{
	if ((integrationrange.getFloor() < std::numeric_limits<double>::lowest())&&(std::numeric_limits<double>::max() < integrationrange.getCailing()))
	{ throw std::invalid_argument(""); }
}

const StationaryOrbit::NumericAnalysis::IMathmaticFunction<double>& StationaryOrbit::NumericAnalysis::MidpointIntegral::Function() const
{ return _func; }

StationaryOrbit::Range<double, true, true> StationaryOrbit::NumericAnalysis::MidpointIntegral::getIntegrationRange() const
{ return _irange; }

double StationaryOrbit::NumericAnalysis::MidpointIntegral::Calc(const double& value) const
{
	return _irange.Length() * _func.Calc((_irange.getFloor() + _irange.getCailing()) / 2);
}

double StationaryOrbit::NumericAnalysis::MidpointIntegral::Calc(const double& value, size_t div) const
{
	auto result = CompensatedDouble(0.0);
	for (size_t i = 0; i < div; i++)
	{
		result += _func.Calc(_irange.getFloor() + (((_irange.Length() * i) + (_irange.Length() * (i + 1)) / div / 2)));
	}
	return result.getValue();
}
