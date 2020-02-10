#ifndef __stationaryorbit_analysis_fuzzyreasoning__
#define __stationaryorbit_analysis_fuzzyreasoning__
#include <utility>
#include "fuzzyset.hpp"
#include "fuzzyrelation.hpp"
namespace zawa_ch::StationaryOrbit::NumericAnalysis
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
#endif // __stationaryorbit_analysis_fuzzyreasoning__