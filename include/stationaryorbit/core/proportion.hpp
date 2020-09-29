//	stationaryorbit/core/proportion
//	Copyright 2020 zawa-ch.
//
#ifndef __stationaryorbit_core_proportion__
#define __stationaryorbit_core_proportion__
#include <cstdint>
#include <cmath>
#include <type_traits>
#include <stdexcept>
#include "fundamental.hpp"
#include "algorithms.hpp"
#include "range.hpp"
namespace zawa_ch::StationaryOrbit
{
	///	0.0から1.0の値を符号なし整数を用いて保持します。
	///	@param	Tp
	///	値の格納に用いる型。
	///	@note
	///	@a Proportion 型は0.0以上1.0以下の数値を型 @a Tp に格納できるようにします。
	template <class Tp>
	struct Proportion
	{
		template<class> friend struct Proportion;
		static_assert(std::is_unsigned_v<Tp>, "テンプレート型 Tp は符号なし算術型である必要があります。");

	public:
		///	この型の値の表現のために内部で使用されている型。
		typedef Tp ValueType;

	private:
		///	この型の内部で使用されているデータとしての値。
		ValueType _value;

		///	この型のオブジェクトを @a ValueType の値から直接構築します。
		constexpr explicit Proportion(const ValueType& init, const Unit&) noexcept : _value(init) {}

	public:
		///	既定の @a Proportion オブジェクトを作成します。
		constexpr Proportion() noexcept = default;
		///	@a double から値をキャストします。
		constexpr explicit Proportion(const double& from) : Proportion(convertFromFloat(from), UnitValue) {}
		///	分子・分母の値からオブジェクトを作成します。
		constexpr Proportion(const ValueType& numerator, const ValueType& denominator) : Proportion(checkedFraction(numerator, denominator), UnitValue) {}
		///	@a オブジェクトの内部の型をキャストします。
		template<class fromT> constexpr explicit Proportion(const Proportion<fromT>& from) noexcept : Proportion(from.template CastTo<Tp>()) {}
		constexpr Proportion(const Proportion<Tp>&) = default;
		constexpr Proportion(Proportion<Tp>&&) = default;
		~Proportion() = default;

	public:
		///	このオブジェクトの内部で保持している値を取得します。
		[[nodiscard]] constexpr ValueType Data() const noexcept { return _value; }
		///	このオブジェクトが空であるかを評価します。
		constexpr bool IsEmpty() const noexcept { return *this == Empty(); }

		// TODO: 計算結果の完全な情報を保持するResult<T, U>を作成、四則演算メソッドに適用する

		///	このオブジェクトを昇格します。
		[[nodiscard]] constexpr Proportion<Tp> Promote() const noexcept { return DirectConstruct(+_value); }
		///	このオブジェクトの反数を求めます。
		[[nodiscard]] constexpr Proportion<Tp> Invert() const noexcept { return DirectConstruct(-_value); }
		///	このオブジェクトと指定されたオブジェクトの和を求めます。
		[[nodiscard]] constexpr Proportion<Tp> Add(const Proportion<Tp>& other) const noexcept { return Proportion(Tp(_value + other._value), UnitValue); }
		///	このオブジェクトと指定されたオブジェクトの差を求めます。
		[[nodiscard]] constexpr Proportion<Tp> Sub(const Proportion<Tp>& other) const noexcept { return Proportion(Tp(_value - other._value), UnitValue); }
		///	このオブジェクトと指定されたオブジェクトの積を求めます。
		[[nodiscard]] constexpr Proportion<Tp> Mul(const Proportion<Tp>& other) const noexcept { return Proportion(multiple_inner(_value, other._value), UnitValue); }
		///	このオブジェクトと指定されたオブジェクトの商を求めます。
		[[nodiscard]] constexpr Proportion<Tp> Div(const Proportion<Tp>& other) const noexcept { return Proportion(Algorithms::IntegralFraction(_value, other._value, std::numeric_limits<Tp>::max()), UnitValue); }
		///	このオブジェクトと指定されたオブジェクトの和を求めます。
		///	計算結果がオーバーフローする場合、表現できる値域に丸めを行います。
		[[nodiscard]] constexpr Proportion<Tp> SaturateAdd(const Proportion<Tp>& other) const noexcept
		{
			if ((Max()._value - other._value) <= _value) { return Proportion(Tp(_value + other._value)); }
			else { return Max(); }
		}
		///	このオブジェクトと指定されたオブジェクトの差を求めます。
		///	計算結果がオーバーフローする場合、表現できる値域に丸めを行います。
		[[nodiscard]] constexpr Proportion<Tp> SaturateSub(const Proportion<Tp>& other) const noexcept
		{
			if (other._value <= _value) { return Proportion(Tp(_value - other._value)); }
			else { return Min(); }
		}
		///	このオブジェクトと指定されたオブジェクトの積を求めます。
		///	計算結果がオーバーフローする場合、表現できる値域に丸めを行います。
		[[nodiscard]] constexpr Proportion<Tp> SaturateMul(const Proportion<Tp>& other) const noexcept
		{
			// note: この型で表せる値域のどの組み合わせでもオーバーフローは発生しない
			return Proportion(multiple_inner(_value, other._value));
		}
		///	このオブジェクトと指定されたオブジェクトの商を求めます。
		///	計算結果がオーバーフローする場合、表現できる値域に丸めを行います。
		[[nodiscard]] constexpr Proportion<Tp> SaturateDiv(const Proportion<Tp>& other) const noexcept
		{
			if (other._value < _value) { return Max(); }
			return Proportion(checkedFraction(_value, other._value));
		}
		///	このオブジェクトと指定されたオブジェクトの和を求めます。
		///	計算結果がオーバーフローする場合、例外をスローします。
		///	@exception
		///	std::overflow_error
		///	計算結果がオーバーフローしました。
		[[nodiscard]] constexpr Proportion<Tp> CheckedAdd(const Proportion<Tp>& other) const
		{
			if ((Max()._value - other._value) <= _value) { return Proportion(Tp(_value + other._value)); }
			else { throw std::overflow_error("計算結果はこの型で表せる範囲を超えています。"); }
		}
		///	このオブジェクトと指定されたオブジェクトの差を求めます。
		///	計算結果がオーバーフローする場合、例外をスローします。
		///	@exception
		///	std::overflow_error
		///	計算結果がオーバーフローしました。
		[[nodiscard]] constexpr Proportion<Tp> CheckedSub(const Proportion<Tp>& other) const
		{
			if (other._value <= _value) { return Proportion(Tp(_value - other._value)); }
			else { throw std::overflow_error("計算結果はこの型で表せる範囲を超えています。"); }
		}
		///	このオブジェクトと指定されたオブジェクトの積を求めます。
		///	計算結果がオーバーフローする場合、例外をスローします。
		///	@exception
		///	std::overflow_error
		///	計算結果がオーバーフローしました。
		[[nodiscard]] constexpr Proportion<Tp> CheckedMul(const Proportion<Tp>& other) const
		{
			// note: この型で表せる値域のどの組み合わせでもオーバーフローは発生しない
			return Proportion(multiple_inner(_value, other._value));
		}
		///	このオブジェクトと指定されたオブジェクトの商を求めます。
		///	計算結果がオーバーフローする場合、例外をスローします。
		///	@exception
		///	std::overflow_error
		///	計算結果がオーバーフローしました。
		[[nodiscard]] constexpr Proportion<Tp> CheckedDiv(const Proportion<Tp>& other) const
		{ return Proportion(checkedFraction(_value, other._value)); }
		///	この値の平方数を取得します。
		[[nodiscard]] constexpr Proportion<Tp> Square() const noexcept { return Mul(*this); }
		///	この値の平方根を取得します。
		[[nodiscard]] constexpr Proportion<Tp> Sqrt() const noexcept
		{
			ValueType result = _value;
			ValueType b = _value;
			do	// X[n+1] = (X[N] + a / X[N]) / 2
			{
				// 0除算の回避(sqrt(0) = 0)
				if (result == 0U) { break; }
				b = result;	///< 前回値(X[N])保持
				// a / X[N] の導出
				ValueType delta = Algorithms::IntegralFraction(_value, b, std::numeric_limits<Tp>::max());
				// X[N] / 2
				result /= 2;
				// 剰余分の計算
				result += ((result % 2) + (delta % 2)) / 2;
				// (a / X[n]) / 2
				result += delta / 2;
			} while (2U < ((result < b)?(b-result):(result - b)));
			return Proportion<Tp>(result, UnitValue);
		}

		[[nodiscard]] constexpr Proportion<Tp> operator+() const noexcept { return Promote(); }
		[[nodiscard]] constexpr Proportion<Tp> operator-() const noexcept { return Invert(); }
		[[nodiscard]] constexpr Proportion<Tp> operator+(const Proportion<Tp>& other) const noexcept { return Add(other); }
		[[nodiscard]] constexpr Proportion<Tp> operator-(const Proportion<Tp>& other) const noexcept { return Sub(other); }
		[[nodiscard]] constexpr Proportion<Tp> operator*(const Proportion<Tp>& other) const noexcept { return Mul(other); }
		[[nodiscard]] constexpr Proportion<Tp> operator/(const Proportion<Tp>& other) const noexcept { return Div(other); }
		[[nodiscard]] constexpr Proportion<Tp>& operator+=(const Proportion<Tp>& other) noexcept { return *this = *this + other; }
		[[nodiscard]] constexpr Proportion<Tp>& operator-=(const Proportion<Tp>& other) noexcept { return *this = *this - other; }
		[[nodiscard]] constexpr Proportion<Tp>& operator*=(const Proportion<Tp>& other) noexcept { return *this = *this * other; }
		[[nodiscard]] constexpr Proportion<Tp>& operator/=(const Proportion<Tp>& other) noexcept { return *this = *this / other; }

		[[nodiscard]] constexpr bool Equals(const Proportion<Tp>& other) const noexcept { return _value == other._value; }
		[[nodiscard]] constexpr bool operator==(const Proportion<Tp>& other) const noexcept { return Equals(other); }
		[[nodiscard]] constexpr bool operator!=(const Proportion<Tp>& other) const noexcept { return !Equals(other); }

		[[nodiscard]] constexpr int Compare(const Proportion<Tp>& other) const noexcept
		{
			if (_value > other._value) { return 1; }
			else if (_value < other._value) { return -1; }
			else { return 0; }
		}
		[[nodiscard]] constexpr bool operator<(const Proportion<Tp>& other) const noexcept { return Compare(other) < 0; }
		[[nodiscard]] constexpr bool operator>(const Proportion<Tp>& other) const noexcept { return Compare(other) > 0; }
		[[nodiscard]] constexpr bool operator<=(const Proportion<Tp>& other) const noexcept { return Compare(other) <= 0; }
		[[nodiscard]] constexpr bool operator>=(const Proportion<Tp>& other) const noexcept { return Compare(other) >= 0; }

		[[nodiscard]] Proportion<Tp>& operator=(const Proportion<Tp>& value) = default;
		[[nodiscard]] Proportion<Tp>& operator=(Proportion<Tp>&& value) = default;

		[[nodiscard]] constexpr explicit operator float() const { return convertToFloat<float>(); }
		[[nodiscard]] constexpr explicit operator double() const { return convertToFloat<double>(); }
		///	内部に使用する型のキャストを行います。
		///	@param	castT
		///	変換先の型。返ってくる値の型は @a Proportion&lt;castT&gt; となります。
		template<class castT>
		[[nodiscard]] constexpr Proportion<castT> CastTo() const noexcept
		{
			static_assert(std::is_unsigned_v<Tp>, "テンプレートの特殊化に失敗しました(テンプレート型 Tp は符号なし算術型ではありません)。");
			static_assert(std::is_unsigned_v<castT>, "テンプレートの特殊化に失敗しました(テンプレート型 castT は符号なし算術型ではありません)。");
			if constexpr (std::is_same_v<Tp, castT>)
			{
				return Proportion<castT>(_value);
			}
			else
			{
				if constexpr (std::is_integral_v<Tp> && std::is_integral_v<castT>)
				{
					if constexpr (sizeof(Tp) < sizeof(castT))
					{
						const size_t length = sizeof(Tp) * 8U;
						const size_t itr = (sizeof(castT) * 8U) / length;
						const size_t mod = (sizeof(castT) * 8U) % length;
						auto result = castT(_value) >> ((length - mod) % length);
						for (auto i : Range<size_t>(0, itr))
						{
							result |= castT(_value) << ((length * i) + mod);
						}
						return Proportion<castT>(result, UnitValue);
					}
					else
					{
						const size_t length = (sizeof(Tp) - sizeof(castT)) * 8U;
						return Proportion<castT>(castT(_value >> length), UnitValue);
					}
				}
				else
				{
					if constexpr (std::is_same_v<Tp, bool> && std::is_integral_v<castT>)
					{
						return (_value)?(Proportion<castT>::Max()):(Proportion<castT>::Min());
					}
					if constexpr (std::is_integral_v<Tp> && std::is_same_v<castT, bool>)
					{
						const size_t length = sizeof(Tp) * 8U;
						return Proportion<castT>((_value >> (length - 1)) != 0, UnitValue);
					}
				}
			}
		}

	public:
		///	この型のオブジェクトを @a ValueType の値から直接構築します。
		[[nodiscard]] constexpr static Proportion<Tp> DirectConstruct(const ValueType& value) noexcept { return Proportion<Tp>(value, UnitValue); }
		///	この型で表すことのできる最大の値を取得します。
		[[nodiscard]] constexpr static Proportion<Tp> Max() noexcept
		{
			static_assert(std::is_unsigned_v<Tp>, "テンプレートの特殊化に失敗しました(テンプレート型 Tp は符号なし算術型ではありません)。");
			if constexpr (std::is_same_v<Tp, bool>) { return Proportion<Tp>(true, UnitValue); }
			else { return Proportion<Tp>(std::numeric_limits<Tp>::max(), UnitValue); }
		}
		///	この型で表すことのできる最小の値を取得します。
		[[nodiscard]] constexpr static Proportion<Tp> Min() noexcept
		{
			static_assert(std::is_unsigned_v<Tp>, "テンプレートの特殊化に失敗しました(テンプレート型 Tp は符号なし算術型ではありません)。");
			if constexpr (std::is_same_v<Tp, bool>) { return Proportion<Tp>(false, UnitValue); }
			else { return Proportion<Tp>(std::numeric_limits<Tp>::min(), UnitValue); }
		}
		///	この型で表すことのできる零値を取得します。
		[[nodiscard]] constexpr static Proportion<Tp> Zero() noexcept
		{
			return Proportion<Tp>(Tp(0), UnitValue);
		}
		///	空のオブジェクトを取得します。
		[[nodiscard]] constexpr static Proportion<Tp> Empty() noexcept
		{
			return Proportion<Tp> {};
		}

	private:
		///	値域チェックが行われる除算を行います。
		///	@param	numerator
		///	除算時の被除数。
		///	@param	denominator
		///	除算時の除数。
		///	@exception
		///	std::invalid_argument
		///	0で除算することはできません。
		///	std::overflow_error
		///	被除数が除数を超えました。
		static constexpr ValueType checkedFraction(const ValueType& numerator, const ValueType& denominator)
		{
			if constexpr ((std::is_integral_v<ValueType>)&&(std::is_unsigned_v<ValueType>))
			{
				if (denominator < numerator) { throw std::overflow_error("計算結果はこの型で表せる範囲を超えています。"); }
				return Algorithms::IntegralFraction(numerator, denominator, std::numeric_limits<Tp>::max());
			}
			else
			{
				return Algorithms::IntegralFraction(numerator, denominator, std::numeric_limits<Tp>::max());
			}
		}
		static constexpr ValueType multiple_inner(const ValueType& left, const ValueType& right)
		{
			if constexpr (std::is_floating_point_v<ValueType>) { return left * right; }
			if constexpr ((std::is_integral_v<ValueType>)&&(std::is_unsigned_v<ValueType>))
			{
				ValueType result = 0UL;
				for(size_t i = 0U; i < (sizeof(ValueType) * 8U); i++)
				{
					ValueType ad = 0U;
					if (left & (ValueType(1U) << (i)))
					{
						ad = right;
					}
					bool cr = ((ad % 2U) != 0) && ((result % 2U) != 0);
					result >>= 1;
					ad >>= 1;
					result += ad + (cr?1U:0U);
				}
				return result;
			}
			if constexpr (std::is_same_v<ValueType, bool>)
			{
				return left && right;
			}
		}
		template<class fromT>
		static constexpr ValueType convertFromFloat(const fromT& value)
		{
			if ((value == std::numeric_limits<double>::quiet_NaN()) || (value == std::numeric_limits<double>::signaling_NaN())) { throw std::invalid_argument("指定する値はNaNであってはなりません。"); }
			if ((value < 0.0) || (1.0 < value)) { throw std::overflow_error("指定された値がこの型で表せる範囲を超えています。"); }
			if constexpr (std::is_integral_v<Tp>) { return ValueType(round(value * fromT(std::numeric_limits<ValueType>::max()))); }
		}
		template<class castT>
		constexpr castT convertToFloat() const
		{
			return castT(_value) / castT(std::numeric_limits<ValueType>::max());
		}
	};

	extern template class Proportion<bool>;
	extern template class Proportion<uint8_t>;
	extern template class Proportion<uint16_t>;
	extern template class Proportion<uint32_t>;
	extern template class Proportion<uint64_t>;

	typedef Proportion<bool> Proportion1_t;
	typedef Proportion<uint8_t> Proportion8_t;
	typedef Proportion<uint16_t> Proportion16_t;
	typedef Proportion<uint32_t> Proportion32_t;
	typedef Proportion<uint64_t> Proportion64_t;
}
#endif // __stationaryorbit_core_proportion__
