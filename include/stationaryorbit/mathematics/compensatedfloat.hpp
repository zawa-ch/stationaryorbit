//	stationaryorbit/mathematics/compensatedfloat
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
#ifndef __stationaryorbit_mathematics_compensatedfloat__
#define __stationaryorbit_mathematics_compensatedfloat__
#include "stationaryorbit/core.traits.hpp"
namespace zawa_ch::StationaryOrbit::Mathematics
{
	/// 計算時に誤差の補償が行われる数値を表します。
	///	@note
	///	正確な値を示す( @a std::numeric_limits<T>::is_exact が @a true である)型に対してはこの型を実体化することはできません。
	template<class T>
	struct CompensatedFloat final
	{
		static_assert(Traits::IsNumericalType<T>, "テンプレート引数 T は数値型である必要があります。");
		static_assert(!std::numeric_limits<T>::is_exact, "テンプレート引数 T が正確な値を示す型であってはなりません。");
	public:
		typedef T ValueType;
	private:
		///	このオブジェクトの値
		T value;
		///	計算時に発生した誤差
		T c;
	public:
		///	オブジェクトを既定の値で初期化します。
		CompensatedFloat() = default;
		///	指定された値でオブジェクトを初期化します。
		explicit constexpr CompensatedFloat(const T& value) : value(value), c() {}
	private:
		///	値からこのオブジェクトを直接構築します。
		constexpr CompensatedFloat(const T& value, const T& c) : value(value), c(c) {}
	public:
		///	このオブジェクトが指す値を取得します。
		constexpr ValueType Value() const noexcept { return value; }
		///	このオブジェクトの計算時に用いられる誤差の値を取得します。
		constexpr ValueType Error() const noexcept { return c; }

		[[nodiscard]] constexpr CompensatedFloat<T> operator+() const noexcept { return CompensatedFloat<T>(*this); }
		[[nodiscard]] constexpr CompensatedFloat<T> operator-() const noexcept { return CompensatedFloat<T>(-value, -c); }
		[[nodiscard]] constexpr CompensatedFloat<T> operator+(const T& other) const noexcept
		{
			ValueType comp = other - c;
			ValueType sum = value + comp;
			return CompensatedFloat<T>(sum, (sum - value) - comp);
		}
		[[nodiscard]] constexpr CompensatedFloat<T> operator-(const T& other) const noexcept
		{
			ValueType comp = other + c;
			ValueType sum = value - comp;
			return CompensatedFloat<T>(sum, (sum - value) + comp);
		}
		[[nodiscard]] constexpr CompensatedFloat<T> operator*(const T& other) const noexcept { return CompensatedFloat<T>(value * other, c * other); }
		[[nodiscard]] constexpr CompensatedFloat<T> operator/(const T& other) const noexcept { return CompensatedFloat<T>(value / other, c / other); }
		constexpr CompensatedFloat<T>& operator+=(const T& other) noexcept { return *this = *this + other; }
		constexpr CompensatedFloat<T>& operator-=(const T& other) noexcept { return *this = *this - other; }
		constexpr CompensatedFloat<T>& operator*=(const T& other) noexcept { return *this = *this * other; }
		constexpr CompensatedFloat<T>& operator/=(const T& other) noexcept { return *this = *this / other; }

		[[nodiscard]] constexpr bool Equals(const CompensatedFloat<T>& other) const noexcept { return T(*this) == T(other); }
		[[nodiscard]] constexpr bool operator==(const CompensatedFloat<T>& other) const noexcept { return Equals(other); }
		[[nodiscard]] constexpr bool operator!=(const CompensatedFloat<T>& other) const noexcept { return !Equals(other); }

		[[nodiscard]] constexpr bool operator<(const CompensatedFloat<T>& other) const noexcept { return T(*this) < T(other); }
		[[nodiscard]] constexpr bool operator>(const CompensatedFloat<T>& other) const noexcept { return T(*this) > T(other); }
		[[nodiscard]] constexpr bool operator<=(const CompensatedFloat<T>& other) const noexcept { return T(*this) <= T(other); }
		[[nodiscard]] constexpr bool operator>=(const CompensatedFloat<T>& other) const noexcept { return T(*this) >= T(other); }

		explicit constexpr operator ValueType() const { return value - c; }
	};

	/// 計算時に誤差の補償が行われる @a float を表します。
	typedef CompensatedFloat<float> CompensatedSingle;
	/// 計算時に誤差の補償が行われる @a double を表します。
	typedef CompensatedFloat<double> CompensatedDouble;
}
#endif // __stationaryorbit_mathematics_compensatedfloat__