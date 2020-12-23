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

	extern template ArithmeticOperation::AdditionResult<bool> ArithmeticOperation::Add<bool>(const bool&, const bool&);
	extern template ArithmeticOperation::AdditionResult<char> ArithmeticOperation::Add<char>(const char&, const char&);
	extern template ArithmeticOperation::AdditionResult<signed char> ArithmeticOperation::Add<signed char>(const signed char&, const signed char&);
	extern template ArithmeticOperation::AdditionResult<unsigned char> ArithmeticOperation::Add<unsigned char>(const unsigned char&, const unsigned char&);
	extern template ArithmeticOperation::AdditionResult<wchar_t> ArithmeticOperation::Add<wchar_t>(const wchar_t&, const wchar_t&);
	extern template ArithmeticOperation::AdditionResult<short> ArithmeticOperation::Add<short>(const short&, const short&);
	extern template ArithmeticOperation::AdditionResult<unsigned short> ArithmeticOperation::Add<unsigned short>(const unsigned short&, const unsigned short&);
	extern template ArithmeticOperation::AdditionResult<int> ArithmeticOperation::Add<int>(const int&, const int&);
	extern template ArithmeticOperation::AdditionResult<unsigned int> ArithmeticOperation::Add<unsigned int>(const unsigned int&, const unsigned int&);
	extern template ArithmeticOperation::AdditionResult<long> ArithmeticOperation::Add<long>(const long&, const long&);
	extern template ArithmeticOperation::AdditionResult<unsigned long> ArithmeticOperation::Add<unsigned long>(const unsigned long&, const unsigned long&);
	extern template ArithmeticOperation::AdditionResult<long long> ArithmeticOperation::Add<long long>(const long long&, const long long&);
	extern template ArithmeticOperation::AdditionResult<unsigned long long> ArithmeticOperation::Add<unsigned long long>(const unsigned long long&, const unsigned long long&);
	extern template ArithmeticOperation::AdditionResult<float> ArithmeticOperation::Add<float>(const float&, const float&);
	extern template ArithmeticOperation::AdditionResult<double> ArithmeticOperation::Add<double>(const double&, const double&);
	extern template ArithmeticOperation::AdditionResult<long double> ArithmeticOperation::Add<long double>(const long double&, const long double&);
	extern template ArithmeticOperation::AdditionResult<char16_t> ArithmeticOperation::Add<char16_t>(const char16_t&, const char16_t&);
	extern template ArithmeticOperation::AdditionResult<char32_t> ArithmeticOperation::Add<char32_t>(const char32_t&, const char32_t&);
	extern template ArithmeticOperation::AdditionResult<bool> ArithmeticOperation::Subtract<bool>(const bool&, const bool&);
	extern template ArithmeticOperation::AdditionResult<char> ArithmeticOperation::Subtract<char>(const char&, const char&);
	extern template ArithmeticOperation::AdditionResult<signed char> ArithmeticOperation::Subtract<signed char>(const signed char&, const signed char&);
	extern template ArithmeticOperation::AdditionResult<unsigned char> ArithmeticOperation::Subtract<unsigned char>(const unsigned char&, const unsigned char&);
	extern template ArithmeticOperation::AdditionResult<wchar_t> ArithmeticOperation::Subtract<wchar_t>(const wchar_t&, const wchar_t&);
	extern template ArithmeticOperation::AdditionResult<short> ArithmeticOperation::Subtract<short>(const short&, const short&);
	extern template ArithmeticOperation::AdditionResult<unsigned short> ArithmeticOperation::Subtract<unsigned short>(const unsigned short&, const unsigned short&);
	extern template ArithmeticOperation::AdditionResult<int> ArithmeticOperation::Subtract<int>(const int&, const int&);
	extern template ArithmeticOperation::AdditionResult<unsigned int> ArithmeticOperation::Subtract<unsigned int>(const unsigned int&, const unsigned int&);
	extern template ArithmeticOperation::AdditionResult<long> ArithmeticOperation::Subtract<long>(const long&, const long&);
	extern template ArithmeticOperation::AdditionResult<unsigned long> ArithmeticOperation::Subtract<unsigned long>(const unsigned long&, const unsigned long&);
	extern template ArithmeticOperation::AdditionResult<long long> ArithmeticOperation::Subtract<long long>(const long long&, const long long&);
	extern template ArithmeticOperation::AdditionResult<unsigned long long> ArithmeticOperation::Subtract<unsigned long long>(const unsigned long long&, const unsigned long long&);
	extern template ArithmeticOperation::AdditionResult<float> ArithmeticOperation::Subtract<float>(const float&, const float&);
	extern template ArithmeticOperation::AdditionResult<double> ArithmeticOperation::Subtract<double>(const double&, const double&);
	extern template ArithmeticOperation::AdditionResult<long double> ArithmeticOperation::Subtract<long double>(const long double&, const long double&);
	extern template ArithmeticOperation::AdditionResult<char16_t> ArithmeticOperation::Subtract<char16_t>(const char16_t&, const char16_t&);
	extern template ArithmeticOperation::AdditionResult<char32_t> ArithmeticOperation::Subtract<char32_t>(const char32_t&, const char32_t&);
	extern template ArithmeticOperation::MultiplicationResult<bool> ArithmeticOperation::Multiply<bool>(const bool&, const bool&);
	extern template ArithmeticOperation::MultiplicationResult<char> ArithmeticOperation::Multiply<char>(const char&, const char&);
	extern template ArithmeticOperation::MultiplicationResult<signed char> ArithmeticOperation::Multiply<signed char>(const signed char&, const signed char&);
	extern template ArithmeticOperation::MultiplicationResult<unsigned char> ArithmeticOperation::Multiply<unsigned char>(const unsigned char&, const unsigned char&);
	extern template ArithmeticOperation::MultiplicationResult<wchar_t> ArithmeticOperation::Multiply<wchar_t>(const wchar_t&, const wchar_t&);
	extern template ArithmeticOperation::MultiplicationResult<short> ArithmeticOperation::Multiply<short>(const short&, const short&);
	extern template ArithmeticOperation::MultiplicationResult<unsigned short> ArithmeticOperation::Multiply<unsigned short>(const unsigned short&, const unsigned short&);
	extern template ArithmeticOperation::MultiplicationResult<int> ArithmeticOperation::Multiply<int>(const int&, const int&);
	extern template ArithmeticOperation::MultiplicationResult<unsigned int> ArithmeticOperation::Multiply<unsigned int>(const unsigned int&, const unsigned int&);
	extern template ArithmeticOperation::MultiplicationResult<long> ArithmeticOperation::Multiply<long>(const long&, const long&);
	extern template ArithmeticOperation::MultiplicationResult<unsigned long> ArithmeticOperation::Multiply<unsigned long>(const unsigned long&, const unsigned long&);
	extern template ArithmeticOperation::MultiplicationResult<long long> ArithmeticOperation::Multiply<long long>(const long long&, const long long&);
	extern template ArithmeticOperation::MultiplicationResult<unsigned long long> ArithmeticOperation::Multiply<unsigned long long>(const unsigned long long&, const unsigned long long&);
	extern template ArithmeticOperation::MultiplicationResult<float> ArithmeticOperation::Multiply<float>(const float&, const float&);
	extern template ArithmeticOperation::MultiplicationResult<double> ArithmeticOperation::Multiply<double>(const double&, const double&);
	extern template ArithmeticOperation::MultiplicationResult<long double> ArithmeticOperation::Multiply<long double>(const long double&, const long double&);
	extern template ArithmeticOperation::MultiplicationResult<char16_t> ArithmeticOperation::Multiply<char16_t>(const char16_t&, const char16_t&);
	extern template ArithmeticOperation::MultiplicationResult<char32_t> ArithmeticOperation::Multiply<char32_t>(const char32_t&, const char32_t&);
	extern template ArithmeticOperation::MultiplicationResult<bool> ArithmeticOperation::Divide<bool>(const bool&, const bool&);
	extern template ArithmeticOperation::MultiplicationResult<char> ArithmeticOperation::Divide<char>(const char&, const char&);
	extern template ArithmeticOperation::MultiplicationResult<signed char> ArithmeticOperation::Divide<signed char>(const signed char&, const signed char&);
	extern template ArithmeticOperation::MultiplicationResult<unsigned char> ArithmeticOperation::Divide<unsigned char>(const unsigned char&, const unsigned char&);
	extern template ArithmeticOperation::MultiplicationResult<wchar_t> ArithmeticOperation::Divide<wchar_t>(const wchar_t&, const wchar_t&);
	extern template ArithmeticOperation::MultiplicationResult<short> ArithmeticOperation::Divide<short>(const short&, const short&);
	extern template ArithmeticOperation::MultiplicationResult<unsigned short> ArithmeticOperation::Divide<unsigned short>(const unsigned short&, const unsigned short&);
	extern template ArithmeticOperation::MultiplicationResult<int> ArithmeticOperation::Divide<int>(const int&, const int&);
	extern template ArithmeticOperation::MultiplicationResult<unsigned int> ArithmeticOperation::Divide<unsigned int>(const unsigned int&, const unsigned int&);
	extern template ArithmeticOperation::MultiplicationResult<long> ArithmeticOperation::Divide<long>(const long&, const long&);
	extern template ArithmeticOperation::MultiplicationResult<unsigned long> ArithmeticOperation::Divide<unsigned long>(const unsigned long&, const unsigned long&);
	extern template ArithmeticOperation::MultiplicationResult<long long> ArithmeticOperation::Divide<long long>(const long long&, const long long&);
	extern template ArithmeticOperation::MultiplicationResult<unsigned long long> ArithmeticOperation::Divide<unsigned long long>(const unsigned long long&, const unsigned long long&);
	extern template ArithmeticOperation::MultiplicationResult<float> ArithmeticOperation::Divide<float>(const float&, const float&);
	extern template ArithmeticOperation::MultiplicationResult<double> ArithmeticOperation::Divide<double>(const double&, const double&);
	extern template ArithmeticOperation::MultiplicationResult<long double> ArithmeticOperation::Divide<long double>(const long double&, const long double&);
	extern template ArithmeticOperation::MultiplicationResult<char16_t> ArithmeticOperation::Divide<char16_t>(const char16_t&, const char16_t&);
	extern template ArithmeticOperation::MultiplicationResult<char32_t> ArithmeticOperation::Divide<char32_t>(const char32_t&, const char32_t&);
}
#endif // __stationaryorbit_core_arithmetic__
