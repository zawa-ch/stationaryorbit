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
    -   ```C++
        constexpr BitReference(std::byte& reference, size_t bit);
        ```
        指定したビットへの参照を作成します。  

    - `BitReference(const BitReference&)` (暗黙)  
        コピーコンストラクタ。  

    - `BitReference(BitReference&&)` (暗黙)  
        ムーブコンストラクタ。  


### デストラクタ

- `~BitReference()` (暗黙)

### 参照

- `get_value()`
    -   ```C++
        constexpr bool get_value() const;
        ```
    -   ```C++
        constexpr operator bool() const;
        ```

    参照先の値を取得します。  

- `set_value()`
    -   ```C++
        constexpr void set_value(bool value);
        ```
    -   ```C++
        constexpr BitReference& operator=(bool value);
        ```

    参照先に値を設定します。  

    **引数**
    - `value` 設定する値。
