#ifndef __stationaryorbit_core_range__
#define __stationaryorbit_core_range__
#include <limits>
#include <type_traits>
namespace zawa_ch::StationaryOrbit
{

	template<class T, bool floor_included, bool ceiling_included> class RangeSlice;
	template<class T, bool floor_included, bool ceiling_included> class RangeReverseSlice;

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
		static_assert(std::is_arithmetic<T>::value, "この型のテンプレート T は算術型のクラスである必要があります。");

	public: // type

		///	値の表現に使用されている型。
		typedef T ValueType;
		typedef Range<T, floor_included, ceiling_included> RangeType;
		typedef RangeSlice<T, floor_included, ceiling_included> SliceType;
		typedef RangeReverseSlice<T, floor_included, ceiling_included> RSliceType;

	private: // contains

		ValueType _bottom;	///< 下限値。
		ValueType _top;	///< 上限値。

	public: // constructor

		///	オブジェクトを既定の値で初期化します。
		constexpr Range() = default;

		///	値を指定してオブジェクトを構築します。
		constexpr Range(const T& bottom, const T& top) noexcept : _bottom(bottom), _top(top) {}

	public: // menber

		///	範囲の下限値を取得します。
		ValueType getFloor() const { return _bottom; }
		///	範囲の上限値を取得します。
		ValueType getCailing() const { return _top; }
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

		constexpr SliceType getSlice() const noexcept { return SliceType(*this, floor_included?(_bottom-1):(_bottom)); }

	public: // container

		constexpr SliceType begin() const noexcept { return SliceType(*this, floor_included?(_bottom):(_bottom+1)); }
		constexpr SliceType end() const noexcept { return SliceType(*this, ceiling_included?(_top+1):(_top)); }
		constexpr RSliceType rbegin() const noexcept { return RSliceType(*this, ceiling_included?(_top):(_top-1)); }
		constexpr RSliceType rend() const noexcept { return RSliceType(*this, floor_included?(_bottom-1):(_bottom)); }

	public: // equatable

		///	指定されたオブジェクトがこのオブジェクトと等価であることを判定します。
		constexpr bool Equals(const Range<ValueType, floor_included, ceiling_included>& value) const { return (_bottom == value._bottom)&&(_top == value._top); }
		bool operator==(const Range<ValueType, floor_included, ceiling_included>& value) const { return Equals(value); }
		bool operator!=(const Range<ValueType, floor_included, ceiling_included>& value) const { return !Equals(value); }

	private:

		constexpr bool isOverBottom(const ValueType& value) const noexcept { if constexpr (floor_included) { return _bottom <= value; } else { return _bottom < value; } }
		constexpr bool isUnderTop(const ValueType& value) const noexcept { if constexpr (ceiling_included) { return value <= _top; } else { return value < _top; } }

	};

	///	@a Range の区間内を反復するためのイテレータを提供します。
	template<class T, bool floor_included = true, bool ceiling_included = false>
	class RangeSlice
	{
		static_assert(std::is_integral<T>::value, "この型のテンプレート T は整数型のクラスである必要があります。");
		friend class Range<T, floor_included, ceiling_included>;

	public: // type

		///	値の表現に使用されている型。
		typedef T ValueType;
		///	スライシング元の @a Range の型。
		typedef Range<T, floor_included, ceiling_included> RangeType;
		typedef RangeSlice<T, floor_included, ceiling_included> SliceType;

	private: // contains

		const RangeType _range;
		ValueType _value;

	private: // constructor

		constexpr RangeSlice(const RangeType& range, const ValueType& value) : _range(range), _value(value) {}

	public: // member

		///	このイテレータの現在示している値を取得します。
		ValueType Current() const noexcept { return _value; }
		///	このイテレータを次に進めます。
		bool Next() noexcept { return _range.isUnderTop(++_value); }
		///	このイテレータを初期位置、つまり最初のオブジェクトの前の位置に進めます。
		void Reset() noexcept { _value = floor_included?(_range._bottom-1):(_range._bottom); }
		///	指定されたオブジェクトがこのオブジェクトと等価であることを判定します。
		bool Equals(const SliceType& other) const noexcept { return (_range.Equals(other._range))&&(_value == other._value); }

	public: // implement LegacyIterator

		ValueType operator*() const noexcept { return _value; }
		SliceType& operator++() noexcept { _value++; return *this; }

	public: // implement LegacyInputIterator

		bool operator==(const SliceType& other) const noexcept { return Equals(other); }
		bool operator!=(const SliceType& other) const noexcept { return !Equals(other); }
		const ValueType* operator->() const noexcept { return &_value; }

	public: // implement LegacyBidirectionalIterator

		SliceType& operator--() noexcept { _value--; return *this; }

	};

	///	@a Range の区間内を反復するための逆イテレータを提供します。
	template<class T, bool floor_included = true, bool ceiling_included = false>
	class RangeReverseSlice
	{
		static_assert(std::is_integral<T>::value, "この型のテンプレート T は整数型のクラスである必要があります。");
		friend class Range<T, floor_included, ceiling_included>;

	public: // type

		///	値の表現に使用されている型。
		typedef T ValueType;
		///	スライシング元の @a Range の型。
		typedef Range<T, floor_included, ceiling_included> RangeType;
		typedef RangeReverseSlice<T, floor_included, ceiling_included> RSliceType;

	private: // contains

		const RangeType _range;
		ValueType _value;

	private: // constructor

		constexpr RangeReverseSlice(const RangeType& range, const ValueType& value) : _range(range), _value(value) {}

	public: // member

		///	このイテレータの現在示している値を取得します。
		ValueType Current() const noexcept { return _value; }
		///	このイテレータを次に進めます。
		bool Next() noexcept { return _range.isOverBottom(--_value); }
		///	このイテレータを初期位置、つまり最初のオブジェクトの前の位置に進めます。
		void Reset() noexcept { _value = ceiling_included?(_range._top):(_range._top-1); }
		///	指定されたオブジェクトがこのオブジェクトと等価であることを判定します。
		bool Equals(const RSliceType& other) const noexcept { return (_range.Equals(other._range))&&(_value == other._value); }

	public: // implement LegacyIterator

		ValueType operator*() const noexcept { return _value; }
		RSliceType& operator++() noexcept { _value--; return *this; }

	public: // implement LegacyInputIterator

		bool operator==(const RSliceType& other) const noexcept { return Equals(other); }
		bool operator!=(const RSliceType& other) const noexcept { return !Equals(other); }
		const ValueType* operator->() const noexcept { return &_value; }

	public: // implement LegacyBidirectionalIterator

		RSliceType& operator--() noexcept { _value++; return *this; }

	};

}
#endif // __stationaryorbit_core_range__