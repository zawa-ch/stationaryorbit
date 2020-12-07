//	stationaryorbit/graphics-core/relativecolor
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
#ifndef __stationaryorbit_graphics_core_relativecolor__
#define __stationaryorbit_graphics_core_relativecolor__
#include <array>
#include <functional>
#include "stationaryorbit/core.traits.hpp"
#include "colortraits.hpp"
#include "channelvalue.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	template<class Tp, size_t N>
	struct RelativeColor final
	{
	public:
		typedef ChannelValue<Tp> ValueType;
		typedef std::array<ValueType, N> DataType;
	private:
		DataType _value;
	public:
		constexpr RelativeColor() = default;
		constexpr explicit RelativeColor(const DataType& list) : _value(list) {}
		template<class fromT>
		constexpr explicit RelativeColor(const RelativeColor<fromT, N>& from) : _value(convert(from.Data())) {}
		constexpr RelativeColor(const ZeroValue_t&) : RelativeColor(Expand(ValueType(Zero))) {}

		[[nodiscard]] constexpr const DataType& Data() const { return _value; }
		[[nodiscard]] constexpr bool IsNormalized() const noexcept
		{
			for(const auto& item: _value) { if (!item.IsNormalized()) { return false; } }
			return true;
		}
		[[nodiscard]] constexpr RelativeColor<Tp, N> Normalize() const noexcept { return Apply([](const auto& item)->ValueType { return item.Normalize(); }); }

		[[nodiscard]] constexpr RelativeColor<Tp, N> Promote() const noexcept { return Apply([](const auto& item)->ValueType { return item.Promote(); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> Invert() const noexcept { return Apply([](const auto& item)->ValueType { return item.Invert(); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> Add(const RelativeColor<Tp, N>& other) const noexcept { return Merge(other, [](const auto& item, const auto& value)->ValueType { return item.Add(value); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> Subtract(const RelativeColor<Tp, N>& other) const noexcept { return Merge(other, [](const auto& item, const auto& value)->ValueType { return item.Subtract(value); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> Multiply(const RelativeColor<Tp, N>& other) const noexcept { return Merge(other, [](const auto& item, const auto& value)->ValueType { return item.Multiply(value); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> Multiply(const ValueType& other) const noexcept { return Merge(other, [](const auto& item, const auto& value)->ValueType { return item.Multiply(value); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> Divide(const RelativeColor<Tp, N>& other) const noexcept { return Merge(other, [](const auto& item, const auto& value)->ValueType { return item.Divide(value); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> Divide(const ValueType& other) const noexcept { return Merge(other, [](const auto& item, const auto& value)->ValueType { return item.Divide(value); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> SaturateAdd(const RelativeColor<Tp, N>& other) const noexcept { return Merge(other, [](const auto& item, const auto& value)->ValueType { return item.SaturateAdd(value); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> SaturateSubtract(const RelativeColor<Tp, N>& other) const noexcept { return Merge(other, [](const auto& item, const auto& value)->ValueType { return item.SaturateSubtract(value); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> SaturateMultiply(const RelativeColor<Tp, N>& other) const noexcept { return Merge(other, [](const auto& item, const auto& value)->ValueType { return item.SaturateMultiply(value); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> SaturateMultiply(const ValueType& other) const noexcept { return Merge(other, [](const auto& item, const auto& value)->ValueType { return item.SaturateMultiply(value); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> SaturateDivide(const RelativeColor<Tp, N>& other) const noexcept { return Merge(other, [](const auto& item, const auto& value)->ValueType { return item.SaturateDivide(value); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> SaturateDivide(const ValueType& other) const noexcept { return Merge(other, [](const auto& item, const auto& value)->ValueType { return item.SaturateDivide(value); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> CheckedAdd(const RelativeColor<Tp, N>& other) const { return Merge(other, [](const auto& item, const auto& value)->ValueType { return item.CheckedAdd(value); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> CheckedSubtract(const RelativeColor<Tp, N>& other) const { return Merge(other, [](const auto& item, const auto& value)->ValueType { return item.CheckedSubtract(value); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> CheckedMultiply(const RelativeColor<Tp, N>& other) const { return Merge(other, [](const auto& item, const auto& value)->ValueType { return item.CheckedMultiply(value); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> CheckedMultiply(const ValueType& other) const { return Merge(other, [](const auto& item, const auto& value)->ValueType { return item.CheckedMultiply(value); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> CheckedDivide(const RelativeColor<Tp, N>& other) const { return Merge(other, [](const auto& item, const auto& value)->ValueType { return item.CheckedDivide(value); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> CheckedDivide(const ValueType& other) const { return Merge(other, [](const auto& item, const auto& value)->ValueType { return item.CheckedDivide(value); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> And(const RelativeColor<Tp, N>& other) const noexcept { return Merge(other, [](const auto& item, const auto& value)->ValueType { return item.And(value); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> Or(const RelativeColor<Tp, N>& other) const noexcept { return Merge(other, [](const auto& item, const auto& value)->ValueType { return item.Or(value); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> Not() const noexcept { return Apply([](const auto& item)->ValueType { return item.Not(); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> Xor(const RelativeColor<Tp, N>& other) const noexcept { return Merge(other, [](const auto& item, const auto& value)->ValueType { return item.Xor(value); }); }
		[[nodiscard]] constexpr bool Equals(const RelativeColor<Tp, N>& other) const noexcept
		{
			auto ti = _value.cbegin();
			auto oi = other._value.cbegin();
			auto te = _value.cend();
			auto oe = other._value.cend();
			while((ti != te) && (oi != oe))
			{
				if (!ti->Equals(*oi)) { return false; }
				++ti;
				++oi;
			}
			return true;
		}

		[[nodiscard]] constexpr RelativeColor<Tp, N> operator+() const noexcept { return Promote(); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> operator-() const noexcept { return Invert(); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> operator+(const RelativeColor<Tp, N>& other) const noexcept { return Add(other); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> operator-(const RelativeColor<Tp, N>& other) const noexcept { return Subtract(other); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> operator*(const RelativeColor<Tp, N>& other) const noexcept { return Multiply(other); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> operator*(const ValueType& other) const noexcept { return Multiply(other); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> operator/(const RelativeColor<Tp, N>& other) const noexcept { return Divide(other); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> operator/(const ValueType& other) const noexcept { return Divide(other); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> operator|(const RelativeColor<Tp, N>& other) const noexcept { return Or(other); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> operator&(const RelativeColor<Tp, N>& other) const noexcept { return And(other); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> operator~() const noexcept { return Not(); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> operator^(const RelativeColor<Tp, N>& other) const noexcept { return Xor(other); }
		constexpr RelativeColor<Tp, N>& operator+=(const RelativeColor<Tp, N>& other) noexcept { return *this = Add(other); }
		constexpr RelativeColor<Tp, N>& operator-=(const RelativeColor<Tp, N>& other) noexcept { return *this = Subtract(other); }
		constexpr RelativeColor<Tp, N>& operator*=(const RelativeColor<Tp, N>& other) noexcept { return *this = Multiply(other); }
		constexpr RelativeColor<Tp, N>& operator*=(const ValueType& other) noexcept { return *this = Multiply(other); }
		constexpr RelativeColor<Tp, N>& operator/=(const RelativeColor<Tp, N>& other) noexcept { return *this = Divide(other); }
		constexpr RelativeColor<Tp, N>& operator/=(const ValueType& other) noexcept { return *this = Divide(other); }
		constexpr RelativeColor<Tp, N>& operator|=(const RelativeColor<Tp, N>& other) noexcept { return *this = Or(other); }
		constexpr RelativeColor<Tp, N>& operator&=(const RelativeColor<Tp, N>& other) noexcept { return *this = And(other); }
		constexpr RelativeColor<Tp, N>& operator^=(const RelativeColor<Tp, N>& other) noexcept { return *this = Xor(other); }
		[[nodiscard]] constexpr bool operator==(const RelativeColor<Tp, N>& other) const noexcept { return Equals(other); }
		[[nodiscard]] constexpr bool operator!=(const RelativeColor<Tp, N>& other) const noexcept { return !Equals(other); }

		[[nodiscard]] constexpr RelativeColor<Tp, N> Apply(const std::function<ValueType(const ValueType&)>& pred) const
		{
			RelativeColor<Tp, N> result;
			auto si = _value.cbegin();
			auto di = result._value.begin();
			auto se = _value.cend();
			auto de = result._value.end();
			while((si != se) && (di != de))
			{
				*di = pred(*si);
				++di;
				++si;
			}
			return result;
		}
		[[nodiscard]] constexpr RelativeColor<Tp, N> Merge(const RelativeColor<Tp, N>& other, const std::function<ValueType(const ValueType&, const ValueType&)>& pred) const
		{
			RelativeColor<Tp, N> result;
			auto s1i = _value.cbegin();
			auto s2i = other._value.cbegin();
			auto di = result._value.begin();
			auto s1e = _value.cend();
			auto s2e = other._value.cend();
			auto de = result._value.end();
			while((s1i != s1e) && (s2i != s2e) && (di != de))
			{
				*di = pred(*s1i, *s2i);
				++di;
				++s1i;
				++s2i;
			}
			return result;
		}
		[[nodiscard]] constexpr RelativeColor<Tp, N> Merge(const ValueType& value, const std::function<ValueType(const ValueType&, const ValueType&)>& pred) const
		{
			RelativeColor<Tp, N> result;
			auto si = _value.cbegin();
			auto di = result._value.begin();
			auto se = _value.cend();
			auto de = result._value.end();
			while((si != se) && (di != de))
			{
				*di = pred(*si, value);
				++di;
				++si;
			}
			return result;
		}

		[[nodiscard]] static constexpr RelativeColor<Tp, N> Expand(const ValueType& value)
		{
			RelativeColor<Tp, N> result;
			for(auto& item: result._value)
			{
				item = value;
			}
			return result;
		}
	private:
		template<class fromT>
		static constexpr std::array<ValueType, N> convert(const std::array<fromT, N>& valuelist)
		{
			std::array<ValueType, N> result;
			auto si = valuelist.cbegin();
			auto di = result.begin();
			auto se = valuelist.cend();
			auto de = result.end();
			while((si != se) && (di != de))
			{
				*di = ValueType(*si);
				++di;
				++si;
			}
			return result;
		}
	};
}
#endif // __stationaryorbit_graphics_core_relativecolor__
