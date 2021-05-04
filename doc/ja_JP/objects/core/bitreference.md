# BitReference

[zawa_ch::StationaryOrbit](../../namespaces/zawa_ch/stationaryorbit.md) 名前空間  
[stationaryorbit/core.bitoperation.hpp](../../headers/stationaryorbit/core.bitoperation.hpp.md)で定義  

```C++
class BitReference final
```

特定のビットへの参照を行います。

## 概要

特定のビットへの参照を保持し、ビット単位でのアクセスを行います。  
このクラスは継承できません。

## メンバ関数

### コンストラクタ

- `BitReference()`
    1. `constexpr BitReference(std::byte& reference, size_t bit)`
    2. `BitReference(const BitReference&)` (暗黙)
    3. `BitReference(BitReference&&)` (暗黙)

    1 ) 指定したビットへの参照を作成します。  
    2 ) コピーコンストラクタ。  
    3 ) ムーブコンストラクタ。  

### デストラクタ

- `~BitReference()` (暗黙)

### 参照

- 
    1. `constexpr bool get_value() const`  
    2. `constexpr operator bool() const`  

    参照先の値を取得します。  

- 
    1. `constexpr void set_value(bool value)`  
    2. `constexpr BitReference& operator=(bool value)`

    参照先に値を設定します。  
    - `value` 設定する値。
