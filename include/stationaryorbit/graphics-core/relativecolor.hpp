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
#include "channelvalue.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	template<class Tp, size_t N>
	struct RelativeColor final
	{
	public:
		typedef ChannelValue<Tp> ValueType;
	private:
		std::array<ValueType, N> _value;
	public:
		constexpr RelativeColor() : _value() {}
		constexpr RelativeColor(const std::initializer_list<ValueType>& list) : _value(list) {}
		template<class fromT>
		constexpr explicit RelativeColor(const RelativeColor<fromT, N>& from) : _value(convert(from.Data())) {}
		constexpr RelativeColor(const ZeroValue_t&) : RelativeColor(Expand(ValueType(Zero))) {}

		[[nodiscard]] constexpr const std::array<ValueType, N>& Data() const { return _value; }

		[[nodiscard]] constexpr RelativeColor<Tp, N> Add(const RelativeColor<Tp, N>& other) const { return Merge(other, [](const auto& a, const auto& b)->Valuetype { return a.Add(b); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> Subtract(const RelativeColor<Tp, N>& other) const { return Merge(other, [](const auto& a, const auto& b)->Valuetype { return a.Subtract(b); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> Multiply(const RelativeColor<Tp, N>& other) const { return Merge(other, [](const auto& a, const auto& b)->Valuetype { return a.Multiply(b); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> Divide(const RelativeColor<Tp, N>& other) const { return Merge(other, [](const auto& a, const auto& b)->Valuetype { return a.Divide(b); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> SaturateAdd(const RelativeColor<Tp, N>& other) const { return Merge(other, [](const auto& a, const auto& b)->Valuetype { return a.SaturateAdd(b); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> SaturateSubtract(const RelativeColor<Tp, N>& other) const { return Merge(other, [](const auto& a, const auto& b)->Valuetype { return a.SaturateSubtract(b); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> SaturateMultiply(const RelativeColor<Tp, N>& other) const { return Merge(other, [](const auto& a, const auto& b)->Valuetype { return a.SaturateMultiply(b); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> SaturateDivide(const RelativeColor<Tp, N>& other) const { return Merge(other, [](const auto& a, const auto& b)->Valuetype { return a.SaturateDivide(b); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> CheckedAdd(const RelativeColor<Tp, N>& other) const { return Merge(other, [](const auto& a, const auto& b)->Valuetype { return a.CheckedAdd(b); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> CheckedSubtract(const RelativeColor<Tp, N>& other) const { return Merge(other, [](const auto& a, const auto& b)->Valuetype { return a.CheckedSubtract(b); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> CheckedMultiply(const RelativeColor<Tp, N>& other) const { return Merge(other, [](const auto& a, const auto& b)->Valuetype { return a.CheckedMultiply(b); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> CheckedDivide(const RelativeColor<Tp, N>& other) const { return Merge(other, [](const auto& a, const auto& b)->Valuetype { return a.CheckedDivide(b); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> And(const RelativeColor<Tp, N>& other) const { return Merge(other, [](const auto& a, const auto& b)->Valuetype { return a.And(b); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> Or(const RelativeColor<Tp, N>& other) const { return Merge(other, [](const auto& a, const auto& b)->Valuetype { return a.Or(b); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> Not() const { return Apply([](const auto& a)->Valuetype { return a.Not(); }); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> Xor(const RelativeColor<Tp, N>& other) const { return Merge(other, [](const auto& a, const auto& b)->Valuetype { return a.Xor(b); }); }
		[[nodiscard]] constexpr bool Equals(const RelativeColor<Tp, N>& other) const
		{
			auto ti = _value.cbegin();
			auto oi = other._value.cbegin();
			auto te = _value.cend();
			auto oe = other._value.cend();
			while((ti != te) && (oi != oe))
			{
				if (*ti != *oi) { return false; }
				++ti;
				++oi;
			}
			return true;
		}

		[[nodiscard]] constexpr RelativeColor<Tp, N> operator+(const RelativeColor<Tp, N>& other) const noexcept { return Add(other); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> operator-(const RelativeColor<Tp, N>& other) const noexcept { return Subtract(other); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> operator*(const RelativeColor<Tp, N>& other) const noexcept { return Multiply(other); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> operator/(const RelativeColor<Tp, N>& other) const noexcept { return Divide(other); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> operator|(const RelativeColor<Tp, N>& other) const noexcept { return Or(other); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> operator&(const RelativeColor<Tp, N>& other) const noexcept { return And(other); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> operator~() const noexcept { return Not(); }
		[[nodiscard]] constexpr RelativeColor<Tp, N> operator^(const RelativeColor<Tp, N>& other) const noexcept { return Xor(other); }
		constexpr RelativeColor<Tp, N>& operator+=(const RelativeColor<Tp, N>& other) noexcept { return *this = Add(other); }
		constexpr RelativeColor<Tp, N>& operator-=(const RelativeColor<Tp, N>& other) noexcept { return *this = Subtract(other); }
		constexpr RelativeColor<Tp, N>& operator*=(const RelativeColor<Tp, N>& other) noexcept { return *this = Multiply(other); }
		constexpr RelativeColor<Tp, N>& operator/=(const RelativeColor<Tp, N>& other) noexcept { return *this = Divide(other); }
		constexpr RelativeColor<Tp, N>& operator|=(const RelativeColor<Tp, N>& other) noexcept { return *this = Or(other); }
		constexpr RelativeColor<Tp, N>& operator&=(const RelativeColor<Tp, N>& other) noexcept { return *this = And(other); }
		constexpr RelativeColor<Tp, N>& operator^=(const RelativeColor<Tp, N>& other) noexcept { return *this = Xor(other); }
		[[nodiscard]] constexpr bool operator==(const ChannelValue<Tp>& other) const noexcept { return Equals(other); }
		[[nodiscard]] constexpr bool operator!=(const ChannelValue<Tp>& other) const noexcept { return !Equals(other); }
		constexpr ChannelValue<Tp>& operator=(const ChannelValue<Tp>&) = default;
		constexpr ChannelValue<Tp>& operator=(ChannelValue<Tp>&&) = default;

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

		[[nodiscard]] static constexpr RelativeColor<Tp, N> Expand(const ValueType& value)
		{
			RelativeColor<Tp, N> result;
			for(auto& item: result)
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
