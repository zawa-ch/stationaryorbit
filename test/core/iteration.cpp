//	stationaryorbit.test.core:/iteration
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
#include "stationaryorbit/core.iteration.hpp"
using namespace zawa_ch::StationaryOrbit;

void Test_Iterator();

void Test_Iteration()
{
	Test_Iterator();
}

void Test_Iterator()
{
	std::cout << "<--- Iterator --->" << std::endl;
	std::vector<int> cont1 = {1, 2, 3, 4, 5};
	ItrProcesser::ForEach(LegacyIterator(cont1), [](auto item) { std::cout << item << " "; });
	std::cout << std::endl;
	ItrProcesser::ForEach(LegacyReverseIterator(cont1), [](const auto& item)->void { std::cout << item << " "; });
	std::cout << std::endl;
}
