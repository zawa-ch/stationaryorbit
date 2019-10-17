#include "General/Structure/Byte.hpp"

StationaryOrbit::Byte::Byte(uint8_t value)
	: _data(value)
{}

StationaryOrbit::BitReference StationaryOrbit::Byte::IndexOf(size_t index)
{ return BitReference(_data, index); }

StationaryOrbit::Byte StationaryOrbit::Byte::Or(const Byte& value) const
{ return Byte(_data | value._data); }

StationaryOrbit::Byte StationaryOrbit::Byte::And(const Byte& value) const
{ return Byte(_data & value._data); }

StationaryOrbit::Byte StationaryOrbit::Byte::Not() const
{ return Byte(~_data); }

StationaryOrbit::Byte StationaryOrbit::Byte::Xor(const Byte& value) const
{ return Byte(_data ^ value._data); }

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

StationaryOrbit::Byte StationaryOrbit::Byte::Shift(int bits) const
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

StationaryOrbit::Byte StationaryOrbit::Byte::Rotate(int bits) const
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

bool StationaryOrbit::Byte::Equals(const Byte& value) const
{ return _data == value._data; }
