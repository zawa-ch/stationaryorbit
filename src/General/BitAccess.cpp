#include <stdexcept>
#include "LogicClass/BitAccess.hpp"

StationaryOrbit::BitAccess::BitAccess(uint8_t& reference, size_t bitpos)
    : _ref(reference)
    , _pos(bitpos)
{
    if (8 <= bitpos) throw new std::out_of_range("bitpos must be between 0 and 7.");
}

StationaryOrbit::BitAccess::operator bool() const
{
    return (_ref & (0x01 << _pos)) != 0;
}

StationaryOrbit::BitAccess& StationaryOrbit::BitAccess::operator =(const bool& value)
{
    _ref = (_ref & ~(0x01 << _pos)) || (value & (0x01 << _pos));
    return *this;
}
