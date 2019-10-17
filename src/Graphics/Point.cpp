#include <cmath>
#include "Graphics/Structure/Point.hpp"

StationaryOrbit::Graphics::Point::Point(const int32_t& x, const int32_t& y)
	: _x(x), _y(y)
{}

int32_t StationaryOrbit::Graphics::Point::getX() const
{ return _x; }

int32_t StationaryOrbit::Graphics::Point::getY() const
{ return _y; }

double StationaryOrbit::Graphics::Point::getMagnitude() const
{ return sqrt(double(_x) * _x + double(_y) * _y); }

StationaryOrbit::Graphics::Point StationaryOrbit::Graphics::Point::Add(const Point& value) const
{ return Point(_x + value._x, _y + value._y); }

StationaryOrbit::Graphics::Point StationaryOrbit::Graphics::Point::Sub(const Point& value) const
{ return Point(_x - value._x, _y - value._y); }

StationaryOrbit::Graphics::Point& StationaryOrbit::Graphics::Point::AssignAdd(const Point& value)
{
	_x += value.getX();
	_y += value.getY();
	return *this;
}

StationaryOrbit::Graphics::Point& StationaryOrbit::Graphics::Point::AssignSub(const Point& value)
{
	_x -= value.getX();
	_y -= value.getY();
	return *this;
}

bool StationaryOrbit::Graphics::Point::Equals(const Point& value) const
{ return (_x == value._x)&&(_y == value._y); }
