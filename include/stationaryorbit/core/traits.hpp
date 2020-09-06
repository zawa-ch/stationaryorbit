//	stationaryorbit/core/traits
//	Copyright 2020 zawa-ch.
//	LGPLv3 (or later) license
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU Lesser General Public License as
//	published by the Free Software Foundation, either version 3 of the
//	License, or any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//	See the GNU Lesser General Public License for more details.
//
//	You should have received a copy of the GNU Lesser General Public
//	License along with this program.
//	If not, see <http://www.gnu.org/licenses/>.
//
#ifndef __stationaryorbit_core_traits__
#define __stationaryorbit_core_traits__
#include <type_traits>
#include <bitset>
namespace zawa_ch::StationaryOrbit
{
	///	このライブラリで用いられる型特性の識別を行います。
	class Traits final
	{
	private:
		Traits() = delete;
		Traits(const Traits&) = delete;
		Traits& operator=(const Traits&) = delete;
		Traits&& operator=(Traits&&) = delete;
		Traits(Traits&&) = delete;
		~Traits() = delete;

		template<class, class = std::void_t<>>
		struct HasPromotion_t : std::false_type {};
		template<class T>
		struct HasPromotion_t<T, std::void_t< decltype( +std::declval<T&>() ) > >
			: std::is_convertible< decltype( +std::declval<T&>() ), T> {};

		template<class, class = std::void_t<>>
		struct HasInverse_t : std::false_type {};
		template<class T>
		struct HasInverse_t<T, std::void_t< decltype( -std::declval<T&>() ) > >
			: std::is_convertible< decltype( -std::declval<T&>() ), T> {};

		template<class, class, class = std::void_t<>>
		struct HasAddition_t : std::false_type {};
		template<class T, class U>
		struct HasAddition_t<T, U, std::void_t< decltype( std::declval<T&>() + std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() + std::declval<U&>() ), T> {};

		template<class, class, class = std::void_t<>>
		struct HasSubtraction_t : std::false_type {};
		template<class T, class U>
		struct HasSubtraction_t<T, U, std::void_t< decltype( std::declval<T&>() - std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() - std::declval<U&>() ), T> {};

		template<class, class, class = std::void_t<>>
		struct HasMultiplication_t : std::false_type {};
		template<class T, class U>
		struct HasMultiplication_t<T, U, std::void_t< decltype( std::declval<T&>() * std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() * std::declval<U&>() ), T> {};

		template<class, class, class = std::void_t<>>
		struct HasDivision_t : std::false_type {};
		template<class T, class U>
		struct HasDivision_t<T, U, std::void_t< decltype( std::declval<T&>() / std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() / std::declval<U&>() ), T> {};

		template<class, class, class = std::void_t<>>
		struct HasModulation_t : std::false_type {};
		template<class T, class U>
		struct HasModulation_t<T, U, std::void_t< decltype( std::declval<T&>() % std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() % std::declval<U&>() ), T> {};

		template<class, class = std::void_t<>>
		struct HasArithmeticNot_t : std::false_type {};
		template<class T>
		struct HasArithmeticNot_t<T, std::void_t< decltype( ~std::declval<T&>() ) > >
			: std::is_convertible< decltype( ~std::declval<T&>() ), T> {};

		template<class, class, class = std::void_t<>>
		struct HasArithmeticOr_t : std::false_type {};
		template<class T, class U>
		struct HasArithmeticOr_t<T, U, std::void_t< decltype( std::declval<T&>() | std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() | std::declval<U&>() ), T> {};

		template<class, class, class = std::void_t<>>
		struct HasArithmeticAnd_t : std::false_type {};
		template<class T, class U>
		struct HasArithmeticAnd_t<T, U, std::void_t< decltype( std::declval<T&>() & std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() & std::declval<U&>() ), T> {};

		template<class, class, class = std::void_t<>>
		struct HasArithmeticXor_t : std::false_type {};
		template<class T, class U>
		struct HasArithmeticXor_t<T, U, std::void_t< decltype( std::declval<T&>() ^ std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() ^ std::declval<U&>() ), T> {};

		template<class, class, class = std::void_t<>>
		struct HasLShift_t : std::false_type {};
		template<class T, class U>
		struct HasLShift_t<T, U, std::void_t< decltype( std::declval<T&>() << std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() << std::declval<U&>() ), T> {};

		template<class, class, class = std::void_t<>>
		struct HasRShift_t : std::false_type {};
		template<class T, class U>
		struct HasRShift_t<T, U, std::void_t< decltype( std::declval<T&>() >> std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() >> std::declval<U&>() ), T> {};

		template<class T>
		struct HasUnaryOperation_t : std::conjunction<HasPromotion_t<T>, HasInverse_t<T>> {};

		template<class T, class U>
		struct HasAdditiveOperation_t : std::conjunction<HasAddition_t<T, U>, HasSubtraction_t<T, U>> {};

		template<class T, class U>
		struct HasMultiplicativeOperation_t : std::conjunction<HasMultiplication_t<T, U>, HasDivision_t<T, U>> {};

		template<class T, class U>
		struct HasArithmeticOperation_t : std::conjunction<HasUnaryOperation_t<T>, HasAdditiveOperation_t<T, U>, HasMultiplicativeOperation_t<T, U>> {};

		template<class T, class U>
		struct HasBitOperation_t : std::conjunction<HasArithmeticNot_t<T>, HasArithmeticOr_t<T, U>, HasArithmeticAnd_t<T, U>, HasArithmeticXor_t<T, U>, HasLShift_t<T, U>, HasRShift_t<T, U>> {};

		template<class, class, class = std::void_t<>>
		struct HasSaturateAdd_t : std::false_type {};
		template<class T, class U>
		struct HasSaturateAdd_t<T, U, std::void_t< decltype( std::declval<T&>().SaturateAdd(std::declval<U&>()) ) > > : std::true_type {};

		template<class, class, class = std::void_t<>>
		struct HasSaturateSub_t : std::false_type {};
		template<class T, class U>
		struct HasSaturateSub_t<T, U, std::void_t< decltype( std::declval<T&>().SaturateSub(std::declval<U&>()) ) > > : std::true_type {};

		template<class, class, class = std::void_t<>>
		struct HasSaturateMultiple_t : std::false_type {};
		template<class T, class U>
		struct HasSaturateMultiple_t<T, U, std::void_t< decltype( std::declval<T&>().SaturateMultiple(std::declval<U&>()) ) > > : std::true_type {};

		template<class, class, class = std::void_t<>>
		struct HasSaturateDivide_t : std::false_type {};
		template<class T, class U>
		struct HasSaturateDivide_t<T, U, std::void_t< decltype( std::declval<T&>().SaturateDivide(std::declval<U&>()) ) > > : std::true_type {};

		template<class T, class U>
		struct HasSaturateOperation_t : std::conjunction<HasSaturateAdd_t<T, U>, HasSaturateSub_t<T, U>, HasSaturateMultiple_t<T, U>, HasSaturateDivide_t<T, U>> {};

		template<class, class, class = std::void_t<>>
		struct HasCheckedAdd_t : std::false_type {};
		template<class T, class U>
		struct HasCheckedAdd_t<T, U, std::void_t< decltype( std::declval<T&>().CheckedAdd(std::declval<U&>()) ) > > : std::true_type {};

		template<class, class, class = std::void_t<>>
		struct HasCheckedSub_t : std::false_type {};
		template<class T, class U>
		struct HasCheckedSub_t<T, U, std::void_t< decltype( std::declval<T&>().CheckedSub(std::declval<U&>()) ) > > : std::true_type {};

		template<class, class, class = std::void_t<>>
		struct HasCheckedMultiple_t : std::false_type {};
		template<class T, class U>
		struct HasCheckedMultiple_t<T, U, std::void_t< decltype( std::declval<T&>().CheckedMultiple(std::declval<U&>()) ) > > : std::true_type {};

		template<class, class, class = std::void_t<>>
		struct HasCheckedDivide_t : std::false_type {};
		template<class T, class U>
		struct HasCheckedDivide_t<T, U, std::void_t< decltype( std::declval<T&>().CheckedDivide(std::declval<U&>()) ) > > : std::true_type {};

		template<class T, class U>
		struct HasCheckedOperation_t : std::conjunction<HasCheckedAdd_t<T, U>, HasCheckedSub_t<T, U>, HasCheckedMultiple_t<T, U>, HasCheckedDivide_t<T, U>> {};

		template<class, class, class = std::void_t<>>
		struct HasComparamentLarger : std::false_type {};
		template<class T, class U>
		struct HasComparamentLarger<T, U, std::void_t< decltype( std::declval<T&>() > std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() > std::declval<U&>() ), bool> {};

		template<class, class, class = std::void_t<>>
		struct HasComparamentSmaller : std::false_type {};
		template<class T, class U>
		struct HasComparamentSmaller<T, U, std::void_t< decltype( std::declval<T&>() < std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() < std::declval<U&>() ), bool> {};

		template<class, class, class = std::void_t<>>
		struct HasComparamentLeast : std::false_type {};
		template<class T, class U>
		struct HasComparamentLeast<T, U, std::void_t< decltype( std::declval<T&>() >= std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() >= std::declval<U&>() ), bool> {};

		template<class, class, class = std::void_t<>>
		struct HasComparamentMost : std::false_type {};
		template<class T, class U>
		struct HasComparamentMost<T, U, std::void_t< decltype( std::declval<T&>() <= std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() <= std::declval<U&>() ), bool> {};

		template<class T, class U>
		struct Comparable_t : std::conjunction< HasComparamentLarger<T, U>, HasComparamentSmaller<T, U>, HasComparamentLeast<T, U>, HasComparamentMost<T, U> > {};

		template<class, class, class = std::void_t<>>
		struct HasEqual : std::false_type {};
		template<class T, class U>
		struct HasEqual<T, U, std::void_t< decltype( std::declval<T&>() == std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() == std::declval<U&>() ), bool> {};

		template<class, class, class = std::void_t<>>
		struct HasNotEqual : std::false_type {};
		template<class T, class U>
		struct HasNotEqual<T, U, std::void_t< decltype( std::declval<T&>() != std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() != std::declval<U&>() ), bool> {};

		template<class T, class U>
		struct Equatable_t : std::conjunction< HasEqual<T, U>, HasNotEqual<T, U> > {};

	public:
		///	単項算術演算子を持つ型を識別します。
		template<class T> inline constexpr static bool HasUnaryOperation = HasUnaryOperation_t<T>::value;
		///	加法演算子を持つ型を識別します。
		template<class T, class U = T> inline constexpr static bool HasAdditiveOperation = HasAdditiveOperation_t<T, U>::value;
		///	乗法演算子を持つ型を識別します。
		template<class T, class U = T> inline constexpr static bool HasMultiplicativeOperation = HasMultiplicativeOperation_t<T, U>::value;
		///	基本的な算術演算を持つ型を識別します。
		template<class T, class U = T> inline constexpr static bool HasArithmeticOperation = HasArithmeticOperation_t<T, U>::value;
		///	基本的なビット演算を持つ型を識別します。
		template<class T, class U = T> inline constexpr static bool HasBitOperation = HasBitOperation_t<T, U>::value;
		///	計算結果が飽和する四則演算を持つ型を識別します。
		template<class T, class U = T> inline constexpr static bool HasSaturateOperation = HasSaturateOperation_t<T, U>::value;
		///	計算結果の値域チェックが行われる四則演算を持つ型を識別します。
		template<class T, class U = T> inline constexpr static bool HasCheckedOperation = HasCheckedOperation_t<T, U>::value;
		///	指定された型のオブジェクトとの比較が可能な型を識別します。
		template<class T, class U = T> inline constexpr static bool Comparable = Comparable_t<T, U>::value;
		///	指定された型のオブジェクトとの比較が可能な型を識別します。
		template<class T, class U = T> inline constexpr static bool Equatable = Equatable_t<T, U>::value;
	};

	///	指定された型の有効なビット幅を識別するための機能を提供します。
	template<class T> struct BitWidth_t : std::integral_constant<size_t, 8U * sizeof(T)>
	{
		static_assert(std::is_integral_v<T>, "ビット幅の計数は整数型、boolなどの固定幅のビットシーケンスでのみ有効です。");
	};
	template<> struct BitWidth_t<bool> : std::integral_constant<size_t, 1U> {};
	template<std::size_t N> struct BitWidth_t<std::bitset<N>> : std::integral_constant<size_t, N> {};
	///	指定された型の有効なビット幅を識別します。
	template<class T> inline constexpr size_t BitWidth = BitWidth_t<T>::value;
}
#endif // __stationaryorbit_core_traits__