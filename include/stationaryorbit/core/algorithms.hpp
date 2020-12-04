//	stationaryorbit/core/algorithms
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
#ifndef __stationaryorbit__core_algorithms__
#define __stationaryorbit__core_algorithms__
#include <stdexcept>
#include "traits.hpp"
#include "range.hpp"
#include "multiplelong.hpp"
namespace zawa_ch::StationaryOrbit
{
	///	ライブラリで使用される基本的なアルゴリズムを実装します。
	///	このクラスは継承できません。
	class Algorithms final
	{
	public:
		///	整数の除算と乗算を行います。
		///	@param	numerator
		///	除算時の被除数。
		///	@param	denominator
		///	除算時の除数。
		///	@param	scale
		///	乗算時の乗数。
		///	@exception
		///	std::invalid_argument
		///	0で除算することはできません。
		template<class Tp>
		static constexpr Tp IntegralFraction(const Tp& numerator, const Tp& denominator, const Tp& scale)
		{
			static_assert(std::is_same_v<Tp, bool> || Traits::IsNumeralType<Tp>, "テンプレート型 Tp は算術型またはboolである必要があります。");
			static_assert(!std::numeric_limits<Tp>::is_signed, "テンプレート型 Tp は符号なしである必要があります。");

			if constexpr (std::is_same_v<Tp, bool>)
			{
				if (denominator == false) { throw std::invalid_argument("分母に0を指定することはできません。"); }
				return numerator&&scale;
			}
			else
			{
				if constexpr (!std::numeric_limits<Tp>::is_signed)
				{
					auto r = MultipleULong<Tp, 2UL>(numerator);
					r *= scale;
					r /= denominator;
					return Tp(r);
				}
				else
				{
					auto r = IntegralFraction<std::make_unsigned_t<Tp>>((numerator >= Tp(0))?numerator:-numerator, (denominator >= Tp(0))?denominator:-denominator, (scale >= Tp(0))?scale:-scale);
					return ((numerator < Tp(0)) ^ (denominator < Tp(0)) ^ (scale < Tp(0)))?(-r):(r);
				}
			}
		}

		template<class Tp>
		static constexpr bool MayOverflowWithAddition(const Tp& left, const Tp& right) noexcept
		{
			static_assert(Traits::IsNumeralType<Tp>, "テンプレート引数型 Tp は算術型である必要があります。");
			static_assert(std::is_constructible_v<Tp, int>, "テンプレート引数型 Tp は (int) を引数に取るコンストラクタを持つ必要があります。");
			if constexpr (std::true_type::value)
			{
				auto eval = std::numeric_limits<Tp>::max() - right;
				if (eval < left)
				{
					return true;
				}
			}
			if constexpr (std::numeric_limits<Tp>::is_signed)
			{
				if (right < Tp(0))
				{
					auto eval = std::numeric_limits<Tp>::lowest() - right;
					if (left < eval)
					{
						return true;
					}
				}
			}
			return false;
		}
		template<class Tp>
		static constexpr bool MayOverflowWithSubtraction(const Tp& left, const Tp& right) noexcept
		{
			static_assert(Traits::IsNumeralType<Tp>, "テンプレート引数型 Tp は算術型である必要があります。");
			static_assert(std::is_constructible_v<Tp, int>, "テンプレート引数型 Tp は (int) を引数に取るコンストラクタを持つ必要があります。");
			if constexpr (std::true_type::value)
			{
				auto eval = std::numeric_limits<Tp>::lowest() + right;
				if (left < eval)
				{
					return true;
				}
			}
			if constexpr (std::numeric_limits<Tp>::is_signed)
			{
				if (right < Tp(0))
				{
					auto eval = std::numeric_limits<Tp>::max() + right;
					if (eval < left)
					{
						return true;
					}
				}
			}
			return false;
		}
		template<class Tp>
		static constexpr bool MayOverflowWithMultiplication(const Tp& left, const Tp& right) noexcept
		{
			static_assert(Traits::IsNumeralType<Tp>, "テンプレート引数型 Tp は算術型である必要があります。");
			static_assert(std::is_constructible_v<Tp, int>, "テンプレート引数型 Tp は (int) を引数に取るコンストラクタを持つ必要があります。");
			if constexpr (std::numeric_limits<Tp>::is_signed)
			{
				if ( ( (Tp(-1) < left)&&(left <= Tp(1)) )||( (Tp(-1) < right)&&(right <= Tp(1)) ) )
				{
					// 一方のオペランドの絶対値が1より小さい(あるいは1に等しい)場合、演算結果はオーバーフローすることはない
					return false;
				}
				if (right == Tp(-1))
				{
					if constexpr (std::numeric_limits<Tp>::lowest() + std::numeric_limits<Tp>::max() != Tp(0))
					{
						if constexpr (std::numeric_limits<Tp>::lowest() + std::numeric_limits<Tp>::max() < Tp(0))
						{ return left < -std::numeric_limits<Tp>::max(); }
						else
						{ return -std::numeric_limits<Tp>::lowest() < left; }
					}
					else
					{
						return false;
					}
				}
			}
			else
			{
				if ( (left <= Tp(1))||(right <= Tp(1)) )
				{
					// 一方のオペランドが1より小さい(あるいは1に等しい)場合、演算結果はオーバーフローすることはない
					return false;
				}
			}
			auto evalc = std::numeric_limits<Tp>::max() / right;
			auto evalf = std::numeric_limits<Tp>::lowest() / right;
			return (left < std::min(evalc, evalf))||(std::max(evalc, evalf) < left);
		}
		template<class Tp>
		static constexpr bool MayOverflowWithDivision(const Tp& left, const Tp& right) noexcept
		{
			static_assert(Traits::IsNumeralType<Tp>, "テンプレート引数型 Tp は算術型である必要があります。");
			static_assert(std::is_constructible_v<Tp, int>, "テンプレート引数型 Tp は (int) を引数に取るコンストラクタを持つ必要があります。");
			if (right == Tp(0))
			{
				return true;
			}
			if constexpr (std::numeric_limits<Tp>::is_signed)
			{
				if ((right < Tp(-1))||(Tp(1) <= right)) { return false; }
			}
			else
			{
				if (Tp(1) <= right) { return false; }
			}
			auto evalc = std::numeric_limits<Tp>::max() * right;
			auto evalf = std::numeric_limits<Tp>::lowest() * right;
			return (left < std::min(evalc, evalf))||(std::max(evalc, evalf) < left);
		}
	};

	extern template bool Algorithms::MayOverflowWithAddition<bool>(const bool&, const bool&);
	extern template bool Algorithms::MayOverflowWithAddition<char>(const char&, const char&);
	extern template bool Algorithms::MayOverflowWithAddition<signed char>(const signed char&, const signed char&);
	extern template bool Algorithms::MayOverflowWithAddition<unsigned char>(const unsigned char&, const unsigned char&);
	extern template bool Algorithms::MayOverflowWithAddition<wchar_t>(const wchar_t&, const wchar_t&);
	extern template bool Algorithms::MayOverflowWithAddition<short>(const short&, const short&);
	extern template bool Algorithms::MayOverflowWithAddition<unsigned short>(const unsigned short&, const unsigned short&);
	extern template bool Algorithms::MayOverflowWithAddition<int>(const int&, const int&);
	extern template bool Algorithms::MayOverflowWithAddition<unsigned int>(const unsigned int&, const unsigned int&);
	extern template bool Algorithms::MayOverflowWithAddition<long>(const long&, const long&);
	extern template bool Algorithms::MayOverflowWithAddition<unsigned long>(const unsigned long&, const unsigned long&);
	extern template bool Algorithms::MayOverflowWithAddition<long long>(const long long&, const long long&);
	extern template bool Algorithms::MayOverflowWithAddition<unsigned long long>(const unsigned long long&, const unsigned long long&);
	extern template bool Algorithms::MayOverflowWithAddition<float>(const float&, const float&);
	extern template bool Algorithms::MayOverflowWithAddition<double>(const double&, const double&);
	extern template bool Algorithms::MayOverflowWithAddition<long double>(const long double&, const long double&);
	extern template bool Algorithms::MayOverflowWithAddition<char16_t>(const char16_t&, const char16_t&);
	extern template bool Algorithms::MayOverflowWithAddition<char32_t>(const char32_t&, const char32_t&);
	extern template bool Algorithms::MayOverflowWithSubtraction<bool>(const bool&, const bool&);
	extern template bool Algorithms::MayOverflowWithSubtraction<char>(const char&, const char&);
	extern template bool Algorithms::MayOverflowWithSubtraction<signed char>(const signed char&, const signed char&);
	extern template bool Algorithms::MayOverflowWithSubtraction<unsigned char>(const unsigned char&, const unsigned char&);
	extern template bool Algorithms::MayOverflowWithSubtraction<wchar_t>(const wchar_t&, const wchar_t&);
	extern template bool Algorithms::MayOverflowWithSubtraction<short>(const short&, const short&);
	extern template bool Algorithms::MayOverflowWithSubtraction<unsigned short>(const unsigned short&, const unsigned short&);
	extern template bool Algorithms::MayOverflowWithSubtraction<int>(const int&, const int&);
	extern template bool Algorithms::MayOverflowWithSubtraction<unsigned int>(const unsigned int&, const unsigned int&);
	extern template bool Algorithms::MayOverflowWithSubtraction<long>(const long&, const long&);
	extern template bool Algorithms::MayOverflowWithSubtraction<unsigned long>(const unsigned long&, const unsigned long&);
	extern template bool Algorithms::MayOverflowWithSubtraction<long long>(const long long&, const long long&);
	extern template bool Algorithms::MayOverflowWithSubtraction<unsigned long long>(const unsigned long long&, const unsigned long long&);
	extern template bool Algorithms::MayOverflowWithSubtraction<float>(const float&, const float&);
	extern template bool Algorithms::MayOverflowWithSubtraction<double>(const double&, const double&);
	extern template bool Algorithms::MayOverflowWithSubtraction<long double>(const long double&, const long double&);
	extern template bool Algorithms::MayOverflowWithSubtraction<char16_t>(const char16_t&, const char16_t&);
	extern template bool Algorithms::MayOverflowWithSubtraction<char32_t>(const char32_t&, const char32_t&);
	extern template bool Algorithms::MayOverflowWithMultiplication<bool>(const bool&, const bool&);
	extern template bool Algorithms::MayOverflowWithMultiplication<char>(const char&, const char&);
	extern template bool Algorithms::MayOverflowWithMultiplication<signed char>(const signed char&, const signed char&);
	extern template bool Algorithms::MayOverflowWithMultiplication<unsigned char>(const unsigned char&, const unsigned char&);
	extern template bool Algorithms::MayOverflowWithMultiplication<wchar_t>(const wchar_t&, const wchar_t&);
	extern template bool Algorithms::MayOverflowWithMultiplication<short>(const short&, const short&);
	extern template bool Algorithms::MayOverflowWithMultiplication<unsigned short>(const unsigned short&, const unsigned short&);
	extern template bool Algorithms::MayOverflowWithMultiplication<int>(const int&, const int&);
	extern template bool Algorithms::MayOverflowWithMultiplication<unsigned int>(const unsigned int&, const unsigned int&);
	extern template bool Algorithms::MayOverflowWithMultiplication<long>(const long&, const long&);
	extern template bool Algorithms::MayOverflowWithMultiplication<unsigned long>(const unsigned long&, const unsigned long&);
	extern template bool Algorithms::MayOverflowWithMultiplication<long long>(const long long&, const long long&);
	extern template bool Algorithms::MayOverflowWithMultiplication<unsigned long long>(const unsigned long long&, const unsigned long long&);
	extern template bool Algorithms::MayOverflowWithMultiplication<float>(const float&, const float&);
	extern template bool Algorithms::MayOverflowWithMultiplication<double>(const double&, const double&);
	extern template bool Algorithms::MayOverflowWithMultiplication<long double>(const long double&, const long double&);
	extern template bool Algorithms::MayOverflowWithMultiplication<char16_t>(const char16_t&, const char16_t&);
	extern template bool Algorithms::MayOverflowWithMultiplication<char32_t>(const char32_t&, const char32_t&);
	extern template bool Algorithms::MayOverflowWithDivision<bool>(const bool&, const bool&);
	extern template bool Algorithms::MayOverflowWithDivision<char>(const char&, const char&);
	extern template bool Algorithms::MayOverflowWithDivision<signed char>(const signed char&, const signed char&);
	extern template bool Algorithms::MayOverflowWithDivision<unsigned char>(const unsigned char&, const unsigned char&);
	extern template bool Algorithms::MayOverflowWithDivision<wchar_t>(const wchar_t&, const wchar_t&);
	extern template bool Algorithms::MayOverflowWithDivision<short>(const short&, const short&);
	extern template bool Algorithms::MayOverflowWithDivision<unsigned short>(const unsigned short&, const unsigned short&);
	extern template bool Algorithms::MayOverflowWithDivision<int>(const int&, const int&);
	extern template bool Algorithms::MayOverflowWithDivision<unsigned int>(const unsigned int&, const unsigned int&);
	extern template bool Algorithms::MayOverflowWithDivision<long>(const long&, const long&);
	extern template bool Algorithms::MayOverflowWithDivision<unsigned long>(const unsigned long&, const unsigned long&);
	extern template bool Algorithms::MayOverflowWithDivision<long long>(const long long&, const long long&);
	extern template bool Algorithms::MayOverflowWithDivision<unsigned long long>(const unsigned long long&, const unsigned long long&);
	extern template bool Algorithms::MayOverflowWithDivision<float>(const float&, const float&);
	extern template bool Algorithms::MayOverflowWithDivision<double>(const double&, const double&);
	extern template bool Algorithms::MayOverflowWithDivision<long double>(const long double&, const long double&);
	extern template bool Algorithms::MayOverflowWithDivision<char16_t>(const char16_t&, const char16_t&);
	extern template bool Algorithms::MayOverflowWithDivision<char32_t>(const char32_t&, const char32_t&);
}
#endif // __stationaryorbit__core_algorithms__