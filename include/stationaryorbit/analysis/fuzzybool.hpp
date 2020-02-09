#ifndef __stationaryorbit_analysis_fuzzybool__
#define __stationaryorbit_analysis_fuzzybool__
#include "stationaryorbit/core/numeral"
namespace zawa_ch::StationaryOrbit::NumericAnalysis
{

	/// trueとfalseの中間を表現できるブール値を表します。
	struct FuzzyBool
	{
	private:
		FractionalDec _value;
	public:
		FuzzyBool() = default;
		FuzzyBool(bool value) : _value((value?1U:0U), 1U) {}
		explicit FuzzyBool(const uintmax_t& num, const uintmax_t& den) : _value(num, den) {}
		explicit FuzzyBool(const double& value) : _value(value) {}
		explicit FuzzyBool(const FractionalDec& value) : _value(value) {}
		///	指定された値でこのオブジェクトの二値化を行います。
		bool Binalization(const FractionalDec& value) const { return value <= _value; }
		FuzzyBool Not() const { return FuzzyBool(FractionalDec::Max() - _value); }
		FuzzyBool operator~() const { return Not(); }
		FuzzyBool Or(const FuzzyBool& value) const { return FuzzyBool((value._value<_value)?_value:value._value); }
		FuzzyBool operator||(const FuzzyBool& value) const { return Or(value); }
		FuzzyBool And(const FuzzyBool& value) const { return FuzzyBool((_value<value._value)?_value:value._value); }
		FuzzyBool operator&&(const FuzzyBool& value) const { return And(value); }
		FuzzyBool AlgebraAdd(const FuzzyBool& value) const { return FuzzyBool(_value + (value._value - _value * value._value)); }
		FuzzyBool AlgebraProduct(const FuzzyBool& value) const { return FuzzyBool(_value * value._value); }
		FuzzyBool LimitAdd(const FuzzyBool& value) const { return FuzzyBool(_value + value._value); }
		FuzzyBool LimitProduct(const FuzzyBool& value) const { return FuzzyBool(_value - (FractionalDec::Max() - value._value)); }
		static FuzzyBool True() { return FuzzyBool(true); }
		static FuzzyBool False() { return FuzzyBool(false); }
	};

}
#endif // __stationaryorbit_analysis_fuzzybool__