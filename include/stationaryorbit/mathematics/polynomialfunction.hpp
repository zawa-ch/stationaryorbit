//	stationaryorbit/mathematics/polynomialfunction
//	Copyright 2020 zawa-ch.
//	GPLv3 (or later) license
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//	See the GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program.
//	If not, see <http://www.gnu.org/licenses/>.
//
#ifndef __stationaryorbit_mathematics_polynomialfunction__
#define __stationaryorbit_mathematics_polynomialfunction__
#include <vector>
#include "stationaryorbit/core.exception.hpp"
#include "mathematicfunction.hpp"
namespace zawa_ch::StationaryOrbit::Mathematics
{

	///	実数の多項式を表します。
	class PolynomialFunction
		: public IMathematicFunction<double>
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

        /// この関数に値を代入した解を取得します。
        ///
        /// @param  value
        /// 代入する値。
        ///
        /// @return
        /// 計算を行い、得られた解が返ります。
		double Calc(const double& value) const;
		double operator()(const double& value) const { return Calc(value); }

	};

}
#endif // __stationaryorbit_mathematics_polynomialfunction__