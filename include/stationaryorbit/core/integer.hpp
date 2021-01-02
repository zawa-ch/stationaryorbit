//	stationaryorbit/core/integer
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
#ifndef __stationaryorbit_core_integer__
#define __stationaryorbit_core_integer__
#include <stdexcept>
#include "traits.hpp"
#include "algorithms.hpp"
#include "range.hpp"
namespace zawa_ch::StationaryOrbit
{
	template<class T>
	struct Integer final
	{
		static_assert(Traits::IsBitSequenceType<T>, "テンプレート引数型 T はビット列である必要があります。");
		template<class> friend class Integer;
	public:
		typedef T ValueType;
	private:
		ValueType _data;
	public:
		Integer() = default;
		constexpr Integer(const ValueType& value) noexcept : _data(value) {}
		template<class fromT>
		constexpr Integer(const std::enable_if_t< std::is_convertible_v<ValueType, fromT> || Traits::IsAggregatable<ValueType, fromT>, fromT>& value) :
			_data
			(
				[](const fromT& value)->ValueType
				{
					if constexpr (std::is_convertible_v<ValueType, fromT>) { return value; }
					if constexpr (Traits::IsAggregatable<ValueType, fromT>) { return ValueType{ value }; }
				}(value)
			)
		{}
		template<class fromT>
		constexpr explicit Integer(const std::enable_if_t< !(std::is_convertible_v<ValueType, fromT> || Traits::IsAggregatable<ValueType, fromT>) && std::is_constructible_v<ValueType, fromT>, fromT>& value) : _data( ValueType(value) ) {}
		template<class fromT>
		constexpr explicit Integer(const std::enable_if_t< !(std::is_convertible_v<ValueType, fromT> || Traits::IsAggregatable<ValueType, fromT> || std::is_constructible_v<ValueType, fromT>) && Traits::IsIntegralType<fromT> && !std::numeric_limits<fromT>::is_signed, fromT>& value) : Integer()
		{
			auto v = value;
			for (auto i: Range<size_t>(0, BitWidth<T>).GetStdIterator())
			{
				setbit(i, (v % 2) != 0);
				v /= 2;
				if (v == fromT(0)) { break; }
			}
		}
		template<class fromT>
		constexpr explicit Integer(const Integer<fromT>& from) : Integer()
		{
			for (auto i: Range<size_t>(0, std::min(BitWidth<fromT>, BitWidth<T>)).GetStdIterator()) { setbit(i, from.getbit(i)); }
		}
	public:
		[[nodiscard]] constexpr const ValueType& Data() const noexcept { return _data; }
		[[nodiscard]] constexpr explicit operator ValueType() const { return _data; }

		[[nodiscard]] constexpr Integer<T> operator~() const { return Integer(~_data); }
		[[nodiscard]] constexpr Integer<T> operator&(const Integer<T>& other) const { return Integer(_data & other._data); }
		[[nodiscard]] constexpr Integer<T> operator|(const Integer<T>& other) const { return Integer(_data | other._data); }
		[[nodiscard]] constexpr Integer<T> operator^(const Integer<T>& other) const { return Integer(_data ^ other._data); }
		template<class rightT, std::enable_if_t<std::is_integral_v<rightT>, int> = 0>
		[[nodiscard]] constexpr Integer<T> operator>>(const rightT& other) const { return Integer(_data >> other); }
		template<class rightT, std::enable_if_t<std::is_integral_v<rightT>>>
		[[nodiscard]] constexpr Integer<T> operator<<(const rightT& other) const { return Integer(_data << other); }
		constexpr Integer<T>& operator&=(const Integer<T>& other) { _data &= other._data; return *this; }
		constexpr Integer<T>& operator|=(const Integer<T>& other) { _data |= other._data; return *this; }
		constexpr Integer<T>& operator^=(const Integer<T>& other) { _data ^= other._data; return *this; }
		template<class rightT, std::enable_if_t<std::is_integral_v<rightT>>>
		constexpr Integer<T>& operator>>=(const rightT& other) { _data >>= other; return *this; }
		template<class rightT, std::enable_if_t<std::is_integral_v<rightT>, int> = 0>
		constexpr Integer<T>& operator<<=(const rightT& other) { _data <<= other; return *this; }
		[[nodiscard]] constexpr bool operator==(const Integer<T>& other) const { return _data == other._data; }
		[[nodiscard]] constexpr bool operator!=(const Integer<T>& other) const { return _data != other._data; }

		[[nodiscard]] constexpr Integer<T> operator+() const
		{
			if constexpr (Traits::HasPromotion<T>) { return Integer<T>(+_data); }
			else { return *this; }
		}
		[[nodiscard]] constexpr Integer<T> operator-() const
		{
			if constexpr (Traits::HasPromotion<T>) { return Integer<T>(-_data); }
			else { return Integer(~_data); }
		}
		[[nodiscard]] constexpr Integer<T> operator+(const Integer<T>& other) const
		{
			if constexpr (Traits::HasAddition<T, T>) { return Integer<T>(_data + other._data); }
			else
			{
				auto result = Integer<T>();
				bool c = false;
				for (auto i: Range<size_t>(0, BitWidth<T>).GetStdIterator())
				{
					bool a = getbit(i);
					bool b = other.getbit(i);
					result.setbit(i, Algorithms::Xor({a, b, c}));
					c = (a & b) | (b & c) | (c & a);
				}
				return result;
			}
		}
		[[nodiscard]] constexpr Integer<T> operator-(const Integer<T>& other) const
		{
			if constexpr (Traits::HasAddition<T, T>) { return Integer<T>(_data - other._data); }
			else
			{
				auto result = Integer<T>();
				bool c = true;
				for (auto i: Range<size_t>(0, BitWidth<T>).GetStdIterator())
				{
					bool a = getbit(i);
					bool b = !other.getbit(i);
					result.setbit(i, Algorithms::Xor({a, b, c}));
					c = (a & b) | (b & c) | (c & a);
				}
				return result;
			}
		}
		[[nodiscard]] constexpr Integer<T> operator*(const Integer<T>& other) const
		{
			if constexpr (Traits::HasMultiplication<T, T>) { return Integer<T>(_data * other._data); }
			else
			{
				auto result = Integer<T>();
				for (auto i: Range<size_t>(0, BitWidth<T>).GetStdIterator())
				{
					if (other.getbit(i))
					{
						result = result + (_data << i);
					}
				}
				return result;
			}
		}
		[[nodiscard]] constexpr Integer<T> operator/(const Integer<T>& other) const
		{
			if constexpr (Traits::HasDivision<T, T>) { return Integer<T>(_data / other._data); }
			else { return divide_impl(other).Value; }
		}
		[[nodiscard]] constexpr Integer<T> operator%(const Integer<T>& other) const
		{
			if constexpr (Traits::HasModulation<T, T>) { return Integer<T>(_data % other._data); }
			else { return divide_impl(other).Mod; }
		}

		constexpr Integer<T>& operator+=(const Integer<T>& other) { *this = *this + other; return *this; }
		constexpr Integer<T>& operator-=(const Integer<T>& other) { *this = *this - other; return *this; }
		constexpr Integer<T>& operator*=(const Integer<T>& other) { *this = *this * other; return *this; }
		constexpr Integer<T>& operator/=(const Integer<T>& other) { *this = *this / other; return *this; }
		constexpr Integer<T>& operator%=(const Integer<T>& other) { *this = *this % other; return *this; }

		constexpr Integer<T>& operator++()
		{
			if constexpr (Traits::HasPreincrement<T>) { (void)++_data; return *this; }
			else
			{
				bool c = true;
				for (auto i: Range<size_t>(0, BitWidth<T>).GetStdIterator())
				{
					bool a = getbit(i);
					setbit(i, Algorithms::Xor(a, c));
					c = (c & a);
				}
				return *this;
			}
		}
		[[nodiscard]] constexpr Integer<T> operator++(int) { auto result = *this; ++(*this); return result; }
		constexpr Integer<T>& operator--()
		{
			if constexpr (Traits::HasPreincrement<T>) { (void)--_data; return *this; }
			else
			{
				bool c = true;
				for (auto i: Range<size_t>(0, BitWidth<T>).GetStdIterator())
				{
					bool a = getbit(i);
					setbit(i, Algorithms::Xor({a, true, c}));
					c = (a | c);
				}
				return *this;
			}
		}
		[[nodiscard]] constexpr Integer<T> operator--(int) { auto result = *this; --(*this); return result; }

		[[nodiscard]] constexpr int Compare(const Integer<T>& other) const
		{
			if constexpr (Traits::IsComparable<T>)
			{
				if (_data < other._data) { return -1; }
				else if (other._data < _data) { return 1; }
				else { return 0; }
			}
			else
			{
				for (auto i: Range<size_t>(0, BitWidth<T>).GetStdReverseIterator())
				{
					auto a = getbit(i);
					auto b = other.getbit(i);
					if (getbit(i) != other.getbit(i))
					{
						if (getbit(i)) { return 1; }
						else { return -1; }
					}
					return 0;
				}
			}
		}
		[[nodiscard]] constexpr bool operator<(const Integer<T>& other) const
		{
			if constexpr (Traits::HasSmallerCompare<T, T>) { return _data < other._data; }
			else { Compare(other) < 0; }
		}
		[[nodiscard]] constexpr bool operator<=(const Integer<T>& other) const
		{
			if constexpr (Traits::HasSmallerCompare<T, T>) { return _data <= other._data; }
			else { Compare(other) <= 0; }
		}
		[[nodiscard]] constexpr bool operator>(const Integer<T>& other) const
		{
			if constexpr (Traits::HasSmallerCompare<T, T>) { return _data > other._data; }
			else { Compare(other) > 0; }
		}
		[[nodiscard]] constexpr bool operator>=(const Integer<T>& other) const
		{
			if constexpr (Traits::HasSmallerCompare<T, T>) { return _data >= other._data; }
			else { Compare(other) >= 0; }
		}

		[[nodiscard]] static constexpr Integer<T> Max() { return Integer<T>(~value_construct(0)); }
		[[nodiscard]] static constexpr Integer<T> Min() { return Integer<T>(value_construct(0)); }
		[[nodiscard]] static constexpr Integer<T> Epsilon() { return Integer<T>(value_construct(1)); }
	private:
		[[nodiscard]] static constexpr ValueType value_construct(const uint8_t& value)
		{
			if constexpr (std::is_convertible_v<ValueType, uint8_t>) { return value; }
			if constexpr (Traits::IsAggregatable<ValueType, uint8_t>) { return ValueType{ value }; }
			if constexpr (std::is_constructible_v<ValueType, uint8_t>) { return ValueType(value); }
		}
		[[nodiscard]] constexpr bool getbit(const size_t& index) const
		{
			if (BitWidth<T> <= index) { throw std::out_of_range("指定されたインデックスはこのオブジェクトの境界を超えています。"); }
			return (_data & (value_construct(1) << index)) != ValueType(0);
		}
		constexpr void setbit(const size_t& index, const bool& value)
		{
			if (BitWidth<T> <= index) { throw std::out_of_range("指定されたインデックスはこのオブジェクトの境界を超えています。"); }
			_data = (_data & ~(value_construct(1) << index)) | (value?(value_construct(1) << index):(value_construct(0)));
		}
		[[nodiscard]] constexpr DivisionResult<Integer<T>> divide_impl(const Integer<T>& other) const
		{
			size_t w = 0;
			for (auto i: Range<size_t>(0, BitWidth<T>).GetStdIterator())
			{
				if (other.getbit(i)) { w = i; }
			}
			auto result = Integer<T>();
			Integer<T> surplus = *this;
			for (auto i: Range<size_t, true, true>(0, w).GetStdReverseIterator())
			{
				Integer<T> div = other._data << i;
				if (div <= surplus)
				{
					result._data |= value_construct(1) << i;
					surplus -= div;
				}
			}
			return DivisionResult<Integer<T>>{ result, surplus };
		}
	};

	extern template struct Integer<std::byte>;
	extern template struct Integer<uint8_t>;
	extern template struct Integer<uint16_t>;
	extern template struct Integer<uint32_t>;
	extern template struct Integer<uint64_t>;
}
namespace std
{
	template<class T>
	class numeric_limits<zawa_ch::StationaryOrbit::Integer<T>> : public numeric_limits<void>
	{
	public:
		static constexpr bool is_specialized = true;
		static constexpr bool is_signed = false;
		static constexpr bool is_integer = true;
		static constexpr bool is_exact = true;
		static constexpr bool has_infinity = false;
		static constexpr bool has_quiet_NaN = false;
		static constexpr bool has_signaling_NaN = false;
		static constexpr float_denorm_style has_denorm = denorm_absent;
		static constexpr bool has_denorm_loss = false;
		static constexpr float_round_style round_style = round_toward_zero;
		static constexpr bool is_iec559 = false;
		static constexpr bool is_bounded = true;
		static constexpr bool is_modulo = true;
		static constexpr int digits = zawa_ch::StationaryOrbit::BitWidth<T>;
		static constexpr int digits10 = int(digits * 0.30102999566398119521373889472449);
		static constexpr int max_digits10 = 0;
		static constexpr int radix = 2;
		static constexpr int min_exponent = 0;
		static constexpr int min_exponent10 = 0;
		static constexpr int max_exponent = 0;
		static constexpr int max_exponent10 = 0;
		static constexpr bool traps = true;
		static constexpr bool tinyness_before = true;
		static constexpr zawa_ch::StationaryOrbit::Integer<T> min() noexcept { return zawa_ch::StationaryOrbit::Integer<T>::Min(); }
		static constexpr zawa_ch::StationaryOrbit::Integer<T> lowest() noexcept { return zawa_ch::StationaryOrbit::Integer<T>::Min(); }
		static constexpr zawa_ch::StationaryOrbit::Integer<T> max() noexcept { return zawa_ch::StationaryOrbit::Integer<T>::Max(); }
		static constexpr zawa_ch::StationaryOrbit::Integer<T> epsilon() noexcept { return zawa_ch::StationaryOrbit::Integer<T>::Epsilon(); }
		static constexpr zawa_ch::StationaryOrbit::Integer<T> round_error() noexcept { return zawa_ch::StationaryOrbit::Integer<T>::Epsilon(); }
	};
}
#endif // __stationaryorbit_core_integer__
