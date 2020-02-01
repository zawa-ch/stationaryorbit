#include <cmath>
#include "stationaryorbit/graphics-core/pointf.hpp"
using namespace zawa_ch::StationaryOrbit;

Graphics::PointF::PointF(const Point& value)
	: _x(float(value.getX())), _y(float(value.getY()))
{}

Graphics::PointF::PointF(const float& x, const float& y)
	: _x(x), _y(y)
{}

float Graphics::PointF::getX() const
{ return _x; }

float Graphics::PointF::getY() const
{ return _y; }

double Graphics::PointF::getMagnitude() const
{ return sqrt(double(_x) * _x + double(_y) * _y); }

Graphics::PointF Graphics::PointF::Add(const PointF& value) const
{ return PointF(_x + value._x, _y + value._y); }

Graphics::PointF Graphics::PointF::Sub(const PointF& value) const
{ return PointF(_x - value._x, _y - value._y); }

Graphics::PointF Graphics::PointF::Multiple(const PointF& value) const
{ return PointF(_x * value._x, _y * value._y); }

Graphics::PointF Graphics::PointF::Multiple(const float& value) const
{ return PointF(_x * value, _y * value); }

Graphics::PointF Graphics::PointF::Divide(const PointF& value) const
{ return PointF(_x / value._x, _y / value._y); }

Graphics::PointF Graphics::PointF::Divide(const float& value) const
{ return PointF(_x / value, _y / value); }

Graphics::PointF& Graphics::PointF::AssignAdd(const PointF& value)
{
	_x += value.getX();
	_y += value.getY();
	return *this;
}

Graphics::PointF& Graphics::PointF::AssignSub(const PointF& value)
{
	_x -= value.getX();
	_y -= value.getY();
	return *this;
}

Graphics::PointF& Graphics::PointF::AssignMultiple(const float& value)
{
	_x *= value;
	_y *= value;
	return *this;
}

Graphics::PointF& Graphics::PointF::AssignDivide(const float& value)
{
	_x /= value;
	_y /= value;
	return *this;
}

bool Graphics::PointF::Equals(const PointF& value) const
{ return (_x == value._x)&&(_y == value._y); }

Graphics::PointF::operator Point() const
{ return Point(int32_t(_x), int32_t(_y)); }

Graphics::PointF Graphics::PointF::Floor() const
{ return PointF(floorf(_x), floorf(_y)); }

Graphics::PointF Graphics::PointF::Ceil() const
{ return PointF(ceilf(_x), ceilf(_y)); }

Graphics::PointF Graphics::PointF::Round() const
{ return PointF(roundf(_x), roundf(_y)); }

Graphics::PointF Graphics::PointF::Extract() const
{ return PointF(_x - truncf(_x), _y - truncf(_y)); }
