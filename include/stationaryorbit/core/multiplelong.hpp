//	stationaryorbit/core/multiplelong
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
#ifndef __stationaryorbit_core_multiplelong__
#define __stationaryorbit_core_multiplelong__
#include <cstddef>
#include <array>
#include "fundamental.hpp"
#include "zerovalue.hpp"
#include "traits.hpp"
#include "range.hpp"
namespace zawa_ch::StationaryOrbit
{
	template<class T, size_t N>
	struct MultipleULong final
	{
		static_assert(Traits::IsIntegralType<T>, "テンプレート型 T は整数型である必要があります。");
		static_assert(!std::numeric_limits<T>::is_signed, "テンプレート型 T は符号なし型である必要があります。");
		static_assert(0 < N, "テンプレート引数 N に 0 を指定することはできません。");
	public:
		typedef std::array<T, N> DataType;
	private:
		DataType _data;
		///	内部表現型から @a MultipleULong のオブジェクトを作成します。
		constexpr explicit MultipleULong(const DataType& data) noexcept : _data(data) {}
	public:
		///	空の @a MultipleULong のオブジェクトを作成します。
		constexpr MultipleULong() = default;
		///	@a T 型の値を @a MultipleULong に変換します。
		constexpr MultipleULong(const T& value) noexcept : _data({value}) {}
		constexpr MultipleULong(const ZeroValue_t&) : _data({Zero}) {}

		[[nodiscard]] constexpr MultipleULong<T, N> operator+() const noexcept { return *this; }
		[[nodiscard]] constexpr MultipleULong<T, N> operator-() const noexcept { return (~*this + 1); }
		[[nodiscard]] constexpr MultipleULong<T, N> operator+(const MultipleULong<T, N>& other) const noexcept
		{
			bool c = false;
			auto result = MultipleULong<T, N>();
			for (auto i: Range<size_t>(0, _data.size()).GetStdIterator())
			{
				result._data[i] = _data[i] + (c?1U:0U);
				c = (c && (std::numeric_limits<T>::max() == result._data[i])) || ((std::numeric_limits<T>::max()-other._data[i]) < result._data[i]);
				result._data[i] += other._data[i];
			}
			return result;
		}
		[[nodiscard]] constexpr MultipleULong<T, N> operator-(const MultipleULong<T, N>& other) const noexcept
		{
			bool b = false;
			auto result = MultipleULong<T, N>();
			for (auto i: Range<size_t>(0, _data.size()).GetStdIterator())
			{
				result._data[i] = _data[i] - (b?1U:0U);
				b = (_data[i] < (b?1U:0U)) || (result._data[i] < other._data[i]);
				result._data[i] -= other._data[i];
			}
			return result;
		}
		[[nodiscard]] constexpr MultipleULong<T, N> operator*(const MultipleULong<T, N>& other) const noexcept
		{
			auto result = MultipleULong<T, N>();
			for (auto i: Range<size_t>(0, BitWidth<T> * N).GetStdIterator())
			{
				if ((other & (MultipleULong<T, N>(1)<<i)) != 0)
				{
					result += (*this) << i;
				}
			}
			return result;
		}
		[[nodiscard]] constexpr DivisionResult<MultipleULong<T, N>> Divide(const MultipleULong<T, N>& other) const noexcept
		{
			size_t w = 0;
			for (auto i: Range<size_t>(0, BitWidth<T> * N).GetStdIterator())
			{
				if (((other << i) & (MultipleULong<T, N>(1U) << (BitWidth<T> * N - 1))) != 0) { w = i; break; }
			}
			auto result = MultipleULong<T, N>();
			MultipleULong<T, N> surplus = *this;
			for (auto i: Range<size_t>(0, w).GetStdReverseIterator())
			{
				MultipleULong<T, N> div = other << i;
				if (div <= surplus)
				{
					result |= MultipleULong<T, N>(1) << i;
					surplus -= div;
				}
			}
			return { result, surplus };
		}
		[[nodiscard]] constexpr MultipleULong<T, N> operator/(const MultipleULong<T, N>& other) const noexcept
		{
			return Divide(other).Value;
		}
		[[nodiscard]] constexpr MultipleULong<T, N> operator%(const MultipleULong<T, N>& other) const noexcept
		{
			return Divide(other).Mod;
		}
		[[nodiscard]] constexpr MultipleULong<T, N> operator~() const noexcept
		{
			auto result = MultipleULong<T, N>();
			for (auto i: Range<size_t>(0, _data.size()).GetStdIterator())
			{
				result._data[i] = ~_data[i];
			}
			return result;
		}
		[[nodiscard]] constexpr MultipleULong<T, N> operator|(const MultipleULong<T, N>& other) const noexcept
		{
			auto result = MultipleULong<T, N>();
			for (auto i: Range<size_t>(0, _data.size()).GetStdIterator())
			{
				result._data[i] = _data[i] | other._data[i];
			}
			return result;
		}
		[[nodiscard]] constexpr MultipleULong<T, N> operator&(const MultipleULong<T, N>& other) const noexcept
		{
			auto result = MultipleULong<T, N>();
			for (auto i: Range<size_t>(0, _data.size()).GetStdIterator())
			{
				result._data[i] = _data[i] & other._data[i];
			}
			return result;
		}
		[[nodiscard]] constexpr MultipleULong<T, N> operator^(const MultipleULong<T, N>& other) const noexcept
		{
			auto result = MultipleULong<T, N>();
			for (auto i: Range<size_t>(0, _data.size()).GetStdIterator())
			{
				result._data[i] = _data[i] ^ other._data[i];
			}
			return result;
		}
		[[nodiscard]] constexpr MultipleULong<T, N> operator>>(const size_t& count) const noexcept
		{
			size_t shiftindex = count / BitWidth<T>;
			size_t shiftbit = count % BitWidth<T>;
			auto result = MultipleULong<T, N>();
			for (size_t i = 0U; (i < _data.size()) && ((i + shiftindex) < _data.size()); i++)
			{
				if ((shiftbit != 0U) && (i + shiftindex + 1U) < _data.size()) { result._data[i] |= _data[i + shiftindex + 1U] << (BitWidth<T> - shiftbit); }
				result._data[i] |= _data[i + shiftindex] >> shiftbit;
			}
			return result;
		}
		[[nodiscard]] constexpr MultipleULong<T, N> operator<<(const size_t& count) const noexcept
		{
			size_t shiftindex = count / BitWidth<T>;
			size_t shiftbit = count % BitWidth<T>;
			auto result = MultipleULong<T, N>();
			for (size_t i = shiftindex; i < _data.size(); i++)
			{
				if ((shiftbit != 0U) && (0U < (i - shiftindex))) { result._data[i] |= _data[i - shiftindex - 1U] >> (BitWidth<T> - shiftbit); }
				result._data[i] |= _data[i - shiftindex] << shiftbit;
			}
			return result;
		}

		[[nodiscard]] constexpr bool operator!() const noexcept { return *this == 0U; }
		[[nodiscard]] constexpr bool operator||(const MultipleULong<T, N>& other) const noexcept { return (*this != 0U) || (other != 0U); }
		[[nodiscard]] constexpr bool operator&&(const MultipleULong<T, N>& other) const noexcept { return (*this != 0U) && (other != 0U); }

		constexpr MultipleULong<T, N>& operator+=(const MultipleULong<T, N>& other) noexcept { return *this = *this + other; }
		constexpr MultipleULong<T, N>& operator-=(const MultipleULong<T, N>& other) noexcept { return *this = *this - other; }
		constexpr MultipleULong<T, N>& operator*=(const MultipleULong<T, N>& other) noexcept { return *this = *this * other; }
		constexpr MultipleULong<T, N>& operator/=(const MultipleULong<T, N>& other) noexcept { return *this = *this / other; }
		constexpr MultipleULong<T, N>& operator|=(const MultipleULong<T, N>& other) noexcept { return *this = *this | other; }
		constexpr MultipleULong<T, N>& operator&=(const MultipleULong<T, N>& other) noexcept { return *this = *this & other; }
		constexpr MultipleULong<T, N>& operator^=(const MultipleULong<T, N>& other) noexcept { return *this = *this ^ other; }
		constexpr MultipleULong<T, N>& operator>>=(const size_t& count) noexcept { return *this = *this >> count; }
		constexpr MultipleULong<T, N>& operator<<=(const size_t& count) noexcept { return *this = *this << count; }

		constexpr MultipleULong<T, N>& operator++() noexcept { return *this = *this + 1; }
		constexpr MultipleULong<T, N>& operator++(int) noexcept { MultipleULong<T, N> result = *this; ++(*this); return *this; }
		constexpr MultipleULong<T, N>& operator--() noexcept { return *this = *this - 1; }
		constexpr MultipleULong<T, N>& operator--(int) noexcept { MultipleULong<T, N> result = *this; --(*this); return *this; }

		///	このオブジェクトが他のオブジェクトと等しいか比較します。
		[[nodiscard]] constexpr bool Equals(const MultipleULong<T, N>& other) const noexcept
		{
			for (auto i: Range<size_t>(0, _data.size()).GetStdIterator())
			{
				if (_data[i] != other._data[i]) { return false; }
			}
			return true;
		}
		///	このオブジェクトと他のオブジェクトの大小関係を比較します。
		[[nodiscard]] constexpr int Compare(const MultipleULong<T, N>& other) const noexcept
		{
			for (auto i: Range<size_t>(0, _data.size()).GetStdReverseIterator())
			{
				if (other._data[i] < _data[i]) { return 1; }
				if (_data[i] < other._data[i]) { return -1; }
			}
			return 0;
		}
		[[nodiscard]] constexpr bool operator==(const MultipleULong<T, N>& other) const noexcept { return Equals(other); }
		[[nodiscard]] constexpr bool operator!=(const MultipleULong<T, N>& other) const noexcept { return !Equals(other); }
		[[nodiscard]] constexpr bool operator<(const MultipleULong<T, N>& other) const noexcept { return Compare(other) < 0;}
		[[nodiscard]] constexpr bool operator>=(const MultipleULong<T, N>& other) const noexcept { return Compare(other) >= 0;}
		[[nodiscard]] constexpr bool operator>(const MultipleULong<T, N>& other) const noexcept { return Compare(other) > 0;}
		[[nodiscard]] constexpr bool operator<=(const MultipleULong<T, N>& other) const noexcept { return Compare(other) <= 0;}

		constexpr explicit operator T() const noexcept { return T(_data[0]); }

		static constexpr MultipleULong<T, N> Min() noexcept { return MultipleULong<T, N>(0); }
		static constexpr MultipleULong<T, N> Max() noexcept { return ~MultipleULong<T, N>(0); }
	};

	template<class T, size_t N> struct BitWidth_t<MultipleULong<T, N>> : std::integral_constant<size_t, BitWidth<T> * N> {};

	typedef MultipleULong<uint8_t, 2UL> uint8double_t;
	typedef MultipleULong<uint16_t, 2UL> uint16double_t;
	typedef MultipleULong<uint32_t, 2UL> uint32double_t;
	typedef MultipleULong<uint64_t, 2UL> uint64double_t;

	extern template struct MultipleULong<uint8_t, 2UL>;
	extern template struct MultipleULong<uint16_t, 2UL>;
	extern template struct MultipleULong<uint32_t, 2UL>;
	extern template struct MultipleULong<uint64_t, 2UL>;
}
namespace std
{
	template<class T, size_t N>
	class numeric_limits<zawa_ch::StationaryOrbit::MultipleULong<T, N>> : numeric_limits<void>
	{
	public:
		static constexpr bool is_specialized = true;
		static constexpr int digits = zawa_ch::StationaryOrbit::BitWidth<zawa_ch::StationaryOrbit::MultipleULong<T, N>>;
		static constexpr int digits10 = int(digits * 0.30102999566398119521373889472449);
		static constexpr int max_digits10 = 0;
		static constexpr bool is_signed = false;
		static constexpr bool is_integer = true;
		static constexpr bool is_exact = true;
		static constexpr int radix = 2;
		static constexpr int min_exponent = 0;
		static constexpr int min_exponent10 = 0;
		static constexpr int max_exponent = 0;
		static constexpr int max_exponent10 = 0;
		static constexpr bool has_infinity = false;
		static constexpr bool has_quiet_NaN = false;
		static constexpr bool has_signaling_NaN = false;
		static constexpr float_denorm_style has_denorm = denorm_absent;
		static constexpr bool has_denorm_loss = false;
		static constexpr bool is_iec559 = false;
		static constexpr bool is_bounded = true;
		static constexpr bool is_modulo = numeric_limits<T>::is_modulo;
		static constexpr bool traps = false;
		static constexpr bool tinyness_before = false;
		static constexpr float_round_style round_style = round_toward_zero;

		static constexpr zawa_ch::StationaryOrbit::MultipleULong<T, N> min() noexcept { return zawa_ch::StationaryOrbit::MultipleULong<T, N>::Min(); }
		static constexpr zawa_ch::StationaryOrbit::MultipleULong<T, N> lowest() noexcept { return zawa_ch::StationaryOrbit::MultipleULong<T, N>::Min(); }
		static constexpr zawa_ch::StationaryOrbit::MultipleULong<T, N> max() noexcept { return zawa_ch::StationaryOrbit::MultipleULong<T, N>::Max(); }
	};
}
#endif // __stationaryorbit_core_multiplelong__
