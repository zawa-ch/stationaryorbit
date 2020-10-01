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
		template<class, class, class = std::void_t<>>
		struct HasSubstitution_t : std::false_type {};
		template<class T, class U>
		struct HasSubstitution_t<T, U, std::void_t< decltype( std::declval<T&>() = std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() = std::declval<U&>() ), T&> {};

		///	代入演算子+=の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasAddSubstitution_t : std::false_type {};
		template<class T, class U>
		struct HasAddSubstitution_t<T, U, std::void_t< decltype( std::declval<T&>() += std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() += std::declval<U&>() ), T&> {};

		///	代入演算子-=の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasSubtractSubstitution_t : std::false_type {};
		template<class T, class U>
		struct HasSubtractSubstitution_t<T, U, std::void_t< decltype( std::declval<T&>() -= std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() -= std::declval<U&>() ), T&> {};

		///	代入演算子*=の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasMultipleSubstitution_t : std::false_type {};
		template<class T, class U>
		struct HasMultipleSubstitution_t<T, U, std::void_t< decltype( std::declval<T&>() *= std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() *= std::declval<U&>() ), T&> {};

		///	代入演算子/=の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasDivideSubstitution_t : std::false_type {};
		template<class T, class U>
		struct HasDivideSubstitution_t<T, U, std::void_t< decltype( std::declval<T&>() /= std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() /= std::declval<U&>() ), T&> {};

		///	代入演算子%=の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasModulateSubstitution_t : std::false_type {};
		template<class T, class U>
		struct HasModulateSubstitution_t<T, U, std::void_t< decltype( std::declval<T&>() %= std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() %= std::declval<U&>() ), T&> {};

		///	代入演算子&=の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasArithmeticAndSubstitution_t : std::false_type {};
		template<class T, class U>
		struct HasArithmeticAndSubstitution_t<T, U, std::void_t< decltype( std::declval<T&>() &= std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() &= std::declval<U&>() ), T&> {};

		///	代入演算子|=の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasArithmeticOrSubstitution_t : std::false_type {};
		template<class T, class U>
		struct HasArithmeticOrSubstitution_t<T, U, std::void_t< decltype( std::declval<T&>() |= std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() |= std::declval<U&>() ), T&> {};

		///	代入演算子^=の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasArithmeticXorSubstitution_t : std::false_type {};
		template<class T, class U>
		struct HasArithmeticXorSubstitution_t<T, U, std::void_t< decltype( std::declval<T&>() ^= std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() ^= std::declval<U&>() ), T&> {};

		///	代入演算子<<=の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasBitLshiftSubstitution_t : std::false_type {};
		template<class T, class U>
		struct HasBitLshiftSubstitution_t<T, U, std::void_t< decltype( std::declval<T&>() <<= std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() <<= std::declval<U&>() ), T&> {};

		///	代入演算子>>=の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasBitRshiftSubstitution_t : std::false_type {};
		template<class T, class U>
		struct HasBitRshiftSubstitution_t<T, U, std::void_t< decltype( std::declval<T&>() >>= std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() >>= std::declval<U&>() ), T&> {};

		///	前置インクリメント演算子++の実装を識別します。
		template<class, class = std::void_t<>>
		struct HasPreIncrement_t : std::false_type {};
		template<class T>
		struct HasPreIncrement_t<T, std::void_t< decltype( ++std::declval<T&>() ) > >
			: std::is_convertible< decltype( ++std::declval<T&>() ), T&> {};

		///	前置デクリメント演算子--の実装を識別します。
		template<class, class = std::void_t<>>
		struct HasPreDecrement_t : std::false_type {};
		template<class T>
		struct HasPreDecrement_t<T, std::void_t< decltype( --std::declval<T&>() ) > >
			: std::is_convertible< decltype( --std::declval<T&>() ), T&> {};

		///	後置インクリメント演算子++の実装を識別します。
		template<class, class = std::void_t<>>
		struct HasPostIncrement_t : std::false_type {};
		template<class T>
		struct HasPostIncrement_t<T, std::void_t< decltype( std::declval<T&>()++ ) > >
			: std::is_convertible< decltype( std::declval<T&>()++ ), T> {};

		///	後置デクリメント演算子--の実装を識別します。
		template<class, class = std::void_t<>>
		struct HasPostDecrement_t : std::false_type {};
		template<class T>
		struct HasPostDecrement_t<T, std::void_t< decltype( std::declval<T&>()-- ) > >
			: std::is_convertible< decltype( std::declval<T&>()-- ), T> {};

		///	単項算術演算子+の実装を識別します。
		template<class, class = std::void_t<>>
		struct HasPromotion_t : std::false_type {};
		template<class T>
		struct HasPromotion_t<T, std::void_t< decltype( +std::declval<T&>() ) > >
			: std::is_convertible< decltype( +std::declval<T&>() ), T> {};

		///	単項算術演算子-の実装を識別します。
		template<class, class = std::void_t<>>
		struct HasInverse_t : std::false_type {};
		template<class T>
		struct HasInverse_t<T, std::void_t< decltype( -std::declval<T&>() ) > >
			: std::is_convertible< decltype( -std::declval<T&>() ), T> {};

		///	二項算術演算子+の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasAddition_t : std::false_type {};
		template<class T, class U>
		struct HasAddition_t<T, U, std::void_t< decltype( std::declval<T&>() + std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() + std::declval<U&>() ), T> {};

		///	二項算術演算子-の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasSubtraction_t : std::false_type {};
		template<class T, class U>
		struct HasSubtraction_t<T, U, std::void_t< decltype( std::declval<T&>() - std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() - std::declval<U&>() ), T> {};

		///	二項算術演算子*の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasMultiplication_t : std::false_type {};
		template<class T, class U>
		struct HasMultiplication_t<T, U, std::void_t< decltype( std::declval<T&>() * std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() * std::declval<U&>() ), T> {};

		///	二項算術演算子/の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasDivision_t : std::false_type {};
		template<class T, class U>
		struct HasDivision_t<T, U, std::void_t< decltype( std::declval<T&>() / std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() / std::declval<U&>() ), T> {};

		///	二項算術演算子%の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasModulation_t : std::false_type {};
		template<class T, class U>
		struct HasModulation_t<T, U, std::void_t< decltype( std::declval<T&>() % std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() % std::declval<U&>() ), T> {};

		///	二項算術演算子~の実装を識別します。
		template<class, class = std::void_t<>>
		struct HasArithmeticNot_t : std::false_type {};
		template<class T>
		struct HasArithmeticNot_t<T, std::void_t< decltype( ~std::declval<T&>() ) > >
			: std::is_convertible< decltype( ~std::declval<T&>() ), T> {};

		///	二項算術演算子|の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasArithmeticOr_t : std::false_type {};
		template<class T, class U>
		struct HasArithmeticOr_t<T, U, std::void_t< decltype( std::declval<T&>() | std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() | std::declval<U&>() ), T> {};

		///	二項算術演算子&の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasArithmeticAnd_t : std::false_type {};
		template<class T, class U>
		struct HasArithmeticAnd_t<T, U, std::void_t< decltype( std::declval<T&>() & std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() & std::declval<U&>() ), T> {};

		///	二項算術演算子^の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasArithmeticXor_t : std::false_type {};
		template<class T, class U>
		struct HasArithmeticXor_t<T, U, std::void_t< decltype( std::declval<T&>() ^ std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() ^ std::declval<U&>() ), T> {};

		///	二項算術演算子<<の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasLShift_t : std::false_type {};
		template<class T, class U>
		struct HasLShift_t<T, U, std::void_t< decltype( std::declval<T&>() << std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() << std::declval<U&>() ), T> {};

		///	二項算術演算子>>の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasRShift_t : std::false_type {};
		template<class T, class U>
		struct HasRShift_t<T, U, std::void_t< decltype( std::declval<T&>() >> std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() >> std::declval<U&>() ), T> {};

		///	単項論理演算子!の実装を識別します。
		template<class, class = std::void_t<>>
		struct HasLogicalNot_t : std::false_type {};
		template<class T>
		struct HasLogicalNot_t<T, std::void_t< decltype( !std::declval<T&>() ) > >
			: std::is_convertible< decltype( !std::declval<T&>() ), T> {};

		///	二項論理演算子&&の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasLogicalAnd_t : std::false_type {};
		template<class T, class U>
		struct HasLogicalAnd_t<T, U, std::void_t< decltype( std::declval<T&>() && std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() && std::declval<U&>() ), T> {};

		///	二項論理演算子||の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasLogicalOr_t : std::false_type {};
		template<class T, class U>
		struct HasLogicalOr_t<T, U, std::void_t< decltype( std::declval<T&>() || std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() || std::declval<U&>() ), T> {};

		///	比較演算子==の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasEqual_t : std::false_type {};
		template<class T, class U>
		struct HasEqual_t<T, U, std::void_t< decltype( std::declval<T&>() == std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() == std::declval<U&>() ), bool> {};

		///	比較演算子!=の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasNotEqual_t : std::false_type {};
		template<class T, class U>
		struct HasNotEqual_t<T, U, std::void_t< decltype( std::declval<T&>() != std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() != std::declval<U&>() ), bool> {};

		///	比較演算子>の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasComparamentLarger_t : std::false_type {};
		template<class T, class U>
		struct HasComparamentLarger_t<T, U, std::void_t< decltype( std::declval<T&>() > std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() > std::declval<U&>() ), bool> {};

		///	比較演算子<の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasComparamentSmaller_t : std::false_type {};
		template<class T, class U>
		struct HasComparamentSmaller_t<T, U, std::void_t< decltype( std::declval<T&>() < std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() < std::declval<U&>() ), bool> {};

		///	比較演算子>=の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasComparamentLeast_t : std::false_type {};
		template<class T, class U>
		struct HasComparamentLeast_t<T, U, std::void_t< decltype( std::declval<T&>() >= std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() >= std::declval<U&>() ), bool> {};

		///	比較演算子<=の実装を識別します。
		template<class, class, class = std::void_t<>>
		struct HasComparamentMost_t : std::false_type {};
		template<class T, class U>
		struct HasComparamentMost_t<T, U, std::void_t< decltype( std::declval<T&>() <= std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() <= std::declval<U&>() ), bool> {};

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
		struct Equatable_t : std::conjunction< HasEqual_t<T, U>, HasNotEqual_t<T, U> > {};

		template<class T, class U>
		struct Comparable_t : std::conjunction< HasComparamentLarger_t<T, U>, HasComparamentSmaller_t<T, U>, HasComparamentLeast_t<T, U>, HasComparamentMost_t<T, U> > {};

		template<class T>
		struct HasUnaryOperation_t : std::conjunction<HasPromotion_t<T>, HasInverse_t<T>> {};

		template<class T, class U>
		struct HasAdditiveOperation_t : std::conjunction<HasAddition_t<T, U>, HasSubtraction_t<T, U>> {};

		template<class T, class U>
		struct HasMultiplicativeOperation_t : std::conjunction<HasMultiplication_t<T, U>, HasDivision_t<T, U>> {};

		template<class T>
		struct HasArithmeticOperation_t : std::conjunction<HasUnaryOperation_t<T>, HasAdditiveOperation_t<T, T>, HasMultiplicativeOperation_t<T, T>> {};

		template<class T, class U>
		struct HasBitOperation_t : std::conjunction<HasArithmeticNot_t<T>, HasArithmeticOr_t<T, T>, HasArithmeticAnd_t<T, T>, HasArithmeticXor_t<T, T>, HasLShift_t<T, U>, HasRShift_t<T, U>> {};

		template<class T>
		struct IsSequencialOrder_t : std::conjunction<HasPreIncrement_t<T>> {};

		template<class T>
		struct IsBidirectionalOrder_t : std::conjunction<IsSequencialOrder_t<T>, HasPreDecrement_t<T>> {};

		template<class T>
		struct IsLinearOrder_t : std::conjunction<IsBidirectionalOrder_t<T>> {};

		template<class T>
		struct IsIntegerType_t : std::conjunction< HasArithmeticOperation_t<T>, HasModulation_t<T, T>, HasBitOperation_t<T, T>, IsBidirectionalOrder_t<T> > {};

		template<class, class, class = std::void_t<>>
		struct HasSaturateAddition_t : std::false_type {};
		template<class T, class U>
		struct HasSaturateAddition_t<T, U, std::void_t< decltype( std::declval<T&>().SaturateAdd(std::declval<U&>()) ) > > : std::true_type {};

		template<class, class, class = std::void_t<>>
		struct HasSaturateSubtraction_t : std::false_type {};
		template<class T, class U>
		struct HasSaturateSubtraction_t<T, U, std::void_t< decltype( std::declval<T&>().SaturateSub(std::declval<U&>()) ) > > : std::true_type {};

		template<class, class, class = std::void_t<>>
		struct HasSaturateMultiplication_t : std::false_type {};
		template<class T, class U>
		struct HasSaturateMultiplication_t<T, U, std::void_t< decltype( std::declval<T&>().SaturateMul(std::declval<U&>()) ) > > : std::true_type {};

		template<class, class, class = std::void_t<>>
		struct HasSaturateDivision_t : std::false_type {};
		template<class T, class U>
		struct HasSaturateDivision_t<T, U, std::void_t< decltype( std::declval<T&>().SaturateDiv(std::declval<U&>()) ) > > : std::true_type {};

		template<class T, class U>
		struct HasSaturateOperation_t : std::conjunction<HasSaturateAddition_t<T, U>, HasSaturateSubtraction_t<T, U>, HasSaturateMultiplication_t<T, U>, HasSaturateDivision_t<T, U>> {};

		template<class, class, class = std::void_t<>>
		struct HasCheckedAddition_t : std::false_type {};
		template<class T, class U>
		struct HasCheckedAddition_t<T, U, std::void_t< decltype( std::declval<T&>().CheckedAdd(std::declval<U&>()) ) > > : std::true_type {};

		template<class, class, class = std::void_t<>>
		struct HasCheckedSubtraction_t : std::false_type {};
		template<class T, class U>
		struct HasCheckedSubtraction_t<T, U, std::void_t< decltype( std::declval<T&>().CheckedSub(std::declval<U&>()) ) > > : std::true_type {};

		template<class, class, class = std::void_t<>>
		struct HasCheckedMultiplication_t : std::false_type {};
		template<class T, class U>
		struct HasCheckedMultiplication_t<T, U, std::void_t< decltype( std::declval<T&>().CheckedMul(std::declval<U&>()) ) > > : std::true_type {};

		template<class, class, class = std::void_t<>>
		struct HasCheckedDivision_t : std::false_type {};
		template<class T, class U>
		struct HasCheckedDivision_t<T, U, std::void_t< decltype( std::declval<T&>().CheckedDiv(std::declval<U&>()) ) > > : std::true_type {};

		template<class T, class U>
		struct HasCheckedOperation_t : std::conjunction<HasCheckedAddition_t<T, U>, HasCheckedSubtraction_t<T, U>, HasCheckedMultiplication_t<T, U>, HasCheckedDivision_t<T, U>> {};

		template<class T, typename std::true_type::value_type = T::value>
		struct VoidImpl_t {};
		template<class T> struct VoidImpl_t<T, std::true_type::value> { constexpr static bool impl = true; };

	public:
		///	代入演算子=の実装を識別します。
		template<class T, class U = T> inline constexpr static bool HasSubstitution = HasSubstitution_t<T, U>::value;
		///	代入演算子+=の実装を識別します。
		template<class T, class U = T> inline constexpr static bool HasAddSubstitution = HasAddSubstitution_t<T, U>::value;
		///	代入演算子-=の実装を識別します。
		template<class T, class U = T> inline constexpr static bool HasSubtractSubstitution = HasSubtractSubstitution_t<T, U>::value;
		///	代入演算子*=の実装を識別します。
		template<class T, class U = T> inline constexpr static bool HasMultipleSubstitution = HasMultipleSubstitution_t<T, U>::value;
		///	代入演算子/=の実装を識別します。
		template<class T, class U = T> inline constexpr static bool HasDivideSubstitution = HasDivideSubstitution_t<T, U>::value;
		///	代入演算子%=の実装を識別します。
		template<class T, class U = T> inline constexpr static bool HasModulateSubstitution = HasModulateSubstitution_t<T, U>::value;
		///	代入演算子&=の実装を識別します。
		template<class T, class U = T> inline constexpr static bool HasArithmeticAndSubstitution = HasArithmeticAndSubstitution_t<T, U>::value;
		///	代入演算子|=の実装を識別します。
		template<class T, class U = T> inline constexpr static bool HasArithmeticOrSubstitution = HasArithmeticOrSubstitution_t<T, U>::value;
		///	代入演算子^=の実装を識別します。
		template<class T, class U = T> inline constexpr static bool HasArithmeticXorSubstitution = HasArithmeticXorSubstitution_t<T, U>::value;
		///	代入演算子<<=の実装を識別します。
		template<class T, class U = T> inline constexpr static bool HasBitLshiftSubstitution = HasBitLshiftSubstitution_t<T, U>::value;
		///	代入演算子>>=の実装を識別します。
		template<class T, class U = T> inline constexpr static bool HasBitRshiftSubstitution = HasBitRshiftSubstitution_t<T, U>::value;
		///	前置インクリメント演算子++の実装を識別します。
		template<class T> inline constexpr static bool HasPreIncrement = HasPreIncrement_t<T>::value;
		///	前置デクリメント演算子--の実装を識別します。
		template<class T> inline constexpr static bool HasPreDecrement = HasPreDecrement_t<T>::value;
		///	後置インクリメント演算子++の実装を識別します。
		template<class T> inline constexpr static bool HasPostIncrement = HasPostIncrement_t<T>::value;
		///	後置デクリメント演算子--の実装を識別します。
		template<class T> inline constexpr static bool HasPostDecrement = HasPostDecrement_t<T>::value;
		///	単項算術演算子+の実装を識別します。
		template<class T> inline constexpr static bool HasOperatorPromotion = HasPromotion_t<T>::value;
		///	単項算術演算子-の実装を識別します。
		template<class T> inline constexpr static bool HasOperatorInverse = HasInverse_t<T>::value;
		///	二項算術演算子+の実装を識別します。
		template<class T, class U = T> inline constexpr static bool HasOperatorAddition = HasAddition_t<T, U>::value;
		///	二項算術演算子-の実装を識別します。
		template<class T, class U = T> inline constexpr static bool HasOperatorSubtraction = HasSubtraction_t<T, U>::value;
		///	二項算術演算子*の実装を識別します。
		template<class T, class U = T> inline constexpr static bool HasOperatorMultiplication = HasMultiplication_t<T, U>::value;
		///	二項算術演算子/の実装を識別します。
		template<class T, class U = T> inline constexpr static bool HasOperatorDivision = HasDivision_t<T, U>::value;
		///	二項算術演算子%の実装を識別します。
		template<class T, class U = T> inline constexpr static bool HasOperatorModulation = HasModulation_t<T, U>::value;
		///	二項算術演算子~の実装を識別します。
		template<class T, class U = T> inline constexpr static bool HasOperatorArithmeticNot = HasArithmeticNot_t<T, U>::value;
		///	二項算術演算子|の実装を識別します。
		template<class T, class U = T> inline constexpr static bool HasOperatorArithmeticOr = HasArithmeticOr_t<T, U>::value;
		///	二項算術演算子&の実装を識別します。
		template<class T, class U = T> inline constexpr static bool HasOperatorArithmeticAnd = HasArithmeticAnd_t<T, U>::value;
		///	二項算術演算子^の実装を識別します。
		template<class T, class U = T> inline constexpr static bool HasOperatorArithmeticXor = HasArithmeticXor_t<T, U>::value;
		///	二項算術演算子<<の実装を識別します。
		template<class T, class U = T> inline constexpr static bool HasOperatorLShift = HasLShift_t<T, U>::value;
		///	二項算術演算子>>の実装を識別します。
		template<class T, class U = T> inline constexpr static bool HasOperatorRShift = HasRShift_t<T, U>::value;
		///	単項論理演算子!の実装を識別します。
		template<class T> inline constexpr static bool HasLogicalNot = HasLogicalNot_t<T>::value;
		///	二項論理演算子&&の実装を識別します。
		template<class T, class U = T> inline constexpr static bool HasLogicalAnd = HasLogicalAnd_t<T, U>::value;
		///	二項論理演算子||の実装を識別します。
		template<class T, class U = T> inline constexpr static bool HasLogicalOr = HasLogicalOr_t<T, U>::value;
		///	比較演算子==の実装を識別します。
		template<class T, class U = T> inline constexpr static bool HasOperatorEqual = HasEqual_t<T, U>::value;
		///	比較演算子!=の実装を識別します。
		template<class T, class U = T> inline constexpr static bool HasOperatorNotEqual = HasNotEqual_t<T, U>::value;
		///	比較演算子>の実装を識別します。
		template<class T, class U = T> inline constexpr static bool HasOperatorComparamentLarger = HasComparamentLarger_t<T, U>::value;
		///	比較演算子<の実装を識別します。
		template<class T, class U = T> inline constexpr static bool HasOperatorComparamentSmaller = HasComparamentSmaller_t<T, U>::value;
		///	比較演算子>=の実装を識別します。
		template<class T, class U = T> inline constexpr static bool HasOperatorComparamentLeast = HasComparamentLeast_t<T, U>::value;
		///	比較演算子<=の実装を識別します。
		template<class T, class U = T> inline constexpr static bool HasOperatorComparamentMost = HasComparamentMost_t<T, U>::value;
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
		template<class T> inline constexpr static bool HasUnaryOperation = HasUnaryOperation_t<T>::value;
		///	加法演算子を持つ型を識別します。
		template<class T, class U = T> inline constexpr static bool HasAdditiveOperation = HasAdditiveOperation_t<T, U>::value;
		///	乗法演算子を持つ型を識別します。
		template<class T, class U = T> inline constexpr static bool HasMultiplicativeOperation = HasMultiplicativeOperation_t<T, U>::value;
		///	基本的な算術演算を持つ型を識別します。
		template<class T> inline constexpr static bool HasArithmeticOperation = HasArithmeticOperation_t<T>::value;
		///	単方向の順序を持つ値型を識別します。
		template<class T> inline constexpr static bool IsSequencialOrder = IsSequencialOrder_t<T>::value;
		///	双方向の順序を持つ値型を識別します。
		template<class T> inline constexpr static bool IsBidirectionalOrder = IsBidirectionalOrder_t<T>::value;
		///	線形の順序を持つ値型を識別します。
		template<class T> inline constexpr static bool IsLinearOrder = IsLinearOrder_t<T>::value;
		///	整数型を識別します。
		template<class T> inline constexpr static bool IsIntegerType = IsIntegerType_t<T>::value;
		///	基本的なビット演算を持つ型を識別します。
		template<class T, class U = T> inline constexpr static bool HasBitOperation = HasBitOperation_t<T, U>::value;
		///	計算結果が飽和する四則演算を持つ型を識別します。
		template<class T, class U = T> inline constexpr static bool HasSaturateOperation = HasSaturateOperation_t<T, U>::value;
		///	計算結果の値域チェックが行われる四則演算を持つ型を識別します。
		template<class T, class U = T> inline constexpr static bool HasCheckedOperation = HasCheckedOperation_t<T, U>::value;
		///	@a T が @a std::true_type と等価な場合にのみ実体化できるメタテンプレートです。
		template<class T> inline constexpr static bool VoidImpl = VoidImpl_t<T>::impl;
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