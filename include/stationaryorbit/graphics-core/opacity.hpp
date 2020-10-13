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
		constexpr Opacity() : _value() {}
		constexpr explicit Opacity(const ValueType& value) : _value(value) {}
		template<class fromT>
		constexpr explicit Opacity(const Opacity<fromT>& from) : _value(ValueType(from.Data())) {}
		constexpr Opacity(const ZeroValue_t&) : _value(Zero) {}

		[[nodiscard]] constexpr const ValueType& Data() const noexcept { return _value; }

		[[nodiscard]] constexpr Opacity<Tp> Add(const Opacity<Tp>& other) const noexcept { return _value.Add(other); }
		[[nodiscard]] constexpr Opacity<Tp> Subtract(const Opacity<Tp>& other) const noexcept { return _value.Subtract(other); }
		[[nodiscard]] constexpr Opacity<Tp> Multiply(const Opacity<Tp>& other) const noexcept { return _value.Multiply(other); }
		[[nodiscard]] constexpr Opacity<Tp> Divide(const Opacity<Tp>& other) const noexcept { return _value.Divide(other); }
		[[nodiscard]] constexpr Opacity<Tp> SaturateAdd(const Opacity<Tp>& other) const noexcept { return _value.SaturateAdd(other); }
		[[nodiscard]] constexpr Opacity<Tp> SaturateSubtract(const Opacity<Tp>& other) const noexcept { return _value.SaturateSubtract(other); }
		[[nodiscard]] constexpr Opacity<Tp> SaturateMultiply(const Opacity<Tp>& other) const noexcept { return _value.SaturateMultiply(other); }
		[[nodiscard]] constexpr Opacity<Tp> SaturateDivide(const Opacity<Tp>& other) const noexcept { return _value.SaturateDivide(other); }
		[[nodiscard]] constexpr Opacity<Tp> CheckedAdd(const Opacity<Tp>& other) const { return _value.CheckedAdd(other); }
		[[nodiscard]] constexpr Opacity<Tp> CheckedSubtract(const Opacity<Tp>& other) const { return _value.CheckedSubtract(other); }
		[[nodiscard]] constexpr Opacity<Tp> CheckedMultiply(const Opacity<Tp>& other) const { return _value.CheckedMultiply(other); }
		[[nodiscard]] constexpr Opacity<Tp> CheckedDivide(const Opacity<Tp>& other) const { return _value.CheckedDivide(other); }
		[[nodiscard]] constexpr Opacity<Tp> And(const Opacity<Tp>& other) const noexcept { return _value.And(other); }
		[[nodiscard]] constexpr Opacity<Tp> Or(const Opacity<Tp>& other) const noexcept { return _value.Or(other); }
		[[nodiscard]] constexpr Opacity<Tp> Not() const noexcept { return _value.Not(); }
		[[nodiscard]] constexpr Opacity<Tp> Xor(const Opacity<Tp>& other) const noexcept { return _value.Xor(other); }
		[[nodiscard]] constexpr bool Equals(const Opacity<Tp>& other) const noexcept { return _value.Equals(other); }
		[[nodiscard]] constexpr bool Compare(const Opacity<Tp>& other) const noexcept { return _value.Compare(other); }

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
		constexpr Opacity<Tp>& operator=(const Opacity<Tp>&) = default;
		constexpr Opacity<Tp>& operator=(Opacity<Tp>&&) = default;
	};
}
#endif // __stationaryorbit_graphics_core_opacity__
