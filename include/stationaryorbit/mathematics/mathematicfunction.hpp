#ifndef __stationaryorbit_mathematics_mathematicfunction__
#define __stationaryorbit_mathematics_mathematicfunction__
#include <functional>
#include "stationaryorbit/exception.hpp"
namespace zawa_ch::StationaryOrbit::Mathematics
{

    /// @a T 型の値を受け取り、 @a T 型の値を返す数学的な関数を実装します。
    template<class T>
    class IMathematicFunction
    {
    public:
        /// この関数に値を代入した解を取得します。
        /// @param  value
        /// 代入する値。
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
		typedef std::function<T(T)> HandlerType;
	private:
		HandlerType func;
	public:
		///	実体となる関数を指定してこのオブジェクトを初期化します。
		explicit MathematicFunction(HandlerType function) : func(function) {}
        /// この関数に値を代入した解を取得します。
        /// @param  value
        /// 代入する値。
        /// @return
        /// 計算を行い、得られた解が返ります。
		T Calc(const T& value) const { return func(value); }
		T operator()(const T& value) const { return Calc(value); }
	};

}
#endif // __stationaryorbit_mathematics_mathematicfunction_