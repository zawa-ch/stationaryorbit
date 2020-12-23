//	stationaryorbit/core/arithmetic
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
#include "traits.hpp"
#include "algorithms.hpp"
#ifndef __stationaryorbit_core_arithmetic__
#define __stationaryorbit_core_arithmetic__
namespace zawa_ch::StationaryOrbit
{
	class ArithmeticOperation
	{
	private:
		ArithmeticOperation() = delete;
		~ArithmeticOperation() = delete;
	public:
		enum class AdditionResultStatus { NoError = 0, PositiveOverflow = 1, NegativeOverflow = -1 };
		template<typename T, typename Tp = typename Traits::PromotionResult<T>> struct AdditionResult final { Tp Result; AdditionResultStatus Status; };
		enum class MultiplicationResultStatus { NoError = 0, Overflow = 1, DivideByZero = -1 };
		template<typename T, typename Tp = typename Traits::PromotionResult<T>> struct MultiplicationResult final { Tp Result; MultiplicationResultStatus Status; };

		template<typename T, typename = std::enable_if_t<Traits::IsNumeralType<T>>>
		static constexpr AdditionResult<T> Add(const T& left, const T& right) noexcept
		{
			static_assert(Traits::IsNumeralType<T>, "テンプレート引数型 T は算術型である必要があります。");
			static_assert(std::is_constructible_v<T, int>, "テンプレート引数型 T は (int) を引数に取るコンストラクタを持つ必要があります。");
			auto eval = std::numeric_limits<T>::max() - right;
			if (eval < left) { return AdditionResult<T>{ left + right, AdditionResultStatus::PositiveOverflow }; }
			if constexpr (std::numeric_limits<T>::is_signed)
			{
				if (right < T(0))
				{
					eval = std::numeric_limits<T>::lowest() - right;
					if (left < eval) { return AdditionResult<T>{ left + right, AdditionResultStatus::NegativeOverflow }; }
				}
			}
			return AdditionResult<T>{ left + right, AdditionResultStatus::NoError };
		}
		template<typename T, typename = std::enable_if_t<Traits::IsNumeralType<T>>>
		static constexpr AdditionResult<T> Subtract(const T& left, const T& right) noexcept
		{
			static_assert(Traits::IsNumeralType<T>, "テンプレート引数型 T は算術型である必要があります。");
			static_assert(std::is_constructible_v<T, int>, "テンプレート引数型 T は (int) を引数に取るコンストラクタを持つ必要があります。");
			auto eval = std::numeric_limits<T>::lowest() + right;
			if (left < eval) { return AdditionResult<T>{ left - right, AdditionResultStatus::NegativeOverflow }; }
			if constexpr (std::numeric_limits<T>::is_signed)
			{
				if (right < T(0))
				{
					auto eval = std::numeric_limits<T>::max() + right;
					if (eval < left) { return AdditionResult<T>{ left - right, AdditionResultStatus::PositiveOverflow }; }
				}
			}
			return AdditionResult<T>{ left - right, AdditionResultStatus::NoError };
		}
		template<typename T, typename = std::enable_if_t<Traits::IsNumeralType<T>>>
		static MultiplicationResult<T> Multiply(const T& left, const T& right) noexcept
		{
			static_assert(Traits::IsNumeralType<T>, "テンプレート引数型 T は算術型である必要があります。");
			static_assert(std::is_constructible_v<T, int>, "テンプレート引数型 T は (int) を引数に取るコンストラクタを持つ必要があります。");
			if constexpr (std::numeric_limits<T>::is_signed)
			{
				if ( ( (T(-1) < left)&&(left <= T(1)) )||( (T(-1) < right)&&(right <= T(1)) ) )
				{
					// 一方のオペランドの絶対値が1より小さい(あるいは1に等しい)場合、演算結果はオーバーフローすることはない
					return MultiplicationResult<T>{ left * right, MultiplicationResultStatus::NoError };
				}
				if (right == T(-1))
				{
					if constexpr (std::numeric_limits<T>::lowest() + std::numeric_limits<T>::max() != T(0))
					{
						if constexpr (std::numeric_limits<T>::lowest() + std::numeric_limits<T>::max() < T(0))
						{ return MultiplicationResult<T>{ left * right, (left < -std::numeric_limits<T>::max())?(MultiplicationResultStatus::Overflow):(MultiplicationResultStatus::NoError) }; }
						else
						{ return MultiplicationResult<T>{ left * right, (-std::numeric_limits<T>::lowest() < left)?(MultiplicationResultStatus::Overflow):(MultiplicationResultStatus::NoError) }; }
					}
					else
					{
						return MultiplicationResult<T>{ left * right, MultiplicationResultStatus::NoError };
					}
				}
			}
			else
			{
				if ( (left <= T(1))||(right <= T(1)) )
				{
					// 一方のオペランドが1より小さい(あるいは1に等しい)場合、演算結果はオーバーフローすることはない
					return MultiplicationResult<T>{ left * right, MultiplicationResultStatus::NoError };
				}
			}
			auto evalc = std::numeric_limits<T>::max() / right;
			auto evalf = std::numeric_limits<T>::lowest() / right;
			return MultiplicationResult<T>{ left * right, ((left < std::min(evalc, evalf))||(std::max(evalc, evalf) < left))?(MultiplicationResultStatus::Overflow):(MultiplicationResultStatus::NoError) };
		}
		template<typename T, typename = std::enable_if_t<Traits::IsNumeralType<T>>>
		static MultiplicationResult<T> Divide(const T& left, const T& right) noexcept
		{
			static_assert(Traits::IsNumeralType<T>, "テンプレート引数型 T は算術型である必要があります。");
			static_assert(std::is_constructible_v<T, int>, "テンプレート引数型 T は (int) を引数に取るコンストラクタを持つ必要があります。");
			if (right == T(0))
			{
				if constexpr (std::numeric_limits<T>::is_iec559) { return MultiplicationResult<T>{ left / right , MultiplicationResultStatus::DivideByZero }; }
				else { return MultiplicationResult<T>{ 0 , MultiplicationResultStatus::DivideByZero }; }
			}
			if constexpr (std::numeric_limits<T>::is_signed)
			{
				if ((right < T(-1))||(T(1) <= right)) { return MultiplicationResult<T>{ left / right, MultiplicationResultStatus::NoError }; }
			}
			else
			{
				if (T(1) <= right) { return MultiplicationResult<T>{ left / right, MultiplicationResultStatus::NoError }; }
			}
			auto evalc = std::numeric_limits<T>::max() * right;
			auto evalf = std::numeric_limits<T>::lowest() * right;
			return MultiplicationResult<T>{ left / right, ((left < std::min(evalc, evalf))||(std::max(evalc, evalf) < left))?(MultiplicationResultStatus::Overflow):(MultiplicationResultStatus::NoError) };
		}
	};
}
#endif // __stationaryorbit_core_arithmetic__
