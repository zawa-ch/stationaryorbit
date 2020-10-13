//	stationaryorbit/graphics-core/channelvalue
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
#ifndef __stationaryorbit_graphics_core_channelvalue__
#define __stationaryorbit_graphics_core_channelvalue__
#include "stationaryorbit/core.traits.hpp"
#include "stationaryorbit/core.numeral.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	template<class Tp, class = void>
	struct ChannelValue final
	{
		static_assert(Traits::Equatable<Tp>, "テンプレート型 Tp は Traits::Equatable の要件を満たす必要があります。");
		static_assert(Traits::Comparable<Tp>, "テンプレート型 Tp は Traits::Comparable の要件を満たす必要があります。");
		static_assert(Traits::HasArithmeticOperation<Tp>, "テンプレート型 Tp は Traits::HasArithmeticOperation の要件を満たす必要があります。");
		static_assert(Traits::HasSaturateOperation<Tp>, "テンプレート型 Tp は Traits::HasSaturateOperation の要件を満たす必要があります。");
		static_assert(Traits::HasCheckedOperation<Tp>, "テンプレート型 Tp は Traits::HasCheckedOperation の要件を満たす必要があります。");
	public:
		///	この型の値の表現のために内部で使用されている型。
		typedef Tp ValueType;

	private:
		///	この型の内部で使用されているデータとしての値。
		ValueType _value;

	public:
		constexpr ChannelValue() noexcept = default;
		constexpr ChannelValue(const ValueType& value) noexcept : _value(value) {}
		template<class fromT>
		constexpr explicit ChannelValue(const ChannelValue<fromT>& from) : _value(static_cast<ValueType>(from.Data())) {}
		constexpr ChannelValue(const ZeroValue_t&) : _value(Zero) {}
		constexpr ChannelValue(const ChannelValue<Tp>&) = default;
		constexpr ChannelValue(ChannelValue<Tp>&&) = default;
		~ChannelValue() = default;

	public:
		[[nodiscard]] constexpr const ValueType& Data() const noexcept { return _value; }
		[[nodiscard]] constexpr bool IsNormalized() const noexcept { return (Min()._value <= _value)&&(_value <= Max()._value); }
		[[nodiscard]] constexpr ChannelValue<Tp> Normalize() const noexcept { return (Min()._value <= _value)?((_value <= Max()._value)?_value:Max()._value):(Min()._value); }

		[[nodiscard]] constexpr ChannelValue<Tp> Promote() const noexcept { return ChannelValue<Tp>(+_value); }
		[[nodiscard]] constexpr ChannelValue<Tp> Invert() const noexcept { return ChannelValue<Tp>(-_value); }
		[[nodiscard]] constexpr ChannelValue<Tp> Add(const ChannelValue<Tp>& other) const noexcept { return _value + other._value; }
		[[nodiscard]] constexpr ChannelValue<Tp> Subtract(const ChannelValue<Tp>& other) const noexcept { return _value - other._value; }
		[[nodiscard]] constexpr ChannelValue<Tp> Multiply(const ChannelValue<Tp>& other) const noexcept { return _value * other._value; }
		[[nodiscard]] constexpr ChannelValue<Tp> Divide(const ChannelValue<Tp>& other) const noexcept { return _value / other._value; }
		[[nodiscard]] constexpr ChannelValue<Tp> SaturateAdd(const ChannelValue<Tp>& other) const noexcept { return _value.SaturateAdd(other._value); }
		[[nodiscard]] constexpr ChannelValue<Tp> SaturateSubtract(const ChannelValue<Tp>& other) const noexcept { return _value.SaturateSubtract(other._value); }
		[[nodiscard]] constexpr ChannelValue<Tp> SaturateMultiply(const ChannelValue<Tp>& other) const noexcept { return _value.SaturateMultiply(other._value); }
		[[nodiscard]] constexpr ChannelValue<Tp> SaturateDivide(const ChannelValue<Tp>& other) const noexcept { return _value.SaturateDivide(other._value); }
		[[nodiscard]] constexpr ChannelValue<Tp> CheckedAdd(const ChannelValue<Tp>& other) const { return _value.CheckedAdd(other._value); }
		[[nodiscard]] constexpr ChannelValue<Tp> CheckedSubtract(const ChannelValue<Tp>& other) const { return _value.CheckedSubtract(other._value); }
		[[nodiscard]] constexpr ChannelValue<Tp> CheckedMultiply(const ChannelValue<Tp>& other) const { return _value.CheckedMultiply(other._value); }
		[[nodiscard]] constexpr ChannelValue<Tp> CheckedDivide(const ChannelValue<Tp>& other) const { return _value.CheckedDivide(other._value); }
		[[nodiscard]] constexpr ChannelValue<Tp> And(const ChannelValue<Tp>& other) const noexcept { return std::min({ _value, other._value }); }
		[[nodiscard]] constexpr ChannelValue<Tp> Or(const ChannelValue<Tp>& other) const noexcept { return std::max({ _value, other._value }); }
		[[nodiscard]] constexpr ChannelValue<Tp> Not() const noexcept { return Max()._value - _value; }
		[[nodiscard]] constexpr ChannelValue<Tp> Xor(const ChannelValue<Tp>& other) const noexcept { return Or(other).And(And(other).Not()) ; }
		[[nodiscard]] constexpr bool Equals(const ChannelValue<Tp>& other) const noexcept { return _value == other._value; }
		[[nodiscard]] constexpr int Compare(const ChannelValue<Tp>& other) const noexcept
		{
			if (_value < other._value) { return -1;}
			else if ( other._value < _value) { return 1; }
			else { return 0; }
		}

		[[nodiscard]] constexpr ChannelValue<Tp> operator+(const ChannelValue<Tp>& other) const noexcept { return Add(other); }
		[[nodiscard]] constexpr ChannelValue<Tp> operator-(const ChannelValue<Tp>& other) const noexcept { return Subtract(other); }
		[[nodiscard]] constexpr ChannelValue<Tp> operator*(const ChannelValue<Tp>& other) const noexcept { return Multiply(other); }
		[[nodiscard]] constexpr ChannelValue<Tp> operator/(const ChannelValue<Tp>& other) const noexcept { return Divide(other); }
		[[nodiscard]] constexpr ChannelValue<Tp> operator|(const ChannelValue<Tp>& other) const noexcept { return Or(other); }
		[[nodiscard]] constexpr ChannelValue<Tp> operator&(const ChannelValue<Tp>& other) const noexcept { return And(other); }
		[[nodiscard]] constexpr ChannelValue<Tp> operator~() const noexcept { return Not(); }
		[[nodiscard]] constexpr ChannelValue<Tp> operator^(const ChannelValue<Tp>& other) const noexcept { return Xor(other); }
		constexpr ChannelValue<Tp>& operator+=(const ChannelValue<Tp>& other) noexcept { return *this = Add(other); }
		constexpr ChannelValue<Tp>& operator-=(const ChannelValue<Tp>& other) noexcept { return *this = Subtract(other); }
		constexpr ChannelValue<Tp>& operator*=(const ChannelValue<Tp>& other) noexcept { return *this = Multiply(other); }
		constexpr ChannelValue<Tp>& operator/=(const ChannelValue<Tp>& other) noexcept { return *this = Divide(other); }
		constexpr ChannelValue<Tp>& operator|=(const ChannelValue<Tp>& other) noexcept { return *this = Or(other); }
		constexpr ChannelValue<Tp>& operator&=(const ChannelValue<Tp>& other) noexcept { return *this = And(other); }
		constexpr ChannelValue<Tp>& operator^=(const ChannelValue<Tp>& other) noexcept { return *this = Xor(other); }
		[[nodiscard]] constexpr bool operator==(const ChannelValue<Tp>& other) const noexcept { return Equals(other); }
		[[nodiscard]] constexpr bool operator!=(const ChannelValue<Tp>& other) const noexcept { return !Equals(other); }
		[[nodiscard]] constexpr bool operator<(const ChannelValue<Tp>& other) const noexcept { return Compare(other) < 0; }
		[[nodiscard]] constexpr bool operator>(const ChannelValue<Tp>& other) const noexcept { return Compare(other) > 0; }
		[[nodiscard]] constexpr bool operator<=(const ChannelValue<Tp>& other) const noexcept { return Compare(other) <= 0; }
		[[nodiscard]] constexpr bool operator>=(const ChannelValue<Tp>& other) const noexcept { return Compare(other) >= 0; }
		constexpr ChannelValue<Tp>& operator=(const ChannelValue<Tp>&) = default;
		constexpr ChannelValue<Tp>& operator=(ChannelValue<Tp>&&) = default;

	public:
		[[nodiscard]] constexpr static ChannelValue<Tp> Empty() noexcept { return ChannelValue<Tp>(); }
		[[nodiscard]] constexpr static ChannelValue<Tp> Max() noexcept { return ChannelValue<Tp>(ValueType(1)); }
		[[nodiscard]] constexpr static ChannelValue<Tp> Min() noexcept { return ChannelValue<Tp>(ValueType(0)); }
	};

	template<class Tp>
	struct ChannelValue<Tp, std::enable_if_t<std::is_floating_point_v<Tp>>>
	{
		static_assert(Traits::Equatable<Tp>, "テンプレート型 Tp は Traits::Equatable の要件を満たす必要があります。");
		static_assert(Traits::Comparable<Tp>, "テンプレート型 Tp は Traits::Comparable の要件を満たす必要があります。");
		static_assert(Traits::HasArithmeticOperation<Tp>, "テンプレート型 Tp は Traits::HasArithmeticOperation の要件を満たす必要があります。");
	public:
		///	この型の値の表現のために内部で使用されている型。
		typedef Tp ValueType;

	private:
		///	この型の内部で使用されているデータとしての値。
		ValueType _value;

	public:
		constexpr ChannelValue() noexcept = default;
		constexpr ChannelValue(const ValueType& value) noexcept : _value(value) {}
		constexpr ChannelValue(const ChannelValue<Tp>&) = default;
		constexpr ChannelValue(ChannelValue<Tp>&&) = default;
		~ChannelValue() = default;

	public:
		[[nodiscard]] constexpr ValueType Data() const noexcept { return _value; }
		[[nodiscard]] constexpr bool IsNormalized() const noexcept { return (Min()._value <= _value)&&(_value <= Max()._value); }
		[[nodiscard]] constexpr ChannelValue<Tp> Normalize() const noexcept { return (Min()._value <= _value)?((_value <= ValueType(1))?_value:ValueType(1)):(Min()._value); }

		[[nodiscard]] constexpr ChannelValue<Tp> Promote() const noexcept { return ChannelValue<Tp>(+_value); }
		[[nodiscard]] constexpr ChannelValue<Tp> Invert() const noexcept { return ChannelValue<Tp>(-_value); }
		[[nodiscard]] constexpr ChannelValue<Tp> Add(const ChannelValue<Tp>& other) const noexcept { return _value + other._value; }
		[[nodiscard]] constexpr ChannelValue<Tp> Subtract(const ChannelValue<Tp>& other) const noexcept { return _value - other._value; }
		[[nodiscard]] constexpr ChannelValue<Tp> Multiply(const ChannelValue<Tp>& other) const noexcept { return _value * other._value; }
		[[nodiscard]] constexpr ChannelValue<Tp> Divide(const ChannelValue<Tp>& other) const noexcept { return _value / other._value; }
		[[nodiscard]] constexpr ChannelValue<Tp> SaturateAdd(const ChannelValue<Tp>& other) const noexcept { return Add(other._value); }
		[[nodiscard]] constexpr ChannelValue<Tp> SaturateSubtract(const ChannelValue<Tp>& other) const noexcept { return Subtract(other._value); }
		[[nodiscard]] constexpr ChannelValue<Tp> SaturateMultiply(const ChannelValue<Tp>& other) const noexcept { return Multiply(other._value); }
		[[nodiscard]] constexpr ChannelValue<Tp> SaturateDivide(const ChannelValue<Tp>& other) const noexcept { return Divide(other._value); }
		[[nodiscard]] constexpr ChannelValue<Tp> CheckedAdd(const ChannelValue<Tp>& other) const { return Add(other._value); }
		[[nodiscard]] constexpr ChannelValue<Tp> CheckedSubtract(const ChannelValue<Tp>& other) const { return Subtract(other._value); }
		[[nodiscard]] constexpr ChannelValue<Tp> CheckedMultiply(const ChannelValue<Tp>& other) const { return Multiply(other._value); }
		[[nodiscard]] constexpr ChannelValue<Tp> CheckedDivide(const ChannelValue<Tp>& other) const { return Divide(other._value); }
		[[nodiscard]] constexpr ChannelValue<Tp> And(const ChannelValue<Tp>& other) const noexcept { return std::min({ _value, other._value }); }
		[[nodiscard]] constexpr ChannelValue<Tp> Or(const ChannelValue<Tp>& other) const noexcept { return std::max({ _value, other._value }); }
		[[nodiscard]] constexpr ChannelValue<Tp> Not() const noexcept { return Max()._value - _value; }
		[[nodiscard]] constexpr ChannelValue<Tp> Xor(const ChannelValue<Tp>& other) const noexcept { return Or(other).And(And(other).Not()) ; }
		[[nodiscard]] constexpr bool Equals(const ChannelValue<Tp>& other) const noexcept { return _value == other._value; }
		[[nodiscard]] constexpr int Compare(const ChannelValue<Tp>& other) const noexcept
		{
			if (_value < other._value) { return -1;}
			else if ( other._value < _value) { return 1; }
			else { return 0; }
		}

		[[nodiscard]] constexpr ChannelValue<Tp> operator+(const ChannelValue<Tp>& other) const noexcept { return Add(other); }
		[[nodiscard]] constexpr ChannelValue<Tp> operator-(const ChannelValue<Tp>& other) const noexcept { return Subtract(other); }
		[[nodiscard]] constexpr ChannelValue<Tp> operator*(const ChannelValue<Tp>& other) const noexcept { return Multiply(other); }
		[[nodiscard]] constexpr ChannelValue<Tp> operator/(const ChannelValue<Tp>& other) const noexcept { return Divide(other); }
		[[nodiscard]] constexpr ChannelValue<Tp> operator|(const ChannelValue<Tp>& other) const noexcept { return Or(other); }
		[[nodiscard]] constexpr ChannelValue<Tp> operator&(const ChannelValue<Tp>& other) const noexcept { return And(other); }
		[[nodiscard]] constexpr ChannelValue<Tp> operator~() const noexcept { return Not(); }
		[[nodiscard]] constexpr ChannelValue<Tp> operator^(const ChannelValue<Tp>& other) const noexcept { return Xor(other); }
		constexpr ChannelValue<Tp>& operator+=(const ChannelValue<Tp>& other) noexcept { return *this = Add(other); }
		constexpr ChannelValue<Tp>& operator-=(const ChannelValue<Tp>& other) noexcept { return *this = Subtract(other); }
		constexpr ChannelValue<Tp>& operator*=(const ChannelValue<Tp>& other) noexcept { return *this = Multiply(other); }
		constexpr ChannelValue<Tp>& operator/=(const ChannelValue<Tp>& other) noexcept { return *this = Divide(other); }
		constexpr ChannelValue<Tp>& operator|=(const ChannelValue<Tp>& other) noexcept { return *this = Or(other); }
		constexpr ChannelValue<Tp>& operator&=(const ChannelValue<Tp>& other) noexcept { return *this = And(other); }
		constexpr ChannelValue<Tp>& operator^=(const ChannelValue<Tp>& other) noexcept { return *this = Xor(other); }
		[[nodiscard]] constexpr bool operator==(const ChannelValue<Tp>& other) const noexcept { return Equals(other); }
		[[nodiscard]] constexpr bool operator!=(const ChannelValue<Tp>& other) const noexcept { return !Equals(other); }
		[[nodiscard]] constexpr bool operator<(const ChannelValue<Tp>& other) const noexcept { return Compare(other) < 0; }
		[[nodiscard]] constexpr bool operator>(const ChannelValue<Tp>& other) const noexcept { return Compare(other) > 0; }
		[[nodiscard]] constexpr bool operator<=(const ChannelValue<Tp>& other) const noexcept { return Compare(other) <= 0; }
		[[nodiscard]] constexpr bool operator>=(const ChannelValue<Tp>& other) const noexcept { return Compare(other) >= 0; }
		constexpr ChannelValue<Tp>& operator=(const ChannelValue<Tp>&) = default;
		constexpr ChannelValue<Tp>& operator=(ChannelValue<Tp>&&) = default;

	public:
		[[nodiscard]] constexpr static ChannelValue<Tp> Empty() noexcept { return ChannelValue<Tp>(); }
		[[nodiscard]] constexpr static ChannelValue<Tp> Max() noexcept { return ChannelValue<Tp>(ValueType(1)); }
		[[nodiscard]] constexpr static ChannelValue<Tp> Min() noexcept { return ChannelValue<Tp>(ValueType(0)); }
	};

	extern template struct ChannelValue<Proportion8_t>;
	extern template struct ChannelValue<Proportion16_t>;
	extern template struct ChannelValue<Proportion32_t>;
	extern template struct ChannelValue<Proportion64_t>;
	extern template struct ChannelValue<FixedPoint16q15_t>;
	extern template struct ChannelValue<FixedPoint32q31_t>;
	extern template struct ChannelValue<FixedPoint64q63_t>;
	extern template struct ChannelValue<float>;
	extern template struct ChannelValue<double>;

	typedef ChannelValue<Proportion8_t> Channel8_t;
	typedef ChannelValue<Proportion16_t> Channel16_t;
	typedef ChannelValue<Proportion32_t> Channel32_t;
	typedef ChannelValue<Proportion64_t> Channel64_t;
	typedef ChannelValue<FixedPoint16q15_t> ChannelI16_t;
	typedef ChannelValue<FixedPoint32q31_t> ChannelI32_t;
	typedef ChannelValue<FixedPoint64q63_t> ChannelI64_t;
	typedef ChannelValue<float> ChannelF32_t;
	typedef ChannelValue<double> ChannelF64_t;
}
#endif // __stationaryorbit_graphics_core_channelvalue__
