//	stationaryorbit.test.mathematics:/differencial
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

void Test_Differencial()
{
	const double x_min = -0.5;
	const double x_max = 0.5;
	const size_t x_div = 10;

	Mathematics::MathematicFunction<double> func = Mathematics::MathematicFunction<double>(exp);
	Mathematics::Differencial diff = Mathematics::Differencial(func);
	for(size_t i = 0; i <= x_div; i++)
	{
		double x = x_min + ((x_max - x_min) * i / x_div);
		std::cout << "x= " << x << ", f(x)" << exp(x) << ", f'(x)= " << diff(x) << std::endl;
	}
	return;
}
