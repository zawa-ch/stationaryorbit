# BitCounter

[zawa_ch::StationaryOrbit](../../namespaces/zawa_ch/stationaryorbit.md) 名前空間  
[stationaryorbit/core.traits.hpp](../../headers/stationaryorbit/core.traits.hpp.md)で定義  

```C++
class BitCounter final;
```

特定の型のビット幅を計測します。  

## 概要

`BitCounter`は型のビット幅を計測するための機能を提供するクラスです。  
このクラスのインスタンスを作成することはできません。また、継承することもできません。  

## 静的メンバ関数

- `count()`
    ```C++
    template<class T, std::enable_if_t<...> = 0>
    static constexpr size_t count() noexcept;
    ```
    指定された型のビット幅を計測します。

    **テンプレート引数**
    - `T` ビット幅を計測する型。型要件:[BitSequenceType](../../requirements/bitsequencetype.md)を満たす必要があります。  

## 関連項目

- [zawa_ch::StationaryOrbit::BitWidth](../../objects/core/bitwidth.md)  
