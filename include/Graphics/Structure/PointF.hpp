#ifndef __StationaryOrbit_Graphics_PointF__
#define __StationaryOrbit_Graphics_PointF__
#include <cstdint>
#include "../Structure/Point.hpp"
namespace StationaryOrbit
{
namespace Graphics
{

	///	ディスプレイ上の点を浮動小数点数で表します。
	struct PointF final
	{
	private:

		float _x;
		float _y;

	public:

		///	空のPointFを初期化します。
		PointF() = default;

		///	Pointから変換します。
		PointF(const Point& value);

		///	x座標およびy座標を指定してPointFを初期化します。
		PointF(const float& x, const float& y);

		~PointF() = default;

		///	X軸の大きさを取得します。
		float getX() const;

		///	Y軸の大きさを取得します。
		float getY() const;

		///	原点からの距離を取得します。
		double getMagnitude() const;

		///	二つのオブジェクトの和を算出します。
		PointF Add(const PointF& value) const;
		PointF operator+(const PointF& value) const { return Add(value); }

		///	二つのオブジェクトの差を算出します。
		PointF Sub(const PointF& value) const;
		PointF operator-(const PointF& value) const { return Sub(value); }

		///	二つのオブジェクトの積を算出します。
		PointF Multiple(const float& value) const;
		PointF operator*(const float& value) const { return Multiple(value); }

		///	二つのオブジェクトの商を算出します。
		PointF Divide(const float& value) const;
		PointF operator/(const float& value) const { return Divide(value); }

		PointF& AssignAdd(const PointF& value);
		PointF& operator+=(const PointF& value) { return AssignAdd(value); }

		PointF& AssignSub(const PointF& value);
		PointF& operator-=(const PointF& value) { return AssignSub(value); }

		PointF& AssignMultiple(const float& value);
		PointF& operator*=(const float& value) { return AssignMultiple(value); }

		PointF& AssignDivide(const float& value);
		PointF& operator/=(const float& value) { return AssignDivide(value); }

		///	指定されたオブジェクトがこのオブジェクトと等価であることを判定します。
		bool Equals(const PointF& value) const;
		bool operator==(const PointF& value) { return Equals(value); }
		bool operator!=(const PointF& value) { return !Equals(value); }

		explicit operator Point() const;

	};

}
}
#endif // __StationaryOrbit_Graphics_PointF__