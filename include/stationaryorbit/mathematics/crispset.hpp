//	stationaryorbit/mathematics/crispset
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
#ifndef __stationaryorbit_mathematics_crispset__
#define __stationaryorbit_mathematics_crispset__
#include <utility>
namespace zawa_ch::StationaryOrbit::MatheMatics
{

	///	クリスプ集合を実装します。
	template<typename T>
	class CrispSet
	{
	public:
		typedef T Type;
		///	指定された値が集合に含まれるかを評価します。
		virtual bool Evaluate(const T& input) const = 0;
	};

	///	クリスプ集合の補集合(~A)を表します。
	template<typename T>
	class CrispComplementalSet
		: virtual public CrispSet<T>
	{
	private:
		const CrispSet<T>& _value;
	public:
		explicit CrispComplementalSet(const CrispSet<T>& value) : _value(value) {}
		bool Evaluate(const T& input) const { return !(_value.Evaluate(input)); }
	};

	template<typename T>
	CrispComplementalSet<T> operator~(const CrispSet<T>& value) { return CrispComplementalSet(value); }

	///	クリスプ集合の和集合(A ∪ B)を表します。
	template<typename TLeft, typename TRight>
	class CrispOrCombining
		: virtual public CrispSet<std::pair<TLeft, TRight>>
	{
	private:
		const CrispSet<TLeft>& _left;
		const CrispSet<TRight>& _right;
	public:
		explicit CrispOrCombining(const CrispSet<TLeft>& left, const CrispSet<TRight>& right) : _left(left), _right(right) {}
		bool Evaluate(const std::pair<TLeft, TRight>& input) const { return Evaluate(input.first, input.second); }
		bool Evaluate(const TLeft& leftinput, const TRight& rightinput) const { return _left.Evaluate(leftinput) || _right.Evaluate(rightinput); }
	};

	template<typename TLeft, typename TRight>
	CrispOrCombining<TLeft, TRight> operator|(const CrispSet<TLeft>& left, const CrispSet<TRight>& right) { return CrispOrCombining(left, right); }

	///	クリスプ集合の積集合(A ∩ B)を表します。
	template<typename TLeft, typename TRight>
	class CrispAndCombining
		: virtual public CrispSet<std::pair<TLeft, TRight>>
	{
	private:
		const CrispSet<TLeft>& _left;
		const CrispSet<TRight>& _right;
	public:
		explicit CrispAndCombining(const CrispSet<TLeft>& left, const CrispSet<TRight>& right) : _left(left), _right(right) {}
		bool Evaluate(const std::pair<TLeft, TRight>& input) const { return Evaluate(input.first, input.second); }
		bool Evaluate(const TLeft& leftinput, const TRight& rightinput) const { return _left.Evaluate(leftinput) && _right.Evaluate(rightinput); }
	};

	template<typename TLeft, typename TRight>
	CrispAndCombining<TLeft, TRight> operator&(const CrispSet<TLeft>& left, const CrispSet<TRight>& right) { return CrispAndCombining(left, right); }

	template<typename T>
	class CrispDelegateSet
		: virtual public CrispSet<T>
	{
	public:
		typedef bool(*Function)(const T&);
	private:
		Function _evaluator_func;
	public:
		CrispDelegateSet(Function evaluator_func) : _evaluator_func(evaluator_func) {}
		bool Evaluate(const T& input) const { return _evaluator_func(input); }
	};

	///	単純なクリスプ集合の実装に用いられるデータセットを表します。
	template<typename T>
	class SimpleCrispLogicSetData
	{
	public:
		T _evaluate_value;
	};

	///	A{ input = value } を表すクリスプ集合を表します。
	template<typename T>
	class CrispEqualSet
		: virtual public CrispSet<T>
		, private SimpleCrispLogicSetData<T>
	{
	public:
		explicit CrispEqual(const T& value) : _evaluate_value(value) {}
		bool Evaluate(const T& input) const { return input == _evaluate_value; }
	};

	///	A{ input != value } を表すクリスプ集合を表します。
	template<typename T>
	class CrispNotEqualSet
		: virtual public CrispSet<T>
		, private SimpleCrispLogicSetData<T>
	{
	public:
		explicit CrispNotEqual(const T& value) : _evaluate_value(value) {}
		bool Evaluate(const T& input) const { return input != _evaluate_value; }
	};

	///	A{ input > value } を表すクリスプ集合を表します。
	template<typename T>
	class CrispMoreSet
		: virtual public CrispSet<T>
		, private SimpleCrispLogicSetData<T>
	{
	public:
		explicit CrispMore(const T& value) : _evaluate_value(value) {}
		bool Evaluate(const T& input) const { return _evaluate_value < input; }
	};

	///	A{ input < value } を表すクリスプ集合を表します。
	template<typename T>
	class CrispLessSet
		: virtual public CrispSet<T>
		, private SimpleCrispLogicSetData<T>
	{
	public:
		explicit CrispLess(const T& value) : _evaluate_value(value) {}
		bool Evaluate(const T& input) const { return input < _evaluate_value; }
	};

	///	A{ input >= value } を表すクリスプ集合を表します。
	template<typename T>
	class CrispMoreEqualSet
		: virtual public CrispSet<T>
		, private SimpleCrispLogicSetData<T>
	{
	public:
		explicit CrispMoreEqual(const T& value) : _evaluate_value(value) {}
		bool Evaluate(const T& input) const { return _evaluate_value <= input; }
	};

	///	A{ input <= value } を表すクリスプ集合を表します。
	template<typename T>
	class CrispLessEqualSet
		: virtual public CrispSet<T>
		, private SimpleCrispLogicSetData<T>
	{
	public:
		explicit CrispLessEqual(const T& value) : _evaluate_value(value) {}
		bool Evaluate(const T& input) const { return input <= _evaluate_value; }
	};

}
#endif // __stationaryorbit_mathematics_crispset__