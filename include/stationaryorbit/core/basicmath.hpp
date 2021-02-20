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
#include "notimplemented.hpp"
#include "fundamental.hpp"
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

		template<class T, class R = decltype( std::sqrt(std::declval<T&>()) )> struct StdSqrtResult_Impl { typedef R type; };
		template<class T, class R = decltype( std::declval<const T&>().Sqrt() )> struct SqrtResult_Impl { typedef R type; };
		template<class T, class = void> struct IsStdSqrtCallable_Impl : std::false_type {};
		template<class T> struct IsStdSqrtCallable_Impl<T, std::void_t< typename StdSqrtResult_Impl<T>::type >> : std::true_type {};
		template<class T, class = void> struct HasSqrt_Impl : std::false_type {};
		template<class T> struct HasSqrt_Impl<T, std::void_t< typename StdSqrtResult_Impl<T>::type >> : std::true_type {};
		template<class T> static constexpr bool IsStdSqrtCallable = IsStdSqrtCallable_Impl<T>::value;
		template<class T> static constexpr bool HasSqrt = HasSqrt_Impl<T>::value;
	public:
		template<class T>
		[[nodiscard]] static constexpr std::enable_if_t<Traits::IsNumericalType<T>, T> Abstract(const T& value) noexcept
		{
			return ( value < T(0) )?(-value):(value);
		}
		template<class T, class = decltype( std::abs( std::declval<T&>() ))>
		[[nodiscard]] static constexpr T Abstract(const T& value) noexcept { return std::abs(value); }
		///	この値の平方根を取得します。
		template<class T, std::enable_if_t<(!IsStdSqrtCallable<T>) && (!HasSqrt<T>), int> = 0>
		[[nodiscard]] static constexpr T Sqrt(const T& value) noexcept
		{
			static_assert(Traits::IsNumericalType<T>, "テンプレート型 T は数値型である必要があります。");
			auto result = value;
			auto b = value;
			do	// X[n+1] = (X[N] + a / X[N]) / 2
			{
				// 0除算の回避(sqrt(0) = 0)
				if (result == T(0))
				{
					if constexpr (std::numeric_limits<T>::has_quiet_NaN) { result = std::numeric_limits<T>::quiet_NaN(); }
					break;
				}
				b = result;	///< 前回値(X[N])保持
				// a / X[N] の導出
				auto delta = value / b;
				// X[N] / 2
				result /= T(2);
				if constexpr (Traits::IsIntegralType<T>)
				{
					// 剰余分の計算
					result += ((result % T(2)) + (delta % T(2))) / T(2);
				}
				// (a / X[n]) / 2
				result += delta / T(2);
			} while (T(2) < ((result < b)?(b-result):(result - b)));
			return result;
		}
		template<class T, std::enable_if_t<(IsStdSqrtCallable<T>), int> = 0>
		[[nodiscard]] static constexpr T Sqrt(const T& value) noexcept { return std::sqrt(value); }
		template<class T, std::enable_if_t<(!IsStdSqrtCallable<T>) && (HasSqrt<T>), int> = 0>
		[[nodiscard]] static constexpr decltype( std::declval<const T&>().Sqrt() ) Sqrt(const T& value) noexcept { return value.Sqrt(); }
		template<class T>
		[[nodiscard]] static constexpr std::enable_if_t<Traits::IsNumericalType<T>, T> Mod(const T& left, const T& right)
		{
			// TODO: フォールバック実装の実装
			throw NotImplementedException();
		}
		template<class T, class = decltype( std::fmod( std::declval<T&>(), std::declval<T&>() ))>
		[[nodiscard]] static constexpr T Mod(const T& value) noexcept { return std::fmod(value); }
	};
}
#endif // __stationaryorbit_core_basicmath__
