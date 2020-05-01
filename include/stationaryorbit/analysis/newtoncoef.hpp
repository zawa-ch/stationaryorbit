#ifndef __StationaryOrbit_NumericAnalysis_NewtonCoef__
#define __StationaryOrbit_NumericAnalysis_NewtonCoef__
#include <vector>
#include "stationaryorbit/exception.hpp"
#include "stationaryorbit/core.numeral.hpp"
#include "mathematicfunction.hpp"
namespace zawa_ch::StationaryOrbit::Analysis
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
#endif // __StationaryOrbit_NumericAnalysis_NewtonCoef__