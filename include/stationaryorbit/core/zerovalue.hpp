//	stationaryorbit/core/zerovalue
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
#ifndef __stationaryorbit_zerovalue__
#define __stationaryorbit_zerovalue__
#include <cstddef>
#include <stdexcept>
namespace zawa_ch::StationaryOrbit
{
	///	他の型に変換可能な零値を表します。
	struct ZeroValue_t
	{
	public:
		constexpr ZeroValue_t() = default;
		constexpr ZeroValue_t(const ZeroValue_t&) = default;
		constexpr ZeroValue_t(ZeroValue_t&&) = default;

		constexpr operator bool() const { return 0; }
		template<class = std::enable_if_t<std::negation_v<std::is_same<std::nullptr_t, void*>>>>
		constexpr operator void*() const { return (void*)(0); }
		constexpr operator std::nullptr_t() const { return nullptr; }
		constexpr operator std::byte() const { return std::byte('\0'); }

		constexpr ZeroValue_t operator+() const { return ZeroValue_t(); }
		constexpr ZeroValue_t operator-() const { return ZeroValue_t(); }
		constexpr ZeroValue_t operator+(const ZeroValue_t&) const { return ZeroValue_t(); }
		constexpr ZeroValue_t operator-(const ZeroValue_t&) const { return ZeroValue_t(); }
		constexpr ZeroValue_t operator*(const ZeroValue_t&) const { return ZeroValue_t(); }
		constexpr ZeroValue_t operator|(const ZeroValue_t&) const { return ZeroValue_t(); }
		constexpr ZeroValue_t operator&(const ZeroValue_t&) const { return ZeroValue_t(); }
		constexpr ZeroValue_t operator^(const ZeroValue_t&) const { return ZeroValue_t(); }
		constexpr ZeroValue_t operator<<(const int&) const { return ZeroValue_t(); }
		constexpr ZeroValue_t operator>>(const int&) const { return ZeroValue_t(); }

		constexpr ZeroValue_t operator||(const ZeroValue_t&) const { return ZeroValue_t(); }
		constexpr ZeroValue_t operator&&(const ZeroValue_t&) const { return ZeroValue_t(); }

		constexpr ZeroValue_t& operator+=(const ZeroValue_t&) { return *this; }
		constexpr ZeroValue_t& operator-=(const ZeroValue_t&) { return *this; }
		constexpr ZeroValue_t& operator*=(const ZeroValue_t&) { return *this; }
		constexpr ZeroValue_t& operator|=(const ZeroValue_t&) { return *this; }
		constexpr ZeroValue_t& operator&=(const ZeroValue_t&) { return *this; }
		constexpr ZeroValue_t& operator^=(const ZeroValue_t&) { return *this; }
		constexpr ZeroValue_t& operator<<=(const int&) { return *this; }
		constexpr ZeroValue_t& operator>>=(const int&) { return *this; }

		constexpr bool Equals(const ZeroValue_t&) const { return true; }
		constexpr bool operator==(const ZeroValue_t&) const { return true; }
		constexpr bool operator!=(const ZeroValue_t&) const { return false; }
		constexpr int Compare(const ZeroValue_t&) const { return 0; }
		constexpr bool operator<(const ZeroValue_t&) const { return false; }
		constexpr bool operator>(const ZeroValue_t&) const { return false; }
		constexpr bool operator<=(const ZeroValue_t&) const { return true; }
		constexpr bool operator>=(const ZeroValue_t&) const { return true; }
	};
	constexpr ZeroValue_t Zero = ZeroValue_t();
}
#endif // __stationaryorbit_zerovalue__