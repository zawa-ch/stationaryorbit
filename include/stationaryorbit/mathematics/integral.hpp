#ifndef __stationaryorbit_mathematics_integral__
#define __stationaryorbit_mathematics_integral__
#include "stationaryorbit/core.numeral.hpp"
#include "mathematicfunction.hpp"
namespace zawa_ch::StationaryOrbit::Mathematics
{

	///	@a IMathematicFunction<double> の有限区間における定積分の関数を実装します。
	class IIntegral
		: virtual public IMathematicFunction<double>
	{
	public:

		///	積分される関数の @a IMathematicFunction<double> オブジェクトの参照を取得します。
		virtual const IMathematicFunction<double>& Function() const = 0;

		///	定積分の範囲を取得します。
		virtual Range<double, true, true> getIntegrationRange() const = 0;

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
#endif // __stationaryorbit_mathematics_integral__