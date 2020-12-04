//	stationaryorbit/core/range
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
#ifndef __stationaryorbit_core_range__
#define __stationaryorbit_core_range__
#include <limits>
#include <type_traits>
#include <stdexcept>
#include "traits.hpp"
#include "iterator.hpp"
namespace zawa_ch::StationaryOrbit
{
	template<class T, bool floor_included, bool ceiling_included> class Range;
	template<class T, bool floor_included, bool ceiling_included> class RangeIterator;

	///	二つの値に囲まれた範囲を表します。
	///	@param	T
	///	値を表現する型。
	///	@param	floor_included
	///	範囲に下限値そのものを含むかどうか。
	///	@param	ceiling_included
	///	範囲に上限値そのものを含むかどうか。
	template<typename T, bool floor_included = true, bool ceiling_included = false>
	struct Range final
	{
		static_assert(Traits::HasArithmeticOperation<T>, "この型のテンプレート T は算術型のクラスである必要があります。");
		static_assert(Traits::Comparable<T>, "この型のテンプレート T は比較可能である必要があります。");

	public: // type
		///	値の表現に使用されている型。
		typedef T ValueType;
		///	この @a Range の型。
		typedef Range<T, floor_included, ceiling_included> RangeType;
		///	この @a Range のイテレータ。
		typedef RangeIterator<T, floor_included, ceiling_included> IteratorType;

	private: // contains
		ValueType _bottom;
		ValueType _top;

	public: // constructor
		///	オブジェクトを既定の値で初期化します。
		constexpr Range() = default;
		///	値を指定してオブジェクトを構築します。
		constexpr Range(const T& bottom, const T& top) noexcept : _bottom(bottom), _top(top) {}

	public: // menber
		///	範囲の下限値を取得します。
		ValueType GetFloor() const { return _bottom; }
		///	範囲の上限値を取得します。
		ValueType GetCeiling() const { return _top; }
		///	範囲の長さを求めます。
		ValueType Length() const
		{
			if ((_bottom < 0)&&((std::numeric_limits<ValueType>::max() - _bottom) < _top)) { throw std::overflow_error("計算結果がテンプレートで指定されている型の最大値を超えています。"); }

			if (_top < _bottom) { return ValueType(0); }
			else if (_top < 0) { return ValueType(-(-_top + _bottom)); }
			else if (_bottom < 0) { return ValueType(_top) + ValueType(-_bottom); }
			else { return ValueType(_top - _bottom); }
		}

		///	指定された値が範囲に含まれているかを検査します。
		///	@param	value
		///	検査を行う値
		///	@return
		///	範囲に含まれれば @a true を返します。そうでなければ @a false を返します。
		constexpr bool isIncluded(const T& value) const { return isOverBottom(value) && isUnderTop(value); }

		///	指定された値が範囲より大きいかを検査します。
		///	@param	value
		///	検査を行う値
		///	@return
		///	範囲より大きければ @a true を返します。そうでなければ @a false を返します。
		constexpr bool isAbove(const T& value) const { return isOverBottom(value) && !isUnderTop(value); }
		bool operator<(const T& value) const { return isAbove(value); }

		///	指定された値が範囲より小さいかを検査します。
		///	@param	value
		///	検査を行う値
		///	@return
		///	範囲より小さければ @a true を返します。そうでなければ @a false を返します。
		constexpr bool isLess(const ValueType& value) const { return !isOverBottom(value) && isUnderTop(value); }
		bool operator>(const ValueType& value) const { return isLess(value); }

		constexpr bool isOverBottom(const ValueType& value) const noexcept { if constexpr (floor_included) { return _bottom <= value; } else { return _bottom < value; } }
		constexpr bool isUnderTop(const ValueType& value) const noexcept { if constexpr (ceiling_included) { return value <= _top; } else { return value < _top; } }

		constexpr IteratorType GetIteratorBegin() const noexcept { return IteratorType(*this, IteratorOrigin::Begin); }
		constexpr IteratorType GetIteratorEnd() const noexcept { return IteratorType(*this, IteratorOrigin::End); }
		IteratorAdaptContainer<IteratorType> GetStdIterator() const noexcept { return IteratorAdaptContainer<IteratorType>(GetIteratorBegin()); }
		IteratorReverseAdaptContainer<IteratorType> GetStdReverseIterator() const noexcept { return IteratorReverseAdaptContainer<IteratorType>(GetIteratorBegin()); }

	public: // equatable

		///	指定されたオブジェクトがこのオブジェクトと等価であることを判定します。
		constexpr bool Equals(const Range<ValueType, floor_included, ceiling_included>& value) const { return (_bottom == value._bottom)&&(_top == value._top); }
		bool operator==(const Range<ValueType, floor_included, ceiling_included>& value) const { return Equals(value); }
		bool operator!=(const Range<ValueType, floor_included, ceiling_included>& value) const { return !Equals(value); }
	};

	///	@a Range の区間内を反復するためのイテレータを提供します。
	template<class T, bool floor_included = true, bool ceiling_included = false>
	class RangeIterator
	{
		static_assert(Traits::HasArithmeticOperation<T>, "この型のテンプレート T は算術型のクラスである必要があります。");
		static_assert(Traits::Comparable<T>, "この型のテンプレート T は比較可能である必要があります。");
		static_assert(Traits::IsBidirectionalOrder<T>, "この型のテンプレート T は双方向の順序を持つ値型である必要があります。");

	public: // type

		///	値の表現に使用されている型。
		typedef T ValueType;
		///	スライシング元の @a Range の型。
		typedef Range<T, floor_included, ceiling_included> RangeType;
		typedef RangeIterator<T, floor_included, ceiling_included> IteratorType;

	private: // contains

		const RangeType _range;
		ValueType _value;

	public: // constructor

		constexpr RangeIterator(const RangeType& range) noexcept : RangeIterator(range, IteratorOrigin::Begin) {}
		constexpr RangeIterator(const RangeType& range, const IteratorOrigin& origin) : _range(range), _value(getOrigin(range, origin)) {}

	public: // member

		///	このイテレータの現在示している値を取得します。
		constexpr const ValueType& Current() const noexcept { return _value; }
		///	このイテレータが示している値を取得できるかを返します。
		constexpr bool HasValue() const noexcept { return _range.isIncluded(_value); }
		///	このイテレータが最初の位置より前にあるかを取得します。
		constexpr bool IsBeforeBegin() const noexcept { return !_range.isOverBottom(_value); }
		///	このイテレータが最後の位置より後にあるかを取得します。
		constexpr bool IsAfterEnd() const noexcept { return !_range.isUnderTop(_value); }
		///	このイテレータを次に進めます。
		constexpr bool Next() noexcept { return _range.isUnderTop(_range.isUnderTop(_value)?(++_value):(_value)); }
		///	このイテレータを前に進めます。
		constexpr bool Previous() noexcept { return _range.isOverBottom(_range.isOverBottom(_value)?(--_value):(_value)); }
		///	このイテレータを初期位置に進めます。
		constexpr void Reset() { Reset(IteratorOrigin::Begin); }
		///	このイテレータを初期位置に進めます。
		///	@param	origin
		///	進める初期位置の場所。
		constexpr void Reset(const IteratorOrigin& origin) { _value = getOrigin(_range, origin); }
		///	指定されたオブジェクトがこのオブジェクトと等価であることを判定します。
		constexpr bool Equals(const IteratorType& other) const noexcept { return (_range.Equals(other._range))&&(_value == other._value); }

		constexpr bool operator==(const IteratorType& other) const noexcept { return Equals(other); }
		constexpr bool operator!=(const IteratorType& other) const noexcept { return !Equals(other); }

	private:
		constexpr static ValueType getOrigin(const RangeType& range, const IteratorOrigin& origin)
		{
			switch(origin)
			{
			case IteratorOrigin::Begin:
				return floor_included?(range.GetFloor()):(range.GetFloor() + 1);
			case IteratorOrigin::End:
				return ceiling_included?(range.GetCeiling()):(range.GetCeiling() - 1);
			default:
				throw std::invalid_argument("origin に無効な値が設定されています。");
			}
		}
	};

}
#endif // __stationaryorbit_core_range__
