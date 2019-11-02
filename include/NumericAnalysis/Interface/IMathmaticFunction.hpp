#ifndef __StationaryOrbit_NumericAnalysis_IMathmaticFunction__
#define __StationaryOrbit_NumericAnalysis_IMathmaticFunction__
namespace StationaryOrbit::NumericAnalysis
{

    /// T型の値を受け取り、T型の値を返す数学的な関数を実装します。
    template<class T>
    class IMathmaticFunction
    {
    public:

        virtual T Calc(const T& value) const = 0;

    };

}
#endif // __StationaryOrbit_NumericAnalysis_IMathmaticFunction__