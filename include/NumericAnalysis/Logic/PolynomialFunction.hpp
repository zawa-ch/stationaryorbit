#ifndef __StationaryOrbit_NumericAnalysis_PolynomialFunction__
#define __StationaryOrbit_NumericAnalysis_PolynomialFunction__
#include <vector>
#include "General/Exception"
#include "../Interface/IMathmaticFunction.hpp"
namespace StationaryOrbit::NumericAnalysis
{

	///	実数の多項式を表します。
	class PolynomialFunction
		: public IMathmaticFunction<double>
	{
	private:

		std::vector<double> num;

	public:

		///	空のオブジェクトを作成します。
		PolynomialFunction() = default;

		///	多項式のオブジェクトを初期化します。
		///	x^n * num[n-1] + ... x^2 * num[2] + x * num[1] + num[0] の順で計算されます。
		explicit PolynomialFunction(const std::vector<double>& value);

		///	多項式への参照を取得します。
		std::vector<double>& Polynomial() { return num; }

		///	多項式を取得します。
		std::vector<double> getPolynomial() const { return num; }

		///	この多項式に値を代入し、値を計算します。
		double Calc(const double& value) const;
		double operator()(const double& value) const { return Calc(value); }

	};

}
#endif // __StationaryOrbit_NumericAnalysis_PolynomialFunction__