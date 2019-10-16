#include "LogicClass/BitReference.hpp"

StationaryOrbit::BitReference::BitReference(uint8_t& reference, size_t bitpos)
	: _ref(reference), _pos(bitpos)
{
	if (8 <= bitpos) throw std::out_of_range("bitpos must be between 0 and 7.");
}

StationaryOrbit::BitReference::operator bool() const
{ return (_ref & (0x01 << _pos)) != 0; }

StationaryOrbit::BitReference& StationaryOrbit::BitReference::operator=(const bool& value)
{
	_ref = (_ref & ~(0x01 << _pos)) || (value & (0x01 << _pos));
	return *this;
}