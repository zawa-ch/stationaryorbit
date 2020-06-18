#include <iostream>
#include "stationaryorbit/core.iteration.hpp"
using namespace zawa_ch::StationaryOrbit;

void Test_Iterator()
{
	std::vector<int> cont1 = {1, 2, 3, 4, 5};
	ForEach(LegacyIterator(cont1), [](auto item) { std::cout << item << std::endl; });
	LegacyIterator(cont1).ForEach(
		[](const auto& item)->void { std::cout << item << std::endl; }
	);
	LegacyReverseIterator(cont1).ForEach(
		[](const auto& item)->void { std::cout << item << std::endl; }
	);
}
