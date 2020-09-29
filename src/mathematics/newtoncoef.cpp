//	stationaryorbit.mathematics:/newtoncoef
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
#include "stationaryorbit/mathematics/newtoncoef.hpp"
using namespace zawa_ch::StationaryOrbit::Mathematics;

void NewtonCoef::Complete()
{
    if (x.size() != b.size()) throw InvalidOperationException("illegal-state");
    for (size_t i = 0; i < b.size()-1; i++)
    {
        b.back() = (b.back() - b[i])/(x.back() - x[i]);
    }
}

NewtonCoef::NewtonCoef(const std::vector<Vector2d>& list)
    : x(), b()
{
    x.reserve(list.size());
    b.reserve(list.size());
    for (const Vector2d& pt : list)
    {
        x.push_back(pt.getX());
        b.push_back(pt.getY());
        Complete();
    }
}

NewtonCoef::NewtonCoef(const IMathematicFunction<double>& func, const std::vector<double> xlist)
    : x(), b()
{
    x.reserve(xlist.size());
    b.reserve(xlist.size());
    for (const double& ptx : xlist)
    {
        x.push_back(ptx);
        b.push_back(func.Calc(ptx));
        Complete();
    }
}

double NewtonCoef::Calc(const double& value) const
{
    CompensatedDouble result = CompensatedDouble(b.back());
    for (size_t i = b.size() - 1; 0 < i; i--)
    {
        result = result * (value - x[i-1]) + b[i-1];
    }
    return double(result);
}
