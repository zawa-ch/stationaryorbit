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
    -   ```C++
        constexpr BitMask();
        ```
        規定の`BitMask`を構築します。  

    -   ```C++
        explicit constexpr Bitmask(const T& value) noexcept;
        ```
        マスク値を指定して`BitMask`を構築します。  

        **引数**  
        - `value` マスクを指定したビット列。

    - `Bitmask(const BitMask<T>&);` (暗黙)  
    コピーコンストラクタ。  

    - `Bitmask(BitMask<T>&&);` (暗黙)  
    ムーブコンストラクタ。  

### デストラクタ

- `~BitMask()` (暗黙)

### 観測

- `begin_index()`
    ```C++
    constexpr size_t begin_index() const noexcept;
    ```
    このマスクが開始される(最初にビットが1となる)、LSBから数えたビット数を取得します。

- `end_index()`
    ```C++
    constexpr size_t end_index() const noexcept;
    ```
    このマスクが終了される(最後にビットが0となる)、LSBから数えたビット数を取得します。

- `length()`
    ```C++
    constexpr size_t length() const noexcept;
    ```
    マスクの開始から終了までのビットの長さを取得します。  

### マスク

- `get_from()`
    ```C++
    constexpr T get_from(const T& source) const noexcept;
    ```
    入力をマスク値に従ってマスクします。  

    **引数**
    - `source` 値を取得するソース。  

- `get_aligned_from()`
    ```C++
    constexpr T get_aligned_from(const T& source) const noexcept;
    ```
    入力をマスク値に従ってマスクし、LSBに詰めます。  

    **引数**
    - `source` 値を取得するソース。  

- `set_to()`
    ```C++
    constexpr T set_to(const T& destination, const T& value) const noexcept;
    ```
    入力をマスク値に従って書き込みます。  

    **引数**
    - `destination` 値の設定先。  
    - `value` 書き込みを行う値。  

- `set_aligned_to()`
    ```C++
    constexpr T set_aligned_to(const T& destination, const T& value) const noexcept;
    ```
    LSBに詰められた入力をマスク値に従って書き込みます。  

    **引数**
    - `destination` 値の設定先。  
    - `value` 書き込みを行う値。  

### 演算

- 
    -   ```C++
        constexpr BitMask<T> operator~() const noexcept;
        ```
        ビット論理否定演算。すべてのビットを反転します。  

    -   ```C++
        constexpr BitMask<T> operator|(const BitMask<T>& other) const noexcept;
        ```
        ビット論理和演算。ビットごとの論理和を取得します。  

    -   ```C++
        constexpr BitMask<T> operator&(const BitMask<T>& other) const noexcept;
        ```
        ビット論理積演算。ビットごとの論理積を取得します。  

    -   ```C++
        constexpr BitMask<T> operator^(const BitMask<T>& other) const noexcept;
        ```
        ビット排他的論理和演算。ビットごとの排他的論理和を取得します。  

    -   ```C++
        constexpr BitMask<T>& operator|=(const BitMask<T>& other) noexcept;
        ```
        複合代入演算。ビットごとの論理和を代入します。

    -   ```C++
        constexpr BitMask<T>& operator&=(const BitMask<T>& other) noexcept;
        ```
        複合代入演算。ビットごとの論理積を代入します。

    -   ```C++
        constexpr BitMask<T>& operator^=(const BitMask<T>& other) noexcept;
        ```
        複合代入演算。ビットごとの排他的論理和を代入します。

### 比較

- `equals()`
    -   ```C++
        constexpr bool equals(const BitMask<T>& other) const noexcept;
        ```
        等価比較。ふたつのオブジェクトが等しいかを取得します。  

    -   ```C++
        constexpr bool operator==(const BitMask<T>& other) const noexcept;
        ```
        等価比較。ふたつのオブジェクトが等しいかを取得します。  

    -   ```C++
        constexpr bool operator!=(const BitMask<T>& other) const noexcept;
        ```
        等価比較の否定。ふたつのオブジェクトが異なるかを取得します。  
