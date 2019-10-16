#include <cmath>
#include "Graphics/Structure/PointF.hpp"

StationaryOrbit::Graphics::PointF::PointF(const Point& value)
	: _x(float(value.getX())), _y(float(value.getY()))
{}

StationaryOrbit::Graphics::PointF::PointF(const float& x, const float& y)
	: _x(x), _y(y)
{}

float StationaryOrbit::Graphics::PointF::getX() const
{ return _x; }

float StationaryOrbit::Graphics::PointF::getY() const
{ return _y; }

double StationaryOrbit::Graphics::PointF::getMagnitude() const
{ return sqrt(double(_x) * _x + double(_y) * _y); }

StationaryOrbit::Graphics::PointF StationaryOrbit::Graphics::PointF::Add(const PointF& left, const PointF& right)
{ return PointF(left.getX() + right.getX(), left.getY() + right.getY()); }

StationaryOrbit::Graphics::PointF StationaryOrbit::Graphics::PointF::Sub(const PointF& left, const PointF& right)
{ return PointF(left.getX() - right.getX(), left.getY() - right.getY()); }

StationaryOrbit::Graphics::PointF StationaryOrbit::Graphics::PointF::Multiple(const PointF& left, const float& right)
{ return PointF(left.getX() * right, left.getY() * right); }

StationaryOrbit::Graphics::PointF StationaryOrbit::Graphics::PointF::Divide(const PointF& left, const float& right)
{ return PointF(left.getX() / right, left.getY() / right); }

StationaryOrbit::Graphics::PointF& StationaryOrbit::Graphics::PointF::AssignAdd(const PointF& value)
{
	_x += value.getX();
	_y += value.getY();
	return *this;
}

StationaryOrbit::Graphics::PointF& StationaryOrbit::Graphics::PointF::AssignSub(const PointF& value)
{
	_x -= value.getX();
	_y -= value.getY();
	return *this;
}

StationaryOrbit::Graphics::PointF& StationaryOrbit::Graphics::PointF::AssignMultiple(const float& value)
{
	_x *= value;
	_y *= value;
	return *this;
}

StationaryOrbit::Graphics::PointF& StationaryOrbit::Graphics::PointF::AssignDivide(const float& value)
{
	_x /= value;
	_y /= value;
	return *this;
}

StationaryOrbit::Graphics::PointF::operator Point() const
{ return Point(int32_t(_x), int32_t(_y)); }
