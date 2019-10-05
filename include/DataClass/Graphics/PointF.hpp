#include <cstdint>
#include "EnumClass/DefaultDirection2d.hpp"
#include "Interface/IVector2d.hpp"
#include "DataClass/Rotation.hpp"
#include "DataClass/Graphics/Point.hpp"
#ifndef __StationaryOrbit_Graphics_PointF__
#define __StationaryOrbit_Graphics_PointF__
namespace StationaryOrbit
{
namespace Graphics
{

	///	ディスプレイ上の点を浮動小数点数で表します。
	struct PointF final
		: IVector2d<float, DefaultDirection2d::R4>
	{
	private:

		float _x;
		float _y;

	public:

		///	空のPointFを初期化します。
		PointF();

		///	IVector2d<float, DefaultDirection2d::R4>から変換します。
		explicit PointF(const IVector2d<float, DefaultDirection2d::R4>& value);

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

		///	X軸正方向を基準とする角度を取得します。
		Rotation getRotation() const;

		///	二つのオブジェクトの和を算出します。
		static PointF Add(const PointF& left, const IVector2d<float, DefaultDirection2d::R4>& right);

		///	二つのオブジェクトの差を算出します。
		static PointF Sub(const PointF& left, const IVector2d<float, DefaultDirection2d::R4>& right);

		///	二つのオブジェクトの積を算出します。
		static PointF Multiple(const PointF& left, const float& right);

		///	二つのオブジェクトの商を算出します。
		static PointF Divide(const PointF& left, const float& right);

		PointF& AssignAdd(const IVector2d<float, DefaultDirection2d::R4>& value);

		PointF& AssignSub(const IVector2d<float, DefaultDirection2d::R4>& value);

		PointF& AssignMultiple(const float& value);

		PointF& AssignDivide(const float& value);

		explicit operator Point() const;

		PointF operator +(const IVector2d<float, DefaultDirection2d::R4>& value) const { return Add(*this, value); }
		PointF operator -(const IVector2d<float, DefaultDirection2d::R4>& value) const { return Sub(*this, value); }
		PointF operator *(const float& value) const { return Multiple(*this, value); }
		PointF operator /(const float& value) const { return Divide(*this, value); }
		PointF& operator +=(const IVector2d<float, DefaultDirection2d::R4>& value) { return AssignAdd(value); }
		PointF& operator -=(const IVector2d<float, DefaultDirection2d::R4>& value) { return AssignSub(value); }
		PointF& operator *=(const float& value) { return AssignMultiple(value); }
		PointF& operator /=(const float& value) { return AssignDivide(value); }
	};

}
}
#endif // __StationaryOrbit_Graphics_PointF__