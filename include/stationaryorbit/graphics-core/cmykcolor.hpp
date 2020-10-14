//	stationaryorbit/graphics-core/cmykcolor
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
#ifndef __stationaryorbit_graphics_core_cmykcolor__
#define __stationaryorbit_graphics_core_cmykcolor__
#include <algorithm>
#include <cstdint>
#include "stationaryorbit/core.numeral.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
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
