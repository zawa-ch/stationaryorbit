//	stationaryorbit.mathematics:/polynomialfunction
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
#include "stationaryorbit/mathematics/compensatedfloat.hpp"
#include "stationaryorbit/mathematics/polynomialfunction.hpp"
using namespace zawa_ch::StationaryOrbit::Mathematics;

PolynomialFunction::PolynomialFunction(const std::vector<double>& value)
	: num(value)
{}

double PolynomialFunction::Calc(const double& value) const
{
	if (num.empty()) throw InvalidOperationException("");
	CompensatedDouble numvalue = CompensatedDouble();
	for(size_t i = num.size() - 1; 0 < i; i--)
	{
		numvalue += num[i];
		numvalue *= value;
	}
	numvalue += num[0];
	return double(numvalue);
}