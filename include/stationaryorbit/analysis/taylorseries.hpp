#ifndef __StationaryOrbit_NumericAnalusis_TaylorSeries__
#define __StationaryOrbit_NumericAnalusis_TaylorSeries__
#include "stationaryorbit/exception.hpp"
#include "mathematicfunction.hpp"
namespace zawa_ch::StationaryOrbit::Analysis
{

	///	Σ(k=0 → n-1, (f(a)/((dx^k)*k!)) * (x-a)^k )によるテイラー級数を表します。
	class TaylorSeries
		: public IMathematicFunction<double>
	{
	public:

		///	任意の回数の微分が可能な固定点の関数。
		typedef double (*BaseFunction)(const size_t&);

		///	指定された値の次の値を返す関数。
		typedef size_t (*SuccessorFunction)(const size_t&);

	private:

		BaseFunction func;
		SuccessorFunction suc;
		double base;
		size_t init;

	public:

		///	関数とその関数の点を指定してオブジェクトを初期化します。
		///
		///	@param	func
		///	特定の点xにおいて、任意回数の微分をサポートする関数。
		///
		///	@param	base
		///	級数の基点となる点xの値。
		TaylorSeries(BaseFunction func, const double& basep);

		///	関数とその関数の点を指定してオブジェクトを初期化します。
		///
		///	@param	func
		///	特定の点xにおいて、任意回数の微分をサポートする関数。
		///
		///	@param	base
		///	級数の基点となる点xの値。
		///
		///	@param	successor
		///	指定された値の次の値を返す関数。
		TaylorSeries(BaseFunction func, const double& basep, SuccessorFunction successor, size_t init);

		///	級数に値を代入し、値を計算します。
		///	値が収束した時点で計算は切り上げられます。
		///
		///	@param	value
		///	求める関数の引数。
		///
		///	@param	ceiling
		///	繰り返し回数の上限。
		///
		///	@exception	NullReferenceException
		///	関数にNULLを代入した状態で計算を行うことはできません。
		double Calc(const double& value, size_t ceiling) const;
		double operator()(const double& value, size_t ceiling) const { return Calc(value, ceiling); }

		///	級数に値を代入し、値を計算します。
		///	値が収束した時点で計算は切り上げられます。
		///
		///	@param	value
		///	求める関数の引数。
		///
		///	@exception	NullReferenceException
		///	関数にNULLを代入した状態で計算を行うことはできません。
		double Calc(const double& value) const;
		double operator()(const double& value) const { return Calc(value); }

		///	デフォルトの後続関数。
		///	value + 1 を返します。
		static size_t DefaultSuc(const size_t& value);

	};

}
#endif // __StationaryOrbit_NumericAnalusis_TaylorSeries__