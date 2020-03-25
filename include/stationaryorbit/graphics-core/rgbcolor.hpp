#ifndef __stationaryorbit_graphics_core_rgbcolor__
#define __stationaryorbit_graphics_core_rgbcolor__
#include <cstdint>
#include "stationaryorbit/exception/soexcept"
namespace zawa_ch::StationaryOrbit::Graphics
{
	///	赤(Red), 緑(Green), 青(Blue)の三要素とアルファ値によって表される色。
	struct ARGB32 final
	{
	private: // contains
		uint32_t _value;
	public: // constructor
		constexpr ARGB32() : _value() {}
	private: // constructor
		constexpr explicit ARGB32(const uint32_t& value) : _value(value) {}
	public: // member
		constexpr uint8_t Alpha() const { return (_value >> 24) & 0xFF; }
		constexpr uint8_t R() const { return (_value >> 16) & 0xFF; }
		constexpr uint8_t G() const { return (_value >> 8) & 0xFF; }
		constexpr uint8_t B() const { return (_value >> 0) & 0xFF; }
		constexpr bool IsEmpty() const { return *this == Empty(); }
		constexpr static ARGB32 FromArgb(const uint32_t& argb) { return ARGB32(argb); }
		constexpr static ARGB32 FromArgb(const uint8_t& a, const ARGB32& basecolor) { return ARGB32((a << 24)|(basecolor._value & 0x00FFFFFF)); }
		constexpr static ARGB32 FromArgb(const uint8_t& r, const uint8_t& g, const uint8_t& b) { return FromArgb(r, g, b, 255U); }
		constexpr static ARGB32 FromArgb(const uint8_t& r, const uint8_t& g, const uint8_t& b, const uint8_t& a) { return ARGB32((a << 24)|(r << 16)|(g << 8)|(b)); }
		///	指定されたオブジェクトがこのオブジェクトと等価であることをテストします。
		constexpr bool Equals(const ARGB32& other) const { return (_value == other._value); }
		constexpr bool operator==(const ARGB32& other) const { return Equals(other); }
		constexpr bool operator!=(const ARGB32& other) const { return !Equals(other); }
		constexpr static ARGB32 Empty() { return ARGB32(); }
	};
	///	赤(Red), 緑(Green), 青(Blue)の三要素によって表される色。
	struct RGBColor final
	{
	private: // contains
		float _r;
		float _g;
		float _b;
	public: // constructor
		///	既定の @a RGBColor を初期化します。
		constexpr RGBColor() : _r(), _g(), _b() {}
		///	RGB値を指定して @a RGBColor を初期化します。
		constexpr RGBColor(float r, float g, float b) : _r(r), _g(g), _b(b) {}
		///	@a ARGB32 を @a RGBColor に変換します。
		explicit RGBColor(const ARGB32& color) : _r(color.R() / 255.0f), _g(color.G() / 255.0f), _b(color.B() / 255.0f) { if (color.Alpha() == 0) { throw InvalidOperationException("指定された color のアルファ値が0です。"); } }
	public: // member
		///	この @a RGBColor の赤要素を取得します。
		constexpr const float& R() const { return _r; }
		///	この @a RGBColor の緑要素を取得します。
		constexpr const float& G() const { return _g; }
		///	この @a RGBColor の青要素を取得します。
		constexpr const float& B() const { return _b; }
		///	この @a RGBColor が正規化されているかを取得します。
		constexpr bool IsNormalized() const { return (0 <= _r)&&(_r <= 1)&&(0 <= _g)&&(_g <= 1)&&(0 <= _b)&&(_b <= 1); }
		///	この @a RGBColor が空であるかを取得します。
		constexpr bool IsEmpty() const { return *this == Empty(); }

		constexpr RGBColor operator+(const RGBColor& other) const { return RGBColor(_r + other._r, _g + other._g, _b + other._b); }
		constexpr RGBColor operator-(const RGBColor& other) const { return RGBColor(_r - other._r, _g - other._g, _b - other._b); }
		constexpr RGBColor operator*(const RGBColor& other) const { return RGBColor(_r * other._r, _g * other._g, _b * other._b); }
		constexpr RGBColor operator*(const float& other) const { return RGBColor(_r * other, _g * other, _b * other); }
		constexpr RGBColor operator/(const RGBColor& other) const { return RGBColor(_r / other._r, _g / other._g, _b / other._b); }
		constexpr RGBColor operator/(const float& other) const { return RGBColor(_r / other, _g / other, _b / other); }
		constexpr RGBColor operator~() const { return RGBColor(1-_r, 1-_g, 1-_b); }
		constexpr RGBColor operator|(const RGBColor& other) const { return RGBColor(((other._r < _r)?(_r):(other._r)), ((other._g < _g)?(_g):(other._g)), ((other._b < _b)?(_b):(other._b))); }
		constexpr RGBColor operator&(const RGBColor& other) const { return RGBColor(((_r < other._r)?(_r):(other._r)), ((_g < other._g)?(_g):(other._g)), ((_b < other._b)?(_b):(other._b))); }
		constexpr RGBColor operator^(const RGBColor& other) const { return (*this | other) & ~(*this & other); }
		constexpr RGBColor& operator+=(const RGBColor& other) { return *this = *this + other; }
		constexpr RGBColor& operator-=(const RGBColor& other) { return *this = *this - other; }
		constexpr RGBColor& operator*=(const RGBColor& other) { return *this = *this * other; }
		constexpr RGBColor& operator*=(const float& other) { return *this = *this * other; }
		constexpr RGBColor& operator/=(const RGBColor& other) { return *this = *this / other; }
		constexpr RGBColor& operator/=(const float& other) { return *this = *this / other; }
		constexpr RGBColor& operator|=(const RGBColor& other) { return *this = *this | other; }
		constexpr RGBColor& operator&=(const RGBColor& other) { return *this = *this & other; }
		constexpr RGBColor& operator^=(const RGBColor& other) { return *this = *this ^ other; }

		///	正規化した @a RGBColor を取得します。
		constexpr RGBColor Normalize() const { return RGBColor(((0 <= _r)?((_r <= 1)?(_r):(1)):(0)), ((0 <= _g)?((_g <= 1)?(_g):(1)):(0)), ((0 <= _b)?((_b <= 1)?(_b):(1)):(0))); }

		constexpr ARGB32 ToARGB32() const { return ARGB32::FromArgb(uint8_t(_r * 255U), uint8_t(_g * 255U), uint8_t(_b * 255U), 255U); }
		constexpr explicit operator ARGB32() const { return ToARGB32(); }

		///	指定されたオブジェクトがこのオブジェクトと等価であることをテストします。
		constexpr bool Equals(const RGBColor& other) const { return (_r == other._r)&&(_g == other._g)&&(_b == other._b); }
		constexpr bool operator==(const RGBColor& other) const { return Equals(other); }
		constexpr bool operator!=(const RGBColor& other) const { return !Equals(other); }

		constexpr static RGBColor Empty() { return RGBColor(); }
	};
	///	赤(Red), 緑(Green), 青(Blue)の三要素とアルファ値によって表される色。
	struct ARGBColor final
	{
	private: // contains
		RGBColor _color;
		float _alpha;
	public: // constructor
		constexpr ARGBColor() : _color(), _alpha() {}
		constexpr explicit ARGBColor(const RGBColor& color) : _color(color), _alpha(1.0f) {}
		constexpr ARGBColor(const RGBColor& color, const float& alpha) : _color(color), _alpha(alpha) {}
		constexpr ARGBColor(const ARGBColor& color, const float& alpha) : _color(color._color), _alpha(alpha) {}
		constexpr ARGBColor(const float& r, const float& g, const float& b) : _color(r, g, b), _alpha(1.0f) {}
		constexpr ARGBColor(const float& r, const float& g, const float& b, const float& alpha) : _color(r, g, b), _alpha(alpha) {}
		constexpr ARGBColor(const ARGB32& color) : _color(color.R() / 255.0f, color.G() / 255.0f, color.B() / 255.0f), _alpha(color.Alpha() / 255.0f) {}
	public: // member
		constexpr const RGBColor& Color() const { return _color; }
		///	この @a ARGBColor の不透明度を取得します。
		constexpr const float& Alpha() const { return _alpha; }
		///	この @a ARGBColor の赤要素を取得します。
		constexpr const float& R() const { return _color.R(); }
		///	この @a ARGBColor の緑要素を取得します。
		constexpr const float& G() const { return _color.G(); }
		///	この @a ARGBColor の青要素を取得します。
		constexpr const float& B() const { return _color.B(); }
		///	この @a ARGBColor が正規化されているかを取得します。
		constexpr bool IsNormalized() const { return (0 <= _alpha)&&(_alpha <= 1)&&(_color.IsNormalized()); }
		///	この @a ARGBColor が空であるかを取得します。
		constexpr bool IsEmpty() const { return *this == Empty(); }

		constexpr ARGBColor operator+(const ARGBColor& other) const { return ARGBColor(_color + (other._color * other._alpha), _alpha); }
		constexpr ARGBColor operator+(const RGBColor& other) const { return ARGBColor(_color + other, _alpha); }
		constexpr ARGBColor operator-(const ARGBColor& other) const { return ARGBColor(_color - (other._color * other._alpha), _alpha); }
		constexpr ARGBColor operator-(const RGBColor& other) const { return ARGBColor(_color - other, _alpha); }
		constexpr ARGBColor operator*(const ARGBColor& other) const { return ARGBColor(_color * (other._color * other._alpha), _alpha); }
		constexpr ARGBColor operator*(const RGBColor& other) const { return ARGBColor(_color * other, _alpha); }
		constexpr ARGBColor operator*(const float& other) const { return ARGBColor(_color, _alpha * other); }
		constexpr ARGBColor operator/(const ARGBColor& other) const { return ARGBColor(_color / (other._color * other._alpha), _alpha); }
		constexpr ARGBColor operator/(const RGBColor& other) const { return ARGBColor(_color / other, _alpha); }
		constexpr ARGBColor operator/(const float& other) const { return ARGBColor(_color, _alpha / other); }
		constexpr ARGBColor operator~() const { return ARGBColor(~_color, _alpha); }
		constexpr ARGBColor operator|(const ARGBColor& other) const { return ARGBColor(_color | (other._color * other._alpha), _alpha); }
		constexpr ARGBColor operator|(const RGBColor& other) const { return ARGBColor(_color | other, _alpha); }
		constexpr ARGBColor operator&(const ARGBColor& other) const { return ARGBColor(_color & (other._color * other._alpha), _alpha); }
		constexpr ARGBColor operator&(const RGBColor& other) const { return ARGBColor(_color & other, _alpha); }
		constexpr ARGBColor operator^(const ARGBColor& other) const { return ARGBColor(_color ^ (other._color * other._alpha), _alpha); }
		constexpr ARGBColor operator^(const RGBColor& other) const { return ARGBColor(_color ^ other, _alpha); }
		constexpr ARGBColor& operator+=(const ARGBColor& other) { return *this = *this + other; }
		constexpr ARGBColor& operator+=(const RGBColor& other) { return *this = *this + other; }
		constexpr ARGBColor& operator-=(const ARGBColor& other) { return *this = *this - other; }
		constexpr ARGBColor& operator-=(const RGBColor& other) { return *this = *this - other; }
		constexpr ARGBColor& operator*=(const ARGBColor& other) { return *this = *this * other; }
		constexpr ARGBColor& operator*=(const RGBColor& other) { return *this = *this * other; }
		constexpr ARGBColor& operator*=(const float& other) { return *this = *this * other; }
		constexpr ARGBColor& operator/=(const ARGBColor& other) { return *this = *this / other; }
		constexpr ARGBColor& operator/=(const RGBColor& other) { return *this = *this / other; }
		constexpr ARGBColor& operator/=(const float& other) { return *this = *this / other; }
		constexpr ARGBColor& operator|=(const ARGBColor& other) { return *this = *this | other; }
		constexpr ARGBColor& operator|=(const RGBColor& other) { return *this = *this | other; }
		constexpr ARGBColor& operator&=(const ARGBColor& other) { return *this = *this & other; }
		constexpr ARGBColor& operator&=(const RGBColor& other) { return *this = *this & other; }
		constexpr ARGBColor& operator^=(const ARGBColor& other) { return *this = *this ^ other; }
		constexpr ARGBColor& operator^=(const RGBColor& other) { return *this = *this ^ other; }

		///	正規化した @a RGBColor を取得します。
		constexpr ARGBColor Normalize() const { return ARGBColor(_color.Normalize(), ((0 <= _alpha)?((_alpha <= 1)?(_alpha):(1)):(0))); }

		constexpr ARGB32 ToARGB32() const { return ARGB32::FromArgb(uint8_t(R() * 255U), uint8_t(G() * 255U), uint8_t(B() * 255U), uint8_t(_alpha * 255U)); }
		constexpr explicit operator ARGB32() const { return ToARGB32(); }
		constexpr explicit operator RGBColor() const { return Color(); }

		///	指定されたオブジェクトがこのオブジェクトと等価であることをテストします。
		constexpr bool Equals(const ARGBColor& other) const { return (_color == other._color)&&(_alpha == other._alpha); }
		constexpr bool operator==(const ARGBColor& other) const { return Equals(other); }
		constexpr bool operator!=(const ARGBColor& other) const { return !Equals(other); }

		constexpr static ARGBColor Empty() { return ARGBColor(); }
	};
}
#endif // __stationaryorbit_graphics_core_rgbcolor__