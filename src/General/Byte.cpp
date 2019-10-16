#include "DataClass/Byte.hpp"

StationaryOrbit::Byte::Byte(uint8_t value)
	: _data(value)
{}

StationaryOrbit::BitReference StationaryOrbit::Byte::IndexOf(size_t index)
{ return BitReference(_data, index); }

StationaryOrbit::Byte StationaryOrbit::Byte::Or(const Byte& left, const Byte& right)
{ return Byte(left._data | right._data); }

StationaryOrbit::Byte StationaryOrbit::Byte::And(const Byte& left, const Byte& right)
{ return Byte(left._data & right._data); }

StationaryOrbit::Byte StationaryOrbit::Byte::Not(const Byte& value)
{ return Byte(~value._data); }

StationaryOrbit::Byte StationaryOrbit::Byte::Xor(const Byte& left, const Byte& right)
{ return Byte(left._data ^ right._data); }

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

StationaryOrbit::Byte StationaryOrbit::Byte::Shift(int bits)
{
	if (0 <= bits)
	{
		return Byte(_data << bits);
	}
	else
	{
		return Byte(_data >> -bits);
	}
}

StationaryOrbit::Byte StationaryOrbit::Byte::Rotate(int bits)
{
	bits %= 8;
	if (0 <= bits)
	{
		return Byte((_data << bits) | (_data >> (8-bits)));
	}
	else
	{
		return Byte((_data << (8+bits)) | (_data >> -bits));
	}
}

bool StationaryOrbit::Byte::Equal(const Byte& left, const Byte& right)
{ return left._data == right._data; }
