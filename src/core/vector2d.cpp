//	stationaryorbit.core:/vaector2d
//	Copyright 2020 zawa-ch.
//	GPLv3 (or later) license
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//	See the GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program.
//	If not, see <http://www.gnu.org/licenses/>.
//
#include <cmath>
#include "stationaryorbit/core/vector2d.hpp"
using namespace zawa_ch::StationaryOrbit;

Vector2d Vector2d::Zero() 
{ return Vector2d(0, 0); }

Vector2d::Vector2d(double x, double y)
	: _x(x)
	, _y(y)
{}

Vector2d::Vector2d(double magnitude, Rotation rotation)
	: _x(magnitude * cos(rotation.getRadian()))
	, _y(magnitude * sin(rotation.getRadian()))
{}

double Vector2d::DotProduct(const Vector2d& value) const
{ return (_x * value._x) + (_y * value._y); }

Vector2d Vector2d::Add(const Vector2d& value) const
{ return Vector2d(_x + value._x, _y + value._y); }

Vector2d Vector2d::Sub(const Vector2d& value) const
{ return Vector2d(_x - value._x, _y - value._y); }

Vector2d Vector2d::Multiple(const double& value) const
{ return Vector2d(_x * value, _y * value); }

Vector2d Vector2d::Divide(const double& value) const
{ return Vector2d(_x / value, _y / value); }

Vector2d& Vector2d::AssignAdd(const Vector2d& value)
{
	_x += value._x;
	_y += value._y;
	return *this;
}

Vector2d& Vector2d::AssignSub(const Vector2d& value)
{
	_x -= value._x;
	_y -= value._y;
	return *this;
}

Vector2d& Vector2d::AssignMultiple(const double& value)
{
	_x *= value;
	_y *= value;
	return *this;
}

Vector2d& Vector2d::AssignDivide(const double& value)
{
	_x /= value;
	_y /= value;
	return *this;
}

int Vector2d::CompareTo(const Vector2d& value) const
{
	if (getMagnitude() > value.getMagnitude()) return 1;
	else if (getMagnitude() < value.getMagnitude()) return -1;
	else return 0;
}

bool Vector2d::Equals(const Vector2d& value) const
{ return (_x == value._x)&&(_y == value._y); }
