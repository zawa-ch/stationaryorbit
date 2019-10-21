#include <cmath>
#include "General/Structure/Vector2d.hpp"

StationaryOrbit::Vector2d StationaryOrbit::Vector2d::Zero() 
{ return Vector2d(0, 0); }

StationaryOrbit::Vector2d::Vector2d(double x, double y)
	: _x(x)
	, _y(y)
{}

StationaryOrbit::Vector2d::Vector2d(double magnitude, Rotation rotation)
	: _x(magnitude * cos(rotation.getRadian()))
	, _y(magnitude * sin(rotation.getRadian()))
{}

double StationaryOrbit::Vector2d::DotProduct(const Vector2d& value) const
{ return (_x * value._x) + (_y * value._y); }

StationaryOrbit::Vector2d StationaryOrbit::Vector2d::Add(const Vector2d& value) const
{ return Vector2d(_x + value._x, _y + value._y); }

StationaryOrbit::Vector2d StationaryOrbit::Vector2d::Sub(const Vector2d& value) const
{ return Vector2d(_x - value._x, _y - value._y); }

StationaryOrbit::Vector2d StationaryOrbit::Vector2d::Multiple(const double& value) const
{ return Vector2d(_x * value, _y * value); }

StationaryOrbit::Vector2d StationaryOrbit::Vector2d::Divide(const double& value) const
{ return Vector2d(_x / value, _y / value); }

StationaryOrbit::Vector2d& StationaryOrbit::Vector2d::AssignAdd(const Vector2d& value)
{
	_x += value._x;
	_y += value._y;
	return *this;
}

StationaryOrbit::Vector2d& StationaryOrbit::Vector2d::AssignSub(const Vector2d& value)
{
	_x -= value._x;
	_y -= value._y;
	return *this;
}

StationaryOrbit::Vector2d& StationaryOrbit::Vector2d::AssignMultiple(const double& value)
{
	_x *= value;
	_y *= value;
	return *this;
}

StationaryOrbit::Vector2d& StationaryOrbit::Vector2d::AssignDivide(const double& value)
{
	_x /= value;
	_y /= value;
	return *this;
}

int StationaryOrbit::Vector2d::CompareTo(const Vector2d& value) const
{
	if (getMagnitude() > value.getMagnitude()) return 1;
	else if (getMagnitude() < value.getMagnitude()) return -1;
	else return 0;
}

bool StationaryOrbit::Vector2d::Equals(const Vector2d& value) const
{ return (_x == value._x)&&(_y == value._y); }
