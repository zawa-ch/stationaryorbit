//	stationaryorbit/mathematics/newtoncoef
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
#ifndef __stationaryorbit_mathematics_newtoncoef__
#define __stationaryorbit_mathematics_newtoncoef__
#include <vector>
#include "stationaryorbit/core.exception.hpp"
#include "stationaryorbit/core.numeral.hpp"
#include "mathematicfunction.hpp"
namespace zawa_ch::StationaryOrbit::Mathematics
{

	///	ニュートン補完による関数を表します。
	class NewtonCoef
		: public IMathematicFunction<double>
	{
	private:

		///	区間を表すx軸のリスト。
		std::vector<double> x;

		///	各区間における補完係数のリスト。
		std::vector<double> b;

		///	追加された座標の値を基に補完係数を更新します。
		void Complete();

	public:

		///	@a Vector2d のリストからこのオブジェクトを構築します。
		explicit NewtonCoef(const std::vector<Vector2d>& list);

		///	xの値のリストとそれに対応する解のリストからこのオブジェクトを構築します。
		NewtonCoef(const IMathematicFunction<double>& func, const std::vector<double> xlist);

		///	x軸の値のリストへの参照を取得します。
		std::vector<double>& X() { return x; }

		///	x軸のリストを取得します。
		std::vector<double> getX() const { return x; }

		///	補完係数のリストを取得します。
		std::vector<double> getB() const { return b; }

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
#endif // __stationaryorbit_mathematics_newtoncoef_