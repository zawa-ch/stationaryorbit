#include "DataClass/Graphics/Rectangle.hpp"

StationaryOrbit::Graphics::Rectangle::Rectangle()
	: _p1(), _p2()
{}

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

double StationaryOrbit::Graphics::Rectangle::Distance() const
{ return (_p2 - _p1).getMagnitude(); }
