#ifndef __StationaryOrbit_NumericAnalysis_NewtonCoef__
#define __StationaryOrbit_NumericAnalysis_NewtonCoef__
#include <vector>
#include "General/Exception"
#include "General/Vector2d"
#include "../Interface/IMathmaticFunction.hpp"
namespace StationaryOrbit::NumericAnalysis
{

	class NewtonCoef
		: public IMathmaticFunction<double>
	{
	private:

		std::vector<double> x;
		std::vector<double> b;

		void Complete();

	public:

		explicit NewtonCoef(const std::vector<Vector2d>& list);

		NewtonCoef(const IMathmaticFunction<double>& func, const std::vector<double> xlist);

		std::vector<double>& X() { return x; }

		std::vector<double> getX() const { return x; }

		std::vector<double> getB() const { return b; }

		double Calc(const double& value) const;
		double operator()(const double& value) const { return Calc(value); }

	};

}
#endif // __StationaryOrbit_NumericAnalysis_NewtonCoef__