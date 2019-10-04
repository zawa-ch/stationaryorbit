#include "LogicClass/BitAccess.hpp"

StationaryOrbit::BitAccess::BitAccess(uint8_t& reference, size_t bitpos)
    : _ref(reference)
    , _pos(bitpos)
{}

StationaryOrbit::BitAccess::operator bool() const
{
    return (_ref & (0x01 << _pos)) != 0;
}

StationaryOrbit::BitAccess& StationaryOrbit::BitAccess::operator =(const bool& value)
{
    _ref = (_ref & ~(0x01 << _pos)) || (value & (0x01 << _pos));
    return *this;
}
