# EndianConverter

[zawa_ch::StationaryOrbit](../../namespaces/zawa_ch/stationaryorbit.md) 名前空間  
[stationaryorbit/core.bitoperation.hpp](../../headers/stationaryorbit/core.bitoperation.hpp.md)で定義  

```C++
template<Endians from, Endians dest>
class EndianConverter final
```

エンディアンの変換を行います

## 概要

値型に対して、リトルエンディアン、ビッグエンディアンの間の変換を行います。  
このクラスは継承できません。  

## テンプレート引数

- `from` 変換元のエンディアン。
- `dest` 変換先のエンディアン。

## 静的メンバ関数

- `convert()`  
    ```C++
    template<class T>
    static constexpr T convert(const T& value);
    ```
    指定された値のエンディアンを`from`から`dest`に変換します。  

    **テンプレート引数**  
    - `T` - エンディアン変換を行う値の型。型要件[ValueType](../../requirements/valuetype.md)を満たす必要があります。  

    **引数**  
    - `value` - エンディアン変換を行う値。  

    **例外**  
    - [InvalidOperationException](invalidoperationexception.md) - 指定されたエンディアンの組み合わせに対する適切な変換が定義されていない場合にスローされます。  

## ヘルパーテンプレート型

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
