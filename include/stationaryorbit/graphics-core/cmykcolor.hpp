#ifndef __stationaryorbit_graphics_core_cmykcolor__
#define __stationaryorbit_graphics_core_cmykcolor__
#include <algorithm>
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
		///	この @a CMYColor のシアンのコンポーネントを取得します。
		constexpr const float& C() const { return _c; }
		///	この @a CMYColor のマゼンタのコンポーネントを取得します。
		constexpr const float& M() const { return _m; }
		///	この @a CMYColor のイエローのコンポーネントを取得します。
		constexpr const float& Y() const { return _y; }
		///	この @a CMYColor が正規化されているかを取得します。
		constexpr bool IsNormalized() const { return (0 <= _c)&&(_c <= 1)&&(0 <= _m)&&(_m <= 1)&&(0 <= _y)&&(_y <= 1); }
		///	この @a CMYColor が空であるかを取得します。
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

		constexpr explicit operator RGBColor() const { return RGBColor(1.f - _c, 1.f - _m, 1.f - _y); }

		///	指定されたオブジェクトがこのオブジェクトと等価であることをテストします。
		constexpr bool Equals(const CMYColor& other) const { return (_c == other._c)&&(_m == other._m)&&(_y == other._y); }
		constexpr bool operator==(const CMYColor& other) const { return Equals(other); }
		constexpr bool operator!=(const CMYColor& other) const { return !Equals(other); }

		constexpr static CMYColor Empty() { return CMYColor(); }
	};
	struct ACMYColor final
	{
	private:
		CMYColor _color;
		float _alpha;
	public: // construct
		///	既定の @a ACMYColor を初期化します。
		constexpr ACMYColor() : _alpha(), _color() {}
		///	CMY値を指定して @a ACMYColor を初期化します。
		constexpr ACMYColor(const float& c, const float& m, const float& y) : _alpha(1.f), _color(c, m, y) {}
		///	CMY値を指定して @a ACMYColor を初期化します。
		constexpr ACMYColor(const float& c, const float& m, const float& y, const float& alpha) : _alpha(alpha), _color(c, m, y) {}
		///	CMY値を指定して @a ACMYColor を初期化します。
		constexpr ACMYColor(const CMYColor& color) : _alpha(1.f), _color(color) {}
		///	CMY値を指定して @a ACMYColor を初期化します。
		constexpr ACMYColor(const CMYColor& color, const float& alpha) : _alpha(alpha), _color(color) {}
		///	@a RGBColor を変換します。
		constexpr explicit ACMYColor(const ARGBColor& color) : _alpha(color.Alpha()), _color(color.Color()) {}
	public: // member
		constexpr const CMYColor& Color() const { return _color; }
		///	この @a ACMYColor の不透明度を取得します。
		constexpr const float& Alpha() const { return _alpha; }
		///	この @a ACMYColor のシアンのコンポーネントを取得します。
		constexpr const float& C() const { return _color.C(); }
		///	この @a ACMYColor のマゼンタのコンポーネントを取得します。
		constexpr const float& M() const { return _color.M(); }
		///	この @a ACMYColor のイエローのコンポーネントを取得します。
		constexpr const float& Y() const { return _color.Y(); }
		///	この @a ACMYColor が正規化されているかを取得します。
		constexpr bool IsNormalized() const { return (_color.IsNormalized())&&(0 <= _alpha)&&(_alpha <= 1); }
		///	この @a ACMYColor が空であるかを取得します。
		constexpr bool IsEmpty() const { return *this == Empty(); }

		constexpr ACMYColor operator+(const ACMYColor& other) const { return ACMYColor(_color + (other._color), _alpha); }
		constexpr ACMYColor operator+(const CMYColor& other) const { return ACMYColor(_color + other, _alpha); }
		constexpr ACMYColor operator-(const ACMYColor& other) const { return ACMYColor(_color - (other._color), _alpha); }
		constexpr ACMYColor operator-(const CMYColor& other) const { return ACMYColor(_color - other, _alpha); }
		constexpr ACMYColor operator*(const ACMYColor& other) const { return ACMYColor(_color * (other._color), _alpha); }
		constexpr ACMYColor operator*(const CMYColor& other) const { return ACMYColor(_color * other, _alpha); }
		constexpr ACMYColor operator*(const float& other) const { return ACMYColor(_color, _alpha * other); }
		constexpr ACMYColor operator/(const ACMYColor& other) const { return ACMYColor(_color / (other._color), _alpha); }
		constexpr ACMYColor operator/(const CMYColor& other) const { return ACMYColor(_color / other, _alpha); }
		constexpr ACMYColor operator/(const float& other) const { return ACMYColor(_color, _alpha / other); }
		constexpr ACMYColor operator~() const { return ACMYColor(~_color, _alpha); }
		constexpr ACMYColor operator|(const ACMYColor& other) const { return ACMYColor(_color | (other._color), _alpha); }
		constexpr ACMYColor operator|(const CMYColor& other) const { return ACMYColor(_color | other, _alpha); }
		constexpr ACMYColor operator&(const ACMYColor& other) const { return ACMYColor(_color & (other._color), _alpha); }
		constexpr ACMYColor operator&(const CMYColor& other) const { return ACMYColor(_color & other, _alpha); }
		constexpr ACMYColor operator^(const ACMYColor& other) const { return ACMYColor(_color ^ (other._color), _alpha); }
		constexpr ACMYColor operator^(const CMYColor& other) const { return ACMYColor(_color ^ other, _alpha); }
		constexpr ACMYColor& operator+=(const ACMYColor& other) { return *this = *this + other; }
		constexpr ACMYColor& operator+=(const CMYColor& other) { return *this = *this + other; }
		constexpr ACMYColor& operator-=(const ACMYColor& other) { return *this = *this - other; }
		constexpr ACMYColor& operator-=(const CMYColor& other) { return *this = *this - other; }
		constexpr ACMYColor& operator*=(const ACMYColor& other) { return *this = *this * other; }
		constexpr ACMYColor& operator*=(const CMYColor& other) { return *this = *this * other; }
		constexpr ACMYColor& operator*=(const float& other) { return *this = *this * other; }
		constexpr ACMYColor& operator/=(const ACMYColor& other) { return *this = *this / other; }
		constexpr ACMYColor& operator/=(const CMYColor& other) { return *this = *this / other; }
		constexpr ACMYColor& operator/=(const float& other) { return *this = *this / other; }
		constexpr ACMYColor& operator|=(const ACMYColor& other) { return *this = *this | other; }
		constexpr ACMYColor& operator|=(const CMYColor& other) { return *this = *this | other; }
		constexpr ACMYColor& operator&=(const ACMYColor& other) { return *this = *this & other; }
		constexpr ACMYColor& operator&=(const CMYColor& other) { return *this = *this & other; }
		constexpr ACMYColor& operator^=(const ACMYColor& other) { return *this = *this ^ other; }
		constexpr ACMYColor& operator^=(const CMYColor& other) { return *this = *this ^ other; }

		///	正規化した @a ACMYColor を取得します。
		constexpr ACMYColor Normalize() const { return ACMYColor(_color.Normalize(), ((0 <= _alpha)?((_alpha <= 1)?(_alpha):(1)):(0))); }

		constexpr explicit operator ARGBColor() const { return ARGBColor(RGBColor(_color), _alpha); }
		constexpr explicit operator CMYColor() const { return Color(); }

		///	指定されたオブジェクトがこのオブジェクトと等価であることをテストします。
		constexpr bool Equals(const ACMYColor& other) const { return (_color == other._color)&&(_alpha == other._alpha); }
		constexpr bool operator==(const ACMYColor& other) const { return Equals(other); }
		constexpr bool operator!=(const ACMYColor& other) const { return !Equals(other); }

		constexpr static ACMYColor Empty() { return ACMYColor(); }
	};
	struct CMYKColor final
	{
	private:
		float _c;
		float _m;
		float _y;
		float _k;
	public: // construct
		///	既定の @a CMYKColor を初期化します。
		constexpr CMYKColor() : _c(), _m(), _y(), _k() {}
		///	CMY値を指定して @a CMYKColor を初期化します。
		constexpr CMYKColor(const float& c, const float& m, const float& y, const float& k) : _c(c), _m(m), _y(y), _k(k) {}
		constexpr CMYKColor(const CMYColor& color)
			: _c(color.C() - std::min({color.C(), color.M(), color.Y()}))
			, _m(color.M() - std::min({color.C(), color.M(), color.Y()}))
			, _y(color.Y() - std::min({color.C(), color.M(), color.Y()}))
			, _k(std::min({color.C(), color.M(), color.Y()}))
		{}
	public: // member
		///	この @a CMYKColor のシアンのコンポーネントを取得します。
		constexpr const float& C() const { return _c; }
		///	この @a CMYKColor のマゼンタのコンポーネントを取得します。
		constexpr const float& M() const { return _m; }
		///	この @a CMYKColor のイエローのコンポーネントを取得します。
		constexpr const float& Y() const { return _y; }
		///	この @a CMYKColor のキープレート(黒色)のコンポーネントを取得します。
		constexpr const float& K() const { return _k; }
		///	この @a CMYKColor が正規化されているかを取得します。
		constexpr bool IsNormalized() const { return (0 <= _c)&&(_c <= 1)&&(0 <= _m)&&(_m <= 1)&&(0 <= _y)&&(_y <= 1)&&(0 <= _k)&&(_k <= 1); }
		///	この @a CMYKColor が空であるかを取得します。
		constexpr bool IsEmpty() const { return *this == Empty(); }

		constexpr CMYKColor operator+(const CMYKColor& other) const { return CMYKColor(_c + other._c, _m + other._m, _y + other._y, _k + other._k); }
		constexpr CMYKColor operator-(const CMYKColor& other) const { return CMYKColor(_c - other._c, _m - other._m, _y - other._y, _k - other._k); }
		constexpr CMYKColor operator*(const CMYKColor& other) const { return CMYKColor(_c * other._c, _m * other._m, _y * other._y, _k * other._k); }
		constexpr CMYKColor operator*(const float& other) const { return CMYKColor(_c * other, _m * other, _y * other, _k * other); }
		constexpr CMYKColor operator/(const CMYKColor& other) const { return CMYKColor(_c / other._c, _m / other._m, _y / other._y, _k / other._k); }
		constexpr CMYKColor operator/(const float& other) const { return CMYKColor(_c / other, _m / other, _y / other, _k / other); }
		constexpr CMYKColor operator~() const { return CMYKColor(1-_c, 1-_m, 1-_y, 1-_k); }
		constexpr CMYKColor operator|(const CMYKColor& other) const { return CMYKColor(((other._c < _c)?(_c):(other._c)), ((other._m < _m)?(_m):(other._m)), ((other._y < _y)?(_y):(other._y)), ((other._k < _k)?(_k):(other._k))); }
		constexpr CMYKColor operator&(const CMYKColor& other) const { return CMYKColor(((_c < other._c)?(_c):(other._c)), ((_m < other._m)?(_m):(other._m)), ((_y < other._y)?(_y):(other._y)), ((_k < other._k)?(_k):(other._k))); }
		constexpr CMYKColor operator^(const CMYKColor& other) const { return (*this | other) & ~(*this & other); }
		constexpr CMYKColor& operator+=(const CMYKColor& other) { return *this = *this + other; }
		constexpr CMYKColor& operator-=(const CMYKColor& other) { return *this = *this - other; }
		constexpr CMYKColor& operator*=(const CMYKColor& other) { return *this = *this * other; }
		constexpr CMYKColor& operator*=(const float& other) { return *this = *this * other; }
		constexpr CMYKColor& operator/=(const CMYKColor& other) { return *this = *this / other; }
		constexpr CMYKColor& operator/=(const float& other) { return *this = *this / other; }
		constexpr CMYKColor& operator|=(const CMYKColor& other) { return *this = *this | other; }
		constexpr CMYKColor& operator&=(const CMYKColor& other) { return *this = *this & other; }
		constexpr CMYKColor& operator^=(const CMYKColor& other) { return *this = *this ^ other; }

		///	正規化した @a CMYKColor を取得します。
		constexpr CMYKColor Normalize() const { return CMYKColor(((0 <= _c)?((_c <= 1)?(_c):(1)):(0)), ((0 <= _m)?((_m <= 1)?(_m):(1)):(0)), ((0 <= _y)?((_y <= 1)?(_y):(1)):(0)), ((0 <= _k)?((_k <= 1)?(_k):(1)):(0))); }

		constexpr explicit operator CMYColor() const { return CMYColor(_k + _c, _k + _m, _k + _y); }

		///	指定されたオブジェクトがこのオブジェクトと等価であることをテストします。
		constexpr bool Equals(const CMYKColor& other) const { return (_c == other._c)&&(_m == other._m)&&(_y == other._y); }
		constexpr bool operator==(const CMYKColor& other) const { return Equals(other); }
		constexpr bool operator!=(const CMYKColor& other) const { return !Equals(other); }

		constexpr static CMYKColor Empty() { return CMYKColor(); }
	};
}
#endif // __stationaryorbit_graphics_core_cmykcolor__