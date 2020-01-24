#ifndef __StationaryOrbit_NumericAnalysis_IMathematicFunction__
#define __StationaryOrbit_NumericAnalysis_IMathematicFunction__
namespace StationaryOrbit::NumericAnalysis
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

}
#endif // __StationaryOrbit_NumericAnalysis_IMathematicFunction__