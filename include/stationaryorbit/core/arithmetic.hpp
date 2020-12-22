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
		enum class OverflowStatus { NoOverflow = 0, PositiveOverflow = 1, NegativeOverflow = -1 };
		template<typename T> struct AdditionResult final { T Result; OverflowStatus Overflow; };

		template<typename T, std::enable_if_t<Traits::IsNumeralType<T>>>
		static constexpr AdditionResult<T> Add(const T& left, const T& right) noexcept
		{
			static_assert(Traits::IsNumeralType<Tp>, "テンプレート引数型 Tp は算術型である必要があります。");
			static_assert(std::is_constructible_v<Tp, int>, "テンプレート引数型 Tp は (int) を引数に取るコンストラクタを持つ必要があります。");
			auto eval = std::numeric_limits<Tp>::max() - right;
			if (eval < left) { return AdditionResult<T>{ left + right, OverflowStatus::PositiveOverflow }; }
			if constexpr (std::numeric_limits<Tp>::is_signed)
			{
				if (right < Tp(0))
				{
					eval = std::numeric_limits<Tp>::lowest() - right;
					if (left < eval) { return AdditionResult<T>{ left + right, OverflowStatus::NegativeOverflow }; }
				}
			}
			return AdditionResult<T>{ left + right, OverflowStatus::NoOverflow };
		}
		template<typename T, std::enable_if_t<Traits::IsNumeralType<T>>>
		static constexpr AdditionResult<T> Subtract(const T& left, const T& right) noexcept
		{
			static_assert(Traits::IsNumeralType<Tp>, "テンプレート引数型 Tp は算術型である必要があります。");
			static_assert(std::is_constructible_v<Tp, int>, "テンプレート引数型 Tp は (int) を引数に取るコンストラクタを持つ必要があります。");
			auto eval = std::numeric_limits<Tp>::lowest() + right;
			if (left < eval) { return AdditionResult<T>{ left - right, OverflowStatus::NegativeOverflow }; }
			if constexpr (std::numeric_limits<Tp>::is_signed)
			{
				if (right < Tp(0))
				{
					auto eval = std::numeric_limits<Tp>::max() + right;
					if (eval < left) { return AdditionResult<T>{ left - right, OverflowStatus::PositiveOverflow }; }
				}
			}
			return AdditionResult<T>{ left - right, OverflowStatus::NoOverflow };
		}
	};
}
#endif // __stationaryorbit_core_arithmetic__
