#include "Graphics/Structure/Rectangle.hpp"

StationaryOrbit::Graphics::Rectangle::Rectangle(const Point& p1, const Point& p2)
	: _p1(p1), _p2(p2)
{}

StationaryOrbit::Graphics::Point StationaryOrbit::Graphics::Rectangle::getP1() const
{ return _p1; }

StationaryOrbit::Graphics::Point StationaryOrbit::Graphics::Rectangle::getP2() const
{ return _p2; }

int32_t StationaryOrbit::Graphics::Rectangle::getTop() const
{ return _p1.getY()<_p2.getY() ? _p1.getY() : _p2.getY(); }

int32_t StationaryOrbit::Graphics::Rectangle::getBottom() const
{ return _p1.getY()>_p2.getY() ? _p1.getY() : _p2.getY(); }

int32_t StationaryOrbit::Graphics::Rectangle::getLeft() const
{ return _p1.getX()<_p2.getX() ? _p1.getX() : _p2.getX(); }

int32_t StationaryOrbit::Graphics::Rectangle::getRight() const
{ return _p1.getX()>_p2.getX() ? _p1.getX() : _p2.getX(); }

int32_t StationaryOrbit::Graphics::Rectangle::getHeight() const
{ return getBottom() - getTop(); }

int32_t StationaryOrbit::Graphics::Rectangle::getWidth() const
{ return getRight() - getTop(); }

StationaryOrbit::Graphics::Point StationaryOrbit::Graphics::Rectangle::getTopLeft() const
{ return Point(getLeft(), getTop()); }

StationaryOrbit::Graphics::Point StationaryOrbit::Graphics::Rectangle::getBottomLeft() const
{ return Point(getLeft(), getBottom()); }

StationaryOrbit::Graphics::Point StationaryOrbit::Graphics::Rectangle::getTopRight() const
{ return Point(getRight(), getTop()); }

StationaryOrbit::Graphics::Point StationaryOrbit::Graphics::Rectangle::getBottomRight() const
{ return Point(getRight(), getBottom()); }

StationaryOrbit::Graphics::Point StationaryOrbit::Graphics::Rectangle::getSize() const
{ return getBottomRight() - getTopLeft(); }

double StationaryOrbit::Graphics::Rectangle::Distance() const
{ return (_p2 - _p1).getMagnitude(); }

bool StationaryOrbit::Graphics::Rectangle::InRange(const Point& value) const
{ return (getLeft() <= value.getX())&&(value.getX() < getRight())&&(getTop() <= value.getY())&&(value.getY() < getBottom()); }

StationaryOrbit::Graphics::Rectangle StationaryOrbit::Graphics::Rectangle::Shift(const Point& value) const
{ return Rectangle(_p1 + value, _p2 + value); }

bool StationaryOrbit::Graphics::Rectangle::Equals(const Rectangle& value) const
{ return (getTop() == value.getTop())&&(getBottom() == value.getBottom())&&(getLeft() == value.getLeft())&&(getRight() == value.getRight()); }
