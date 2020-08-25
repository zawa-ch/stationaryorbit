#ifndef __stationaryorbit_graphics_core_rgbcolor__
#define __stationaryorbit_graphics_core_rgbcolor__
#include <cstdint>
#include "stationaryorbit/core.numeral.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	///	赤(Red), 緑(Green), 青(Blue)の三要素によって表される色。
	template <class Tp = float>
	struct RGBColor final
	{
	public: // types
		///	この型の各チャネルの値の表現のために内部で使用されている型。
		typedef Proportion<Tp> ChannelType;
	private: // contains
		ChannelType _r;
		ChannelType _g;
		ChannelType _b;
	public: // constructor
		///	既定の @a RGBColor を初期化します。
		constexpr RGBColor() : _r(), _g(), _b() {}
		///	RGB値を指定して @a RGBColor を初期化します。
		constexpr RGBColor(ChannelType r, ChannelType g, ChannelType b) : _r(r), _g(g), _b(b) {}
		template <class fromT>
		constexpr explicit RGBColor(const RGBColor<fromT>& from) : RGBColor(from.template CastTo<Tp>()) {}
	public: // member
		///	この @a RGBColor の赤要素を取得します。
		constexpr const ChannelType& R() const { return _r; }
		///	この @a RGBColor の緑要素を取得します。
		constexpr const ChannelType& G() const { return _g; }
		///	この @a RGBColor の青要素を取得します。
		constexpr const ChannelType& B() const { return _b; }
		///	この @a RGBColor が正規化されているかを取得します。
		constexpr bool IsNormalized() const { return (_r.IsNormalized())&&(_g.IsNormalized())&&(_b.IsNormalized()); }
		///	この @a RGBColor が空であるかを取得します。
		constexpr bool IsEmpty() const { return *this == Empty(); }

		constexpr RGBColor<Tp> operator+(const RGBColor<Tp>& other) const { return RGBColor<Tp>(_r + other._r, _g + other._g, _b + other._b); }
		constexpr RGBColor<Tp> operator-(const RGBColor<Tp>& other) const { return RGBColor<Tp>(_r - other._r, _g - other._g, _b - other._b); }
		constexpr RGBColor<Tp> operator*(const RGBColor<Tp>& other) const { return RGBColor<Tp>(_r * other._r, _g * other._g, _b * other._b); }
		constexpr RGBColor<Tp> operator*(const ChannelType& other) const { return RGBColor<Tp>(_r * other, _g * other, _b * other); }
		constexpr RGBColor<Tp> operator/(const RGBColor<Tp>& other) const { return RGBColor<Tp>(_r / other._r, _g / other._g, _b / other._b); }
		constexpr RGBColor<Tp> operator/(const ChannelType& other) const { return RGBColor<Tp>(_r / other, _g / other, _b / other); }
		constexpr RGBColor<Tp> operator~() const { return RGBColor<Tp>(ChannelType::Max()-_r, ChannelType::Max()-_g, ChannelType::Max()-_b); }
		constexpr RGBColor<Tp> operator|(const RGBColor<Tp>& other) const { return RGBColor<Tp>(((other._r < _r)?(_r):(other._r)), ((other._g < _g)?(_g):(other._g)), ((other._b < _b)?(_b):(other._b))); }
		constexpr RGBColor<Tp> operator&(const RGBColor<Tp>& other) const { return RGBColor<Tp>(((_r < other._r)?(_r):(other._r)), ((_g < other._g)?(_g):(other._g)), ((_b < other._b)?(_b):(other._b))); }
		constexpr RGBColor<Tp> operator^(const RGBColor<Tp>& other) const { return (*this | other) & ~(*this & other); }
		constexpr RGBColor<Tp>& operator+=(const RGBColor<Tp>& other) { return *this = *this + other; }
		constexpr RGBColor<Tp>& operator-=(const RGBColor<Tp>& other) { return *this = *this - other; }
		constexpr RGBColor<Tp>& operator*=(const RGBColor<Tp>& other) { return *this = *this * other; }
		constexpr RGBColor<Tp>& operator*=(const ChannelType& other) { return *this = *this * other; }
		constexpr RGBColor<Tp>& operator/=(const RGBColor<Tp>& other) { return *this = *this / other; }
		constexpr RGBColor<Tp>& operator/=(const ChannelType& other) { return *this = *this / other; }
		constexpr RGBColor<Tp>& operator|=(const RGBColor<Tp>& other) { return *this = *this | other; }
		constexpr RGBColor<Tp>& operator&=(const RGBColor<Tp>& other) { return *this = *this & other; }
		constexpr RGBColor<Tp>& operator^=(const RGBColor<Tp>& other) { return *this = *this ^ other; }

		///	正規化した @a RGBColor を取得します。
		constexpr RGBColor<Tp> Normalize() const { return RGBColor<Tp>(_r.Normalize(), _g.Normalize(), _b.Normalize()); }

		template <class castT>
		constexpr RGBColor<castT> CastTo() const { return RGBColor<castT>(_r.template CastTo<castT>(), _g.template CastTo<castT>(), _g.template CastTo<castT>()); }

		constexpr bool Equals(const RGBColor<Tp>& other) const { return (_r == other._r)&&(_g == other._g)&&(_b == other._b); }
		constexpr bool operator==(const RGBColor<Tp>& other) const { return Equals(other); }
		constexpr bool operator!=(const RGBColor<Tp>& other) const { return !Equals(other); }

		constexpr static RGBColor<Tp> Empty() { return RGBColor<Tp>(); }
	};

	typedef RGBColor<uint8_t> RGBI8_t;
	typedef RGBColor<uint16_t> RGBI16_t;
	typedef RGBColor<float> RGBF32_t;
	typedef RGBColor<double> RGBF64_t;

	///	不透明度の要素を持つ @a RGBColor 。
	template <class Tp = float>
	struct ARGBColor final
	{
	public: // types
		///	この型の各チャネルの値の表現のために内部で使用されている型。
		typedef Proportion<Tp> ChannelType;
	private: // contains
		ChannelType _alpha;
		RGBColor<Tp> _color;
	public: // constructor
		///	既定の @a ARGBColor のオブジェクトを作成します。
		constexpr ARGBColor() : _color(), _alpha() {}
		///	@a RGBColor を @a ARGBColor に変換します。
		constexpr ARGBColor(const RGBColor<Tp>& color) : _color(color), _alpha(ChannelType::Max()) {}
		constexpr ARGBColor(const RGBColor<Tp>& color, const ChannelType& alpha) : _color(color), _alpha(alpha) {}
		constexpr ARGBColor(const ChannelType& r, const ChannelType& g, const ChannelType& b) : _color(r, g, b), _alpha(ChannelType::Max()) {}
		constexpr ARGBColor(const ChannelType& r, const ChannelType& g, const ChannelType& b, const ChannelType& alpha) : _color(r, g, b), _alpha(alpha) {}
		template <class fromT>
		constexpr explicit ARGBColor(const ARGBColor<fromT>& from) : ARGBColor(from.template CastTo<Tp>()) {}
	public: // member
		///	この @a ARGBColor の色要素を示す @a RGBColor を取得します。
		constexpr const RGBColor<Tp>& Color() const { return _color; }
		///	この @a ARGBColor の不透明度を取得します。
		constexpr const ChannelType& Alpha() const { return _alpha; }
		///	この @a ARGBColor の赤要素を取得します。
		constexpr const ChannelType& R() const { return _color.R(); }
		///	この @a ARGBColor の緑要素を取得します。
		constexpr const ChannelType& G() const { return _color.G(); }
		///	この @a ARGBColor の青要素を取得します。
		constexpr const ChannelType& B() const { return _color.B(); }
		///	この @a ARGBColor が正規化されているかを取得します。
		constexpr bool IsNormalized() const { return (_alpha.IsNormalized())&&(_color.IsNormalized()); }
		///	この @a ARGBColor が空であるかを取得します。
		constexpr bool IsEmpty() const { return *this == Empty(); }

		constexpr ARGBColor<Tp> operator+(const ARGBColor<Tp>& other) const { return ARGBColor<Tp>(_color + (other._color * other._alpha), _alpha); }
		constexpr ARGBColor<Tp> operator+(const RGBColor<Tp>& other) const { return ARGBColor<Tp>(_color + other, _alpha); }
		constexpr ARGBColor<Tp> operator-(const ARGBColor<Tp>& other) const { return ARGBColor<Tp>(_color - (other._color * other._alpha), _alpha); }
		constexpr ARGBColor<Tp> operator-(const RGBColor<Tp>& other) const { return ARGBColor<Tp>(_color - other, _alpha); }
		constexpr ARGBColor<Tp> operator*(const ARGBColor<Tp>& other) const { return ARGBColor<Tp>(_color * (other._color * other._alpha), _alpha); }
		constexpr ARGBColor<Tp> operator*(const RGBColor<Tp>& other) const { return ARGBColor<Tp>(_color * other, _alpha); }
		constexpr ARGBColor<Tp> operator*(const float& other) const { return ARGBColor<Tp>(_color, _alpha * other); }
		constexpr ARGBColor<Tp> operator/(const ARGBColor<Tp>& other) const { return ARGBColor<Tp>(_color / (other._color * other._alpha), _alpha); }
		constexpr ARGBColor<Tp> operator/(const RGBColor<Tp>& other) const { return ARGBColor<Tp>(_color / other, _alpha); }
		constexpr ARGBColor<Tp> operator/(const float& other) const { return ARGBColor<Tp>(_color, _alpha / other); }
		constexpr ARGBColor<Tp> operator~() const { return ARGBColor<Tp>(~_color, _alpha); }
		constexpr ARGBColor<Tp> operator|(const ARGBColor<Tp>& other) const { return ARGBColor<Tp>(_color | (other._color * other._alpha), _alpha); }
		constexpr ARGBColor<Tp> operator|(const RGBColor<Tp>& other) const { return ARGBColor<Tp>(_color | other, _alpha); }
		constexpr ARGBColor<Tp> operator&(const ARGBColor<Tp>& other) const { return ARGBColor<Tp>(_color & (other._color * other._alpha), _alpha); }
		constexpr ARGBColor<Tp> operator&(const RGBColor<Tp>& other) const { return ARGBColor<Tp>(_color & other, _alpha); }
		constexpr ARGBColor<Tp> operator^(const ARGBColor<Tp>& other) const { return ARGBColor<Tp>(_color ^ (other._color * other._alpha), _alpha); }
		constexpr ARGBColor<Tp> operator^(const RGBColor<Tp>& other) const { return ARGBColor<Tp>(_color ^ other, _alpha); }
		constexpr ARGBColor<Tp>& operator+=(const ARGBColor<Tp>& other) { return *this = *this + other; }
		constexpr ARGBColor<Tp>& operator+=(const RGBColor<Tp>& other) { return *this = *this + other; }
		constexpr ARGBColor<Tp>& operator-=(const ARGBColor<Tp>& other) { return *this = *this - other; }
		constexpr ARGBColor<Tp>& operator-=(const RGBColor<Tp>& other) { return *this = *this - other; }
		constexpr ARGBColor<Tp>& operator*=(const ARGBColor<Tp>& other) { return *this = *this * other; }
		constexpr ARGBColor<Tp>& operator*=(const RGBColor<Tp>& other) { return *this = *this * other; }
		constexpr ARGBColor<Tp>& operator*=(const float& other) { return *this = *this * other; }
		constexpr ARGBColor<Tp>& operator/=(const ARGBColor<Tp>& other) { return *this = *this / other; }
		constexpr ARGBColor<Tp>& operator/=(const RGBColor<Tp>& other) { return *this = *this / other; }
		constexpr ARGBColor<Tp>& operator/=(const float& other) { return *this = *this / other; }
		constexpr ARGBColor<Tp>& operator|=(const ARGBColor<Tp>& other) { return *this = *this | other; }
		constexpr ARGBColor<Tp>& operator|=(const RGBColor<Tp>& other) { return *this = *this | other; }
		constexpr ARGBColor<Tp>& operator&=(const ARGBColor<Tp>& other) { return *this = *this & other; }
		constexpr ARGBColor<Tp>& operator&=(const RGBColor<Tp>& other) { return *this = *this & other; }
		constexpr ARGBColor<Tp>& operator^=(const ARGBColor<Tp>& other) { return *this = *this ^ other; }
		constexpr ARGBColor<Tp>& operator^=(const RGBColor<Tp>& other) { return *this = *this ^ other; }

		///	正規化した @a RGBColor を取得します。
		constexpr ARGBColor<Tp> Normalize() const { return ARGBColor<Tp>(_color.Normalize(), _alpha.Normalize()); }

		constexpr explicit operator RGBColor<Tp>() const { return Color(); }
		template <class castT>
		constexpr ARGBColor<castT> CastTo() const { return ARGBColor<castT>(_color.template CastTo<castT>(), _alpha.template CastTo<castT>()); }

		///	指定されたオブジェクトがこのオブジェクトと等価であることをテストします。
		constexpr bool Equals(const ARGBColor<Tp>& other) const { return (_color == other._color)&&(_alpha == other._alpha); }
		constexpr bool operator==(const ARGBColor<Tp>& other) const { return Equals(other); }
		constexpr bool operator!=(const ARGBColor<Tp>& other) const { return !Equals(other); }

		constexpr static ARGBColor<Tp> Empty() { return ARGBColor<Tp>(); }
	};

	typedef ARGBColor<uint8_t> ARGBI8_t;
	typedef ARGBColor<uint16_t> ARGBI16_t;
	typedef ARGBColor<float> ARGBF32_t;
	typedef ARGBColor<double> ARGBF64_t;
}
#endif // __stationaryorbit_graphics_core_rgbcolor__
