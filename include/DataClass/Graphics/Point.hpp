#include <cstdint>
#include "Interface/IVector2d.hpp"
#ifndef __StationaryOrbit_Graphics_Point__
#define __StationaryOrbit_Graphics_Point__
namespace StationaryOrbit
{
namespace Graphics
{

	struct Point
		: virtual public IVector2d<int32_t, DefaultDirection2d::R4>
	{
	private:

		int32_t _x;
		int32_t _y;

	public:

		Point();

		Point(const int32_t& x, const int32_t& y);

		~Point();

		///	X軸の大きさを取得します。
		T getX() const;

		///	Y軸の大きさを取得します。
		T getY() const;

		///	原点からの距離を取得します。
		double getMagnitude() const;

		///	X軸正方向を基準とする角度を取得します。
		Rotation getRotation() const;

	};	

}
}
#endif // __StationaryOrbit_Graphics_Point__