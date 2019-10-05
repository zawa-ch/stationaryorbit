#ifndef __StationaryOrbit_IVector2d__
#define __StationaryOrbit_IVector2d__
#include "EnumClass/DefaultDirection2d.hpp"
#include "DataClass/Rotation.hpp"
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
#endif // __StationaryOrbit_IVector2d__