//	stationaryorbit.mathematics:/differencial
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
#include <cmath>
#include <climits>
#include <limits>
#include "stationaryorbit/mathematics/differencial.hpp"
using namespace zawa_ch::StationaryOrbit::Mathematics;

double Differencial::Diff(const double& value, const double& h) const
{
	return func.Calc(value + h) - func.Calc(value);
}

double Differencial::DefaultH(const double& value) const
{
	const double epsilon = std::numeric_limits<double>::epsilon();
	double h = epsilon;
	if (0.0 < std::abs(value)) h *= std::abs(value);
	double i = (epsilon * 1048576) / Diff(value, h);
	return h * i;
}

Differencial::Differencial(const IMathematicFunction<double>& function)
	: func(function)
{}

double Differencial::Calc(const double& value, const double& h) const
{
	return Diff(value, h) / h;
}

double Differencial::Calc(const double& value) const
{
	return Calc(value, DefaultH(value));
}
