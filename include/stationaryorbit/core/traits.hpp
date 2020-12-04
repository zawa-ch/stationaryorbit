//	stationaryorbit/core/traits
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

		///	代入演算子=の実装を識別します。
		template<class, class, class, class = std::void_t<>>
		struct HasSubstitution_t : std::false_type {};
		template<class T, class U, class R>
		struct HasSubstitution_t<T, U, R, std::void_t< decltype( std::declval<T&>() = std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() = std::declval<U&>() ), R> {};

		///	代入演算子+=の実装を識別します。
		template<class, class, class, class = std::void_t<>>
		struct HasAddSubstitution_t : std::false_type {};
		template<class T, class U, class R>
		struct HasAddSubstitution_t<T, U, R, std::void_t< decltype( std::declval<T&>() += std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() += std::declval<U&>() ), R> {};

		///	代入演算子-=の実装を識別します。
		template<class, class, class, class = std::void_t<>>
		struct HasSubtractSubstitution_t : std::false_type {};
		template<class T, class U, class R>
		struct HasSubtractSubstitution_t<T, U, R, std::void_t< decltype( std::declval<T&>() -= std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() -= std::declval<U&>() ), R> {};

		///	代入演算子*=の実装を識別します。
		template<class, class, class, class = std::void_t<>>
		struct HasMultipleSubstitution_t : std::false_type {};
		template<class T, class U, class R>
		struct HasMultipleSubstitution_t<T, U, R, std::void_t< decltype( std::declval<T&>() *= std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() *= std::declval<U&>() ), R> {};

		///	代入演算子/=の実装を識別します。
		template<class, class, class, class = std::void_t<>>
		struct HasDivideSubstitution_t : std::false_type {};
		template<class T, class U, class R>
		struct HasDivideSubstitution_t<T, U, R, std::void_t< decltype( std::declval<T&>() /= std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() /= std::declval<U&>() ), R> {};

		///	代入演算子%=の実装を識別します。
		template<class, class, class, class = std::void_t<>>
		struct HasModulateSubstitution_t : std::false_type {};
		template<class T, class U, class R>
		struct HasModulateSubstitution_t<T, U, R, std::void_t< decltype( std::declval<T&>() %= std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() %= std::declval<U&>() ), R> {};

		///	代入演算子&=の実装を識別します。
		template<class, class, class, class = std::void_t<>>
		struct HasArithmeticAndSubstitution_t : std::false_type {};
		template<class T, class U, class R>
		struct HasArithmeticAndSubstitution_t<T, U, R, std::void_t< decltype( std::declval<T&>() &= std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() &= std::declval<U&>() ), R> {};

		///	代入演算子|=の実装を識別します。
		template<class, class, class, class = std::void_t<>>
		struct HasArithmeticOrSubstitution_t : std::false_type {};
		template<class T, class U, class R>
		struct HasArithmeticOrSubstitution_t<T, U, R, std::void_t< decltype( std::declval<T&>() |= std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() |= std::declval<U&>() ), R> {};

		///	代入演算子^=の実装を識別します。
		template<class, class, class, class = std::void_t<>>
		struct HasArithmeticXorSubstitution_t : std::false_type {};
		template<class T, class U, class R>
		struct HasArithmeticXorSubstitution_t<T, U, R, std::void_t< decltype( std::declval<T&>() ^= std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() ^= std::declval<U&>() ), R> {};

		///	代入演算子<<=の実装を識別します。
		template<class, class, class, class = std::void_t<>>
		struct HasBitLshiftSubstitution_t : std::false_type {};
		template<class T, class U, class R>
		struct HasBitLshiftSubstitution_t<T, U, R, std::void_t< decltype( std::declval<T&>() <<= std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() <<= std::declval<U&>() ),R&> {};

		///	代入演算子>>=の実装を識別します。
		template<class, class, class, class = std::void_t<>>
		struct HasBitRshiftSubstitution_t : std::false_type {};
		template<class T, class U, class R>
		struct HasBitRshiftSubstitution_t<T, U, R, std::void_t< decltype( std::declval<T&>() >>= std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() >>= std::declval<U&>() ),R&> {};

		///	前置インクリメント演算子++の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasPreIncrement_t : std::false_type {};
		template<class T, class R>
		struct HasPreIncrement_t<T, R, std::void_t< decltype( ++std::declval<T&>() ) > >
			: std::is_convertible< decltype( ++std::declval<T&>() ), R> {};

		///	前置デクリメント演算子--の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasPreDecrement_t : std::false_type {};
		template<class T, class R>
		struct HasPreDecrement_t<T, R, std::void_t< decltype( --std::declval<T&>() ) > >
			: std::is_convertible< decltype( --std::declval<T&>() ), R> {};

		///	後置インクリメント演算子++の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasPostIncrement_t : std::false_type {};
		template<class T, class R>
		struct HasPostIncrement_t<T, R, std::void_t< decltype( std::declval<T&>()++ ) > >
			: std::is_convertible< decltype( std::declval<T&>()++ ), R> {};

		///	後置デクリメント演算子--の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasPostDecrement_t : std::false_type {};
		template<class T, class R>
		struct HasPostDecrement_t<T, R, std::void_t< decltype( std::declval<T&>()-- ) > >
			: std::is_convertible< decltype( std::declval<T&>()-- ), R> {};

		///	単項算術演算子+の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasPromotion_t : std::false_type {};
		template<class T, class R>
		struct HasPromotion_t<T, R, std::void_t< decltype( +std::declval<T&>() ) > >
			: std::is_convertible< decltype( +std::declval<T&>() ), R> {};

		///	単項算術演算子-の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasInverse_t : std::false_type {};
		template<class T, class R>
		struct HasInverse_t<T, R, std::void_t< decltype( -std::declval<T&>() ) > >
			: std::is_convertible< decltype( -std::declval<T&>() ), R> {};

		///	二項算術演算子+の実装を識別します。
		template<class, class, class, class = std::void_t<>>
		struct HasAddition_t : std::false_type {};
		template<class T, class U, class R>
		struct HasAddition_t<T, U, R, std::void_t< decltype( std::declval<T&>() + std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() + std::declval<U&>() ), R> {};

		///	二項算術演算子-の実装を識別します。
		template<class, class, class, class = std::void_t<>>
		struct HasSubtraction_t : std::false_type {};
		template<class T, class U, class R>
		struct HasSubtraction_t<T, U, R, std::void_t< decltype( std::declval<T&>() - std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() - std::declval<U&>() ), R> {};

		///	二項算術演算子*の実装を識別します。
		template<class, class, class, class = std::void_t<>>
		struct HasMultiplication_t : std::false_type {};
		template<class T, class U, class R>
		struct HasMultiplication_t<T, U, R, std::void_t< decltype( std::declval<T&>() * std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() * std::declval<U&>() ), R> {};

		///	二項算術演算子/の実装を識別します。
		template<class, class, class, class = std::void_t<>>
		struct HasDivision_t : std::false_type {};
		template<class T, class U, class R>
		struct HasDivision_t<T, U, R, std::void_t< decltype( std::declval<T&>() / std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() / std::declval<U&>() ), R> {};

		///	二項算術演算子%の実装を識別します。
		template<class, class, class, class = std::void_t<>>
		struct HasModulation_t : std::false_type {};
		template<class T, class U, class R>
		struct HasModulation_t<T, U, R, std::void_t< decltype( std::declval<T&>() % std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() % std::declval<U&>() ), R> {};

		///	二項算術演算子~の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasArithmeticNot_t : std::false_type {};
		template<class T, class R>
		struct HasArithmeticNot_t<T, R, std::void_t< decltype( ~std::declval<T&>() ) > >
			: std::is_convertible< decltype( ~std::declval<T&>() ), R> {};

		///	二項算術演算子|の実装を識別します。
		template<class, class, class, class = std::void_t<>>
		struct HasArithmeticOr_t : std::false_type {};
		template<class T, class U, class R>
		struct HasArithmeticOr_t<T, U, R, std::void_t< decltype( std::declval<T&>() | std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() | std::declval<U&>() ), R> {};

		///	二項算術演算子&の実装を識別します。
		template<class, class, class, class = std::void_t<>>
		struct HasArithmeticAnd_t : std::false_type {};
		template<class T, class U, class R>
		struct HasArithmeticAnd_t<T, U, R, std::void_t< decltype( std::declval<T&>() & std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() & std::declval<U&>() ), R> {};

		///	二項算術演算子^の実装を識別します。
		template<class, class, class, class = std::void_t<>>
		struct HasArithmeticXor_t : std::false_type {};
		template<class T, class U, class R>
		struct HasArithmeticXor_t<T, U, R, std::void_t< decltype( std::declval<T&>() ^ std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() ^ std::declval<U&>() ), R> {};

		///	二項算術演算子<<の実装を識別します。
		template<class, class, class, class = std::void_t<>>
		struct HasLShift_t : std::false_type {};
		template<class T, class U, class R>
		struct HasLShift_t<T, U, R, std::void_t< decltype( std::declval<T&>() << std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() << std::declval<U&>() ), R> {};

		///	二項算術演算子>>の実装を識別します。
		template<class, class, class, class = std::void_t<>>
		struct HasRShift_t : std::false_type {};
		template<class T, class U, class R>
		struct HasRShift_t<T, U, R, std::void_t< decltype( std::declval<T&>() >> std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() >> std::declval<U&>() ), R> {};

		///	単項論理演算子!の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasLogicalNot_t : std::false_type {};
		template<class T, class R>
		struct HasLogicalNot_t<T, R, std::void_t< decltype( !std::declval<T&>() ) > >
			: std::is_convertible< decltype( !std::declval<T&>() ), R> {};

		///	二項論理演算子&&の実装を識別します。
		template<class, class, class, class = std::void_t<>>
		struct HasLogicalAnd_t : std::false_type {};
		template<class T, class U, class R>
		struct HasLogicalAnd_t<T, U, R, std::void_t< decltype( std::declval<T&>() && std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() && std::declval<U&>() ), R> {};

		///	二項論理演算子||の実装を識別します。
		template<class, class, class, class = std::void_t<>>
		struct HasLogicalOr_t : std::false_type {};
		template<class T, class U, class R>
		struct HasLogicalOr_t<T, U, R, std::void_t< decltype( std::declval<T&>() || std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() || std::declval<U&>() ), R> {};

		///	比較演算子==の実装を識別します。
		template<class, class, class, class = std::void_t<>>
		struct HasEqual_t : std::false_type {};
		template<class T, class U, class R>
		struct HasEqual_t<T, U, R, std::void_t< decltype( std::declval<T&>() == std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() == std::declval<U&>() ), R> {};

		///	比較演算子!=の実装を識別します。
		template<class, class, class, class = std::void_t<>>
		struct HasNotEqual_t : std::false_type {};
		template<class T, class U, class R>
		struct HasNotEqual_t<T, U, R, std::void_t< decltype( std::declval<T&>() != std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() != std::declval<U&>() ), R> {};

		///	比較演算子>の実装を識別します。
		template<class, class, class, class = std::void_t<>>
		struct HasComparamentLarger_t : std::false_type {};
		template<class T, class U, class R>
		struct HasComparamentLarger_t<T, U, R, std::void_t< decltype( std::declval<T&>() > std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() > std::declval<U&>() ), R> {};

		///	比較演算子<の実装を識別します。
		template<class, class, class, class = std::void_t<>>
		struct HasComparamentSmaller_t : std::false_type {};
		template<class T, class U, class R>
		struct HasComparamentSmaller_t<T, U, R, std::void_t< decltype( std::declval<T&>() < std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() < std::declval<U&>() ), R> {};

		///	比較演算子>=の実装を識別します。
		template<class, class, class, class = std::void_t<>>
		struct HasComparamentLeast_t : std::false_type {};
		template<class T, class U, class R>
		struct HasComparamentLeast_t<T, U, R, std::void_t< decltype( std::declval<T&>() >= std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() >= std::declval<U&>() ), R> {};

		///	比較演算子<=の実装を識別します。
		template<class, class, class, class = std::void_t<>>
		struct HasComparamentMost_t : std::false_type {};
		template<class T, class U, class R>
		struct HasComparamentMost_t<T, U, R, std::void_t< decltype( std::declval<T&>() <= std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() <= std::declval<U&>() ), R> {};

		///	添字演算子[]の実装を識別します。
		template<class, class, class, class = std::void_t<>>
		struct HasSubScript_t : std::false_type {};
		template<class T, class U, class R>
		struct HasSubScript_t<T, U, R, std::void_t< decltype( std::declval<T&>() [std::declval<U&>()] ) > >
			: std::is_convertible< decltype( std::declval<T&>() [std::declval<U&>()] ), R> {};

		///	間接参照演算子*の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasDereference_t : std::false_type {};
		template<class T, class R>
		struct HasDereference_t<T, R, std::void_t< decltype( *std::declval<T&>() ) > >
			: std::is_convertible< decltype( *std::declval<T&>() ), R> {};

		///	アドレス取得演算子&の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasReference_t : std::false_type {};
		template<class T, class R>
		struct HasReference_t<T, R, std::void_t< decltype( &std::declval<T&>() ) > >
			: std::is_convertible< decltype( &std::declval<T&>() ), R> {};

		///	アロー演算子->のオーバーロード実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasArrowOverload_t : std::false_type {};
		template<class T, class R>
		struct HasArrowOverload_t<T, R, std::void_t< decltype( std::declval<T&>().operator->() ) > >
			: std::is_convertible< decltype( std::declval<T&>().operator->() ), R> {};

		///	アロー間接参照演算子->*のオーバーロード実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasArrowDereferenceOverload_t : std::false_type {};
		template<class T, class R>
		struct HasArrowDereferenceOverload_t<T, R, std::void_t< decltype( std::declval<T&>().operator->*() ) > >
			: std::is_convertible< decltype( std::declval<T&>().operator->*() ), R> {};

		///	コンマ演算子,の実装を識別します。
		template<class, class, class, class = std::void_t<>>
		struct HasComma_t : std::false_type {};
		template<class T, class U, class R>
		struct HasComma_t<T, U, R, std::void_t< decltype( std::declval<T&>() , std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() , std::declval<U&>() ), R> {};

		template<class T, class U>
		struct Equatable_t : std::conjunction< HasEqual_t<T, U, bool>, HasNotEqual_t<T, U, bool> > {};

		template<class T, class U>
		struct Comparable_t : std::conjunction< HasComparamentLarger_t<T, U, bool>, HasComparamentSmaller_t<T, U, bool>, HasComparamentLeast_t<T, U, bool>, HasComparamentMost_t<T, U, bool> > {};

		template<class T, class R>
		struct HasUnaryOperation_t : std::conjunction<HasPromotion_t<T, R>, HasInverse_t<T, R>> {};

		template<class T, class U, class R>
		struct HasAdditiveOperation_t : std::conjunction<HasAddition_t<T, U, R>, HasSubtraction_t<T, U, R>> {};

		template<class T, class U, class R>
		struct HasMultiplicativeOperation_t : std::conjunction<HasMultiplication_t<T, U, R>, HasDivision_t<T, U, R>> {};

		template<class T>
		struct HasArithmeticOperation_t : std::conjunction<HasUnaryOperation_t<T, T>, HasAdditiveOperation_t<T, T, T>, HasMultiplicativeOperation_t<T, T, T>> {};

		template<class T, class U>
		struct HasBitOperation_t : std::conjunction<HasArithmeticNot_t<T, T>, HasArithmeticOr_t<T, T, T>, HasArithmeticAnd_t<T, T, T>, HasArithmeticXor_t<T, T, T>, HasLShift_t<T, U, T>, HasRShift_t<T, U, T>> {};

		template<class T>
		struct IsSequencialOrder_t : std::conjunction<HasPreIncrement_t<T, T&>, HasPostIncrement_t<T, T>> {};

		template<class T>
		struct IsBidirectionalOrder_t : std::conjunction<IsSequencialOrder_t<T>, HasPreDecrement_t<T, T&>, HasPostDecrement_t<T, T>> {};

		template<class T, class N>
		struct IsLinearOrder_t : std::conjunction<IsBidirectionalOrder_t<T>, HasAdditiveOperation_t<T, N, T>, HasAddSubstitution_t<T, N, T&>, HasSubtractSubstitution_t<T, N, T&>> {};

		template<class T>
		struct IsValueType_t :
			std::conjunction
			<
				std::is_default_constructible<T>,
				std::is_trivially_default_constructible<T>,
				std::is_nothrow_default_constructible<T>,
				std::is_destructible<T>,
				std::is_nothrow_destructible<T>,
				std::is_trivially_destructible<T>,
				std::is_copy_constructible<T>,
				std::is_nothrow_copy_constructible<T>,
				std::is_trivially_copy_constructible<T>,
				std::is_move_constructible<T>,
				std::is_nothrow_move_constructible<T>,
				std::is_trivially_move_constructible<T>,
				std::is_copy_assignable<T>,
				std::is_nothrow_copy_assignable<T>,
				std::is_trivially_copy_assignable<T>,
				std::is_move_assignable<T>,
				std::is_nothrow_move_assignable<T>,
				std::is_trivially_move_assignable<T>,
				Equatable_t<T, T>
			>
		{};

		template<class T>
		struct IsBitSequence_t : std::conjunction< IsValueType_t<T>, HasBitOperation_t<T, int> > {};

		template<class T>
		struct IsNumeralType_t : std::conjunction< IsValueType_t<T>, HasArithmeticOperation_t<T>, Comparable_t<T, T>, std::bool_constant<std::numeric_limits<T>::is_specialized> > {};

		template<class T>
		struct IsIntegerType_t : std::conjunction< IsNumeralType_t<T>, HasModulation_t<T, T, T>, HasBitOperation_t<T, T>, IsBidirectionalOrder_t<T> > {};

		template<class, class, class = std::void_t<>>
		struct HasSaturateAddition_t : std::false_type {};
		template<class T, class U>
		struct HasSaturateAddition_t<T, U, std::void_t< decltype( std::declval<T&>().SaturateAdd(std::declval<U&>()) ) > > : std::true_type {};

		template<class, class, class = std::void_t<>>
		struct HasSaturateSubtraction_t : std::false_type {};
		template<class T, class U>
		struct HasSaturateSubtraction_t<T, U, std::void_t< decltype( std::declval<T&>().SaturateSubtract(std::declval<U&>()) ) > > : std::true_type {};

		template<class, class, class = std::void_t<>>
		struct HasSaturateMultiplication_t : std::false_type {};
		template<class T, class U>
		struct HasSaturateMultiplication_t<T, U, std::void_t< decltype( std::declval<T&>().SaturateMultiply(std::declval<U&>()) ) > > : std::true_type {};

		template<class, class, class = std::void_t<>>
		struct HasSaturateDivision_t : std::false_type {};
		template<class T, class U>
		struct HasSaturateDivision_t<T, U, std::void_t< decltype( std::declval<T&>().SaturateDivide(std::declval<U&>()) ) > > : std::true_type {};

		template<class T, class U>
		struct HasSaturateOperation_t : std::conjunction<HasSaturateAddition_t<T, U>, HasSaturateSubtraction_t<T, U>, HasSaturateMultiplication_t<T, U>, HasSaturateDivision_t<T, U>> {};

		template<class, class, class = std::void_t<>>
		struct HasCheckedAddition_t : std::false_type {};
		template<class T, class U>
		struct HasCheckedAddition_t<T, U, std::void_t< decltype( std::declval<T&>().CheckedAdd(std::declval<U&>()) ) > > : std::true_type {};

		template<class, class, class = std::void_t<>>
		struct HasCheckedSubtraction_t : std::false_type {};
		template<class T, class U>
		struct HasCheckedSubtraction_t<T, U, std::void_t< decltype( std::declval<T&>().CheckedSubtract(std::declval<U&>()) ) > > : std::true_type {};

		template<class, class, class = std::void_t<>>
		struct HasCheckedMultiplication_t : std::false_type {};
		template<class T, class U>
		struct HasCheckedMultiplication_t<T, U, std::void_t< decltype( std::declval<T&>().CheckedMultiply(std::declval<U&>()) ) > > : std::true_type {};

		template<class, class, class = std::void_t<>>
		struct HasCheckedDivision_t : std::false_type {};
		template<class T, class U>
		struct HasCheckedDivision_t<T, U, std::void_t< decltype( std::declval<T&>().CheckedDivide(std::declval<U&>()) ) > > : std::true_type {};

		template<class T, class U>
		struct HasCheckedOperation_t : std::conjunction<HasCheckedAddition_t<T, U>, HasCheckedSubtraction_t<T, U>, HasCheckedMultiplication_t<T, U>, HasCheckedDivision_t<T, U>> {};

		template<class, class = std::void_t<>>
		struct IsStdLegacyIterator_t : std::false_type {};
		template<class It>
		struct IsStdLegacyIterator_t
		<
			It,
			std::void_t
			<
				typename std::iterator_traits<It>::value_type,
				typename std::iterator_traits<It>::difference_type,
				typename std::iterator_traits<It>::reference,
				typename std::iterator_traits<It>::pointer,
				typename std::iterator_traits<It>::iterator_category,
				decltype( *std::declval<It&>() )
			>
		>
			: std::conjunction
			<
				std::is_copy_constructible<It>,
				std::is_copy_assignable<It>,
				std::is_destructible<It>,
				std::is_swappable<It&>,
				HasPreIncrement_t<It, It&>
			>
		{};

		template<class, class = std::void_t<>>
		struct IsStdLegacyInputIterator_t : std::false_type {};
		template<class It>
		struct IsStdLegacyInputIterator_t
		<
			It,
			std::void_t
			<
				typename std::iterator_traits<It>::value_type,
				typename std::iterator_traits<It>::reference,
				decltype( *std::declval<It&>()++ ),
				decltype( (void)std::declval<It&>()++ )
			>
		>
			: std::conjunction
			<
				IsStdLegacyIterator_t<It>,
				Equatable_t<It, It>,
				HasDereference_t<It, typename std::iterator_traits<It>::value_type>,
				HasPreIncrement_t<It, It&>,
				std::is_convertible<decltype( *std::declval<It&>()++ ), typename std::iterator_traits<It>::value_type>
			>
		{};

		template<class, class = std::void_t<>>
		struct IsStdLegacyForwardIterator_t : std::false_type {};
		template<class It>
		struct IsStdLegacyForwardIterator_t<It, std::void_t< typename std::iterator_traits<It>::reference, decltype( *std::declval<It&>()++ ) >>
			: std::conjunction
			<
				IsStdLegacyInputIterator_t<It>,
				HasPostIncrement_t<It, It>,
				std::is_same<decltype( *std::declval<It&>()++ ), typename std::iterator_traits<It>::reference>
			>
		{};

		template<class, class = std::void_t<>>
		struct IsStdLegacyBidirectionalIterator_t : std::false_type {};
		template<class It>
		struct IsStdLegacyBidirectionalIterator_t<It, std::void_t< typename std::iterator_traits<It>::reference, decltype( *std::declval<It&>()-- ) >>
			: std::conjunction
			<
				IsStdLegacyForwardIterator_t<It>,
				HasPreDecrement_t<It, It&>,
				HasPostDecrement_t<It, const It&>,
				std::is_same<decltype( *std::declval<It&>()-- ), typename std::iterator_traits<It>::reference>
			>
		{};

		template<class, class = std::void_t<>>
		struct IsStdLegacyRandomAccessIterator_t : std::false_type {};
		template<class It>
		struct IsStdLegacyRandomAccessIterator_t<It, std::void_t< typename std::iterator_traits<It>::value_type, typename std::iterator_traits<It>::difference_type, typename std::iterator_traits<It>::reference, decltype( *std::declval<It&>()-- ) >>
			: std::conjunction
			<
				IsStdLegacyBidirectionalIterator_t<It>,
				HasAddSubstitution_t<It, typename std::iterator_traits<It>::difference_type, It&>,
				HasSubtractSubstitution_t<It, typename std::iterator_traits<It>::difference_type, It&>,
				HasAdditiveOperation_t<It, typename std::iterator_traits<It>::difference_type, It>,
				Comparable_t<It, It>,
				HasSubScript_t<It, typename std::iterator_traits<It>::difference_type, typename std::iterator_traits<It>::reference>
			>
		{};

		template<class, class, class = std::void_t<>>
		struct IsStdLegacyOutputIterator_t : std::false_type {};
		template<class It, class O>
		struct IsStdLegacyOutputIterator_t < It, O, std::void_t < decltype( *std::declval<It&>() = std::declval<O&>() ), decltype( *std::declval<It&>()++ = std::declval<O&>() ) > >
			: std::conjunction< IsStdLegacyIterator_t<It>, HasPreIncrement_t<It, It&>, HasPostIncrement_t<It, It> > {};

	public:
		///	代入演算子=の実装を識別します。
		template<class T, class U = T, class R = T&> inline constexpr static bool HasSubstitution = HasSubstitution_t<T, U, R>::value;
		///	代入演算子+=の実装を識別します。
		template<class T, class U = T, class R = T&> inline constexpr static bool HasAddSubstitution = HasAddSubstitution_t<T, U, R>::value;
		///	代入演算子-=の実装を識別します。
		template<class T, class U = T, class R = T&> inline constexpr static bool HasSubtractSubstitution = HasSubtractSubstitution_t<T, U, R>::value;
		///	代入演算子*=の実装を識別します。
		template<class T, class U = T, class R = T&> inline constexpr static bool HasMultipleSubstitution = HasMultipleSubstitution_t<T, U, R>::value;
		///	代入演算子/=の実装を識別します。
		template<class T, class U = T, class R = T&> inline constexpr static bool HasDivideSubstitution = HasDivideSubstitution_t<T, U, R>::value;
		///	代入演算子%=の実装を識別します。
		template<class T, class U = T, class R = T&> inline constexpr static bool HasModulateSubstitution = HasModulateSubstitution_t<T, U, R>::value;
		///	代入演算子&=の実装を識別します。
		template<class T, class U = T, class R = T&> inline constexpr static bool HasArithmeticAndSubstitution = HasArithmeticAndSubstitution_t<T, U, R>::value;
		///	代入演算子|=の実装を識別します。
		template<class T, class U = T, class R = T&> inline constexpr static bool HasArithmeticOrSubstitution = HasArithmeticOrSubstitution_t<T, U, R>::value;
		///	代入演算子^=の実装を識別します。
		template<class T, class U = T, class R = T&> inline constexpr static bool HasArithmeticXorSubstitution = HasArithmeticXorSubstitution_t<T, U, R>::value;
		///	代入演算子<<=の実装を識別します。
		template<class T, class U = T, class R = T&> inline constexpr static bool HasBitLshiftSubstitution = HasBitLshiftSubstitution_t<T, U, R>::value;
		///	代入演算子>>=の実装を識別します。
		template<class T, class U = T, class R = T&> inline constexpr static bool HasBitRshiftSubstitution = HasBitRshiftSubstitution_t<T, U, R>::value;
		///	前置インクリメント演算子++の実装を識別します。
		template<class T, class R = T&> inline constexpr static bool HasPreIncrement = HasPreIncrement_t<T, R>::value;
		///	前置デクリメント演算子--の実装を識別します。
		template<class T, class R = T&> inline constexpr static bool HasPreDecrement = HasPreDecrement_t<T, R>::value;
		///	後置インクリメント演算子++の実装を識別します。
		template<class T, class R = T> inline constexpr static bool HasPostIncrement = HasPostIncrement_t<T, R>::value;
		///	後置デクリメント演算子--の実装を識別します。
		template<class T, class R = T> inline constexpr static bool HasPostDecrement = HasPostDecrement_t<T, R>::value;
		///	単項算術演算子+の実装を識別します。
		template<class T, class R = T> inline constexpr static bool HasOperatorPromotion = HasPromotion_t<T, R>::value;
		///	単項算術演算子-の実装を識別します。
		template<class T, class R = T> inline constexpr static bool HasOperatorInverse = HasInverse_t<T, R>::value;
		///	二項算術演算子+の実装を識別します。
		template<class T, class U = T, class R = T> inline constexpr static bool HasOperatorAddition = HasAddition_t<T, U, R>::value;
		///	二項算術演算子-の実装を識別します。
		template<class T, class U = T, class R = T> inline constexpr static bool HasOperatorSubtraction = HasSubtraction_t<T, U, R>::value;
		///	二項算術演算子*の実装を識別します。
		template<class T, class U = T, class R = T> inline constexpr static bool HasOperatorMultiplication = HasMultiplication_t<T, U, R>::value;
		///	二項算術演算子/の実装を識別します。
		template<class T, class U = T, class R = T> inline constexpr static bool HasOperatorDivision = HasDivision_t<T, U, R>::value;
		///	二項算術演算子%の実装を識別します。
		template<class T, class U = T, class R = T> inline constexpr static bool HasOperatorModulation = HasModulation_t<T, U, R>::value;
		///	二項算術演算子~の実装を識別します。
		template<class T, class R = T> inline constexpr static bool HasOperatorArithmeticNot = HasArithmeticNot_t<T, R>::value;
		///	二項算術演算子|の実装を識別します。
		template<class T, class U = T, class R = T> inline constexpr static bool HasOperatorArithmeticOr = HasArithmeticOr_t<T, U, R>::value;
		///	二項算術演算子&の実装を識別します。
		template<class T, class U = T, class R = T> inline constexpr static bool HasOperatorArithmeticAnd = HasArithmeticAnd_t<T, U, R>::value;
		///	二項算術演算子^の実装を識別します。
		template<class T, class U = T, class R = T> inline constexpr static bool HasOperatorArithmeticXor = HasArithmeticXor_t<T, U, R>::value;
		///	二項算術演算子<<の実装を識別します。
		template<class T, class U = T, class R = T> inline constexpr static bool HasOperatorLShift = HasLShift_t<T, U, R>::value;
		///	二項算術演算子>>の実装を識別します。
		template<class T, class U = T, class R = T> inline constexpr static bool HasOperatorRShift = HasRShift_t<T, U, R>::value;
		///	単項論理演算子!の実装を識別します。
		template<class T, class R = T> inline constexpr static bool HasLogicalNot = HasLogicalNot_t<T, R>::value;
		///	二項論理演算子&&の実装を識別します。
		template<class T, class U = T, class R = T> inline constexpr static bool HasLogicalAnd = HasLogicalAnd_t<T, U, R>::value;
		///	二項論理演算子||の実装を識別します。
		template<class T, class U = T, class R = T> inline constexpr static bool HasLogicalOr = HasLogicalOr_t<T, U, R>::value;
		///	比較演算子==の実装を識別します。
		template<class T, class U = T, class R = bool> inline constexpr static bool HasOperatorEqual = HasEqual_t<T, U, R>::value;
		///	比較演算子!=の実装を識別します。
		template<class T, class U = T, class R = bool> inline constexpr static bool HasOperatorNotEqual = HasNotEqual_t<T, U, R>::value;
		///	比較演算子>の実装を識別します。
		template<class T, class U = T, class R = bool> inline constexpr static bool HasOperatorComparamentLarger = HasComparamentLarger_t<T, U, R>::value;
		///	比較演算子<の実装を識別します。
		template<class T, class U = T, class R = bool> inline constexpr static bool HasOperatorComparamentSmaller = HasComparamentSmaller_t<T, U, R>::value;
		///	比較演算子>=の実装を識別します。
		template<class T, class U = T, class R = bool> inline constexpr static bool HasOperatorComparamentLeast = HasComparamentLeast_t<T, U, R>::value;
		///	比較演算子<=の実装を識別します。
		template<class T, class U = T, class R = bool> inline constexpr static bool HasOperatorComparamentMost = HasComparamentMost_t<T, U, R>::value;
		///	添字演算子[]の実装を識別します。
		template<class T, class U, class R> inline constexpr static bool HasSubScript = HasSubScript_t<T, U, R>::value;
		///	間接参照演算子*の実装を識別します。
		template<class T, class R> inline constexpr static bool HasDereference = HasDereference_t<T, R>::value;
		///	アドレス取得演算子&の実装を識別します。
		template<class T, class R = T*> inline constexpr static bool HasReference = HasReference_t<T, R>::value;
		///	アロー演算子->のオーバーロード実装を識別します。
		template<class T, class R = T*> inline constexpr static bool HasArrow = HasArrowOverload_t<T, R>::value;
		///	アロー間接参照演算子->*のオーバーロード実装を識別します。
		template<class T, class R> inline constexpr static bool HasArrowDereference = HasArrowDereferenceOverload_t<T, R>::value;
		///	コンマ演算子,の実装を識別します。
		template<class T, class U = T, class R = T> inline constexpr static bool HasComma = HasComma_t<T, U, R>::value;
		///	指定された型のオブジェクトとの等価比較が可能な型を識別します。
		template<class T, class U = T> inline constexpr static bool Equatable = Equatable_t<T, U>::value;
		///	指定された型のオブジェクトとの大小比較が可能な型を識別します。
		template<class T, class U = T> inline constexpr static bool Comparable = Comparable_t<T, U>::value;
		///	単項算術演算子を持つ型を識別します。
		template<class T, class R = T> inline constexpr static bool HasUnaryOperation = HasUnaryOperation_t<T, R>::value;
		///	加法演算子を持つ型を識別します。
		template<class T, class U = T, class R = T> inline constexpr static bool HasAdditiveOperation = HasAdditiveOperation_t<T, U, R>::value;
		///	乗法演算子を持つ型を識別します。
		template<class T, class U = T, class R = T> inline constexpr static bool HasMultiplicativeOperation = HasMultiplicativeOperation_t<T, U, R>::value;
		///	基本的な算術演算を持つ型を識別します。
		template<class T> inline constexpr static bool HasArithmeticOperation = HasArithmeticOperation_t<T>::value;
		///	単方向の順序を持つ値型を識別します。
		template<class T> inline constexpr static bool IsSequencialOrder = IsSequencialOrder_t<T>::value;
		///	双方向の順序を持つ値型を識別します。
		template<class T> inline constexpr static bool IsBidirectionalOrder = IsBidirectionalOrder_t<T>::value;
		///	線形の順序を持つ値型を識別します。
		template<class T, class N = std::make_signed_t<size_t>> inline constexpr static bool IsLinearOrder = IsLinearOrder_t<T, N>::value;
		///	値型を識別します。
		template<class T> inline constexpr static bool IsValueType = IsValueType_t<T>::value;
		///	ビット列型を識別します。
		template<class T> inline constexpr static bool IsBitSequence = IsBitSequence_t<T>::value;
		///	算術型を識別します。
		template<class T> inline constexpr static bool IsNumeralType = IsNumeralType_t<T>::value;
		///	整数型を識別します。
		template<class T> inline constexpr static bool IsIntegerType = IsIntegerType_t<T>::value;
		///	基本的なビット演算を持つ型を識別します。
		template<class T, class U = T> inline constexpr static bool HasBitOperation = HasBitOperation_t<T, U>::value;
		///	計算結果が飽和する四則演算を持つ型を識別します。
		template<class T, class U = T> inline constexpr static bool HasSaturateOperation = HasSaturateOperation_t<T, U>::value;
		///	計算結果の値域チェックが行われる四則演算を持つ型を識別します。
		template<class T, class U = T> inline constexpr static bool HasCheckedOperation = HasCheckedOperation_t<T, U>::value;
		///	名前付き要件:LegacyIteratorを満たす型を識別します。
		template<class It> inline constexpr static bool IsStdLegacyIterator = IsStdLegacyIterator_t<It>::value;
		///	名前付き要件:LegacyInputIteratorを満たす型を識別します。
		template<class It> inline constexpr static bool IsStdLegacyInputIterator = IsStdLegacyInputIterator_t<It>::value;
		///	名前付き要件:LegacyForwardIteratorを満たす型を識別します。
		template<class It> inline constexpr static bool IsStdLegacyForwardIterator = IsStdLegacyForwardIterator_t<It>::value;
		///	名前付き要件:LegacyBidirectionalIteratorを満たす型を識別します。
		template<class It> inline constexpr static bool IsStdLegacyBidirectionalIterator = IsStdLegacyBidirectionalIterator_t<It>::value;
		///	名前付き要件:LegacyRandomAccessIteratorを満たす型を識別します。
		template<class It> inline constexpr static bool IsStdLegacyRandomAccessIterator = IsStdLegacyRandomAccessIterator_t<It>::value;
		///	名前付き要件:LegacyOutputIteratorを満たす型を識別します。
		template<class It, class O> inline constexpr static bool IsStdLegacyOutputIterator = IsStdLegacyOutputIterator_t<It, O>::value;
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