# MultiplicationResultStatus

[ArithmeticOperation](index.md) » `MultiplicationResultStatus`

[zawa_ch::StationaryOrbit::ArithmeticOperation](index.md) クラス  
[stationaryorbit/core.utilities.hpp](../../headers/stationaryorbit/core.utilities.hpp.md)で定義  

```C++
enum class MultiplicationResultStatus { no_error = 0, overflow = 1, divide_by_zero = -1 };
```

乗算を行った結果の状態を示すフラグ

## 概要

乗除算を行った結果がどのような状態になっているかを表すためのフラグです。  

## メンバ定数

- `no_error` - 正しく乗除算が行われたことを示す定数。  
- `overflow` - オーバーフローが発生したことを示す定数。  
- `divide_by_zero` - 0除算が行われたことを示す定数。  

## 関連項目

- [zawa_ch::StationaryOrbit::ArithmeticOperation](index.md)
- [zawa_ch::StationaryOrbit::ArithmeticOperation::MultiplicationResult](multiplicationresult.md)
