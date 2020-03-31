#ifndef __stationaryorbit_graphics_core_xyzcolor__
#define __stationaryorbit_graphics_core_xyzcolor__
#include <cstdint>
#include "stationaryorbit/exception/soexcept"
namespace zawa_ch::StationaryOrbit::Graphics
{
	///	CIE1931 XYZ色空間によって表される色。
	struct XYZColor final
	{
	private: // contains
		float _x;
		float _y;
		float _z;
	public: // construct
		constexpr XYZColor() : _x(), _y(), _z() {}
		constexpr XYZColor(const float& x, const float& y, const float& z) : _x(x), _y(y), _z(z) {}
	public: // member
		///	この @a XYZColor のXコンポーネントを取得します。
		constexpr const float& X() const { return _x; }
		///	この @a XYZColor のYコンポーネントを取得します。
		constexpr const float& Y() const { return _y; }
		///	この @a XYZColor のZコンポーネントを取得します。
		constexpr const float& Z() const { return _z; }
		///	この @a XYZColor が正規化されているかを取得します。
		constexpr bool IsNormalized() const { return (0 <= _x)&&(_x <= 1)&&(0 <= _y)&&(_y <= 1)&&(0 <= _z)&&(_z <= 1); }
		///	この @a XYZColor が空であるかを取得します。
		constexpr bool IsEmpty() const { return *this == Empty(); }

		constexpr XYZColor operator+(const XYZColor& other) const { return XYZColor(_x + other._x, _y + other._y, _z + other._z); }
		constexpr XYZColor operator-(const XYZColor& other) const { return XYZColor(_x - other._x, _y - other._y, _z - other._z); }
		constexpr XYZColor operator*(const XYZColor& other) const { return XYZColor(_x * other._x, _y * other._y, _z * other._z); }
		constexpr XYZColor operator*(const float& other) const { return XYZColor(_x * other, _y * other, _z * other); }
		constexpr XYZColor operator/(const XYZColor& other) const { return XYZColor(_x / other._x, _y / other._y, _z / other._z); }
		constexpr XYZColor operator/(const float& other) const { return XYZColor(_x / other, _y / other, _z / other); }
		constexpr XYZColor operator~() const { return XYZColor(1-_x, 1-_y, 1-_z); }
		constexpr XYZColor operator|(const XYZColor& other) const { return XYZColor(((other._x < _x)?(_x):(other._x)), ((other._y < _y)?(_y):(other._y)), ((other._z < _z)?(_z):(other._z))); }
		constexpr XYZColor operator&(const XYZColor& other) const { return XYZColor(((_x < other._x)?(_x):(other._x)), ((_y < other._y)?(_y):(other._y)), ((_z < other._z)?(_z):(other._z))); }
		constexpr XYZColor operator^(const XYZColor& other) const { return (*this | other) & ~(*this & other); }
		constexpr XYZColor& operator+=(const XYZColor& other) { return *this = *this + other; }
		constexpr XYZColor& operator-=(const XYZColor& other) { return *this = *this - other; }
		constexpr XYZColor& operator*=(const XYZColor& other) { return *this = *this * other; }
		constexpr XYZColor& operator*=(const float& other) { return *this = *this * other; }
		constexpr XYZColor& operator/=(const XYZColor& other) { return *this = *this / other; }
		constexpr XYZColor& operator/=(const float& other) { return *this = *this / other; }
		constexpr XYZColor& operator|=(const XYZColor& other) { return *this = *this | other; }
		constexpr XYZColor& operator&=(const XYZColor& other) { return *this = *this & other; }
		constexpr XYZColor& operator^=(const XYZColor& other) { return *this = *this ^ other; }

		///	正規化した @a XYZColor を取得します。
		constexpr XYZColor Normalize() const { return XYZColor(((0 <= _x)?((_x <= 1)?(_x):(1)):(0)), ((0 <= _y)?((_y <= 1)?(_y):(1)):(0)), ((0 <= _z)?((_z <= 1)?(_z):(1)):(0))); }

		///	指定されたオブジェクトがこのオブジェクトと等価であることをテストします。
		constexpr bool Equals(const XYZColor& other) const { return (_x == other._x)&&(_y == other._y)&&(_z == other._z); }
		constexpr bool operator==(const XYZColor& other) const { return Equals(other); }
		constexpr bool operator!=(const XYZColor& other) const { return !Equals(other); }

		constexpr static XYZColor Empty() { return XYZColor(); }
	};
	///	CIE1931 XYZ色空間と不透明度によって表される色。
	struct AXYZColor final
	{
	private: // contains
		XYZColor _color;
		float _alpha;
	public: // construct
		constexpr AXYZColor() :_color(), _alpha() {}
		constexpr explicit AXYZColor(const XYZColor& color) :_color(color), _alpha(1.0f) {}
		constexpr AXYZColor(const float& x, const float& y, const float& z) : _color(x, y, z), _alpha(1.0f) {}
		constexpr AXYZColor(const XYZColor& color, const float& alpha) :_color(color), _alpha(alpha) {}
		constexpr AXYZColor(const float& x, const float& y, const float& z, const float& alpha) : _color(x, y, z), _alpha(alpha) {}
	public: // member
		constexpr const XYZColor& Color() const { return _color; }
		///	この @a AXYZColor の不透明度を取得します。
		constexpr const float& Alpha() const { return _alpha; }
		///	この @a AXYZColor のXコンポーネントを取得します。
		constexpr const float& X() const { return _color.X(); }
		///	この @a AXYZColor のYコンポーネントを取得します。
		constexpr const float& Y() const { return _color.Y(); }
		///	この @a AXYZColor のZコンポーネントを取得します。
		constexpr const float& Z() const { return _color.Z(); }
		///	この @a AXYZColor が正規化されているかを取得します。
		constexpr bool IsNormalized() const { return (_color.IsNormalized())&&(0 <= _alpha)&&(_alpha <= 1); }
		///	この @a AXYZColor が空であるかを取得します。
		constexpr bool IsEmpty() const { return *this == Empty(); }

		constexpr AXYZColor operator+(const AXYZColor& other) const { return AXYZColor(_color + (other._color * other._alpha), _alpha); }
		constexpr AXYZColor operator+(const XYZColor& other) const { return AXYZColor(_color + other, _alpha); }
		constexpr AXYZColor operator-(const AXYZColor& other) const { return AXYZColor(_color - (other._color * other._alpha), _alpha); }
		constexpr AXYZColor operator-(const XYZColor& other) const { return AXYZColor(_color - other, _alpha); }
		constexpr AXYZColor operator*(const AXYZColor& other) const { return AXYZColor(_color * (other._color * other._alpha), _alpha); }
		constexpr AXYZColor operator*(const XYZColor& other) const { return AXYZColor(_color * other, _alpha); }
		constexpr AXYZColor operator*(const float& other) const { return AXYZColor(_color, _alpha * other); }
		constexpr AXYZColor operator/(const AXYZColor& other) const { return AXYZColor(_color / (other._color * other._alpha), _alpha); }
		constexpr AXYZColor operator/(const XYZColor& other) const { return AXYZColor(_color / other, _alpha); }
		constexpr AXYZColor operator/(const float& other) const { return AXYZColor(_color, _alpha / other); }
		constexpr AXYZColor operator~() const { return AXYZColor(~_color, _alpha); }
		constexpr AXYZColor operator|(const AXYZColor& other) const { return AXYZColor(_color | (other._color * other._alpha), _alpha); }
		constexpr AXYZColor operator|(const XYZColor& other) const { return AXYZColor(_color | other, _alpha); }
		constexpr AXYZColor operator&(const AXYZColor& other) const { return AXYZColor(_color & (other._color * other._alpha), _alpha); }
		constexpr AXYZColor operator&(const XYZColor& other) const { return AXYZColor(_color & other, _alpha); }
		constexpr AXYZColor operator^(const AXYZColor& other) const { return AXYZColor(_color ^ (other._color * other._alpha), _alpha); }
		constexpr AXYZColor operator^(const XYZColor& other) const { return AXYZColor(_color ^ other, _alpha); }
		constexpr AXYZColor& operator+=(const AXYZColor& other) { return *this = *this + other; }
		constexpr AXYZColor& operator+=(const XYZColor& other) { return *this = *this + other; }
		constexpr AXYZColor& operator-=(const AXYZColor& other) { return *this = *this - other; }
		constexpr AXYZColor& operator-=(const XYZColor& other) { return *this = *this - other; }
		constexpr AXYZColor& operator*=(const AXYZColor& other) { return *this = *this * other; }
		constexpr AXYZColor& operator*=(const XYZColor& other) { return *this = *this * other; }
		constexpr AXYZColor& operator*=(const float& other) { return *this = *this * other; }
		constexpr AXYZColor& operator/=(const AXYZColor& other) { return *this = *this / other; }
		constexpr AXYZColor& operator/=(const XYZColor& other) { return *this = *this / other; }
		constexpr AXYZColor& operator/=(const float& other) { return *this = *this / other; }
		constexpr AXYZColor& operator|=(const AXYZColor& other) { return *this = *this | other; }
		constexpr AXYZColor& operator|=(const XYZColor& other) { return *this = *this | other; }
		constexpr AXYZColor& operator&=(const AXYZColor& other) { return *this = *this & other; }
		constexpr AXYZColor& operator&=(const XYZColor& other) { return *this = *this & other; }
		constexpr AXYZColor& operator^=(const AXYZColor& other) { return *this = *this ^ other; }
		constexpr AXYZColor& operator^=(const XYZColor& other) { return *this = *this ^ other; }

		///	正規化した @a AXYZColor を取得します。
		constexpr AXYZColor Normalize() const { return AXYZColor(_color.Normalize(), ((0 <= _alpha)?((_alpha <= 1)?(_alpha):(1)):(0))); }

		///	指定されたオブジェクトがこのオブジェクトと等価であることをテストします。
		constexpr bool Equals(const AXYZColor& other) const { return (_color == other._color)&&(_alpha == other._alpha); }
		constexpr bool operator==(const AXYZColor& other) const { return Equals(other); }
		constexpr bool operator!=(const AXYZColor& other) const { return !Equals(other); }

		constexpr static AXYZColor Empty() { return AXYZColor(); }
	};
}
#endif // __stationaryorbit_graphics_core_xyzcolor__