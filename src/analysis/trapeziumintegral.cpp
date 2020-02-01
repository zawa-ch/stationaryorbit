#include "NumericAnalysis/Structure/CompensatedFloat.hpp"
#include "NumericAnalysis/Logic/TrapeziumIntegral.hpp"

StationaryOrbit::NumericAnalysis::TrapeziumIntegral::TrapeziumIntegral(const IMathematicFunction<double>& function, const Range<double, true, true>& integrationrange)
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

const StationaryOrbit::NumericAnalysis::IMathematicFunction<double>& StationaryOrbit::NumericAnalysis::TrapeziumIntegral::Function() const
{ return _func; }

StationaryOrbit::Range<double, true, true> StationaryOrbit::NumericAnalysis::TrapeziumIntegral::getIntegrationRange() const
{ return _irange; }

double StationaryOrbit::NumericAnalysis::TrapeziumIntegral::Calc(const double& value) const
{
	return (_func.Calc(_irange.getFloor()) + _func.Calc(_irange.getCailing())) * _irange.Length() / 2;
}

double StationaryOrbit::NumericAnalysis::TrapeziumIntegral::Calc(const double& value, size_t div) const
{
	auto result = CompensatedDouble(0.0);
	auto length = _irange.Length();
	for (size_t i = 0; i < div; i++)
	{
		result += (_func.Calc(length * i) + _func.Calc(length * (i + 1))) * length / div / 2;
	}
	return result.getValue();
}
