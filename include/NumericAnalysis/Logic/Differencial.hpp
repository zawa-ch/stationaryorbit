#ifndef __StationaryOrbit_NumericAnalysis_Differencial__
#define __StationaryOrbit_NumericAnalysis_Differencial__
#include "../Interface/IMathmaticFunction.hpp"
namespace StationaryOrbit::NumericAnalysis
{

	///	@a IMathmaticFunction<double> の微分関数を表します。
	class Differencial final
		: IMathmaticFunction<double>
	{
	private:

		const IMathmaticFunction<double>& func;

		double Diff(const double& value, const double& h) const;

		double DefaultH(const double& value) const;

	public:

		///	元の関数となる @a IMathmaticFunction<double> を指定し、このオブジェクトを初期化します。
		Differencial(const IMathmaticFunction<double>& function);

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
#endif // __StationaryOrbit_NumericAnalysis_Differencial__