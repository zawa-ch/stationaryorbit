#include <climits>
#include "NumericAnalysis/Structure/CompensatedFloat.hpp"
#include "NumericAnalysis/Logic/TaylorSeries.hpp"

size_t StationaryOrbit::NumericAnalysis::TaylorSeries::DefaultSuc(const size_t& value)
{
	return value + 1;
}

StationaryOrbit::NumericAnalysis::TaylorSeries::TaylorSeries(BaseFunction func, const double& basep)
	: func(func), base(basep), suc(DefaultSuc)
{}

StationaryOrbit::NumericAnalysis::TaylorSeries::TaylorSeries(BaseFunction func, const double& basep, SuccessorFunction successor)
	: func(func), base(basep), suc(successor)
{}

double StationaryOrbit::NumericAnalysis::TaylorSeries::Calc(const double& value, size_t ceiling) const
{
	if ((func == NULL)||(suc == NULL)) throw NullReferenceException("");

	double x = value - base;
	// 初期値(i = 0)
	double exp = 1.0;
	double fraction = 1.0;
	CompensatedDouble sum = CompensatedDouble(func(0));
	double buffer = double(sum);
	size_t suc_buf = 0U;
	// それ以降(次の値は後続関数 suc() で導出)
	for(size_t i = suc(0U); (i < ceiling)&&(suc_buf < i); i = suc(i))
	{
		suc_buf = i;
		exp *= x;
		fraction *= i;
		sum += func(i) * exp / fraction;
		if (buffer == double(sum)) break;
		buffer = double(sum);
	}
	return double(sum);
}

double StationaryOrbit::NumericAnalysis::TaylorSeries::Calc(const double& value) const
{
	return Calc(value, UINT_MAX);
}
