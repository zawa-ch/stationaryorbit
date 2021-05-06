# EndianConverter

[zawa_ch::StationaryOrbit](../../namespaces/zawa_ch/stationaryorbit.md) 名前空間  
[stationaryorbit/core.bitoperation.hpp](../../headers/stationaryorbit/core.bitoperation.hpp.md)で定義  

```C++
template<Endians from, Endians dest>
class EndianConverter final;
```

エンディアンの変換を行います

## 概要

値型に対して、リトルエンディアン、ビッグエンディアンの間の変換を行います。  
このクラスは継承できません。  

## テンプレート引数

- `from` 変換元のエンディアン。
- `dest` 変換先のエンディアン。

## 静的メンバ関数

- `encode()`  
    ```C++
    template<class T>
    static constexpr std::array<std::byte, sizeof(T)> encode(const T& value);
    ```
    指定された値のエンディアンを`from`から`dest`に変換します。  

    **テンプレート引数**  
    - `T` - エンディアン変換を行う値の型。型要件[ValueType](../../requirements/valuetype.md)を満たす必要があります。  

    **引数**  
    - `value` - エンディアン変換を行う値。  

    **例外**  
    - [InvalidOperationException](invalidoperationexception.md) - 指定されたエンディアンの組み合わせに対する適切な変換が定義されていない場合にスローされます。  

- `decode()`  
    ```C++
    template<class T>
    static constexpr T decode(const std::array<std::byte, sizeof(T)>& data);
    ```
    指定された値のエンディアンを`dest`から`from`に変換します。  

    **テンプレート引数**  
    - `T` - エンディアン変換を行う値の型。型要件[ValueType](../../requirements/valuetype.md)を満たす必要があります。  

    **引数**  
    - `value` - エンディアン変換を行うビット列。  

    **例外**  
    - [InvalidOperationException](invalidoperationexception.md) - 指定されたエンディアンの組み合わせに対する適切な変換が定義されていない場合にスローされます。  

- `convert()`  
    ```C++
    template<size_t N>
    static constexpr std::array<std::byte, N> convert(const std::array<std::byte, N>& data);
    ```
    指定された`std::array`のバイト順序を`from`から`dest`に変換します。  

    **テンプレート引数**  
    - `N` - `std::array`の大きさ。バイト単位で指定します。  

    **引数**  
    - `data` - バイト順序変換を行うビット列。  

    **例外**  
    - [InvalidOperationException](invalidoperationexception.md) - 指定されたエンディアンの組み合わせに対する適切な変換が定義されていない場合にスローされます。  

## 特殊化

リトルエンディアン、ビッグエンディアンのそれぞれの変換のために、2つの`typedef`が提供されています。  

- `LittleEndian`
    ```C++
    typedef EndianConverter<Endians::native, Endian::little> LittleEndian;
    ```
    現在のバイトオーダーからリトルエンディアンへの変換を表す`EndianConverter`。  

- `BigEndian`
    ```C++
    typedef EndianConverter<Endians::native, Endian::big> BigEndian;
    ```
    現在のバイトオーダーからビッグエンディアンへの変換を表す`EndianConverter`。  
