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
#include <cstdint>
#include "stationaryorbit/core.numeral.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	///	CIE1931 XYZ色空間によって表される色。
	template <class Tp = float>
	struct XYZColor final
	{
	public: // types
		///	この型の各チャネルの値の表現のために内部で使用されている型。
		typedef Proportion<Tp> ChannelType;
	private: // contains
		ChannelType _x;
		ChannelType _y;
		ChannelType _z;
	public: // construct
		constexpr XYZColor() : _x(), _y(), _z() {}
		constexpr XYZColor(const ChannelType& x, const ChannelType& y, const ChannelType& z) : _x(x), _y(y), _z(z) {}
	public: // member
		///	この @a XYZColor のXコンポーネントを取得します。
		constexpr const ChannelType& X() const { return _x; }
		///	この @a XYZColor のYコンポーネントを取得します。
		constexpr const ChannelType& Y() const { return _y; }
		///	この @a XYZColor のZコンポーネントを取得します。
		constexpr const ChannelType& Z() const { return _z; }
		///	この @a XYZColor が正規化されているかを取得します。
		constexpr bool IsNormalized() const { return (_x.IsNormalized())&&(_y.IsNormalized())&&(_z.IsNormalized()); }
		///	この @a XYZColor が空であるかを取得します。
		constexpr bool IsEmpty() const { return *this == Empty(); }

		constexpr XYZColor<Tp> operator+(const XYZColor<Tp>& other) const { return XYZColor<Tp>(_x + other._x, _y + other._y, _z + other._z); }
		constexpr XYZColor<Tp> operator-(const XYZColor<Tp>& other) const { return XYZColor<Tp>(_x - other._x, _y - other._y, _z - other._z); }
		constexpr XYZColor<Tp> operator*(const XYZColor<Tp>& other) const { return XYZColor<Tp>(_x * other._x, _y * other._y, _z * other._z); }
		constexpr XYZColor<Tp> operator*(const ChannelType& other) const { return XYZColor<Tp>(_x * other, _y * other, _z * other); }
		constexpr XYZColor<Tp> operator/(const XYZColor<Tp>& other) const { return XYZColor<Tp>(_x / other._x, _y / other._y, _z / other._z); }
		constexpr XYZColor<Tp> operator/(const ChannelType& other) const { return XYZColor<Tp>(_x / other, _y / other, _z / other); }
		constexpr XYZColor<Tp> operator~() const { return XYZColor<Tp>(ChannelType::Max()-_x, ChannelType::Max()-_y, ChannelType::Max()-_z); }
		constexpr XYZColor<Tp> operator|(const XYZColor<Tp>& other) const { return XYZColor<Tp>(((other._x < _x)?(_x):(other._x)), ((other._y < _y)?(_y):(other._y)), ((other._z < _z)?(_z):(other._z))); }
		constexpr XYZColor<Tp> operator&(const XYZColor<Tp>& other) const { return XYZColor<Tp>(((_x < other._x)?(_x):(other._x)), ((_y < other._y)?(_y):(other._y)), ((_z < other._z)?(_z):(other._z))); }
		constexpr XYZColor<Tp> operator^(const XYZColor<Tp>& other) const { return (*this | other) & ~(*this & other); }
		constexpr XYZColor<Tp>& operator+=(const XYZColor<Tp>& other) { return *this = *this + other; }
		constexpr XYZColor<Tp>& operator-=(const XYZColor<Tp>& other) { return *this = *this - other; }
		constexpr XYZColor<Tp>& operator*=(const XYZColor<Tp>& other) { return *this = *this * other; }
		constexpr XYZColor<Tp>& operator*=(const ChannelType& other) { return *this = *this * other; }
		constexpr XYZColor<Tp>& operator/=(const XYZColor<Tp>& other) { return *this = *this / other; }
		constexpr XYZColor<Tp>& operator/=(const ChannelType& other) { return *this = *this / other; }
		constexpr XYZColor<Tp>& operator|=(const XYZColor<Tp>& other) { return *this = *this | other; }
		constexpr XYZColor<Tp>& operator&=(const XYZColor<Tp>& other) { return *this = *this & other; }
		constexpr XYZColor<Tp>& operator^=(const XYZColor<Tp>& other) { return *this = *this ^ other; }

		///	正規化した @a XYZColor を取得します。
		constexpr XYZColor<Tp> Normalize() const { return XYZColor<Tp>(_x.Normalize(), _y.Normalize(), _z.Normalize()); }

		template <class castT>
		constexpr XYZColor<castT> CastTo() const { return XYZColor<castT>(_x.template CastTo<castT>(), _y.template CastTo<castT>(), _z.template CastTo<castT>()); }

		///	指定されたオブジェクトがこのオブジェクトと等価であることをテストします。
		constexpr bool Equals(const XYZColor<Tp>& other) const { return (_x == other._x)&&(_y == other._y)&&(_z == other._z); }
		constexpr bool operator==(const XYZColor<Tp>& other) const { return Equals(other); }
		constexpr bool operator!=(const XYZColor<Tp>& other) const { return !Equals(other); }

		constexpr static XYZColor<Tp> Empty() { return XYZColor<Tp>(); }
	};

	///	不透明度の要素を持つ @a XYZColor 。
	template <class Tp = float>
	struct AXYZColor final
	{
	public: // types
		///	この型の各チャネルの値の表現のために内部で使用されている型。
		typedef Proportion<Tp> ChannelType;
	private: // contains
		ChannelType _alpha;
		XYZColor<Tp> _color;
	public: // construct
		constexpr AXYZColor() :_color(), _alpha() {}
		constexpr explicit AXYZColor(const XYZColor<Tp>& color) :_color(color), _alpha(ChannelType::Max()) {}
		constexpr AXYZColor(const ChannelType& x, const ChannelType& y, const ChannelType& z) : _color(x, y, z), _alpha(ChannelType::Max()) {}
		constexpr AXYZColor(const XYZColor<Tp>& color, const ChannelType& alpha) :_color(color), _alpha(alpha) {}
		constexpr AXYZColor(const ChannelType& x, const ChannelType& y, const ChannelType& z, const ChannelType& alpha) : _color(x, y, z), _alpha(alpha) {}
		template <class fromT>
		constexpr explicit AXYZColor(const AXYZColor<fromT>& from) : AXYZColor(from.template CastTo<Tp>()) {}
	public: // member
		constexpr const XYZColor<Tp>& Color() const { return _color; }
		///	この @a AXYZColor の不透明度を取得します。
		constexpr const ChannelType& Alpha() const { return _alpha; }
		///	この @a AXYZColor のXコンポーネントを取得します。
		constexpr const ChannelType& X() const { return _color.X(); }
		///	この @a AXYZColor のYコンポーネントを取得します。
		constexpr const ChannelType& Y() const { return _color.Y(); }
		///	この @a AXYZColor のZコンポーネントを取得します。
		constexpr const ChannelType& Z() const { return _color.Z(); }
		///	この @a AXYZColor が正規化されているかを取得します。
		constexpr bool IsNormalized() const { return (_color.IsNormalized())&&(_alpha.IsNormalized()); }
		///	この @a AXYZColor が空であるかを取得します。
		constexpr bool IsEmpty() const { return *this == Empty(); }

		constexpr AXYZColor<Tp> operator+(const AXYZColor<Tp>& other) const { return AXYZColor<Tp>(_color + (other._color * other._alpha), _alpha); }
		constexpr AXYZColor<Tp> operator+(const XYZColor<Tp>& other) const { return AXYZColor<Tp>(_color + other, _alpha); }
		constexpr AXYZColor<Tp> operator-(const AXYZColor<Tp>& other) const { return AXYZColor<Tp>(_color - (other._color * other._alpha), _alpha); }
		constexpr AXYZColor<Tp> operator-(const XYZColor<Tp>& other) const { return AXYZColor<Tp>(_color - other, _alpha); }
		constexpr AXYZColor<Tp> operator*(const AXYZColor<Tp>& other) const { return AXYZColor<Tp>(_color * (other._color * other._alpha), _alpha); }
		constexpr AXYZColor<Tp> operator*(const XYZColor<Tp>& other) const { return AXYZColor<Tp>(_color * other, _alpha); }
		constexpr AXYZColor<Tp> operator*(const ChannelType& other) const { return AXYZColor<Tp>(_color, _alpha * other); }
		constexpr AXYZColor<Tp> operator/(const AXYZColor<Tp>& other) const { return AXYZColor<Tp>(_color / (other._color * other._alpha), _alpha); }
		constexpr AXYZColor<Tp> operator/(const XYZColor<Tp>& other) const { return AXYZColor<Tp>(_color / other, _alpha); }
		constexpr AXYZColor<Tp> operator/(const ChannelType& other) const { return AXYZColor<Tp>(_color, _alpha / other); }
		constexpr AXYZColor<Tp> operator~() const { return AXYZColor<Tp>(~_color, _alpha); }
		constexpr AXYZColor<Tp> operator|(const AXYZColor<Tp>& other) const { return AXYZColor<Tp>(_color | (other._color * other._alpha), _alpha); }
		constexpr AXYZColor<Tp> operator|(const XYZColor<Tp>& other) const { return AXYZColor<Tp>(_color | other, _alpha); }
		constexpr AXYZColor<Tp> operator&(const AXYZColor<Tp>& other) const { return AXYZColor<Tp>(_color & (other._color * other._alpha), _alpha); }
		constexpr AXYZColor<Tp> operator&(const XYZColor<Tp>& other) const { return AXYZColor<Tp>(_color & other, _alpha); }
		constexpr AXYZColor<Tp> operator^(const AXYZColor<Tp>& other) const { return AXYZColor<Tp>(_color ^ (other._color * other._alpha), _alpha); }
		constexpr AXYZColor<Tp> operator^(const XYZColor<Tp>& other) const { return AXYZColor<Tp>(_color ^ other, _alpha); }
		constexpr AXYZColor<Tp>& operator+=(const AXYZColor<Tp>& other) { return *this = *this + other; }
		constexpr AXYZColor<Tp>& operator+=(const XYZColor<Tp>& other) { return *this = *this + other; }
		constexpr AXYZColor<Tp>& operator-=(const AXYZColor<Tp>& other) { return *this = *this - other; }
		constexpr AXYZColor<Tp>& operator-=(const XYZColor<Tp>& other) { return *this = *this - other; }
		constexpr AXYZColor<Tp>& operator*=(const AXYZColor<Tp>& other) { return *this = *this * other; }
		constexpr AXYZColor<Tp>& operator*=(const XYZColor<Tp>& other) { return *this = *this * other; }
		constexpr AXYZColor<Tp>& operator*=(const ChannelType& other) { return *this = *this * other; }
		constexpr AXYZColor<Tp>& operator/=(const AXYZColor<Tp>& other) { return *this = *this / other; }
		constexpr AXYZColor<Tp>& operator/=(const XYZColor<Tp>& other) { return *this = *this / other; }
		constexpr AXYZColor<Tp>& operator/=(const ChannelType& other) { return *this = *this / other; }
		constexpr AXYZColor<Tp>& operator|=(const AXYZColor<Tp>& other) { return *this = *this | other; }
		constexpr AXYZColor<Tp>& operator|=(const XYZColor<Tp>& other) { return *this = *this | other; }
		constexpr AXYZColor<Tp>& operator&=(const AXYZColor<Tp>& other) { return *this = *this & other; }
		constexpr AXYZColor<Tp>& operator&=(const XYZColor<Tp>& other) { return *this = *this & other; }
		constexpr AXYZColor<Tp>& operator^=(const AXYZColor<Tp>& other) { return *this = *this ^ other; }
		constexpr AXYZColor<Tp>& operator^=(const XYZColor<Tp>& other) { return *this = *this ^ other; }

		///	正規化した @a AXYZColor を取得します。
		constexpr AXYZColor<Tp> Normalize() const { return AXYZColor<Tp>(_color.Normalize(), _alpha.Normalize()); }

		template <class castT>
		constexpr AXYZColor<castT> CastTo() const { return AXYZColor<castT>(_color.template CastTo<castT>(), _alpha.template CastTo<castT>()); }

		///	指定されたオブジェクトがこのオブジェクトと等価であることをテストします。
		constexpr bool Equals(const AXYZColor<Tp>& other) const { return (_color == other._color)&&(_alpha == other._alpha); }
		constexpr bool operator==(const AXYZColor<Tp>& other) const { return Equals(other); }
		constexpr bool operator!=(const AXYZColor<Tp>& other) const { return !Equals(other); }

		constexpr static AXYZColor<Tp> Empty() { return AXYZColor<Tp>(); }
	};
}
#endif // __stationaryorbit_graphics_core_xyzcolor__