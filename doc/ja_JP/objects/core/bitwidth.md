# BitWidth

[zawa_ch::StationaryOrbit](../../namespaces/zawa_ch/stationaryorbit.md) 名前空間  
[stationaryorbit/core.traits.hpp](../../headers/stationaryorbit/core.traits.hpp.md)で定義  

```C++
class BitWidth_t final;
```

指定された型のビット幅を識別します。  

## 概要

`BitWidth_t`は型のビット幅を識別するメタクラスです。  
このクラスに対する特殊化の試みは未定義動作です。  

## テンプレート引数

- `T` ビット幅を識別する型。型要件:[BitSequenceType](../../requirements/bitsequencetype.md)を満たす必要があります。  

## メンバ型

- `value_type`: `size_t` ([std::integral_constant](https://ja.cppreference.com/w/cpp/types/integral_constant)から継承)
- `type`: `std::integral_constant<size_t, ...>` ([std::integral_constant](https://ja.cppreference.com/w/cpp/types/integral_constant)から継承)

## 静的メンバ定数

- `size_t value` ([std::integral_constant](https://ja.cppreference.com/w/cpp/types/integral_constant)から継承)
    型`T`のビット幅が代入された定数

## メンバ関数

- 
    1. `constexpr operator size_t() const noexcept` ([std::integral_constant](https://ja.cppreference.com/w/cpp/types/integral_constant)から継承)
    2. `constexpr size_t operator()() const noexcept` ([std::integral_constant](https://ja.cppreference.com/w/cpp/types/integral_constant)から継承)

    ラップされた値を取得します。  

## ヘルパー変数テンプレート

- `bitwidth`  
    `template<class T> inline constexpr size_t bitwidth = BitWidth_t<T>::value;`  

## 関連項目

- [zawa_ch::StationaryOrbit::BitCounter](../../objects/core/bitcounter.md)  
