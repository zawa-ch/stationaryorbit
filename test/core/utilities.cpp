//	stationaryorbit.test.core:/utilities
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
#include "stationaryorbit/core.utilities.hpp"
using namespace zawa_ch::StationaryOrbit;

void Test_ConstArray();
void Test_ZeroValue();

void Test_Utilities()
{
	Test_ConstArray();
	Test_ZeroValue();
}

constexpr int Suc(int i) { return i + 1; }
void Test_ConstArray()
{
	std::cout << "<--- ConstArray/ConstProgression --->" << std::endl;
	for (auto i: Range<size_t>(0, 10).GetStdIterator())
	{
		std::cout << ConstProgression<int, Suc, 1, 10>::values[i] << " ";
	}
	std::cout << std::endl;
}
void Test_ZeroValue()
{
	static_assert(Zero == false, "Zero == false ではありません。");
	static_assert(Zero == 0, "Zero == 0 ではありません。");
	static_assert(Zero == 0L, "Zero == 0L ではありません。");
	static_assert(Zero == 0UL, "Zero == 0UL ではありません。");
	static_assert(Zero == 0.0, "Zero == 0.0 ではありません。");
	static_assert(Zero == '\0', "Zero == '\\0' ではありません。");
	static_assert(Zero == (void*)(0), "Zero == (void*)0 ではありません。");
	static_assert((5 + Zero) == 5, "5 + Zero == 5 ではありません。");
}
