//	stationaryorbit.test.core:/traits
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
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>
#include "stationaryorbit/core.traits.hpp"
using namespace zawa_ch::StationaryOrbit;

void Test_Traits()
{
	std::cout << "<--- Traits --->" << std::endl;
	if (Traits::HasArithmeticOperation<int>) { std::cout << "HasArithmeticOperation<int> -> true" << std::endl; } else { throw std::exception(); }
	if (Traits::HasBitOperation<int>) { std::cout << "HasBitOperation<int> -> true" << std::endl; } else { throw std::exception(); }
	if (Traits::IsIntegerType<int>) { std::cout << "IsIntegerType<int> -> true" << std::endl; } else { throw std::exception(); }
	if (Traits::Comparable<int>) { std::cout << "Comparable<int> -> true" << std::endl; } else { throw std::exception(); }
	if (Traits::Equatable<int>) { std::cout << "Equatable<int> -> true" << std::endl; } else { throw std::exception(); }

	if (Traits::HasArithmeticOperation<double>) { std::cout << "HasArithmeticOperation<double> -> true" << std::endl; } else { throw std::exception(); }
	if (!Traits::HasBitOperation<double>) { std::cout << "HasBitOperation<double> -> false" << std::endl; } else { throw std::exception(); }
	if (!Traits::IsIntegerType<double>) { std::cout << "IsIntegerType<double> -> false" << std::endl; } else { throw std::exception(); }
	if (Traits::Comparable<double>) { std::cout << "Comparable<double> -> true" << std::endl; } else { throw std::exception(); }
	if (Traits::Equatable<double>) { std::cout << "Equatable<double> -> true" << std::endl; } else { throw std::exception(); }

	if (!Traits::HasArithmeticOperation<std::string>) { std::cout << "HasArithmeticOperation<std::string> -> false" << std::endl; } else { throw std::exception(); }
	if (!Traits::HasBitOperation<std::string>) { std::cout << "HasBitOperation<std::string> -> false" << std::endl; } else { throw std::exception(); }
	if (!Traits::IsIntegerType<std::string>) { std::cout << "IsIntegerType<std::string> -> false" << std::endl; } else { throw std::exception(); }
	if (Traits::Comparable<std::string>) { std::cout << "Comparable<std::string> -> true" << std::endl; } else { throw std::exception(); }
	if (Traits::Equatable<std::string>) { std::cout << "Equatable<std::string> -> true" << std::endl; } else { throw std::exception(); }

	if (BitWidth<uint32_t> == 32UL) { std::cout << "BitWidth<uint32_t> -> " << BitWidth<uint32_t> << "[bit(s)]" << std::endl; } else { throw std::exception(); }
	if (BitWidth<int64_t> == 64UL) { std::cout << "BitWidth<int64_t> -> " << BitWidth<int64_t> << "[bit(s)]" << std::endl; } else { throw std::exception(); }
	if (BitWidth<bool> == 1UL) { std::cout << "BitWidth<bool> -> " << BitWidth<bool> << "[bit(s)]" << std::endl; } else { throw std::exception(); }
	std::cout << "sizeof(bool) -> " << sizeof(bool) << "[byte(s)]" << std::endl;
	if (BitWidth<std::bitset<14>> == 14UL) { std::cout << "BitWidth<std::bitset<14>> -> " << BitWidth<std::bitset<14>> << "[bit(s)]" << std::endl; } else { throw std::exception(); }
}
