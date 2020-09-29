//	stationaryorbit/core/rotation
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
#ifndef __StationaryOrbit_Rotation__
#define __StationaryOrbit_Rotation__
namespace zawa_ch::StationaryOrbit
{

	///	角度の単位を示す列挙体。
	enum class RotationUnit
	{
        Radian,
        Degree,
	};

	///	角度の情報を保持し、度またはラジアンへの変換を行います。
	struct Rotation final
	{
	private:

		int _value;

	public:

		Rotation() = default;

		///	角度とその単位を指定してこのオブジェクトを初期化します。
		Rotation(double value, RotationUnit unit = RotationUnit::Radian);

		~Rotation() = default;

		///	このオブジェクトの内容をRadian(ラジアン)で取得します。
		double getRadian() const;

		///	このオブジェクトの内容をDegree(度)で取得します。
		double getDegree() const;

		double Sin() const;

		double Cos() const;

		double Tan() const;

		///	このオブジェクトの反対側の向きを示すオブジェクトを取得します。
		static Rotation Negative(const Rotation& value);
		Rotation operator -() const { return Negative(*this); }

		///	二つのオブジェクトの和を算出します。
		static Rotation Add(const Rotation& left, const Rotation& right);
		Rotation operator +(const Rotation& value) const { return Add(*this, value); }

		///	二つのオブジェクトの差を算出します。
		static Rotation Sub(const Rotation& left, const Rotation& right);
		Rotation operator -(const Rotation& value) const { return Sub(*this, value); }

		///	二つのオブジェクトの積を算出します。
		static Rotation Multiple(const Rotation& left, const double& right);
		Rotation operator *(const double& value) const { return Multiple(*this, value); }

		///	二つのオブジェクトの商を算出します。
		static Rotation Divide(const Rotation& left, const double& right);
		Rotation operator /(const double& value) const { return Divide(*this, value); }

		///	このオブジェクトを指定したオブジェクトと比較します。
		int CompareTo(const Rotation& value) const;
		bool operator >(const Rotation& value) const { return CompareTo(value)>0; }
		bool operator <(const Rotation& value) const { return CompareTo(value)<0; }
		bool operator >=(const Rotation& value) const { return CompareTo(value)>=0; }
		bool operator <=(const Rotation& value) const { return CompareTo(value)<=0; }

		///	指定されたオブジェクトがこのオブジェクトと等価であることを判定します。
		bool Equals(const Rotation& value) const;
		bool operator ==(const Rotation& value) const { return Equals(value); }
		bool operator !=(const Rotation& value) const { return !Equals(value); }

	};    

}
#endif // __StationaryOrbit_Rotation__