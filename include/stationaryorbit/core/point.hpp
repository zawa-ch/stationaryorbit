#ifndef __stationaryorbit_core_point__
#define __stationaryorbit_core_point__
#include <cmath>
#include "rectanglesize.hpp"
namespace zawa_ch::StationaryOrbit
{
	enum class Quadrants { UpRight, UpLeft, DownLeft, DownRight };
	template<Quadrants from, Quadrants to> class QuadrantConvertHelper;
	template<Quadrants quad> struct Point;
	template<Quadrants quad> struct PointF;

	template<Quadrants from, Quadrants to>
	class QuadrantConvertHelper final
	{
	public:
		static constexpr bool InvertX()
		{
			if constexpr (
				(((from==Quadrants::UpRight)||(from==Quadrants::DownRight))&&((to==Quadrants::UpLeft)||(to==Quadrants::DownLeft)))
				||(((from==Quadrants::UpLeft)||(from==Quadrants::DownLeft))&&((to==Quadrants::UpRight)||(to==Quadrants::DownRight)))
			)
			{ return true; }
			else
			{ return false; }
		}
		static constexpr bool InvertY()
		{
			if constexpr (
				(((from==Quadrants::UpRight)||(from==Quadrants::UpLeft))&&((to==Quadrants::DownRight)||(to==Quadrants::DownLeft)))
				||(((from==Quadrants::DownRight)||(from==Quadrants::DownLeft))&&((to==Quadrants::UpRight)||(to==Quadrants::UpLeft)))
			)
			{ return true; }
			else
			{ return false; }
		}
	};
	///	二次元平面上におけるある一点を表します。
	template<Quadrants quad = Quadrants::UpRight>
	struct Point final
	{
	private: // contains
		int _x;
		int _y;
	public: // construct
		constexpr Point() : _x(), _y() {}
		constexpr Point(const int& x, const int& y) : _x(x), _y(y) {}
		template<Quadrants fromquad>
		constexpr Point(const Point<fromquad>& from) : _x((QuadrantConvertHelper<fromquad, quad>::InvertX())?(-from.X()):(from.X())), _y((QuadrantConvertHelper<fromquad, quad>::InvertY())?(-from.Y()):(from.Y())) {}
		constexpr explicit Point(const RectangleSize& from) : _x(from.Width()), _y(from.Height()) {}
	public: // copy/move/destruct
		Point(const Point<quad>&) = default;
		Point<quad>& operator=(const Point<quad>&) = default;
		Point(Point<quad>&&) = default;
		Point<quad>& operator=(Point<quad>&&) = default;
		~Point() = default;
	public: // member
		///	水平軸の値を取得します。
		constexpr int X() const { return _x; }
		///	垂直軸の値を取得します。
		constexpr int Y() const { return _y; }
		constexpr bool IsEmpty() const { return (_x==0)&&(_y==0); }

		constexpr Point<quad> operator+(const Point<quad>& other) const { return Point<quad>(_x + other._x, _y + other._y); }
		constexpr Point<quad> operator+(const RectangleSize& other) const { return Point<quad>(_x + other.Width(), _y + other.Height()); }
		constexpr Point<quad>& operator+=(const Point<quad>& other) { return *this = *this + other; }
		constexpr Point<quad>& operator+=(const RectangleSize& other) { return *this = *this + other; }
		constexpr Point<quad> operator-(const Point<quad>& other) const { return Point<quad>(_x - other._x, _y - other._y); }
		constexpr Point<quad> operator-(const RectangleSize& other) const { return Point<quad>(_x - other.Width(), _y - other.Height()); }
		constexpr Point<quad>& operator-=(const Point<quad>& other) { return *this = *this - other; }
		constexpr Point<quad>& operator-=(const RectangleSize& other) { return *this = *this - other; }

		///	指定されたオブジェクトがこのオブジェクトと等価であることをテストします。
		constexpr bool Equals(const Point<quad>& value) const { return (_x == value._x)&&(_y == value._y); }
		constexpr bool operator==(const Point<quad>& value) const { return Equals(value); }
		constexpr bool operator!=(const Point<quad>& value) const { return !Equals(value); }

		constexpr explicit operator RectangleSize() const { return RectangleSize(_x, _y); }

		///	空の @a Point を表します。
		static constexpr Point<quad> Empty() { return Point<quad>{}; }
	};
	///	二次元平面上におけるある一点を表します。
	template<Quadrants quad = Quadrants::UpRight>
	struct PointF final
	{
	private: // contains
		float _x;
		float _y;
	public: // construct
		constexpr PointF() : _x(), _y() {}
		constexpr PointF(const float& x, const float& y) : _x(x), _y(y) {}
		constexpr PointF(const Point<quad>& value) : _x(value.X()), _y(value.Y()) {}
		template<Quadrants fromquad>
		constexpr PointF(const PointF<fromquad>& from) : _x((QuadrantConvertHelper<fromquad, quad>::InvertX())?(-from._x):(from._x)), _y((QuadrantConvertHelper<fromquad, quad>::InvertY())?(-from._y):(from._y)) {}
		constexpr explicit PointF(const RectangleSizeF& from) : _x(from.Width()), _y(from.Height()) {}
	public: // copy/move/destruct
		PointF(const PointF<quad>&) = default;
		PointF<quad>& operator=(const PointF<quad>&) = default;
		PointF(PointF<quad>&&) = default;
		PointF<quad>& operator=(PointF<quad>&&) = default;
		~PointF() = default;
	public: // member
		///	水平軸の値を取得します。
		constexpr float X() const { return _x; }
		///	垂直軸の値を取得します。
		constexpr float Y() const { return _y; }
		constexpr bool IsEmpty() const { return (_x==0)&&(_y==0); }

		constexpr PointF<quad> operator+(const PointF<quad>& other) const { return PointF<quad>(_x + other._x, _y + other._y); }
		constexpr PointF<quad> operator+(const RectangleSizeF& other) const { return PointF<quad>(_x + other.Width(), _y + other.Height()); }
		constexpr PointF<quad>& operator+=(const PointF<quad>& other) { return *this = *this + other; }
		constexpr PointF<quad>& operator+=(const RectangleSizeF& other) { return *this = *this + other; }
		constexpr PointF<quad> operator-(const PointF<quad>& other) const { return PointF<quad>(_x - other._x, _y - other._y); }
		constexpr PointF<quad> operator-(const RectangleSizeF& other) const { return PointF<quad>(_x - other.Width(), _y - other.Height()); }
		constexpr PointF<quad>& operator-=(const PointF<quad>& other) { return *this = *this - other; }
		constexpr PointF<quad>& operator-=(const RectangleSizeF& other) { return *this = *this - other; }
		constexpr PointF<quad> operator*(const PointF<quad>& other) const { return PointF<quad>(_x * other._x, _y * other._y); }
		constexpr PointF<quad> operator*(const float& other) const { return PointF<quad>(_x * other, _y * other); }
		constexpr PointF<quad>& operator*=(const float& other) { return *this = *this * other; }
		constexpr PointF<quad> operator/(const PointF<quad>& other) const { return PointF<quad>(_x / other._x, _y / other._y); }
		constexpr PointF<quad> operator/(const float& other) const { return PointF<quad>(_x / other, _y / other); }
		constexpr PointF<quad>& operator/=(const float& other) { return *this = *this / other; }

		///	指定されたオブジェクトがこのオブジェクトと等価であることをテストします。
		constexpr bool Equals(const PointF<quad>& other) const { return (_x == other._x)&&(_y == other._y); }
		constexpr bool operator==(const PointF<quad>& other) { return Equals(other); }
		constexpr bool operator!=(const PointF<quad>& other) { return !Equals(other); }

		constexpr explicit operator Point<quad>() const { return Point<quad>(int(_x), int(_y)); }
		constexpr explicit operator RectangleSizeF() const { return RectangleSizeF(_x, _y); }

		///	@a PointF<quad> の小数部を抜き出します。
		PointF<quad> Extract() const { return PointF<quad>(_x - truncf(_x), _y - truncf(_y)); }
		///	@a PointF を切り捨て方向に丸め、 @a Point に変換します。
		Point<quad> Floor() const { return Point<quad>(floorf(X()), floorf(Y())); }
		///	@a PointF を切り上げ方向に丸め、 @a Point に変換します。
		Point<quad> Ceiling() const { return Point<quad>(ceilf(X()), ceilf(Y())); }
		/// @a PointF を最も近い @a Point に変換します。
		Point<quad> Round() const { return Point<quad>(roundf(X()), roundf(Y())); }

		///	空の @a PointF を表します。
		static constexpr PointF<quad> Empty() { return PointF<quad>{}; }
	};

	typedef Point<Quadrants::UpRight> GeometricPoint;
	typedef PointF<Quadrants::UpRight> GeometricPointF;

}
#endif // __stationaryorbit_core_point__