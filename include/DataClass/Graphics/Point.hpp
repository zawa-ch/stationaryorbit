#include <cstdint>
#include "EnumClass/DefaultDirection2d.hpp"
#include "Interface/IVector2d.hpp"
#include "DataClass/Rotation.hpp"
#ifndef __StationaryOrbit_Graphics_Point__
#define __StationaryOrbit_Graphics_Point__
namespace StationaryOrbit
{
namespace Graphics
{

	struct Point final
		: virtual public IVector2d<int32_t, DefaultDirection2d::R4>
	{
	private:

		int32_t _x;
		int32_t _y;

	public:

		Point();

		Point(const int32_t& x, const int32_t& y);

		~Point() = default;

		///	X軸の大きさを取得します。
		int32_t getX() const;

		///	Y軸の大きさを取得します。
		int32_t getY() const;

		///	原点からの距離を取得します。
		double getMagnitude() const;

		///	X軸正方向を基準とする角度を取得します。
		Rotation getRotation() const;

		///	二つのオブジェクトの和を算出します。
		static Point Add(const Point& left, const IVector2d<int32_t, DefaultDirection2d::R4>& right);

		///	二つのオブジェクトの差を算出します。
		static Point Sub(const Point& left, const IVector2d<int32_t, DefaultDirection2d::R4>& right);

		Point& AssignAdd(const IVector2d<int32_t, DefaultDirection2d::R4>& value);

		Point& AssignSub(const IVector2d<int32_t, DefaultDirection2d::R4>& value);

		Point operator +(const IVector2d<int32_t, DefaultDirection2d::R4>& value) const { return Add(*this, value); }
		Point operator -(const IVector2d<int32_t, DefaultDirection2d::R4>& value) const { return Sub(*this, value); }
		Point& operator +=(const IVector2d<int32_t, DefaultDirection2d::R4>& value) { return AssignAdd(value); }
		Point& operator -=(const IVector2d<int32_t, DefaultDirection2d::R4>& value) { return AssignSub(value); }

	};	

}
}
#endif // __StationaryOrbit_Graphics_Point__