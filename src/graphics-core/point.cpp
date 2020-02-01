#include <cmath>
#include "stationaryorbit/graphics-core/point.hpp"
using namespace zawa_ch::StationaryOrbit;

Graphics::Point::Point(const int32_t& x, const int32_t& y)
	: _x(x), _y(y)
{}

int32_t Graphics::Point::getX() const
{ return _x; }

int32_t Graphics::Point::getY() const
{ return _y; }

double Graphics::Point::getMagnitude() const
{ return sqrt(double(_x) * _x + double(_y) * _y); }

Graphics::Point Graphics::Point::Add(const Point& value) const
{ return Point(_x + value._x, _y + value._y); }

Graphics::Point Graphics::Point::Sub(const Point& value) const
{ return Point(_x - value._x, _y - value._y); }

Graphics::Point& Graphics::Point::AssignAdd(const Point& value)
{
	_x += value.getX();
	_y += value.getY();
	return *this;
}

Graphics::Point& Graphics::Point::AssignSub(const Point& value)
{
	_x -= value.getX();
	_y -= value.getY();
	return *this;
}

bool Graphics::Point::Equals(const Point& value) const
{ return (_x == value._x)&&(_y == value._y); }
