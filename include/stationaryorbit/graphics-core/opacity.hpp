//	stationaryorbit/graphics-core/opacity
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
#ifndef __stationaryorbit_graphics_core_opacity__
#define __stationaryorbit_graphics_core_opacity__
#include "channelvalue.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	template<class Tp>
	struct Opacity final
	{
	public:
		typedef ChannelValue<Tp> ValueType;
	private:
		ValueType _value;
	public:
		constexpr Opacity() = default;
		constexpr explicit Opacity(const ValueType& value) : _value(value) {}
		template<class fromT>
		constexpr explicit Opacity(const Opacity<fromT>& from) : _value(ValueType(from.Data())) {}
		constexpr Opacity(const ZeroValue_t&) : _value(Zero) {}

		[[nodiscard]] constexpr const ValueType& Data() const noexcept { return _value; }
		[[nodiscard]] constexpr bool IsNormalized() const noexcept { return _value.IsNormalized(); }
		[[nodiscard]] constexpr Opacity<Tp> Normalize() const noexcept { return Opacity<Tp>(_value.Normalize()); }

		[[nodiscard]] constexpr Opacity<Tp> Add(const Opacity<Tp>& other) const noexcept { return  Opacity<Tp>(_value.Add(other._value)); }
		[[nodiscard]] constexpr Opacity<Tp> Subtract(const Opacity<Tp>& other) const noexcept { return  Opacity<Tp>(_value.Subtract(other._value)); }
		[[nodiscard]] constexpr Opacity<Tp> Multiply(const Opacity<Tp>& other) const noexcept { return  Opacity<Tp>(_value.Multiply(other._value)); }
		[[nodiscard]] constexpr Opacity<Tp> Divide(const Opacity<Tp>& other) const noexcept { return  Opacity<Tp>(_value.Divide(other._value)); }
		[[nodiscard]] constexpr Opacity<Tp> SaturateAdd(const Opacity<Tp>& other) const noexcept { return  Opacity<Tp>(_value.SaturateAdd(other._value)); }
		[[nodiscard]] constexpr Opacity<Tp> SaturateSubtract(const Opacity<Tp>& other) const noexcept { return  Opacity<Tp>(_value.SaturateSubtract(other._value)); }
		[[nodiscard]] constexpr Opacity<Tp> SaturateMultiply(const Opacity<Tp>& other) const noexcept { return  Opacity<Tp>(_value.SaturateMultiply(other._value)); }
		[[nodiscard]] constexpr Opacity<Tp> SaturateDivide(const Opacity<Tp>& other) const noexcept { return  Opacity<Tp>(_value.SaturateDivide(other._value)); }
		[[nodiscard]] constexpr Opacity<Tp> CheckedAdd(const Opacity<Tp>& other) const { return  Opacity<Tp>(_value.CheckedAdd(other._value)); }
		[[nodiscard]] constexpr Opacity<Tp> CheckedSubtract(const Opacity<Tp>& other) const { return  Opacity<Tp>(_value.CheckedSubtract(other._value)); }
		[[nodiscard]] constexpr Opacity<Tp> CheckedMultiply(const Opacity<Tp>& other) const { return  Opacity<Tp>(_value.CheckedMultiply(other._value)); }
		[[nodiscard]] constexpr Opacity<Tp> CheckedDivide(const Opacity<Tp>& other) const { return  Opacity<Tp>(_value.CheckedDivide(other._value)); }
		[[nodiscard]] constexpr Opacity<Tp> And(const Opacity<Tp>& other) const noexcept { return  Opacity<Tp>(_value.And(other._value)); }
		[[nodiscard]] constexpr Opacity<Tp> Or(const Opacity<Tp>& other) const noexcept { return  Opacity<Tp>(_value.Or(other._value)); }
		[[nodiscard]] constexpr Opacity<Tp> Not() const noexcept { return  Opacity<Tp>(_value.Not()); }
		[[nodiscard]] constexpr Opacity<Tp> Xor(const Opacity<Tp>& other) const noexcept { return  Opacity<Tp>(_value.Xor(other._value)); }
		[[nodiscard]] constexpr bool Equals(const Opacity<Tp>& other) const noexcept { return _value.Equals(other._value); }
		[[nodiscard]] constexpr bool Compare(const Opacity<Tp>& other) const noexcept { return _value.Compare(other._value); }

		[[nodiscard]] constexpr Opacity<Tp> operator+(const Opacity<Tp>& other) const noexcept { return Add(other); }
		[[nodiscard]] constexpr Opacity<Tp> operator-(const Opacity<Tp>& other) const noexcept { return Subtract(other); }
		[[nodiscard]] constexpr Opacity<Tp> operator*(const Opacity<Tp>& other) const noexcept { return Multiply(other); }
		[[nodiscard]] constexpr Opacity<Tp> operator/(const Opacity<Tp>& other) const noexcept { return Divide(other); }
		[[nodiscard]] constexpr Opacity<Tp> operator|(const Opacity<Tp>& other) const noexcept { return Or(other); }
		[[nodiscard]] constexpr Opacity<Tp> operator&(const Opacity<Tp>& other) const noexcept { return And(other); }
		[[nodiscard]] constexpr Opacity<Tp> operator~() const noexcept { return Not(); }
		[[nodiscard]] constexpr Opacity<Tp> operator^(const Opacity<Tp>& other) const noexcept { return Xor(other); }
		constexpr Opacity<Tp>& operator+=(const Opacity<Tp>& other) noexcept { return *this = Add(other); }
		constexpr Opacity<Tp>& operator-=(const Opacity<Tp>& other) noexcept { return *this = Subtract(other); }
		constexpr Opacity<Tp>& operator*=(const Opacity<Tp>& other) noexcept { return *this = Multiply(other); }
		constexpr Opacity<Tp>& operator/=(const Opacity<Tp>& other) noexcept { return *this = Divide(other); }
		constexpr Opacity<Tp>& operator|=(const Opacity<Tp>& other) noexcept { return *this = Or(other); }
		constexpr Opacity<Tp>& operator&=(const Opacity<Tp>& other) noexcept { return *this = And(other); }
		constexpr Opacity<Tp>& operator^=(const Opacity<Tp>& other) noexcept { return *this = Xor(other); }
		[[nodiscard]] constexpr bool operator==(const Opacity<Tp>& other) const noexcept { return Equals(other); }
		[[nodiscard]] constexpr bool operator!=(const Opacity<Tp>& other) const noexcept { return !Equals(other); }
		[[nodiscard]] constexpr bool operator<(const Opacity<Tp>& other) const noexcept { return Compare(other) < 0; }
		[[nodiscard]] constexpr bool operator>(const Opacity<Tp>& other) const noexcept { return Compare(other) > 0; }
		[[nodiscard]] constexpr bool operator<=(const Opacity<Tp>& other) const noexcept { return Compare(other) <= 0; }
		[[nodiscard]] constexpr bool operator>=(const Opacity<Tp>& other) const noexcept { return Compare(other) >= 0; }

		[[nodiscard]] constexpr static Opacity<Tp> Empty() noexcept { return Opacity<Tp>(); }
		[[nodiscard]] constexpr static Opacity<Tp> Max() noexcept { return Opacity<Tp>(ValueType::Max()); }
		[[nodiscard]] constexpr static Opacity<Tp> Min() noexcept { return Opacity<Tp>(ValueType::Min()); }
	};

	extern template struct Opacity<Proportion1_t>;
	extern template struct Opacity<Proportion8_t>;
	extern template struct Opacity<Proportion16_t>;
	extern template struct Opacity<Proportion32_t>;
	extern template struct Opacity<Proportion64_t>;
	extern template struct Opacity<FixedPoint16q15_t>;
	extern template struct Opacity<FixedPoint32q31_t>;
	extern template struct Opacity<FixedPoint64q63_t>;
	extern template struct Opacity<float>;
	extern template struct Opacity<double>;

	typedef Opacity<Proportion1_t> Opacity1_t;
	typedef Opacity<Proportion8_t> Opacity8_t;
	typedef Opacity<Proportion16_t> Opacity16_t;
	typedef Opacity<Proportion32_t> Opacity32_t;
	typedef Opacity<Proportion64_t> Opacity64_t;
	typedef Opacity<FixedPoint16q15_t> OpacityI16_t;
	typedef Opacity<FixedPoint32q31_t> OpacityI32_t;
	typedef Opacity<FixedPoint64q63_t> OpacityI64_t;
	typedef Opacity<float> OpacityF32_t;
	typedef Opacity<double> OpacityF64_t;
}
#endif // __stationaryorbit_graphics_core_opacity__
