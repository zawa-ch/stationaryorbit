#ifndef __StationaryOrbit_NumericAnalysis_Differencial__
#define __StationaryOrbit_NumericAnalysis_Differencial__
#include "../Interface/IMathematicFunction.hpp"
namespace StationaryOrbit::NumericAnalysis
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
#endif // __StationaryOrbit_NumericAnalysis_Differencial__