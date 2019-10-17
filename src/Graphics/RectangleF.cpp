#include "Graphics/Structure/RectangleF.hpp"

StationaryOrbit::Graphics::RectangleF::RectangleF(const PointF& p1, const PointF& p2)
	: _p1(p1), _p2(p2)
{}

StationaryOrbit::Graphics::RectangleF::RectangleF(const Rectangle& value)
	: _p1(value.getP1()), _p2(value.getP2())
{}

StationaryOrbit::Graphics::PointF StationaryOrbit::Graphics::RectangleF::getP1() const
{ return _p1; }

StationaryOrbit::Graphics::PointF StationaryOrbit::Graphics::RectangleF::getP2() const
{ return _p2; }

float StationaryOrbit::Graphics::RectangleF::getTop() const
{ return _p1.getY()<_p2.getY() ? _p1.getY() : _p2.getY(); }

float StationaryOrbit::Graphics::RectangleF::getBottom() const
{ return _p1.getY()>_p2.getY() ? _p1.getY() : _p2.getY(); }

float StationaryOrbit::Graphics::RectangleF::getLeft() const
{ return _p1.getX()<_p2.getX() ? _p1.getX() : _p2.getX(); }

float StationaryOrbit::Graphics::RectangleF::getRight() const
{ return _p1.getX()>_p2.getX() ? _p1.getX() : _p2.getX(); }

float StationaryOrbit::Graphics::RectangleF::getHeight() const
{ return getBottom() - getTop(); }

float StationaryOrbit::Graphics::RectangleF::getWidth() const
{ return getRight() - getTop(); }

StationaryOrbit::Graphics::PointF StationaryOrbit::Graphics::RectangleF::getTopLeft() const
{ return PointF(getLeft(), getTop()); }

StationaryOrbit::Graphics::PointF StationaryOrbit::Graphics::RectangleF::getBottomLeft() const
{ return PointF(getLeft(), getBottom()); }

StationaryOrbit::Graphics::PointF StationaryOrbit::Graphics::RectangleF::getTopRight() const
{ return PointF(getRight(), getTop()); }

StationaryOrbit::Graphics::PointF StationaryOrbit::Graphics::RectangleF::getBottomRight() const
{ return PointF(getRight(), getBottom()); }

double StationaryOrbit::Graphics::RectangleF::Distance() const
{ return (_p2 - _p1).getMagnitude(); }

StationaryOrbit::Graphics::RectangleF StationaryOrbit::Graphics::RectangleF::Shift(const PointF& value) const
{ return RectangleF(_p1 + value, _p2 + value); }

bool StationaryOrbit::Graphics::RectangleF::Equals(const RectangleF& value) const
{ return (getTop() == value.getTop())&&(getBottom() == value.getBottom())&&(getLeft() == value.getLeft())&&(getRight() == value.getRight()); }

StationaryOrbit::Graphics::RectangleF::operator StationaryOrbit::Graphics::Rectangle() const
{ return Rectangle(Point(_p1), Point(_p2)); }
