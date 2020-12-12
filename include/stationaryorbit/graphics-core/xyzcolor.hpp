//	stationaryorbit/graphics-core/xyzcolor
//	Copyright 2020 zawa-ch.
//	GPLv3 (or later) license
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//	See the GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program.
//	If not, see <http://www.gnu.org/licenses/>.
//
#ifndef __stationaryorbit_graphics_core_xyzcolor__
#define __stationaryorbit_graphics_core_xyzcolor__
#include "channelvalue.hpp"
#include "translucentcolor.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	///	CIE1931 XYZ色空間によって表される色。
	template <class Tp>
	struct XYZColor final
	{
	public: // types
		///	この型の各チャネルの値の表現のために内部で使用されている型。
		typedef ChannelValue<Tp> ValueType;
	private: // contains
		ValueType _x;
		ValueType _y;
		ValueType _z;
	public: // construct
		constexpr XYZColor() = default;
		constexpr XYZColor(const ValueType& x, const ValueType& y, const ValueType& z) : _x(x), _y(y), _z(z) {}
		template <class fromT>
		constexpr explicit XYZColor(const XYZColor<fromT>& from) : XYZColor(ValueType(from._x), ValueType(from._y), ValueType(from._z)) {}
		constexpr XYZColor(const ZeroValue_t&) : XYZColor(Zero, Zero, Zero) {}
	public: // member
		///	この @a XYZColor のXコンポーネントを取得します。
		constexpr const ValueType& X() const { return _x; }
		///	この @a XYZColor のYコンポーネントを取得します。
		constexpr const ValueType& Y() const { return _y; }
		///	この @a XYZColor のZコンポーネントを取得します。
		constexpr const ValueType& Z() const { return _z; }
		///	この @a XYZColor が正規化されているかを取得します。
		constexpr bool IsNormalized() const { return (_x.IsNormalized())&&(_y.IsNormalized())&&(_z.IsNormalized()); }
		///	正規化した @a XYZColor を取得します。
		constexpr XYZColor<Tp> Normalize() const { return XYZColor<Tp>(_x.Normalize(), _y.Normalize(), _z.Normalize()); }

		constexpr XYZColor<Tp> operator+() const { return XYZColor<Tp>(_x.Promote(), _y.Promote(), _z.Promote()); }
		constexpr XYZColor<Tp> operator-() const { return XYZColor<Tp>(_x.Invert(), _y.Invert(), _z.Invert()); }
		constexpr XYZColor<Tp> operator+(const XYZColor<Tp>& other) const { return XYZColor<Tp>(_x + other._x, _y + other._y, _z + other._z); }
		constexpr XYZColor<Tp> operator-(const XYZColor<Tp>& other) const { return XYZColor<Tp>(_x - other._x, _y - other._y, _z - other._z); }
		constexpr XYZColor<Tp> operator*(const XYZColor<Tp>& other) const { return XYZColor<Tp>(_x * other._x, _y * other._y, _z * other._z); }
		constexpr XYZColor<Tp> operator*(const ValueType& other) const { return XYZColor<Tp>(_x * other, _y * other, _z * other); }
		constexpr XYZColor<Tp> operator/(const XYZColor<Tp>& other) const { return XYZColor<Tp>(_x / other._x, _y / other._y, _z / other._z); }
		constexpr XYZColor<Tp> operator/(const ValueType& other) const { return XYZColor<Tp>(_x / other, _y / other, _z / other); }
		constexpr XYZColor<Tp> operator~() const { return XYZColor<Tp>(ValueType::Max()-_x, ValueType::Max()-_y, ValueType::Max()-_z); }
		constexpr XYZColor<Tp> operator|(const XYZColor<Tp>& other) const { return XYZColor<Tp>(((other._x < _x)?(_x):(other._x)), ((other._y < _y)?(_y):(other._y)), ((other._z < _z)?(_z):(other._z))); }
		constexpr XYZColor<Tp> operator&(const XYZColor<Tp>& other) const { return XYZColor<Tp>(((_x < other._x)?(_x):(other._x)), ((_y < other._y)?(_y):(other._y)), ((_z < other._z)?(_z):(other._z))); }
		constexpr XYZColor<Tp> operator^(const XYZColor<Tp>& other) const { return (*this | other) & ~(*this & other); }
		constexpr XYZColor<Tp>& operator+=(const XYZColor<Tp>& other) { return *this = *this + other; }
		constexpr XYZColor<Tp>& operator-=(const XYZColor<Tp>& other) { return *this = *this - other; }
		constexpr XYZColor<Tp>& operator*=(const XYZColor<Tp>& other) { return *this = *this * other; }
		constexpr XYZColor<Tp>& operator*=(const ValueType& other) { return *this = *this * other; }
		constexpr XYZColor<Tp>& operator/=(const XYZColor<Tp>& other) { return *this = *this / other; }
		constexpr XYZColor<Tp>& operator/=(const ValueType& other) { return *this = *this / other; }
		constexpr XYZColor<Tp>& operator|=(const XYZColor<Tp>& other) { return *this = *this | other; }
		constexpr XYZColor<Tp>& operator&=(const XYZColor<Tp>& other) { return *this = *this & other; }
		constexpr XYZColor<Tp>& operator^=(const XYZColor<Tp>& other) { return *this = *this ^ other; }

		constexpr bool Equals(const XYZColor<Tp>& other) const { return (_x == other._x)&&(_y == other._y)&&(_z == other._z); }
		constexpr bool operator==(const XYZColor<Tp>& other) const { return Equals(other); }
		constexpr bool operator!=(const XYZColor<Tp>& other) const { return !Equals(other); }

		constexpr static XYZColor<Tp> Empty() { return XYZColor<Tp>(); }
	};

	extern template struct XYZColor<Proportion8_t>;
	extern template struct XYZColor<Proportion16_t>;
	extern template struct XYZColor<Proportion32_t>;
	extern template struct XYZColor<Proportion64_t>;
	extern template struct XYZColor<FixedPoint16q15_t>;
	extern template struct XYZColor<FixedPoint32q31_t>;
	extern template struct XYZColor<FixedPoint64q63_t>;
	extern template struct XYZColor<float>;
	extern template struct XYZColor<double>;
	extern template struct TranslucentColor<XYZColor<Proportion8_t>>;
	extern template struct TranslucentColor<XYZColor<Proportion16_t>>;
	extern template struct TranslucentColor<XYZColor<Proportion32_t>>;
	extern template struct TranslucentColor<XYZColor<Proportion64_t>>;
	extern template struct TranslucentColor<XYZColor<FixedPoint16q15_t>>;
	extern template struct TranslucentColor<XYZColor<FixedPoint32q31_t>>;
	extern template struct TranslucentColor<XYZColor<FixedPoint64q63_t>>;
	extern template struct TranslucentColor<XYZColor<float>>;
	extern template struct TranslucentColor<XYZColor<double>>;

	typedef XYZColor<Proportion8_t> XYZ8_t;
	typedef XYZColor<Proportion16_t> XYZ16_t;
	typedef XYZColor<Proportion32_t> XYZ32_t;
	typedef XYZColor<Proportion64_t> XYZ64_t;
	typedef XYZColor<FixedPoint16q15_t> XYZI16_t;
	typedef XYZColor<FixedPoint32q31_t> XYZI32_t;
	typedef XYZColor<FixedPoint64q63_t> XYZI64_t;
	typedef XYZColor<float> XYZF32_t;
	typedef XYZColor<double> XYZF64_t;
	typedef TranslucentColor<XYZColor<Proportion8_t>> AXYZ8_t;
	typedef TranslucentColor<XYZColor<Proportion16_t>> AXYZ16_t;
	typedef TranslucentColor<XYZColor<Proportion32_t>> AXYZ32_t;
	typedef TranslucentColor<XYZColor<Proportion64_t>> AXYZ64_t;
	typedef TranslucentColor<XYZColor<FixedPoint16q15_t>> AXYZI16_t;
	typedef TranslucentColor<XYZColor<FixedPoint32q31_t>> AXYZI32_t;
	typedef TranslucentColor<XYZColor<FixedPoint64q63_t>> AXYZI64_t;
	typedef TranslucentColor<XYZColor<float>> AXYZF32_t;
	typedef TranslucentColor<XYZColor<double>> AXYZF64_t;
}
#endif // __stationaryorbit_graphics_core_xyzcolor__