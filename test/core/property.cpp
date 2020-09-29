//	stationaryorbit.test.core:/property
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
#include "stationaryorbit/core.property.hpp"
using namespace zawa_ch::StationaryOrbit;

class testcase
{
private:
	int _x;
	static int getx(const testcase& inst) { return inst._x; }
	static void setx(testcase& inst, const int& value) { inst._x = value; }
public:
	testcase() = default;
	testcase(const int& x) : _x(x) {}
	Property<testcase, int> X() { return Property<testcase, int>(*this, getx, setx); }
};

void Test_Property()
{
	auto test = testcase(10);
	std::cout << test.X() << std::endl;
}
