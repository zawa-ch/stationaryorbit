#include <iostream>
#include "stationaryorbit/core.bitoperation.hpp"
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

void Test_Endian()
{
	uint32_t deadbeef = 0xDEADBEEF;
	auto fmtflg = std::cout.setf((std::ios_base::fmtflags)0, (std::ios_base::fmtflags)0);
	std::cout.setf(std::ios_base::hex, std::ios_base::basefield);
	std::cout << "little endian: 0x" << LittleEndian::Convert(deadbeef) << std::endl;
	std::cout << "big endian: 0x" << BigEndian::Convert(deadbeef) << std::endl;
	uint32be_t bevalue = deadbeef;
	std::cout << "0x" << bevalue << std::endl;
	std::cout.setf(fmtflg, std::ios_base::basefield);
}
