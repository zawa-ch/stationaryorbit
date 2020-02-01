#ifndef __stationaryorbit_ai_fuzzyset__
#define __stationaryorbit_ai_fuzzyset__
#include "stationaryorbit/core/numeral"
namespace zawa_ch::StationaryOrbit::ArtificalIntelligence
{

	///	ファジィ集合を表します。
	///	このクラスは抽象クラスです。
	///
	///	@param	T
	///	メンバーシップ関数の入力型。
	template<typename T>
	class FuzzySet
	{
	public:

		///	指定された入力のこの集合における帰属度を取得します。
		virtual FractionalDec Grade(const T& input) const = 0;

	};

}
#endif // __stationaryorbit_ai_fuzzyset__