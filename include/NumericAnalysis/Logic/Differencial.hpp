#ifndef __StationaryOrbit_NumericAnalysis_Differencial__
#define __StationaryOrbit_NumericAnalysis_Differencial__
#include "../Interface/IMathmaticFunction.hpp"
namespace StationaryOrbit::NumericAnalysis
{

	class Differencial final
		: IMathmaticFunction<double>
	{
	private:

		const IMathmaticFunction<double>& func;

		double Diff(const double& value, const double& h) const;

		double DefaultH(const double& value) const;

	public:

		Differencial(const IMathmaticFunction<double>& function);

		double Calc(const double& value, const double& h) const;

		double Calc(const double& value) const;
		double operator()(const double& value) const { return Calc(value); }

	};

}
#endif // __StationaryOrbit_NumericAnalysis_Differencial__