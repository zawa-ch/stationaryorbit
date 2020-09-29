//	stationaryorbit/mathematics/fuzzyreasoning
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
#ifndef __stationaryorbit_mathematics_fuzzyreasoning__
#define __stationaryorbit_mathematics_fuzzyreasoning__
#include <utility>
#include "fuzzyset.hpp"
#include "fuzzyrelation.hpp"
namespace zawa_ch::StationaryOrbit::Mathematics
{

	///	ファジィ関係に対して条件となるファジィ集合が与えられた場合のファジィ推論を表します。
	template<typename TAntecedent, typename TConsequent>
	class FuzzyReasoning
		: virtual public FuzzySet<std::pair<TAntecedent, TConsequent>>
	{
	public:

		typedef TAntecedent AntecedentType;
		typedef TConsequent ConsequentType;

	private:

		const FuzzyRelation<TAntecedent, TConsequent> _relation;
		const FuzzySet<TAntecedent>& _condition;

	public:

		FuzzyReasoning(const FuzzyRelation<TAntecedent, TConsequent>& relation, const FuzzySet<TAntecedent>& condition) : _relation(relation), _condition(condition) {}

		FuzzyBool Evaluate(const std::pair<TAntecedent, TConsequent>& input) const { return FuzzyAndCombining<TAntecedent, std::pair<TAntecedent, TConsequent>>(_condition, _relation).Evaluate(input.first, input); }
		FuzzyBool Evaluate(const TAntecedent& antecedent_input, const TConsequent& consequent_input) const { return Evaluate(std::pair<TAntecedent, std::pair<TAntecedent, TConsequent>>{antecedent_input, consequent_input}); }

	};

}
#endif // __stationaryorbit_mathematics_fuzzyreasoning__