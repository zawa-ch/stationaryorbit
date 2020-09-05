#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>
#include "stationaryorbit/core.traits.hpp"
using namespace zawa_ch::StationaryOrbit;

void Test_Traits()
{
	std::cout << "<--- Traits --->" << std::endl;
	if (Traits::ArithmeticOperatable<int>) { std::cout << "ArithmeticOperatable<int> -> true" << std::endl; } else { throw std::exception(); }
	if (Traits::Comparable<int>) { std::cout << "Comparable<int> -> true" << std::endl; } else { throw std::exception(); }
	if (Traits::Equatable<int>) { std::cout << "Equatable<int> -> true" << std::endl; } else { throw std::exception(); }

	if (Traits::ArithmeticOperatable<double>) { std::cout << "ArithmeticOperatable<double> -> true" << std::endl; } else { throw std::exception(); }
	if (Traits::Comparable<double>) { std::cout << "Comparable<double> -> true" << std::endl; } else { throw std::exception(); }
	if (Traits::Equatable<double>) { std::cout << "Equatable<double> -> true" << std::endl; } else { throw std::exception(); }

	if (!Traits::ArithmeticOperatable<std::string>) { std::cout << "ArithmeticOperatable<std::string> -> false" << std::endl; } else { throw std::exception(); }
	if (Traits::Comparable<std::string>) { std::cout << "Comparable<std::string> -> true" << std::endl; } else { throw std::exception(); }
	if (Traits::Equatable<std::string>) { std::cout << "Equatable<std::string> -> true" << std::endl; } else { throw std::exception(); }

	if (BitWidth<uint32_t> == 32UL) { std::cout << "BitWidth<uint32_t> -> 32" << std::endl; } else { throw std::exception(); }
	if (BitWidth<int64_t> == 64UL) { std::cout << "BitWidth<int64_t> -> 64" << std::endl; } else { throw std::exception(); }
	if (BitWidth<bool> == 1UL) { std::cout << "BitWidth<bool> -> 1" << std::endl; } else { throw std::exception(); }
	std::cout << "sizeof(bool) -> " << sizeof(bool) << std::endl;
	if (BitWidth<std::bitset<14>> == 14UL) { std::cout << "BitWidth<std::bitset<14>> -> 14" << std::endl; } else { throw std::exception(); }
}
