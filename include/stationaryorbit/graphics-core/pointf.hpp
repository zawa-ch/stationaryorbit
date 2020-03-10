#ifndef __stationaryorbit_graphics_core_pointf__
#define __stationaryorbit_graphics_core_pointf__
#include <cstdint>
#include "point.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{

	///	ディスプレイ上の点を浮動小数点数で表します。
	struct PointF final
	{
	private:

		float _x;
		float _y;

	public:

		///	空の @a PointF を初期化します。
		PointF() = default;

		///	@a Point から変換します。
		PointF(const Point& value);

		///	x座標およびy座標を指定して @a PointF を初期化します。
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
		PointF Multiple(const PointF& value) const;
		PointF operator*(const PointF& value) const { return Multiple(value); }

		///	二つのオブジェクトの積を算出します。
		PointF Multiple(const float& value) const;
		PointF operator*(const float& value) const { return Multiple(value); }

		///	二つのオブジェクトの商を算出します。
		PointF Divide(const PointF& value) const;
		PointF operator/(const PointF& value) const { return Divide(value); }

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

		///	@a PointF を切り捨て方向に丸めます。
		PointF Floor() const;

		///	@a PointF を切り上げ方向に丸めます。
		PointF Ceil() const;

		/// @a PointF を最も近い整数の値に変換します。
		PointF Round() const;

		///	@a PointF の小数部を抜き出します。
		PointF Extract() const;

		///	このオブジェクトにおける零点を表します。
		static PointF Zero() { return PointF(0, 0); }

	};

}
#endif // __stationaryorbit_graphics_core_pointf__