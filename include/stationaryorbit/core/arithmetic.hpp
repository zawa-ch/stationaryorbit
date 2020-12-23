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

		template<typename T, std::enable_if_t<Traits::IsNumeralType<T>>>
		static constexpr AdditionResult<T> Add(const T& left, const T& right) noexcept
		{
			static_assert(Traits::IsNumeralType<Tp>, "テンプレート引数型 Tp は算術型である必要があります。");
			static_assert(std::is_constructible_v<Tp, int>, "テンプレート引数型 Tp は (int) を引数に取るコンストラクタを持つ必要があります。");
			auto eval = std::numeric_limits<Tp>::max() - right;
			if (eval < left) { return AdditionResult<T>{ left + right, AdditionResultStatus::PositiveOverflow }; }
			if constexpr (std::numeric_limits<Tp>::is_signed)
			{
				if (right < Tp(0))
				{
					eval = std::numeric_limits<Tp>::lowest() - right;
					if (left < eval) { return AdditionResult<T>{ left + right, AdditionResultStatus::NegativeOverflow }; }
				}
			}
			return AdditionResult<T>{ left + right, AdditionResultStatus::NoError };
		}
		template<typename T, std::enable_if_t<Traits::IsNumeralType<T>>>
		static constexpr AdditionResult<T> Subtract(const T& left, const T& right) noexcept
		{
			static_assert(Traits::IsNumeralType<Tp>, "テンプレート引数型 Tp は算術型である必要があります。");
			static_assert(std::is_constructible_v<Tp, int>, "テンプレート引数型 Tp は (int) を引数に取るコンストラクタを持つ必要があります。");
			auto eval = std::numeric_limits<Tp>::lowest() + right;
			if (left < eval) { return AdditionResult<T>{ left - right, AdditionResultStatus::NegativeOverflow }; }
			if constexpr (std::numeric_limits<Tp>::is_signed)
			{
				if (right < Tp(0))
				{
					auto eval = std::numeric_limits<Tp>::max() + right;
					if (eval < left) { return AdditionResult<T>{ left - right, AdditionResultStatus::PositiveOverflow }; }
				}
			}
			return AdditionResult<T>{ left - right, AdditionResultStatus::NoError };
		}
		template<typename T, std::enable_if_t<Traits::IsNumeralType<T>>>
		static MultiplicationResult<T> Multiply(const T& left, const T& right) noexcept
		{
			static_assert(Traits::IsNumeralType<Tp>, "テンプレート引数型 Tp は算術型である必要があります。");
			static_assert(std::is_constructible_v<Tp, int>, "テンプレート引数型 Tp は (int) を引数に取るコンストラクタを持つ必要があります。");
			if constexpr (std::numeric_limits<Tp>::is_signed)
			{
				if ( ( (Tp(-1) < left)&&(left <= Tp(1)) )||( (Tp(-1) < right)&&(right <= Tp(1)) ) )
				{
					// 一方のオペランドの絶対値が1より小さい(あるいは1に等しい)場合、演算結果はオーバーフローすることはない
					return MultiplicationResult<T>{ left * right, MultiplicationResultStatus::NoError };
				}
				if (right == Tp(-1))
				{
					if constexpr (std::numeric_limits<Tp>::lowest() + std::numeric_limits<Tp>::max() != Tp(0))
					{
						if constexpr (std::numeric_limits<Tp>::lowest() + std::numeric_limits<Tp>::max() < Tp(0))
						{ return MultiplicationResult<T>{ left * right, (left < -std::numeric_limits<Tp>::max())?(MultiplicationResultStatus::Overflow):(MultiplicationResultStatus::NoError) }; }
						else
						{ return MultiplicationResult<T>{ left * right, (-std::numeric_limits<Tp>::lowest() < left)?(MultiplicationResultStatus::Overflow):(MultiplicationResultStatus::NoError) }; }
					}
					else
					{
						return MultiplicationResult<T>{ left * right, MultiplicationResultStatus::NoError };
					}
				}
			}
			else
			{
				if ( (left <= Tp(1))||(right <= Tp(1)) )
				{
					// 一方のオペランドが1より小さい(あるいは1に等しい)場合、演算結果はオーバーフローすることはない
					return MultiplicationResult<T>{ left * right, MultiplicationResultStatus::NoError };
				}
			}
			auto evalc = std::numeric_limits<Tp>::max() / right;
			auto evalf = std::numeric_limits<Tp>::lowest() / right;
			return MultiplicationResult<T>{ left * right, ((left < std::min(evalc, evalf))||(std::max(evalc, evalf) < left))?(MultiplicationResultStatus::Overflow):(MultiplicationResultStatus::NoError) };
		}
		template<typename T, std::enable_if_t<Traits::IsNumeralType<T>>>
		static T Divide(const T& left, const T& right)
		{
			static_assert(Traits::IsNumeralType<Tp>, "テンプレート引数型 Tp は算術型である必要があります。");
			static_assert(std::is_constructible_v<Tp, int>, "テンプレート引数型 Tp は (int) を引数に取るコンストラクタを持つ必要があります。");
			if (right == Tp(0))
			{
				if constexpr (std::numeric_limits<T>::is_iec559) { return MultiplicationResult<T>{ left / right , MultiplicationResultStatus::DivideByZero }; }
				else { return MultiplicationResult<T>{ 0 , MultiplicationResultStatus::DivideByZero }; }
			}
			if constexpr (std::numeric_limits<Tp>::is_signed)
			{
				if ((right < Tp(-1))||(Tp(1) <= right)) { return MultiplicationResult<T>{ left / right, MultiplicationResultStatus::NoError }; }
			}
			else
			{
				if (Tp(1) <= right) { return MultiplicationResult<T>{ left / right, MultiplicationResultStatus::NoError }; }
			}
			auto evalc = std::numeric_limits<Tp>::max() * right;
			auto evalf = std::numeric_limits<Tp>::lowest() * right;
			return MultiplicationResult<T>{ left / right, ((left < std::min(evalc, evalf))||(std::max(evalc, evalf) < left))?(MultiplicationResultStatus::Overflow):(MultiplicationResultStatus::NoError) };
		}
	};
}
#endif // __stationaryorbit_core_arithmetic__
