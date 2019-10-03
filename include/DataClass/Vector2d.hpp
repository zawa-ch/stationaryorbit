#include "EnumClass/DefaultDirection2d.hpp"
#include "Interface/IVector2d.hpp"
#ifndef __VECTOR2D_HPP__
#define __VECTOR2D_HPP__
namespace StationaryOrbit
{

	///	二次元平面上における点、あるいはベクトルを表します。
	struct Vector2d
		: virtual public IVector2d<double, DefaultDirection2d::L1>
		, virtual public ICompareble<IVector2d<double, DefaultDirection2d::L1>>
	{
	private:

		double _x;
		double _y;

	public:

		///	既定の値でこのオブジェクトを初期化します。
		Vector2d();

		///	軸座標の値を指定してこのオブジェクトを初期化します。
		Vector2d(double x, double y);

		///	極座標の値を指定してこのオブジェクトを初期化します。
		Vector2d(double magnitude, Rotation rotation);

		///	IVector2d<double, DefaultDirection2d::L1>オブジェクトをこの型に変換します。
		explicit Vector2d(const IVector2d<double, DefaultDirection2d::L1>& value);

		virtual ~Vector2d();

		///	X軸の大きさを取得します。
		double getX() const;

		///	Y軸の大きさを取得します。
		double getY() const;

		///	原点からの距離を取得します。
		double getMagnitude() const;

		///	X軸正方向を基準とする角度を取得します。
		Rotation getRotation() const;

		///	このオブジェクトを指定したオブジェクトと比較します。
		int Compare(const IVector2d<double, DefaultDirection2d::L1>& value) const;

		///	二つのオブジェクトの和を算出します。
		static Vector2d Add(const Vector2d& left, const IVector2d<double, DefaultDirection2d::L1>& right);

		///	二つのオブジェクトの差を算出します。
		static Vector2d Sub(const Vector2d& left, const IVector2d<double, DefaultDirection2d::L1>& right);

		///	二つのオブジェクトの積を算出します。
		static Vector2d Multiple(const Vector2d& left, const IVector2d<double, DefaultDirection2d::L1>& right);

		///	二つのオブジェクトの商を算出します。
		static Vector2d Divide(const Vector2d& left, const IVector2d<double, DefaultDirection2d::L1>& right);

		///	二つのオブジェクトの積を算出します。
		static Vector2d Multiple(const Vector2d& left, const double& right);

		///	二つのオブジェクトの商を算出します。
		static Vector2d Divide(const Vector2d& left, const double& right);

		Vector2d operator +(const IVector2d<double, DefaultDirection2d::L1>& value) const { return Add(*this, value); }

		Vector2d operator -(const IVector2d<double, DefaultDirection2d::L1>& value) const { return Sub(*this, value); }

		Vector2d operator *(const IVector2d<double, DefaultDirection2d::L1>& value) const { return Multiple(*this, value); }

		Vector2d operator /(const IVector2d<double, DefaultDirection2d::L1>& value) const { return Divide(*this, value); }

		Vector2d operator *(const double& value) const { return Multiple(*this, value); }

		Vector2d operator /(const double& value) const { return Divide(*this, value); }

		bool operator >(const IVector2d<double, DefaultDirection2d::L1>& value) const { return Compare(value)>0; }

		bool operator <(const IVector2d<double, DefaultDirection2d::L1>& value) const { return Compare(value)<0; }

		bool operator >=(const IVector2d<double, DefaultDirection2d::L1>& value) const { return Compare(value)>=0; }

		bool operator <=(const IVector2d<double, DefaultDirection2d::L1>& value) const { return Compare(value)<=0; }

		bool operator ==(const IVector2d<double, DefaultDirection2d::L1>& value) const { return Compare(value)==0; }

		bool operator !=(const IVector2d<double, DefaultDirection2d::L1>& value) const { return Compare(value)!=0; }

	};

}
#endif // __VECTOR2D_HPP__
