#ifndef __StationaryOrbit_Graphics_Point__
#define __StationaryOrbit_Graphics_Point__
#include <cstdint>
#include "General/Rotation"
namespace StationaryOrbit
{
namespace Graphics
{

	///	ディスプレイ上の点を表します。
	struct Point final
	{
	private:

		int32_t _x;
		int32_t _y;

	public:

		///	空のPointを初期化します。
		Point() = default;

		///	x座標y座標を指定してPointを初期化します。
		Point(const int32_t& x, const int32_t& y);

		~Point() = default;

		///	X軸の大きさを取得します。
		int32_t getX() const;

		///	Y軸の大きさを取得します。
		int32_t getY() const;

		///	原点からの距離を取得します。
		double getMagnitude() const;

		///	二つのオブジェクトの和を算出します。
		static Point Add(const Point& left, const Point& right);

		///	二つのオブジェクトの差を算出します。
		static Point Sub(const Point& left, const Point& right);

		Point& AssignAdd(const Point& value);

		Point& AssignSub(const Point& value);

		Point operator +(const Point& value) const { return Add(*this, value); }
		Point operator -(const Point& value) const { return Sub(*this, value); }
		Point& operator +=(const Point& value) { return AssignAdd(value); }
		Point& operator -=(const Point& value) { return AssignSub(value); }

	};	

}
}
#endif // __StationaryOrbit_Graphics_Point__