#include <climits>
#include "NumericAnalysis/Structure/CompensatedFloat.hpp"
#include "NumericAnalysis/Logic/TaylorSeries.hpp"

size_t StationaryOrbit::NumericAnalysis::TaylorSeries::DefaultSuc(const size_t& value)
{
	return value + 1;
}

StationaryOrbit::NumericAnalysis::TaylorSeries::TaylorSeries(BaseFunction func, const double& basep)
	: func(func), base(basep), suc(DefaultSuc), init(0U)
{}

StationaryOrbit::NumericAnalysis::TaylorSeries::TaylorSeries(BaseFunction func, const double& basep, SuccessorFunction successor, size_t init)
	: func(func), base(basep), suc(successor), init(init)
{}

double StationaryOrbit::NumericAnalysis::TaylorSeries::Calc(const double& value, size_t ceiling) const
{
	if ((func == NULL)||(suc == NULL)) throw NullReferenceException("");

	double x = value - base;
	// 初期値(i = 0)
	double exp = 1.0;
	double fraction = 1.0;
	CompensatedDouble sum = CompensatedDouble();
	double buffer = double(sum);
	size_t suc_buf = init;
	// それ以降(次の値は後続関数 suc() で導出)
	for(size_t i = 0U; i < ceiling; i++)
	{
		if (i != 0)
		{
			exp *= x;
			fraction *= i;
		}
		if (i == suc_buf)
		{
			suc_buf = suc(suc_buf);
			sum += func(i) * exp / fraction;
			if ((0U < i)&&(buffer == double(sum))) break;
			buffer = double(sum);
		}
	}
	return double(sum);
}

double StationaryOrbit::NumericAnalysis::TaylorSeries::Calc(const double& value) const
{
	return Calc(value, UINT_MAX);
}