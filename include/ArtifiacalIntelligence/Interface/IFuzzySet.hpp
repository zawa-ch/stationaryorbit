#ifndef __StationaryOrbit_ArtificalIntelligence__
#define __StationaryOrbit_ArtificalIntelligence__
#include "General/Numeral"
namespace StationaryOrbit::ArtificalIntelligence
{

	///	ファジィ集合を実装します。
	///
	///	@param	T
	///	メンバーシップ関数の入力型。
	template<typename T>
	class IFuzzySet
	{
	public:

		///	指定された入力のこの集合における帰属度を取得します。
		virtual FractionalDec Grade(const T& input) const = 0;

	};

}
#endif // __StationaryOrbit_ArtificalIntelligence__