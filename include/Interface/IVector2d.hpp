#include "EnumClass/DefaultDirection2d.hpp"
#include "DataClass/Rotation.hpp"
#ifndef __IVECTOR2D_HPP__
#define __IVECTOR2D_HPP__
namespace StationaryOrbit
{

	///	二つのスカラー値を持つ値を実装します。
	template<typename T, DefaultDirection2d dir>
	class IVector2d
	{
	public:

		///	X軸の大きさを取得します。
		virtual T getX() const = 0;

		///	Y軸の大きさを取得します。
		virtual T getY() const = 0;

		///	原点からの距離を取得します。
		virtual double getMagnitude() const = 0;

		///	X軸正方向を基準とする角度を取得します。
		virtual Rotation getRotation() const = 0;

	};

}
#endif // __IVECTOR2D_HPP__