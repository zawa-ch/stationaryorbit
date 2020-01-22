#ifndef __StationaryOrbit_NumericAnalysis_IIntegral__
#define __StationaryOrbit_NumericAnalysis_IIntegral__
#include "../Interface/IMathmaticFunction.hpp"
namespace StationaryOrbit::NumericAnalysis
{

	///	@a IMathmaticFunction<double> の積分関数を実装します。
	class IIntegral
		: virtual public IMathmaticFunction<double>
	{
	public:

        /// この関数に値を代入した解を取得します。
        ///
        /// @param  value
        /// 代入する値。
        ///
        /// @return
        /// 計算を行い、得られた解が返ります。
        virtual double Calc(const double& value) const = 0;

	};

}
#endif // __StationaryOrbit_NumericAnalysis_IIntegral__