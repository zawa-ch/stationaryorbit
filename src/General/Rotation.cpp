#include <limits>
#include <cmath>
#include "General/Rotation"

StationaryOrbit::Rotation::Rotation() {}

StationaryOrbit::Rotation::Rotation(double value, RotationUnit unit)
{
	switch (unit)
	{
	case RotationUnit::Degree:
		value /= 180.0;
		break;

	case RotationUnit::Radian:
		value /= M_PI;
		break;

	default:
		break;
	}
	value += 1.0;
	value = std::fmod(value, 2.0);
	value -= 1.0;
	_value = (int)(-value * std::numeric_limits<int>::min());
}

StationaryOrbit::Rotation::Rotation(int value)
	: _value(value)
{}

StationaryOrbit::Rotation::~Rotation() {}

double StationaryOrbit::Rotation::getDegree() const
{
	return 180.0 * double(_value);
}

double StationaryOrbit::Rotation::getRadian() const
{
	return M_PI * double(_value);
}

int StationaryOrbit::Rotation::Compare(const Rotation& value) const
{
	if (_value > value._value) return 1;
	else if (_value < value._value) return -1;
	else return 0;
}

StationaryOrbit::Rotation StationaryOrbit::Rotation::Add(const Rotation& left, const Rotation& right)
{
	return Rotation(left._value + right._value);
}

StationaryOrbit::Rotation StationaryOrbit::Rotation::Sub(const Rotation& left, const Rotation& right)
{
	return Rotation(left._value - right._value);
}

StationaryOrbit::Rotation StationaryOrbit::Rotation::Multiple(const Rotation& left, const double& right)
{
	return Rotation(left._value * right);
}

StationaryOrbit::Rotation StationaryOrbit::Rotation::Divide(const Rotation& left, const double& right)
{
	return Rotation(left._value / right);
}

