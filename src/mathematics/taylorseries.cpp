//	stationaryorbit.mathematics:/taylorseries
//	Copyright 2020 zawa-ch.
//	GPLv3 (or later) license
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//	See the GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program.
//	If not, see <http://www.gnu.org/licenses/>.
//
#include <climits>
#include "stationaryorbit/mathematics/compensatedfloat.hpp"
#include "stationaryorbit/mathematics/taylorseries.hpp"
using namespace zawa_ch::StationaryOrbit::Mathematics;

size_t TaylorSeries::DefaultSuc(const size_t& value)
{
	return value + 1;
}

TaylorSeries::TaylorSeries(BaseFunction func, const double& basep)
	: func(func), base(basep), suc(DefaultSuc), init(0U)
{}

TaylorSeries::TaylorSeries(BaseFunction func, const double& basep, SuccessorFunction successor, size_t init)
	: func(func), base(basep), suc(successor), init(init)
{}

double TaylorSeries::Calc(const double& value, size_t ceiling) const
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

double TaylorSeries::Calc(const double& value) const
{
	return Calc(value, UINT_MAX);
}
