#include "NumericAnalysis/Structure/CompensatedFloat.hpp"
#include "NumericAnalysis/Logic/MidpointIntegral.hpp"

StationaryOrbit::NumericAnalysis::MidpointIntegral::MidpointIntegral(const IMathematicFunction<double>& function, const Range<double, true, true>& integrationrange)
	: _func(function), _irange(integrationrange)
{
	if (
		!(
			(std::numeric_limits<double>::lowest() <= integrationrange.getFloor())
			&&(integrationrange.getFloor() <= std::numeric_limits<double>::max())
			&&(std::numeric_limits<double>::lowest() <= integrationrange.getCailing())
			&&(integrationrange.getCailing() <= std::numeric_limits<double>::max())
		)
	)
	{ throw std::invalid_argument("引数 integrationrange として指定可能な範囲は有限な実数である必要があります。"); }
}

const StationaryOrbit::NumericAnalysis::IMathematicFunction<double>& StationaryOrbit::NumericAnalysis::MidpointIntegral::Function() const
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
	auto length = _irange.Length();
	for (size_t i = 0; i < div; i++)
	{
		result += _func.Calc(_irange.getFloor() + (((length * i) + (length * (i + 1)) / div / 2)));
	}
	return result.getValue();
}
