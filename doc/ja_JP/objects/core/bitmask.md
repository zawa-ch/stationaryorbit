# BitMask

[zawa_ch::StationaryOrbit](../../namespaces/zawa_ch/stationaryorbit.md) 名前空間  
[stationaryorbit/core.bitoperation.hpp](../../headers/stationaryorbit/core.bitoperation.hpp.md)で定義  

```C++
template<class T>
class BitMask final
```

ビット列をマスクする機能を提供します。

## 概要

マスクするためのビット列を保持し、マスクを用いたビット列の取得・変更を行います。  
このクラスは継承できません。  

## テンプレート引数

- `T` マスクのためのビット列の型。[BitSequenceType](../../requirements/bitsequencetype.md)の要件を満たす必要があります。  

## メンバ変数

- `mask`: `T`  
    このオブジェクトのマスク値。

## メンバ関数

### コンストラクタ

- `BitMask()`
    1. `constexpr BitMask()`
    2. `explicit constexpr Bitmask(const T& value) noexcept`
    3. `Bitmask(const BitMask<T>&)` (暗黙)
    4. `Bitmask(BitMask<T>&&)` (暗黙)

    1 ) 規定の`BitMask`を構築します。  
    2 ) マスク値を指定して`BitMask`を構築します。  
    - `value` マスクするを指定したビット列。
    3 ) コピーコンストラクタ。
    4 ) ムーブコンストラクタ。

### デストラクタ

- `~BitMask()` (暗黙)

### 観測

- `constexpr size_t begin_index() const noexcept`  
    このマスクが開始される(最初にビットが1となる)、LSBから数えたビット数を取得します。

- `constexpr size_t end_index() const noexcept`  
    このマスクが終了される(最後にビットが0となる)、LSBから数えたビット数を取得します。

- `constexpr size_t length() const noexcept`  
    マスクの開始から終了までのビットの長さを取得します。  

### マスク

- `constexpr T get_from(const T& source) const noexcept`  
    入力をマスク値に従ってマスクします。  
    - `source` 値を取得するソース。  

- `constexpr T get_aligned_from(const T& source) const noexcept`  
    入力をマスク値に従ってマスクし、LSBに詰めます。  
    - `source` 値を取得するソース。

- `constexpr T set_to(const T& destination, const T& value) const noexcept`  
    入力をマスク値に従って書き込みます。  
    - `destination` 値の設定先。
    - `value` 書き込みを行う値。

- `constexpr T set_to(const T& destination, const T& value) const noexcept`  
    LSBに詰められた入力をマスク値に従って書き込みます。  
    - `destination` 値の設定先。
    - `value` 書き込みを行う値。

### 演算

- operator
    1. `constexpr BitMask<T> operator~() const noexcept`
    2. `constexpr BitMask<T> operator|(const BitMask<T>& other) const noexcept`
    3. `constexpr BitMask<T> operator&(const BitMask<T>& other) const noexcept`
    4. `constexpr BitMask<T> operator^(const BitMask<T>& other) const noexcept`
    5. `constexpr BitMask<T>& operator|=(const BitMask<T>& other) noexcept`
    6. `constexpr BitMask<T>& operator&=(const BitMask<T>& other) noexcept`
    7. `constexpr BitMask<T>& operator^=(const BitMask<T>& other) noexcept`

    1 ) ビット論理否定演算。すべてのビットを反転します。  
    2 ) ビット論理和演算。ビットごとの論理和を取得します。  
    3 ) ビット論理積演算。ビットごとの論理積を取得します。  
    4 ) ビット排他的論理和演算。ビットごとの排他的論理和を取得します。  
    5 ) 複合代入演算。ビットごとの論理和を代入します。
    6 ) 複合代入演算。ビットごとの論理積を代入します。
    7 ) 複合代入演算。ビットごとの排他的論理和を代入します。

### 比較

- `equals()`
    1. `constexpr bool equals(const BitMask<T>& other) const noexcept`
    2. `constexpr bool operator==(const BitMask<T>& other) const noexcept`
    3. `constexpr bool operator!=(const BitMask<T>& other) const noexcept`

    1,2 ) 等価比較。ふたつのオブジェクトが等しいかを取得します。  
    3 ) 等価比較の否定。ふたつのオブジェクトが異なるかを取得します。  
