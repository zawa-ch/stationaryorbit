#ifndef __stationaryorbit_graphics_core_graycolor__
#define __stationaryorbit_graphics_core_graycolor__
namespace zawa_ch::StationaryOrbit::Graphics
{
	struct GrayColor final
	{
	private:
		float _l;
	public:
		///	既定の @a GrayColor を初期化します。
		constexpr GrayColor() : _l() {}
		///	輝度を指定して @a GrayColor を初期化します。
		constexpr explicit GrayColor(const float& luminance) : _l(luminance) {}
	public:
		///	この @a GrayColor の輝度コンポーネントを取得します。
		constexpr float Luminance() const { return _l; }
		///	この @a GrayColor が正規化されているかを取得します。
		constexpr bool IsNormalized() const { return (0 <= _l)&&(_l <= 1); }
		///	この @a GrayColor が空であるかを取得します。
		constexpr bool IsEmpty() const { return *this == Empty(); }

		constexpr GrayColor operator+(const GrayColor& other) const { return GrayColor(_l + other._l); }
		constexpr GrayColor operator-(const GrayColor& other) const { return GrayColor(_l - other._l); }
		constexpr GrayColor operator*(const GrayColor& other) const { return GrayColor(_l * other._l); }
		constexpr GrayColor operator*(const float& other) const { return GrayColor(_l * other); }
		constexpr GrayColor operator/(const GrayColor& other) const { return GrayColor(_l / other._l); }
		constexpr GrayColor operator/(const float& other) const { return GrayColor(_l / other); }
		constexpr GrayColor operator~() const { return GrayColor(1-_l); }
		constexpr GrayColor operator|(const GrayColor& other) const { return GrayColor(((other._l < _l)?(_l):(other._l))); }
		constexpr GrayColor operator&(const GrayColor& other) const { return GrayColor(((_l < other._l)?(_l):(other._l))); }
		constexpr GrayColor operator^(const GrayColor& other) const { return (*this | other) & ~(*this & other); }
		constexpr GrayColor& operator+=(const GrayColor& other) { return *this = *this + other; }
		constexpr GrayColor& operator-=(const GrayColor& other) { return *this = *this - other; }
		constexpr GrayColor& operator*=(const GrayColor& other) { return *this = *this * other; }
		constexpr GrayColor& operator*=(const float& other) { return *this = *this * other; }
		constexpr GrayColor& operator/=(const GrayColor& other) { return *this = *this / other; }
		constexpr GrayColor& operator/=(const float& other) { return *this = *this / other; }
		constexpr GrayColor& operator|=(const GrayColor& other) { return *this = *this | other; }
		constexpr GrayColor& operator&=(const GrayColor& other) { return *this = *this & other; }
		constexpr GrayColor& operator^=(const GrayColor& other) { return *this = *this ^ other; }

		///	正規化した @a GrayColor を取得します。
		constexpr GrayColor Normalize() const { return GrayColor(((0 <= _l)?((_l <= 1)?(_l):(1)):(0))); }

		///	指定されたオブジェクトがこのオブジェクトと等価であることをテストします。
		constexpr bool Equals(const GrayColor& other) const { return (_l == other._l); }
		constexpr bool operator==(const GrayColor& other) const { return Equals(other); }
		constexpr bool operator!=(const GrayColor& other) const { return !Equals(other); }

		constexpr static GrayColor Empty() { return GrayColor(); }
	};
}
#endif // __stationaryorbit_graphics_core_graycolor__