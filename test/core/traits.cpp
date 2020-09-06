#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>
#include "stationaryorbit/core.traits.hpp"
#include "stationaryorbit/core.numeral.hpp"
using namespace zawa_ch::StationaryOrbit;

void Test_Traits()
{
	std::cout << "<--- Traits --->" << std::endl;
	if (Traits::HasArithmeticOperation<int>) { std::cout << "HasArithmeticOperation<int> -> true" << std::endl; } else { throw std::exception(); }
	if (Traits::HasBitOperation<int>) { std::cout << "HasBitOperation<int> -> true" << std::endl; } else { throw std::exception(); }
	if (Traits::Comparable<int>) { std::cout << "Comparable<int> -> true" << std::endl; } else { throw std::exception(); }
	if (Traits::Equatable<int>) { std::cout << "Equatable<int> -> true" << std::endl; } else { throw std::exception(); }

	if (Traits::HasArithmeticOperation<double>) { std::cout << "HasArithmeticOperation<double> -> true" << std::endl; } else { throw std::exception(); }
	if (!Traits::HasBitOperation<double>) { std::cout << "HasBitOperation<double> -> false" << std::endl; } else { throw std::exception(); }
	if (Traits::Comparable<double>) { std::cout << "Comparable<double> -> true" << std::endl; } else { throw std::exception(); }
	if (Traits::Equatable<double>) { std::cout << "Equatable<double> -> true" << std::endl; } else { throw std::exception(); }

	if (!Traits::HasArithmeticOperation<std::string>) { std::cout << "HasArithmeticOperation<std::string> -> false" << std::endl; } else { throw std::exception(); }
	if (!Traits::HasBitOperation<std::string>) { std::cout << "HasBitOperation<std::string> -> false" << std::endl; } else { throw std::exception(); }
	if (Traits::Comparable<std::string>) { std::cout << "Comparable<std::string> -> true" << std::endl; } else { throw std::exception(); }
	if (Traits::Equatable<std::string>) { std::cout << "Equatable<std::string> -> true" << std::endl; } else { throw std::exception(); }

	if (Traits::HasArithmeticOperation<Proportion8_t>) { std::cout << "HasArithmeticOperation<Proportion8_t> -> true" << std::endl; } else { throw std::exception(); }
	if (!Traits::HasBitOperation<Proportion8_t>) { std::cout << "HasBitOperation<Proportion8_t> -> false" << std::endl; } else { throw std::exception(); }
	if (Traits::HasSaturateOperation<Proportion8_t>) { std::cout << "HasSaturateOperation<Proportion8_t> -> true" << std::endl; } else { throw std::exception(); }
	if (Traits::HasCheckedOperation<Proportion8_t>) { std::cout << "HasCheckedOperation<Proportion8_t> -> true" << std::endl; } else { throw std::exception(); }

	if (BitWidth<uint32_t> == 32UL) { std::cout << "BitWidth<uint32_t> -> " << BitWidth<uint32_t> << "[bit(s)]" << std::endl; } else { throw std::exception(); }
	if (BitWidth<int64_t> == 64UL) { std::cout << "BitWidth<int64_t> -> " << BitWidth<int64_t> << "[bit(s)]" << std::endl; } else { throw std::exception(); }
	if (BitWidth<bool> == 1UL) { std::cout << "BitWidth<bool> -> " << BitWidth<bool> << "[bit(s)]" << std::endl; } else { throw std::exception(); }
	std::cout << "sizeof(bool) -> " << sizeof(bool) << "[byte(s)]" << std::endl;
	if (BitWidth<std::bitset<14>> == 14UL) { std::cout << "BitWidth<std::bitset<14>> -> " << BitWidth<std::bitset<14>> << "[bit(s)]" << std::endl; } else { throw std::exception(); }
}
