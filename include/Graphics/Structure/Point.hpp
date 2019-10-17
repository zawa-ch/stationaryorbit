#ifndef __StationaryOrbit_Graphics_Point__
#define __StationaryOrbit_Graphics_Point__
#include <cstdint>
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
		Point Add(const Point& value) const;
		Point operator+(const Point& value) const { return Add(value); }

		///	二つのオブジェクトの差を算出します。
		Point Sub(const Point& value) const;
		Point operator-(const Point& value) const { return Sub(value); }

		Point& AssignAdd(const Point& value);
		Point& operator+=(const Point& value) { return AssignAdd(value); }

		Point& AssignSub(const Point& value);
		Point& operator-=(const Point& value) { return AssignSub(value); }

		///	指定されたオブジェクトがこのオブジェクトと等価であることを判定します。
		bool Equals(const Point& value) const;
		bool operator==(const Point& value) const { return Equals(value); }
		bool operator!=(const Point& value) const { return !Equals(value); }

	};	

}
}
#endif // __StationaryOrbit_Graphics_Point__