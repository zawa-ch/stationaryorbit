#ifndef __stationaryorbit_mathematics_fuzzybool__
#define __stationaryorbit_mathematics_fuzzybool__
#include "stationaryorbit/core.numeral.hpp"
namespace zawa_ch::StationaryOrbit::Mathematics
{

	/// trueとfalseの中間を表現できるブール値を表します。
	struct FuzzyBool
	{
	private:

		FractionalDec _value;

	public:

		FuzzyBool() = default;
		FuzzyBool(bool value);
		explicit FuzzyBool(const uintmax_t& num, const uintmax_t& den);
		explicit FuzzyBool(const double& value);
		explicit FuzzyBool(const FractionalDec& value);

		///	指定された値でこのオブジェクトの二値化を行います。
		bool Binalization(const FractionalDec& value) const;

		FuzzyBool Not() const;
		FuzzyBool operator!() const { return Not(); }

		FuzzyBool Or(const FuzzyBool& value) const;
		FuzzyBool operator||(const FuzzyBool& value) const { return Or(value); }

		FuzzyBool And(const FuzzyBool& value) const;
		FuzzyBool operator&&(const FuzzyBool& value) const { return And(value); }

		FuzzyBool AlgebraAdd(const FuzzyBool& value) const;

		FuzzyBool AlgebraProduct(const FuzzyBool& value) const;

		FuzzyBool LimitAdd(const FuzzyBool& value) const;

		FuzzyBool LimitProduct(const FuzzyBool& value) const;

		static FuzzyBool True();

		static FuzzyBool False();

	};

}
#endif // __stationaryorbit_mathematics_fuzzybool__