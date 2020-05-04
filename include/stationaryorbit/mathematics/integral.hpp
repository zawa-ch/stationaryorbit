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
		/// @param  value
		/// 代入する値。
		/// @return
		/// 計算を行い、得られた解が返ります。
		virtual double Calc(const double& value) const = 0;

	};

	///	中点則を用いた数値積分を行う関数を表します。
	class MidpointIntegral
		: virtual public IIntegral
	{
	private:
		const IMathematicFunction<double>& _func;
		Range<double, true, true> _irange;
	public:
		MidpointIntegral(const IMathematicFunction<double>& function, const Range<double, true, true>& integrationrange);
		///	積分される関数の @a IMathematicFunction<double> オブジェクトの参照を取得します。
		const IMathematicFunction<double>& Function() const;
		///	定積分の範囲を取得します。
		Range<double, true, true> getIntegrationRange() const;
		/// この関数に値を代入した解を取得します。
		/// @param  value
		/// 代入する値。
		/// @return
		/// 計算を行い、得られた解が返ります。
		double Calc(const double& value) const;
		/// この関数に値を代入した解を取得します。
		/// @param  value
		/// 代入する値。
		///	@param	div
		///	計算区間の分割数。
		/// @return
		/// 計算を行い、得られた解が返ります。
		double Calc(const double& value, size_t div) const;
	};

	///	台形則を用いた数値積分を行う関数を表します。
	class TrapeziumIntegral
		: virtual public IIntegral
	{
	private:
		const IMathematicFunction<double>& _func;
		Range<double, true, true> _irange;
	public:
		TrapeziumIntegral(const IMathematicFunction<double>& function, const Range<double, true, true>& integrationrange);
		///	積分される関数の @a IMathematicFunction<double> オブジェクトの参照を取得します。
		const IMathematicFunction<double>& Function() const;
		///	定積分の範囲を取得します。
		Range<double, true, true> getIntegrationRange() const;
		/// この関数に値を代入した解を取得します。
		/// @param  value
		/// 代入する値。
		/// @return
		/// 計算を行い、得られた解が返ります。
		double Calc(const double& value) const;
		/// この関数に値を代入した解を取得します。
		/// @param  value
		/// 代入する値。
		///	@param	div
		///	計算区間の分割数。
		/// @return
		/// 計算を行い、得られた解が返ります。
		double Calc(const double& value, size_t div) const;
	};

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
		/// @param  value
		/// 代入する値。
		/// @return
		/// 計算を行い、得られた解が返ります。
		double Calc(const double& value) const;
		/// この関数に値を代入した解を取得します。
		/// @param  value
		/// 代入する値。
		///	@param	div
		///	計算区間の分割数。
		/// @return
		/// 計算を行い、得られた解が返ります。
		double Calc(const double& value, size_t div) const;
	};
}
#endif // __stationaryorbit_mathematics_integral__