//	stationaryorbit/graphics-core/yuvcolor
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
#ifndef __stationaryorbit_graphics_core_yuvcolor__
#define __stationaryorbit_graphics_core_yuvcolor__
#include "relativecolor.hpp"
#include "translucentcolor.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	///	輝度と二つの色差によって表される色。
	template <class Tp>
	struct YUVColor final
	{
	public: // types
		typedef RelativeColor<Tp, 3UL> DataType;
		///	この型の各チャネルの値の表現のために内部で使用されている型。
		typedef typename DataType::ValueType ValueType;
	private: // contains
		DataType _value;
	public: // constructor
		///	既定の @a YUVColor を初期化します。
		constexpr YUVColor() = default;
		///	RGB値を指定して @a YUVColor を初期化します。
		constexpr YUVColor(const ValueType& y, const ValueType& u, const ValueType& v) : _value({y, u, v}) {}
		constexpr explicit YUVColor(const DataType& value) : _value(value) {}
		template <class fromT>
		constexpr explicit YUVColor(const YUVColor<fromT>& from) : YUVColor(DataType(from.Data())) {}
		constexpr YUVColor(const ZeroValue_t&) : _value(Zero) {}
	public: // member
		constexpr const DataType& Data() const { return _value; }
		///	この @a YUVColor の輝度要素を取得します。
		constexpr const ValueType& Y() const { return _value.Data()[0]; }
		///	この @a YUVColor の赤色差要素を取得します。
		constexpr const ValueType& U() const { return _value.Data()[1]; }
		///	この @a YUVColor の青色差要素を取得します。
		constexpr const ValueType& V() const { return _value.Data()[2]; }
		///	この @a YUVColor が正規化されているかを取得します。
		constexpr bool IsNormalized() const { return _value.IsNormalized(); }
		///	正規化した @a YUVColor を取得します。
		constexpr YUVColor<Tp> Normalize() const { return YUVColor<Tp>(_value.Normalize()); }

		[[nodiscard]] constexpr YUVColor<Tp> SaturateAdd(const YUVColor<Tp>& other) const noexcept { return YUVColor<Tp>(_value.SaturateAdd(other._value)); }
		[[nodiscard]] constexpr YUVColor<Tp> SaturateSubtract(const YUVColor<Tp>& other) const noexcept { return YUVColor<Tp>(_value.SaturateSubtract(other._value)); }
		[[nodiscard]] constexpr YUVColor<Tp> SaturateMultiply(const YUVColor<Tp>& other) const noexcept { return YUVColor<Tp>(_value.SaturateMultiply(other._value)); }
		[[nodiscard]] constexpr YUVColor<Tp> SaturateMultiply(const ValueType& other) const noexcept { return YUVColor<Tp>(_value.SaturateMultiply(other)); }
		[[nodiscard]] constexpr YUVColor<Tp> SaturateDivide(const YUVColor<Tp>& other) const noexcept { return YUVColor<Tp>(_value.SaturateDivide(other._value)); }
		[[nodiscard]] constexpr YUVColor<Tp> SaturateDivide(const ValueType& other) const noexcept { return YUVColor<Tp>(_value.SaturateDivide(other)); }
		[[nodiscard]] constexpr YUVColor<Tp> CheckedAdd(const YUVColor<Tp>& other) const { return YUVColor<Tp>(_value.CheckedAdd(other._value)); }
		[[nodiscard]] constexpr YUVColor<Tp> CheckedSubtract(const YUVColor<Tp>& other) const { return YUVColor<Tp>(_value.CheckedSubtract(other._value)); }
		[[nodiscard]] constexpr YUVColor<Tp> CheckedMultiply(const YUVColor<Tp>& other) const { return YUVColor<Tp>(_value.CheckedMultiply(other._value)); }
		[[nodiscard]] constexpr YUVColor<Tp> CheckedMultiply(const ValueType& other) const { return YUVColor<Tp>(_value.CheckedMultiply(other)); }
		[[nodiscard]] constexpr YUVColor<Tp> CheckedDivide(const YUVColor<Tp>& other) const { return YUVColor<Tp>(_value.CheckedDivide(other._value)); }
		[[nodiscard]] constexpr YUVColor<Tp> CheckedDivide(const ValueType& other) const { return YUVColor<Tp>(_value.CheckedDivide(other)); }

		constexpr YUVColor<Tp> operator+() const { return YUVColor<Tp>(+_value); }
		constexpr YUVColor<Tp> operator-() const { return YUVColor<Tp>(-_value); }
		constexpr YUVColor<Tp> operator+(const YUVColor<Tp>& other) const { return YUVColor<Tp>(_value + other._value); }
		constexpr YUVColor<Tp> operator-(const YUVColor<Tp>& other) const { return YUVColor<Tp>(_value - other._value); }
		constexpr YUVColor<Tp> operator*(const YUVColor<Tp>& other) const { return YUVColor<Tp>(_value * other._value); }
		constexpr YUVColor<Tp> operator*(const ValueType& other) const { return YUVColor<Tp>(_value * other); }
		constexpr YUVColor<Tp> operator/(const YUVColor<Tp>& other) const { return YUVColor<Tp>(_value / other._value); }
		constexpr YUVColor<Tp> operator/(const ValueType& other) const { return YUVColor<Tp>(_value / other); }
		constexpr YUVColor<Tp> operator~() const { return YUVColor<Tp>(~_value); }
		constexpr YUVColor<Tp> operator&(const YUVColor<Tp>& other) const { return YUVColor<Tp>(_value & other._value); }
		constexpr YUVColor<Tp> operator|(const YUVColor<Tp>& other) const { return YUVColor<Tp>(_value | other._value); }
		constexpr YUVColor<Tp> operator^(const YUVColor<Tp>& other) const { return YUVColor<Tp>(_value ^ other._value); }
		constexpr YUVColor<Tp>& operator+=(const YUVColor<Tp>& other) { return *this = *this + other; }
		constexpr YUVColor<Tp>& operator-=(const YUVColor<Tp>& other) { return *this = *this - other; }
		constexpr YUVColor<Tp>& operator*=(const YUVColor<Tp>& other) { return *this = *this * other; }
		constexpr YUVColor<Tp>& operator*=(const ValueType& other) { return *this = *this * other; }
		constexpr YUVColor<Tp>& operator/=(const YUVColor<Tp>& other) { return *this = *this / other; }
		constexpr YUVColor<Tp>& operator/=(const ValueType& other) { return *this = *this / other; }
		constexpr YUVColor<Tp>& operator|=(const YUVColor<Tp>& other) { return *this = *this | other; }
		constexpr YUVColor<Tp>& operator&=(const YUVColor<Tp>& other) { return *this = *this & other; }
		constexpr YUVColor<Tp>& operator^=(const YUVColor<Tp>& other) { return *this = *this ^ other; }

		constexpr bool Equals(const YUVColor<Tp>& other) const { return _value.Equals(other._value); }
		constexpr bool operator==(const YUVColor<Tp>& other) const { return Equals(other); }
		constexpr bool operator!=(const YUVColor<Tp>& other) const { return !Equals(other); }

		constexpr static YUVColor<Tp> Empty() { return YUVColor<Tp>(); }
	};

	extern template struct YUVColor<Proportion8_t>;
	extern template struct YUVColor<Proportion16_t>;
	extern template struct YUVColor<Proportion32_t>;
	extern template struct YUVColor<Proportion64_t>;
	extern template struct YUVColor<FixedPoint16q15_t>;
	extern template struct YUVColor<FixedPoint32q31_t>;
	extern template struct YUVColor<FixedPoint64q63_t>;
	extern template struct YUVColor<float>;
	extern template struct YUVColor<double>;
	extern template struct TranslucentColor<YUVColor<Proportion8_t>>;
	extern template struct TranslucentColor<YUVColor<Proportion16_t>>;
	extern template struct TranslucentColor<YUVColor<Proportion32_t>>;
	extern template struct TranslucentColor<YUVColor<Proportion64_t>>;
	extern template struct TranslucentColor<YUVColor<FixedPoint16q15_t>>;
	extern template struct TranslucentColor<YUVColor<FixedPoint32q31_t>>;
	extern template struct TranslucentColor<YUVColor<FixedPoint64q63_t>>;
	extern template struct TranslucentColor<YUVColor<float>>;
	extern template struct TranslucentColor<YUVColor<double>>;

	typedef YUVColor<Proportion8_t> YUV8_t;
	typedef YUVColor<Proportion16_t> YUV16_t;
	typedef YUVColor<Proportion32_t> YUV32_t;
	typedef YUVColor<Proportion64_t> YUV64_t;
	typedef YUVColor<FixedPoint16q15_t> YUVI16_t;
	typedef YUVColor<FixedPoint32q31_t> YUVI32_t;
	typedef YUVColor<FixedPoint64q63_t> YUVI64_t;
	typedef YUVColor<float> YUVF32_t;
	typedef YUVColor<double> YUVF64_t;
	typedef TranslucentColor<YUVColor<Proportion8_t>> AYUV8_t;
	typedef TranslucentColor<YUVColor<Proportion16_t>> AYUV16_t;
	typedef TranslucentColor<YUVColor<Proportion32_t>> AYUV32_t;
	typedef TranslucentColor<YUVColor<Proportion64_t>> AYUV64_t;
	typedef TranslucentColor<YUVColor<FixedPoint16q15_t>> AYUVI16_t;
	typedef TranslucentColor<YUVColor<FixedPoint32q31_t>> AYUVI32_t;
	typedef TranslucentColor<YUVColor<FixedPoint64q63_t>> AYUVI64_t;
	typedef TranslucentColor<YUVColor<float>> AYUVF32_t;
	typedef TranslucentColor<YUVColor<double>> AYUVF64_t;
}
#endif // __stationaryorbit_graphics_core_yuvcolor__