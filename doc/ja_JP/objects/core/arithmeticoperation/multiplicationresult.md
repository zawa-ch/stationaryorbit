# MultiplicationResult

[ArithmeticOperation](index.md) » `MultiplicationResult`

[zawa_ch::StationaryOrbit::ArithmeticOperation](index.md) クラス  
[stationaryorbit/core.utilities.hpp](../../headers/stationaryorbit/core.utilities.hpp.md)で定義  

```C++
template<typename T, typename Tp = typename Traits::PromotionResult<T>>
struct MultiplicationResult final;
```

乗算を行った結果を格納する構造体

## 概要

乗除算を行った結果を格納します。  
このクラスは継承できません。  

## テンプレート引数

- `T` - 乗除算を行う型。型要件:[NumericalType](../../../requirements/numericaltype.md)を満たす必要があります。
- `Tp`: `Traits::PromotionResult<T>`

## メンバ変数

- `result`: `Tp` - 演算結果の内容
- `status`: [MultiplicationResultStatus](multiplicationresultstatus.md) - 演算結果の状態

## 関連項目

- [zawa_ch::StationaryOrbit::ArithmeticOperation](index.md)
- [zawa_ch::StationaryOrbit::ArithmeticOperation::MultiplicationResultStatus](multiplicationresultstatus.md)
