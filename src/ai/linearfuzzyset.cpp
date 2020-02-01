#include <cmath>
#include "stationaryorbit/ai/linearfuzzyset.hpp"
using namespace zawa_ch::StationaryOrbit;

FractionalDec ArtificalIntelligence::LinearFuzzySet::Grade(const double& input) const
{
	auto diff = std::abs(_center - input) / _variance;
	if (1.0 <= diff) { return _min; }
	else
	{
		auto prop = FractionalDec::Max() - FractionalDec(diff);
		return _min + (_max - _min) * prop;
	}
}
