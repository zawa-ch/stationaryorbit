//	stationaryorbit/mathematics/fuzzybool
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
#ifndef __stationaryorbit_mathematics_fuzzybool__
#define __stationaryorbit_mathematics_fuzzybool__
#include "stationaryorbit/core.numeral.hpp"
namespace zawa_ch::StationaryOrbit::Mathematics
{

	/// trueとfalseの中間を表現できるブール値を表します。
	struct FuzzyBool
	{
	private:

		Proportion64_t _value;

	public:

		FuzzyBool() = default;
		FuzzyBool(bool value);
		explicit FuzzyBool(const uintmax_t& num, const uintmax_t& den);
		explicit FuzzyBool(const double& value);
		explicit FuzzyBool(const Proportion64_t& value);

		///	指定された値でこのオブジェクトの二値化を行います。
		bool Binalization(const Proportion64_t& value) const;

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