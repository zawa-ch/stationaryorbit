#include <cmath>
#include "General/Vector2d"

StationaryOrbit::Vector2d::Vector2d() {}

StationaryOrbit::Vector2d::Vector2d(double x, double y)
	: _x(x)
	, _y(y)
{}

StationaryOrbit::Vector2d::Vector2d(double magnitude, Rotation rotation)
	: _x(magnitude * cos(rotation.getRadian()))
	, _y(magnitude * sin(rotation.getRadian()))
{}

StationaryOrbit::Vector2d::Vector2d(const IVector2d<double, DefaultDirection2d::L1>& value)
	: _x(value.getX())
	, _y(value.getY())
{}

StationaryOrbit::Vector2d::~Vector2d() {}

double StationaryOrbit::Vector2d::getX() const { return _x; }

double StationaryOrbit::Vector2d::getY() const { return _y; }

double StationaryOrbit::Vector2d::getMagnitude() const { return sqrt(_x * _x + _y * _y); }

StationaryOrbit::Rotation StationaryOrbit::Vector2d::getRotation() const
{ return Rotation(atan2(_y, _x), RotationUnit::Radian); }

int StationaryOrbit::Vector2d::Compare(const IVector2d<double, DefaultDirection2d::L1>& value) const
{
	if (getMagnitude() > value.getMagnitude()) return 1;
	else if (getMagnitude() < value.getMagnitude()) return -1;
	else return 0;
}

StationaryOrbit::Vector2d StationaryOrbit::Vector2d::Add(const Vector2d& left, const IVector2d<double, DefaultDirection2d::L1>& right)
{
	return Vector2d(left.getX() + right.getX(), left.getY() + right.getY());
}

StationaryOrbit::Vector2d StationaryOrbit::Vector2d::Sub(const Vector2d& left, const IVector2d<double, DefaultDirection2d::L1>& right)
{
	return Vector2d(left.getX() - right.getX(), left.getY() - right.getY());
}

StationaryOrbit::Vector2d StationaryOrbit::Vector2d::Multiple(const Vector2d& left, const IVector2d<double, DefaultDirection2d::L1>& right)
{
	return Vector2d(left.getMagnitude() * right.getMagnitude(), left.getRotation() + right.getRotation());
}

StationaryOrbit::Vector2d StationaryOrbit::Vector2d::Divide(const Vector2d& left, const IVector2d<double, DefaultDirection2d::L1>& right)
{
	return Vector2d(left.getMagnitude() / right.getMagnitude(), left.getRotation() - right.getRotation());
}

StationaryOrbit::Vector2d StationaryOrbit::Vector2d::Multiple(const Vector2d& left, const double& right)
{
	return Vector2d(left.getMagnitude() * right, left.getRotation());
}

StationaryOrbit::Vector2d StationaryOrbit::Vector2d::Divide(const Vector2d& left, const double& right)
{
	return Vector2d(left.getMagnitude() / right, left.getRotation());
}
