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
#include "stationaryorbit/exception.hpp"
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
		template<typename T, typename = std::enable_if_t<Traits::IsNumeralType<T>>>
		static constexpr T SaturateAdd(const T& left, const T& right)
		{
			static_assert(Traits::IsNumeralType<T>, "テンプレート引数型 T は算術型である必要があります。");
			static_assert(std::is_constructible_v<T, int>, "テンプレート引数型 T は (int) を引数に取るコンストラクタを持つ必要があります。");
			auto result = Add(left, right);
			switch(result.Status)
			{
				case AdditionResultStatus::NoError: { return T(result.Result); }
				case AdditionResultStatus::PositiveOverflow: { return std::numeric_limits<T>::max(); }
				case AdditionResultStatus::NegativeOverflow: { return std::numeric_limits<T>::lowest(); }
				default: { throw InvalidOperationException("計算結果の状態が定義されていない状態になりました。"); }
			}
		}
		template<typename T, typename = std::enable_if_t<Traits::IsNumeralType<T>>>
		static constexpr T SaturateSubtract(const T& left, const T& right)
		{
			static_assert(Traits::IsNumeralType<T>, "テンプレート引数型 T は算術型である必要があります。");
			static_assert(std::is_constructible_v<T, int>, "テンプレート引数型 T は (int) を引数に取るコンストラクタを持つ必要があります。");
			auto result = Subtract(left, right);
			switch(result.Status)
			{
				case AdditionResultStatus::NoError: { return T(result.Result); }
				case AdditionResultStatus::PositiveOverflow: { return std::numeric_limits<T>::max(); }
				case AdditionResultStatus::NegativeOverflow: { return std::numeric_limits<T>::lowest(); }
				default: { throw InvalidOperationException("計算結果の状態が定義されていない状態になりました。"); }
			}
		}
		template<typename T, typename = std::enable_if_t<Traits::IsNumeralType<T>>>
		static constexpr T SaturateMultiply(const T& left, const T& right)
		{
			static_assert(Traits::IsNumeralType<T>, "テンプレート引数型 T は算術型である必要があります。");
			static_assert(std::is_constructible_v<T, int>, "テンプレート引数型 T は (int) を引数に取るコンストラクタを持つ必要があります。");
			auto result = Multiply(left, right);
			switch(result.Status)
			{
				case MultiplicationResultStatus::NoError: { return T(result.Result); }
				case MultiplicationResultStatus::Overflow:
				{
					if constexpr (std::numeric_limits<T>::is_signed)
					{
						if ( ( (left < T(0))||(right < T(0)) ) && !( (left < T(0))&&(right < T(0)) ) ) { return std::numeric_limits<T>::lowest(); }
						else { return std::numeric_limits<T>::max(); }
					}
					else { return std::numeric_limits<T>::max(); }
				}
				default: { throw InvalidOperationException("計算結果の状態が定義されていない状態になりました。"); }
			}
		}
		template<typename T, typename = std::enable_if_t<Traits::IsNumeralType<T>>>
		static constexpr T SaturateDivide(const T& left, const T& right)
		{
			static_assert(Traits::IsNumeralType<T>, "テンプレート引数型 T は算術型である必要があります。");
			static_assert(std::is_constructible_v<T, int>, "テンプレート引数型 T は (int) を引数に取るコンストラクタを持つ必要があります。");
			auto result = Divide(left, right);
			switch(result.Status)
			{
				case MultiplicationResultStatus::NoError: { return T(result.Result); }
				case MultiplicationResultStatus::Overflow:
				{
					if constexpr (std::numeric_limits<T>::is_signed)
					{
						if ( ( (left < T(0))||(right < T(0)) ) && !( (left < T(0))&&(right < T(0)) ) ) { return std::numeric_limits<T>::lowest(); }
						else { return std::numeric_limits<T>::max(); }
					}
					else { return std::numeric_limits<T>::max(); }
				}
				case MultiplicationResultStatus::DivideByZero: { throw std::range_error("除数に0が指定されました。丸め先が定義されないため、丸めを行うことができません。"); }
				default: { throw InvalidOperationException("計算結果の状態が定義されていない状態になりました。"); }
			}
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
	extern template bool ArithmeticOperation::SaturateAdd<bool>(const bool&, const bool&);
	extern template char ArithmeticOperation::SaturateAdd<char>(const char&, const char&);
	extern template signed char ArithmeticOperation::SaturateAdd<signed char>(const signed char&, const signed char&);
	extern template unsigned char ArithmeticOperation::SaturateAdd<unsigned char>(const unsigned char&, const unsigned char&);
	extern template wchar_t ArithmeticOperation::SaturateAdd<wchar_t>(const wchar_t&, const wchar_t&);
	extern template short ArithmeticOperation::SaturateAdd<short>(const short&, const short&);
	extern template unsigned short ArithmeticOperation::SaturateAdd<unsigned short>(const unsigned short&, const unsigned short&);
	extern template int ArithmeticOperation::SaturateAdd<int>(const int&, const int&);
	extern template unsigned int ArithmeticOperation::SaturateAdd<unsigned int>(const unsigned int&, const unsigned int&);
	extern template long ArithmeticOperation::SaturateAdd<long>(const long&, const long&);
	extern template unsigned long ArithmeticOperation::SaturateAdd<unsigned long>(const unsigned long&, const unsigned long&);
	extern template long long ArithmeticOperation::SaturateAdd<long long>(const long long&, const long long&);
	extern template unsigned long long ArithmeticOperation::SaturateAdd<unsigned long long>(const unsigned long long&, const unsigned long long&);
	extern template float ArithmeticOperation::SaturateAdd<float>(const float&, const float&);
	extern template double ArithmeticOperation::SaturateAdd<double>(const double&, const double&);
	extern template long double ArithmeticOperation::SaturateAdd<long double>(const long double&, const long double&);
	extern template char16_t ArithmeticOperation::SaturateAdd<char16_t>(const char16_t&, const char16_t&);
	extern template char32_t ArithmeticOperation::SaturateAdd<char32_t>(const char32_t&, const char32_t&);
	extern template bool ArithmeticOperation::SaturateSubtract<bool>(const bool&, const bool&);
	extern template char ArithmeticOperation::SaturateSubtract<char>(const char&, const char&);
	extern template signed char ArithmeticOperation::SaturateSubtract<signed char>(const signed char&, const signed char&);
	extern template unsigned char ArithmeticOperation::SaturateSubtract<unsigned char>(const unsigned char&, const unsigned char&);
	extern template wchar_t ArithmeticOperation::SaturateSubtract<wchar_t>(const wchar_t&, const wchar_t&);
	extern template short ArithmeticOperation::SaturateSubtract<short>(const short&, const short&);
	extern template unsigned short ArithmeticOperation::SaturateSubtract<unsigned short>(const unsigned short&, const unsigned short&);
	extern template int ArithmeticOperation::SaturateSubtract<int>(const int&, const int&);
	extern template unsigned int ArithmeticOperation::SaturateSubtract<unsigned int>(const unsigned int&, const unsigned int&);
	extern template long ArithmeticOperation::SaturateSubtract<long>(const long&, const long&);
	extern template unsigned long ArithmeticOperation::SaturateSubtract<unsigned long>(const unsigned long&, const unsigned long&);
	extern template long long ArithmeticOperation::SaturateSubtract<long long>(const long long&, const long long&);
	extern template unsigned long long ArithmeticOperation::SaturateSubtract<unsigned long long>(const unsigned long long&, const unsigned long long&);
	extern template float ArithmeticOperation::SaturateSubtract<float>(const float&, const float&);
	extern template double ArithmeticOperation::SaturateSubtract<double>(const double&, const double&);
	extern template long double ArithmeticOperation::SaturateSubtract<long double>(const long double&, const long double&);
	extern template char16_t ArithmeticOperation::SaturateSubtract<char16_t>(const char16_t&, const char16_t&);
	extern template char32_t ArithmeticOperation::SaturateSubtract<char32_t>(const char32_t&, const char32_t&);
	extern template bool ArithmeticOperation::SaturateMultiply<bool>(const bool&, const bool&);
	extern template char ArithmeticOperation::SaturateMultiply<char>(const char&, const char&);
	extern template signed char ArithmeticOperation::SaturateMultiply<signed char>(const signed char&, const signed char&);
	extern template unsigned char ArithmeticOperation::SaturateMultiply<unsigned char>(const unsigned char&, const unsigned char&);
	extern template wchar_t ArithmeticOperation::SaturateMultiply<wchar_t>(const wchar_t&, const wchar_t&);
	extern template short ArithmeticOperation::SaturateMultiply<short>(const short&, const short&);
	extern template unsigned short ArithmeticOperation::SaturateMultiply<unsigned short>(const unsigned short&, const unsigned short&);
	extern template int ArithmeticOperation::SaturateMultiply<int>(const int&, const int&);
	extern template unsigned int ArithmeticOperation::SaturateMultiply<unsigned int>(const unsigned int&, const unsigned int&);
	extern template long ArithmeticOperation::SaturateMultiply<long>(const long&, const long&);
	extern template unsigned long ArithmeticOperation::SaturateMultiply<unsigned long>(const unsigned long&, const unsigned long&);
	extern template long long ArithmeticOperation::SaturateMultiply<long long>(const long long&, const long long&);
	extern template unsigned long long ArithmeticOperation::SaturateMultiply<unsigned long long>(const unsigned long long&, const unsigned long long&);
	extern template float ArithmeticOperation::SaturateMultiply<float>(const float&, const float&);
	extern template double ArithmeticOperation::SaturateMultiply<double>(const double&, const double&);
	extern template long double ArithmeticOperation::SaturateMultiply<long double>(const long double&, const long double&);
	extern template char16_t ArithmeticOperation::SaturateMultiply<char16_t>(const char16_t&, const char16_t&);
	extern template char32_t ArithmeticOperation::SaturateMultiply<char32_t>(const char32_t&, const char32_t&);
	extern template bool ArithmeticOperation::SaturateDivide<bool>(const bool&, const bool&);
	extern template char ArithmeticOperation::SaturateDivide<char>(const char&, const char&);
	extern template signed char ArithmeticOperation::SaturateDivide<signed char>(const signed char&, const signed char&);
	extern template unsigned char ArithmeticOperation::SaturateDivide<unsigned char>(const unsigned char&, const unsigned char&);
	extern template wchar_t ArithmeticOperation::SaturateDivide<wchar_t>(const wchar_t&, const wchar_t&);
	extern template short ArithmeticOperation::SaturateDivide<short>(const short&, const short&);
	extern template unsigned short ArithmeticOperation::SaturateDivide<unsigned short>(const unsigned short&, const unsigned short&);
	extern template int ArithmeticOperation::SaturateDivide<int>(const int&, const int&);
	extern template unsigned int ArithmeticOperation::SaturateDivide<unsigned int>(const unsigned int&, const unsigned int&);
	extern template long ArithmeticOperation::SaturateDivide<long>(const long&, const long&);
	extern template unsigned long ArithmeticOperation::SaturateDivide<unsigned long>(const unsigned long&, const unsigned long&);
	extern template long long ArithmeticOperation::SaturateDivide<long long>(const long long&, const long long&);
	extern template unsigned long long ArithmeticOperation::SaturateDivide<unsigned long long>(const unsigned long long&, const unsigned long long&);
	extern template float ArithmeticOperation::SaturateDivide<float>(const float&, const float&);
	extern template double ArithmeticOperation::SaturateDivide<double>(const double&, const double&);
	extern template long double ArithmeticOperation::SaturateDivide<long double>(const long double&, const long double&);
	extern template char16_t ArithmeticOperation::SaturateDivide<char16_t>(const char16_t&, const char16_t&);
	extern template char32_t ArithmeticOperation::SaturateDivide<char32_t>(const char32_t&, const char32_t&);
}
#endif // __stationaryorbit_core_arithmetic__
