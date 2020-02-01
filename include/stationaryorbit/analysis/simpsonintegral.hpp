#ifndef __StationaryOrbit_NumericAnalysis_SimpsonIntegral__
#define __StationaryOrbit_NumericAnalysis_SimpsonIntegral__
#include "../Interface/IIntegral.hpp"
#include "../Logic/MidpointIntegral.hpp"
#include "../Logic/TrapeziumIntegral.hpp"
namespace StationaryOrbit::NumericAnalysis
{

	///	シンプソン則を用いた数値積分を行う関数を表します。
	class SimpsonIntegral
		: virtual public IIntegral
	{
	private:

		const IMathematicFunction<double>& _func;
		Range<double, true, true> _irange;

	public:

		SimpsonIntegral(const IMathematicFunction<double>& function, const Range<double, true, true>& integrationrange);

		///	積分される関数の @a IMathematicFunction<double> オブジェクトの参照を取得します。
		const IMathematicFunction<double>& Function() const;

		///	定積分の範囲を取得します。
		Range<double, true, true> getIntegrationRange() const;

		/// この関数に値を代入した解を取得します。
		///
		/// @param  value
		/// 代入する値。
		///
		/// @return
		/// 計算を行い、得られた解が返ります。
		double Calc(const double& value) const;

		/// この関数に値を代入した解を取得します。
		///
		/// @param  value
		/// 代入する値。
		///
		///	@param	div
		///	計算区間の分割数。
		///
		/// @return
		/// 計算を行い、得られた解が返ります。
		double Calc(const double& value, size_t div) const;

	};

}
#endif // __StationaryOrbit_NumericAnalysis_SimpsonIntegral__