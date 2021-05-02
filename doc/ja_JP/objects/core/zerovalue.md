# ZeroValue_t

[zawa_ch::StationaryOrbit](../../namespaces/zawa_ch/stationaryorbit.md) 名前空間  
[stationaryorbit/core.utilities.hpp](../../headers/stationaryorbit/core.utilities.hpp.md)で定義  

```C++
struct ZeroValue_t final;
```

他の型に変換可能な零値を表します。

## 概要

`ZeroValue_t`は他の型において零として振る舞う値型です。オブジェクト自体は値を持たず、他の型へキャストすることによってのみその効果を持ちます。  

## メンバ関数

### コンストラクタ

- `ZeroValue_t()`
    1. `ZeroValue_t()` (暗黙)
    2. `ZeroValue_t(const ZeroValue_t&)` (暗黙)
    3. `ZeroValue_t(ZeroValue_t&&)` (暗黙)

### デストラクタ

- `~ZeroValue_t()` (暗黙)

### 変換

- `operator bool() const`  
    `bool`に変換します。常に`false`が返ります。  
    `bool`からの暗黙の変換ですべての整数型・浮動小数点型に暗黙に変換することができます。  

- `operator void*() const`  
    ポインタに変換します。常に`0x0`が返ります。  

- `operator std::nullptr_t() const`  
    `std::nullptr_t`に変換します。常に`nullptr`が返ります。  

- `operator std::byte() const`  
    `std::byte`に変換します。常に`std::byte{0}`が返ります。  

### 演算

- 
    1. `ZeroValue_t operator+() const`  
    2. `ZeroValue_t operator-() const`  
    3. `ZeroValue_t operator+(const ZeroValue_t&) const`
    4. `ZeroValue_t operator-(const ZeroValue_t&) const`
    5. `ZeroValue_t operator*(const ZeroValue_t&) const`
    6. `ZeroValue_t operator|(const ZeroValue_t&) const`
    7. `ZeroValue_t operator&(const ZeroValue_t&) const`
    8. `ZeroValue_t operator^(const ZeroValue_t&) const`
    9. `ZeroValue_t operator<<(int) const`
    10. `ZeroValue_t operator>>(int) const`
    11. `ZeroValue_t operator||(const ZeroValue_t&) const`
    12. `ZeroValue_t operator&&(const ZeroValue_t&) const`

    各種演算。`ZeroValue_t`では何も行わず、`ZeroValue_t`の新しいインスタンスを返します。  
    除算・剰余は常にゼロ除算となるため、定義されません。  

### 代入

- `operator=`
    1. `ZeroValue_t& operator=(const ZeroValue_t&)` (暗黙)
    2. `ZeroValue_t& operator=(ZeroValue_t&&)` (暗黙)

- 
    1. `ZeroValue_t& operator+=(const ZeroValue_t&)`
    2. `ZeroValue_t& operator-=(const ZeroValue_t&)`
    3. `ZeroValue_t& operator*=(const ZeroValue_t&)`
    4. `ZeroValue_t& operator|=(const ZeroValue_t&)`
    5. `ZeroValue_t& operator&=(const ZeroValue_t&)`
    6. `ZeroValue_t& operator^=(const ZeroValue_t&)`
    7. `ZeroValue_t& operator<<=(int)`
    8. `ZeroValue_t& operator>>=(int)`

    各種複合代入。`ZeroValue_t`では何も行わず、自身を返します。  
    除算・剰余は常にゼロ除算となるため、定義されません。  

### 比較

- `equals()`
    1. `bool equals(const ZeroValue&) const`
    2. `bool operator==(const ZeroValue&) const`
    3. `bool operator!=(const ZeroValue&) const`

    1,2 ) 等価比較。`ZeroValue_t`では常に`true`が返ります。  
    3 ) `equals()`を反転した結果が返ります。`ZeroValue_t`では常に`false`が返ります。  

- `compare()`
    1. `int compare(const ZeroValue&) const`
    2. `bool operator<(const ZeroValue&) const`
    3. `bool operator>(const ZeroValue&) const`
    4. `bool operator<=(const ZeroValue&) const`
    5. `bool operator>=(const ZeroValue&) const`

    1 ) 大小比較。`ZeroValue_t`では常に`0`が返ります。  
    2,3 ) 不等号演算子。`ZeroValue_t`では常に`false`が返ります。  
    4,5 ) 不等号演算子。`ZeroValue_t`では常に`true`が返ります。  

## 参照

- [Zero](zero.md) - この型のインスタンスを表す定数
