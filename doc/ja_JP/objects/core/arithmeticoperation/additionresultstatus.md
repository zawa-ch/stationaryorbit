# AdditionResultStatus

[ArithmeticOperation](index.md) » `AdditionResultStatus`

[zawa_ch::StationaryOrbit::ArithmeticOperation](index.md) クラス  
[stationaryorbit/core.utilities.hpp](../../headers/stationaryorbit/core.utilities.hpp.md)で定義  

```C++
enum class AdditionResultStatus { no_error = 0, overflow_positive = 1, overflow_negative = -1 };
```

加算を行った結果の状態を示すフラグ

## 概要

加減算を行った結果がどのような状態になっているかを表すためのフラグです。  

## メンバ定数

- `no_error` - 正しく加減算が行われたことを示す定数。  
- `overflow_positive` - 正方向のオーバーフローが発生したことを示す定数。  
- `overflow_negative` - 負方向のオーバーフローが発生したことを示す定数。  

## 関連項目

- [zawa_ch::StationaryOrbit::ArithmeticOperation](index.md)
- [zawa_ch::StationaryOrbit::ArithmeticOperation::AdditionResult](additionresult.md)
