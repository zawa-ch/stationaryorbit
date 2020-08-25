#ifndef __stationaryorbit_graphics_core_cmykcolor__
#define __stationaryorbit_graphics_core_cmykcolor__
#include <algorithm>
namespace zawa_ch::StationaryOrbit::Graphics
{
	///	シアン(Cyan), マゼンタ(Magenta), イエロー(Yellow)の三要素によって表される色。
	template <class Tp = float>
	struct CMYColor final
	{
	public: // types
		///	この型の各チャネルの値の表現のために内部で使用されている型。
		typedef Proportion<Tp> ChannelType;
	private:
		ChannelType _c;
		ChannelType _m;
		ChannelType _y;
	public: // construct
		///	既定の @a CMYColor を初期化します。
		constexpr CMYColor() : _c(), _m(), _y() {}
		///	CMY値を指定して @a CMYColor を初期化します。
		constexpr CMYColor(const ChannelType& c, const ChannelType& m, const ChannelType& y) : _c(c), _m(m), _y(y) {}
		template <class fromT>
		constexpr explicit CMYColor(const CMYColor<fromT>& from) : CMYColor(from.template CastTo<Tp>()) {}
	public: // member
		///	この @a CMYColor のシアンのコンポーネントを取得します。
		constexpr const ChannelType& C() const { return _c; }
		///	この @a CMYColor のマゼンタのコンポーネントを取得します。
		constexpr const ChannelType& M() const { return _m; }
		///	この @a CMYColor のイエローのコンポーネントを取得します。
		constexpr const ChannelType& Y() const { return _y; }
		///	この @a CMYColor が正規化されているかを取得します。
		constexpr bool IsNormalized() const { return (_c.IsNormalized())&&(_m.IsNormalized())&&(_y.IsNormalized()); }
		///	この @a CMYColor が空であるかを取得します。
		constexpr bool IsEmpty() const { return *this == Empty(); }

		constexpr CMYColor<Tp> operator+(const CMYColor<Tp>& other) const { return CMYColor<Tp>(_c + other._c, _m + other._m, _y + other._y); }
		constexpr CMYColor<Tp> operator-(const CMYColor<Tp>& other) const { return CMYColor<Tp>(_c - other._c, _m - other._m, _y - other._y); }
		constexpr CMYColor<Tp> operator*(const CMYColor<Tp>& other) const { return CMYColor<Tp>(_c * other._c, _m * other._m, _y * other._y); }
		constexpr CMYColor<Tp> operator*(const ChannelType& other) const { return CMYColor<Tp>(_c * other, _m * other, _y * other); }
		constexpr CMYColor<Tp> operator/(const CMYColor<Tp>& other) const { return CMYColor<Tp>(_c / other._c, _m / other._m, _y / other._y); }
		constexpr CMYColor<Tp> operator/(const ChannelType& other) const { return CMYColor<Tp>(_c / other, _m / other, _y / other); }
		constexpr CMYColor<Tp> operator~() const { return CMYColor<Tp>(ChannelType::Max()-_c, ChannelType::Max()-_m, ChannelType::Max()-_y); }
		constexpr CMYColor<Tp> operator|(const CMYColor<Tp>& other) const { return CMYColor<Tp>(((other._c < _c)?(_c):(other._c)), ((other._m < _m)?(_m):(other._m)), ((other._y < _y)?(_y):(other._y))); }
		constexpr CMYColor<Tp> operator&(const CMYColor<Tp>& other) const { return CMYColor<Tp>(((_c < other._c)?(_c):(other._c)), ((_m < other._m)?(_m):(other._m)), ((_y < other._y)?(_y):(other._y))); }
		constexpr CMYColor<Tp> operator^(const CMYColor<Tp>& other) const { return (*this | other) & ~(*this & other); }
		constexpr CMYColor<Tp>& operator+=(const CMYColor<Tp>& other) { return *this = *this + other; }
		constexpr CMYColor<Tp>& operator-=(const CMYColor<Tp>& other) { return *this = *this - other; }
		constexpr CMYColor<Tp>& operator*=(const CMYColor<Tp>& other) { return *this = *this * other; }
		constexpr CMYColor<Tp>& operator*=(const ChannelType& other) { return *this = *this * other; }
		constexpr CMYColor<Tp>& operator/=(const CMYColor<Tp>& other) { return *this = *this / other; }
		constexpr CMYColor<Tp>& operator/=(const ChannelType& other) { return *this = *this / other; }
		constexpr CMYColor<Tp>& operator|=(const CMYColor<Tp>& other) { return *this = *this | other; }
		constexpr CMYColor<Tp>& operator&=(const CMYColor<Tp>& other) { return *this = *this & other; }
		constexpr CMYColor<Tp>& operator^=(const CMYColor<Tp>& other) { return *this = *this ^ other; }

		///	正規化した @a CMYColor を取得します。
		constexpr CMYColor<Tp> Normalize() const { return CMYColor<Tp>(_c.Normalize(), _m.Normalize(), _y.Normalize()); }

		template <class castT>
		constexpr CMYColor<castT> CastTo() const { return CMYColor<castT>(_c.template CastTo<castT>(), _m.template CastTo<castT>(), _y.template CastTo<castT>()); }

		///	指定されたオブジェクトがこのオブジェクトと等価であることをテストします。
		constexpr bool Equals(const CMYColor<Tp>& other) const { return (_c == other._c)&&(_m == other._m)&&(_y == other._y); }
		constexpr bool operator==(const CMYColor<Tp>& other) const { return Equals(other); }
		constexpr bool operator!=(const CMYColor<Tp>& other) const { return !Equals(other); }

		constexpr static CMYColor<Tp> Empty() { return CMYColor<Tp>(); }
	};

	typedef CMYColor<uint8_t> CMYI8_t;
	typedef CMYColor<uint16_t> CMYI16_t;
	typedef CMYColor<float> CMYF32_t;
	typedef CMYColor<double> CMYF64_t;

	///	不透明度の要素を持つ @a CMYColor 。
	template <class Tp = float>
	struct ACMYColor final
	{
	public: // types
		///	この型の各チャネルの値の表現のために内部で使用されている型。
		typedef Proportion<Tp> ChannelType;
	private:
		ChannelType _alpha;
		CMYColor<Tp> _color;
	public: // construct
		///	既定の @a ACMYColor を初期化します。
		constexpr ACMYColor() : _alpha(), _color() {}
		///	CMY値を指定して @a ACMYColor を初期化します。
		constexpr ACMYColor(const ChannelType& c, const ChannelType& m, const ChannelType& y) : _alpha(ChannelType::Max()), _color(c, m, y) {}
		///	CMY値を指定して @a ACMYColor を初期化します。
		constexpr ACMYColor(const ChannelType& c, const ChannelType& m, const ChannelType& y, const ChannelType& alpha) : _alpha(alpha), _color(c, m, y) {}
		///	CMY値を指定して @a ACMYColor を初期化します。
		constexpr ACMYColor(const CMYColor<Tp>& color) : _alpha(ChannelType::Max()), _color(color) {}
		///	CMY値を指定して @a ACMYColor を初期化します。
		constexpr ACMYColor(const CMYColor<Tp>& color, const ChannelType& alpha) : _alpha(alpha), _color(color) {}
	public: // member
		constexpr const CMYColor<Tp>& Color() const { return _color; }
		///	この @a ACMYColor の不透明度を取得します。
		constexpr const ChannelType& Alpha() const { return _alpha; }
		///	この @a ACMYColor のシアンのコンポーネントを取得します。
		constexpr const ChannelType& C() const { return _color.C(); }
		///	この @a ACMYColor のマゼンタのコンポーネントを取得します。
		constexpr const ChannelType& M() const { return _color.M(); }
		///	この @a ACMYColor のイエローのコンポーネントを取得します。
		constexpr const ChannelType& Y() const { return _color.Y(); }
		///	この @a ACMYColor が正規化されているかを取得します。
		constexpr bool IsNormalized() const { return (_color.IsNormalized())&&(_alpha.IsNormalized()); }
		///	この @a ACMYColor が空であるかを取得します。
		constexpr bool IsEmpty() const { return *this == Empty(); }

		constexpr ACMYColor<Tp> operator+(const ACMYColor<Tp>& other) const { return ACMYColor<Tp>(_color + (other._color), _alpha); }
		constexpr ACMYColor<Tp> operator+(const CMYColor<Tp>& other) const { return ACMYColor<Tp>(_color + other, _alpha); }
		constexpr ACMYColor<Tp> operator-(const ACMYColor<Tp>& other) const { return ACMYColor<Tp>(_color - (other._color), _alpha); }
		constexpr ACMYColor<Tp> operator-(const CMYColor<Tp>& other) const { return ACMYColor<Tp>(_color - other, _alpha); }
		constexpr ACMYColor<Tp> operator*(const ACMYColor<Tp>& other) const { return ACMYColor<Tp>(_color * (other._color), _alpha); }
		constexpr ACMYColor<Tp> operator*(const CMYColor<Tp>& other) const { return ACMYColor<Tp>(_color * other, _alpha); }
		constexpr ACMYColor<Tp> operator*(const ChannelType& other) const { return ACMYColor<Tp>(_color, _alpha * other); }
		constexpr ACMYColor<Tp> operator/(const ACMYColor<Tp>& other) const { return ACMYColor<Tp>(_color / (other._color), _alpha); }
		constexpr ACMYColor<Tp> operator/(const CMYColor<Tp>& other) const { return ACMYColor<Tp>(_color / other, _alpha); }
		constexpr ACMYColor<Tp> operator/(const ChannelType& other) const { return ACMYColor<Tp>(_color, _alpha / other); }
		constexpr ACMYColor<Tp> operator~() const { return ACMYColor<Tp>(~_color, _alpha); }
		constexpr ACMYColor<Tp> operator|(const ACMYColor<Tp>& other) const { return ACMYColor<Tp>(_color | (other._color), _alpha); }
		constexpr ACMYColor<Tp> operator|(const CMYColor<Tp>& other) const { return ACMYColor<Tp>(_color | other, _alpha); }
		constexpr ACMYColor<Tp> operator&(const ACMYColor<Tp>& other) const { return ACMYColor<Tp>(_color & (other._color), _alpha); }
		constexpr ACMYColor<Tp> operator&(const CMYColor<Tp>& other) const { return ACMYColor<Tp>(_color & other, _alpha); }
		constexpr ACMYColor<Tp> operator^(const ACMYColor<Tp>& other) const { return ACMYColor<Tp>(_color ^ (other._color), _alpha); }
		constexpr ACMYColor<Tp> operator^(const CMYColor<Tp>& other) const { return ACMYColor<Tp>(_color ^ other, _alpha); }
		constexpr ACMYColor<Tp>& operator+=(const ACMYColor<Tp>& other) { return *this = *this + other; }
		constexpr ACMYColor<Tp>& operator+=(const CMYColor<Tp>& other) { return *this = *this + other; }
		constexpr ACMYColor<Tp>& operator-=(const ACMYColor<Tp>& other) { return *this = *this - other; }
		constexpr ACMYColor<Tp>& operator-=(const CMYColor<Tp>& other) { return *this = *this - other; }
		constexpr ACMYColor<Tp>& operator*=(const ACMYColor<Tp>& other) { return *this = *this * other; }
		constexpr ACMYColor<Tp>& operator*=(const CMYColor<Tp>& other) { return *this = *this * other; }
		constexpr ACMYColor<Tp>& operator*=(const ChannelType& other) { return *this = *this * other; }
		constexpr ACMYColor<Tp>& operator/=(const ACMYColor<Tp>& other) { return *this = *this / other; }
		constexpr ACMYColor<Tp>& operator/=(const CMYColor<Tp>& other) { return *this = *this / other; }
		constexpr ACMYColor<Tp>& operator/=(const ChannelType& other) { return *this = *this / other; }
		constexpr ACMYColor<Tp>& operator|=(const ACMYColor<Tp>& other) { return *this = *this | other; }
		constexpr ACMYColor<Tp>& operator|=(const CMYColor<Tp>& other) { return *this = *this | other; }
		constexpr ACMYColor<Tp>& operator&=(const ACMYColor<Tp>& other) { return *this = *this & other; }
		constexpr ACMYColor<Tp>& operator&=(const CMYColor<Tp>& other) { return *this = *this & other; }
		constexpr ACMYColor<Tp>& operator^=(const ACMYColor<Tp>& other) { return *this = *this ^ other; }
		constexpr ACMYColor<Tp>& operator^=(const CMYColor<Tp>& other) { return *this = *this ^ other; }

		///	正規化した @a ACMYColor を取得します。
		constexpr ACMYColor<Tp> Normalize() const { return ACMYColor<Tp>(_color.Normalize(), _alpha.Normalize()); }

		template <class castT>
		constexpr ACMYColor<castT> CastTo() const { return ACMYColor<castT>(_color.template CastTo<castT>(), _alpha.template CastTo<castT>()); }
		constexpr explicit operator CMYColor<Tp>() const { return Color(); }

		///	指定されたオブジェクトがこのオブジェクトと等価であることをテストします。
		constexpr bool Equals(const ACMYColor<Tp>& other) const { return (_color == other._color)&&(_alpha == other._alpha); }
		constexpr bool operator==(const ACMYColor<Tp>& other) const { return Equals(other); }
		constexpr bool operator!=(const ACMYColor<Tp>& other) const { return !Equals(other); }

		constexpr static ACMYColor<Tp> Empty() { return ACMYColor<Tp>(); }
	};

	typedef ACMYColor<uint8_t> ACMYI8_t;
	typedef ACMYColor<uint16_t> ACMYI16_t;
	typedef ACMYColor<float> ACMYF32_t;
	typedef ACMYColor<double> ACMYF64_t;

	///	シアン(Cyan), マゼンタ(Magenta), イエロー(Yellow), キー プレート(Key plate)の四要素によって表される色。
	template <class Tp = float>
	struct CMYKColor final
	{
	public: // types
		///	この型の各チャネルの値の表現のために内部で使用されている型。
		typedef Proportion<Tp> ChannelType;
	private:
		ChannelType _c;
		ChannelType _m;
		ChannelType _y;
		ChannelType _k;
	public: // construct
		///	既定の @a CMYKColor を初期化します。
		constexpr CMYKColor() : _c(), _m(), _y(), _k() {}
		///	CMY値を指定して @a CMYKColor を初期化します。
		constexpr CMYKColor(const ChannelType& c, const ChannelType& m, const ChannelType& y, const ChannelType& k) : _c(c), _m(m), _y(y), _k(k) {}
		constexpr CMYKColor(const CMYColor<Tp>& color)
			: _c(color.C() - std::min({color.C(), color.M(), color.Y()}))
			, _m(color.M() - std::min({color.C(), color.M(), color.Y()}))
			, _y(color.Y() - std::min({color.C(), color.M(), color.Y()}))
			, _k(std::min({color.C(), color.M(), color.Y()}))
		{}
		template <class fromT>
		constexpr explicit CMYKColor(const CMYKColor<fromT>& from) : CMYKColor(from.template CastTo<Tp>()) {}
	public: // member
		///	この @a CMYKColor のシアンのコンポーネントを取得します。
		constexpr const ChannelType& C() const { return _c; }
		///	この @a CMYKColor のマゼンタのコンポーネントを取得します。
		constexpr const ChannelType& M() const { return _m; }
		///	この @a CMYKColor のイエローのコンポーネントを取得します。
		constexpr const ChannelType& Y() const { return _y; }
		///	この @a CMYKColor のキープレート(黒色)のコンポーネントを取得します。
		constexpr const ChannelType& K() const { return _k; }
		///	この @a CMYKColor が正規化されているかを取得します。
		constexpr bool IsNormalized() const { return (_c.IsNormalized())&&(_m.IsNormalized())&&(_y.IsNormalized())&&(_k.IsNormalized()); }
		///	この @a CMYKColor が空であるかを取得します。
		constexpr bool IsEmpty() const { return *this == Empty(); }

		constexpr CMYKColor<Tp> operator+(const CMYKColor<Tp>& other) const { return CMYKColor<Tp>(_c + other._c, _m + other._m, _y + other._y, _k + other._k); }
		constexpr CMYKColor<Tp> operator-(const CMYKColor<Tp>& other) const { return CMYKColor<Tp>(_c - other._c, _m - other._m, _y - other._y, _k - other._k); }
		constexpr CMYKColor<Tp> operator*(const CMYKColor<Tp>& other) const { return CMYKColor<Tp>(_c * other._c, _m * other._m, _y * other._y, _k * other._k); }
		constexpr CMYKColor<Tp> operator*(const ChannelType& other) const { return CMYKColor<Tp>(_c * other, _m * other, _y * other, _k * other); }
		constexpr CMYKColor<Tp> operator/(const CMYKColor<Tp>& other) const { return CMYKColor<Tp>(_c / other._c, _m / other._m, _y / other._y, _k / other._k); }
		constexpr CMYKColor<Tp> operator/(const ChannelType& other) const { return CMYKColor<Tp>(_c / other, _m / other, _y / other, _k / other); }
		constexpr CMYKColor<Tp> operator~() const { return CMYKColor<Tp>(ChannelType::Max()-_c, ChannelType::Max()-_m, ChannelType::Max()-_y, ChannelType::Max()-_k); }
		constexpr CMYKColor<Tp> operator|(const CMYKColor<Tp>& other) const { return CMYKColor<Tp>(((other._c < _c)?(_c):(other._c)), ((other._m < _m)?(_m):(other._m)), ((other._y < _y)?(_y):(other._y)), ((other._k < _k)?(_k):(other._k))); }
		constexpr CMYKColor<Tp> operator&(const CMYKColor<Tp>& other) const { return CMYKColor<Tp>(((_c < other._c)?(_c):(other._c)), ((_m < other._m)?(_m):(other._m)), ((_y < other._y)?(_y):(other._y)), ((_k < other._k)?(_k):(other._k))); }
		constexpr CMYKColor<Tp> operator^(const CMYKColor<Tp>& other) const { return (*this | other) & ~(*this & other); }
		constexpr CMYKColor<Tp>& operator+=(const CMYKColor<Tp>& other) { return *this = *this + other; }
		constexpr CMYKColor<Tp>& operator-=(const CMYKColor<Tp>& other) { return *this = *this - other; }
		constexpr CMYKColor<Tp>& operator*=(const CMYKColor<Tp>& other) { return *this = *this * other; }
		constexpr CMYKColor<Tp>& operator*=(const ChannelType& other) { return *this = *this * other; }
		constexpr CMYKColor<Tp>& operator/=(const CMYKColor<Tp>& other) { return *this = *this / other; }
		constexpr CMYKColor<Tp>& operator/=(const ChannelType& other) { return *this = *this / other; }
		constexpr CMYKColor<Tp>& operator|=(const CMYKColor<Tp>& other) { return *this = *this | other; }
		constexpr CMYKColor<Tp>& operator&=(const CMYKColor<Tp>& other) { return *this = *this & other; }
		constexpr CMYKColor<Tp>& operator^=(const CMYKColor<Tp>& other) { return *this = *this ^ other; }

		///	正規化した @a CMYKColor を取得します。
		constexpr CMYKColor<Tp> Normalize() const { return CMYKColor<Tp>(_c.Normalize(), _m.Normalize(), _y.Normalize(), _k.Normalize()); }

		template <class castT>
		constexpr CMYKColor<castT> CastTo() const { return CMYKColor<castT>(_c.template CastTo<castT>(), _m.template CastTo<castT>(), _y.template CastTo<castT>(), _k.template CastTo<castT>()); }
		constexpr explicit operator CMYColor<Tp>() const { return CMYColor<Tp>(_k + _c, _k + _m, _k + _y); }

		///	指定されたオブジェクトがこのオブジェクトと等価であることをテストします。
		constexpr bool Equals(const CMYKColor<Tp>& other) const { return (_c == other._c)&&(_m == other._m)&&(_y == other._y); }
		constexpr bool operator==(const CMYKColor<Tp>& other) const { return Equals(other); }
		constexpr bool operator!=(const CMYKColor<Tp>& other) const { return !Equals(other); }

		constexpr static CMYKColor<Tp> Empty() { return CMYKColor<Tp>(); }
	};

	typedef CMYKColor<uint8_t> CMYKI8_t;
	typedef CMYKColor<uint16_t> CMYKI16_t;
	typedef CMYKColor<float> CMYKF32_t;
	typedef CMYKColor<double> CMYKF64_t;
}
#endif // __stationaryorbit_graphics_core_cmykcolor__
