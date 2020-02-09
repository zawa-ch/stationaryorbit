#ifndef __stationaryorbit_analysis_fuzzyrelation__
#define __stationaryorbit_analysis_fuzzyrelation__
#include "fuzzyset.hpp"
namespace zawa_ch::StationaryOrbit::NumericAnalysis
{

	/// 二つのファジィ集合間のファジィif-then関係を表します。
	class FuzzyRelation
	{
	private:

		FuzzySet<double>* _antecedent;	///< ファジィ関係のifに当たる前件部。
		FuzzySet<double>* _consequent;	///< ファジィ関係のthenに当たる後件部。

	};

}
#endif // __stationaryorbit_analysis_fuzzyrelation__