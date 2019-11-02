#ifndef __StationaryOrbit_NumericAnalysis_PolynomialFunction__
#define __StationaryOrbit_NumericAnalysis_PolynomialFunction__
#include <vector>
#include "General/Exception"
#include "../Interface/IMathmaticFunction.hpp"
namespace StationaryOrbit::NumericAnalysis
{

	///	分子と分母を持つ多項式を表します。
	class PolynomialFunction
		: IMathmaticFunction<double>
	{
	private:

		std::vector<double> num;
		std::vector<double> denom;

	public:

		///	空のオブジェクトを作成します。
		PolynomialFunction() = default;

		///	分子の項を指定して多項式のオブジェクトを初期化します。
		///	x^n * num[n-1] + ... x^2 * num[2] + x * num[1] + num[0] の順で計算されます。
		explicit PolynomialFunction(const std::vector<double>& numerator);

		///	分子・分母の各項を指定して多項式のオブジェクトを初期化します。
		///	(x^n * num[n-1] + ... x * num[1] + num[0])/(x^n * denom[n-1] + ... x * denom[1] + denom[0]) の順で計算されます。
		PolynomialFunction(const std::vector<double>& numerator, const std::vector<double>& denominator);

		///	多項式の分子部分への参照を取得します。
		std::vector<double>& Numerator() { return num; }

		///	多項式の分子部分を取得します。
		std::vector<double> getNumerator() const { return num; }

		///	多項式の分母部分への参照を取得します。
		std::vector<double>& Denominator() { return denom; }

		///	多項式の分母部分を取得します。
		std::vector<double> getDenominator() const { return denom; }

		///	この多項式に値を代入し、値を計算します。
		double Calc(const double& value) const;

		double operator()(const double& value) const { return Calc(value); }

	};

}
#endif // __StationaryOrbit_NumericAnalysis_PolynomialFunction__