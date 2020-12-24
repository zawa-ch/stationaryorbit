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

		template<typename T>
		static constexpr AdditionResult<T> Add(const T& left, const T& right) noexcept
		{
			static_assert(Traits::IsNumericalType<T>, "テンプレート引数型 T は数値型である必要があります。");
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
		template<typename T>
		static constexpr AdditionResult<T> Subtract(const T& left, const T& right) noexcept
		{
			static_assert(Traits::IsNumericalType<T>, "テンプレート引数型 T は数値型である必要があります。");
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
		template<typename T>
		static MultiplicationResult<T> Multiply(const T& left, const T& right) noexcept
		{
			static_assert(Traits::IsNumericalType<T>, "テンプレート引数型 T は数値型である必要があります。");
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
		template<typename T>
		static MultiplicationResult<T> Divide(const T& left, const T& right) noexcept
		{
			static_assert(Traits::IsNumericalType<T>, "テンプレート引数型 T は数値型である必要があります。");
			static_assert(std::is_constructible_v<T, int>, "テンプレート引数型 T は (int) を引数に取るコンストラクタを持つ必要があります。");
			if (right == T(0))
			{
				if constexpr (std::numeric_limits<T>::is_iec559) { return MultiplicationResult<T>{ left / right , MultiplicationResultStatus::DivideByZero }; }
				else { return MultiplicationResult<T>{ T(0) , MultiplicationResultStatus::DivideByZero }; }
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
		template<typename T>
		static constexpr T SaturateAdd(const T& left, const T& right)
		{
			static_assert(Traits::IsNumericalType<T>, "テンプレート引数型 T は数値型である必要があります。");
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
		template<typename T>
		static constexpr T SaturateSubtract(const T& left, const T& right)
		{
			static_assert(Traits::IsNumericalType<T>, "テンプレート引数型 T は数値型である必要があります。");
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
		template<typename T>
		static constexpr T SaturateMultiply(const T& left, const T& right)
		{
			static_assert(Traits::IsNumericalType<T>, "テンプレート引数型 T は数値型である必要があります。");
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
				case MultiplicationResultStatus::DivideByZero: { throw std::range_error("除数に0が指定されました。丸め先が定義されないため、丸めを行うことができません。"); }
				default: { throw InvalidOperationException("計算結果の状態が定義されていない状態になりました。"); }
			}
		}
		template<typename T>
		static constexpr T SaturateDivide(const T& left, const T& right)
		{
			static_assert(Traits::IsNumericalType<T>, "テンプレート引数型 T は数値型である必要があります。");
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
		template<typename T>
		static constexpr T CheckedAdd(const T& left, const T& right)
		{
			static_assert(Traits::IsNumericalType<T>, "テンプレート引数型 T は数値型である必要があります。");
			static_assert(std::is_constructible_v<T, int>, "テンプレート引数型 T は (int) を引数に取るコンストラクタを持つ必要があります。");
			auto result = Add(left, right);
			switch(result.Status)
			{
				case AdditionResultStatus::NoError: { return T(result.Result); }
				case AdditionResultStatus::PositiveOverflow:
				case AdditionResultStatus::NegativeOverflow:
				{ throw std::range_error("計算結果がこの型で表せる値域を超えています。"); }
				default: { throw InvalidOperationException("計算結果の状態が定義されていない状態になりました。"); }
			}
		}
		template<typename T>
		static constexpr T CheckedSubtract(const T& left, const T& right)
		{
			static_assert(Traits::IsNumericalType<T>, "テンプレート引数型 T は数値型である必要があります。");
			static_assert(std::is_constructible_v<T, int>, "テンプレート引数型 T は (int) を引数に取るコンストラクタを持つ必要があります。");
			auto result = Subtract(left, right);
			switch(result.Status)
			{
				case AdditionResultStatus::NoError: { return T(result.Result); }
				case AdditionResultStatus::PositiveOverflow:
				case AdditionResultStatus::NegativeOverflow:
				{ throw std::range_error("計算結果がこの型で表せる値域を超えています。"); }
				default: { throw InvalidOperationException("計算結果の状態が定義されていない状態になりました。"); }
			}
		}
		template<typename T>
		static constexpr T CheckedMultiply(const T& left, const T& right)
		{
			static_assert(Traits::IsNumericalType<T>, "テンプレート引数型 T は数値型である必要があります。");
			static_assert(std::is_constructible_v<T, int>, "テンプレート引数型 T は (int) を引数に取るコンストラクタを持つ必要があります。");
			auto result = Multiply(left, right);
			switch(result.Status)
			{
				case MultiplicationResultStatus::NoError: { return T(result.Result); }
				case MultiplicationResultStatus::Overflow:
				case MultiplicationResultStatus::DivideByZero:
				{ throw std::range_error("計算結果がこの型で表せる値域を超えています。"); }
				default: { throw InvalidOperationException("計算結果の状態が定義されていない状態になりました。"); }
			}
		}
		template<typename T>
		static constexpr T CheckedDivide(const T& left, const T& right)
		{
			static_assert(Traits::IsNumericalType<T>, "テンプレート引数型 T は数値型である必要があります。");
			static_assert(std::is_constructible_v<T, int>, "テンプレート引数型 T は (int) を引数に取るコンストラクタを持つ必要があります。");
			auto result = Divide(left, right);
			switch(result.Status)
			{
				case MultiplicationResultStatus::NoError: { return T(result.Result); }
				case MultiplicationResultStatus::Overflow:
				case MultiplicationResultStatus::DivideByZero:
				{ throw std::range_error("計算結果がこの型で表せる値域を超えています。"); }
				default: { throw InvalidOperationException("計算結果の状態が定義されていない状態になりました。"); }
			}
		}
		template<class Tp>
		static constexpr bool MayOverflowWithAddition(const Tp& left, const Tp& right) noexcept
		{
			static_assert(Traits::IsNumericalType<Tp>, "テンプレート引数型 Tp は数値型である必要があります。");
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
			static_assert(Traits::IsNumericalType<Tp>, "テンプレート引数型 Tp は数値型である必要があります。");
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
			static_assert(Traits::IsNumericalType<Tp>, "テンプレート引数型 Tp は数値型である必要があります。");
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
			static_assert(Traits::IsNumericalType<Tp>, "テンプレート引数型 Tp は数値型である必要があります。");
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
	extern template bool ArithmeticOperation::CheckedAdd<bool>(const bool&, const bool&);
	extern template char ArithmeticOperation::CheckedAdd<char>(const char&, const char&);
	extern template signed char ArithmeticOperation::CheckedAdd<signed char>(const signed char&, const signed char&);
	extern template unsigned char ArithmeticOperation::CheckedAdd<unsigned char>(const unsigned char&, const unsigned char&);
	extern template wchar_t ArithmeticOperation::CheckedAdd<wchar_t>(const wchar_t&, const wchar_t&);
	extern template short ArithmeticOperation::CheckedAdd<short>(const short&, const short&);
	extern template unsigned short ArithmeticOperation::CheckedAdd<unsigned short>(const unsigned short&, const unsigned short&);
	extern template int ArithmeticOperation::CheckedAdd<int>(const int&, const int&);
	extern template unsigned int ArithmeticOperation::CheckedAdd<unsigned int>(const unsigned int&, const unsigned int&);
	extern template long ArithmeticOperation::CheckedAdd<long>(const long&, const long&);
	extern template unsigned long ArithmeticOperation::CheckedAdd<unsigned long>(const unsigned long&, const unsigned long&);
	extern template long long ArithmeticOperation::CheckedAdd<long long>(const long long&, const long long&);
	extern template unsigned long long ArithmeticOperation::CheckedAdd<unsigned long long>(const unsigned long long&, const unsigned long long&);
	extern template float ArithmeticOperation::CheckedAdd<float>(const float&, const float&);
	extern template double ArithmeticOperation::CheckedAdd<double>(const double&, const double&);
	extern template long double ArithmeticOperation::CheckedAdd<long double>(const long double&, const long double&);
	extern template char16_t ArithmeticOperation::CheckedAdd<char16_t>(const char16_t&, const char16_t&);
	extern template char32_t ArithmeticOperation::CheckedAdd<char32_t>(const char32_t&, const char32_t&);
	extern template bool ArithmeticOperation::CheckedSubtract<bool>(const bool&, const bool&);
	extern template char ArithmeticOperation::CheckedSubtract<char>(const char&, const char&);
	extern template signed char ArithmeticOperation::CheckedSubtract<signed char>(const signed char&, const signed char&);
	extern template unsigned char ArithmeticOperation::CheckedSubtract<unsigned char>(const unsigned char&, const unsigned char&);
	extern template wchar_t ArithmeticOperation::CheckedSubtract<wchar_t>(const wchar_t&, const wchar_t&);
	extern template short ArithmeticOperation::CheckedSubtract<short>(const short&, const short&);
	extern template unsigned short ArithmeticOperation::CheckedSubtract<unsigned short>(const unsigned short&, const unsigned short&);
	extern template int ArithmeticOperation::CheckedSubtract<int>(const int&, const int&);
	extern template unsigned int ArithmeticOperation::CheckedSubtract<unsigned int>(const unsigned int&, const unsigned int&);
	extern template long ArithmeticOperation::CheckedSubtract<long>(const long&, const long&);
	extern template unsigned long ArithmeticOperation::CheckedSubtract<unsigned long>(const unsigned long&, const unsigned long&);
	extern template long long ArithmeticOperation::CheckedSubtract<long long>(const long long&, const long long&);
	extern template unsigned long long ArithmeticOperation::CheckedSubtract<unsigned long long>(const unsigned long long&, const unsigned long long&);
	extern template float ArithmeticOperation::CheckedSubtract<float>(const float&, const float&);
	extern template double ArithmeticOperation::CheckedSubtract<double>(const double&, const double&);
	extern template long double ArithmeticOperation::CheckedSubtract<long double>(const long double&, const long double&);
	extern template char16_t ArithmeticOperation::CheckedSubtract<char16_t>(const char16_t&, const char16_t&);
	extern template char32_t ArithmeticOperation::CheckedSubtract<char32_t>(const char32_t&, const char32_t&);
	extern template bool ArithmeticOperation::CheckedMultiply<bool>(const bool&, const bool&);
	extern template char ArithmeticOperation::CheckedMultiply<char>(const char&, const char&);
	extern template signed char ArithmeticOperation::CheckedMultiply<signed char>(const signed char&, const signed char&);
	extern template unsigned char ArithmeticOperation::CheckedMultiply<unsigned char>(const unsigned char&, const unsigned char&);
	extern template wchar_t ArithmeticOperation::CheckedMultiply<wchar_t>(const wchar_t&, const wchar_t&);
	extern template short ArithmeticOperation::CheckedMultiply<short>(const short&, const short&);
	extern template unsigned short ArithmeticOperation::CheckedMultiply<unsigned short>(const unsigned short&, const unsigned short&);
	extern template int ArithmeticOperation::CheckedMultiply<int>(const int&, const int&);
	extern template unsigned int ArithmeticOperation::CheckedMultiply<unsigned int>(const unsigned int&, const unsigned int&);
	extern template long ArithmeticOperation::CheckedMultiply<long>(const long&, const long&);
	extern template unsigned long ArithmeticOperation::CheckedMultiply<unsigned long>(const unsigned long&, const unsigned long&);
	extern template long long ArithmeticOperation::CheckedMultiply<long long>(const long long&, const long long&);
	extern template unsigned long long ArithmeticOperation::CheckedMultiply<unsigned long long>(const unsigned long long&, const unsigned long long&);
	extern template float ArithmeticOperation::CheckedMultiply<float>(const float&, const float&);
	extern template double ArithmeticOperation::CheckedMultiply<double>(const double&, const double&);
	extern template long double ArithmeticOperation::CheckedMultiply<long double>(const long double&, const long double&);
	extern template char16_t ArithmeticOperation::CheckedMultiply<char16_t>(const char16_t&, const char16_t&);
	extern template char32_t ArithmeticOperation::CheckedMultiply<char32_t>(const char32_t&, const char32_t&);
	extern template bool ArithmeticOperation::CheckedDivide<bool>(const bool&, const bool&);
	extern template char ArithmeticOperation::CheckedDivide<char>(const char&, const char&);
	extern template signed char ArithmeticOperation::CheckedDivide<signed char>(const signed char&, const signed char&);
	extern template unsigned char ArithmeticOperation::CheckedDivide<unsigned char>(const unsigned char&, const unsigned char&);
	extern template wchar_t ArithmeticOperation::CheckedDivide<wchar_t>(const wchar_t&, const wchar_t&);
	extern template short ArithmeticOperation::CheckedDivide<short>(const short&, const short&);
	extern template unsigned short ArithmeticOperation::CheckedDivide<unsigned short>(const unsigned short&, const unsigned short&);
	extern template int ArithmeticOperation::CheckedDivide<int>(const int&, const int&);
	extern template unsigned int ArithmeticOperation::CheckedDivide<unsigned int>(const unsigned int&, const unsigned int&);
	extern template long ArithmeticOperation::CheckedDivide<long>(const long&, const long&);
	extern template unsigned long ArithmeticOperation::CheckedDivide<unsigned long>(const unsigned long&, const unsigned long&);
	extern template long long ArithmeticOperation::CheckedDivide<long long>(const long long&, const long long&);
	extern template unsigned long long ArithmeticOperation::CheckedDivide<unsigned long long>(const unsigned long long&, const unsigned long long&);
	extern template float ArithmeticOperation::CheckedDivide<float>(const float&, const float&);
	extern template double ArithmeticOperation::CheckedDivide<double>(const double&, const double&);
	extern template long double ArithmeticOperation::CheckedDivide<long double>(const long double&, const long double&);
	extern template char16_t ArithmeticOperation::CheckedDivide<char16_t>(const char16_t&, const char16_t&);
	extern template char32_t ArithmeticOperation::CheckedDivide<char32_t>(const char32_t&, const char32_t&);
	extern template bool ArithmeticOperation::MayOverflowWithAddition<bool>(const bool&, const bool&);
	extern template bool ArithmeticOperation::MayOverflowWithAddition<char>(const char&, const char&);
	extern template bool ArithmeticOperation::MayOverflowWithAddition<signed char>(const signed char&, const signed char&);
	extern template bool ArithmeticOperation::MayOverflowWithAddition<unsigned char>(const unsigned char&, const unsigned char&);
	extern template bool ArithmeticOperation::MayOverflowWithAddition<wchar_t>(const wchar_t&, const wchar_t&);
	extern template bool ArithmeticOperation::MayOverflowWithAddition<short>(const short&, const short&);
	extern template bool ArithmeticOperation::MayOverflowWithAddition<unsigned short>(const unsigned short&, const unsigned short&);
	extern template bool ArithmeticOperation::MayOverflowWithAddition<int>(const int&, const int&);
	extern template bool ArithmeticOperation::MayOverflowWithAddition<unsigned int>(const unsigned int&, const unsigned int&);
	extern template bool ArithmeticOperation::MayOverflowWithAddition<long>(const long&, const long&);
	extern template bool ArithmeticOperation::MayOverflowWithAddition<unsigned long>(const unsigned long&, const unsigned long&);
	extern template bool ArithmeticOperation::MayOverflowWithAddition<long long>(const long long&, const long long&);
	extern template bool ArithmeticOperation::MayOverflowWithAddition<unsigned long long>(const unsigned long long&, const unsigned long long&);
	extern template bool ArithmeticOperation::MayOverflowWithAddition<float>(const float&, const float&);
	extern template bool ArithmeticOperation::MayOverflowWithAddition<double>(const double&, const double&);
	extern template bool ArithmeticOperation::MayOverflowWithAddition<long double>(const long double&, const long double&);
	extern template bool ArithmeticOperation::MayOverflowWithAddition<char16_t>(const char16_t&, const char16_t&);
	extern template bool ArithmeticOperation::MayOverflowWithAddition<char32_t>(const char32_t&, const char32_t&);
	extern template bool ArithmeticOperation::MayOverflowWithSubtraction<bool>(const bool&, const bool&);
	extern template bool ArithmeticOperation::MayOverflowWithSubtraction<char>(const char&, const char&);
	extern template bool ArithmeticOperation::MayOverflowWithSubtraction<signed char>(const signed char&, const signed char&);
	extern template bool ArithmeticOperation::MayOverflowWithSubtraction<unsigned char>(const unsigned char&, const unsigned char&);
	extern template bool ArithmeticOperation::MayOverflowWithSubtraction<wchar_t>(const wchar_t&, const wchar_t&);
	extern template bool ArithmeticOperation::MayOverflowWithSubtraction<short>(const short&, const short&);
	extern template bool ArithmeticOperation::MayOverflowWithSubtraction<unsigned short>(const unsigned short&, const unsigned short&);
	extern template bool ArithmeticOperation::MayOverflowWithSubtraction<int>(const int&, const int&);
	extern template bool ArithmeticOperation::MayOverflowWithSubtraction<unsigned int>(const unsigned int&, const unsigned int&);
	extern template bool ArithmeticOperation::MayOverflowWithSubtraction<long>(const long&, const long&);
	extern template bool ArithmeticOperation::MayOverflowWithSubtraction<unsigned long>(const unsigned long&, const unsigned long&);
	extern template bool ArithmeticOperation::MayOverflowWithSubtraction<long long>(const long long&, const long long&);
	extern template bool ArithmeticOperation::MayOverflowWithSubtraction<unsigned long long>(const unsigned long long&, const unsigned long long&);
	extern template bool ArithmeticOperation::MayOverflowWithSubtraction<float>(const float&, const float&);
	extern template bool ArithmeticOperation::MayOverflowWithSubtraction<double>(const double&, const double&);
	extern template bool ArithmeticOperation::MayOverflowWithSubtraction<long double>(const long double&, const long double&);
	extern template bool ArithmeticOperation::MayOverflowWithSubtraction<char16_t>(const char16_t&, const char16_t&);
	extern template bool ArithmeticOperation::MayOverflowWithSubtraction<char32_t>(const char32_t&, const char32_t&);
	extern template bool ArithmeticOperation::MayOverflowWithMultiplication<bool>(const bool&, const bool&);
	extern template bool ArithmeticOperation::MayOverflowWithMultiplication<char>(const char&, const char&);
	extern template bool ArithmeticOperation::MayOverflowWithMultiplication<signed char>(const signed char&, const signed char&);
	extern template bool ArithmeticOperation::MayOverflowWithMultiplication<unsigned char>(const unsigned char&, const unsigned char&);
	extern template bool ArithmeticOperation::MayOverflowWithMultiplication<wchar_t>(const wchar_t&, const wchar_t&);
	extern template bool ArithmeticOperation::MayOverflowWithMultiplication<short>(const short&, const short&);
	extern template bool ArithmeticOperation::MayOverflowWithMultiplication<unsigned short>(const unsigned short&, const unsigned short&);
	extern template bool ArithmeticOperation::MayOverflowWithMultiplication<int>(const int&, const int&);
	extern template bool ArithmeticOperation::MayOverflowWithMultiplication<unsigned int>(const unsigned int&, const unsigned int&);
	extern template bool ArithmeticOperation::MayOverflowWithMultiplication<long>(const long&, const long&);
	extern template bool ArithmeticOperation::MayOverflowWithMultiplication<unsigned long>(const unsigned long&, const unsigned long&);
	extern template bool ArithmeticOperation::MayOverflowWithMultiplication<long long>(const long long&, const long long&);
	extern template bool ArithmeticOperation::MayOverflowWithMultiplication<unsigned long long>(const unsigned long long&, const unsigned long long&);
	extern template bool ArithmeticOperation::MayOverflowWithMultiplication<float>(const float&, const float&);
	extern template bool ArithmeticOperation::MayOverflowWithMultiplication<double>(const double&, const double&);
	extern template bool ArithmeticOperation::MayOverflowWithMultiplication<long double>(const long double&, const long double&);
	extern template bool ArithmeticOperation::MayOverflowWithMultiplication<char16_t>(const char16_t&, const char16_t&);
	extern template bool ArithmeticOperation::MayOverflowWithMultiplication<char32_t>(const char32_t&, const char32_t&);
	extern template bool ArithmeticOperation::MayOverflowWithDivision<bool>(const bool&, const bool&);
	extern template bool ArithmeticOperation::MayOverflowWithDivision<char>(const char&, const char&);
	extern template bool ArithmeticOperation::MayOverflowWithDivision<signed char>(const signed char&, const signed char&);
	extern template bool ArithmeticOperation::MayOverflowWithDivision<unsigned char>(const unsigned char&, const unsigned char&);
	extern template bool ArithmeticOperation::MayOverflowWithDivision<wchar_t>(const wchar_t&, const wchar_t&);
	extern template bool ArithmeticOperation::MayOverflowWithDivision<short>(const short&, const short&);
	extern template bool ArithmeticOperation::MayOverflowWithDivision<unsigned short>(const unsigned short&, const unsigned short&);
	extern template bool ArithmeticOperation::MayOverflowWithDivision<int>(const int&, const int&);
	extern template bool ArithmeticOperation::MayOverflowWithDivision<unsigned int>(const unsigned int&, const unsigned int&);
	extern template bool ArithmeticOperation::MayOverflowWithDivision<long>(const long&, const long&);
	extern template bool ArithmeticOperation::MayOverflowWithDivision<unsigned long>(const unsigned long&, const unsigned long&);
	extern template bool ArithmeticOperation::MayOverflowWithDivision<long long>(const long long&, const long long&);
	extern template bool ArithmeticOperation::MayOverflowWithDivision<unsigned long long>(const unsigned long long&, const unsigned long long&);
	extern template bool ArithmeticOperation::MayOverflowWithDivision<float>(const float&, const float&);
	extern template bool ArithmeticOperation::MayOverflowWithDivision<double>(const double&, const double&);
	extern template bool ArithmeticOperation::MayOverflowWithDivision<long double>(const long double&, const long double&);
	extern template bool ArithmeticOperation::MayOverflowWithDivision<char16_t>(const char16_t&, const char16_t&);
	extern template bool ArithmeticOperation::MayOverflowWithDivision<char32_t>(const char32_t&, const char32_t&);
}
#endif // __stationaryorbit_core_arithmetic__
