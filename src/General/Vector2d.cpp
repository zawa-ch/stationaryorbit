#include <cmath>
#include "General/Rotation"
#include "EnumClass/DefaultDirection2d.hpp"
#include "DataClass/Vector2d.hpp"

StationaryOrbit::Vector2d StationaryOrbit::Vector2d::Zero() 
{ return Vector2d(0, 0); }

StationaryOrbit::Vector2d::Vector2d()
	: _x()
	, _y()
{}

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

double StationaryOrbit::Vector2d::DotProduct(const Vector2d& left, const IVector2d<double, DefaultDirection2d::L1>& right)
{ return (left.getX() * right.getX()) + (left.getY() * right.getY()); }

StationaryOrbit::Vector2d StationaryOrbit::Vector2d::Add(const Vector2d& left, const IVector2d<double, DefaultDirection2d::L1>& right)
{ return Vector2d(left.getX() + right.getX(), left.getY() + right.getY()); }

StationaryOrbit::Vector2d StationaryOrbit::Vector2d::Sub(const Vector2d& left, const IVector2d<double, DefaultDirection2d::L1>& right)
{ return Vector2d(left.getX() - right.getX(), left.getY() - right.getY()); }

StationaryOrbit::Vector2d StationaryOrbit::Vector2d::Multiple(const Vector2d& left, const double& right)
{ return Vector2d(left.getX() * right, left.getY() * right); }

StationaryOrbit::Vector2d StationaryOrbit::Vector2d::Divide(const Vector2d& left, const double& right)
{ return Vector2d(left.getX() / right, left.getY() / right); }

StationaryOrbit::Vector2d& StationaryOrbit::Vector2d::AssignAdd(const IVector2d<double, DefaultDirection2d::L1>& value)
{
	_x += value.getX();
	_y += value.getY();
	return *this;
}

StationaryOrbit::Vector2d& StationaryOrbit::Vector2d::AssignSub(const IVector2d<double, DefaultDirection2d::L1>& value)
{
	_x -= value.getX();
	_y -= value.getY();
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
