//	stationaryorbit/core/rectsize
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
#ifndef __stationaryorbit_core_rectsize__
#define __stationaryorbit_core_rectsize__
#include <cmath>
#include "traits.hpp"
#include "zerovalue.hpp"
#include "range.hpp"
namespace zawa_ch::StationaryOrbit
{
	///	幅・高さを持つオブジェクトの大きさを表します。
	template<class T, class = void>
	struct Rect2DSize final
	{
		static_assert(Traits::IsNumericalType<T>, "テンプレート引数型 T は数値型である必要があります。");
	public:
		typedef T ValueType;
	private:
		ValueType _w;
		ValueType _h;
	public:
		constexpr Rect2DSize() = default;
		constexpr Rect2DSize(const ValueType& width, const ValueType& height) : _w(width), _h(height) {}
		template<class fromT, std::enable_if_t<std::is_convertible_v<fromT, T>, int> = 0>
		constexpr Rect2DSize(const Rect2DSize<fromT>& from) : _w(from.Width()), _h(from.Height()) {}
		template<class fromT, std::enable_if_t<std::conjunction_v<std::negation<std::is_convertible<fromT, T>>, std::is_constructible<T, fromT>>, int> = 0>
		constexpr explicit Rect2DSize(const Rect2DSize<fromT>& from) : _w(from.Width()), _h(from.Height()) {}
		constexpr Rect2DSize(const ZeroValue_t&) : _w(Zero), _h(Zero) {}

		///	水平軸の値を取得します。
		[[nodiscard]] constexpr const ValueType& Width() const noexcept { return _w; }
		///	垂直軸の値を取得します。
		[[nodiscard]] constexpr const ValueType& Height() const noexcept { return _h; }

		///	水平軸コンポーネントの値の範囲を示す @a Range を取得します。
		[[nodiscard]] constexpr Range<T> XRange() const noexcept { return Range(T(0), _w); }
		///	垂直軸コンポーネントの値の範囲を示す @a Range を取得します。
		[[nodiscard]] constexpr Range<T> YRange() const noexcept { return Range(T(0), _h); }

		[[nodiscard]] constexpr Rect2DSize<T> operator+(const Rect2DSize<T>& other) const noexcept { return Rect2DSize(_w + other._w, _h + other._h); }
		[[nodiscard]] constexpr Rect2DSize<T> operator-(const Rect2DSize<T>& other) const noexcept { return Rect2DSize(_w - other._w, _h - other._h); }
		[[nodiscard]] constexpr Rect2DSize<T> operator*(const Rect2DSize<T>& other) const noexcept { return Rect2DSize(_w * other._w, _h * other._h); }
		[[nodiscard]] constexpr Rect2DSize<T> operator/(const Rect2DSize<T>& other) const noexcept { return Rect2DSize(_w / other._w, _h / other._h); }
		[[nodiscard]] constexpr Rect2DSize<T> operator*(const ValueType& other) const noexcept { return Rect2DSize(_w * other, _h * other); }
		[[nodiscard]] constexpr Rect2DSize<T> operator/(const ValueType& other) const noexcept { return Rect2DSize(_w / other, _h / other); }
		constexpr Rect2DSize<T>& operator+=(const Rect2DSize<T>& other) { return *this = *this + other; }
		constexpr Rect2DSize<T>& operator-=(const Rect2DSize<T>& other) { return *this = *this - other; }
		constexpr Rect2DSize<T>& operator*=(const Rect2DSize<T>& other) { return *this = *this * other; }
		constexpr Rect2DSize<T>& operator/=(const Rect2DSize<T>& other) { return *this = *this / other; }
		constexpr Rect2DSize<T>& operator*=(const ValueType& other) { return *this = *this * other; }
		constexpr Rect2DSize<T>& operator/=(const ValueType& other) { return *this = *this / other; }

		[[nodiscard]] constexpr bool Equals(const Rect2DSize<T>& value) const noexcept { return (_w == value._w)&&(_h == value._h); }
		[[nodiscard]] constexpr bool operator==(const Rect2DSize<T>& value) const noexcept { return Equals(value); }
		[[nodiscard]] constexpr bool operator!=(const Rect2DSize<T>& value) const noexcept { return !Equals(value); }

		[[nodiscard]] static constexpr Rect2DSize<T> Empty() { return Rect2DSize<T>{}; }
	};
	///	幅・高さを持つオブジェクトの大きさを表します。
	///	@note
	///	こちらは @a std::is_floting_point_v が @a true の場合の特殊化です。
	template<class T>
	struct Rect2DSize<T, std::enable_if_t<std::is_floating_point_v<T> > > final
	{
		static_assert(Traits::IsNumericalType<T>, "テンプレート引数型 T は数値型である必要があります。");
	public:
		typedef T ValueType;
	private:
		ValueType _w;
		ValueType _h;
	public:
		constexpr Rect2DSize() = default;
		constexpr Rect2DSize(const ValueType& width, const ValueType& height) : _w(width), _h(height) {}
		template<class fromT, std::enable_if_t<std::is_convertible_v<fromT, T>, int> = 0>
		constexpr Rect2DSize(const Rect2DSize<fromT>& from) : _w(from.Width()), _h(from.Height()) {}
		template<class fromT, std::enable_if_t<std::conjunction_v<std::negation<std::is_convertible<fromT, T>>, std::is_constructible<T, fromT>>, int> = 0>
		constexpr explicit Rect2DSize(const Rect2DSize<fromT>& from) : _w(from.Width()), _h(from.Height()) {}
		constexpr Rect2DSize(const ZeroValue_t&) : _w(Zero), _h(Zero) {}

		///	水平軸の値を取得します。
		[[nodiscard]] constexpr const ValueType& Width() const noexcept { return _w; }
		///	垂直軸の値を取得します。
		[[nodiscard]] constexpr const ValueType& Height() const noexcept { return _h; }

		///	水平軸コンポーネントの値の範囲を示す @a Range を取得します。
		[[nodiscard]] constexpr Range<T> XRange() const noexcept { return Range(T(0), _w); }
		///	垂直軸コンポーネントの値の範囲を示す @a Range を取得します。
		[[nodiscard]] constexpr Range<T> YRange() const noexcept { return Range(T(0), _h); }

		[[nodiscard]] constexpr Rect2DSize<T> operator+(const Rect2DSize<T>& other) const noexcept { return Rect2DSize(_w + other._w, _h + other._h); }
		[[nodiscard]] constexpr Rect2DSize<T> operator-(const Rect2DSize<T>& other) const noexcept { return Rect2DSize(_w - other._w, _h - other._h); }
		[[nodiscard]] constexpr Rect2DSize<T> operator*(const Rect2DSize<T>& other) const noexcept { return Rect2DSize(_w * other._w, _h * other._h); }
		[[nodiscard]] constexpr Rect2DSize<T> operator/(const Rect2DSize<T>& other) const noexcept { return Rect2DSize(_w / other._w, _h / other._h); }
		[[nodiscard]] constexpr Rect2DSize<T> operator*(const ValueType& other) const noexcept { return Rect2DSize(_w * other, _h * other); }
		[[nodiscard]] constexpr Rect2DSize<T> operator/(const ValueType& other) const noexcept { return Rect2DSize(_w / other, _h / other); }
		constexpr Rect2DSize<T>& operator+=(const Rect2DSize<T>& other) { return *this = *this + other; }
		constexpr Rect2DSize<T>& operator-=(const Rect2DSize<T>& other) { return *this = *this - other; }
		constexpr Rect2DSize<T>& operator*=(const Rect2DSize<T>& other) { return *this = *this * other; }
		constexpr Rect2DSize<T>& operator/=(const Rect2DSize<T>& other) { return *this = *this / other; }
		constexpr Rect2DSize<T>& operator*=(const ValueType& other) { return *this = *this * other; }
		constexpr Rect2DSize<T>& operator/=(const ValueType& other) { return *this = *this / other; }

		[[nodiscard]] constexpr bool Equals(const Rect2DSize<T>& value) const noexcept { return (_w == value._w)&&(_h == value._h); }
		[[nodiscard]] constexpr bool operator==(const Rect2DSize<T>& value) const noexcept { return Equals(value); }
		[[nodiscard]] constexpr bool operator!=(const Rect2DSize<T>& value) const noexcept { return !Equals(value); }

		///	@a Rect2DSize<T> の小数部を抜き出します。
		[[nodiscard]] Rect2DSize<T> Extract() const { return Rect2DSize<T>(_w - trunc(_w), _h - trunc(_h)); }
		///	@a Rect2DSize<T> を切り捨て方向に丸めます。
		template<class intT = T, std::enable_if_t<std::is_constructible_v<intT, T>, int > = 0>
		[[nodiscard]] Rect2DSize<intT> Floor() const { return Rect2DSize<intT>(intT(floor(Width())), intT(floor(Height()))); }
		///	@a Rect2DSize<T> を切り上げ方向に丸めます。
		template<class intT = T, std::enable_if_t<std::is_constructible_v<intT, T>, int > = 0>
		[[nodiscard]] Rect2DSize<intT> Ceiling() const { return Rect2DSize<intT>(intT(ceil(Width())), intT(ceil(Height()))); }
		/// @a Rect2DSize<T> を最も近い整数に丸めます。
		template<class intT = T, std::enable_if_t<std::is_constructible_v<intT, T>, int > = 0>
		[[nodiscard]] Rect2DSize<intT> Round() const { return Rect2DSize<intT>(intT(round(Width())), intT(round(Height()))); }

		[[nodiscard]] static constexpr Rect2DSize<T> Empty() { return Rect2DSize<T>{}; }
	};

	extern template struct Rect2DSize<uint8_t>;
	extern template struct Rect2DSize<uint16_t>;
	extern template struct Rect2DSize<uint32_t>;
	extern template struct Rect2DSize<uint64_t>;
	extern template struct Rect2DSize<int8_t>;
	extern template struct Rect2DSize<int16_t>;
	extern template struct Rect2DSize<int32_t>;
	extern template struct Rect2DSize<int64_t>;
	extern template struct Rect2DSize<float>;
	extern template struct Rect2DSize<double>;
}
#endif // __stationaryorbit_core_rectsize__