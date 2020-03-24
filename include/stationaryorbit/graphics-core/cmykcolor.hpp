#ifndef __stationaryorbit_graphics_core_cmykcolor__
#define __stationaryorbit_graphics_core_cmykcolor__
#include "rgbcolor.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	struct CMYColor final
	{
	private:
		float _c;
		float _m;
		float _y;
	public: // construct
		///	既定の @a CMYColor を初期化します。
		constexpr CMYColor() : _c(), _m(), _y() {}
		///	CMY値を指定して @a CMYColor を初期化します。
		constexpr CMYColor(const float& c, const float& m, const float& y) : _c(c), _m(m), _y(y) {}
		///	@a RGBColor を変換します。
		constexpr explicit CMYColor(const RGBColor& color) : _c(1.f - color.R()), _m(1.f - color.G()), _y(1.f - color.B()) {}
	public: // member
		///	この @a YUVColor の赤要素を取得します。
		constexpr const float& C() const { return _c; }
		///	この @a YUVColor の緑要素を取得します。
		constexpr const float& M() const { return _m; }
		///	この @a YUVColor の青要素を取得します。
		constexpr const float& Y() const { return _y; }
		///	この @a YUVColor が正規化されているかを取得します。
		constexpr bool IsNormalized() const { return (0 <= _c)&&(_c <= 1)&&(0 <= _m)&&(_m <= 1)&&(0 <= _y)&&(_y <= 1); }
		///	この @a YUVColor が空であるかを取得します。
		constexpr bool IsEmpty() const { return *this == Empty(); }

		constexpr CMYColor operator+(const CMYColor& other) const { return CMYColor(_c + other._c, _m + other._m, _y + other._y); }
		constexpr CMYColor operator-(const CMYColor& other) const { return CMYColor(_c - other._c, _m - other._m, _y - other._y); }
		constexpr CMYColor operator*(const CMYColor& other) const { return CMYColor(_c * other._c, _m * other._m, _y * other._y); }
		constexpr CMYColor operator*(const float& other) const { return CMYColor(_c * other, _m * other, _y * other); }
		constexpr CMYColor operator/(const CMYColor& other) const { return CMYColor(_c / other._c, _m / other._m, _y / other._y); }
		constexpr CMYColor operator/(const float& other) const { return CMYColor(_c / other, _m / other, _y / other); }
		constexpr CMYColor operator~() const { return CMYColor(1-_c, 1-_m, 1-_y); }
		constexpr CMYColor operator|(const CMYColor& other) const { return CMYColor(((other._c < _c)?(_c):(other._c)), ((other._m < _m)?(_m):(other._m)), ((other._y < _y)?(_y):(other._y))); }
		constexpr CMYColor operator&(const CMYColor& other) const { return CMYColor(((_c < other._c)?(_c):(other._c)), ((_m < other._m)?(_m):(other._m)), ((_y < other._y)?(_y):(other._y))); }
		constexpr CMYColor operator^(const CMYColor& other) const { return (*this | other) & ~(*this & other); }
		constexpr CMYColor& operator+=(const CMYColor& other) { return *this = *this + other; }
		constexpr CMYColor& operator-=(const CMYColor& other) { return *this = *this - other; }
		constexpr CMYColor& operator*=(const CMYColor& other) { return *this = *this * other; }
		constexpr CMYColor& operator*=(const float& other) { return *this = *this * other; }
		constexpr CMYColor& operator/=(const CMYColor& other) { return *this = *this / other; }
		constexpr CMYColor& operator/=(const float& other) { return *this = *this / other; }
		constexpr CMYColor& operator|=(const CMYColor& other) { return *this = *this | other; }
		constexpr CMYColor& operator&=(const CMYColor& other) { return *this = *this & other; }
		constexpr CMYColor& operator^=(const CMYColor& other) { return *this = *this ^ other; }

		///	正規化した @a CMYColor を取得します。
		constexpr CMYColor Normalize() const { return CMYColor(((0 <= _c)?((_c <= 1)?(_c):(1)):(0)), ((0 <= _m)?((_m <= 1)?(_m):(1)):(0)), ((0 <= _y)?((_y <= 1)?(_y):(1)):(0))); }

		constexpr RGBColor ToRGBColor() const { return RGBColor(1.f - _c, 1.f - _m, 1.f - _y); }
		constexpr explicit operator RGBColor() const { return ToRGBColor(); }

		///	指定されたオブジェクトがこのオブジェクトと等価であることをテストします。
		constexpr bool Equals(const CMYColor& other) const { return (_c == other._c)&&(_m == other._m)&&(_y == other._y); }
		constexpr bool operator==(const CMYColor& other) const { return Equals(other); }
		constexpr bool operator!=(const CMYColor& other) const { return !Equals(other); }

		constexpr static CMYColor Empty() { return CMYColor(); }
	};
}
#endif // __stationaryorbit_graphics_core_cmykcolor__