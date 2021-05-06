# EndianValueType

[zawa_ch::StationaryOrbit](../../namespaces/zawa_ch/stationaryorbit.md) 名前空間  
[stationaryorbit/core.bitoperation.hpp](../../headers/stationaryorbit/core.bitoperation.hpp.md)で定義  

```C++
template<class Tp, Endians order = Endians::native>
class EndianValueType final;
```

スカラー型を特定のバイトオーダーで格納します

## 概要

スカラー型を指定されたバイトオーダーでメモリ上に格納します。  
このクラスは継承できません。  

## テンプレート引数

- `Tp` 格納する値の型。型要件:[ValueType](../../requirements/valuetype.md)を満たす必要があります。  
- `order` メモリに配置する際のバイトオーダー。

## メンバ型

- `ValueType`  
    ```C++
    typedef Tp ValueType;
    ```
    格納されている値の型。  

- `DataType`  
    ```C++
    typedef std::array<std::byte, sizeof(Tp)> DataType;
    ```
    内部でデータを格納するための型。  

## 静的メンバ定数

- `endian`: `Endians`  
    ```C++
    static constexpr Endians Endian = order;
    ```
    メモリに配置する際のバイトオーダー。

## メンバ関数

### コンストラクタ

- `EndianValueType()`
    -   ```C++
        EndianValueType() = default;
        ```
        規定値で`EndianValueType`を構築します。  

    -   ```C++
        constexpr EndianValueType(const ValueType& value);
        ```
        `EndianValueType`を指定された値で構築します。  

        **引数**
        - `value` - 構築時に代入する値。  

    -   ```C++
        template<Endians from>
        constexpr EndianValueType(const EndianValueType<Tp, from>& value);
        ```
        異なるエンディアンの`EndianValueType`からエンディアンを変換します。  

        **引数**
        - `value` - 変換元となる`EndianValueType`。

    - `EndianValueType(const EndianValueType<Tp, order>&)` (暗黙)

    - `EndianValueType(EndianValueType<Tp, order>&&)` (暗黙)

### 観測

- `value()`  
    ```C++
    constexpr ValueType value() const;
    ```
    このオブジェクトの値を取得します。  

- `data()`
    ```C++
    constexpr const DataType& data() const;
    ```
    このオブジェクトが格納されているデータに直接アクセスします。  

## 特殊化

リトルエンディアン、ビッグエンディアンのそれぞれにおける組み込みのスカラー型のために、12の`typedef`が提供されています。  

- `uint8be_t`
    ```C++
    typedef EndianValueType<uint8_t, Endians::big> uint8be_t;
    ```

    リトルエンディアンとして格納される`uint8_t`。  

- `uint16be_t`
    ```C++
    typedef EndianValueType<uint16_t, Endians::big> uint16be_t;
    ```

    リトルエンディアンとして格納される`uint16_t`。  

- `uint32be_t`
    ```C++
    typedef EndianValueType<uint32_t, Endians::big> uint32be_t;
    ```

    リトルエンディアンとして格納される`uint32_t`。  

- `uint64be_t`
    ```C++
    typedef EndianValueType<uint64_t, Endians::big> uint64be_t;
    ```

    リトルエンディアンとして格納される`uint64_t`。  

- `float32be_t`
    ```C++
    typedef EndianValueType<float, Endians::big> float32be_t;
    ```

    リトルエンディアンとして格納される`float`。  

- `float64be_t`
    ```C++
    typedef EndianValueType<double, Endians::big> float64be_t;
    ```

    リトルエンディアンとして格納される`double`。  

- `uint8le_t`
    ```C++
    typedef EndianValueType<uint8_t, Endians::little> uint8le_t;
    ```

    ビッグエンディアンとして格納される`uint8_t`。  

- `uint16le_t`
    ```C++
    typedef EndianValueType<uint16_t, Endians::little> uint16le_t;
    ```

    ビッグエンディアンとして格納される`uint16_t`。  

- `uint32le_t`
    ```C++
    typedef EndianValueType<uint32_t, Endians::little> uint32le_t;
    ```

    ビッグエンディアンとして格納される`uint32_t`。  

- `uint64le_t`
    ```C++
    typedef EndianValueType<uint64_t, Endians::little> uint64le_t;
    ```

    ビッグエンディアンとして格納される`uint64_t`。  

- `float32le_t`
    ```C++
    typedef EndianValueType<float, Endians::little> float32le_t;
    ```

    ビッグエンディアンとして格納される`float`。  

- `float64le_t`
    ```C++
    typedef EndianValueType<double, Endians::little> float64le_t;
    ```

    ビッグエンディアンとして格納される`double`。  
