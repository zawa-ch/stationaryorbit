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

		template<class T, class U, class R = decltype( std::declval<T&>() = std::declval<U&>() )> struct SubstitutionResult_impl { typedef R type; };
		template<class T, class U, class R = decltype( std::declval<T&>() += std::declval<U&>() )> struct SubstitutionAddResult_impl { typedef R type; };
		template<class T, class U, class R = decltype( std::declval<T&>() -= std::declval<U&>() )> struct SubstitutionSubtractResult_impl { typedef R type; };
		template<class T, class U, class R = decltype( std::declval<T&>() *= std::declval<U&>() )> struct SubstitutionMultipleResult_impl { typedef R type; };
		template<class T, class U, class R = decltype( std::declval<T&>() /= std::declval<U&>() )> struct SubstitutionDivideResult_impl { typedef R type; };
		template<class T, class U, class R = decltype( std::declval<T&>() %= std::declval<U&>() )> struct SubstitutionModulateResult_impl { typedef R type; };
		template<class T, class U, class R = decltype( std::declval<T&>() &= std::declval<U&>() )> struct SubstitutionArithmeticAndResult_impl { typedef R type; };
		template<class T, class U, class R = decltype( std::declval<T&>() |= std::declval<U&>() )> struct SubstitutionArithmeticOrResult_impl { typedef R type; };
		template<class T, class U, class R = decltype( std::declval<T&>() ^= std::declval<U&>() )> struct SubstitutionArithmeticXorResult_impl { typedef R type; };
		template<class T, class U, class R = decltype( std::declval<T&>() <<= std::declval<U&>() )> struct SubstitutionLShiftResult_impl { typedef R type; };
		template<class T, class U, class R = decltype( std::declval<T&>() >>= std::declval<U&>() )> struct SubstitutionRShiftResult_impl { typedef R type; };
		template<class T, class R = decltype( ++std::declval<T&>() )> struct PreincrementResult_impl { typedef R type; };
		template<class T, class R = decltype( --std::declval<T&>() )> struct PredecrementResult_impl { typedef R type; };
		template<class T, class R = decltype( std::declval<T&>()++ )> struct PostincrementResult_impl { typedef R type; };
		template<class T, class R = decltype( std::declval<T&>()-- )> struct PostdecrementResult_impl { typedef R type; };
		template<class T, class R = decltype( +std::declval<T&>() )> struct PromotionResult_impl { typedef R type; };
		template<class T, class R = decltype( -std::declval<T&>() )> struct InverseResult_impl { typedef R type; };
		template<class T, class U, class R = decltype( std::declval<T&>() + std::declval<U&>() )> struct AdditionResult_impl { typedef R type; };
		template<class T, class U, class R = decltype( std::declval<T&>() - std::declval<U&>() )> struct SubtractionResult_impl { typedef R type; };
		template<class T, class U, class R = decltype( std::declval<T&>() * std::declval<U&>() )> struct MultiplicationResult_impl { typedef R type; };
		template<class T, class U, class R = decltype( std::declval<T&>() / std::declval<U&>() )> struct DivisionResult_impl { typedef R type; };
		template<class T, class U, class R = decltype( std::declval<T&>() % std::declval<U&>() )> struct ModulationResult_impl { typedef R type; };
		template<class T, class R = decltype( ~std::declval<T&>() )> struct ArithmeticNotResult_impl { typedef R type; };
		template<class T, class U, class R = decltype( std::declval<T&>() & std::declval<U&>() )> struct ArithmeticOrResult_impl { typedef R type; };
		template<class T, class U, class R = decltype( std::declval<T&>() | std::declval<U&>() )> struct ArithmeticAndResult_impl { typedef R type; };
		template<class T, class U, class R = decltype( std::declval<T&>() ^ std::declval<U&>() )> struct ArithmeticXorResult_impl { typedef R type; };
		template<class T, class U, class R = decltype( std::declval<T&>() << std::declval<U&>() )> struct LShiftResult_impl { typedef R type; };
		template<class T, class U, class R = decltype( std::declval<T&>() >> std::declval<U&>() )> struct RShiftResult_impl { typedef R type; };
		template<class T, class R = decltype( !std::declval<T&>() )> struct LogicalNotResult_impl { typedef R type; };
		template<class T, class U, class R = decltype( std::declval<T&>() && std::declval<U&>() )> struct LogicalAndResult_impl { typedef R type; };
		template<class T, class U, class R = decltype( std::declval<T&>() || std::declval<U&>() )> struct LogicalOrResult_impl { typedef R type; };
		template<class T, class U, class R = decltype( std::declval<T&>() == std::declval<U&>() )> struct EqualResult_impl { typedef R type; };
		template<class T, class U, class R = decltype( std::declval<T&>() != std::declval<U&>() )> struct NotEqualResult_impl { typedef R type; };
		template<class T, class U, class R = decltype( std::declval<T&>() > std::declval<U&>() )> struct LargerCompareResult_impl { typedef R type; };
		template<class T, class U, class R = decltype( std::declval<T&>() < std::declval<U&>() )> struct SmallerCompareResult_impl { typedef R type; };
		template<class T, class U, class R = decltype( std::declval<T&>() >= std::declval<U&>() )> struct LeastCompareResult_impl { typedef R type; };
		template<class T, class U, class R = decltype( std::declval<T&>() <= std::declval<U&>() )> struct MostCompareResult_impl { typedef R type; };
		template<class T, class U, class R = decltype( std::declval<T&>()[ std::declval<U&>() ] )> struct SubscriptResult_impl { typedef R type; };
		template<class T, class R = decltype( *std::declval<T&>() )> struct DereferenceResult_impl { typedef R type; };
		template<class T, class R = decltype( &std::declval<T&>() )> struct ReferenceResult_impl { typedef R type; };
		template<class T, class U, class R = decltype( std::declval<T&>(), std::declval<U&>() )> struct CommaResult_impl { typedef R type; };
	public:
		///	代入演算子 @a T::operator=(U) の結果を表す型。
		template<class T, class U> using SubstitutionResult = typename SubstitutionResult_impl<T, U>::type;
		///	代入演算子 @a T::operator+=(U) の結果を表す型。
		template<class T, class U> using SubstitutionAddResult = typename SubstitutionAddResult_impl<T, U>::type;
		///	代入演算子 @a T::operator-=(U) の結果を表す型。
		template<class T, class U> using SubstitutionSubtractResult = typename SubstitutionSubtractResult_impl<T, U>::type;
		///	代入演算子 @a T::operator*=(U) の結果を表す型。
		template<class T, class U> using SubstitutionMultipleResult = typename SubstitutionMultipleResult_impl<T, U>::type;
		///	代入演算子 @a T::operator/=(U) の結果を表す型。
		template<class T, class U> using SubstitutionDivideResult = typename SubstitutionDivideResult_impl<T, U>::type;
		///	代入演算子 @a T::operator%=(U) の結果を表す型。
		template<class T, class U> using SubstitutionModulateResult = typename SubstitutionModulateResult_impl<T, U>::type;
		///	代入演算子 @a T::operator&=(U) の結果を表す型。
		template<class T, class U> using SubstitutionArithmeticAndResult = typename SubstitutionArithmeticAndResult_impl<T, U>::type;
		///	代入演算子 @a T::operator|=(U) の結果を表す型。
		template<class T, class U> using SubstitutionArithmeticOrResult = typename SubstitutionArithmeticOrResult_impl<T, U>::type;
		///	代入演算子 @a T::operator^=(U) の結果を表す型。
		template<class T, class U> using SubstitutionArithmeticXorResult = typename SubstitutionArithmeticXorResult_impl<T, U>::type;
		///	代入演算子 @a T::operator<<=(U) の結果を表す型。
		template<class T, class U> using SubstitutionLShiftResult = typename SubstitutionLShiftResult_impl<T, U>::type;
		///	代入演算子 @a T::operator>>=(U) の結果を表す型。
		template<class T, class U> using SubstitutionRShiftResult = typename SubstitutionRShiftResult_impl<T, U>::type;
		///	前置インクリメント演算子 @a T::operator++() の結果を表す型。
		template<class T> using PreincrementResult = typename PreincrementResult_impl<T>::type;
		///	前置デクリメント演算子 @a T::operator--() の結果を表す型。
		template<class T> using PredecrementResult = typename PredecrementResult_impl<T>::type;
		///	後置インクリメント演算子 @a T::operator++(int) の結果を表す型。
		template<class T> using PostincrementResult = typename PostincrementResult_impl<T>::type;
		///	後置デクリメント演算子 @a T::operator--(int) の結果を表す型。
		template<class T> using PostdecrementResult = typename PostdecrementResult_impl<T>::type;
		///	算術演算子 @a T::operator+() の結果を表す型。
		template<class T> using PromotionResult = typename PromotionResult_impl<T>::type;
		///	算術演算子 @a T::operator-() の結果を表す型。
		template<class T> using InverseResult = typename InverseResult_impl<T>::type;
		///	算術演算子 @a T::operator+(U) の結果を表す型。
		template<class T, class U> using AdditionResult = typename AdditionResult_impl<T, U>::type;
		///	算術演算子 @a T::operator-(U) の結果を表す型。
		template<class T, class U> using SubtractionResult = typename SubtractionResult_impl<T, U>::type;
		///	算術演算子 @a T::operator*(U) の結果を表す型。
		template<class T, class U> using MultiplicationResult = typename MultiplicationResult_impl<T, U>::type;
		///	算術演算子 @a T::operator/(U) の結果を表す型。
		template<class T, class U> using DivisionResult = typename DivisionResult_impl<T, U>::type;
		///	算術演算子 @a T::operator%(U) の結果を表す型。
		template<class T, class U> using ModulationResult = typename ModulationResult_impl<T, U>::type;
		///	算術演算子 @a T::operator~() の結果を表す型。
		template<class T> using ArithmeticNotResult = typename ArithmeticNotResult_impl<T>::type;
		///	算術演算子 @a T::operator&(U) の結果を表す型。
		template<class T, class U> using ArithmeticAndResult = typename ArithmeticAndResult_impl<T, U>::type;
		///	算術演算子 @a T::operator|(U) の結果を表す型。
		template<class T, class U> using ArithmeticOrResult = typename ArithmeticOrResult_impl<T, U>::type;
		///	算術演算子 @a T::operator^(U) の結果を表す型。
		template<class T, class U> using ArithmeticXorResult = typename ArithmeticXorResult_impl<T, U>::type;
		///	算術演算子 @a T::operator<<(U) の結果を表す型。
		template<class T, class U> using LShiftResult = typename LShiftResult_impl<T, U>::type;
		///	算術演算子 @a T::operator>>(U) の結果を表す型。
		template<class T, class U> using RShiftResult = typename RShiftResult_impl<T, U>::type;
		///	論理演算子 @a T::operator!() の結果を表す型。
		template<class T> using LogicalNotResult = typename LogicalNotResult_impl<T>::type;
		///	論理演算子 @a T::operator&&(U) の結果を表す型。
		template<class T, class U> using LogicalOrResult = typename LogicalOrResult_impl<T, U>::type;
		///	論理演算子 @a T::operator||(U) の結果を表す型。
		template<class T, class U> using LogicalAndResult = typename LogicalAndResult_impl<T, U>::type;
		///	比較演算子 @a T::operator==(U) の結果を表す型。
		template<class T, class U> using EqualResult = typename EqualResult_impl<T, U>::type;
		///	比較演算子 @a T::operator!=(U) の結果を表す型。
		template<class T, class U> using NotEqualResult = typename NotEqualResult_impl<T, U>::type;
		///	比較演算子 @a T::operator>(U) の結果を表す型。
		template<class T, class U> using LargerCompareResult = typename LargerCompareResult_impl<T, U>::type;
		///	比較演算子 @a T::operator<(U) の結果を表す型。
		template<class T, class U> using SmallerCompareResult = typename SmallerCompareResult_impl<T, U>::type;
		///	比較演算子 @a T::operator>=(U) の結果を表す型。
		template<class T, class U> using LeastCompareResult = typename LeastCompareResult_impl<T, U>::type;
		///	比較演算子 @a T::operator<=(U) の結果を表す型。
		template<class T, class U> using MostCompareResult = typename MostCompareResult_impl<T, U>::type;
		///	比較演算子 @a T::operator[](U) の結果を表す型。
		template<class T, class U> using SubscriptResult = typename SubscriptResult_impl<T, U>::type;
		///	比較演算子 @a T::operator*() の結果を表す型。
		template<class T> using DereferenceResult = typename DereferenceResult_impl<T>::type;
		///	比較演算子 @a T::operator&() の結果を表す型。
		template<class T> using ReferenceResult = typename ReferenceResult_impl<T>::type;
		///	比較演算子 @a T::operator,(U) の結果を表す型。
		template<class T, class U> using CommaResult = typename CommaResult_impl<T, U>::type;
	private:
		///	代入演算子 @a T::operator=(U) の実装を識別するための実装。
		template<class, class, class = std::void_t<>> struct HasSubstitution_t : std::false_type {};
		template<class T, class U> struct HasSubstitution_t<T, U, std::void_t< SubstitutionResult<T, U> > > : std::true_type {};
		///	代入演算子 @a T::operator+=(U) の実装を識別するための実装。
		template<class, class, class = std::void_t<>> struct HasSubstitutionAdd_t : std::false_type {};
		template<class T, class U> struct HasSubstitutionAdd_t<T, U, std::void_t< SubstitutionAddResult<T, U> > > : std::true_type {};
		///	代入演算子 @a T::operator-=(U) の実装を識別するための実装。
		template<class, class, class = std::void_t<>> struct HasSubstitutionSubtract_t : std::false_type {};
		template<class T, class U> struct HasSubstitutionSubtract_t<T, U, std::void_t< SubstitutionSubtractResult<T, U> > > : std::true_type {};
		///	代入演算子 @a T::operator*=(U) の実装を識別するための実装。
		template<class, class, class = std::void_t<>> struct HasSubstitutionMultiple_t : std::false_type {};
		template<class T, class U> struct HasSubstitutionMultiple_t<T, U, std::void_t< SubstitutionMultipleResult<T, U> > > : std::true_type {};
		///	代入演算子 @a T::operator/=(U) の実装を識別するための実装。
		template<class, class, class = std::void_t<>> struct HasSubstitutionDivide_t : std::false_type {};
		template<class T, class U> struct HasSubstitutionDivide_t<T, U, std::void_t< SubstitutionDivideResult<T, U> > > : std::true_type {};
		///	代入演算子 @a T::operator%=(U) の実装を識別するための実装。
		template<class, class, class = std::void_t<>> struct HasSubstitutionModulate_t : std::false_type {};
		template<class T, class U> struct HasSubstitutionModulate_t<T, U, std::void_t< SubstitutionModulateResult<T, U> > > : std::true_type {};
		///	代入演算子 @a T::operator&=(U) の実装を識別するための実装。
		template<class, class, class = std::void_t<>> struct HasSubstitutionArithmeticAnd_t : std::false_type {};
		template<class T, class U> struct HasSubstitutionArithmeticAnd_t<T, U, std::void_t< SubstitutionArithmeticAndResult<T, U> > > : std::true_type {};
		///	代入演算子 @a T::operator|=(U) の実装を識別するための実装。
		template<class, class, class = std::void_t<>> struct HasSubstitutionArithmeticOr_t : std::false_type {};
		template<class T, class U> struct HasSubstitutionArithmeticOr_t<T, U, std::void_t< SubstitutionArithmeticOrResult<T, U> > > : std::true_type {};
		///	代入演算子 @a T::operator^=(U) の実装を識別するための実装。
		template<class, class, class = std::void_t<>> struct HasSubstitutionArithmeticXor_t : std::false_type {};
		template<class T, class U> struct HasSubstitutionArithmeticXor_t<T, U, std::void_t< SubstitutionArithmeticXorResult<T, U> > > : std::true_type {};
		///	代入演算子 @a T::operator<<=(U) の実装を識別するための実装。
		template<class, class, class = std::void_t<>> struct HasSubstitutionLShift_t : std::false_type {};
		template<class T, class U> struct HasSubstitutionLShift_t<T, U, std::void_t< SubstitutionLShiftResult<T, U> > > : std::true_type {};
		///	代入演算子 @a T::operator>>=(U) の実装を識別するための実装。
		template<class, class, class = std::void_t<>> struct HasSubstitutionRShift_t : std::false_type {};
		template<class T, class U> struct HasSubstitutionRShift_t<T, U, std::void_t< SubstitutionRShiftResult<T, U> > > : std::true_type {};
		///	前置インクリメント演算子 @a T::operator++() の実装を識別するための実装。
		template<class, class = std::void_t<>> struct HasPreincrement_t : std::false_type {};
		template<class T> struct HasPreincrement_t<T, std::void_t< PreincrementResult<T> > > : std::true_type {};
		///	前置デクリメント演算子 @a T::operator--() の実装を識別するための実装。
		template<class, class = std::void_t<>> struct HasPredecrement_t : std::false_type {};
		template<class T> struct HasPredecrement_t<T, std::void_t< PredecrementResult<T> > > : std::true_type {};
		///	後置インクリメント演算子 @a T::operator++(int) の実装を識別するための実装。
		template<class, class = std::void_t<>> struct HasPostincrement_t : std::false_type {};
		template<class T> struct HasPostincrement_t<T, std::void_t< PostincrementResult<T> > > : std::true_type {};
		///	後置デクリメント演算子 @a T::operator--(int) の実装を識別するための実装。
		template<class, class = std::void_t<>> struct HasPostdecrement_t : std::false_type {};
		template<class T> struct HasPostdecrement_t<T, std::void_t< PostdecrementResult<T> > > : std::true_type {};
		///	算術演算子 @a T::operator+() の実装を識別するための実装。
		template<class, class = std::void_t<>> struct HasPromotion_t : std::false_type {};
		template<class T> struct HasPromotion_t<T, std::void_t< PromotionResult<T> > > : std::true_type {};
		///	算術演算子 @a T::operator-() の実装を識別するための実装。
		template<class, class = std::void_t<>> struct HasInverse_t : std::false_type {};
		template<class T> struct HasInverse_t<T, std::void_t< InverseResult<T> > > : std::true_type {};
		///	算術演算子 @a T::operator+(U) の実装を識別するための実装。
		template<class, class, class = std::void_t<>> struct HasAddition_t : std::false_type {};
		template<class T, class U> struct HasAddition_t<T, U, std::void_t< AdditionResult<T, U> > > : std::true_type {};
		///	算術演算子 @a T::operator-(U) の実装を識別するための実装。
		template<class, class, class = std::void_t<>> struct HasSubtraction_t : std::false_type {};
		template<class T, class U> struct HasSubtraction_t<T, U, std::void_t< SubtractionResult<T, U> > > : std::true_type {};
		///	算術演算子 @a T::operator*(U) の実装を識別するための実装。
		template<class, class, class = std::void_t<>> struct HasMultiplication_t : std::false_type {};
		template<class T, class U> struct HasMultiplication_t<T, U, std::void_t< MultiplicationResult<T, U> > > : std::true_type {};
		///	算術演算子 @a T::operator/(U) の実装を識別するための実装。
		template<class, class, class = std::void_t<>> struct HasDivision_t : std::false_type {};
		template<class T, class U> struct HasDivision_t<T, U, std::void_t< DivisionResult<T, U> > > : std::true_type {};
		///	算術演算子 @a T::operator%(U) の実装を識別するための実装。
		template<class, class, class = std::void_t<>> struct HasModulation_t : std::false_type {};
		template<class T, class U> struct HasModulation_t<T, U, std::void_t< ModulationResult<T, U> > > : std::true_type {};
		///	算術演算子 @a T::operator~() の実装を識別するための実装。
		template<class, class = std::void_t<>> struct HasArithmeticNot_t : std::false_type {};
		template<class T> struct HasArithmeticNot_t<T, std::void_t< ArithmeticNotResult<T> > > : std::true_type {};
		///	算術演算子 @a T::operator&(U) の実装を識別するための実装。
		template<class, class, class = std::void_t<>> struct HasArithmeticAnd_t : std::false_type {};
		template<class T, class U> struct HasArithmeticAnd_t<T, U, std::void_t< ArithmeticAndResult<T, U> > > : std::true_type {};
		///	算術演算子 @a T::operator|(U) の実装を識別するための実装。
		template<class, class, class = std::void_t<>> struct HasArithmeticOr_t : std::false_type {};
		template<class T, class U> struct HasArithmeticOr_t<T, U, std::void_t< ArithmeticOrResult<T, U> > > : std::true_type {};
		///	算術演算子 @a T::operator^(U) の実装を識別するための実装。
		template<class, class, class = std::void_t<>> struct HasArithmeticXor_t : std::false_type {};
		template<class T, class U> struct HasArithmeticXor_t<T, U, std::void_t< ArithmeticXorResult<T, U> > > : std::true_type {};
		///	算術演算子 @a T::operator<<(U) の実装を識別するための実装。
		template<class, class, class = std::void_t<>> struct HasLShift_t : std::false_type {};
		template<class T, class U> struct HasLShift_t<T, U, std::void_t< LShiftResult<T, U> > > : std::true_type {};
		///	算術演算子 @a T::operator>>(U) の実装を識別するための実装。
		template<class, class, class = std::void_t<>> struct HasRShift_t : std::false_type {};
		template<class T, class U> struct HasRShift_t<T, U, std::void_t< RShiftResult<T, U> > > : std::true_type {};
		///	論理演算子 @a T::operator!() の実装を識別するための実装。
		template<class, class = std::void_t<>> struct HasLogicalNot_t : std::false_type {};
		template<class T> struct HasLogicalNot_t<T, std::void_t< LogicalNotResult<T> > > : std::true_type {};
		///	論理演算子 @a T::operator&&(U) の実装を識別するための実装。
		template<class, class, class = std::void_t<>> struct HasLogicalOr_t : std::false_type {};
		template<class T, class U> struct HasLogicalOr_t<T, U, std::void_t< LogicalOrResult<T, U> > > : std::true_type {};
		///	論理演算子 @a T::operator||(U) の実装を識別するための実装。
		template<class, class, class = std::void_t<>> struct HasLogicalAnd_t : std::false_type {};
		template<class T, class U> struct HasLogicalAnd_t<T, U, std::void_t< LogicalAndResult<T, U> > > : std::true_type {};
		///	比較演算子 @a T::operator==(U) の実装を識別するための実装。
		template<class, class, class = std::void_t<>> struct HasEqual_t : std::false_type {};
		template<class T, class U> struct HasEqual_t<T, U, std::void_t< EqualResult<T, U> > > : std::true_type {};
		///	比較演算子 @a T::operator!=(U) の実装を識別するための実装。
		template<class, class, class = std::void_t<>> struct HasNotEqual_t : std::false_type {};
		template<class T, class U> struct HasNotEqual_t<T, U, std::void_t< NotEqualResult<T, U> > > : std::true_type {};
		///	比較演算子 @a T::operator>(U) の実装を識別するための実装。
		template<class, class, class = std::void_t<>> struct HasLargerCompare_t : std::false_type {};
		template<class T, class U> struct HasLargerCompare_t<T, U, std::void_t< LargerCompareResult<T, U> > > : std::true_type {};
		///	比較演算子 @a T::operator<(U) の実装を識別するための実装。
		template<class, class, class = std::void_t<>> struct HasSmallerCompare_t : std::false_type {};
		template<class T, class U> struct HasSmallerCompare_t<T, U, std::void_t< SmallerCompareResult<T, U> > > : std::true_type {};
		///	比較演算子 @a T::operator>=(U) の実装を識別するための実装。
		template<class, class, class = std::void_t<>> struct HasLeastCompare_t : std::false_type {};
		template<class T, class U> struct HasLeastCompare_t<T, U, std::void_t< LeastCompareResult<T, U> > > : std::true_type {};
		///	比較演算子 @a T::operator<=(U) の実装を識別するための実装。
		template<class, class, class = std::void_t<>> struct HasMostCompare_t : std::false_type {};
		template<class T, class U> struct HasMostCompare_t<T, U, std::void_t< MostCompareResult<T, U> > > : std::true_type {};
		///	比較演算子 @a T::operator[](U) の実装を識別するための実装。
		template<class, class, class = std::void_t<>> struct HasSubscript_t : std::false_type {};
		template<class T, class U> struct HasSubscript_t<T, U, std::void_t< SubscriptResult<T, U> > > : std::true_type {};
		///	比較演算子 @a T::operator*() の実装を識別するための実装。
		template<class, class = std::void_t<>> struct HasDereference_t : std::false_type {};
		template<class T> struct HasDereference_t<T, std::void_t< DereferenceResult<T> > > : std::true_type {};
		///	比較演算子 @a T::operator&() の実装を識別するための実装。
		template<class, class = std::void_t<>> struct HasReference_t : std::false_type {};
		template<class T> struct HasReference_t<T, std::void_t< ReferenceResult<T> > > : std::true_type {};
		///	比較演算子 @a T::operator,(U) の実装を識別するための実装。
		template<class, class, class = std::void_t<>> struct HasComma_t : std::false_type {};
		template<class T, class U> struct HasComma_t<T, U, std::void_t< CommaResult<T, U> > > : std::true_type {};
	public:
		///	代入演算子 @a T::operator=(U) の実装を識別します。
		template<class T, class U> static constexpr bool HasSubstitution = HasSubstitution_t<T, U>::value;
		///	代入演算子 @a T::operator+=(U) の実装を識別します。
		template<class T, class U> static constexpr bool HasSubstitutionAdd = HasSubstitutionAdd_t<T, U>::value;
		///	代入演算子 @a T::operator-=(U) の実装を識別します。
		template<class T, class U> static constexpr bool HasSubstitutionSubtract = HasSubstitutionSubtract_t<T, U>::value;
		///	代入演算子 @a T::operator*=(U) の実装を識別します。
		template<class T, class U> static constexpr bool HasSubstitutionMultiple = HasSubstitutionMultiple_t<T, U>::value;
		///	代入演算子 @a T::operator/=(U) の実装を識別します。
		template<class T, class U> static constexpr bool HasSubstitutionDivide = HasSubstitutionDivide_t<T, U>::value;
		///	代入演算子 @a T::operator%=(U) の実装を識別します。
		template<class T, class U> static constexpr bool HasSubstitutionModulate = HasSubstitutionModulate_t<T, U>::value;
		///	代入演算子 @a T::operator&=(U) の実装を識別します。
		template<class T, class U> static constexpr bool HasSubstitutionArithmeticAnd = HasSubstitutionArithmeticAnd_t<T, U>::value;
		///	代入演算子 @a T::operator|=(U) の実装を識別します。
		template<class T, class U> static constexpr bool HasSubstitutionArithmeticOr = HasSubstitutionArithmeticOr_t<T, U>::value;
		///	代入演算子 @a T::operator^=(U) の実装を識別します。
		template<class T, class U> static constexpr bool HasSubstitutionArithmeticXor = HasSubstitutionArithmeticXor_t<T, U>::value;
		///	代入演算子 @a T::operator<<=(U) の実装を識別します。
		template<class T, class U> static constexpr bool HasSubstitutionLShift = HasSubstitutionLShift_t<T, U>::value;
		///	代入演算子 @a T::operator>>=(U) の実装を識別します。
		template<class T, class U> static constexpr bool HasSubstitutionRShift = HasSubstitutionRShift_t<T, U>::value;
		///	前置インクリメント演算子 @a T::operator++() の実装を識別します。
		template<class T> static constexpr bool HasPreincrement = HasPreincrement_t<T>::value;
		///	前置デクリメント演算子 @a T::operator--() の実装を識別します。
		template<class T> static constexpr bool HasPredecrement = HasPredecrement_t<T>::value;
		///	後置インクリメント演算子 @a T::operator++(int) の実装を識別します。
		template<class T> static constexpr bool HasPostincrement = HasPostincrement_t<T>::value;
		///	後置デクリメント演算子 @a T::operator--(int) の実装を識別します。
		template<class T> static constexpr bool HasPostdecrement = HasPostdecrement_t<T>::value;
		///	算術演算子 @a T::operator+() の実装を識別します。
		template<class T> static constexpr bool HasPromotion = HasPromotion_t<T>::value;
		///	算術演算子 @a T::operator-() の実装を識別します。
		template<class T> static constexpr bool HasInverse = HasInverse_t<T>::value;
		///	算術演算子 @a T::operator+(U) の実装を識別します。
		template<class T, class U> static constexpr bool HasAddition = HasAddition_t<T, U>::value;
		///	算術演算子 @a T::operator-(U) の実装を識別します。
		template<class T, class U> static constexpr bool HasSubtraction = HasSubtraction_t<T, U>::value;
		///	算術演算子 @a T::operator*(U) の実装を識別します。
		template<class T, class U> static constexpr bool HasMultiplication = HasMultiplication_t<T, U>::value;
		///	算術演算子 @a T::operator/(U) の実装を識別します。
		template<class T, class U> static constexpr bool HasDivision = HasDivision_t<T, U>::value;
		///	算術演算子 @a T::operator%(U) の実装を識別します。
		template<class T, class U> static constexpr bool HasModulation = HasModulation_t<T, U>::value;
		///	算術演算子 @a T::operator~() の実装を識別します。
		template<class T> static constexpr bool HasArithmeticNot = HasArithmeticNot_t<T>::value;
		///	算術演算子 @a T::operator&(U) の実装を識別します。
		template<class T, class U> static constexpr bool HasArithmeticAnd = HasArithmeticAnd_t<T, U>::value;
		///	算術演算子 @a T::operator|(U) の実装を識別します。
		template<class T, class U> static constexpr bool HasArithmeticOr = HasArithmeticOr_t<T, U>::value;
		///	算術演算子 @a T::operator^(U) の実装を識別します。
		template<class T, class U> static constexpr bool HasArithmeticXor = HasArithmeticXor_t<T, U>::value;
		///	算術演算子 @a T::operator<<(U) の実装を識別します。
		template<class T, class U> static constexpr bool HasLShift = HasLShift_t<T, U>::value;
		///	算術演算子 @a T::operator>>(U) の実装を識別します。
		template<class T, class U> static constexpr bool HasRShift = HasRShift_t<T, U>::value;
		///	論理演算子 @a T::operator!() の実装を識別します。
		template<class T> static constexpr bool HasLogicalNot = HasLogicalNot_t<T>::value;
		///	論理演算子 @a T::operator&&(U) の実装を識別します。
		template<class T, class U> static constexpr bool HasLogicalOr = HasLogicalOr_t<T, U>::value;
		///	論理演算子 @a T::operator||(U) の実装を識別します。
		template<class T, class U> static constexpr bool HasLogicalAnd = HasLogicalAnd_t<T, U>::value;
		///	比較演算子 @a T::operator==(U) の実装を識別します。
		template<class T, class U> static constexpr bool HasEqual = HasEqual_t<T, U>::value;
		///	比較演算子 @a T::operator!=(U) の実装を識別します。
		template<class T, class U> static constexpr bool HasNotEqual = HasNotEqual_t<T, U>::value;
		///	比較演算子 @a T::operator>(U) の実装を識別します。
		template<class T, class U> static constexpr bool HasLargerCompare = HasLargerCompare_t<T, U>::value;
		///	比較演算子 @a T::operator<(U) の実装を識別します。
		template<class T, class U> static constexpr bool HasSmallerCompare = HasSmallerCompare_t<T, U>::value;
		///	比較演算子 @a T::operator>=(U) の実装を識別します。
		template<class T, class U> static constexpr bool HasLeastCompare = HasLeastCompare_t<T, U>::value;
		///	比較演算子 @a T::operator<=(U) の実装を識別します。
		template<class T, class U> static constexpr bool HasMostCompare = HasMostCompare_t<T, U>::value;
		///	比較演算子 @a T::operator[](U) の実装を識別します。
		template<class T, class U> static constexpr bool HasSubscript = HasSubscript_t<T, U>::value;
		///	比較演算子 @a T::operator*() の実装を識別します。
		template<class T> static constexpr bool HasDereference = HasDereference_t<T>::value;
		///	比較演算子 @a T::operator&() の実装を識別します。
		template<class T> static constexpr bool HasReference = HasReference_t<T>::value;
		///	比較演算子 @a T::operator,(U) の実装を識別します。
		template<class T, class U> static constexpr bool HasComma = HasComma_t<T, U>::value;
	private:
		///	代入演算子 @a T::operator=(U) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionResultIsSame_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionResultIsSame_t<T, U, R, std::void_t< SubstitutionResult<T, U> > > : std::is_same<SubstitutionResult<T, U>, R> {};
		///	代入演算子 @a T::operator+=(U) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionAddResultIsSame_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionAddResultIsSame_t<T, U, R, std::void_t< SubstitutionAddResult<T, U> > > : std::is_same<SubstitutionAddResult<T, U>, R> {};
		///	代入演算子 @a T::operator-=(U) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionSubtractResultIsSame_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionSubtractResultIsSame_t<T, U, R, std::void_t< SubstitutionSubtractResult<T, U> > > : std::is_same<SubstitutionSubtractResult<T, U>, R> {};
		///	代入演算子 @a T::operator*=(U) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionMultipleResultIsSame_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionMultipleResultIsSame_t<T, U, R, std::void_t< SubstitutionMultipleResult<T, U> > > : std::is_same<SubstitutionMultipleResult<T, U>, R> {};
		///	代入演算子 @a T::operator/=(U) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionDivideResultIsSame_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionDivideResultIsSame_t<T, U, R, std::void_t< SubstitutionDivideResult<T, U> > > : std::is_same<SubstitutionDivideResult<T, U>, R> {};
		///	代入演算子 @a T::operator%=(U) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionModulateResultIsSame_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionModulateResultIsSame_t<T, U, R, std::void_t< SubstitutionModulateResult<T, U> > > : std::is_same<SubstitutionModulateResult<T, U>, R> {};
		///	代入演算子 @a T::operator&=(U) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionArithmeticAndResultIsSame_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionArithmeticAndResultIsSame_t<T, U, R, std::void_t< SubstitutionArithmeticAndResult<T, U> > > : std::is_same<SubstitutionArithmeticAndResult<T, U>, R> {};
		///	代入演算子 @a T::operator|=(U) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionArithmeticOrResultIsSame_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionArithmeticOrResultIsSame_t<T, U, R, std::void_t< SubstitutionArithmeticOrResult<T, U> > > : std::is_same<SubstitutionArithmeticOrResult<T, U>, R> {};
		///	代入演算子 @a T::operator^=(U) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionArithmeticXorResultIsSame_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionArithmeticXorResultIsSame_t<T, U, R, std::void_t< SubstitutionArithmeticXorResult<T, U> > > : std::is_same<SubstitutionArithmeticXorResult<T, U>, R> {};
		///	代入演算子 @a T::operator<<=(U) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionLShiftResultIsSame_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionLShiftResultIsSame_t<T, U, R, std::void_t< SubstitutionLShiftResult<T, U> > > : std::is_same<SubstitutionLShiftResult<T, U>, R> {};
		///	代入演算子 @a T::operator>>=(U) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionRShiftResultIsSame_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionRShiftResultIsSame_t<T, U, R, std::void_t< SubstitutionRShiftResult<T, U> > > : std::is_same<SubstitutionRShiftResult<T, U>, R> {};
		///	前置インクリメント演算子 @a T::operator++() の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class = std::void_t<>> struct PreincrementResultIsSame_t : std::false_type {};
		template<class T, class R> struct PreincrementResultIsSame_t<T, R, std::void_t< PreincrementResult<T> > > : std::is_same<PreincrementResult<T>, R> {};
		#if 201703L <= __cplusplus
		// Clang C++17でコンパイルするとbool::operator++()を実体化しようとしてエラーを吐くため
		// boolによるインクリメントトレイトは強制的にfalseで実体化する
		template<class R> struct PreincrementResultIsSame_t<bool, R> : std::false_type {};
		#endif
		///	前置デクリメント演算子 @a T::operator--() の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class = std::void_t<>> struct PredecrementResultIsSame_t : std::false_type {};
		template<class T, class R> struct PredecrementResultIsSame_t<T, R, std::void_t< PredecrementResult<T> > > : std::is_same<PredecrementResult<T>, R> {};
		///	後置インクリメント演算子 @a T::operator++(int) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class = std::void_t<>> struct PostincrementResultIsSame_t : std::false_type {};
		template<class T, class R> struct PostincrementResultIsSame_t<T, R, std::void_t< PostincrementResult<T> > > : std::is_same<PostincrementResult<T>, R> {};
		#if 201703L <= __cplusplus
		// Clang C++17でコンパイルするとbool::operator++(int)を実体化しようとしてエラーを吐くため
		// boolによるインクリメントトレイトは強制的にfalseで実体化する
		template<class R> struct PostincrementResultIsSame_t<bool, R> : std::false_type {};
		#endif
		///	後置デクリメント演算子 @a T::operator--(int) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class = std::void_t<>> struct PostdecrementResultIsSame_t : std::false_type {};
		template<class T, class R> struct PostdecrementResultIsSame_t<T, R, std::void_t< PostdecrementResult<T> > > : std::is_same<PostdecrementResult<T>, R> {};
		///	算術演算子 @a T::operator+() の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class = std::void_t<>> struct PromotionResultIsSame_t : std::false_type {};
		template<class T, class R> struct PromotionResultIsSame_t<T, R, std::void_t< PromotionResult<T> > > : std::is_same<PromotionResult<T>, R> {};
		///	算術演算子 @a T::operator-() の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class = std::void_t<>> struct InverseResultIsSame_t : std::false_type {};
		template<class T, class R> struct InverseResultIsSame_t<T, R, std::void_t< InverseResult<T> > > : std::is_same<InverseResult<T>, R> {};
		///	算術演算子 @a T::operator+(U) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct AdditionResultIsSame_t : std::false_type {};
		template<class T, class U, class R> struct AdditionResultIsSame_t<T, U, R, std::void_t< AdditionResult<T, U> > > : std::is_same<AdditionResult<T, U>, R> {};
		///	算術演算子 @a T::operator-(U) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubtractionResultIsSame_t : std::false_type {};
		template<class T, class U, class R> struct SubtractionResultIsSame_t<T, U, R, std::void_t< SubtractionResult<T, U> > > : std::is_same<SubtractionResult<T, U>, R> {};
		///	算術演算子 @a T::operator*(U) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct MultiplicationResultIsSame_t : std::false_type {};
		template<class T, class U, class R> struct MultiplicationResultIsSame_t<T, U, R, std::void_t< MultiplicationResult<T, U> > > : std::is_same<MultiplicationResult<T, U>, R> {};
		///	算術演算子 @a T::operator/(U) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct DivisionResultIsSame_t : std::false_type {};
		template<class T, class U, class R> struct DivisionResultIsSame_t<T, U, R, std::void_t< DivisionResult<T, U> > > : std::is_same<DivisionResult<T, U>, R> {};
		///	算術演算子 @a T::operator%(U) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct ModulationResultIsSame_t : std::false_type {};
		template<class T, class U, class R> struct ModulationResultIsSame_t<T, U, R, std::void_t< ModulationResult<T, U> > > : std::is_same<ModulationResult<T, U>, R> {};
		///	算術演算子 @a T::operator~() の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class = std::void_t<>> struct ArithmeticNotResultIsSame_t : std::false_type {};
		template<class T, class R> struct ArithmeticNotResultIsSame_t<T, R, std::void_t< ArithmeticNotResult<T> > > : std::is_same<ArithmeticNotResult<T>, R> {};
		///	算術演算子 @a T::operator&(U) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct ArithmeticAndResultIsSame_t : std::false_type {};
		template<class T, class U, class R> struct ArithmeticAndResultIsSame_t<T, U, R, std::void_t< ArithmeticAndResult<T, U> > > : std::is_same<ArithmeticAndResult<T, U>, R> {};
		///	算術演算子 @a T::operator|(U) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct ArithmeticOrResultIsSame_t : std::false_type {};
		template<class T, class U, class R> struct ArithmeticOrResultIsSame_t<T, U, R, std::void_t< ArithmeticOrResult<T, U> > > : std::is_same<ArithmeticOrResult<T, U>, R> {};
		///	算術演算子 @a T::operator^(U) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct ArithmeticXorResultIsSame_t : std::false_type {};
		template<class T, class U, class R> struct ArithmeticXorResultIsSame_t<T, U, R, std::void_t< ArithmeticXorResult<T, U> > > : std::is_same<ArithmeticXorResult<T, U>, R> {};
		///	算術演算子 @a T::operator<<(U) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct LShiftResultIsSame_t : std::false_type {};
		template<class T, class U, class R> struct LShiftResultIsSame_t<T, U, R, std::void_t< LShiftResult<T, U> > > : std::is_same<LShiftResult<T, U>, R> {};
		///	算術演算子 @a T::operator>>(U) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct RShiftResultIsSame_t : std::false_type {};
		template<class T, class U, class R> struct RShiftResultIsSame_t<T, U, R, std::void_t< RShiftResult<T, U> > > : std::is_same<RShiftResult<T, U>, R> {};
		///	論理演算子 @a T::operator!() の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class = std::void_t<>> struct LogicalNotResultIsSame_t : std::false_type {};
		template<class T, class R> struct LogicalNotResultIsSame_t<T, R, std::void_t< LogicalNotResult<T> > > : std::is_same<LogicalNotResult<T>, R> {};
		///	論理演算子 @a T::operator&&(U) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct LogicalOrResultIsSame_t : std::false_type {};
		template<class T, class U, class R> struct LogicalOrResultIsSame_t<T, U, R, std::void_t< LogicalOrResult<T, U> > > : std::is_same<LogicalOrResult<T, U>, R> {};
		///	論理演算子 @a T::operator||(U) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct LogicalAndResultIsSame_t : std::false_type {};
		template<class T, class U, class R> struct LogicalAndResultIsSame_t<T, U, R, std::void_t< LogicalAndResult<T, U> > > : std::is_same<LogicalAndResult<T, U>, R> {};
		///	比較演算子 @a T::operator==(U) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct EqualResultIsSame_t : std::false_type {};
		template<class T, class U, class R> struct EqualResultIsSame_t<T, U, R, std::void_t< EqualResult<T, U> > > : std::is_same<EqualResult<T, U>, R> {};
		///	比較演算子 @a T::operator!=(U) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct NotEqualResultIsSame_t : std::false_type {};
		template<class T, class U, class R> struct NotEqualResultIsSame_t<T, U, R, std::void_t< NotEqualResult<T, U> > > : std::is_same<NotEqualResult<T, U>, R> {};
		///	比較演算子 @a T::operator>(U) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct LargerCompareResultIsSame_t : std::false_type {};
		template<class T, class U, class R> struct LargerCompareResultIsSame_t<T, U, R, std::void_t< LargerCompareResult<T, U> > > : std::is_same<LargerCompareResult<T, U>, R> {};
		///	比較演算子 @a T::operator<(U) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SmallerCompareResultIsSame_t : std::false_type {};
		template<class T, class U, class R> struct SmallerCompareResultIsSame_t<T, U, R, std::void_t< SmallerCompareResult<T, U> > > : std::is_same<SmallerCompareResult<T, U>, R> {};
		///	比較演算子 @a T::operator>=(U) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct LeastCompareResultIsSame_t : std::false_type {};
		template<class T, class U, class R> struct LeastCompareResultIsSame_t<T, U, R, std::void_t< LeastCompareResult<T, U> > > : std::is_same<LeastCompareResult<T, U>, R> {};
		///	比較演算子 @a T::operator<=(U) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct MostCompareResultIsSame_t : std::false_type {};
		template<class T, class U, class R> struct MostCompareResultIsSame_t<T, U, R, std::void_t< MostCompareResult<T, U> > > : std::is_same<MostCompareResult<T, U>, R> {};
		///	比較演算子 @a T::operator[](U) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubscriptResultIsSame_t : std::false_type {};
		template<class T, class U, class R> struct SubscriptResultIsSame_t<T, U, R, std::void_t< SubscriptResult<T, U> > > : std::is_same<SubscriptResult<T, U>, R> {};
		///	比較演算子 @a T::operator*() の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class = std::void_t<>> struct DereferenceResultIsSame_t : std::false_type {};
		template<class T, class R> struct DereferenceResultIsSame_t<T, R, std::void_t< DereferenceResult<T> > > : std::is_same<DereferenceResult<T>, R> {};
		///	比較演算子 @a T::operator&() の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class = std::void_t<>> struct ReferenceResultIsSame_t : std::false_type {};
		template<class T, class R> struct ReferenceResultIsSame_t<T, R, std::void_t< ReferenceResult<T> > > : std::is_same<ReferenceResult<T>, R> {};
		///	比較演算子 @a T::operator,(U) の返却型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct CommaResultIsSame_t : std::false_type {};
		template<class T, class U, class R> struct CommaResultIsSame_t<T, U, R, std::void_t< CommaResult<T, U> > > : std::is_same<CommaResult<T, U>, R> {};
	public:
		///	代入演算子 @a T::operator=(U) の返却型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionResultIsSame = SubstitutionResultIsSame_t<T, U, R>::value;
		///	代入演算子 @a T::operator+=(U) の返却型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionAddResultIsSame = SubstitutionAddResultIsSame_t<T, U, R>::value;
		///	代入演算子 @a T::operator-=(U) の返却型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionSubtractResultIsSame = SubstitutionSubtractResultIsSame_t<T, U, R>::value;
		///	代入演算子 @a T::operator*=(U) の返却型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionMultipleResultIsSame = SubstitutionMultipleResultIsSame_t<T, U, R>::value;
		///	代入演算子 @a T::operator/=(U) の返却型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionDivideResultIsSame = SubstitutionDivideResultIsSame_t<T, U, R>::value;
		///	代入演算子 @a T::operator%=(U) の返却型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionModulateResultIsSame = SubstitutionModulateResultIsSame_t<T, U, R>::value;
		///	代入演算子 @a T::operator&=(U) の返却型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionArithmeticAndResultIsSame = SubstitutionArithmeticAndResultIsSame_t<T, U, R>::value;
		///	代入演算子 @a T::operator|=(U) の返却型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionArithmeticOrResultIsSame = SubstitutionArithmeticOrResultIsSame_t<T, U, R>::value;
		///	代入演算子 @a T::operator^=(U) の返却型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionArithmeticXorResultIsSame = SubstitutionArithmeticXorResultIsSame_t<T, U, R>::value;
		///	代入演算子 @a T::operator<<=(U) の返却型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionLShiftResultIsSame = SubstitutionLShiftResultIsSame_t<T, U, R>::value;
		///	代入演算子 @a T::operator>>=(U) の返却型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionRShiftResultIsSame = SubstitutionRShiftResultIsSame_t<T, U, R>::value;
		///	前置インクリメント演算子 @a T::operator++() の返却型が指定されたものに一致するかを識別します。
		template<class T, class R> static constexpr bool PreincrementResultIsSame = PreincrementResultIsSame_t<T, R>::value;
		///	前置デクリメント演算子 @a T::operator--() の返却型が指定されたものに一致するかを識別します。
		template<class T, class R> static constexpr bool PredecrementResultIsSame = PredecrementResultIsSame_t<T, R>::value;
		///	後置インクリメント演算子 @a T::operator++(int) の返却型が指定されたものに一致するかを識別します。
		template<class T, class R> static constexpr bool PostincrementResultIsSame = PostincrementResultIsSame_t<T, R>::value;
		///	後置デクリメント演算子 @a T::operator--(int) の返却型が指定されたものに一致するかを識別します。
		template<class T, class R> static constexpr bool PostdecrementResultIsSame = PostdecrementResultIsSame_t<T, R>::value;
		///	算術演算子 @a T::operator+() の返却型が指定されたものに一致するかを識別します。
		template<class T, class R> static constexpr bool PromotionResultIsSame = PromotionResultIsSame_t<T, R>::value;
		///	算術演算子 @a T::operator-() の返却型が指定されたものに一致するかを識別します。
		template<class T, class R> static constexpr bool InverseResultIsSame = InverseResultIsSame_t<T, R>::value;
		///	算術演算子 @a T::operator+(U) の返却型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool AdditionResultIsSame = AdditionResultIsSame_t<T, U, R>::value;
		///	算術演算子 @a T::operator-(U) の返却型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool SubtractionResultIsSame = SubtractionResultIsSame_t<T, U, R>::value;
		///	算術演算子 @a T::operator*(U) の返却型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool MultiplicationResultIsSame = MultiplicationResultIsSame_t<T, U, R>::value;
		///	算術演算子 @a T::operator/(U) の返却型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool DivisionResultIsSame = DivisionResultIsSame_t<T, U, R>::value;
		///	算術演算子 @a T::operator%(U) の返却型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool ModulationResultIsSame = ModulationResultIsSame_t<T, U, R>::value;
		///	算術演算子 @a T::operator~() の返却型が指定されたものに一致するかを識別します。
		template<class T, class R> static constexpr bool ArithmeticNotResultIsSame = ArithmeticNotResultIsSame_t<T, R>::value;
		///	算術演算子 @a T::operator&(U) の返却型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool ArithmeticAndResultIsSame = ArithmeticAndResultIsSame_t<T, U, R>::value;
		///	算術演算子 @a T::operator|(U) の返却型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool ArithmeticOrResultIsSame = ArithmeticOrResultIsSame_t<T, U, R>::value;
		///	算術演算子 @a T::operator^(U) の返却型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool ArithmeticXorResultIsSame = ArithmeticXorResultIsSame_t<T, U, R>::value;
		///	算術演算子 @a T::operator<<(U) の返却型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool LShiftResultIsSame = LShiftResultIsSame_t<T, U, R>::value;
		///	算術演算子 @a T::operator>>(U) の返却型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool RShiftResultIsSame = RShiftResultIsSame_t<T, U, R>::value;
		///	論理演算子 @a T::operator!() の返却型が指定されたものに一致するかを識別します。
		template<class T, class R> static constexpr bool LogicalNotResultIsSame = LogicalNotResultIsSame_t<T, R>::value;
		///	論理演算子 @a T::operator&&(U) の返却型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool LogicalOrResultIsSame = LogicalOrResultIsSame_t<T, U, R>::value;
		///	論理演算子 @a T::operator||(U) の返却型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool LogicalAndResultIsSame = LogicalAndResultIsSame_t<T, U, R>::value;
		///	比較演算子 @a T::operator==(U) の返却型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool EqualResultIsSame = EqualResultIsSame_t<T, U, R>::value;
		///	比較演算子 @a T::operator!=(U) の返却型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool NotEqualResultIsSame = NotEqualResultIsSame_t<T, U, R>::value;
		///	比較演算子 @a T::operator>(U) の返却型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool LargerCompareResultIsSame = LargerCompareResultIsSame_t<T, U, R>::value;
		///	比較演算子 @a T::operator<(U) の返却型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool SmallerCompareResultIsSame = SmallerCompareResultIsSame_t<T, U, R>::value;
		///	比較演算子 @a T::operator>=(U) の返却型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool LeastCompareResultIsSame = LeastCompareResultIsSame_t<T, U, R>::value;
		///	比較演算子 @a T::operator<=(U) の返却型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool MostCompareResultIsSame = MostCompareResultIsSame_t<T, U, R>::value;
		///	比較演算子 @a T::operator[](U) の返却型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool SubscriptResultIsSame = SubscriptResultIsSame_t<T, U, R>::value;
		///	比較演算子 @a T::operator*() の返却型が指定されたものに一致するかを識別します。
		template<class T, class R> static constexpr bool DereferenceResultIsSame = DereferenceResultIsSame_t<T, R>::value;
		///	比較演算子 @a T::operator&() の返却型が指定されたものに一致するかを識別します。
		template<class T, class R> static constexpr bool ReferenceResultIsSame = ReferenceResultIsSame_t<T, R>::value;
		///	比較演算子 @a T::operator,(U) の返却型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool CommaResultIsSame = CommaResultIsSame_t<T, U, R>::value;
	private:
		///	代入演算子 @a T::operator=(U) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionResultIsConvertible_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionResultIsConvertible_t<T, U, R, std::void_t< SubstitutionResult<T, U> > > : std::is_convertible<SubstitutionResult<T, U>, R> {};
		///	代入演算子 @a T::operator+=(U) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionAddResultIsConvertible_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionAddResultIsConvertible_t<T, U, R, std::void_t< SubstitutionAddResult<T, U> > > : std::is_convertible<SubstitutionAddResult<T, U>, R> {};
		///	代入演算子 @a T::operator-=(U) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionSubtractResultIsConvertible_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionSubtractResultIsConvertible_t<T, U, R, std::void_t< SubstitutionSubtractResult<T, U> > > : std::is_convertible<SubstitutionSubtractResult<T, U>, R> {};
		///	代入演算子 @a T::operator*=(U) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionMultipleResultIsConvertible_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionMultipleResultIsConvertible_t<T, U, R, std::void_t< SubstitutionMultipleResult<T, U> > > : std::is_convertible<SubstitutionMultipleResult<T, U>, R> {};
		///	代入演算子 @a T::operator/=(U) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionDivideResultIsConvertible_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionDivideResultIsConvertible_t<T, U, R, std::void_t< SubstitutionDivideResult<T, U> > > : std::is_convertible<SubstitutionDivideResult<T, U>, R> {};
		///	代入演算子 @a T::operator%=(U) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionModulateResultIsConvertible_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionModulateResultIsConvertible_t<T, U, R, std::void_t< SubstitutionModulateResult<T, U> > > : std::is_convertible<SubstitutionModulateResult<T, U>, R> {};
		///	代入演算子 @a T::operator&=(U) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionArithmeticAndResultIsConvertible_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionArithmeticAndResultIsConvertible_t<T, U, R, std::void_t< SubstitutionArithmeticAndResult<T, U> > > : std::is_convertible<SubstitutionArithmeticAndResult<T, U>, R> {};
		///	代入演算子 @a T::operator|=(U) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionArithmeticOrResultIsConvertible_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionArithmeticOrResultIsConvertible_t<T, U, R, std::void_t< SubstitutionArithmeticOrResult<T, U> > > : std::is_convertible<SubstitutionArithmeticOrResult<T, U>, R> {};
		///	代入演算子 @a T::operator^=(U) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionArithmeticXorResultIsConvertible_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionArithmeticXorResultIsConvertible_t<T, U, R, std::void_t< SubstitutionArithmeticXorResult<T, U> > > : std::is_convertible<SubstitutionArithmeticXorResult<T, U>, R> {};
		///	代入演算子 @a T::operator<<=(U) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionLShiftResultIsConvertible_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionLShiftResultIsConvertible_t<T, U, R, std::void_t< SubstitutionLShiftResult<T, U> > > : std::is_convertible<SubstitutionLShiftResult<T, U>, R> {};
		///	代入演算子 @a T::operator>>=(U) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionRShiftResultIsConvertible_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionRShiftResultIsConvertible_t<T, U, R, std::void_t< SubstitutionRShiftResult<T, U> > > : std::is_convertible<SubstitutionRShiftResult<T, U>, R> {};
		///	前置インクリメント演算子 @a T::operator++() の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class = std::void_t<>> struct PreincrementResultIsConvertible_t : std::false_type {};
		template<class T, class R> struct PreincrementResultIsConvertible_t<T, R, std::void_t< PreincrementResult<T> > > : std::is_convertible<PreincrementResult<T>, R> {};
		#if 201703L <= __cplusplus
		// Clang C++17でコンパイルするとbool::operator++()を実体化しようとしてエラーを吐くため
		// boolによるインクリメントトレイトは強制的にfalseで実体化する
		template<class R> struct PreincrementResultIsConvertible_t<bool, R> : std::false_type {};
		#endif
		///	前置デクリメント演算子 @a T::operator--() の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class = std::void_t<>> struct PredecrementResultIsConvertible_t : std::false_type {};
		template<class T, class R> struct PredecrementResultIsConvertible_t<T, R, std::void_t< PredecrementResult<T> > > : std::is_convertible<PredecrementResult<T>, R> {};
		///	後置インクリメント演算子 @a T::operator++(int) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class = std::void_t<>> struct PostincrementResultIsConvertible_t : std::false_type {};
		template<class T, class R> struct PostincrementResultIsConvertible_t<T, R, std::void_t< PostincrementResult<T> > > : std::is_convertible<PostincrementResult<T>, R> {};
		#if 201703L <= __cplusplus
		// Clang C++17でコンパイルするとbool::operator++(int)を実体化しようとしてエラーを吐くため
		// boolによるインクリメントトレイトは強制的にfalseで実体化する
		template<class R> struct PostincrementResultIsConvertible_t<bool, R> : std::false_type {};
		#endif
		///	後置デクリメント演算子 @a T::operator--(int) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class = std::void_t<>> struct PostdecrementResultIsConvertible_t : std::false_type {};
		template<class T, class R> struct PostdecrementResultIsConvertible_t<T, R, std::void_t< PostdecrementResult<T> > > : std::is_convertible<PostdecrementResult<T>, R> {};
		///	算術演算子 @a T::operator+() の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class = std::void_t<>> struct PromotionResultIsConvertible_t : std::false_type {};
		template<class T, class R> struct PromotionResultIsConvertible_t<T, R, std::void_t< PromotionResult<T> > > : std::is_convertible<PromotionResult<T>, R> {};
		///	算術演算子 @a T::operator-() の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class = std::void_t<>> struct InverseResultIsConvertible_t : std::false_type {};
		template<class T, class R> struct InverseResultIsConvertible_t<T, R, std::void_t< InverseResult<T> > > : std::is_convertible<InverseResult<T>, R> {};
		///	算術演算子 @a T::operator+(U) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct AdditionResultIsConvertible_t : std::false_type {};
		template<class T, class U, class R> struct AdditionResultIsConvertible_t<T, U, R, std::void_t< AdditionResult<T, U> > > : std::is_convertible<AdditionResult<T, U>, R> {};
		///	算術演算子 @a T::operator-(U) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubtractionResultIsConvertible_t : std::false_type {};
		template<class T, class U, class R> struct SubtractionResultIsConvertible_t<T, U, R, std::void_t< SubtractionResult<T, U> > > : std::is_convertible<SubtractionResult<T, U>, R> {};
		///	算術演算子 @a T::operator*(U) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct MultiplicationResultIsConvertible_t : std::false_type {};
		template<class T, class U, class R> struct MultiplicationResultIsConvertible_t<T, U, R, std::void_t< MultiplicationResult<T, U> > > : std::is_convertible<MultiplicationResult<T, U>, R> {};
		///	算術演算子 @a T::operator/(U) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct DivisionResultIsConvertible_t : std::false_type {};
		template<class T, class U, class R> struct DivisionResultIsConvertible_t<T, U, R, std::void_t< DivisionResult<T, U> > > : std::is_convertible<DivisionResult<T, U>, R> {};
		///	算術演算子 @a T::operator%(U) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct ModulationResultIsConvertible_t : std::false_type {};
		template<class T, class U, class R> struct ModulationResultIsConvertible_t<T, U, R, std::void_t< ModulationResult<T, U> > > : std::is_convertible<ModulationResult<T, U>, R> {};
		///	算術演算子 @a T::operator~() の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class = std::void_t<>> struct ArithmeticNotResultIsConvertible_t : std::false_type {};
		template<class T, class R> struct ArithmeticNotResultIsConvertible_t<T, R, std::void_t< ArithmeticNotResult<T> > > : std::is_convertible<ArithmeticNotResult<T>, R> {};
		///	算術演算子 @a T::operator&(U) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct ArithmeticAndResultIsConvertible_t : std::false_type {};
		template<class T, class U, class R> struct ArithmeticAndResultIsConvertible_t<T, U, R, std::void_t< ArithmeticAndResult<T, U> > > : std::is_convertible<ArithmeticAndResult<T, U>, R> {};
		///	算術演算子 @a T::operator|(U) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct ArithmeticOrResultIsConvertible_t : std::false_type {};
		template<class T, class U, class R> struct ArithmeticOrResultIsConvertible_t<T, U, R, std::void_t< ArithmeticOrResult<T, U> > > : std::is_convertible<ArithmeticOrResult<T, U>, R> {};
		///	算術演算子 @a T::operator^(U) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct ArithmeticXorResultIsConvertible_t : std::false_type {};
		template<class T, class U, class R> struct ArithmeticXorResultIsConvertible_t<T, U, R, std::void_t< ArithmeticXorResult<T, U> > > : std::is_convertible<ArithmeticXorResult<T, U>, R> {};
		///	算術演算子 @a T::operator<<(U) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct LShiftResultIsConvertible_t : std::false_type {};
		template<class T, class U, class R> struct LShiftResultIsConvertible_t<T, U, R, std::void_t< LShiftResult<T, U> > > : std::is_convertible<LShiftResult<T, U>, R> {};
		///	算術演算子 @a T::operator>>(U) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct RShiftResultIsConvertible_t : std::false_type {};
		template<class T, class U, class R> struct RShiftResultIsConvertible_t<T, U, R, std::void_t< RShiftResult<T, U> > > : std::is_convertible<RShiftResult<T, U>, R> {};
		///	論理演算子 @a T::operator!() の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class = std::void_t<>> struct LogicalNotResultIsConvertible_t : std::false_type {};
		template<class T, class R> struct LogicalNotResultIsConvertible_t<T, R, std::void_t< LogicalNotResult<T> > > : std::is_convertible<LogicalNotResult<T>, R> {};
		///	論理演算子 @a T::operator&&(U) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct LogicalOrResultIsConvertible_t : std::false_type {};
		template<class T, class U, class R> struct LogicalOrResultIsConvertible_t<T, U, R, std::void_t< LogicalOrResult<T, U> > > : std::is_convertible<LogicalOrResult<T, U>, R> {};
		///	論理演算子 @a T::operator||(U) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct LogicalAndResultIsConvertible_t : std::false_type {};
		template<class T, class U, class R> struct LogicalAndResultIsConvertible_t<T, U, R, std::void_t< LogicalAndResult<T, U> > > : std::is_convertible<LogicalAndResult<T, U>, R> {};
		///	比較演算子 @a T::operator==(U) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct EqualResultIsConvertible_t : std::false_type {};
		template<class T, class U, class R> struct EqualResultIsConvertible_t<T, U, R, std::void_t< EqualResult<T, U> > > : std::is_convertible<EqualResult<T, U>, R> {};
		///	比較演算子 @a T::operator!=(U) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct NotEqualResultIsConvertible_t : std::false_type {};
		template<class T, class U, class R> struct NotEqualResultIsConvertible_t<T, U, R, std::void_t< NotEqualResult<T, U> > > : std::is_convertible<NotEqualResult<T, U>, R> {};
		///	比較演算子 @a T::operator>(U) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct LargerCompareResultIsConvertible_t : std::false_type {};
		template<class T, class U, class R> struct LargerCompareResultIsConvertible_t<T, U, R, std::void_t< LargerCompareResult<T, U> > > : std::is_convertible<LargerCompareResult<T, U>, R> {};
		///	比較演算子 @a T::operator<(U) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SmallerCompareResultIsConvertible_t : std::false_type {};
		template<class T, class U, class R> struct SmallerCompareResultIsConvertible_t<T, U, R, std::void_t< SmallerCompareResult<T, U> > > : std::is_convertible<SmallerCompareResult<T, U>, R> {};
		///	比較演算子 @a T::operator>=(U) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct LeastCompareResultIsConvertible_t : std::false_type {};
		template<class T, class U, class R> struct LeastCompareResultIsConvertible_t<T, U, R, std::void_t< LeastCompareResult<T, U> > > : std::is_convertible<LeastCompareResult<T, U>, R> {};
		///	比較演算子 @a T::operator<=(U) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct MostCompareResultIsConvertible_t : std::false_type {};
		template<class T, class U, class R> struct MostCompareResultIsConvertible_t<T, U, R, std::void_t< MostCompareResult<T, U> > > : std::is_convertible<MostCompareResult<T, U>, R> {};
		///	比較演算子 @a T::operator[](U) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubscriptResultIsConvertible_t : std::false_type {};
		template<class T, class U, class R> struct SubscriptResultIsConvertible_t<T, U, R, std::void_t< SubscriptResult<T, U> > > : std::is_convertible<SubscriptResult<T, U>, R> {};
		///	比較演算子 @a T::operator*() の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class = std::void_t<>> struct DereferenceResultIsConvertible_t : std::false_type {};
		template<class T, class R> struct DereferenceResultIsConvertible_t<T, R, std::void_t< DereferenceResult<T> > > : std::is_convertible<DereferenceResult<T>, R> {};
		///	比較演算子 @a T::operator&() の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class = std::void_t<>> struct ReferenceResultIsConvertible_t : std::false_type {};
		template<class T, class R> struct ReferenceResultIsConvertible_t<T, R, std::void_t< ReferenceResult<T> > > : std::is_convertible<ReferenceResult<T>, R> {};
		///	比較演算子 @a T::operator,(U) の返却型が指定されたものに変換可能かを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct CommaResultIsConvertible_t : std::false_type {};
		template<class T, class U, class R> struct CommaResultIsConvertible_t<T, U, R, std::void_t< CommaResult<T, U> > > : std::is_convertible<CommaResult<T, U>, R> {};
	public:
		///	代入演算子 @a T::operator=(U) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionResultIsConvertible = SubstitutionResultIsConvertible_t<T, U, R>::value;
		///	代入演算子 @a T::operator+=(U) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionAddResultIsConvertible = SubstitutionAddResultIsConvertible_t<T, U, R>::value;
		///	代入演算子 @a T::operator-=(U) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionSubtractResultIsConvertible = SubstitutionSubtractResultIsConvertible_t<T, U, R>::value;
		///	代入演算子 @a T::operator*=(U) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionMultipleResultIsConvertible = SubstitutionMultipleResultIsConvertible_t<T, U, R>::value;
		///	代入演算子 @a T::operator/=(U) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionDivideResultIsConvertible = SubstitutionDivideResultIsConvertible_t<T, U, R>::value;
		///	代入演算子 @a T::operator%=(U) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionModulateResultIsConvertible = SubstitutionModulateResultIsConvertible_t<T, U, R>::value;
		///	代入演算子 @a T::operator&=(U) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionArithmeticAndResultIsConvertible = SubstitutionArithmeticAndResultIsConvertible_t<T, U, R>::value;
		///	代入演算子 @a T::operator|=(U) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionArithmeticOrResultIsConvertible = SubstitutionArithmeticOrResultIsConvertible_t<T, U, R>::value;
		///	代入演算子 @a T::operator^=(U) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionArithmeticXorResultIsConvertible = SubstitutionArithmeticXorResultIsConvertible_t<T, U, R>::value;
		///	代入演算子 @a T::operator<<=(U) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionLShiftResultIsConvertible = SubstitutionLShiftResultIsConvertible_t<T, U, R>::value;
		///	代入演算子 @a T::operator>>=(U) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionRShiftResultIsConvertible = SubstitutionRShiftResultIsConvertible_t<T, U, R>::value;
		///	前置インクリメント演算子 @a T::operator++() の返却型が指定されたものに変換可能かを識別します。
		template<class T, class R> static constexpr bool PreincrementResultIsConvertible = PreincrementResultIsConvertible_t<T, R>::value;
		///	前置デクリメント演算子 @a T::operator--() の返却型が指定されたものに変換可能かを識別します。
		template<class T, class R> static constexpr bool PredecrementResultIsConvertible = PredecrementResultIsConvertible_t<T, R>::value;
		///	後置インクリメント演算子 @a T::operator++(int) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class R> static constexpr bool PostincrementResultIsConvertible = PostincrementResultIsConvertible_t<T, R>::value;
		///	後置デクリメント演算子 @a T::operator--(int) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class R> static constexpr bool PostdecrementResultIsConvertible = PostdecrementResultIsConvertible_t<T, R>::value;
		///	算術演算子 @a T::operator+() の返却型が指定されたものに変換可能かを識別します。
		template<class T, class R> static constexpr bool PromotionResultIsConvertible = PromotionResultIsConvertible_t<T, R>::value;
		///	算術演算子 @a T::operator-() の返却型が指定されたものに変換可能かを識別します。
		template<class T, class R> static constexpr bool InverseResultIsConvertible = InverseResultIsConvertible_t<T, R>::value;
		///	算術演算子 @a T::operator+(U) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class U, class R> static constexpr bool AdditionResultIsConvertible = AdditionResultIsConvertible_t<T, U, R>::value;
		///	算術演算子 @a T::operator-(U) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class U, class R> static constexpr bool SubtractionResultIsConvertible = SubtractionResultIsConvertible_t<T, U, R>::value;
		///	算術演算子 @a T::operator*(U) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class U, class R> static constexpr bool MultiplicationResultIsConvertible = MultiplicationResultIsConvertible_t<T, U, R>::value;
		///	算術演算子 @a T::operator/(U) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class U, class R> static constexpr bool DivisionResultIsConvertible = DivisionResultIsConvertible_t<T, U, R>::value;
		///	算術演算子 @a T::operator%(U) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class U, class R> static constexpr bool ModulationResultIsConvertible = ModulationResultIsConvertible_t<T, U, R>::value;
		///	算術演算子 @a T::operator~() の返却型が指定されたものに変換可能かを識別します。
		template<class T, class R> static constexpr bool ArithmeticNotResultIsConvertible = ArithmeticNotResultIsConvertible_t<T, R>::value;
		///	算術演算子 @a T::operator&(U) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class U, class R> static constexpr bool ArithmeticAndResultIsConvertible = ArithmeticAndResultIsConvertible_t<T, U, R>::value;
		///	算術演算子 @a T::operator|(U) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class U, class R> static constexpr bool ArithmeticOrResultIsConvertible = ArithmeticOrResultIsConvertible_t<T, U, R>::value;
		///	算術演算子 @a T::operator^(U) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class U, class R> static constexpr bool ArithmeticXorResultIsConvertible = ArithmeticXorResultIsConvertible_t<T, U, R>::value;
		///	算術演算子 @a T::operator<<(U) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class U, class R> static constexpr bool LShiftResultIsConvertible = LShiftResultIsConvertible_t<T, U, R>::value;
		///	算術演算子 @a T::operator>>(U) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class U, class R> static constexpr bool RShiftResultIsConvertible = RShiftResultIsConvertible_t<T, U, R>::value;
		///	論理演算子 @a T::operator!() の返却型が指定されたものに変換可能かを識別します。
		template<class T, class R> static constexpr bool LogicalNotResultIsConvertible = LogicalNotResultIsConvertible_t<T, R>::value;
		///	論理演算子 @a T::operator&&(U) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class U, class R> static constexpr bool LogicalOrResultIsConvertible = LogicalOrResultIsConvertible_t<T, U, R>::value;
		///	論理演算子 @a T::operator||(U) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class U, class R> static constexpr bool LogicalAndResultIsConvertible = LogicalAndResultIsConvertible_t<T, U, R>::value;
		///	比較演算子 @a T::operator==(U) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class U, class R> static constexpr bool EqualResultIsConvertible = EqualResultIsConvertible_t<T, U, R>::value;
		///	比較演算子 @a T::operator!=(U) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class U, class R> static constexpr bool NotEqualResultIsConvertible = NotEqualResultIsConvertible_t<T, U, R>::value;
		///	比較演算子 @a T::operator>(U) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class U, class R> static constexpr bool LargerCompareResultIsConvertible = LargerCompareResultIsConvertible_t<T, U, R>::value;
		///	比較演算子 @a T::operator<(U) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class U, class R> static constexpr bool SmallerCompareResultIsConvertible = SmallerCompareResultIsConvertible_t<T, U, R>::value;
		///	比較演算子 @a T::operator>=(U) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class U, class R> static constexpr bool LeastCompareResultIsConvertible = LeastCompareResultIsConvertible_t<T, U, R>::value;
		///	比較演算子 @a T::operator<=(U) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class U, class R> static constexpr bool MostCompareResultIsConvertible = MostCompareResultIsConvertible_t<T, U, R>::value;
		///	比較演算子 @a T::operator[](U) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class U, class R> static constexpr bool SubscriptResultIsConvertible = SubscriptResultIsConvertible_t<T, U, R>::value;
		///	比較演算子 @a T::operator*() の返却型が指定されたものに変換可能かを識別します。
		template<class T, class R> static constexpr bool DereferenceResultIsConvertible = DereferenceResultIsConvertible_t<T, R>::value;
		///	比較演算子 @a T::operator&() の返却型が指定されたものに変換可能かを識別します。
		template<class T, class R> static constexpr bool ReferenceResultIsConvertible = ReferenceResultIsConvertible_t<T, R>::value;
		///	比較演算子 @a T::operator,(U) の返却型が指定されたものに変換可能かを識別します。
		template<class T, class U, class R> static constexpr bool CommaResultIsConvertible = CommaResultIsConvertible_t<T, U, R>::value;
	private:
		///	代入演算子 @a T::operator=(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionResultRemoveCVRefIsSame_t<T, U, R, std::void_t< SubstitutionResult<T, U> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<SubstitutionResult<T, U>>>, R> {};
		///	代入演算子 @a T::operator+=(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionAddResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionAddResultRemoveCVRefIsSame_t<T, U, R, std::void_t< SubstitutionAddResult<T, U> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<SubstitutionAddResult<T, U>>>, R> {};
		///	代入演算子 @a T::operator-=(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionSubtractResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionSubtractResultRemoveCVRefIsSame_t<T, U, R, std::void_t< SubstitutionSubtractResult<T, U> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<SubstitutionSubtractResult<T, U>>>, R> {};
		///	代入演算子 @a T::operator*=(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionMultipleResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionMultipleResultRemoveCVRefIsSame_t<T, U, R, std::void_t< SubstitutionMultipleResult<T, U> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<SubstitutionMultipleResult<T, U>>>, R> {};
		///	代入演算子 @a T::operator/=(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionDivideResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionDivideResultRemoveCVRefIsSame_t<T, U, R, std::void_t< SubstitutionDivideResult<T, U> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<SubstitutionDivideResult<T, U>>>, R> {};
		///	代入演算子 @a T::operator%=(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionModulateResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionModulateResultRemoveCVRefIsSame_t<T, U, R, std::void_t< SubstitutionModulateResult<T, U> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<SubstitutionModulateResult<T, U>>>, R> {};
		///	代入演算子 @a T::operator&=(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionArithmeticAndResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionArithmeticAndResultRemoveCVRefIsSame_t<T, U, R, std::void_t< SubstitutionArithmeticAndResult<T, U> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<SubstitutionArithmeticAndResult<T, U>>>, R> {};
		///	代入演算子 @a T::operator|=(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionArithmeticOrResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionArithmeticOrResultRemoveCVRefIsSame_t<T, U, R, std::void_t< SubstitutionArithmeticOrResult<T, U> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<SubstitutionArithmeticOrResult<T, U>>>, R> {};
		///	代入演算子 @a T::operator^=(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionArithmeticXorResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionArithmeticXorResultRemoveCVRefIsSame_t<T, U, R, std::void_t< SubstitutionArithmeticXorResult<T, U> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<SubstitutionArithmeticXorResult<T, U>>>, R> {};
		///	代入演算子 @a T::operator<<=(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionLShiftResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionLShiftResultRemoveCVRefIsSame_t<T, U, R, std::void_t< SubstitutionLShiftResult<T, U> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<SubstitutionLShiftResult<T, U>>>, R> {};
		///	代入演算子 @a T::operator>>=(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubstitutionRShiftResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class U, class R> struct SubstitutionRShiftResultRemoveCVRefIsSame_t<T, U, R, std::void_t< SubstitutionRShiftResult<T, U> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<SubstitutionRShiftResult<T, U>>>, R> {};
		///	前置インクリメント演算子 @a T::operator++() の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class = std::void_t<>> struct PreincrementResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class R> struct PreincrementResultRemoveCVRefIsSame_t<T, R, std::void_t< PreincrementResult<T> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<PreincrementResult<T>>>, R> {};
		#if 201703L <= __cplusplus
		// Clang C++17でコンパイルするとbool::operator++()を実体化しようとしてエラーを吐くため
		// boolによるインクリメントトレイトは強制的にfalseで実体化する
		template<class R> struct PreincrementResultRemoveCVRefIsSame_t<bool, R> : std::false_type {};
		#endif
		///	前置デクリメント演算子 @a T::operator--() の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class = std::void_t<>> struct PredecrementResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class R> struct PredecrementResultRemoveCVRefIsSame_t<T, R, std::void_t< PredecrementResult<T> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<PredecrementResult<T>>>, R> {};
		///	後置インクリメント演算子 @a T::operator++(int) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class = std::void_t<>> struct PostincrementResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class R> struct PostincrementResultRemoveCVRefIsSame_t<T, R, std::void_t< PostincrementResult<T> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<PostincrementResult<T>>>, R> {};
		#if 201703L <= __cplusplus
		// Clang C++17でコンパイルするとbool::operator++(int)を実体化しようとしてエラーを吐くため
		// boolによるインクリメントトレイトは強制的にfalseで実体化する
		template<class R> struct PostincrementResultRemoveCVRefIsSame_t<bool, R> : std::false_type {};
		#endif
		///	後置デクリメント演算子 @a T::operator--(int) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class = std::void_t<>> struct PostdecrementResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class R> struct PostdecrementResultRemoveCVRefIsSame_t<T, R, std::void_t< PostdecrementResult<T> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<PostdecrementResult<T>>>, R> {};
		///	算術演算子 @a T::operator+() の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class = std::void_t<>> struct PromotionResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class R> struct PromotionResultRemoveCVRefIsSame_t<T, R, std::void_t< PromotionResult<T> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<PromotionResult<T>>>, R> {};
		///	算術演算子 @a T::operator-() の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class = std::void_t<>> struct InverseResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class R> struct InverseResultRemoveCVRefIsSame_t<T, R, std::void_t< InverseResult<T> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<InverseResult<T>>>, R> {};
		///	算術演算子 @a T::operator+(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct AdditionResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class U, class R> struct AdditionResultRemoveCVRefIsSame_t<T, U, R, std::void_t< AdditionResult<T, U> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<AdditionResult<T, U>>>, R> {};
		///	算術演算子 @a T::operator-(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubtractionResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class U, class R> struct SubtractionResultRemoveCVRefIsSame_t<T, U, R, std::void_t< SubtractionResult<T, U> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<SubtractionResult<T, U>>>, R> {};
		///	算術演算子 @a T::operator*(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct MultiplicationResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class U, class R> struct MultiplicationResultRemoveCVRefIsSame_t<T, U, R, std::void_t< MultiplicationResult<T, U> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<MultiplicationResult<T, U>>>, R> {};
		///	算術演算子 @a T::operator/(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct DivisionResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class U, class R> struct DivisionResultRemoveCVRefIsSame_t<T, U, R, std::void_t< DivisionResult<T, U> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<DivisionResult<T, U>>>, R> {};
		///	算術演算子 @a T::operator%(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct ModulationResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class U, class R> struct ModulationResultRemoveCVRefIsSame_t<T, U, R, std::void_t< ModulationResult<T, U> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<ModulationResult<T, U>>>, R> {};
		///	算術演算子 @a T::operator~() の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class = std::void_t<>> struct ArithmeticNotResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class R> struct ArithmeticNotResultRemoveCVRefIsSame_t<T, R, std::void_t< ArithmeticNotResult<T> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<ArithmeticNotResult<T>>>, R> {};
		///	算術演算子 @a T::operator&(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct ArithmeticAndResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class U, class R> struct ArithmeticAndResultRemoveCVRefIsSame_t<T, U, R, std::void_t< ArithmeticAndResult<T, U> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<ArithmeticAndResult<T, U>>>, R> {};
		///	算術演算子 @a T::operator|(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct ArithmeticOrResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class U, class R> struct ArithmeticOrResultRemoveCVRefIsSame_t<T, U, R, std::void_t< ArithmeticOrResult<T, U> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<ArithmeticOrResult<T, U>>>, R> {};
		///	算術演算子 @a T::operator^(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct ArithmeticXorResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class U, class R> struct ArithmeticXorResultRemoveCVRefIsSame_t<T, U, R, std::void_t< ArithmeticXorResult<T, U> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<ArithmeticXorResult<T, U>>>, R> {};
		///	算術演算子 @a T::operator<<(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct LShiftResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class U, class R> struct LShiftResultRemoveCVRefIsSame_t<T, U, R, std::void_t< LShiftResult<T, U> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<LShiftResult<T, U>>>, R> {};
		///	算術演算子 @a T::operator>>(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct RShiftResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class U, class R> struct RShiftResultRemoveCVRefIsSame_t<T, U, R, std::void_t< RShiftResult<T, U> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<RShiftResult<T, U>>>, R> {};
		///	論理演算子 @a T::operator!() の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class = std::void_t<>> struct LogicalNotResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class R> struct LogicalNotResultRemoveCVRefIsSame_t<T, R, std::void_t< LogicalNotResult<T> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<LogicalNotResult<T>>>, R> {};
		///	論理演算子 @a T::operator&&(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct LogicalOrResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class U, class R> struct LogicalOrResultRemoveCVRefIsSame_t<T, U, R, std::void_t< LogicalOrResult<T, U> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<LogicalOrResult<T, U>>>, R> {};
		///	論理演算子 @a T::operator||(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct LogicalAndResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class U, class R> struct LogicalAndResultRemoveCVRefIsSame_t<T, U, R, std::void_t< LogicalAndResult<T, U> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<LogicalAndResult<T, U>>>, R> {};
		///	比較演算子 @a T::operator==(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct EqualResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class U, class R> struct EqualResultRemoveCVRefIsSame_t<T, U, R, std::void_t< EqualResult<T, U> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<EqualResult<T, U>>>, R> {};
		///	比較演算子 @a T::operator!=(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct NotEqualResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class U, class R> struct NotEqualResultRemoveCVRefIsSame_t<T, U, R, std::void_t< NotEqualResult<T, U> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<NotEqualResult<T, U>>>, R> {};
		///	比較演算子 @a T::operator>(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct LargerCompareResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class U, class R> struct LargerCompareResultRemoveCVRefIsSame_t<T, U, R, std::void_t< LargerCompareResult<T, U> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<LargerCompareResult<T, U>>>, R> {};
		///	比較演算子 @a T::operator<(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SmallerCompareResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class U, class R> struct SmallerCompareResultRemoveCVRefIsSame_t<T, U, R, std::void_t< SmallerCompareResult<T, U> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<SmallerCompareResult<T, U>>>, R> {};
		///	比較演算子 @a T::operator>=(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct LeastCompareResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class U, class R> struct LeastCompareResultRemoveCVRefIsSame_t<T, U, R, std::void_t< LeastCompareResult<T, U> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<LeastCompareResult<T, U>>>, R> {};
		///	比較演算子 @a T::operator<=(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct MostCompareResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class U, class R> struct MostCompareResultRemoveCVRefIsSame_t<T, U, R, std::void_t< MostCompareResult<T, U> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<MostCompareResult<T, U>>>, R> {};
		///	比較演算子 @a T::operator[](U) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct SubscriptResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class U, class R> struct SubscriptResultRemoveCVRefIsSame_t<T, U, R, std::void_t< SubscriptResult<T, U> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<SubscriptResult<T, U>>>, R> {};
		///	比較演算子 @a T::operator*() の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class = std::void_t<>> struct DereferenceResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class R> struct DereferenceResultRemoveCVRefIsSame_t<T, R, std::void_t< DereferenceResult<T> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<DereferenceResult<T>>>, R> {};
		///	比較演算子 @a T::operator&() の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class = std::void_t<>> struct ReferenceResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class R> struct ReferenceResultRemoveCVRefIsSame_t<T, R, std::void_t< ReferenceResult<T> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<ReferenceResult<T>>>, R> {};
		///	比較演算子 @a T::operator,(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別するための実装。
		template<class, class, class, class = std::void_t<>> struct CommaResultRemoveCVRefIsSame_t : std::false_type {};
		template<class T, class U, class R> struct CommaResultRemoveCVRefIsSame_t<T, U, R, std::void_t< CommaResult<T, U> > > : std::is_same<std::remove_cv_t<std::remove_reference_t<CommaResult<T, U>>>, R> {};
	public:
		///	代入演算子 @a T::operator=(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionResultRemoveCVRefIsSame = SubstitutionResultRemoveCVRefIsSame_t<T, U, R>::value;
		///	代入演算子 @a T::operator+=(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionAddResultRemoveCVRefIsSame = SubstitutionAddResultRemoveCVRefIsSame_t<T, U, R>::value;
		///	代入演算子 @a T::operator-=(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionSubtractResultRemoveCVRefIsSame = SubstitutionSubtractResultRemoveCVRefIsSame_t<T, U, R>::value;
		///	代入演算子 @a T::operator*=(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionMultipleResultRemoveCVRefIsSame = SubstitutionMultipleResultRemoveCVRefIsSame_t<T, U, R>::value;
		///	代入演算子 @a T::operator/=(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionDivideResultRemoveCVRefIsSame = SubstitutionDivideResultRemoveCVRefIsSame_t<T, U, R>::value;
		///	代入演算子 @a T::operator%=(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionModulateResultRemoveCVRefIsSame = SubstitutionModulateResultRemoveCVRefIsSame_t<T, U, R>::value;
		///	代入演算子 @a T::operator&=(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionArithmeticAndResultRemoveCVRefIsSame = SubstitutionArithmeticAndResultRemoveCVRefIsSame_t<T, U, R>::value;
		///	代入演算子 @a T::operator|=(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionArithmeticOrResultRemoveCVRefIsSame = SubstitutionArithmeticOrResultRemoveCVRefIsSame_t<T, U, R>::value;
		///	代入演算子 @a T::operator^=(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionArithmeticXorResultRemoveCVRefIsSame = SubstitutionArithmeticXorResultRemoveCVRefIsSame_t<T, U, R>::value;
		///	代入演算子 @a T::operator<<=(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionLShiftResultRemoveCVRefIsSame = SubstitutionLShiftResultRemoveCVRefIsSame_t<T, U, R>::value;
		///	代入演算子 @a T::operator>>=(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool SubstitutionRShiftResultRemoveCVRefIsSame = SubstitutionRShiftResultRemoveCVRefIsSame_t<T, U, R>::value;
		///	前置インクリメント演算子 @a T::operator++() の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class R> static constexpr bool PreincrementResultRemoveCVRefIsSame = PreincrementResultRemoveCVRefIsSame_t<T, R>::value;
		///	前置デクリメント演算子 @a T::operator--() の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class R> static constexpr bool PredecrementResultRemoveCVRefIsSame = PredecrementResultRemoveCVRefIsSame_t<T, R>::value;
		///	後置インクリメント演算子 @a T::operator++(int) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class R> static constexpr bool PostincrementResultRemoveCVRefIsSame = PostincrementResultRemoveCVRefIsSame_t<T, R>::value;
		///	後置デクリメント演算子 @a T::operator--(int) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class R> static constexpr bool PostdecrementResultRemoveCVRefIsSame = PostdecrementResultRemoveCVRefIsSame_t<T, R>::value;
		///	算術演算子 @a T::operator+() の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class R> static constexpr bool PromotionResultRemoveCVRefIsSame = PromotionResultRemoveCVRefIsSame_t<T, R>::value;
		///	算術演算子 @a T::operator-() の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class R> static constexpr bool InverseResultRemoveCVRefIsSame = InverseResultRemoveCVRefIsSame_t<T, R>::value;
		///	算術演算子 @a T::operator+(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool AdditionResultRemoveCVRefIsSame = AdditionResultRemoveCVRefIsSame_t<T, U, R>::value;
		///	算術演算子 @a T::operator-(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool SubtractionResultRemoveCVRefIsSame = SubtractionResultRemoveCVRefIsSame_t<T, U, R>::value;
		///	算術演算子 @a T::operator*(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool MultiplicationResultRemoveCVRefIsSame = MultiplicationResultRemoveCVRefIsSame_t<T, U, R>::value;
		///	算術演算子 @a T::operator/(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool DivisionResultRemoveCVRefIsSame = DivisionResultRemoveCVRefIsSame_t<T, U, R>::value;
		///	算術演算子 @a T::operator%(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool ModulationResultRemoveCVRefIsSame = ModulationResultRemoveCVRefIsSame_t<T, U, R>::value;
		///	算術演算子 @a T::operator~() の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class R> static constexpr bool ArithmeticNotResultRemoveCVRefIsSame = ArithmeticNotResultRemoveCVRefIsSame_t<T, R>::value;
		///	算術演算子 @a T::operator&(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool ArithmeticAndResultRemoveCVRefIsSame = ArithmeticAndResultRemoveCVRefIsSame_t<T, U, R>::value;
		///	算術演算子 @a T::operator|(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool ArithmeticOrResultRemoveCVRefIsSame = ArithmeticOrResultRemoveCVRefIsSame_t<T, U, R>::value;
		///	算術演算子 @a T::operator^(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool ArithmeticXorResultRemoveCVRefIsSame = ArithmeticXorResultRemoveCVRefIsSame_t<T, U, R>::value;
		///	算術演算子 @a T::operator<<(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool LShiftResultRemoveCVRefIsSame = LShiftResultRemoveCVRefIsSame_t<T, U, R>::value;
		///	算術演算子 @a T::operator>>(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool RShiftResultRemoveCVRefIsSame = RShiftResultRemoveCVRefIsSame_t<T, U, R>::value;
		///	論理演算子 @a T::operator!() の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class R> static constexpr bool LogicalNotResultRemoveCVRefIsSame = LogicalNotResultRemoveCVRefIsSame_t<T, R>::value;
		///	論理演算子 @a T::operator&&(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool LogicalOrResultRemoveCVRefIsSame = LogicalOrResultRemoveCVRefIsSame_t<T, U, R>::value;
		///	論理演算子 @a T::operator||(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool LogicalAndResultRemoveCVRefIsSame = LogicalAndResultRemoveCVRefIsSame_t<T, U, R>::value;
		///	比較演算子 @a T::operator==(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool EqualResultRemoveCVRefIsSame = EqualResultRemoveCVRefIsSame_t<T, U, R>::value;
		///	比較演算子 @a T::operator!=(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool NotEqualResultRemoveCVRefIsSame = NotEqualResultRemoveCVRefIsSame_t<T, U, R>::value;
		///	比較演算子 @a T::operator>(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool LargerCompareResultRemoveCVRefIsSame = LargerCompareResultRemoveCVRefIsSame_t<T, U, R>::value;
		///	比較演算子 @a T::operator<(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool SmallerCompareResultRemoveCVRefIsSame = SmallerCompareResultRemoveCVRefIsSame_t<T, U, R>::value;
		///	比較演算子 @a T::operator>=(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool LeastCompareResultRemoveCVRefIsSame = LeastCompareResultRemoveCVRefIsSame_t<T, U, R>::value;
		///	比較演算子 @a T::operator<=(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool MostCompareResultRemoveCVRefIsSame = MostCompareResultRemoveCVRefIsSame_t<T, U, R>::value;
		///	比較演算子 @a T::operator[](U) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool SubscriptResultRemoveCVRefIsSame = SubscriptResultRemoveCVRefIsSame_t<T, U, R>::value;
		///	比較演算子 @a T::operator*() の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class R> static constexpr bool DereferenceResultRemoveCVRefIsSame = DereferenceResultRemoveCVRefIsSame_t<T, R>::value;
		///	比較演算子 @a T::operator&() の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class R> static constexpr bool ReferenceResultRemoveCVRefIsSame = ReferenceResultRemoveCVRefIsSame_t<T, R>::value;
		///	比較演算子 @a T::operator,(U) の返却値(CVRef除去)型が指定されたものに一致するかを識別します。
		template<class T, class U, class R> static constexpr bool CommaResultRemoveCVRefIsSame = CommaResultRemoveCVRefIsSame_t<T, U, R>::value;
	private:
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

		struct do_Aggregatable_impl
		{
			template<class T, class... Targs, typename = decltype( T{ ( std::declval<Targs&>() )... } )>
			static std::true_type do_Aggrigation(int);
			template<class T, class... Targs>
			static std::false_type do_Aggrigation(...);
		};
		template<class T, class... Targs>
		struct do_Aggregatable_t : public do_Aggregatable_impl
		{
			typedef decltype(do_Aggrigation<T, Targs ...>(0)) type;
		};
		template<class T, class... Targs>
		struct IsAggregatable_t : public do_Aggregatable_t<T, Targs ...>::type {};

		///	指定された型のオブジェクトとの等価比較が可能な型を識別するための実装。
		template<class T, class U>
		struct IsEquatable_t : std::conjunction< EqualResultIsConvertible_t<T, U, bool>, NotEqualResultIsConvertible_t<T, U, bool> > {};
		///	指定された型のオブジェクトとの大小比較が可能な型を識別するための実装。
		template<class T, class U>
		struct IsComparable_t : std::conjunction< LargerCompareResultIsConvertible_t<T, U, bool>, SmallerCompareResultIsConvertible_t<T, U, bool>, LeastCompareResultIsConvertible_t<T, U, bool>, MostCompareResultIsConvertible_t<T, U, bool> > {};
	public:
		///	指定された型のオブジェクトとの等価比較が可能な型を識別します。
		template<class T, class U = T> inline constexpr static bool IsEquatable = IsEquatable_t<T, U>::value;
		///	指定された型のオブジェクトとの大小比較が可能な型を識別します。
		template<class T, class U = T> inline constexpr static bool IsComparable = IsComparable_t<T, U>::value;
	private:
		template<class T> struct IsValueType_t : std::conjunction
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
				IsEquatable_t<T, T>
			>
		{};
	public:
		///	値型を識別します。
		template<class T> static constexpr bool IsValueType = IsValueType_t<T>::value;
	private:
		///	位置型が実装すべき演算子の実装を識別するための実装。
		template<class, class, class = void> struct HasPointableTypeOperation_t : std::false_type {};
		template<class T, class U> struct HasPointableTypeOperation_t<T, U, std::enable_if_t< IsValueType_t<U>::value >> : std::conjunction
			<
				SubstitutionAddResultIsSame_t<T, U, T&>,
				SubstitutionSubtractResultIsSame_t<T, U, T&>,
				AdditionResultIsSame_t<T, U, T>,
				SubtractionResultIsSame_t<T, U, T>,
				SubtractionResultIsSame_t<T, T, U>,
				IsEquatable_t<T, T>
			>
		{};
		///	位置型を識別するための実装。
		template<class T, class U> struct IsPointableType_t : std::conjunction< IsValueType_t<T>, HasPointableTypeOperation_t<T, U> > {};
	public:
		///	位置型を識別します。
		template<class T, class U> static constexpr bool IsPointableType = IsPointableType_t<T, U>::value;
	private:
		///	算術型が実装すべき演算子の実装を識別するための実装。
		template<class, class = std::void_t<>> struct HasNumeralTypeOperation_t : std::false_type {};
		template<class T> struct HasNumeralTypeOperation_t<T, std::void_t< PromotionResult<T> >> : std::conjunction
			<
				PromotionResultIsConvertible_t<T, T>,
				InverseResultIsSame_t<T, PromotionResult<T>>,
				AdditionResultIsSame_t<T, T, PromotionResult<T>>,
				SubtractionResultIsSame_t<T, T, PromotionResult<T>>,
				MultiplicationResultIsSame_t<T, T, PromotionResult<T>>,
				DivisionResultIsSame_t<T, T, PromotionResult<T>>,
				SubstitutionAddResultIsSame_t<T, T, T&>,
				SubstitutionSubtractResultIsSame_t<T, T, T&>,
				SubstitutionMultipleResultIsSame_t<T, T, T&>,
				SubstitutionDivideResultIsSame_t<T, T, T&>,
				IsEquatable_t<T, T>,
				IsComparable_t<T, T>
			>
		{};
		///	整数型が実装すべき演算子の実装を識別するための実装。
		template<class, class = std::void_t<>> struct HasIntegralTypeOperation_t : std::false_type {};
		template<class T> struct HasIntegralTypeOperation_t<T, std::void_t< PromotionResult<T> >> : std::conjunction
			<
				PreincrementResultIsSame_t<T, T&>,
				PredecrementResultIsSame_t<T, T&>,
				HasNumeralTypeOperation_t<T>,
				SubstitutionModulateResultIsSame_t<T, T, T&>,
				ModulationResultIsSame_t<T, T, PromotionResult<T>>
			>
		{};
		///	算術型を識別するための実装。
		template<class T> struct IsNumeralType_t : std::conjunction< IsValueType_t<T>, HasNumeralTypeOperation_t<T>, std::bool_constant<std::numeric_limits<T>::is_specialized> > {};
		///	整数型を識別するための実装。
		template<class T> struct IsIntegralType_t : std::conjunction< IsNumeralType_t<T>, HasIntegralTypeOperation_t<T> > {};
	public:
		///	基本的な算術演算を持つ型を識別します。
		template<class T> static constexpr bool HasNumeralOperation = HasNumeralTypeOperation_t<T>::value;
		///	算術型を識別します。
		template<class T> static constexpr bool IsNumeralType = IsNumeralType_t<T>::value;
		///	整数型を識別します。
		template<class T> static constexpr bool IsIntegralType = IsIntegralType_t<T>::value;
	private:
		///	単方向順序型が実装すべき演算子の実装を識別するための実装。
		template<class T> struct HasSequencialOrderTypeOperation_t : std::conjunction
			<
				PreincrementResultIsSame_t<T, T&>,
				IsEquatable_t<T, T>
			>
		{};
		///	双方向順序型が実装すべき演算子の実装を識別するための実装。
		template<class T> struct HasBidirectionalOrderTypeOperation_t : std::conjunction
			<
				HasSequencialOrderTypeOperation_t<T>,
				PredecrementResultIsSame_t<T, T&>
			>
		{};
		///	線形順序型が実装すべき演算子の実装を識別するための実装。
		template<class, class, class = void> struct HasLinearOrderTypeOperation_t : std::false_type {};
		template<class T, class N> struct HasLinearOrderTypeOperation_t<T, N, std::enable_if_t< IsIntegralType<N> >> : std::conjunction
			<
				HasBidirectionalOrderTypeOperation_t<T>,
				AdditionResultIsSame_t<T, N, T>,
				SubtractionResultIsSame_t<T, N, T>,
				SubstitutionAddResultIsSame_t<T, N, T&>,
				SubstitutionSubtractResultIsSame_t<T, N, T&>,
				IsComparable_t<T, T>
			>
		{};
		///	単方向順序型を識別するための実装。
		template<class T> struct IsSequencialOrderType_t : std::conjunction< HasSequencialOrderTypeOperation_t<T> > {};
		///	双方向順序型を識別するための実装。
		template<class T> struct IsBidirectionalOrderType_t : std::conjunction< IsSequencialOrderType_t<T>, HasBidirectionalOrderTypeOperation_t<T> > {};
		///	線形順序型を識別するための実装。
		template<class T, class N> struct IsLinearOrderType_t : std::conjunction< IsBidirectionalOrderType_t<T>, HasLinearOrderTypeOperation_t<T, N> > {};
	public:
		///	単方向の順序を持つ型を識別します。
		template<class T> static constexpr bool IsSequencialOrderType = IsSequencialOrderType_t<T>::value;
		///	双方向の順序を持つ型を識別します。
		template<class T> static constexpr bool IsBidirectionalOrderType = IsBidirectionalOrderType_t<T>::value;
		///	線形の順序を持つ型を識別します。
		template<class T, class N = int> static constexpr bool IsLinearOrderType = IsLinearOrderType_t<T, N>::value;
	private:
		///	ビット列型が実装すべき演算子の実装を識別するための実装。
		template<class, class, class = void> struct HasBitSequenceTypeOperation_t : std::false_type {};
		template<class T, class N> struct HasBitSequenceTypeOperation_t<T, N, std::enable_if_t< IsIntegralType<N> >> : std::conjunction
			<
				ArithmeticNotResultIsConvertible_t<T, T>,
				ArithmeticAndResultIsConvertible_t<T, T, T>,
				ArithmeticOrResultIsConvertible_t<T, T, T>,
				ArithmeticXorResultIsConvertible_t<T, T, T>,
				LShiftResultIsConvertible_t<T, N, T>,
				RShiftResultIsConvertible_t<T, N, T>,
				SubstitutionArithmeticAndResultIsSame_t<T, T, T&>,
				SubstitutionArithmeticOrResultIsSame_t<T, T, T&>,
				SubstitutionArithmeticXorResultIsSame_t<T, T, T&>,
				SubstitutionLShiftResultIsSame_t<T, N, T&>,
				SubstitutionRShiftResultIsSame_t<T, N, T&>,
				IsEquatable_t<T, T>
			>
		{};
		///	単方向順序型を識別するための実装。
		template<class T, class N> struct IsBitSequenceType_t : std::conjunction< IsValueType_t<T>, HasBitSequenceTypeOperation_t<T, N>, std::negation<std::is_signed<T>>, std::bool_constant<(!std::numeric_limits<T>::is_specialized) || (!std::numeric_limits<T>::is_signed)> > {};
	public:
		///	基本的なビット演算を持つ型を識別します。
		template<class T, class N = int> static constexpr bool HasBitSequenceOperation = HasBitSequenceTypeOperation_t<T, N>::value;
		///	ビット列型を識別します。
		///	@note
		///	signedな型はビット演算の結果が未定義(または処理系定義)となる値域を含むためサポートされません。
		template<class T, class N = int> static constexpr bool IsBitSequenceType = IsBitSequenceType_t<T, N>::value;
	private:
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

		struct do_StdLegacyIterator_impl
		{
			template<class It, typename = typename std::iterator_traits<It>::value_type> static std::true_type test_has_value_type(int);
			template<class It> static std::false_type test_has_value_type(...);
			template<class It, typename = typename std::iterator_traits<It>::difference_type> static std::true_type test_has_difference_type(int);
			template<class It> static std::false_type test_has_difference_type(...);
			template<class It, typename = typename std::iterator_traits<It>::reference> static std::true_type test_has_reference(int);
			template<class It> static std::false_type test_has_reference(...);
			template<class It, typename = typename std::iterator_traits<It>::pointer> static std::true_type test_has_pointer(int);
			template<class It> static std::false_type test_has_pointer(...);
			template<class It, typename = typename std::iterator_traits<It>::iterator_category> static std::true_type test_has_iterator_category(int);
			template<class It> static std::false_type test_has_iterator_category(...);
		};
		template<class It>
		struct do_StdLegacyIterator_t : do_StdLegacyIterator_impl
		{
			typedef decltype(test_has_value_type<It>(0)) has_value_type;
			typedef decltype(test_has_difference_type<It>(0)) has_difference_type;
			typedef decltype(test_has_reference<It>(0)) has_reference;
			typedef decltype(test_has_pointer<It>(0)) has_pointer;
			typedef decltype(test_has_iterator_category<It>(0)) has_iterator_category;
		};
		struct do_StdLegacyInputIterator_impl
		{
			template<class It, typename R = decltype( *std::declval<It&>() ), typename C = typename std::iterator_traits<It>::reference> static std::is_same<R, C> test_dereference_is_same_reference(int);
			template<class It> static std::false_type test_dereference_is_same_reference(...);
			template<class It, typename R = decltype( *std::declval<It&>() ), typename C = typename std::iterator_traits<It>::value_type> static std::is_convertible<R, C> test_dereference_is_convertible_value_type(int);
			template<class It> static std::false_type test_dereference_is_convertible_value_type(...);
			template<class It, typename R = decltype( *std::declval<It&>()++ ), typename C = typename std::iterator_traits<It>::value_type> static std::is_convertible<R, C> test_incdereference_is_convertible_value_type(int);
			template<class It> static std::false_type test_incdereference_is_convertible_value_type(...);
		};
		template<class It>
		struct do_StdLegacyInputIterator_t : do_StdLegacyInputIterator_impl
		{
			typedef decltype(test_dereference_is_same_reference<It>(0)) dereference_is_same_reference;
			typedef decltype(test_dereference_is_convertible_value_type<It>(0)) dereference_is_convertible_value_type;
			typedef decltype(test_incdereference_is_convertible_value_type<It>(0)) incdereference_is_convertible_value_type;
		};
		struct do_StdLegacyOutputIterator_impl
		{
			template<class It, class O, typename = decltype( *std::declval<It&>() = std::declval<O&>() )> static std::true_type test_has_dereference_assign(int);
			template<class It> static std::false_type test_has_dereference_assign(...);
			template<class It, class O, typename = decltype( *std::declval<It&>()++ = std::declval<O&>() )> static std::true_type test_has_incdereference_assign(int);
			template<class It> static std::false_type test_has_incdereference_assign(...);
		};
		template<class It, class O>
		struct do_StdLegacyOutputIterator_t : do_StdLegacyOutputIterator_impl
		{
			typedef decltype(test_has_dereference_assign<It, O>(0)) has_dereference_assign;
			typedef decltype(test_has_incdereference_assign<It, O>(0)) has_incdereference_assign;
		};
		struct do_StdLegacyForwardIterator_impl
		{
			template<class It, typename R = typename std::iterator_traits<It>::reference, typename C = typename std::iterator_traits<It>::value_type&> static std::is_same<R, C> test_reference_is_same_value_type_lvalue(int);
			template<class It> static std::false_type test_reference_is_same_value_type_lvalue(...);
			template<class It, typename R = typename std::iterator_traits<It>::reference, typename C = const typename std::iterator_traits<It>::value_type&> static std::is_same<R, C> test_reference_is_same_value_type_const_lvalue(int);
			template<class It> static std::false_type test_reference_is_same_value_type_const_lvalue(...);
			template<class It, typename R = decltype( *std::declval<It&>()++ ), typename C = typename std::iterator_traits<It>::reference> static std::is_same<R, C> test_incdereference_is_same_reference(int);
			template<class It> static std::false_type test_incdereference_is_same_reference(...);
		};
		template<class It>
		struct do_StdLegacyForwardIterator_t : do_StdLegacyForwardIterator_impl
		{
			typedef decltype(test_reference_is_same_value_type_lvalue<It>(0)) reference_is_same_value_type_lvalue;
			typedef decltype(test_reference_is_same_value_type_const_lvalue<It>(0)) reference_is_same_value_type_const_lvalue;
			typedef decltype(test_incdereference_is_same_reference<It>(0)) incdereference_is_same_reference;
		};
		struct do_StdLegacyBidirectionalIterator_impl
		{
			template<class It, typename R = decltype( *std::declval<It&>()-- ), typename C = typename std::iterator_traits<It>::reference> static std::is_same<R, C> test_decdereference_is_same_reference(int);
			template<class It> static std::false_type test_decdereference_is_same_reference(...);
		};
		template<class It>
		struct do_StdLegacyBidirectionalIterator_t : do_StdLegacyBidirectionalIterator_impl
		{
			typedef decltype(test_decdereference_is_same_reference<It>(0)) decdereference_is_same_reference;
		};
		struct do_StdLegacyRandomAccessIterator_impl
		{
			template<class It, typename D = typename std::iterator_traits<It>::difference_type, typename R = decltype( std::declval<It&>() += std::declval<D&>() ), typename C = It&> static std::is_same<R, C> test_difference_type_addstitution_is_same_lvalue(int);
			template<class It> static std::false_type test_difference_type_addstitution_is_same_lvalue(...);
			template<class It, typename D = typename std::iterator_traits<It>::difference_type, typename R = decltype( std::declval<It&>() + std::declval<D&>() ), typename C = It> static std::is_same<R, C> test_difference_type_add_is_same_object(int);
			template<class It> static std::false_type test_difference_type_add_is_same_object(...);
			template<class It, typename D = typename std::iterator_traits<It>::difference_type, typename R = decltype( std::declval<It&>() -= std::declval<D&>() ), typename C = It&> static std::is_same<R, C> test_difference_type_subtractstitution_is_same_lvalue(int);
			template<class It> static std::false_type test_difference_type_subtractstitution_is_same_lvalue(...);
			template<class It, typename D = typename std::iterator_traits<It>::difference_type, typename R = decltype( std::declval<It&>() - std::declval<D&>() ), typename C = It> static std::is_same<R, C> test_difference_type_subtract_is_same_object(int);
			template<class It> static std::false_type test_difference_type_subtract_is_same_object(...);
			template<class It, typename R = decltype( std::declval<It&>() - std::declval<It&>() ), typename C = typename std::iterator_traits<It>::difference_type> static std::is_same<R, C> test_type_subtract_is_same_difference_type(int);
			template<class It> static std::false_type test_type_subtract_is_same_difference_type(...);
			template<class It, typename D = typename std::iterator_traits<It>::difference_type, typename R = decltype( std::declval<It&>() [ std::declval<D&>() ] ), typename C = typename std::iterator_traits<It>::reference> static std::is_convertible<R, C> test_difference_type_subscript_is_convertible_reference(int);
			template<class It> static std::false_type test_difference_type_subscript_is_convertible_reference(...);
		};
		template<class It>
		struct do_StdLegacyRandomAccessIterator_t : do_StdLegacyRandomAccessIterator_impl
		{
			typedef decltype(test_difference_type_addstitution_is_same_lvalue<It>(0)) difference_type_addstitution_is_same_lvalue;
			typedef decltype(test_difference_type_add_is_same_object<It>(0)) difference_type_add_is_same_object;
			typedef decltype(test_difference_type_subtractstitution_is_same_lvalue<It>(0)) difference_type_subtractstitution_is_same_lvalue;
			typedef decltype(test_difference_type_subtract_is_same_object<It>(0)) difference_type_subtract_is_same_object;
			typedef decltype(test_type_subtract_is_same_difference_type<It>(0)) type_subtract_is_same_difference_type;
			typedef decltype(test_difference_type_subscript_is_convertible_reference<It>(0)) difference_type_subscript_is_convertible_reference;
		};
		template<class It> struct IsStdLegacyIterator_t : std::conjunction
			<
				std::is_copy_constructible<It>,
				std::is_copy_assignable<It>,
				std::is_destructible<It>,
				std::is_swappable<It&>,
				typename do_StdLegacyIterator_t<It>::has_value_type,
				typename do_StdLegacyIterator_t<It>::has_difference_type,
				typename do_StdLegacyIterator_t<It>::has_reference,
				typename do_StdLegacyIterator_t<It>::has_pointer,
				typename do_StdLegacyIterator_t<It>::has_iterator_category,
				PreincrementResultIsSame_t<It, It&>,
				HasDereference_t<It>
			>
		{};
		template<class It> struct IsStdLegacyInputIterator_t : std::conjunction
			<
				IsStdLegacyIterator_t<It>,
				IsEquatable_t<It, It>,
				PreincrementResultIsSame_t<It, It&>,
				HasPostincrement_t<It>,
				typename do_StdLegacyInputIterator_t<It>::dereference_is_same_reference,
				typename do_StdLegacyInputIterator_t<It>::dereference_is_convertible_value_type,
				typename do_StdLegacyInputIterator_t<It>::incdereference_is_convertible_value_type
			>
		{};
		template<class It, class O> struct IsStdLegacyOutputIterator_t : std::conjunction
			<
				IsStdLegacyIterator_t<It>,
				std::disjunction
				<
					std::is_class<It>,
					std::is_pointer<It>
				>,
				typename do_StdLegacyOutputIterator_t<It, O>::has_dereference_assign,
				typename do_StdLegacyOutputIterator_t<It, O>::has_incdereference_assign,
				PreincrementResultIsSame_t<It, It&>,
				PostincrementResultIsConvertible_t<It, const It&>
			>
		{};
		template<class It> struct IsStdLegacyForwardIterator_t : std::conjunction
			<
				IsStdLegacyInputIterator_t<It>,
				std::is_default_constructible<It>,
				std::disjunction
				<
					typename do_StdLegacyForwardIterator_t<It>::reference_is_same_value_type_lvalue,
					typename do_StdLegacyForwardIterator_t<It>::reference_is_same_value_type_const_lvalue
				>,
				PostincrementResultIsSame_t<It, It>,
				typename do_StdLegacyForwardIterator_t<It>::incdereference_is_same_reference
			>
		{};
		template<class It> struct IsStdLegacyBidirectionalIterator_t : std::conjunction
			<
				IsStdLegacyForwardIterator_t<It>,
				PredecrementResultIsSame_t<It, It&>,
				PostdecrementResultIsConvertible_t<It, const It&>,
				typename do_StdLegacyBidirectionalIterator_t<It>::decdereference_is_same_reference
			>
		{};
		template<class It> struct IsStdLegacyRandomAccessIterator_t : std::conjunction
			<
				IsStdLegacyBidirectionalIterator_t<It>,
				IsComparable_t<It, It>,
				typename do_StdLegacyRandomAccessIterator_t<It>::difference_type_addstitution_is_same_lvalue,
				typename do_StdLegacyRandomAccessIterator_t<It>::difference_type_add_is_same_object,
				typename do_StdLegacyRandomAccessIterator_t<It>::difference_type_subtractstitution_is_same_lvalue,
				typename do_StdLegacyRandomAccessIterator_t<It>::difference_type_subtract_is_same_object,
				typename do_StdLegacyRandomAccessIterator_t<It>::type_subtract_is_same_difference_type,
				typename do_StdLegacyRandomAccessIterator_t<It>::difference_type_subscript_is_convertible_reference
			>
		{};

	public:
		///	アロー演算子->のオーバーロード実装を識別します。
		template<class T, class R = T*> inline constexpr static bool HasArrow = HasArrowOverload_t<T, R>::value;
		///	アロー間接参照演算子->*のオーバーロード実装を識別します。
		template<class T, class R> inline constexpr static bool HasArrowDereference = HasArrowDereferenceOverload_t<T, R>::value;
		///	指定された型の波括弧による初期化が可能な型を識別します。
		template<class T, class... Targs> inline constexpr static bool IsAggregatable = IsAggregatable_t<T, Targs...>::value;
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
	#if 201703L <= __cplusplus
	// Clang C++17でコンパイルするとbool::operator++()を実体化しようとしてエラーを吐くため
	// boolによるインクリメントトレイトは強制的にfalseで実体化する
	template<> struct Traits::HasPreincrement_t<bool> : std::false_type {};
	// Clang C++17でコンパイルするとbool::operator++(int)を実体化しようとしてエラーを吐くため
	// boolによるインクリメントトレイトは強制的にfalseで実体化する
	template<> struct Traits::HasPostincrement_t<bool> : std::false_type {};
	#endif

	class BitCounter final
	{
		BitCounter() = delete;
		BitCounter(const BitCounter&) = delete;
		BitCounter(BitCounter&&) = delete;
		~BitCounter() = delete;
	public:
		template<class T, std::enable_if_t<Traits::IsBitSequenceType<T>, int> = 0>
		static constexpr size_t Count()
		{
			static_assert(std::is_constructible_v<T, int>, "テンプレート型 T は (int) を引数に持つコンストラクタをサポートする必要があります。");
			auto v = T(1);
			const auto z = T(0);
			size_t result = 0;
			while(v != z)
			{
				++result;
				if (v == T(v << 1)) { break; }
				v = v << 1;
			}
			return result;
		}
	};
	///	指定された型の有効なビット幅を識別するための機能を提供します。
	template<class T> struct BitWidth_t : std::integral_constant<size_t, BitCounter::Count<T>()>
	{
		static_assert(Traits::IsBitSequenceType<T>, "ビット幅の計数は整数型、boolなどの固定幅のビットシーケンスでのみ有効です。");
	};
	template<std::size_t N> struct BitWidth_t<std::bitset<N>> : std::integral_constant<size_t, N> {};
	///	指定された型の有効なビット幅を識別します。
	template<class T> inline constexpr size_t BitWidth = BitWidth_t<T>::value;
}
#endif // __stationaryorbit_core_traits__