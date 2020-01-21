#ifndef __StationaryOrbit_NumericAnalysis_MathmaticFunction__
#define __StationaryOrbit_NumericAnalysis_MathmaticFunction__
#include "General/Exception"
#include "../Interface/IMathmaticFunction.hpp"
namespace StationaryOrbit::NumericAnalysis
{

    /// @a T 型の値を受け取り、 @a T 型の値を返す数学的な関数を表します。
	template<class T>
	class MathmaticFunction
		: public IMathmaticFunction<T>
	{
	public:

		///	@a T 型の値を受け取り、 @a T 型の値を返す数学的な関数の実体。
		typedef T (*BaseFunc)(T);

	private:

		BaseFunc func;

	public:

		///	実体となる関数を指定してこのオブジェクトを初期化します。
		explicit MathmaticFunction(BaseFunc function) : func(function) {}

        /// この関数に値を代入した解を取得します。
        ///
        /// @param  value
        /// 代入する値。
        ///
        /// @return
        /// 計算を行い、得られた解が返ります。
		T Calc(const T& value) const
		{
			if (func == NULL) throw NullReferenceException("function pointer must be non-null value");
			return func(value);
		}
		T operator()(const T& value) const { return Calc(value); }

	};

}
#endif // __StationaryOrbit_NumericAnalysis_MathmaticFunction__