//	stationaryorbit/mathematics/fuzzyset
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
#ifndef __stationaryorbit_mathematics_fuzzyset__
#define __stationaryorbit_mathematics_fuzzyset__
#include <utility>
#include "fuzzybool.hpp"
namespace zawa_ch::StationaryOrbit::Mathematics
{

	///	ファジィ集合を表します。
	template<typename T>
	class FuzzySet
	{
	public:
		typedef T Type;
		///	指定された値が集合にどの程度含まれるか(帰属度)を評価します。
		virtual FuzzyBool Evaluate(const T& input) const = 0;
	};

	///	ファジィ集合の補集合(~A)を表します。
	template<typename T>
	class FuzzyComplementalSet
		: virtual public FuzzySet<T>
	{
	private:
		const FuzzySet<T>& _value;
	public:
		explicit FuzzyComplementalSet(const FuzzySet<T>& value) : _value(value) {}
		FuzzyBool Evaluate(const T& input) const { return !(_value.Evaluate(input)); }
	};

	template<typename T>
	FuzzyComplementalSet<T> operator~(const FuzzySet<T>& value) { return FuzzyComplementalSet(value); }

	///	ファジィ集合の和集合(A ∪ B)を表します。
	template<typename TLeft, typename TRight>
	class FuzzyOrCombining
		: virtual public FuzzySet<std::pair<TLeft, TRight>>
	{
	private:
		const FuzzySet<TLeft>& _left;
		const FuzzySet<TRight>& _right;
	public:
		explicit FuzzyOrCombining(const FuzzySet<TLeft>& left, const FuzzySet<TRight>& right) : _left(left), _right(right) {}
		FuzzyBool Evaluate(const std::pair<TLeft, TRight>& input) const { return Evaluate(input.first, input.second); }
		FuzzyBool Evaluate(const TLeft& leftinput, const TRight& rightinput) const { return _left.Evaluate(leftinput) || _right.Evaluate(rightinput); }
	};

	template<typename TLeft, typename TRight>
	FuzzyOrCombining<TLeft, TRight> operator|(const FuzzySet<TLeft>& left, const FuzzySet<TRight>& right) { return FuzzyOrCombining(left, right); }

	///	ファジィ集合の積集合(A ∩ B)を表します。
	template<typename TLeft, typename TRight>
	class FuzzyAndCombining
		: virtual public FuzzySet<std::pair<TLeft, TRight>>
	{
	private:
		const FuzzySet<TLeft>& _left;
		const FuzzySet<TRight>& _right;
	public:
		explicit FuzzyAndCombining(const FuzzySet<TLeft>& left, const FuzzySet<TRight>& right) : _left(left), _right(right) {}
		FuzzyBool Evaluate(const std::pair<TLeft, TRight>& input) const { return Evaluate(input.first, input.second); }
		FuzzyBool Evaluate(const TLeft& leftinput, const TRight& rightinput) const { return _left.Evaluate(leftinput) && _right.Evaluate(rightinput); }
	};

	template<typename TLeft, typename TRight>
	FuzzyAndCombining<TLeft, TRight> operator&(const FuzzySet<TLeft>& left, const FuzzySet<TRight>& right) { return FuzzyAndCombining(left, right); }

	template<typename T>
	class FuzzyDelegateSet
		: virtual public FuzzySet<T>
	{
	public:
		typedef FuzzyBool(*Function)(const T&);
	private:
		Function _evaluator_func;
	public:
		FuzzyDelegateSet(Function evaluator_func) : _evaluator_func(evaluator_func) {}
		FuzzyBool Evaluate(const T& input) const { return _evaluator_func(input); }
	};

	///	単純なファジィ集合の実装に用いられるデータセットを表します。
	template<typename T>
	class SimpleFuzzyLogicSetData
	{
	public:
		T _value;
		T _variance;
		typedef FuzzyBool(*DecreaseFunction)(T dist, T variance);
	};

	template<typename T>
	class FuzzyLogicFunctions final
	{
		static FuzzyBool Liner(T dist, T variance) { return (variance != T(0))?(FuzzyBool(T(1) - ((T(0) <= dist)?(dist):(-dist)) / variance)):(FuzzyBool(dist == T(0))); }
	};

	///	A{ input ~= value } を表すファジィ集合を表します。
	template<typename T, typename SimpleFuzzyLogicSetData<T>::DecreaseFunction Decrfunc = FuzzyLogicFunctions<T>::Liner>
	class FuzzyEqualSet
		: virtual public FuzzySet<T>
		, private SimpleFuzzyLogicSetData<T>
	{
	public:
		FuzzyEqualSet(const T& value, const T& variance) : _value(value), _variance(variance) {}
		FuzzyBool Evaluate(const T& input) const { return Decrfunc(input - _value, _variance); }
	};

	///	A{ input ~!= value } を表すファジィ集合を表します。
	template<typename T, typename SimpleFuzzyLogicSetData<T>::DecreaseFunction Decrfunc = FuzzyLogicFunctions<T>::Liner>
	class FuzzyNotEqualSet
		: virtual public FuzzySet<T>
		, private SimpleFuzzyLogicSetData<T>
	{
	public:
		FuzzyNotEqualSet(const T& value, const T& variance) : _value(value), _variance(variance) {}
		FuzzyBool Evaluate(const T& input) const { return ~(Decrfunc(input - _value, _variance)); }
	};

	///	A{ input ~< value } を表すファジィ集合を表します。
	template<typename T, typename SimpleFuzzyLogicSetData<T>::DecreaseFunction Decrfunc = FuzzyLogicFunctions<T>::Liner>
	class FuzzyMoreSet
		: virtual public FuzzySet<T>
		, private SimpleFuzzyLogicSetData<T>
	{
	public:
		FuzzyMoreSet(const T& value, const T& variance) : _value(value), _variance(variance) {}
		FuzzyBool Evaluate(const T& input) const { return (_value < input)?(FuzzyBool::True()):((_variance!=T(0))?(Decrfunc(_value - input, _variance)):(FuzzyBool::False())); }
	};

	///	A{ input ~<= value } を表すファジィ集合を表します。
	template<typename T, typename SimpleFuzzyLogicSetData<T>::DecreaseFunction Decrfunc = FuzzyLogicFunctions<T>::Liner>
	class FuzzyMoreEqualSet
		: virtual public FuzzySet<T>
		, private SimpleFuzzyLogicSetData<T>
	{
	public:
		FuzzyMoreEqualSet(const T& value, const T& variance) : _value(value), _variance(variance) {}
		FuzzyBool Evaluate(const T& input) const { return (_value <= input)?(FuzzyBool::True()):((_variance!=T(0))?(Decrfunc(_value - input, _variance)):(FuzzyBool::False())); }
	};

	///	A{ input ~> value } を表すファジィ集合を表します。
	template<typename T, typename SimpleFuzzyLogicSetData<T>::DecreaseFunction Decrfunc = FuzzyLogicFunctions<T>::Liner>
	class FuzzyLessSet
		: virtual public FuzzySet<T>
		, private SimpleFuzzyLogicSetData<T>
	{
	public:
		FuzzyLessSet(const T& value, const T& variance) : _value(value), _variance(variance) {}
		FuzzyBool Evaluate(const T& input) const { return (input < _value)?(FuzzyBool::True()):((_variance!=T(0))?(Decrfunc(input - _value, _variance)):(FuzzyBool::False())); }
	};

	///	A{ input ~>= value } を表すファジィ集合を表します。
	template<typename T, typename SimpleFuzzyLogicSetData<T>::DecreaseFunction Decrfunc = FuzzyLogicFunctions<T>::Liner>
	class FuzzyLessEqualSet
		: virtual public FuzzySet<T>
		, private SimpleFuzzyLogicSetData<T>
	{
	public:
		FuzzyLessEqualSet(const T& value, const T& variance) : _value(value), _variance(variance) {}
		FuzzyBool Evaluate(const T& input) const { return (input <= _value)?(FuzzyBool::True()):((_variance!=T(0))?(Decrfunc(input - _value, _variance)):(FuzzyBool::False())); }
	};

}
#endif // __stationaryorbit_mathematics_fuzzyset__