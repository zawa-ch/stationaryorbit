#ifndef __stationaryorbit_mathematics_fuzzyrelation__
#define __stationaryorbit_mathematics_fuzzyrelation__
#include <utility>
#include "fuzzyset.hpp"
namespace zawa_ch::StationaryOrbit::Mathematics
{

	/// 二つのファジィ集合間のif-then関係を表します。
	template<typename TAntecedent, typename TConsequent>
	class FuzzyRelation
		: virtual public FuzzySet<std::pair<TAntecedent, TConsequent>>
	{
	public:

		typedef TAntecedent AntecedentType;
		typedef TConsequent ConsequentType;

	private:

		const FuzzySet<TAntecedent>& _antecedent;	///< ファジィ関係のifに当たる前件部。
		const FuzzySet<TConsequent>& _consequent;	///< ファジィ関係のthenに当たる後件部。

	public:

		FuzzyRelation(const FuzzySet<TAntecedent>& antecedent, const FuzzySet<TConsequent>& consequent) : _antecedent(antecedent), _consequent(consequent) {}

		FuzzyBool Evaluate(const std::pair<TAntecedent, TConsequent>& input) const { return Evaluate(input.first, input.second); }
		FuzzyBool Evaluate(const TAntecedent& antecedent_input, const TConsequent& consequent_input) const { return FuzzyAndCombining<TAntecedent, TConsequent>(_antecedent, _consequent).Evaluate(antecedent_input, consequent_input); }

	};

}
#endif // __stationaryorbit_mathematics_fuzzyrelation__