#include <limits>
#include <cmath>
#include "EnumClass/RotationUnit.hpp"
#include "DataClass/Rotation.hpp"

StationaryOrbit::Rotation::Rotation() {}

StationaryOrbit::Rotation::Rotation(const IRotation& value)
	: Rotation(value.getRadian())
{}

StationaryOrbit::Rotation::Rotation(double value, RotationUnit unit)
{
	switch (unit)
	{
	case RotationUnit::Radian:
		// -PI...PIスケールを-1...1にする
		value /= M_PI;
		break;

	case RotationUnit::Degree:
		// -180...180スケールを-1...1にする
		value /= 180.0;
		break;

	default:
		break;
	}
	// 0...2としてから整数回転分をカット、-1...1に戻す
	value += 1.0;
	value = std::fmod(value, 2.0);
	value -= 1.0;
	// intの最小-最大となるようにする
	// 最大値は"1.0に限りなく近い数"であるため-1を基準にスケーリング
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

int StationaryOrbit::Rotation::Compare(const Rotation& value) const
{
	if (_value > value._value) return 1;
	else if (_value < value._value) return -1;
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

