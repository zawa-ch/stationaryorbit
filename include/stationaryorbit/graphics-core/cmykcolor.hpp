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
#include "relativecolor.hpp"
#include "translucentcolor.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	///	シアン(Cyan), マゼンタ(Magenta), イエロー(Yellow), キー プレート(Key plate)の四要素によって表される色。
	template <class Tp>
	struct CMYKColor final
	{
	public: // types
		///	この型の各チャネルの値の表現のために内部で使用されている型。
		typedef typename RelativeColor<Tp, 4UL>::ValueType ValueType;
	private: // contains
		RelativeColor<Tp, 4UL> _value;
	public: // constructor
		///	既定の @a CMYKColor を初期化します。
		constexpr CMYKColor() : _value() {}
		///	CMYK値を指定して @a CMYKColor を初期化します。
		constexpr CMYKColor(ValueType c, ValueType m, ValueType y, ValueType k) : _value({c, m, y, k}) {}
		constexpr explicit CMYKColor(const RelativeColor<Tp, 4UL>& value) : _value(value) {}
		template <class fromT>
		constexpr explicit CMYKColor(const CMYKColor<fromT>& from) : CMYKColor(RelativeColor<Tp, 4UL>(from.Data())) {}
		constexpr CMYKColor(const ZeroValue_t&) : _value(Zero) {}
	public: // member
		constexpr const RelativeColor<Tp, 3U>& Data() const { return _value; }
		///	この @a CMYKColor のシアンのコンポーネントを取得します。
		constexpr const ValueType& C() const { return _value.Data()[0]; }
		///	この @a CMYKColor のマゼンタのコンポーネントを取得します。
		constexpr const ValueType& M() const { return _value.Data()[1]; }
		///	この @a CMYKColor のイエローのコンポーネントを取得します。
		constexpr const ValueType& Y() const { return _value.Data()[2]; }
		///	この @a CMYKColor のキープレート(黒色)のコンポーネントを取得します。
		constexpr const ValueType& K() const { return _value.Data()[3]; }
		///	この @a CMYKColor が正規化されているかを取得します。
		constexpr bool IsNormalized() const { return _value.IsNormalized(); }
		///	正規化した @a CMYKColor を取得します。
		constexpr CMYKColor<Tp> Normalize() const { return CMYKColor<Tp>(_value.Normalize()); }

		[[nodiscard]] constexpr CMYKColor<Tp> Add(const CMYKColor<Tp>& other) const noexcept { return CMYKColor<Tp>(_value.Add(other._value)); }
		[[nodiscard]] constexpr CMYKColor<Tp> Subtract(const CMYKColor<Tp>& other) const noexcept { return CMYKColor<Tp>(_value.Subtract(other._value)); }
		[[nodiscard]] constexpr CMYKColor<Tp> Multiply(const CMYKColor<Tp>& other) const noexcept { return CMYKColor<Tp>(_value.Multiply(other._value)); }
		[[nodiscard]] constexpr CMYKColor<Tp> Multiply(const ValueType& other) const noexcept { return CMYKColor<Tp>(_value.Multiply(other._value)); }
		[[nodiscard]] constexpr CMYKColor<Tp> Divide(const CMYKColor<Tp>& other) const noexcept { return CMYKColor<Tp>(_value.Divide(other._value)); }
		[[nodiscard]] constexpr CMYKColor<Tp> Divide(const ValueType& other) const noexcept { return CMYKColor<Tp>(_value.Divide(other._value)); }
		[[nodiscard]] constexpr CMYKColor<Tp> SaturateAdd(const CMYKColor<Tp>& other) const noexcept { return CMYKColor<Tp>(_value.SaturateAdd(other._value)); }
		[[nodiscard]] constexpr CMYKColor<Tp> SaturateSubtract(const CMYKColor<Tp>& other) const noexcept { return CMYKColor<Tp>(_value.SaturateSubtract(other._value)); }
		[[nodiscard]] constexpr CMYKColor<Tp> SaturateMultiply(const CMYKColor<Tp>& other) const noexcept { return CMYKColor<Tp>(_value.SaturateMultiply(other._value)); }
		[[nodiscard]] constexpr CMYKColor<Tp> SaturateMultiply(const ValueType& other) const noexcept { return CMYKColor<Tp>(_value.SaturateMultiply(other._value)); }
		[[nodiscard]] constexpr CMYKColor<Tp> SaturateDivide(const CMYKColor<Tp>& other) const noexcept { return CMYKColor<Tp>(_value.SaturateDivide(other._value)); }
		[[nodiscard]] constexpr CMYKColor<Tp> SaturateDivide(const ValueType& other) const noexcept { return CMYKColor<Tp>(_value.SaturateDivide(other._value)); }
		[[nodiscard]] constexpr CMYKColor<Tp> CheckedAdd(const CMYKColor<Tp>& other) const { return CMYKColor<Tp>(_value.CheckedAdd(other._value)); }
		[[nodiscard]] constexpr CMYKColor<Tp> CheckedSubtract(const CMYKColor<Tp>& other) const { return CMYKColor<Tp>(_value.CheckedSubtract(other._value)); }
		[[nodiscard]] constexpr CMYKColor<Tp> CheckedMultiply(const CMYKColor<Tp>& other) const { return CMYKColor<Tp>(_value.CheckedMultiply(other._value)); }
		[[nodiscard]] constexpr CMYKColor<Tp> CheckedMultiply(const ValueType& other) const { return CMYKColor<Tp>(_value.CheckedMultiply(other._value)); }
		[[nodiscard]] constexpr CMYKColor<Tp> CheckedDivide(const CMYKColor<Tp>& other) const { return CMYKColor<Tp>(_value.CheckedDivide(other._value)); }
		[[nodiscard]] constexpr CMYKColor<Tp> CheckedDivide(const ValueType& other) const { return CMYKColor<Tp>(_value.CheckedDivide(other._value)); }
		[[nodiscard]] constexpr CMYKColor<Tp> And(const CMYKColor<Tp>& other) const noexcept { return CMYKColor<Tp>(_value.And(other._value)); }
		[[nodiscard]] constexpr CMYKColor<Tp> Or(const CMYKColor<Tp>& other) const noexcept { return CMYKColor<Tp>(_value.Or(other._value)); }
		[[nodiscard]] constexpr CMYKColor<Tp> Not() const noexcept { return CMYKColor<Tp>(_value.Not()); }
		[[nodiscard]] constexpr CMYKColor<Tp> Xor(const CMYKColor<Tp>& other) const noexcept { return CMYKColor<Tp>(_value.Xor(other._value)); }

		constexpr CMYKColor<Tp> operator+(const CMYKColor<Tp>& other) const { return Add(other); }
		constexpr CMYKColor<Tp> operator-(const CMYKColor<Tp>& other) const { return Subtract(other); }
		constexpr CMYKColor<Tp> operator*(const CMYKColor<Tp>& other) const { return Multiply(other); }
		constexpr CMYKColor<Tp> operator*(const ValueType& other) const { return Multiply(other); }
		constexpr CMYKColor<Tp> operator/(const CMYKColor<Tp>& other) const { return Divide(other); }
		constexpr CMYKColor<Tp> operator/(const ValueType& other) const { return Divide(other); }
		constexpr CMYKColor<Tp> operator~() const { return Not(); }
		constexpr CMYKColor<Tp> operator|(const CMYKColor<Tp>& other) const { return Or(other); }
		constexpr CMYKColor<Tp> operator&(const CMYKColor<Tp>& other) const { return And(other); }
		constexpr CMYKColor<Tp> operator^(const CMYKColor<Tp>& other) const { return Xor(other); }
		constexpr CMYKColor<Tp>& operator+=(const CMYKColor<Tp>& other) { return *this = *this + other; }
		constexpr CMYKColor<Tp>& operator-=(const CMYKColor<Tp>& other) { return *this = *this - other; }
		constexpr CMYKColor<Tp>& operator*=(const CMYKColor<Tp>& other) { return *this = *this * other; }
		constexpr CMYKColor<Tp>& operator*=(const ValueType& other) { return *this = *this * other; }
		constexpr CMYKColor<Tp>& operator/=(const CMYKColor<Tp>& other) { return *this = *this / other; }
		constexpr CMYKColor<Tp>& operator/=(const ValueType& other) { return *this = *this / other; }
		constexpr CMYKColor<Tp>& operator|=(const CMYKColor<Tp>& other) { return *this = *this | other; }
		constexpr CMYKColor<Tp>& operator&=(const CMYKColor<Tp>& other) { return *this = *this & other; }
		constexpr CMYKColor<Tp>& operator^=(const CMYKColor<Tp>& other) { return *this = *this ^ other; }

		constexpr bool Equals(const CMYKColor<Tp>& other) const { return _value.Equals(other._value); }
		constexpr bool operator==(const CMYKColor<Tp>& other) const { return Equals(other); }
		constexpr bool operator!=(const CMYKColor<Tp>& other) const { return !Equals(other); }

		constexpr static CMYKColor<Tp> Empty() { return CMYKColor<Tp>(); }
	};

	extern template struct CMYKColor<Proportion8_t>;
	extern template struct CMYKColor<Proportion16_t>;
	extern template struct CMYKColor<Proportion32_t>;
	extern template struct CMYKColor<Proportion64_t>;
	extern template struct CMYKColor<FixedPoint16q15_t>;
	extern template struct CMYKColor<FixedPoint32q31_t>;
	extern template struct CMYKColor<FixedPoint64q63_t>;
	extern template struct CMYKColor<float>;
	extern template struct CMYKColor<double>;
	extern template struct TranslucentColor<CMYKColor<Proportion8_t>>;
	extern template struct TranslucentColor<CMYKColor<Proportion16_t>>;
	extern template struct TranslucentColor<CMYKColor<Proportion32_t>>;
	extern template struct TranslucentColor<CMYKColor<Proportion64_t>>;
	extern template struct TranslucentColor<CMYKColor<FixedPoint16q15_t>>;
	extern template struct TranslucentColor<CMYKColor<FixedPoint32q31_t>>;
	extern template struct TranslucentColor<CMYKColor<FixedPoint64q63_t>>;
	extern template struct TranslucentColor<CMYKColor<float>>;
	extern template struct TranslucentColor<CMYKColor<double>>;

	typedef CMYKColor<Proportion8_t> CMYK8_t;
	typedef CMYKColor<Proportion16_t> CMYK16_t;
	typedef CMYKColor<Proportion32_t> CMYK32_t;
	typedef CMYKColor<Proportion64_t> CMYK64_t;
	typedef CMYKColor<FixedPoint16q15_t> CMYKI16_t;
	typedef CMYKColor<FixedPoint32q31_t> CMYKI32_t;
	typedef CMYKColor<FixedPoint64q63_t> CMYKI64_t;
	typedef CMYKColor<float> CMYKF32_t;
	typedef CMYKColor<double> CMYKF64_t;
	typedef TranslucentColor<CMYKColor<Proportion8_t>> ACMYK8_t;
	typedef TranslucentColor<CMYKColor<Proportion16_t>> ACMYK16_t;
	typedef TranslucentColor<CMYKColor<Proportion32_t>> ACMYK32_t;
	typedef TranslucentColor<CMYKColor<Proportion64_t>> ACMYK64_t;
	typedef TranslucentColor<CMYKColor<FixedPoint16q15_t>> ACMYKI16_t;
	typedef TranslucentColor<CMYKColor<FixedPoint32q31_t>> ACMYKI32_t;
	typedef TranslucentColor<CMYKColor<FixedPoint64q63_t>> ACMYKI64_t;
	typedef TranslucentColor<CMYKColor<float>> ACMYKF32_t;
	typedef TranslucentColor<CMYKColor<double>> ACMYKF64_t;
}
#endif // __stationaryorbit_graphics_core_cmykcolor__
