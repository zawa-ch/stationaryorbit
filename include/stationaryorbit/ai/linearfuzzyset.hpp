#ifndef __stationaryorbit_ai_linerfuzzyset__
#define __stationaryorbit_ai_linerfuzzyset__
#include "fuzzyset.hpp"
namespace zawa_ch::StationaryOrbit::ArtificalIntelligence
{

	///	数値軸上の線形関数で表すことのできるファジィ集合を表します。
	class LinearFuzzySet
		: virtual public FuzzySet<double>
	{
	private:

		FractionalDec _max;
		FractionalDec _min;
		double _center;
		double _variance;

	public:

		///	指定された入力のこの集合における帰属度を取得します。
		FractionalDec Grade(const double& input) const;

	};

}
#endif // __stationaryorbit_ai_linerfuzzyset__