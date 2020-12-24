//	stationaryorbit/graphics-core/cmycolor
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
#ifndef __stationaryorbit_graphics_core_cmycolor__
#define __stationaryorbit_graphics_core_cmycolor__
#include "relativecolor.hpp"
#include "translucentcolor.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	///	シアン(Cyan), マゼンタ(Magenta), イエロー(Yellow)の三要素によって表される色。
	template <class Tp>
	struct CMYColor final
	{
	public: // types
		typedef RelativeColor<Tp, 3UL> DataType;
		///	この型の各チャネルの値の表現のために内部で使用されている型。
		typedef typename DataType::ValueType ValueType;
	private: // contains
		DataType _value;
	public: // constructor
		///	既定の @a CMYColor を初期化します。
		constexpr CMYColor() = default;
		///	CMY値を指定して @a CMYColor を初期化します。
		constexpr CMYColor(const ValueType& c, const ValueType& m, const ValueType& y) : _value({c, m, y}) {}
		constexpr explicit CMYColor(const DataType& value) : _value(value) {}
		template <class fromT>
		constexpr explicit CMYColor(const CMYColor<fromT>& from) : CMYColor(DataType(from.Data())) {}
		constexpr CMYColor(const ZeroValue_t&) : _value(Zero) {}
	public: // member
		constexpr const DataType& Data() const { return _value; }
		///	この @a CMYColor のシアンのコンポーネントを取得します。
		constexpr const ValueType& C() const { return _value.Data()[0]; }
		///	この @a CMYColor のマゼンタのコンポーネントを取得します。
		constexpr const ValueType& M() const { return _value.Data()[1]; }
		///	この @a CMYColor のイエローのコンポーネントを取得します。
		constexpr const ValueType& Y() const { return _value.Data()[2]; }
		///	この @a CMYColor が正規化されているかを取得します。
		constexpr bool IsNormalized() const { return _value.IsNormalized(); }
		///	正規化した @a CMYColor を取得します。
		constexpr CMYColor<Tp> Normalize() const { return CMYColor<Tp>(_value.Normalize()); }

		[[nodiscard]] constexpr CMYColor<Tp> SaturateAdd(const CMYColor<Tp>& other) const noexcept { return CMYColor<Tp>(_value.SaturateAdd(other._value)); }
		[[nodiscard]] constexpr CMYColor<Tp> SaturateSubtract(const CMYColor<Tp>& other) const noexcept { return CMYColor<Tp>(_value.SaturateSubtract(other._value)); }
		[[nodiscard]] constexpr CMYColor<Tp> SaturateMultiply(const CMYColor<Tp>& other) const noexcept { return CMYColor<Tp>(_value.SaturateMultiply(other._value)); }
		[[nodiscard]] constexpr CMYColor<Tp> SaturateMultiply(const ValueType& other) const noexcept { return CMYColor<Tp>(_value.SaturateMultiply(other)); }
		[[nodiscard]] constexpr CMYColor<Tp> SaturateDivide(const CMYColor<Tp>& other) const noexcept { return CMYColor<Tp>(_value.SaturateDivide(other._value)); }
		[[nodiscard]] constexpr CMYColor<Tp> SaturateDivide(const ValueType& other) const noexcept { return CMYColor<Tp>(_value.SaturateDivide(other)); }
		[[nodiscard]] constexpr CMYColor<Tp> CheckedAdd(const CMYColor<Tp>& other) const { return CMYColor<Tp>(_value.CheckedAdd(other._value)); }
		[[nodiscard]] constexpr CMYColor<Tp> CheckedSubtract(const CMYColor<Tp>& other) const { return CMYColor<Tp>(_value.CheckedSubtract(other._value)); }
		[[nodiscard]] constexpr CMYColor<Tp> CheckedMultiply(const CMYColor<Tp>& other) const { return CMYColor<Tp>(_value.CheckedMultiply(other._value)); }
		[[nodiscard]] constexpr CMYColor<Tp> CheckedMultiply(const ValueType& other) const { return CMYColor<Tp>(_value.CheckedMultiply(other)); }
		[[nodiscard]] constexpr CMYColor<Tp> CheckedDivide(const CMYColor<Tp>& other) const { return CMYColor<Tp>(_value.CheckedDivide(other._value)); }
		[[nodiscard]] constexpr CMYColor<Tp> CheckedDivide(const ValueType& other) const { return CMYColor<Tp>(_value.CheckedDivide(other)); }

		constexpr CMYColor<Tp> operator+() const { return CMYColor<Tp>(+_value); }
		constexpr CMYColor<Tp> operator-() const { return CMYColor<Tp>(-_value); }
		constexpr CMYColor<Tp> operator+(const CMYColor<Tp>& other) const { return CMYColor<Tp>(_value + other._value); }
		constexpr CMYColor<Tp> operator-(const CMYColor<Tp>& other) const { return CMYColor<Tp>(_value - other._value); }
		constexpr CMYColor<Tp> operator*(const CMYColor<Tp>& other) const { return CMYColor<Tp>(_value * other._value); }
		constexpr CMYColor<Tp> operator*(const ValueType& other) const { return CMYColor<Tp>(_value * other); }
		constexpr CMYColor<Tp> operator/(const CMYColor<Tp>& other) const { return CMYColor<Tp>(_value / other._value); }
		constexpr CMYColor<Tp> operator/(const ValueType& other) const { return CMYColor<Tp>(_value / other); }
		constexpr CMYColor<Tp> operator~() const { return CMYColor<Tp>(~_value); }
		constexpr CMYColor<Tp> operator&(const CMYColor<Tp>& other) const { return CMYColor<Tp>(_value & other._value); }
		constexpr CMYColor<Tp> operator|(const CMYColor<Tp>& other) const { return CMYColor<Tp>(_value | other._value); }
		constexpr CMYColor<Tp> operator^(const CMYColor<Tp>& other) const { return CMYColor<Tp>(_value ^ other._value); }
		constexpr CMYColor<Tp>& operator+=(const CMYColor<Tp>& other) { return *this = *this + other; }
		constexpr CMYColor<Tp>& operator-=(const CMYColor<Tp>& other) { return *this = *this - other; }
		constexpr CMYColor<Tp>& operator*=(const CMYColor<Tp>& other) { return *this = *this * other; }
		constexpr CMYColor<Tp>& operator*=(const ValueType& other) { return *this = *this * other; }
		constexpr CMYColor<Tp>& operator/=(const CMYColor<Tp>& other) { return *this = *this / other; }
		constexpr CMYColor<Tp>& operator/=(const ValueType& other) { return *this = *this / other; }
		constexpr CMYColor<Tp>& operator|=(const CMYColor<Tp>& other) { return *this = *this | other; }
		constexpr CMYColor<Tp>& operator&=(const CMYColor<Tp>& other) { return *this = *this & other; }
		constexpr CMYColor<Tp>& operator^=(const CMYColor<Tp>& other) { return *this = *this ^ other; }

		constexpr bool Equals(const CMYColor<Tp>& other) const { return _value.Equals(other._value); }
		constexpr bool operator==(const CMYColor<Tp>& other) const { return Equals(other); }
		constexpr bool operator!=(const CMYColor<Tp>& other) const { return !Equals(other); }

		constexpr static CMYColor<Tp> Empty() { return CMYColor<Tp>(); }
	};

	extern template struct CMYColor<Proportion8_t>;
	extern template struct CMYColor<Proportion16_t>;
	extern template struct CMYColor<Proportion32_t>;
	extern template struct CMYColor<Proportion64_t>;
	extern template struct CMYColor<FixedPoint16q15_t>;
	extern template struct CMYColor<FixedPoint32q31_t>;
	extern template struct CMYColor<FixedPoint64q63_t>;
	extern template struct CMYColor<float>;
	extern template struct CMYColor<double>;
	extern template struct TranslucentColor<CMYColor<Proportion8_t>>;
	extern template struct TranslucentColor<CMYColor<Proportion16_t>>;
	extern template struct TranslucentColor<CMYColor<Proportion32_t>>;
	extern template struct TranslucentColor<CMYColor<Proportion64_t>>;
	extern template struct TranslucentColor<CMYColor<FixedPoint16q15_t>>;
	extern template struct TranslucentColor<CMYColor<FixedPoint32q31_t>>;
	extern template struct TranslucentColor<CMYColor<FixedPoint64q63_t>>;
	extern template struct TranslucentColor<CMYColor<float>>;
	extern template struct TranslucentColor<CMYColor<double>>;

	typedef CMYColor<Proportion8_t> CMY8_t;
	typedef CMYColor<Proportion16_t> CMY16_t;
	typedef CMYColor<Proportion32_t> CMY32_t;
	typedef CMYColor<Proportion64_t> CMY64_t;
	typedef CMYColor<FixedPoint16q15_t> CMYI16_t;
	typedef CMYColor<FixedPoint32q31_t> CMYI32_t;
	typedef CMYColor<FixedPoint64q63_t> CMYI64_t;
	typedef CMYColor<float> CMYF32_t;
	typedef CMYColor<double> CMYF64_t;
	typedef TranslucentColor<CMYColor<Proportion8_t>> ACMY8_t;
	typedef TranslucentColor<CMYColor<Proportion16_t>> ACMY16_t;
	typedef TranslucentColor<CMYColor<Proportion32_t>> ACMY32_t;
	typedef TranslucentColor<CMYColor<Proportion64_t>> ACMY64_t;
	typedef TranslucentColor<CMYColor<FixedPoint16q15_t>> ACMYI16_t;
	typedef TranslucentColor<CMYColor<FixedPoint32q31_t>> ACMYI32_t;
	typedef TranslucentColor<CMYColor<FixedPoint64q63_t>> ACMYI64_t;
	typedef TranslucentColor<CMYColor<float>> ACMYF32_t;
	typedef TranslucentColor<CMYColor<double>> ACMYF64_t;
}
#endif // __stationaryorbit_graphics_core_cmycolor__
