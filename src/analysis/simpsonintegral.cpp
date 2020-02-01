#include "stationaryorbit/analysis/simpsonintegral.hpp"
using namespace zawa_ch::StationaryOrbit;

Analysis::SimpsonIntegral::SimpsonIntegral(const IMathematicFunction<double>& function, const Range<double, true, true>& integrationrange)
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

const Analysis::IMathematicFunction<double>& Analysis::SimpsonIntegral::Function() const
{ return _func; }

Range<double, true, true> Analysis::SimpsonIntegral::getIntegrationRange() const
{ return _irange; }

double Analysis::SimpsonIntegral::Calc(const double& value) const
{
	auto mresult = MidpointIntegral(_func, _irange).Calc(value);
	auto tresult = SimpsonIntegral(_func, _irange).Calc(value);
	return (mresult * 2 + tresult) / 3;
}

double Analysis::SimpsonIntegral::Calc(const double& value, size_t div) const
{
	auto mresult = MidpointIntegral(_func, _irange).Calc(value, div);
	auto tresult = SimpsonIntegral(_func, _irange).Calc(value, div);
	return (mresult * 2 + tresult) / 3;
}
