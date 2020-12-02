//	stationaryorbit/graphics-core/rgbcolor
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
#ifndef __stationaryorbit_graphics_core_rgbcolor__
#define __stationaryorbit_graphics_core_rgbcolor__
#include "relativecolor.hpp"
#include "translucentcolor.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	///	赤(Red), 緑(Green), 青(Blue)の三要素によって表される色。
	template <class Tp>
	struct RGBColor final
	{
	public: // types
		typedef RelativeColor<Tp, 3UL> DataType;
		///	この型の各チャネルの値の表現のために内部で使用されている型。
		typedef typename DataType::ValueType ValueType;
	private: // contains
		DataType _value;
	public: // constructor
		///	既定の @a RGBColor を初期化します。
		constexpr RGBColor() = default;
		///	RGB値を指定して @a RGBColor を初期化します。
		constexpr RGBColor(const ValueType& r, const ValueType& g, const ValueType& b) : _value({r, g, b}) {}
		constexpr explicit RGBColor(const DataType& value) : _value(value) {}
		template <class fromT>
		constexpr explicit RGBColor(const RGBColor<fromT>& from) : RGBColor(DataType(from.Data())) {}
		constexpr RGBColor(const ZeroValue_t&) : _value(Zero) {}
	public: // member
		constexpr const DataType& Data() const { return _value; }
		///	この @a RGBColor の赤要素を取得します。
		constexpr const ValueType& R() const { return _value.Data()[0]; }
		///	この @a RGBColor の緑要素を取得します。
		constexpr const ValueType& G() const { return _value.Data()[1]; }
		///	この @a RGBColor の青要素を取得します。
		constexpr const ValueType& B() const { return _value.Data()[2]; }
		///	この @a RGBColor が正規化されているかを取得します。
		constexpr bool IsNormalized() const { return _value.IsNormalized(); }
		///	正規化した @a RGBColor を取得します。
		constexpr RGBColor<Tp> Normalize() const { return RGBColor<Tp>(_value.Normalize()); }

		[[nodiscard]] constexpr RGBColor<Tp> Add(const RGBColor<Tp>& other) const noexcept { return RGBColor<Tp>(_value.Add(other._value)); }
		[[nodiscard]] constexpr RGBColor<Tp> Subtract(const RGBColor<Tp>& other) const noexcept { return RGBColor<Tp>(_value.Subtract(other._value)); }
		[[nodiscard]] constexpr RGBColor<Tp> Multiply(const RGBColor<Tp>& other) const noexcept { return RGBColor<Tp>(_value.Multiply(other._value)); }
		[[nodiscard]] constexpr RGBColor<Tp> Multiply(const ValueType& other) const noexcept { return RGBColor<Tp>(_value.Multiply(other)); }
		[[nodiscard]] constexpr RGBColor<Tp> Divide(const RGBColor<Tp>& other) const noexcept { return RGBColor<Tp>(_value.Divide(other._value)); }
		[[nodiscard]] constexpr RGBColor<Tp> Divide(const ValueType& other) const noexcept { return RGBColor<Tp>(_value.Divide(other)); }
		[[nodiscard]] constexpr RGBColor<Tp> SaturateAdd(const RGBColor<Tp>& other) const noexcept { return RGBColor<Tp>(_value.SaturateAdd(other._value)); }
		[[nodiscard]] constexpr RGBColor<Tp> SaturateSubtract(const RGBColor<Tp>& other) const noexcept { return RGBColor<Tp>(_value.SaturateSubtract(other._value)); }
		[[nodiscard]] constexpr RGBColor<Tp> SaturateMultiply(const RGBColor<Tp>& other) const noexcept { return RGBColor<Tp>(_value.SaturateMultiply(other._value)); }
		[[nodiscard]] constexpr RGBColor<Tp> SaturateMultiply(const ValueType& other) const noexcept { return RGBColor<Tp>(_value.SaturateMultiply(other)); }
		[[nodiscard]] constexpr RGBColor<Tp> SaturateDivide(const RGBColor<Tp>& other) const noexcept { return RGBColor<Tp>(_value.SaturateDivide(other._value)); }
		[[nodiscard]] constexpr RGBColor<Tp> SaturateDivide(const ValueType& other) const noexcept { return RGBColor<Tp>(_value.SaturateDivide(other)); }
		[[nodiscard]] constexpr RGBColor<Tp> CheckedAdd(const RGBColor<Tp>& other) const { return RGBColor<Tp>(_value.CheckedAdd(other._value)); }
		[[nodiscard]] constexpr RGBColor<Tp> CheckedSubtract(const RGBColor<Tp>& other) const { return RGBColor<Tp>(_value.CheckedSubtract(other._value)); }
		[[nodiscard]] constexpr RGBColor<Tp> CheckedMultiply(const RGBColor<Tp>& other) const { return RGBColor<Tp>(_value.CheckedMultiply(other._value)); }
		[[nodiscard]] constexpr RGBColor<Tp> CheckedMultiply(const ValueType& other) const { return RGBColor<Tp>(_value.CheckedMultiply(other)); }
		[[nodiscard]] constexpr RGBColor<Tp> CheckedDivide(const RGBColor<Tp>& other) const { return RGBColor<Tp>(_value.CheckedDivide(other._value)); }
		[[nodiscard]] constexpr RGBColor<Tp> CheckedDivide(const ValueType& other) const { return RGBColor<Tp>(_value.CheckedDivide(other)); }
		[[nodiscard]] constexpr RGBColor<Tp> And(const RGBColor<Tp>& other) const noexcept { return RGBColor<Tp>(_value.And(other._value)); }
		[[nodiscard]] constexpr RGBColor<Tp> Or(const RGBColor<Tp>& other) const noexcept { return RGBColor<Tp>(_value.Or(other._value)); }
		[[nodiscard]] constexpr RGBColor<Tp> Not() const noexcept { return RGBColor<Tp>(_value.Not()); }
		[[nodiscard]] constexpr RGBColor<Tp> Xor(const RGBColor<Tp>& other) const noexcept { return RGBColor<Tp>(_value.Xor(other._value)); }

		constexpr RGBColor<Tp> operator+(const RGBColor<Tp>& other) const { return Add(other); }
		constexpr RGBColor<Tp> operator-(const RGBColor<Tp>& other) const { return Subtract(other); }
		constexpr RGBColor<Tp> operator*(const RGBColor<Tp>& other) const { return Multiply(other); }
		constexpr RGBColor<Tp> operator*(const ValueType& other) const { return Multiply(other); }
		constexpr RGBColor<Tp> operator/(const RGBColor<Tp>& other) const { return Divide(other); }
		constexpr RGBColor<Tp> operator/(const ValueType& other) const { return Divide(other); }
		constexpr RGBColor<Tp> operator~() const { return Not(); }
		constexpr RGBColor<Tp> operator|(const RGBColor<Tp>& other) const { return Or(other); }
		constexpr RGBColor<Tp> operator&(const RGBColor<Tp>& other) const { return And(other); }
		constexpr RGBColor<Tp> operator^(const RGBColor<Tp>& other) const { return Xor(other); }
		constexpr RGBColor<Tp>& operator+=(const RGBColor<Tp>& other) { return *this = *this + other; }
		constexpr RGBColor<Tp>& operator-=(const RGBColor<Tp>& other) { return *this = *this - other; }
		constexpr RGBColor<Tp>& operator*=(const RGBColor<Tp>& other) { return *this = *this * other; }
		constexpr RGBColor<Tp>& operator*=(const ValueType& other) { return *this = *this * other; }
		constexpr RGBColor<Tp>& operator/=(const RGBColor<Tp>& other) { return *this = *this / other; }
		constexpr RGBColor<Tp>& operator/=(const ValueType& other) { return *this = *this / other; }
		constexpr RGBColor<Tp>& operator|=(const RGBColor<Tp>& other) { return *this = *this | other; }
		constexpr RGBColor<Tp>& operator&=(const RGBColor<Tp>& other) { return *this = *this & other; }
		constexpr RGBColor<Tp>& operator^=(const RGBColor<Tp>& other) { return *this = *this ^ other; }

		constexpr bool Equals(const RGBColor<Tp>& other) const { return _value.Equals(other._value); }
		constexpr bool operator==(const RGBColor<Tp>& other) const { return Equals(other); }
		constexpr bool operator!=(const RGBColor<Tp>& other) const { return !Equals(other); }

		constexpr static RGBColor<Tp> Empty() { return RGBColor<Tp>(); }
	};

	extern template struct RGBColor<Proportion8_t>;
	extern template struct RGBColor<Proportion16_t>;
	extern template struct RGBColor<Proportion32_t>;
	extern template struct RGBColor<Proportion64_t>;
	extern template struct RGBColor<FixedPoint16q15_t>;
	extern template struct RGBColor<FixedPoint32q31_t>;
	extern template struct RGBColor<FixedPoint64q63_t>;
	extern template struct RGBColor<float>;
	extern template struct RGBColor<double>;
	extern template struct TranslucentColor<RGBColor<Proportion8_t>>;
	extern template struct TranslucentColor<RGBColor<Proportion16_t>>;
	extern template struct TranslucentColor<RGBColor<Proportion32_t>>;
	extern template struct TranslucentColor<RGBColor<Proportion64_t>>;
	extern template struct TranslucentColor<RGBColor<FixedPoint16q15_t>>;
	extern template struct TranslucentColor<RGBColor<FixedPoint32q31_t>>;
	extern template struct TranslucentColor<RGBColor<FixedPoint64q63_t>>;
	extern template struct TranslucentColor<RGBColor<float>>;
	extern template struct TranslucentColor<RGBColor<double>>;

	typedef RGBColor<Proportion8_t> RGB8_t;
	typedef RGBColor<Proportion16_t> RGB16_t;
	typedef RGBColor<Proportion32_t> RGB32_t;
	typedef RGBColor<Proportion64_t> RGB64_t;
	typedef RGBColor<FixedPoint16q15_t> RGBI16_t;
	typedef RGBColor<FixedPoint32q31_t> RGBI32_t;
	typedef RGBColor<FixedPoint64q63_t> RGBI64_t;
	typedef RGBColor<float> RGBF32_t;
	typedef RGBColor<double> RGBF64_t;
	typedef TranslucentColor<RGBColor<Proportion8_t>> ARGB8_t;
	typedef TranslucentColor<RGBColor<Proportion16_t>> ARGB16_t;
	typedef TranslucentColor<RGBColor<Proportion32_t>> ARGB32_t;
	typedef TranslucentColor<RGBColor<Proportion64_t>> ARGB64_t;
	typedef TranslucentColor<RGBColor<FixedPoint16q15_t>> ARGBI16_t;
	typedef TranslucentColor<RGBColor<FixedPoint32q31_t>> ARGBI32_t;
	typedef TranslucentColor<RGBColor<FixedPoint64q63_t>> ARGBI64_t;
	typedef TranslucentColor<RGBColor<float>> ARGBF32_t;
	typedef TranslucentColor<RGBColor<double>> ARGBF64_t;
}
#endif // __stationaryorbit_graphics_core_rgbcolor__
