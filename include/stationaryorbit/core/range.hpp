#ifndef __StationaryOrbit_Range__
#define __StationaryOrbit_Range__
#include <limits>
#include <type_traits>
namespace zawa_ch::StationaryOrbit
{

	///	二つの値に囲まれた範囲を表します。
	///
	///	@param	T
	///	値を表現する型。
	///
	///	@param	floor_included
	///	範囲に下限値そのものを含むかどうか。
	///
	///	@param	ceiling_included
	///	範囲に上限値そのものを含むかどうか。
	template<typename T, bool floor_included, bool ceiling_included>
	struct Range final
	{
	private:

		T _bottom;	///< 下限値。
		T _top;	///< 上限値。

		constexpr bool isOverBottom(const T& value) const
		{
			if constexpr (floor_included) { return _bottom <= value; }
			else { return _bottom < value; }
		}

		constexpr bool isUnderTop(const T& value) const
		{
			if constexpr (ceiling_included) { return value <= _top; }
			else { return value < _top; }
		}

	public:

		///	オブジェクトを既定の値で初期化します。
		constexpr Range() = default;

		///	値を指定してオブジェクトを構築します。
		constexpr Range(const T& bottom, const T& top) noexcept
			: _bottom(bottom), _top(top)
		{
			static_assert(std::is_arithmetic<T>::value, "この型のテンプレート T は算術型のクラスである必要があります。");
		}

		///	範囲の下限値を取得します。
		T getFloor() const { return _bottom; }

		///	範囲の上限値を取得します。
		T getCailing() const { return _top; }

		///	範囲の長さを求めます。
		T Length() const
		{
			if ((_bottom < 0)&&((std::numeric_limits<T>::max() - _bottom) < _top)) { throw std::overflow_error("計算結果がテンプレートで指定されている型の最大値を超えています。"); }

			if (_top < _bottom) { return T(0); }
			else if (_top < 0) { return T(-(-_top + _bottom)); }
			else if (_bottom < 0) { return T(_top) + T(-_bottom); }
			else { return T(_top - _bottom); }
		}

		///	指定された値が範囲に含まれているかを検査します。
		///
		///	@param	value
		///	検査を行う値
		///
		///	@return
		///	範囲に含まれれば @a true を返します。そうでなければ @a false を返します。
		constexpr bool isIncluded(const T& value) const { return isOverBottom(value) && isUnderTop(value); }

		///	指定された値が範囲より大きいかを検査します。
		///
		///	@param	value
		///	検査を行う値
		///
		///	@return
		///	範囲より大きければ @a true を返します。そうでなければ @a false を返します。
		constexpr bool isAbove(const T& value) const { return isOverBottom(value) && !isUnderTop(value); }
		bool operator<(const T& value) const { return isAbove(value); }

		///	指定された値が範囲より小さいかを検査します。
		///
		///	@param	value
		///	検査を行う値
		///
		///	@return
		///	範囲より小さければ @a true を返します。そうでなければ @a false を返します。
		constexpr bool isLess(const T& value) const { return !isOverBottom(value) && isUnderTop(value); }
		bool operator>(const T& value) const { return isLess(value); }

		///	指定されたオブジェクトがこのオブジェクトと等価であることを判定します。
		bool Equals(const Range<T, floor_included, ceiling_included>& value) const { return (_bottom == value._bottom)&&(_top == value._top); }
		bool operator ==(const Range<T, floor_included, ceiling_included>& value) const { return Equals(value); }
		bool operator !=(const Range<T, floor_included, ceiling_included>& value) const { return !Equals(value); }

	};

}
#endif // __StationaryOrbit_Range__