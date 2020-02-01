#include "stationaryorbit/graphics-core/rectangle.hpp"
using namespace zawa_ch::StationaryOrbit;

Graphics::Rectangle::Rectangle(const Point& p1, const Point& p2)
	: _p1(p1), _p2(p2)
{}

Graphics::Point Graphics::Rectangle::getP1() const
{ return _p1; }

Graphics::Point Graphics::Rectangle::getP2() const
{ return _p2; }

int32_t Graphics::Rectangle::getTop() const
{ return _p1.getY()<_p2.getY() ? _p1.getY() : _p2.getY(); }

int32_t Graphics::Rectangle::getBottom() const
{ return _p1.getY()>_p2.getY() ? _p1.getY() : _p2.getY(); }

int32_t Graphics::Rectangle::getLeft() const
{ return _p1.getX()<_p2.getX() ? _p1.getX() : _p2.getX(); }

int32_t Graphics::Rectangle::getRight() const
{ return _p1.getX()>_p2.getX() ? _p1.getX() : _p2.getX(); }

int32_t Graphics::Rectangle::getHeight() const
{ return getBottom() - getTop(); }

int32_t Graphics::Rectangle::getWidth() const
{ return getRight() - getTop(); }

Graphics::Point Graphics::Rectangle::getTopLeft() const
{ return Point(getLeft(), getTop()); }

Graphics::Point Graphics::Rectangle::getBottomLeft() const
{ return Point(getLeft(), getBottom()); }

Graphics::Point Graphics::Rectangle::getTopRight() const
{ return Point(getRight(), getTop()); }

Graphics::Point Graphics::Rectangle::getBottomRight() const
{ return Point(getRight(), getBottom()); }

Graphics::Point Graphics::Rectangle::getSize() const
{ return getBottomRight() - getTopLeft(); }

double Graphics::Rectangle::Distance() const
{ return (_p2 - _p1).getMagnitude(); }

bool Graphics::Rectangle::InRange(const Point& value) const
{ return (getLeft() <= value.getX())&&(value.getX() < getRight())&&(getTop() <= value.getY())&&(value.getY() < getBottom()); }

Graphics::Rectangle Graphics::Rectangle::Shift(const Point& value) const
{ return Rectangle(_p1 + value, _p2 + value); }

bool Graphics::Rectangle::Equals(const Rectangle& value) const
{ return (getTop() == value.getTop())&&(getBottom() == value.getBottom())&&(getLeft() == value.getLeft())&&(getRight() == value.getRight()); }
