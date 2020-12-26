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
	public:
		typedef T ValueType;
	private:
		ValueType _data;
	public:
		Integer() = default;
		constexpr Integer(const ValueType& value) noexcept : _data(value) {}
		template<class fromT, typename = std::void_t< std::enable_if_t< std::is_convertible_v<ValueType, fromT> || Traits::IsAggregatable<ValueType, fromT> || std::is_constructible_v<ValueType, fromT> > > >
		constexpr Integer(const fromT& value) :
			_data
			(
				[](const fromT& value)->ValueType
				{
					if constexpr (std::is_convertible_v<ValueType, fromT>) { return value; }
					if constexpr (Traits::IsAggregatable<ValueType, fromT>) { return ValueType{ value }; }
					if constexpr (std::is_constructible_v<ValueType, fromT>) { return ValueType(value); }
				}(value)
			)
		{}
	private:
	public:

		[[nodiscard]] constexpr const ValueType& Data() const noexcept { return _data; }

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
					if (getbit(i))
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
			if constexpr (Traits::HasPreincrement<T>) { return ++_data; }
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
			if constexpr (Traits::HasPreincrement<T>) { return --_data; }
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
			auto result = Integer<T>();
			Integer<T> surplus = *this;
			for (auto i: Range<size_t>(0, BitWidth<T>).GetStdReverseIterator())
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
}
#endif // __stationaryorbit_core_integer__
