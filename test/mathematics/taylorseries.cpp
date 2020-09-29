//	stationaryorbit.test.mathematics:/taylorseries
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
#include <iostream>
#include <stdexcept>
#include <cmath>
#include "stationaryorbit/mathematics.algorithm.hpp"
using namespace zawa_ch::StationaryOrbit;

double exp0(const size_t& n);
double sin_f(const size_t& n);
size_t sin_suc(const size_t& n);
double cos_f(const size_t& n);
size_t cos_suc(const size_t& n);

void Test_TaylorSeries1()
{
	const double x_min = -1.0;
	const double x_max = 1.0;
	const size_t x_div = 20;
    Mathematics::TaylorSeries func1 = Mathematics::TaylorSeries(exp0, 0.0);
	for(size_t i = 0; i <= x_div; i++)
	{
		double x = x_min + ((x_max - x_min) * i / x_div);
		std::cout << "x= " << x << ", f1(x)= " << func1(x) << std::endl;
	}
	return;
}

void Test_TaylorSeries2()
{
	const double x_min = 0;
	const double x_max = M_PI_2;
	const size_t x_div = 10;
    Mathematics::TaylorSeries func2 = Mathematics::TaylorSeries(sin_f, 0.0, sin_suc, 1U);
    Mathematics::TaylorSeries func3 = Mathematics::TaylorSeries(cos_f, 0.0, cos_suc, 0U);
	for(size_t i = 0; i <= x_div; i++)
	{
		double x = x_min + ((x_max - x_min) * i / x_div);
		std::cout << "x= " << x << ", f2(x)= " << func2(x) << ", f3(x)= " << func3(x) << std::endl;
	}
	return;
}

double exp0(const size_t& n)
{
    return 1.0;
}

double sin_f(const size_t& n)
{
	switch(n % 4)
	{
		case 0:	return 0.0;
		case 1: return 1.0;
		case 2: return 0.0;
		case 3: return -1.0;
		default: throw std::runtime_error("Can't reach");
	}
}

size_t sin_suc(const size_t& n)
{
	return n + 2;
}

double cos_f(const size_t& n)
{
	switch(n % 4)
	{
		case 0: return 1.0;
		case 1:	return 0.0;
		case 2: return -1.0;
		case 3: return 0.0;
		default: throw std::runtime_error("Can't reach");
	}
}

size_t cos_suc(const size_t& n)
{
	return n + 2;
}
