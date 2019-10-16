#ifndef __StationaryOrbit_Graphics_PointF__
#define __StationaryOrbit_Graphics_PointF__
#include <cstdint>
#include "DataClass/Rotation.hpp"
#include "DataClass/Graphics/Point.hpp"
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
		static PointF Add(const PointF& left, const PointF& right);

		///	二つのオブジェクトの差を算出します。
		static PointF Sub(const PointF& left, const PointF& right);

		///	二つのオブジェクトの積を算出します。
		static PointF Multiple(const PointF& left, const float& right);

		///	二つのオブジェクトの商を算出します。
		static PointF Divide(const PointF& left, const float& right);

		PointF& AssignAdd(const PointF& value);

		PointF& AssignSub(const PointF& value);

		PointF& AssignMultiple(const float& value);

		PointF& AssignDivide(const float& value);

		explicit operator Point() const;

		PointF operator +(const PointF& value) const { return Add(*this, value); }
		PointF operator -(const PointF& value) const { return Sub(*this, value); }
		PointF operator *(const float& value) const { return Multiple(*this, value); }
		PointF operator /(const float& value) const { return Divide(*this, value); }
		PointF& operator +=(const PointF& value) { return AssignAdd(value); }
		PointF& operator -=(const PointF& value) { return AssignSub(value); }
		PointF& operator *=(const float& value) { return AssignMultiple(value); }
		PointF& operator /=(const float& value) { return AssignDivide(value); }
	};

}
}
#endif // __StationaryOrbit_Graphics_PointF__