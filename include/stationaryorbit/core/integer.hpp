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
	template<class T> struct Integer;
	template<class T> struct SignedInteger;

	template<class T>
	struct Integer final
	{
		static_assert(Traits::IsBitSequenceType<T>, "テンプレート引数型 T はビット列である必要があります。");
		template<class> friend class Integer;
		template<class> friend class SignedInteger;
	public:
		typedef T ValueType;
		typedef SignedInteger<T> SignedType;
	private:
		ValueType _data;
	public:
		///	空の @a Integer を構築します。
		Integer() = default;
		///	内部の型と同じビット列型から @a Integer を構築します。
		///	@note
		///	内部型が整数型トレイトを満たす場合にこちらのコンストラクタが適用されます。
		template<class fromT, std::enable_if_t< std::is_same_v<ValueType, fromT> && Traits::IsIntegralType<fromT>, int> = 0>
		constexpr Integer(const fromT& value) noexcept : _data(value) {}
		///	内部の型と同じビット列型から @a Integer を構築します。
		///	@note
		///	内部型が整数型トレイトを満たさない場合にこちらのコンストラクタが適用されます。
		template<class fromT, std::enable_if_t< std::is_same_v<ValueType, fromT> && !Traits::IsIntegralType<fromT>, int> = 0>
		constexpr explicit Integer(const fromT& value) noexcept : _data(value) {}
		///	内部の型に変換可能な型から @a Integer を構築します。
		///	@note
		///	内部型が暗黙の変換をサポートし、整数型トレイトを満たす場合にこちらのコンストラクタが適用されます。
		template<class fromT, std::enable_if_t< !(std::is_same_v<ValueType, fromT>) && (std::is_convertible_v<ValueType, fromT> || Traits::IsAggregatable<ValueType, fromT>) && Traits::IsIntegralType<fromT>, int> = 0>
		constexpr Integer(const fromT& value) : _data(value_construct<fromT>(value)) {}
		///	内部の型に変換可能な型から @a Integer を構築します。
		///	@note
		///	内部型が整数型トレイトを満たさない、または暗黙の変換をサポートしない場合にこちらのコンストラクタが適用されます。
		template<class fromT, std::enable_if_t< !(std::is_same_v<ValueType, fromT>) && (((std::is_convertible_v<ValueType, fromT> || Traits::IsAggregatable<ValueType, fromT>) && !Traits::IsIntegralType<fromT>) || (!(std::is_convertible_v<ValueType, fromT> || Traits::IsAggregatable<ValueType, fromT>) && std::is_constructible_v<ValueType, fromT>)), int> = 0>
		constexpr explicit Integer(const fromT& value) : _data(value_construct<fromT>(value)) {}
		///	整数型から @a Integer を構築します。
		template<class fromT, std::enable_if_t< !(std::is_same_v<ValueType, fromT> || std::is_convertible_v<ValueType, fromT> || Traits::IsAggregatable<ValueType, fromT> || std::is_constructible_v<ValueType, fromT>) && Traits::IsIntegralType<fromT> && !std::numeric_limits<fromT>::is_signed, int> = 0>
		constexpr explicit Integer(const fromT& value) : Integer()
		{
			auto v = value;
			for (auto i: Range<size_t>(0, BitWidth<T>).GetStdIterator())
			{
				setbit(i, (v % 2) != 0);
				v /= 2;
				if (v == fromT(0)) { break; }
			}
		}
		///	異なるテンプレートの @a Integer から変換します。
		template<class fromT>
		constexpr explicit Integer(const Integer<fromT>& from) : Integer()
		{
			for (auto i: Range<size_t>(0, std::min(BitWidth<fromT>, BitWidth<T>)).GetStdIterator()) { setbit(i, from.getbit(i)); }
		}
		///	@a SignedInteger から変換します。
		constexpr explicit Integer(const SignedType& from) noexcept : _data(from.Data()) {}
		///	@a ZeroValue_t から変換します。
		constexpr Integer(const ZeroValue_t&) noexcept : _data(value_construct<uint8_t>(0)) {}

		[[nodiscard]] constexpr const ValueType& Data() const noexcept { return _data; }
		[[nodiscard]] constexpr explicit operator ValueType() const { return _data; }

		[[nodiscard]] constexpr Integer<T> operator~() const { return Integer(T(~_data)); }
		[[nodiscard]] constexpr Integer<T> operator&(const Integer<T>& other) const { return Integer(T(_data & other._data)); }
		[[nodiscard]] constexpr Integer<T> operator|(const Integer<T>& other) const { return Integer(T(_data | other._data)); }
		[[nodiscard]] constexpr Integer<T> operator^(const Integer<T>& other) const { return Integer(T(_data ^ other._data)); }
		template<class rightT, std::enable_if_t<std::is_integral_v<rightT>, int> = 0>
		[[nodiscard]] constexpr Integer<T> operator>>(const rightT& other) const { return Integer(T(_data >> other)); }
		template<class rightT, std::enable_if_t<std::is_integral_v<rightT>, int> = 0>
		[[nodiscard]] constexpr Integer<T> operator<<(const rightT& other) const { return Integer(T(_data << other)); }
		constexpr Integer<T>& operator&=(const Integer<T>& other) { _data &= other._data; return *this; }
		constexpr Integer<T>& operator|=(const Integer<T>& other) { _data |= other._data; return *this; }
		constexpr Integer<T>& operator^=(const Integer<T>& other) { _data ^= other._data; return *this; }
		template<class rightT, std::enable_if_t<std::is_integral_v<rightT>, int> = 0>
		constexpr Integer<T>& operator>>=(const rightT& other) { _data >>= other; return *this; }
		template<class rightT, std::enable_if_t<std::is_integral_v<rightT>, int> = 0>
		constexpr Integer<T>& operator<<=(const rightT& other) { _data <<= other; return *this; }
		[[nodiscard]] constexpr bool operator==(const Integer<T>& other) const { return _data == other._data; }
		[[nodiscard]] constexpr bool operator!=(const Integer<T>& other) const { return _data != other._data; }

		[[nodiscard]] constexpr Integer<T> operator+() const
		{
			if constexpr (Traits::HasPromotion<T>) { return Integer<T>(T(+_data)); }
			else { return *this; }
		}
		[[nodiscard]] constexpr Integer<T> operator-() const
		{
			if constexpr (Traits::HasPromotion<T>) { return Integer<T>(T(-_data)); }
			else { return Integer(~_data); }
		}
		[[nodiscard]] constexpr Integer<T> operator+(const Integer<T>& other) const
		{
			if constexpr (Traits::HasAddition<T, T>) { return Integer<T>(T(_data + other._data)); }
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
			if constexpr (Traits::HasAddition<T, T>) { return Integer<T>(T(_data - other._data)); }
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
			if constexpr (Traits::HasMultiplication<T, T>) { return Integer<T>(T(_data * other._data)); }
			else
			{
				auto result = Integer<T>();
				for (auto i: Range<size_t>(0, BitWidth<T>).GetStdIterator())
				{
					if (getbit(i)) { result = result + (other << i); }
				}
				return result;
			}
		}
		[[nodiscard]] constexpr Integer<T> operator/(const Integer<T>& other) const
		{
			if constexpr (Traits::HasDivision<T, T>) { return Integer<T>(T(_data / other._data)); }
			else { return divide_impl(other).Value; }
		}
		[[nodiscard]] constexpr Integer<T> operator%(const Integer<T>& other) const
		{
			if constexpr (Traits::HasModulation<T, T>) { return Integer<T>(T(_data % other._data)); }
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
			else { return Compare(other) < 0; }
		}
		[[nodiscard]] constexpr bool operator<=(const Integer<T>& other) const
		{
			if constexpr (Traits::HasSmallerCompare<T, T>) { return _data <= other._data; }
			else { return Compare(other) <= 0; }
		}
		[[nodiscard]] constexpr bool operator>(const Integer<T>& other) const
		{
			if constexpr (Traits::HasSmallerCompare<T, T>) { return _data > other._data; }
			else { return Compare(other) > 0; }
		}
		[[nodiscard]] constexpr bool operator>=(const Integer<T>& other) const
		{
			if constexpr (Traits::HasSmallerCompare<T, T>) { return _data >= other._data; }
			else { return Compare(other) >= 0; }
		}

		[[nodiscard]] static constexpr Integer<T> Max() { return Integer<T>(T(~value_construct<uint8_t>(0))); }
		[[nodiscard]] static constexpr Integer<T> Min() { return Integer<T>(value_construct<uint8_t>(0)); }
		[[nodiscard]] static constexpr Integer<T> Epsilon() { return Integer<T>(value_construct<uint8_t>(1)); }
	private:
		template<class fromT, std::enable_if_t< std::is_convertible_v<ValueType, fromT> || Traits::IsAggregatable<ValueType, fromT> || std::is_constructible_v<ValueType, fromT>, int> = 0>
		[[nodiscard]] static constexpr ValueType value_construct(const fromT& value)
		{
			if constexpr (std::is_convertible_v<ValueType, fromT>) { return value; }
			if constexpr (Traits::IsAggregatable<ValueType, fromT>) { return ValueType{ value }; }
			if constexpr (std::is_constructible_v<ValueType, fromT>) { return ValueType(value); }
		}
		[[nodiscard]] constexpr bool getbit(const size_t& index) const
		{
			if (BitWidth<T> <= index) { throw std::out_of_range("指定されたインデックスはこのオブジェクトの境界を超えています。"); }
			return (_data & (value_construct<uint8_t>(1) << index)) != ValueType(0);
		}
		constexpr void setbit(const size_t& index, const bool& value)
		{
			if (BitWidth<T> <= index) { throw std::out_of_range("指定されたインデックスはこのオブジェクトの境界を超えています。"); }
			_data = (_data & ~(value_construct<uint8_t>(1) << index)) | (value?(value_construct<uint8_t>(1) << index):(value_construct<uint8_t>(0)));
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
				Integer<T> div = Integer<T>(T(other._data << i));
				if (div <= surplus)
				{
					result._data |= value_construct<uint8_t>(1) << i;
					surplus -= div;
				}
			}
			return DivisionResult<Integer<T>>{ result, surplus };
		}
	};

	template<class T>
	struct SignedInteger final
	{
		static_assert(Traits::IsBitSequenceType<T>, "テンプレート引数型 T はビット列である必要があります。");
		template<class> friend class Integer;
		template<class> friend class SignedInteger;
	public:
		typedef T ValueType;
		typedef Integer<T> UnsignedType;
	private:
		ValueType _data;
	public:
		SignedInteger() = default;
		constexpr explicit SignedInteger(const ValueType& value) noexcept : _data(value) {}
		template<class fromT, std::enable_if_t< std::is_convertible_v<ValueType, fromT> || Traits::IsAggregatable<ValueType, fromT> || std::is_constructible_v<ValueType, fromT>, int> = 0>
		constexpr explicit SignedInteger(const fromT& value) : _data(value_construct<fromT>(value)) {}
		template<class fromT, std::enable_if_t< !(std::is_convertible_v<ValueType, fromT> || Traits::IsAggregatable<ValueType, fromT> || std::is_constructible_v<ValueType, fromT>) && Traits::IsIntegralType<fromT> && std::numeric_limits<fromT>::is_signed, int> = 0>
		constexpr explicit SignedInteger(const fromT& value) : SignedInteger()
		{
			auto v = value;
			for (auto i: Range<size_t>(0, BitWidth<T>).GetStdIterator())
			{
				setbit(i, (v % 2) != fromT(0));
				v /= 2;
				if (v == fromT(0)) { break; }
			}
			if (value < fromT(0))
			{
				_data = ~_data;
				++(*this);
			}
		}
		template<class fromT>
		constexpr explicit SignedInteger(const SignedInteger<fromT>& from) : SignedInteger()
		{
			for (auto i: Range<size_t>(0, std::min(BitWidth<fromT>, BitWidth<T>)).GetStdIterator()) { setbit(i, from.getbit(i)); }
		}
		constexpr explicit SignedInteger(const UnsignedType& from) noexcept : _data(from.Data()) {}
		constexpr SignedInteger(const ZeroValue_t&) noexcept : _data(value_construct<uint8_t>(0)) {}

		[[nodiscard]] constexpr const ValueType& Data() const noexcept { return _data; }
		[[nodiscard]] constexpr explicit operator ValueType() const { return _data; }

		[[nodiscard]] constexpr SignedInteger<T> operator~() const { return SignedInteger(T(~_data)); }
		[[nodiscard]] constexpr SignedInteger<T> operator&(const SignedInteger<T>& other) const { return SignedInteger(T(_data & other._data)); }
		[[nodiscard]] constexpr SignedInteger<T> operator|(const SignedInteger<T>& other) const { return SignedInteger(T(_data | other._data)); }
		[[nodiscard]] constexpr SignedInteger<T> operator^(const SignedInteger<T>& other) const { return SignedInteger(T(_data ^ other._data)); }
		template<class rightT, std::enable_if_t<std::is_integral_v<rightT>, int> = 0>
		[[nodiscard]] constexpr SignedInteger<T> operator>>(const rightT& other) const { return SignedInteger(T(_data >> other)); }
		template<class rightT, std::enable_if_t<std::is_integral_v<rightT>, int> = 0>
		[[nodiscard]] constexpr SignedInteger<T> operator<<(const rightT& other) const { return SignedInteger(T(_data << other)); }
		constexpr SignedInteger<T>& operator&=(const SignedInteger<T>& other) { _data &= other._data; return *this; }
		constexpr SignedInteger<T>& operator|=(const SignedInteger<T>& other) { _data |= other._data; return *this; }
		constexpr SignedInteger<T>& operator^=(const SignedInteger<T>& other) { _data ^= other._data; return *this; }
		template<class rightT, std::enable_if_t<std::is_integral_v<rightT>, int> = 0>
		constexpr SignedInteger<T>& operator>>=(const rightT& other) { _data >>= other; return *this; }
		template<class rightT, std::enable_if_t<std::is_integral_v<rightT>, int> = 0>
		constexpr SignedInteger<T>& operator<<=(const rightT& other) { _data <<= other; return *this; }
		[[nodiscard]] constexpr bool operator==(const SignedInteger<T>& other) const { return _data == other._data; }
		[[nodiscard]] constexpr bool operator!=(const SignedInteger<T>& other) const { return _data != other._data; }

		[[nodiscard]] constexpr SignedInteger<T> operator+() const
		{
			return *this;
		}
		[[nodiscard]] constexpr SignedInteger<T> operator-() const
		{
			return ++SignedInteger(T(~_data));
		}
		[[nodiscard]] constexpr SignedInteger<T> operator+(const SignedInteger<T>& other) const
		{
			auto result = SignedInteger<T>();
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
		[[nodiscard]] constexpr SignedInteger<T> operator-(const SignedInteger<T>& other) const
		{
			auto result = SignedInteger<T>();
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
		[[nodiscard]] constexpr SignedInteger<T> operator*(const SignedInteger<T>& other) const
		{
			auto result = SignedInteger<T>();
			auto ov = other ^ (Epsilon() << (BitWidth<T> - 1));
			for (auto i: Range<size_t>(0, BitWidth<T> - 1).GetStdIterator())
			{
				if (getbit(i)) { result = result + (ov << i); }
			}
			return result;
		}
		[[nodiscard]] constexpr SignedInteger<T> operator/(const SignedInteger<T>& other) const
		{
			return divide_impl(other).Value;
		}
		[[nodiscard]] constexpr SignedInteger<T> operator%(const SignedInteger<T>& other) const
		{
			return divide_impl(other).Mod;
		}

		constexpr SignedInteger<T>& operator+=(const SignedInteger<T>& other) { *this = *this + other; return *this; }
		constexpr SignedInteger<T>& operator-=(const SignedInteger<T>& other) { *this = *this - other; return *this; }
		constexpr SignedInteger<T>& operator*=(const SignedInteger<T>& other) { *this = *this * other; return *this; }
		constexpr SignedInteger<T>& operator/=(const SignedInteger<T>& other) { *this = *this / other; return *this; }
		constexpr SignedInteger<T>& operator%=(const SignedInteger<T>& other) { *this = *this % other; return *this; }

		constexpr SignedInteger<T>& operator++()
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
		[[nodiscard]] constexpr SignedInteger<T> operator++(int) { auto result = *this; ++(*this); return result; }
		constexpr SignedInteger<T>& operator--()
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
		[[nodiscard]] constexpr SignedInteger<T> operator--(int) { auto result = *this; --(*this); return result; }

		[[nodiscard]] constexpr int Compare(const SignedInteger<T>& other) const
		{
			bool sa = getbit(BitWidth<T> - 1);
			bool sb = other.getbit(BitWidth<T> - 1);
			if (sa != sb)
			{
				if (sa) { return -1; }
				else { return 1; }
			}
			for (auto i: Range<size_t>(0, BitWidth<T> - 1).GetStdReverseIterator())
			{
				auto a = getbit(i);
				auto b = other.getbit(i);
				if (getbit(i) != other.getbit(i))
				{
					if (Algorithms::Xor(getbit(i), sa)) { return 1; }
					else { return -1; }
				}
			}
			return 0;
		}
		[[nodiscard]] constexpr bool operator<(const SignedInteger<T>& other) const
		{
			return Compare(other) < 0;
		}
		[[nodiscard]] constexpr bool operator<=(const SignedInteger<T>& other) const
		{
			return Compare(other) <= 0;
		}
		[[nodiscard]] constexpr bool operator>(const SignedInteger<T>& other) const
		{
			return Compare(other) > 0;
		}
		[[nodiscard]] constexpr bool operator>=(const SignedInteger<T>& other) const
		{
			return Compare(other) >= 0;
		}

		[[nodiscard]] static constexpr SignedInteger<T> Max() { return ~Min(); }
		[[nodiscard]] static constexpr SignedInteger<T> Min() { return Epsilon() << (BitWidth<T> - 1); }
		[[nodiscard]] static constexpr SignedInteger<T> Epsilon() { return SignedInteger<T>(value_construct<uint8_t>(1)); }
	private:
		template<class fromT, std::enable_if_t< std::is_convertible_v<ValueType, fromT> || Traits::IsAggregatable<ValueType, fromT> || std::is_constructible_v<ValueType, fromT>, int> = 0>
		[[nodiscard]] static constexpr ValueType value_construct(const fromT& value)
		{
			if constexpr (std::is_convertible_v<ValueType, fromT>) { return value; }
			if constexpr (Traits::IsAggregatable<ValueType, fromT>) { return ValueType{ value }; }
			if constexpr (std::is_constructible_v<ValueType, fromT>) { return ValueType(value); }
		}
		[[nodiscard]] constexpr bool getbit(const size_t& index) const
		{
			if (BitWidth<T> <= index) { throw std::out_of_range("指定されたインデックスはこのオブジェクトの境界を超えています。"); }
			return (_data & (value_construct<uint8_t>(1) << index)) != ValueType(0);
		}
		constexpr void setbit(const size_t& index, const bool& value)
		{
			if (BitWidth<T> <= index) { throw std::out_of_range("指定されたインデックスはこのオブジェクトの境界を超えています。"); }
			_data = (_data & ~(value_construct<uint8_t>(1) << index)) | (value?(value_construct<uint8_t>(1) << index):(value_construct<uint8_t>(0)));
		}
		[[nodiscard]] constexpr DivisionResult<SignedInteger<T>> divide_impl(const SignedInteger<T>& other) const
		{
			auto vb = (other < Zero)?(-other):(other);
			size_t w = 0;
			for (auto i: Range<size_t>(0, BitWidth<T>).GetStdIterator())
			{
				if (vb.getbit(i)) { w = i; }
			}
			auto result = SignedInteger<T>();
			SignedInteger<T> surplus = (*this < Zero)?(-(*this)):(*this);
			for (auto i: Range<size_t, true, true>(0, w).GetStdReverseIterator())
			{
				SignedInteger<T> div = SignedInteger<T>(vb._data << i);
				if (div <= surplus)
				{
					result._data |= value_construct<uint8_t>(1) << i;
					surplus -= div;
				}
			}
			return DivisionResult<SignedInteger<T>>{ (Algorithms::Xor(*this < Zero, other < Zero))?(-result):(result), (Algorithms::Xor(*this < Zero, other < Zero))?(-surplus):(surplus) };
		}
	};

	extern template struct Integer<std::byte>;
	extern template struct Integer<uint8_t>;
	extern template struct Integer<uint16_t>;
	extern template struct Integer<uint32_t>;
	extern template struct Integer<uint64_t>;
	extern template struct SignedInteger<std::byte>;
	extern template struct SignedInteger<uint8_t>;
	extern template struct SignedInteger<uint16_t>;
	extern template struct SignedInteger<uint32_t>;
	extern template struct SignedInteger<uint64_t>;
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
	template<class T>
	class numeric_limits<zawa_ch::StationaryOrbit::SignedInteger<T>> : public numeric_limits<void>
	{
	public:
		static constexpr bool is_specialized = true;
		static constexpr bool is_signed = true;
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
		static constexpr bool is_modulo = false;
		static constexpr int digits = zawa_ch::StationaryOrbit::BitWidth<T> - 1;
		static constexpr int digits10 = int(digits * 0.30102999566398119521373889472449);
		static constexpr int max_digits10 = 0;
		static constexpr int radix = 2;
		static constexpr int min_exponent = 0;
		static constexpr int min_exponent10 = 0;
		static constexpr int max_exponent = 0;
		static constexpr int max_exponent10 = 0;
		static constexpr bool traps = true;
		static constexpr bool tinyness_before = true;
		static constexpr zawa_ch::StationaryOrbit::SignedInteger<T> min() noexcept { return zawa_ch::StationaryOrbit::SignedInteger<T>::Min(); }
		static constexpr zawa_ch::StationaryOrbit::SignedInteger<T> lowest() noexcept { return zawa_ch::StationaryOrbit::SignedInteger<T>::Min(); }
		static constexpr zawa_ch::StationaryOrbit::SignedInteger<T> max() noexcept { return zawa_ch::StationaryOrbit::SignedInteger<T>::Max(); }
		static constexpr zawa_ch::StationaryOrbit::SignedInteger<T> epsilon() noexcept { return zawa_ch::StationaryOrbit::SignedInteger<T>::Epsilon(); }
		static constexpr zawa_ch::StationaryOrbit::SignedInteger<T> round_error() noexcept { return zawa_ch::StationaryOrbit::SignedInteger<T>::Epsilon(); }
	};
}
#endif // __stationaryorbit_core_integer__
