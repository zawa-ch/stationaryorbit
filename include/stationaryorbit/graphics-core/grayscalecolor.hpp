#ifndef __stationaryorbit_graphics_core_grayscalecolor__
#define __stationaryorbit_graphics_core_grayscalecolor__
#include "stationaryorbit/core.numeral.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	///
	template <class Tp = float>
	struct GrayScaleColor final
	{
	public: // types
		///	この型の各チャネルの値の表現のために内部で使用されている型。
		typedef Proportion<Tp> ChannelType;
	private:
		ChannelType _l;
	public:
		///	既定の @a GrayScaleColor を初期化します。
		constexpr GrayScaleColor() : _l() {}
		///	輝度を指定して @a GrayScaleColor を初期化します。
		constexpr explicit GrayScaleColor(const ChannelType& luminance) : _l(luminance) {}
		template <class fromT>
		constexpr explicit GrayScaleColor(const GrayScaleColor<fromT>& from) : GrayScaleColor(from.template CastTo<Tp>()) {}
	public:
		///	この @a GrayScaleColor の輝度コンポーネントを取得します。
		constexpr ChannelType Luminance() const { return _l; }
		///	この @a GrayScaleColor が正規化されているかを取得します。
		constexpr bool IsNormalized() const { return _l.IsNormalized(); }
		///	この @a GrayScaleColor が空であるかを取得します。
		constexpr bool IsEmpty() const { return *this == Empty(); }

		constexpr GrayScaleColor operator+(const GrayScaleColor& other) const { return GrayScaleColor(_l + other._l); }
		constexpr GrayScaleColor operator-(const GrayScaleColor& other) const { return GrayScaleColor(_l - other._l); }
		constexpr GrayScaleColor operator*(const GrayScaleColor& other) const { return GrayScaleColor(_l * other._l); }
		constexpr GrayScaleColor operator*(const ChannelType& other) const { return GrayScaleColor(_l * other); }
		constexpr GrayScaleColor operator/(const GrayScaleColor& other) const { return GrayScaleColor(_l / other._l); }
		constexpr GrayScaleColor operator/(const ChannelType& other) const { return GrayScaleColor(_l / other); }
		constexpr GrayScaleColor operator~() const { return GrayScaleColor(1-_l); }
		constexpr GrayScaleColor operator|(const GrayScaleColor& other) const { return GrayScaleColor(((other._l < _l)?(_l):(other._l))); }
		constexpr GrayScaleColor operator&(const GrayScaleColor& other) const { return GrayScaleColor(((_l < other._l)?(_l):(other._l))); }
		constexpr GrayScaleColor operator^(const GrayScaleColor& other) const { return (*this | other) & ~(*this & other); }
		constexpr GrayScaleColor& operator+=(const GrayScaleColor& other) { return *this = *this + other; }
		constexpr GrayScaleColor& operator-=(const GrayScaleColor& other) { return *this = *this - other; }
		constexpr GrayScaleColor& operator*=(const GrayScaleColor& other) { return *this = *this * other; }
		constexpr GrayScaleColor& operator*=(const ChannelType& other) { return *this = *this * other; }
		constexpr GrayScaleColor& operator/=(const GrayScaleColor& other) { return *this = *this / other; }
		constexpr GrayScaleColor& operator/=(const ChannelType& other) { return *this = *this / other; }
		constexpr GrayScaleColor& operator|=(const GrayScaleColor& other) { return *this = *this | other; }
		constexpr GrayScaleColor& operator&=(const GrayScaleColor& other) { return *this = *this & other; }
		constexpr GrayScaleColor& operator^=(const GrayScaleColor& other) { return *this = *this ^ other; }

		///	正規化した @a GrayScaleColor を取得します。
		constexpr GrayScaleColor Normalize() const { return GrayScaleColor(_l.Normalize()); }

		template <class castT>
		constexpr GrayScaleColor<castT> CastTo() const { return GrayScaleColor<castT>(_l.template CastTo<castT>()); }

		///	指定されたオブジェクトがこのオブジェクトと等価であることをテストします。
		constexpr bool Equals(const GrayScaleColor& other) const { return (_l == other._l); }
		constexpr bool operator==(const GrayScaleColor& other) const { return Equals(other); }
		constexpr bool operator!=(const GrayScaleColor& other) const { return !Equals(other); }

		constexpr static GrayScaleColor Empty() { return GrayScaleColor(); }
	};

	typedef GrayScaleColor<uint8_t> GrayScaleI8_t;
	typedef GrayScaleColor<uint16_t> GrayScaleI16_t;
	typedef GrayScaleColor<float> GrayScaleF32_t;
	typedef GrayScaleColor<double> GrayScaleF64_t;
}
#endif // __stationaryorbit_graphics_core_grayscalecolor__
