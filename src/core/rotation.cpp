#include <limits>
#include <cmath>
#include "stationaryorbit/core/rotation.hpp"
using namespace zawa_ch::StationaryOrbit;

Rotation::Rotation(double value, RotationUnit unit)
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

double Rotation::getRadian() const
{ return M_PI * -double(_value) / std::numeric_limits<int>::min(); }

double Rotation::getDegree() const
{ return 180.0 * -double(_value) / std::numeric_limits<int>::min(); }

double Rotation::Sin() const
{
	return std::sin(getRadian());
}

double Rotation::Cos() const
{
	return std::cos(getRadian());
}

double Rotation::Tan() const
{
	return std::tan(getRadian());
}

Rotation Rotation::Negative(const Rotation& value)
{
	Rotation result = value;
	result._value += std::numeric_limits<int>::min();
	return result;
}

int Rotation::CompareTo(const Rotation& value) const
{
	if (getRadian() > value.getRadian()) return 1;
	else if (getRadian() < value.getRadian()) return -1;
	else return 0;
}

bool Rotation::Equals(const Rotation& value) const
{ return _value == value._value; }

Rotation Rotation::Add(const Rotation& left, const Rotation& right)
{ return Rotation(left.getRadian() + right.getRadian()); }

Rotation Rotation::Sub(const Rotation& left, const Rotation& right)
{ return Rotation(left.getRadian() - right.getRadian()); }

Rotation Rotation::Multiple(const Rotation& left, const double& right)
{ return Rotation(left.getRadian() * right); }

Rotation Rotation::Divide(const Rotation& left, const double& right)
{ return Rotation(left.getRadian() / right); }
