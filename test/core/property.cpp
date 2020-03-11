#include <iostream>
#include "stationaryorbit/core/property"
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
