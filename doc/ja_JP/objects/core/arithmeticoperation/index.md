# ArithmeticOperation

[zawa_ch::StationaryOrbit](../../namespaces/zawa_ch/stationaryorbit.md) 名前空間  
[stationaryorbit/core.utilities.hpp](../../headers/stationaryorbit/core.utilities.hpp.md)で定義  

```C++
class ArithmeticOperation final;
```

数値型による数値演算の拡張を行います  

## 概要

数値型\(型要件:[NumericalType](../../../requirements/numericaltype.md)を満たす型\)の演算の拡張を行います。  
このクラスのインスタンスを作成することはできません。また、継承することもできません。  

## メンバ型

- [AdditionResultStatus](additionresultstatus.md) - 加算を行った結果の状態を示すフラグ
- [AdditionResult](additionresult.md) - 加算を行った結果を格納する構造体
- [MultiplicationResultStatus](multiplicationresultstatus.md) - 乗算を行った結果の状態を示すフラグ
- [MultiplicationResult](multiplicationresult.md) - 乗算を行った結果を格納する構造体

## 静的メンバ関数

### 演算の拡張

- `add`
    ```C++
    template<typename T>
    static constexpr AdditionResult<T> add(const T& left, const T& right) noexcept;
    ```
    演算時のエラーをレポートする加算を行います。  

    **引数**
    - `left` - 演算子の左辺に代入される値。  
    - `right` - 演算子の右辺に代入される値。  

- `subtract`
    ```C++
    template<typename T>
    static constexpr AdditionResult<T> subtract(const T& left, const T& right) noexcept;
    ```
    演算時のエラーをレポートする減算を行います。  

    **引数**
    - `left` - 演算子の左辺に代入される値。  
    - `right` - 演算子の右辺に代入される値。  

- `multiply`
    ```C++
    template<typename T>
    static MultiplicationResult<T> multiply(const T& left, const T& right) noexcept;
    ```
    演算時のエラーをレポートする乗算を行います。  

    **引数**
    - `left` - 演算子の左辺に代入される値。  
    - `right` - 演算子の右辺に代入される値。  

- `divide`
    ```C++
    template<typename T>
    static MultiplicationResult<T> divide(const T& left, const T& right) noexcept;
    ```
    演算時のエラーをレポートする除算を行います。  

    **引数**
    - `left` - 演算子の左辺に代入される値。  
    - `right` - 演算子の右辺に代入される値。  

### 演算結果の飽和

- `add_saturate`
    ```C++
    template<typename T>
    static constexpr T add_saturate(const T& left, const T& right);
    ```
    演算後の結果を値域内に丸める加算を行います。  

    **引数**
    - `left` - 演算子の左辺に代入される値。  
    - `right` - 演算子の右辺に代入される値。  

- `subtract_saturate`
    ```C++
    template<typename T>
    static constexpr T subtract_saturate(const T& left, const T& right);
    ```
    演算後の結果を値域内に丸める減算を行います。  

    **引数**
    - `left` - 演算子の左辺に代入される値。  
    - `right` - 演算子の右辺に代入される値。  

- `multiply_saturate`
    ```C++
    template<typename T>
    static constexpr T multiply_saturate(const T& left, const T& right);
    ```
    演算後の結果を値域内に丸める乗算を行います。  

    **引数**
    - `left` - 演算子の左辺に代入される値。  
    - `right` - 演算子の右辺に代入される値。  

- `divide_saturate`
    ```C++
    template<typename T>
    static constexpr T divide_saturate(const T& left, const T& right);
    ```
    演算後の結果を値域内に丸める除算を行います。  

    **引数**
    - `left` - 演算子の左辺に代入される値。  
    - `right` - 演算子の右辺に代入される値。  

### 演算結果の値域チェック

- `add_checked`
    ```C++
    template<typename T>
    static constexpr T add_checked(const T& left, const T& right);
    ```
    演算結果が値域に収まらない場合に例外をスローする加算を行います。

    **引数**
    - `left` - 演算子の左辺に代入される値。  
    - `right` - 演算子の右辺に代入される値。  

- `subtract_checked`
    ```C++
    template<typename T>
    static constexpr T subtract_checked(const T& left, const T& right);
    ```
    演算結果が値域に収まらない場合に例外をスローする減算を行います。

    **引数**
    - `left` - 演算子の左辺に代入される値。  
    - `right` - 演算子の右辺に代入される値。  

- `multiply_checked`
    ```C++
    template<typename T>
    static constexpr T multiply_checked(const T& left, const T& right);
    ```
    演算結果が値域に収まらない場合に例外をスローする乗算を行います。

    **引数**
    - `left` - 演算子の左辺に代入される値。  
    - `right` - 演算子の右辺に代入される値。  

- `divide_checked`
    ```C++
    template<typename T>
    static constexpr T divide_checked(const T& left, const T& right);
    ```
    演算結果が値域に収まらない場合に例外をスローする除算を行います。

    **引数**
    - `left` - 演算子の左辺に代入される値。  
    - `right` - 演算子の右辺に代入される値。  

### 演算前の値域チェック

- `may_overflow_add`
    ```C++
    template<class Tp>
    static constexpr bool may_overflow_addition(const Tp& left, const Tp& right) noexcept;
    ```
    加算の演算結果が値域外となるかを取得します。

    **引数**
    - `left` - 演算子の左辺に代入される値。  
    - `right` - 演算子の右辺に代入される値。  

- `may_overflow_subtract`
    ```C++
    template<class Tp>
    static constexpr bool may_overflow_subtraction(const Tp& left, const Tp& right) noexcept;
    ```
    減算の演算結果が値域外となるかを取得します。

    **引数**
    - `left` - 演算子の左辺に代入される値。  
    - `right` - 演算子の右辺に代入される値。  

- `may_overflow_multiply`
    ```C++
    	template<class Tp>
    static constexpr bool may_overflow_multiplication(const Tp& left, const Tp& right) noexcept;
    ```
    乗算の演算結果が値域外となるかを取得します。

    **引数**
    - `left` - 演算子の左辺に代入される値。  
    - `right` - 演算子の右辺に代入される値。  

- `may_overflow_divide`
    ```C++
    template<class Tp>
    static constexpr bool may_overflow_division(const Tp& left, const Tp& right) noexcept;
    ```
    除算の演算結果が値域外となるかを取得します。

    **引数**
    - `left` - 演算子の左辺に代入される値。  
    - `right` - 演算子の右辺に代入される値。  
