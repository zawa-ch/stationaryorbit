#include "DataClass/Byte.hpp"

StationaryOrbit::Byte::Byte()
	: _data()
{}

StationaryOrbit::Byte::Byte(uint8_t value)
	: _data(value)
{}

StationaryOrbit::Byte::~Byte() {}

StationaryOrbit::BitReference StationaryOrbit::Byte::IndexOf(size_t index) { return BitReference(_data, index); }

StationaryOrbit::Byte StationaryOrbit::Byte::Or(const Byte& left, const Byte& right) { return Byte(left._data | right._data); }

StationaryOrbit::Byte StationaryOrbit::Byte::And(const Byte& left, const Byte& right) { return Byte(left._data & right._data); }

StationaryOrbit::Byte StationaryOrbit::Byte::Not(const Byte& value) { return Byte(~value._data); }

StationaryOrbit::Byte StationaryOrbit::Byte::Xor(const Byte& left, const Byte& right) { return Byte(left._data ^ right._data); }

StationaryOrbit::Byte& StationaryOrbit::Byte::AssignOr(const Byte& value)
{
	_data |= value._data;
	return *this;
}

StationaryOrbit::Byte& StationaryOrbit::Byte::AssignAnd(const Byte& value)
{
	_data &= value._data;
	return *this;
}

StationaryOrbit::Byte& StationaryOrbit::Byte::AssignXor(const Byte& value)
{
	_data ^= value._data;
	return *this;
}

StationaryOrbit::Byte::operator uint8_t() const { return _data; }
