#include "Interface/ICompareble.hpp"
#include "Interface/IRotation.hpp"
#include "DataClass/RotationUnit.hpp"
#ifndef __ROTATION_HPP__
#define __ROTATION_HPP__
namespace StationaryOrbit
{

	///	角度の情報を保持し、度またはラジアンへの変換を行います。
	struct Rotation : virtual public IRotation, virtual public ICompareble<Rotation>
	{
	private:
		int _value;

	public:

		///	既定の値でこのオブジェクトを初期化します。
		Rotation();

		///	角度とその単位を指定してこのオブジェクトを初期化します。
		Rotation(double value, RotationUnit unit);
	
	protected:

		Rotation(int value);

	public:

		virtual ~Rotation();

		///	このオブジェクトの内容をDegree(度)で取得します。
		double getDegree() const;

		///	このオブジェクトの内容をRadian(ラジアン)で取得します。
		double getRadian() const;

		///	このオブジェクトを指定したオブジェクトと比較します。
		int Compare(const Rotation& value) const;

		///	二つのオブジェクトの和を算出します。
		static Rotation Add(const Rotation& left, const Rotation& right);

		///	二つのオブジェクトの差を算出します。
		static Rotation Sub(const Rotation& left, const Rotation& right);

		///	二つのオブジェクトの積を算出します。
		static Rotation Multiple(const Rotation& left, const double& right);

		///	二つのオブジェクトの商を算出します。
		static Rotation Divide(const Rotation& left, const double& right);

		Rotation operator +(const Rotation& value) const { return Add(*this, value); }

		Rotation operator -(const Rotation& value) const { return Sub(*this, value); }

		Rotation operator *(const double& value) const { return Multiple(*this, value); }

		Rotation operator /(const double& value) const { return Divide(*this, value); }

	};    

}
#endif // __ROTATION_HPP__