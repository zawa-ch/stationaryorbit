#include <limits>
#include <cmath>
#include "General/Rotation"

StationaryOrbit::Rotation::Rotation() {}

StationaryOrbit::Rotation::Rotation(double value, RotationUnit unit)
{
	switch (unit)
	{
	case RotationUnit::Radian:
		value /= M_PI;
		break;

	case RotationUnit::Degree:
		value /= 180.0;
		break;

	default:
		break;
	}
	value += 1.0;
	value = std::fmod(value, 2.0);
	value -= 1.0;
	_value = (int)(-value * std::numeric_limits<int>::min());
}

StationaryOrbit::Rotation::~Rotation() {}

double StationaryOrbit::Rotation::getRadian() const { return M_PI * -double(_value) / std::numeric_limits<int>::min(); }

double StationaryOrbit::Rotation::getDegree() const { return 180.0 * -double(_value) / std::numeric_limits<int>::min(); }

int StationaryOrbit::Rotation::Compare(const IRotation& value) const
{
	if (getRadian() > value.getRadian()) return 1;
	else if (getRadian() < value.getRadian()) return -1;
	else return 0;
}

StationaryOrbit::Rotation StationaryOrbit::Rotation::Add(const Rotation& left, const IRotation& right)
{
	return Rotation(left.getRadian() + right.getRadian());
}

StationaryOrbit::Rotation StationaryOrbit::Rotation::Sub(const Rotation& left, const IRotation& right)
{
	return Rotation(left.getRadian() - right.getRadian());
}

StationaryOrbit::Rotation StationaryOrbit::Rotation::Multiple(const Rotation& left, const double& right)
{
	return Rotation(left.getRadian() * right);
}

StationaryOrbit::Rotation StationaryOrbit::Rotation::Divide(const Rotation& left, const double& right)
{
	return Rotation(left.getRadian() / right);
}

