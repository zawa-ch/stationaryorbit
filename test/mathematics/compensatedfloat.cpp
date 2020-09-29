//	stationaryorbit.test.mathematics:/compensatedfloat
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
#include "stationaryorbit/mathematics.primitives.hpp"
using namespace zawa_ch::StationaryOrbit;

void Test_CompensatedFloat()
{
    float sum1 = float();
    Mathematics::CompensatedSingle sum2 = Mathematics::CompensatedSingle();
    for(int i = 0; i < 10000; i++)
    {
        sum1 += 0.1f;
        sum2 += 0.1f;
    }
    std::cout << float(sum1) << ", " << float(sum2) << std::endl;
    return;
}
