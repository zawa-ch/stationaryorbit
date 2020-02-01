#include "stationaryorbit/graphics-core/rectanglef.hpp"
using namespace zawa_ch::StationaryOrbit;

Graphics::RectangleF::RectangleF(const PointF& p1, const PointF& p2)
	: _p1(p1), _p2(p2)
{}

Graphics::RectangleF::RectangleF(const Rectangle& value)
	: _p1(value.getP1()), _p2(value.getP2())
{}

Graphics::PointF Graphics::RectangleF::getP1() const
{ return _p1; }

Graphics::PointF Graphics::RectangleF::getP2() const
{ return _p2; }

float Graphics::RectangleF::getTop() const
{ return _p1.getY()<_p2.getY() ? _p1.getY() : _p2.getY(); }

float Graphics::RectangleF::getBottom() const
{ return _p1.getY()>_p2.getY() ? _p1.getY() : _p2.getY(); }

float Graphics::RectangleF::getLeft() const
{ return _p1.getX()<_p2.getX() ? _p1.getX() : _p2.getX(); }

float Graphics::RectangleF::getRight() const
{ return _p1.getX()>_p2.getX() ? _p1.getX() : _p2.getX(); }

float Graphics::RectangleF::getHeight() const
{ return getBottom() - getTop(); }

float Graphics::RectangleF::getWidth() const
{ return getRight() - getTop(); }

Graphics::PointF Graphics::RectangleF::getTopLeft() const
{ return PointF(getLeft(), getTop()); }

Graphics::PointF Graphics::RectangleF::getBottomLeft() const
{ return PointF(getLeft(), getBottom()); }

Graphics::PointF Graphics::RectangleF::getTopRight() const
{ return PointF(getRight(), getTop()); }

Graphics::PointF Graphics::RectangleF::getBottomRight() const
{ return PointF(getRight(), getBottom()); }

Graphics::PointF Graphics::RectangleF::getSize() const
{ return getBottomRight() - getTopLeft(); }

double Graphics::RectangleF::Distance() const
{ return (_p2 - _p1).getMagnitude(); }

bool Graphics::RectangleF::InRange(const PointF& value) const
{ return (getLeft() <= value.getX())&&(value.getX() < getRight())&&(getTop() <= value.getY())&&(value.getY() < getBottom()); }

Graphics::RectangleF Graphics::RectangleF::Shift(const PointF& value) const
{ return RectangleF(_p1 + value, _p2 + value); }

bool Graphics::RectangleF::Equals(const RectangleF& value) const
{ return (getTop() == value.getTop())&&(getBottom() == value.getBottom())&&(getLeft() == value.getLeft())&&(getRight() == value.getRight()); }

Graphics::RectangleF::operator Graphics::Rectangle() const
{ return Rectangle(Point(_p1), Point(_p2)); }
