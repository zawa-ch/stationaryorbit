#ifndef __stationaryorbit_graphics_core_yuvcolor__
#define __stationaryorbit_graphics_core_yuvcolor__
namespace zawa_ch::StationaryOrbit::Graphics
{
	///	輝度と二つの色差によって表される色。
	struct YUVColor final
	{
	private: // contains
		float _y;
		float _u;
		float _v;
	public: // constructor
		///	既定の @a YUVColor を初期化します。
		constexpr YUVColor() : _y(), _u(), _v() {}
		///	YUV値を指定して @a YUVColor を初期化します。
		constexpr YUVColor(const float& y, const float& cr, const float& cb) : _y(y), _u(cr), _v(cb) {}
	public: // member
		///	この @a YUVColor の輝度コンポーネントを取得します。
		constexpr const float& Y() const { return _y; }
		///	この @a YUVColor の赤色差コンポーネントを取得します。
		constexpr const float& U() const { return _u; }
		///	この @a YUVColor の青色差コンポーネントを取得します。
		constexpr const float& V() const { return _v; }
		///	この @a YUVColor が正規化されているかを取得します。
		constexpr bool IsNormalized() const { return (0 <= _y)&&(_y <= 1)&&(-0.5 <= _u)&&(_u <= 0.5)&&(-0.5 <= _v)&&(_v <= 0.5); }
		///	この @a YUVColor が空であるかを取得します。
		constexpr bool IsEmpty() const { return *this == Empty(); }

		constexpr YUVColor operator+(const YUVColor& other) const { return YUVColor(_y + other._y, _u + other._u, _v + other._v); }
		constexpr YUVColor operator-(const YUVColor& other) const { return YUVColor(_y - other._y, _u - other._u, _v - other._v); }
		constexpr YUVColor& operator+=(const YUVColor& other) { return *this = *this + other; }
		constexpr YUVColor& operator-=(const YUVColor& other) { return *this = *this - other; }

		///	正規化した @a YUVColor を取得します。
		constexpr YUVColor Normalize() const { return YUVColor(((0 <= _y)?((_y <= 1)?(_y):(1)):(0)), ((-0.5 <= _u)?((_u <= 0.5)?(_u):(0.5)):(-0.5)), ((-0.5 <= _v)?((_v <= 0.5)?(_v):(0.5)):(-0.5))); }

		///	指定されたオブジェクトがこのオブジェクトと等価であることをテストします。
		constexpr bool Equals(const YUVColor& other) const { return (_y == other._y)&&(_u == other._u)&&(_v == other._v); }
		constexpr bool operator==(const YUVColor& other) const { return Equals(other); }
		constexpr bool operator!=(const YUVColor& other) const { return !Equals(other); }

		constexpr static YUVColor Empty() { return YUVColor(); }
	};
}
#endif // __stationaryorbit_graphics_core_yuvcolor__