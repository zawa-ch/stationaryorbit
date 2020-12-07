//	stationaryorbit/graphics-core/grayscalecolor
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
#ifndef __stationaryorbit_graphics_core_grayscalecolor__
#define __stationaryorbit_graphics_core_grayscalecolor__
#include "relativecolor.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	///
	template <class Tp>
	struct GrayScaleColor final
	{
	public: // types
		typedef RelativeColor<Tp, 1UL> DataType;
		///	この型の各チャネルの値の表現のために内部で使用されている型。
		typedef typename DataType::ValueType ValueType;
	private:
		DataType _value;
	public:
		///	既定の @a GrayScaleColor を初期化します。
		constexpr GrayScaleColor() = default;
		///	輝度を指定して @a GrayScaleColor を初期化します。
		constexpr explicit GrayScaleColor(const ValueType& luminance) : _value({luminance}) {}
		constexpr explicit GrayScaleColor(const DataType& value) : _value(value) {}
		template <class fromT>
		constexpr explicit GrayScaleColor(const GrayScaleColor<fromT>& from) : GrayScaleColor(DataType(from.Data())) {}
		constexpr GrayScaleColor(const ZeroValue_t&) : _value(Zero) {}
	public:
		constexpr const DataType& Data() const { return _value; }
		///	この @a GrayScaleColor の輝度コンポーネントを取得します。
		constexpr ValueType Luminance() const { return _value.Data()[0]; }
		///	この @a GrayScaleColor が正規化されているかを取得します。
		constexpr bool IsNormalized() const { return _value.IsNormalized(); }
		///	正規化した @a GrayScaleColor を取得します。
		constexpr GrayScaleColor<Tp> Normalize() const { return GrayScaleColor<Tp>(_value.Normalize()); }

		[[nodiscard]] constexpr GrayScaleColor<Tp> Promote() const noexcept { return GrayScaleColor<Tp>(_value.Promote()); }
		[[nodiscard]] constexpr GrayScaleColor<Tp> Invert() const noexcept { return GrayScaleColor<Tp>(_value.Invert()); }
		[[nodiscard]] constexpr GrayScaleColor<Tp> Add(const GrayScaleColor<Tp>& other) const noexcept { return GrayScaleColor<Tp>(_value.Add(other._value)); }
		[[nodiscard]] constexpr GrayScaleColor<Tp> Subtract(const GrayScaleColor<Tp>& other) const noexcept { return GrayScaleColor<Tp>(_value.Subtract(other._value)); }
		[[nodiscard]] constexpr GrayScaleColor<Tp> Multiply(const GrayScaleColor<Tp>& other) const noexcept { return GrayScaleColor<Tp>(_value.Multiply(other._value)); }
		[[nodiscard]] constexpr GrayScaleColor<Tp> Multiply(const ValueType& other) const noexcept { return GrayScaleColor<Tp>(_value.Multiply(other.Data())); }
		[[nodiscard]] constexpr GrayScaleColor<Tp> Divide(const GrayScaleColor<Tp>& other) const noexcept { return GrayScaleColor<Tp>(_value.Divide(other._value)); }
		[[nodiscard]] constexpr GrayScaleColor<Tp> Divide(const ValueType& other) const noexcept { return GrayScaleColor<Tp>(_value.Divide(other.Data())); }
		[[nodiscard]] constexpr GrayScaleColor<Tp> SaturateAdd(const GrayScaleColor<Tp>& other) const noexcept { return GrayScaleColor<Tp>(_value.SaturateAdd(other._value)); }
		[[nodiscard]] constexpr GrayScaleColor<Tp> SaturateSubtract(const GrayScaleColor<Tp>& other) const noexcept { return GrayScaleColor<Tp>(_value.SaturateSubtract(other._value)); }
		[[nodiscard]] constexpr GrayScaleColor<Tp> SaturateMultiply(const GrayScaleColor<Tp>& other) const noexcept { return GrayScaleColor<Tp>(_value.SaturateMultiply(other._value)); }
		[[nodiscard]] constexpr GrayScaleColor<Tp> SaturateMultiply(const ValueType& other) const noexcept { return GrayScaleColor<Tp>(_value.SaturateMultiply(other.Data())); }
		[[nodiscard]] constexpr GrayScaleColor<Tp> SaturateDivide(const GrayScaleColor<Tp>& other) const noexcept { return GrayScaleColor<Tp>(_value.SaturateDivide(other._value)); }
		[[nodiscard]] constexpr GrayScaleColor<Tp> SaturateDivide(const ValueType& other) const noexcept { return GrayScaleColor<Tp>(_value.SaturateDivide(other.Data())); }
		[[nodiscard]] constexpr GrayScaleColor<Tp> CheckedAdd(const GrayScaleColor<Tp>& other) const { return GrayScaleColor<Tp>(_value.CheckedAdd(other._value)); }
		[[nodiscard]] constexpr GrayScaleColor<Tp> CheckedSubtract(const GrayScaleColor<Tp>& other) const { return GrayScaleColor<Tp>(_value.CheckedSubtract(other._value)); }
		[[nodiscard]] constexpr GrayScaleColor<Tp> CheckedMultiply(const GrayScaleColor<Tp>& other) const { return GrayScaleColor<Tp>(_value.CheckedMultiply(other._value)); }
		[[nodiscard]] constexpr GrayScaleColor<Tp> CheckedMultiply(const ValueType& other) const { return GrayScaleColor<Tp>(_value.CheckedMultiply(other.Data())); }
		[[nodiscard]] constexpr GrayScaleColor<Tp> CheckedDivide(const GrayScaleColor<Tp>& other) const { return GrayScaleColor<Tp>(_value.CheckedDivide(other._value)); }
		[[nodiscard]] constexpr GrayScaleColor<Tp> CheckedDivide(const ValueType& other) const { return GrayScaleColor<Tp>(_value.CheckedDivide(other.Data())); }
		[[nodiscard]] constexpr GrayScaleColor<Tp> And(const GrayScaleColor<Tp>& other) const noexcept { return GrayScaleColor<Tp>(_value.And(other._value)); }
		[[nodiscard]] constexpr GrayScaleColor<Tp> Or(const GrayScaleColor<Tp>& other) const noexcept { return GrayScaleColor<Tp>(_value.Or(other._value)); }
		[[nodiscard]] constexpr GrayScaleColor<Tp> Not() const noexcept { return GrayScaleColor<Tp>(_value.Not()); }
		[[nodiscard]] constexpr GrayScaleColor<Tp> Xor(const GrayScaleColor<Tp>& other) const noexcept { return GrayScaleColor<Tp>(_value.Xor(other._value)); }

		constexpr GrayScaleColor<Tp> operator+() const { return Promote(); }
		constexpr GrayScaleColor<Tp> operator-() const { return Invert(); }
		constexpr GrayScaleColor<Tp> operator+(const GrayScaleColor<Tp>& other) const { return Add(other); }
		constexpr GrayScaleColor<Tp> operator-(const GrayScaleColor<Tp>& other) const { return Subtract(other); }
		constexpr GrayScaleColor<Tp> operator*(const GrayScaleColor<Tp>& other) const { return Multiply(other); }
		constexpr GrayScaleColor<Tp> operator*(const ValueType& other) const { return Multiply(other); }
		constexpr GrayScaleColor<Tp> operator/(const GrayScaleColor<Tp>& other) const { return Divide(other); }
		constexpr GrayScaleColor<Tp> operator/(const ValueType& other) const { return Divide(other); }
		constexpr GrayScaleColor<Tp> operator~() const { return Not(); }
		constexpr GrayScaleColor<Tp> operator|(const GrayScaleColor<Tp>& other) const { return Or(other); }
		constexpr GrayScaleColor<Tp> operator&(const GrayScaleColor<Tp>& other) const { return And(other); }
		constexpr GrayScaleColor<Tp> operator^(const GrayScaleColor<Tp>& other) const { return Xor(other); }
		constexpr GrayScaleColor<Tp>& operator+=(const GrayScaleColor<Tp>& other) { return *this = *this + other; }
		constexpr GrayScaleColor<Tp>& operator-=(const GrayScaleColor<Tp>& other) { return *this = *this - other; }
		constexpr GrayScaleColor<Tp>& operator*=(const GrayScaleColor<Tp>& other) { return *this = *this * other; }
		constexpr GrayScaleColor<Tp>& operator*=(const ValueType& other) { return *this = *this * other; }
		constexpr GrayScaleColor<Tp>& operator/=(const GrayScaleColor<Tp>& other) { return *this = *this / other; }
		constexpr GrayScaleColor<Tp>& operator/=(const ValueType& other) { return *this = *this / other; }
		constexpr GrayScaleColor<Tp>& operator|=(const GrayScaleColor<Tp>& other) { return *this = *this | other; }
		constexpr GrayScaleColor<Tp>& operator&=(const GrayScaleColor<Tp>& other) { return *this = *this & other; }
		constexpr GrayScaleColor<Tp>& operator^=(const GrayScaleColor<Tp>& other) { return *this = *this ^ other; }

		constexpr bool Equals(const GrayScaleColor<Tp>& other) const { return _value.Equals(other._value); }
		constexpr bool operator==(const GrayScaleColor<Tp>& other) const { return Equals(other); }
		constexpr bool operator!=(const GrayScaleColor<Tp>& other) const { return !Equals(other); }

		constexpr static GrayScaleColor<Tp> Empty() { return GrayScaleColor<Tp>(); }
	};

	extern template struct GrayScaleColor<Proportion1_t>;
	extern template struct GrayScaleColor<Proportion8_t>;
	extern template struct GrayScaleColor<Proportion16_t>;
	extern template struct GrayScaleColor<Proportion32_t>;
	extern template struct GrayScaleColor<Proportion64_t>;
	extern template struct GrayScaleColor<FixedPoint16q15_t>;
	extern template struct GrayScaleColor<FixedPoint32q31_t>;
	extern template struct GrayScaleColor<FixedPoint64q63_t>;
	extern template struct GrayScaleColor<float>;
	extern template struct GrayScaleColor<double>;

	typedef GrayScaleColor<Proportion1_t> GrayScale1_t;
	typedef GrayScaleColor<Proportion8_t> GrayScale8_t;
	typedef GrayScaleColor<Proportion16_t> GrayScale16_t;
	typedef GrayScaleColor<Proportion32_t> GrayScale32_t;
	typedef GrayScaleColor<Proportion64_t> GrayScale64_t;
	typedef GrayScaleColor<FixedPoint16q15_t> GrayScaleI16_t;
	typedef GrayScaleColor<FixedPoint32q31_t> GrayScaleI32_t;
	typedef GrayScaleColor<FixedPoint64q63_t> GrayScaleI64_t;
	typedef GrayScaleColor<float> GrayScaleF32_t;
	typedef GrayScaleColor<double> GrayScaleF64_t;
}
#endif // __stationaryorbit_graphics_core_grayscalecolor__
