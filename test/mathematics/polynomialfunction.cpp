//	stationaryorbit.test.mathematics:/polynomialfunction
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
#include "stationaryorbit/mathematics.algorithm.hpp"
using namespace zawa_ch::StationaryOrbit;

void Test_PolynomialFunction()
{
	const double x_min = -1.0;
	const double x_max = 1.0;
	const size_t x_div = 20;
	auto func1 = Mathematics::PolynomialFunction<double, 3>({ 0.0, 0.0, 1.0 });
	auto func2 = Mathematics::PolynomialFunction<double, 4>({ -1.0, 0.0, -7.0, -5.0 });
	for(size_t i = 0; i <= x_div; i++)
	{
		double x = x_min + ((x_max - x_min) * i / x_div);
		std::cout << "x= " << x << ", f1(x)= " << func1(x) << ", f2(x)= " << func2(x) << std::endl;
	}
	return;
}
