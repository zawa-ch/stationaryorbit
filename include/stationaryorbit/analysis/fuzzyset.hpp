#ifndef __stationaryorbit_analysis_fuzzyset__
#define __stationaryorbit_analysis_fuzzyset__
#include <utility>
#include "fuzzybool.hpp"
namespace zawa_ch::StationaryOrbit::NumericAnalysis
{

	///	ファジィ集合を表します。
	template<typename T>
	class FuzzySet
	{
	public:
		///	指定された値が集合にどの程度含まれるか(帰属度)を評価します。
		virtual FuzzyBool Evaluate(const T& input) const = 0;
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
	template<typename T, SimpleFuzzyLogicSetData<T>::DecreaseFunction Decrfunc = FuzzyLogicFunctions<T>::Liner>
	class FuzzyEqualSet
		: virtual public FuzzySet<T>
		, private SimpleFuzzyLogicSetData<T>
	{
	public:
		FuzzyEqualSet(const T& value, const T& variance) : _value(value), _variance(variance) {}
		FuzzyBool Evaluate(const T& input) const { return Decrfunc(input - _value, _variance); }
	};

	///	A{ input ~!= value } を表すファジィ集合を表します。
	template<typename T, SimpleFuzzyLogicSetData<T>::DecreaseFunction Decrfunc = FuzzyLogicFunctions<T>::Liner>
	class FuzzyNotEqualSet
		: virtual public FuzzySet<T>
		, private SimpleFuzzyLogicSetData<T>
	{
	public:
		FuzzyNotEqualSet(const T& value, const T& variance) : _value(value), _variance(variance) {}
		FuzzyBool Evaluate(const T& input) const { return ~(Decrfunc(input - _value, _variance)); }
	};

	///	A{ input ~< value } を表すファジィ集合を表します。
	template<typename T, SimpleFuzzyLogicSetData<T>::DecreaseFunction Decrfunc = FuzzyLogicFunctions<T>::Liner>
	class FuzzyMoreSet
		: virtual public FuzzySet<T>
		, private SimpleFuzzyLogicSetData<T>
	{
	public:
		FuzzyMoreSet(const T& value, const T& variance) : _value(value), _variance(variance) {}
		FuzzyBool Evaluate(const T& input) const { return (_value < input)?(FuzzyBool::True()):((_variance!=T(0))?(Decrfunc(_value - input, _variance)):(FuzzyBool::False())); }
	};

	///	A{ input ~<= value } を表すファジィ集合を表します。
	template<typename T, SimpleFuzzyLogicSetData<T>::DecreaseFunction Decrfunc = FuzzyLogicFunctions<T>::Liner>
	class FuzzyMoreEqualSet
		: virtual public FuzzySet<T>
		, private SimpleFuzzyLogicSetData<T>
	{
	public:
		FuzzyMoreEqualSet(const T& value, const T& variance) : _value(value), _variance(variance) {}
		FuzzyBool Evaluate(const T& input) const { return (_value <= input)?(FuzzyBool::True()):((_variance!=T(0))?(Decrfunc(_value - input, _variance)):(FuzzyBool::False())); }
	};

	///	A{ input ~> value } を表すファジィ集合を表します。
	template<typename T, SimpleFuzzyLogicSetData<T>::DecreaseFunction Decrfunc = FuzzyLogicFunctions<T>::Liner>
	class FuzzyLessSet
		: virtual public FuzzySet<T>
		, private SimpleFuzzyLogicSetData<T>
	{
	public:
		FuzzyLessSet(const T& value, const T& variance) : _value(value), _variance(variance) {}
		FuzzyBool Evaluate(const T& input) const { return (input < _value)?(FuzzyBool::True()):((_variance!=T(0))?(Decrfunc(input - _value, _variance)):(FuzzyBool::False())); }
	};

	///	A{ input ~>= value } を表すファジィ集合を表します。
	template<typename T, SimpleFuzzyLogicSetData<T>::DecreaseFunction Decrfunc = FuzzyLogicFunctions<T>::Liner>
	class FuzzyLessEqualSet
		: virtual public FuzzySet<T>
		, private SimpleFuzzyLogicSetData<T>
	{
	public:
		FuzzyLessEqualSet(const T& value, const T& variance) : _value(value), _variance(variance) {}
		FuzzyBool Evaluate(const T& input) const { return (input <= _value)?(FuzzyBool::True()):((_variance!=T(0))?(Decrfunc(input - _value, _variance)):(FuzzyBool::False())); }
	};

}
#endif // __stationaryorbit_analysis_fuzzyset__