#include <iostream>
#include "stationaryorbit/core/bitreference"
using namespace zawa_ch::StationaryOrbit;

void Test_BitMask()
{
	auto mask = BitMask<uint32_t>(0xF0);
	if (mask.GetFrom(0x38) == 0x30) { std::cout << "mask(0xF0 | 0x38) -> 0x30" << std::endl; } else { throw std::exception(); }
	if (mask.GetAlignedFrom(0x38) == 0x3) { std::cout << "alignedmask(0xF0 | 0x38) -> 0x3" << std::endl; } else { throw std::exception(); }
	if (mask.GetFrom(0x250) == 0x50) { std::cout << "mask(0xF0 | 0x250) -> 0x50" << std::endl; } else { throw std::exception(); }
	if (mask.GetAlignedFrom(0x250) == 0x5) { std::cout << "alignedmask(0xF0 | 0x250) -> 0x5" << std::endl; } else { throw std::exception(); }
	if (BitMask<uint32_t>(0xFFFF).GetFrom(0xDEADBEEF) == 0xBEEF) { std::cout << "mask(0xFFFF | 0xDEADBEEF) -> 0xBEEF" << std::endl; } else { throw std::exception(); }
	if (BitMask<uint32_t>(0xFFFF0000).GetAlignedFrom(0xDEADBEEF) == 0xDEAD) { std::cout << "alignedmask(0xFFFF0000 | 0xDEADBEEF) -> 0xDEAD" << std::endl; } else { throw std::exception(); }
}
