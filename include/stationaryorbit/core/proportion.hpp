//	stationaryorbit/core/proportion
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
#ifndef __stationaryorbit_core_proportion__
#define __stationaryorbit_core_proportion__
#include <cstdint>
#include <cmath>
#include <type_traits>
#include <stdexcept>
#include "fundamental.hpp"
#include "arithmetic.hpp"
#include "algorithms.hpp"
#include "range.hpp"
#include "zerovalue.hpp"
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
		constexpr explicit Proportion(const int& from) : _value(convertFromInteger(from)) {}
		///	@a double から値をキャストします。
		constexpr explicit Proportion(const double& from) : _value(convertFromFloat(from)) {}
		///	分子・分母の値からオブジェクトを作成します。
		constexpr Proportion(const ValueType& numerator, const ValueType& denominator)
			: Proportion
			(
				[](const auto& n, const auto& d) -> ValueType
				{
					auto v = checkedFraction(n, d);
					return v.Value + (((d/2) <= v.Mod)?(1):(0));
				} (numerator, denominator)
				, UnitValue
			)
		{}
		///	@a オブジェクトの内部の型をキャストします。
		template<class fromT> constexpr explicit Proportion(const Proportion<fromT>& from) noexcept : Proportion(from.template CastTo<Tp>()) {}
		constexpr Proportion(const ZeroValue_t&) : _value(0) {}
		constexpr Proportion(const Proportion<Tp>&) = default;
		constexpr Proportion(Proportion<Tp>&&) = default;
		~Proportion() = default;

	public:
		///	このオブジェクトの内部で保持している値を取得します。
		[[nodiscard]] constexpr ValueType Data() const noexcept { return _value; }
		///	このオブジェクトが空であるかを評価します。
		constexpr bool IsEmpty() const noexcept { return *this == Empty(); }

		///	この値の平方数を取得します。
		[[nodiscard]] constexpr Proportion<Tp> Square() const noexcept { return (*this) * (*this); }
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
				ValueType delta = Algorithms::IntegralFraction(_value, b, std::numeric_limits<Tp>::max()).Value;
				// X[N] / 2
				result /= 2;
				// 剰余分の計算
				result += ((result % 2) + (delta % 2)) / 2;
				// (a / X[n]) / 2
				result += delta / 2;
			} while (2U < ((result < b)?(b-result):(result - b)));
			return Proportion<Tp>(result, UnitValue);
		}

		[[nodiscard]] constexpr Proportion<Tp> operator+() const noexcept { return DirectConstruct(+_value); }
		[[nodiscard]] constexpr Proportion<Tp> operator-() const noexcept { return DirectConstruct(-_value); }
		[[nodiscard]] constexpr Proportion<Tp> operator+(const Proportion<Tp>& other) const noexcept { return Proportion(Tp(_value + other._value), UnitValue); }
		[[nodiscard]] constexpr Proportion<Tp> operator-(const Proportion<Tp>& other) const noexcept { return Proportion(Tp(_value - other._value), UnitValue); }
		[[nodiscard]] constexpr Proportion<Tp> operator*(const Proportion<Tp>& other) const noexcept { return Proportion(multiple_inner(_value, other._value), UnitValue); }
		[[nodiscard]] constexpr Proportion<Tp> operator/(const Proportion<Tp>& other) const noexcept { return Proportion(Algorithms::IntegralFraction(_value, other._value, std::numeric_limits<Tp>::max()).Value, UnitValue); }
		constexpr Proportion<Tp>& operator+=(const Proportion<Tp>& other) noexcept { return *this = *this + other; }
		constexpr Proportion<Tp>& operator-=(const Proportion<Tp>& other) noexcept { return *this = *this - other; }
		constexpr Proportion<Tp>& operator*=(const Proportion<Tp>& other) noexcept { return *this = *this * other; }
		constexpr Proportion<Tp>& operator/=(const Proportion<Tp>& other) noexcept { return *this = *this / other; }

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

		Proportion<Tp>& operator=(const Proportion<Tp>& value) = default;
		Proportion<Tp>& operator=(Proportion<Tp>&& value) = default;

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
						for (auto i : Range<size_t>(0, itr).GetStdIterator())
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
		///	この型で表すことのできる最小の刻み幅を取得します。
		[[nodiscard]] constexpr static Proportion<Tp> Epsilon() noexcept
		{
			return Proportion<Tp>(Tp(1), UnitValue);
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
		static constexpr DivisionResult<ValueType> checkedFraction(const ValueType& numerator, const ValueType& denominator)
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
		static constexpr ValueType convertFromInteger(const fromT& value)
		{
			if constexpr(std::is_same_v<fromT, bool>)
			{
				if(value) { return Max().Data(); }
				else { return Min().Data(); }
			}
			else
			{
				switch(value)
				{
				case 0:
					return Min().Data();
				case 1:
					return Max().Data();
				default:
					throw std::range_error("指定された値がこの型で表せる範囲を超えています。");
				}
			}
		}
		template<class fromT>
		static constexpr ValueType convertFromFloat(const fromT& value)
		{
			if ((value == std::numeric_limits<double>::quiet_NaN()) || (value == std::numeric_limits<double>::signaling_NaN())) { throw std::invalid_argument("指定する値はNaNであってはなりません。"); }
			if ((value < 0.0) || (1.0 < value)) { throw std::range_error("指定された値がこの型で表せる範囲を超えています。"); }
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

	extern template ArithmeticOperation::AdditionResult<Proportion1_t> ArithmeticOperation::Add<Proportion1_t>(const Proportion1_t&, const Proportion1_t&);
	extern template ArithmeticOperation::AdditionResult<Proportion1_t> ArithmeticOperation::Subtract<Proportion1_t>(const Proportion1_t&, const Proportion1_t&);
	extern template ArithmeticOperation::MultiplicationResult<Proportion1_t> ArithmeticOperation::Multiply<Proportion1_t>(const Proportion1_t&, const Proportion1_t&);
	extern template ArithmeticOperation::MultiplicationResult<Proportion1_t> ArithmeticOperation::Divide<Proportion1_t>(const Proportion1_t&, const Proportion1_t&);
	extern template Proportion1_t ArithmeticOperation::SaturateAdd<Proportion1_t>(const Proportion1_t&, const Proportion1_t&);
	extern template Proportion1_t ArithmeticOperation::SaturateSubtract<Proportion1_t>(const Proportion1_t&, const Proportion1_t&);
	extern template Proportion1_t ArithmeticOperation::SaturateMultiply<Proportion1_t>(const Proportion1_t&, const Proportion1_t&);
	extern template Proportion1_t ArithmeticOperation::SaturateDivide<Proportion1_t>(const Proportion1_t&, const Proportion1_t&);
	extern template Proportion1_t ArithmeticOperation::CheckedAdd<Proportion1_t>(const Proportion1_t&, const Proportion1_t&);
	extern template Proportion1_t ArithmeticOperation::CheckedSubtract<Proportion1_t>(const Proportion1_t&, const Proportion1_t&);
	extern template Proportion1_t ArithmeticOperation::CheckedMultiply<Proportion1_t>(const Proportion1_t&, const Proportion1_t&);
	extern template Proportion1_t ArithmeticOperation::CheckedDivide<Proportion1_t>(const Proportion1_t&, const Proportion1_t&);
	extern template bool ArithmeticOperation::MayOverflowWithAddition<Proportion1_t>(const Proportion1_t&, const Proportion1_t&);
	extern template bool ArithmeticOperation::MayOverflowWithSubtraction<Proportion1_t>(const Proportion1_t&, const Proportion1_t&);
	extern template bool ArithmeticOperation::MayOverflowWithMultiplication<Proportion1_t>(const Proportion1_t&, const Proportion1_t&);
	extern template bool ArithmeticOperation::MayOverflowWithDivision<Proportion1_t>(const Proportion1_t&, const Proportion1_t&);
	extern template ArithmeticOperation::AdditionResult<Proportion8_t> ArithmeticOperation::Add<Proportion8_t>(const Proportion8_t&, const Proportion8_t&);
	extern template ArithmeticOperation::AdditionResult<Proportion8_t> ArithmeticOperation::Subtract<Proportion8_t>(const Proportion8_t&, const Proportion8_t&);
	extern template ArithmeticOperation::MultiplicationResult<Proportion8_t> ArithmeticOperation::Multiply<Proportion8_t>(const Proportion8_t&, const Proportion8_t&);
	extern template ArithmeticOperation::MultiplicationResult<Proportion8_t> ArithmeticOperation::Divide<Proportion8_t>(const Proportion8_t&, const Proportion8_t&);
	extern template Proportion8_t ArithmeticOperation::SaturateAdd<Proportion8_t>(const Proportion8_t&, const Proportion8_t&);
	extern template Proportion8_t ArithmeticOperation::SaturateSubtract<Proportion8_t>(const Proportion8_t&, const Proportion8_t&);
	extern template Proportion8_t ArithmeticOperation::SaturateMultiply<Proportion8_t>(const Proportion8_t&, const Proportion8_t&);
	extern template Proportion8_t ArithmeticOperation::SaturateDivide<Proportion8_t>(const Proportion8_t&, const Proportion8_t&);
	extern template Proportion8_t ArithmeticOperation::CheckedAdd<Proportion8_t>(const Proportion8_t&, const Proportion8_t&);
	extern template Proportion8_t ArithmeticOperation::CheckedSubtract<Proportion8_t>(const Proportion8_t&, const Proportion8_t&);
	extern template Proportion8_t ArithmeticOperation::CheckedMultiply<Proportion8_t>(const Proportion8_t&, const Proportion8_t&);
	extern template Proportion8_t ArithmeticOperation::CheckedDivide<Proportion8_t>(const Proportion8_t&, const Proportion8_t&);
	extern template bool ArithmeticOperation::MayOverflowWithAddition<Proportion8_t>(const Proportion8_t&, const Proportion8_t&);
	extern template bool ArithmeticOperation::MayOverflowWithSubtraction<Proportion8_t>(const Proportion8_t&, const Proportion8_t&);
	extern template bool ArithmeticOperation::MayOverflowWithMultiplication<Proportion8_t>(const Proportion8_t&, const Proportion8_t&);
	extern template bool ArithmeticOperation::MayOverflowWithDivision<Proportion8_t>(const Proportion8_t&, const Proportion8_t&);
	extern template ArithmeticOperation::AdditionResult<Proportion16_t> ArithmeticOperation::Add<Proportion16_t>(const Proportion16_t&, const Proportion16_t&);
	extern template ArithmeticOperation::AdditionResult<Proportion16_t> ArithmeticOperation::Subtract<Proportion16_t>(const Proportion16_t&, const Proportion16_t&);
	extern template ArithmeticOperation::MultiplicationResult<Proportion16_t> ArithmeticOperation::Multiply<Proportion16_t>(const Proportion16_t&, const Proportion16_t&);
	extern template ArithmeticOperation::MultiplicationResult<Proportion16_t> ArithmeticOperation::Divide<Proportion16_t>(const Proportion16_t&, const Proportion16_t&);
	extern template Proportion16_t ArithmeticOperation::SaturateAdd<Proportion16_t>(const Proportion16_t&, const Proportion16_t&);
	extern template Proportion16_t ArithmeticOperation::SaturateSubtract<Proportion16_t>(const Proportion16_t&, const Proportion16_t&);
	extern template Proportion16_t ArithmeticOperation::SaturateMultiply<Proportion16_t>(const Proportion16_t&, const Proportion16_t&);
	extern template Proportion16_t ArithmeticOperation::SaturateDivide<Proportion16_t>(const Proportion16_t&, const Proportion16_t&);
	extern template Proportion16_t ArithmeticOperation::CheckedAdd<Proportion16_t>(const Proportion16_t&, const Proportion16_t&);
	extern template Proportion16_t ArithmeticOperation::CheckedSubtract<Proportion16_t>(const Proportion16_t&, const Proportion16_t&);
	extern template Proportion16_t ArithmeticOperation::CheckedMultiply<Proportion16_t>(const Proportion16_t&, const Proportion16_t&);
	extern template Proportion16_t ArithmeticOperation::CheckedDivide<Proportion16_t>(const Proportion16_t&, const Proportion16_t&);
	extern template bool ArithmeticOperation::MayOverflowWithAddition<Proportion16_t>(const Proportion16_t&, const Proportion16_t&);
	extern template bool ArithmeticOperation::MayOverflowWithSubtraction<Proportion16_t>(const Proportion16_t&, const Proportion16_t&);
	extern template bool ArithmeticOperation::MayOverflowWithMultiplication<Proportion16_t>(const Proportion16_t&, const Proportion16_t&);
	extern template bool ArithmeticOperation::MayOverflowWithDivision<Proportion16_t>(const Proportion16_t&, const Proportion16_t&);
	extern template ArithmeticOperation::AdditionResult<Proportion32_t> ArithmeticOperation::Add<Proportion32_t>(const Proportion32_t&, const Proportion32_t&);
	extern template ArithmeticOperation::AdditionResult<Proportion32_t> ArithmeticOperation::Subtract<Proportion32_t>(const Proportion32_t&, const Proportion32_t&);
	extern template ArithmeticOperation::MultiplicationResult<Proportion32_t> ArithmeticOperation::Multiply<Proportion32_t>(const Proportion32_t&, const Proportion32_t&);
	extern template ArithmeticOperation::MultiplicationResult<Proportion32_t> ArithmeticOperation::Divide<Proportion32_t>(const Proportion32_t&, const Proportion32_t&);
	extern template Proportion32_t ArithmeticOperation::SaturateAdd<Proportion32_t>(const Proportion32_t&, const Proportion32_t&);
	extern template Proportion32_t ArithmeticOperation::SaturateSubtract<Proportion32_t>(const Proportion32_t&, const Proportion32_t&);
	extern template Proportion32_t ArithmeticOperation::SaturateMultiply<Proportion32_t>(const Proportion32_t&, const Proportion32_t&);
	extern template Proportion32_t ArithmeticOperation::SaturateDivide<Proportion32_t>(const Proportion32_t&, const Proportion32_t&);
	extern template Proportion32_t ArithmeticOperation::CheckedAdd<Proportion32_t>(const Proportion32_t&, const Proportion32_t&);
	extern template Proportion32_t ArithmeticOperation::CheckedSubtract<Proportion32_t>(const Proportion32_t&, const Proportion32_t&);
	extern template Proportion32_t ArithmeticOperation::CheckedMultiply<Proportion32_t>(const Proportion32_t&, const Proportion32_t&);
	extern template Proportion32_t ArithmeticOperation::CheckedDivide<Proportion32_t>(const Proportion32_t&, const Proportion32_t&);
	extern template bool ArithmeticOperation::MayOverflowWithAddition<Proportion32_t>(const Proportion32_t&, const Proportion32_t&);
	extern template bool ArithmeticOperation::MayOverflowWithSubtraction<Proportion32_t>(const Proportion32_t&, const Proportion32_t&);
	extern template bool ArithmeticOperation::MayOverflowWithMultiplication<Proportion32_t>(const Proportion32_t&, const Proportion32_t&);
	extern template bool ArithmeticOperation::MayOverflowWithDivision<Proportion32_t>(const Proportion32_t&, const Proportion32_t&);
	extern template ArithmeticOperation::AdditionResult<Proportion64_t> ArithmeticOperation::Add<Proportion64_t>(const Proportion64_t&, const Proportion64_t&);
	extern template ArithmeticOperation::AdditionResult<Proportion64_t> ArithmeticOperation::Subtract<Proportion64_t>(const Proportion64_t&, const Proportion64_t&);
	extern template ArithmeticOperation::MultiplicationResult<Proportion64_t> ArithmeticOperation::Multiply<Proportion64_t>(const Proportion64_t&, const Proportion64_t&);
	extern template ArithmeticOperation::MultiplicationResult<Proportion64_t> ArithmeticOperation::Divide<Proportion64_t>(const Proportion64_t&, const Proportion64_t&);
	extern template Proportion64_t ArithmeticOperation::SaturateAdd<Proportion64_t>(const Proportion64_t&, const Proportion64_t&);
	extern template Proportion64_t ArithmeticOperation::SaturateSubtract<Proportion64_t>(const Proportion64_t&, const Proportion64_t&);
	extern template Proportion64_t ArithmeticOperation::SaturateMultiply<Proportion64_t>(const Proportion64_t&, const Proportion64_t&);
	extern template Proportion64_t ArithmeticOperation::SaturateDivide<Proportion64_t>(const Proportion64_t&, const Proportion64_t&);
	extern template Proportion64_t ArithmeticOperation::CheckedAdd<Proportion64_t>(const Proportion64_t&, const Proportion64_t&);
	extern template Proportion64_t ArithmeticOperation::CheckedSubtract<Proportion64_t>(const Proportion64_t&, const Proportion64_t&);
	extern template Proportion64_t ArithmeticOperation::CheckedMultiply<Proportion64_t>(const Proportion64_t&, const Proportion64_t&);
	extern template Proportion64_t ArithmeticOperation::CheckedDivide<Proportion64_t>(const Proportion64_t&, const Proportion64_t&);
	extern template bool ArithmeticOperation::MayOverflowWithAddition<Proportion64_t>(const Proportion64_t&, const Proportion64_t&);
	extern template bool ArithmeticOperation::MayOverflowWithSubtraction<Proportion64_t>(const Proportion64_t&, const Proportion64_t&);
	extern template bool ArithmeticOperation::MayOverflowWithMultiplication<Proportion64_t>(const Proportion64_t&, const Proportion64_t&);
	extern template bool ArithmeticOperation::MayOverflowWithDivision<Proportion64_t>(const Proportion64_t&, const Proportion64_t&);
}
namespace std
{
	template<class T>
	class numeric_limits<zawa_ch::StationaryOrbit::Proportion<T>> : public numeric_limits<void>
	{
	public:
		static constexpr bool is_specialized = true;
		static constexpr bool is_signed = false;
		static constexpr bool is_integer = false;
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
		static constexpr int digits = numeric_limits<T>::digits;
		static constexpr int digits10 = numeric_limits<T>::digits10;
		static constexpr int max_digits10 = numeric_limits<T>::max_digits10;
		static constexpr int radix = 2;
		static constexpr int min_exponent = 0;
		static constexpr int min_exponent10 = 0;
		static constexpr int max_exponent = 0;
		static constexpr int max_exponent10 = 0;
		static constexpr bool traps = true;
		static constexpr bool tinyness_before = true;
		static constexpr zawa_ch::StationaryOrbit::Proportion<T> min() noexcept { return zawa_ch::StationaryOrbit::Proportion<T>::Min(); }
		static constexpr zawa_ch::StationaryOrbit::Proportion<T> lowest() noexcept { return zawa_ch::StationaryOrbit::Proportion<T>::Min(); }
		static constexpr zawa_ch::StationaryOrbit::Proportion<T> max() noexcept { return zawa_ch::StationaryOrbit::Proportion<T>::Max(); }
		static constexpr zawa_ch::StationaryOrbit::Proportion<T> epsilon() noexcept { return zawa_ch::StationaryOrbit::Proportion<T>::Epsilon(); }
	};
}
#endif // __stationaryorbit_core_proportion__
