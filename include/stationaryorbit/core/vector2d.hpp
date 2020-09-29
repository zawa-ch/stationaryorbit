//	stationaryorbit/core/vector2d
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
#ifndef __StationaryOrbit_Vector2d__
#define __StationaryOrbit_Vector2d__
#include <cmath>
#include "rotation.hpp"
namespace zawa_ch::StationaryOrbit
{

	///	二次元平面上における線形代数学的なベクトルを表します。
	struct Vector2d final
	{
	private:

		double _x;
		double _y;

	public:

		static Vector2d Zero();

		///	既定の値でこのオブジェクトを初期化します。
		Vector2d() = default;

		///	軸座標の値を指定してこのオブジェクトを初期化します。
		Vector2d(double x, double y);

		///	極座標の値を指定してこのオブジェクトを初期化します。
		Vector2d(double magnitude, Rotation rotation);

		~Vector2d() = default;

		///	X軸の大きさを取得します。
		double getX() const { return _x; }

		///	Y軸の大きさを取得します。
		double getY() const { return _y; }

		///	原点からの距離を取得します。
		double getMagnitude() const { return sqrt(_x * _x + _y * _y); }

		///	X軸正方向を基準とする角度を取得します。
		Rotation getRotation() const { return Rotation(atan2(_y, _x), RotationUnit::Radian); }

		///	二つのベクトルの和を算出します。
		Vector2d Add(const Vector2d& value) const;
		Vector2d operator +(const Vector2d& value) const { return Add(value); }

		///	二つのベクトルの差を算出します。
		Vector2d Sub(const Vector2d& value) const;
		Vector2d operator -(const Vector2d& value) const { return Sub(value); }

		///	ベクトルとスカラーの積を算出します。
		Vector2d Multiple(const double& value) const;
		Vector2d operator *(const double& value) const { return Multiple(value); }

		///	ベクトルとスカラーの商を算出します。
		Vector2d Divide(const double& value) const;
		Vector2d operator /(const double& value) const { return Divide(value); }

		///	二つのベクトルの和を算出します。
		Vector2d& AssignAdd(const Vector2d& value);
		Vector2d& operator +=(const Vector2d& value) { return AssignAdd(value); }

		///	二つのベクトルの差を算出します。
		Vector2d& AssignSub(const Vector2d& value);
		Vector2d& operator -=(const Vector2d& value) { return AssignSub(value); }

		///	ベクトルとスカラーの積を算出します。
		Vector2d& AssignMultiple(const double& value);
		Vector2d& operator *=(const double& value) { return AssignMultiple(value); }

		///	ベクトルとスカラーの商を算出します。
		Vector2d& AssignDivide(const double& value);
		Vector2d& operator /=(const double& value) { return AssignDivide(value); }

		///	二つのベクトルの内積を算出します。
		double DotProduct(const Vector2d& value) const;

		///	このオブジェクトを指定したオブジェクトと比較します。
		int CompareTo(const Vector2d& value) const;
		bool operator >(const Vector2d& value) const { return CompareTo(value)>0; }
		bool operator <(const Vector2d& value) const { return CompareTo(value)<0; }
		bool operator >=(const Vector2d& value) const { return CompareTo(value)>=0; }
		bool operator <=(const Vector2d& value) const { return CompareTo(value)<=0; }

		///	指定されたオブジェクトがこのオブジェクトと等価であることを判定します。
		bool Equals(const Vector2d& value) const;
		bool operator ==(const Vector2d& value) const { return Equals(value)==0; }
		bool operator !=(const Vector2d& value) const { return Equals(value)!=0; }

	};

}
#endif // __StationaryOrbit_Vector2d__
