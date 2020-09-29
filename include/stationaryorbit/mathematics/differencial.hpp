//	stationaryorbit/mathematics/differencial
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
#ifndef __stationaryorbit_mathematics_differencial__
#define __stationaryorbit_mathematics_differencial__
#include "mathematicfunction.hpp"
namespace zawa_ch::StationaryOrbit::Mathematics
{

	///	@a IMathematicFunction<double> の微分関数を表します。
	class Differencial final
		: IMathematicFunction<double>
	{
	private:

		const IMathematicFunction<double>& func;

		double Diff(const double& value, const double& h) const;

		double DefaultH(const double& value) const;

	public:

		///	元の関数となる @a IMathematicFunction<double> を指定し、このオブジェクトを初期化します。
		Differencial(const IMathematicFunction<double>& function);

		///	微分される関数の @a IMathematicFunction<double> オブジェクトの参照を取得します。
		const IMathematicFunction<double>& Function() const { return func; }

        /// この関数に値を代入した解を取得します。
        ///
        /// @param  value
        /// 代入する値。
		///
		/// @param	h
		///	微分の刻み幅。
        ///
        /// @return
        /// 計算を行い、得られた解が返ります。
		double Calc(const double& value, const double& h) const;

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
#endif // __stationaryorbit_mathematics_differencial__