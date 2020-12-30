//	stationaryorbit/core/basicmath
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
#ifndef __stationaryorbit_core_basicmath__
#define __stationaryorbit_core_basicmath__
#include <cmath>
#include "traits.hpp"
namespace zawa_ch::StationaryOrbit
{
	class BasicMathematics
	{
	private:
		BasicMathematics() = delete;
		BasicMathematics(const BasicMathematics&) = delete;
		BasicMathematics(BasicMathematics&&) = delete;
		~BasicMathematics() = delete;
	public:
		///	この値の平方根を取得します。
		template<class T>
		[[nodiscard]] static constexpr T Sqrt(const T& value) noexcept
		{
			static_assert(Traits::IsNumericalType<T>, "テンプレート引数型 T は数値型である必要があります。");
			auto result = value;
			auto b = value;
			do	// X[n+1] = (X[N] + a / X[N]) / 2
			{
				// 0除算の回避(sqrt(0) = 0)
				if (result == T(0U))
				{
					if constexpr (std::numeric_limits<T>::has_quiet_NaN) { result = std::numeric_limits<T>::quiet_NaN(); }
					break;
				}
				b = result;	///< 前回値(X[N])保持
				// a / X[N] の導出
				auto delta = Algorithms::IntegralFraction(value, b, std::numeric_limits<Tp>::max()).Value;
				// X[N] / 2
				result /= 2;
				// 剰余分の計算
				result += ((result % 2) + (delta % 2)) / 2;
				// (a / X[n]) / 2
				result += delta / 2;
			} while (2U < ((result < b)?(b-result):(result - b)));
			return result;
		}
		template<class T, class = decltype( std::sqrt( std::declval<T&>() ))>
		[[nodiscard]] static constexpr T Sqrt(const T& value) noexcept { return std::sqrt(value); }
	};
}
#endif // __stationaryorbit_core_basicmath__
