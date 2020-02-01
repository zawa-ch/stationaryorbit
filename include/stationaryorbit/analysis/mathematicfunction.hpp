#ifndef __StationaryOrbit_NumericAnalysis_MathematicFunction__
#define __StationaryOrbit_NumericAnalysis_MathematicFunction__
#include "stationaryorbit/exception/soexcept"
namespace zawa_ch::StationaryOrbit::Analysis
{

    /// @a T 型の値を受け取り、 @a T 型の値を返す数学的な関数を実装します。
    template<class T>
    class IMathematicFunction
    {
    public:

        /// この関数に値を代入した解を取得します。
        ///
        /// @param  value
        /// 代入する値。
        ///
        /// @return
        /// 計算を行い、得られた解が返ります。
        virtual T Calc(const T& value) const = 0;

    };

    /// @a T 型の値を受け取り、 @a T 型の値を返す数学的な関数を表します。
	template<class T>
	class MathematicFunction
		: public IMathematicFunction<T>
	{
	public:

		///	@a T 型の値を受け取り、 @a T 型の値を返す数学的な関数の実体。
		typedef T (*BaseFunc)(T);

	private:

		BaseFunc func;

	public:

		///	実体となる関数を指定してこのオブジェクトを初期化します。
		explicit MathematicFunction(BaseFunc function) : func(function) {}

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
#endif // __StationaryOrbit_NumericAnalysis_MathematicFunction__