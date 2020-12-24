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
	///	0..1の範囲で表される色チャネルを表します。
	///	@param	Tp
	///	値の表現に用いるための型。
	template<class Tp, class = void>
	struct ChannelValue final
	{
		static_assert(Traits::IsNumericalType<Tp>, "テンプレート型 Tp は Traits::IsNumericalType の要件を満たす必要があります。");
		static_assert(std::is_constructible_v<Tp, int>, "テンプレート引数型 Tp は (int) を引数に取るコンストラクタを持つ必要があります。");
	public:
		///	この型の値の表現のために内部で使用されている型。
		typedef Tp ValueType;

	private:
		///	この型の内部で使用されているデータとしての値。
		ValueType _value;

	public:
		constexpr ChannelValue() noexcept = default;
		constexpr ChannelValue(const ValueType& value) noexcept : _value(value) {}
		constexpr explicit ChannelValue(const int& value) noexcept : ChannelValue(ValueType(value)) {}
		template<class fromT>
		constexpr explicit ChannelValue(const ChannelValue<fromT>& from) : _value(static_cast<ValueType>(from.Data())) {}
		constexpr ChannelValue(const ZeroValue_t&) noexcept : _value(Zero) {}
		~ChannelValue() = default;

	public:
		///	このオブジェクトの内部用いられているデータを取得します。
		[[nodiscard]] constexpr const ValueType& Data() const noexcept { return _value; }
		///	このオブジェクトが正規化された値であるかを取得します。
		[[nodiscard]] constexpr bool IsNormalized() const noexcept { return (Min()._value <= _value)&&(_value <= Max()._value); }
		///	正規化されたオブジェクトを取得します。
		[[nodiscard]] constexpr ChannelValue<Tp> Normalize() const noexcept { return (Min()._value <= _value)?((_value <= Max()._value)?_value:Max()._value):(Min()._value); }

		[[nodiscard]] constexpr bool Equals(const ChannelValue<Tp>& other) const noexcept { return _value == other._value; }
		[[nodiscard]] constexpr int Compare(const ChannelValue<Tp>& other) const noexcept
		{
			if (_value < other._value) { return -1;}
			else if ( other._value < _value) { return 1; }
			else { return 0; }
		}

		[[nodiscard]] constexpr ChannelValue<Tp> operator+() const noexcept { return ChannelValue<Tp>(+_value); }
		[[nodiscard]] constexpr ChannelValue<Tp> operator-() const noexcept { return ChannelValue<Tp>(-_value); }
		[[nodiscard]] constexpr ChannelValue<Tp> operator+(const ChannelValue<Tp>& other) const noexcept { return ArithmeticOperation::SaturateAdd(_value, other._value); }
		[[nodiscard]] constexpr ChannelValue<Tp> operator-(const ChannelValue<Tp>& other) const noexcept { return ArithmeticOperation::SaturateSubtract(_value, other._value); }
		[[nodiscard]] constexpr ChannelValue<Tp> operator*(const ChannelValue<Tp>& other) const noexcept { return ArithmeticOperation::SaturateMultiply(_value, other._value); }
		[[nodiscard]] constexpr ChannelValue<Tp> operator/(const ChannelValue<Tp>& other) const noexcept { return ArithmeticOperation::SaturateDivide(_value, other._value); }
		[[nodiscard]] constexpr ChannelValue<Tp> operator&(const ChannelValue<Tp>& other) const noexcept { return std::min({ _value, other._value }); }
		[[nodiscard]] constexpr ChannelValue<Tp> operator|(const ChannelValue<Tp>& other) const noexcept { return std::max({ _value, other._value }); }
		[[nodiscard]] constexpr ChannelValue<Tp> operator~() const noexcept { return Max()._value - _value; }
		[[nodiscard]] constexpr ChannelValue<Tp> operator^(const ChannelValue<Tp>& other) const noexcept { return ((*this)|(other))&(~(((*this)&(other)))); }
		constexpr ChannelValue<Tp>& operator+=(const ChannelValue<Tp>& other) noexcept { return *this = (*this) + (other); }
		constexpr ChannelValue<Tp>& operator-=(const ChannelValue<Tp>& other) noexcept { return *this = (*this) - (other); }
		constexpr ChannelValue<Tp>& operator*=(const ChannelValue<Tp>& other) noexcept { return *this = (*this) * (other); }
		constexpr ChannelValue<Tp>& operator/=(const ChannelValue<Tp>& other) noexcept { return *this = (*this) / (other); }
		constexpr ChannelValue<Tp>& operator&=(const ChannelValue<Tp>& other) noexcept { return *this = (*this) & (other); }
		constexpr ChannelValue<Tp>& operator|=(const ChannelValue<Tp>& other) noexcept { return *this = (*this) | (other); }
		constexpr ChannelValue<Tp>& operator^=(const ChannelValue<Tp>& other) noexcept { return *this = (*this) ^ (other); }
		[[nodiscard]] constexpr bool operator==(const ChannelValue<Tp>& other) const noexcept { return Equals(other); }
		[[nodiscard]] constexpr bool operator!=(const ChannelValue<Tp>& other) const noexcept { return !Equals(other); }
		[[nodiscard]] constexpr bool operator<(const ChannelValue<Tp>& other) const noexcept { return Compare(other) < 0; }
		[[nodiscard]] constexpr bool operator>(const ChannelValue<Tp>& other) const noexcept { return Compare(other) > 0; }
		[[nodiscard]] constexpr bool operator<=(const ChannelValue<Tp>& other) const noexcept { return Compare(other) <= 0; }
		[[nodiscard]] constexpr bool operator>=(const ChannelValue<Tp>& other) const noexcept { return Compare(other) >= 0; }

	public:
		///	空のオブジェクトを取得します。
		[[nodiscard]] constexpr static ChannelValue<Tp> Empty() noexcept { return ChannelValue<Tp>(); }
		///	この型で表せる最大の値を持つオブジェクトを取得します。
		[[nodiscard]] constexpr static ChannelValue<Tp> Max() noexcept { return ChannelValue<Tp>(ValueType(1)); }
		///	この型で表せる最小の値を持つオブジェクトを取得します。
		[[nodiscard]] constexpr static ChannelValue<Tp> Min() noexcept { return ChannelValue<Tp>(ValueType(0)); }
	};

	///	0..1の範囲で表される色チャネルを表します。
	///	@a ChannelValue の浮動小数点型に対する特殊化です。
	template<class Tp>
	struct ChannelValue<Tp, std::enable_if_t<std::is_floating_point_v<Tp>>>
	{
		static_assert(Traits::IsNumericalType<Tp>, "テンプレート型 Tp は Traits::IsNumericalType の要件を満たす必要があります。");
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
		~ChannelValue() = default;

	public:
		///	このオブジェクトの内部用いられているデータを取得します。
		[[nodiscard]] constexpr ValueType Data() const noexcept { return _value; }
		///	このオブジェクトが正規化された値であるかを取得します。
		[[nodiscard]] constexpr bool IsNormalized() const noexcept { return (Min()._value <= _value)&&(_value <= Max()._value); }
		///	正規化されたオブジェクトを取得します。
		[[nodiscard]] constexpr ChannelValue<Tp> Normalize() const noexcept { return (Min()._value <= _value)?((_value <= Max()._value)?_value:Max()._value):(Min()._value); }

		[[nodiscard]] constexpr bool Equals(const ChannelValue<Tp>& other) const noexcept { return _value == other._value; }
		[[nodiscard]] constexpr int Compare(const ChannelValue<Tp>& other) const noexcept
		{
			if (_value < other._value) { return -1;}
			else if ( other._value < _value) { return 1; }
			else { return 0; }
		}

		[[nodiscard]] constexpr ChannelValue<Tp> operator+() const noexcept { return ChannelValue<Tp>(+_value); }
		[[nodiscard]] constexpr ChannelValue<Tp> operator-() const noexcept { return ChannelValue<Tp>(-_value); }
		[[nodiscard]] constexpr ChannelValue<Tp> operator+(const ChannelValue<Tp>& other) const noexcept { return ArithmeticOperation::SaturateAdd(_value, other._value); }
		[[nodiscard]] constexpr ChannelValue<Tp> operator-(const ChannelValue<Tp>& other) const noexcept { return ArithmeticOperation::SaturateSubtract(_value, other._value); }
		[[nodiscard]] constexpr ChannelValue<Tp> operator*(const ChannelValue<Tp>& other) const noexcept { return ArithmeticOperation::SaturateMultiply(_value, other._value); }
		[[nodiscard]] constexpr ChannelValue<Tp> operator/(const ChannelValue<Tp>& other) const noexcept { return ArithmeticOperation::SaturateDivide(_value, other._value); }
		[[nodiscard]] constexpr ChannelValue<Tp> operator&(const ChannelValue<Tp>& other) const noexcept { return std::min({ _value, other._value }); }
		[[nodiscard]] constexpr ChannelValue<Tp> operator|(const ChannelValue<Tp>& other) const noexcept { return std::max({ _value, other._value }); }
		[[nodiscard]] constexpr ChannelValue<Tp> operator~() const noexcept { return Max()._value - _value; }
		[[nodiscard]] constexpr ChannelValue<Tp> operator^(const ChannelValue<Tp>& other) const noexcept { return ((*this)|(other))&(~(((*this)&(other)))); }
		constexpr ChannelValue<Tp>& operator+=(const ChannelValue<Tp>& other) noexcept { return *this = (*this) + (other); }
		constexpr ChannelValue<Tp>& operator-=(const ChannelValue<Tp>& other) noexcept { return *this = (*this) - (other); }
		constexpr ChannelValue<Tp>& operator*=(const ChannelValue<Tp>& other) noexcept { return *this = (*this) * (other); }
		constexpr ChannelValue<Tp>& operator/=(const ChannelValue<Tp>& other) noexcept { return *this = (*this) / (other); }
		constexpr ChannelValue<Tp>& operator&=(const ChannelValue<Tp>& other) noexcept { return *this = (*this) & (other); }
		constexpr ChannelValue<Tp>& operator|=(const ChannelValue<Tp>& other) noexcept { return *this = (*this) | (other); }
		constexpr ChannelValue<Tp>& operator^=(const ChannelValue<Tp>& other) noexcept { return *this = (*this) ^ (other); }
		[[nodiscard]] constexpr bool operator==(const ChannelValue<Tp>& other) const noexcept { return Equals(other); }
		[[nodiscard]] constexpr bool operator!=(const ChannelValue<Tp>& other) const noexcept { return !Equals(other); }
		[[nodiscard]] constexpr bool operator<(const ChannelValue<Tp>& other) const noexcept { return Compare(other) < 0; }
		[[nodiscard]] constexpr bool operator>(const ChannelValue<Tp>& other) const noexcept { return Compare(other) > 0; }
		[[nodiscard]] constexpr bool operator<=(const ChannelValue<Tp>& other) const noexcept { return Compare(other) <= 0; }
		[[nodiscard]] constexpr bool operator>=(const ChannelValue<Tp>& other) const noexcept { return Compare(other) >= 0; }

	public:
		///	空のオブジェクトを取得します。
		[[nodiscard]] constexpr static ChannelValue<Tp> Empty() noexcept { return ChannelValue<Tp>(); }
		///	この型で表せる最大の値を持つオブジェクトを取得します。
		[[nodiscard]] constexpr static ChannelValue<Tp> Max() noexcept { return ChannelValue<Tp>(ValueType(1)); }
		///	この型で表せる最小の値を持つオブジェクトを取得します。
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

	///	内部に @a Proportion8_t 型のデータを持つ @a ChannelValue です。
	typedef ChannelValue<Proportion8_t> Channel8_t;
	/// 内部に @a Proportion16_t 型のデータを持つ @a ChannelValue です。
	typedef ChannelValue<Proportion16_t> Channel16_t;
	/// 内部に @a Proportion32_t 型のデータを持つ @a ChannelValue です。
	typedef ChannelValue<Proportion32_t> Channel32_t;
	/// 内部に @a Proportion64_t 型のデータを持つ @a ChannelValue です。
	typedef ChannelValue<Proportion64_t> Channel64_t;
	/// 内部に @a FixedPoint16q15_t 型のデータを持つ @a ChannelValue です。
	typedef ChannelValue<FixedPoint16q15_t> ChannelI16_t;
	/// 内部に @a FixedPoint32q31_t 型のデータを持つ @a ChannelValue です。
	typedef ChannelValue<FixedPoint32q31_t> ChannelI32_t;
	/// 内部に @a FixedPoint64q63_t 型のデータを持つ @a ChannelValue です。
	typedef ChannelValue<FixedPoint64q63_t> ChannelI64_t;
	/// 内部に @a float 型のデータを持つ @a ChannelValue です。
	typedef ChannelValue<float> ChannelF32_t;
	/// 内部に @a double 型のデータを持つ @a ChannelValue です。
	typedef ChannelValue<double> ChannelF64_t;
}
namespace std
{
	template<class Tp>
	class numeric_limits<zawa_ch::StationaryOrbit::Graphics::ChannelValue<Tp>> : public numeric_limits<void>
	{
	public:
		static constexpr bool is_specialized = true;
		static constexpr bool is_signed = false;
		static constexpr bool is_integer = false;
		static constexpr bool is_exact = true;
		static constexpr bool has_infinity = false;
		static constexpr bool has_quiet_NaN = false;
		static constexpr bool has_signaling_NaN = false;
		static constexpr float_denorm_style has_denorm = denorm_absent;
		static constexpr bool has_denorm_loss = false;
		static constexpr float_round_style round_style = round_toward_zero;
		static constexpr bool is_iec559 = false;
		static constexpr bool is_bounded = true;
		static constexpr bool is_modulo = false;
		static constexpr int digits = numeric_limits<Tp>::digits;
		static constexpr int digits10 = numeric_limits<Tp>::digits10;
		static constexpr int max_digits10 = numeric_limits<Tp>::max_digits10;
		static constexpr int radix = 2;
		static constexpr int min_exponent = 0;
		static constexpr int min_exponent10 = 0;
		static constexpr int max_exponent = 0;
		static constexpr int max_exponent10 = 0;
		static constexpr bool traps = true;
		static constexpr bool tinyness_before = true;
		static constexpr zawa_ch::StationaryOrbit::Graphics::ChannelValue<Tp> min() noexcept { return zawa_ch::StationaryOrbit::Graphics::ChannelValue<Tp>::Min(); }
		static constexpr zawa_ch::StationaryOrbit::Graphics::ChannelValue<Tp> lowest() noexcept { return zawa_ch::StationaryOrbit::Graphics::ChannelValue<Tp>::Min(); }
		static constexpr zawa_ch::StationaryOrbit::Graphics::ChannelValue<Tp> max() noexcept { return zawa_ch::StationaryOrbit::Graphics::ChannelValue<Tp>::Max(); }
		static constexpr zawa_ch::StationaryOrbit::Graphics::ChannelValue<Tp> epsilon() noexcept { return zawa_ch::StationaryOrbit::Graphics::ChannelValue<Tp>(numeric_limits<Tp>::epsiron()); }
		static constexpr zawa_ch::StationaryOrbit::Graphics::ChannelValue<Tp> round_error() noexcept { return zawa_ch::StationaryOrbit::Graphics::ChannelValue<Tp>(numeric_limits<Tp>::round_error()); }
	};
}
#endif // __stationaryorbit_graphics_core_channelvalue__
