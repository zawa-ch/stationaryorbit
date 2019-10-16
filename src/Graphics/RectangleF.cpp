#include "Graphics/Structure/RectangleF.hpp"

StationaryOrbit::Graphics::RectangleF::RectangleF()
	: _p1(), _p2()
{}

StationaryOrbit::Graphics::RectangleF::RectangleF(const PointF& p1, const PointF& p2)
	: _p1(p1), _p2(p2)
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

double StationaryOrbit::Graphics::RectangleF::Distance() const
{ return (_p2 - _p1).getMagnitude(); }
