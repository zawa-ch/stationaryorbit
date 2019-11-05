#include "General/Logic/BitReference.hpp"

StationaryOrbit::BitReference::BitReference(std::byte& reference, size_t bitpos)
	: _ref(reference), _pos(bitpos)
{
	if (8 <= bitpos) throw std::out_of_range("bitpos must be between 0 and 7.");
}

StationaryOrbit::BitReference::operator bool() const
{ return (_ref & std::byte(0x01 << _pos)) != std::byte(0); }

StationaryOrbit::BitReference& StationaryOrbit::BitReference::operator=(const bool& value)
{
	_ref = (_ref & std::byte(~(0x01 << _pos))) | std::byte(value & (0x01 << _pos));
	return *this;
}
