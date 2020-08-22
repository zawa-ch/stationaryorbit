#include <iostream>
#include "stationaryorbit/core.iteration.hpp"
using namespace zawa_ch::StationaryOrbit;

void Test_Iterator()
{
	std::cout << "<--- Iteration --->" << std::endl;
	std::vector<int> cont1 = {1, 2, 3, 4, 5};
	ItrProcesser::ForEach(LegacyIterator(cont1), [](auto item) { std::cout << item << " "; });
	std::cout << std::endl;
	ItrProcesser::ForEach(LegacyReverseIterator(cont1), [](const auto& item)->void { std::cout << item << " "; });
	std::cout << std::endl;
}
