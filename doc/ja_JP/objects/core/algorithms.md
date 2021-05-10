# Algorithms

[zawa_ch::StationaryOrbit](../../namespaces/zawa_ch/stationaryorbit.md) 名前空間  
[stationaryorbit/core.utilities.hpp](../../headers/stationaryorbit/core.utilities.hpp.md)で定義  

```C++
class Algorithms final;
```

このライブラリで使用するアルゴリズムを定義します  

## 概要

ライブラリで使用される基本的なアルゴリズムを実装します。  
このクラスのインスタンスを作成することはできません。また、継承することもできません。  

## 静的メンバ関数

- `integral_fraction`
    ```C++
    template<class Tp>
    static constexpr DivisionResult<Tp> integral_fraction(const Tp& numerator, const Tp& denominator, const Tp& scale);
    ```
    整数の除算と乗算を同時に行います。  

    **テンプレート引数**
    - `Tp` - 演算を行う整数型。型要件:[IntegralType](../../requirements/integraltype.md)を満たす型か、`bool`のどちらかである必要があります。  

    **引数**
    - `numerator` - 除算時の被除数。  
    - `denominator` - 除算時の除数。  
    - `scale` - 乗算時の乗数。  

    **例外**
    - `std::invalid_argument` - 分母に0が代入されました。  

- `boolean_and`
    -   ```C++
        static constexpr bool boolean_and(const bool& left, const bool& right);
        ```
        `bool`のand結合を行います。  
        このメソッドはちょうど`left&right`に等しい操作を行います。  

    -   ```C++
        static constexpr bool boolean_and(const std::initializer_list<bool>& list);
        ```
        `bool`のand結合を行います。  
        このメソッドは`std::initializer_list<bool>&`内のすべての値をand結合します。  

- `boolean_or`
    -   ```C++
        static constexpr bool boolean_or(const bool& left, const bool& right);
        ```
        `bool`のor結合を行います。  
        このメソッドはちょうど`left|right`に等しい操作を行います。  

    -   ```C++
        static constexpr bool boolean_or(const std::initializer_list<bool>& list);
        ```
        `bool`のor結合を行います。  
        このメソッドは`std::initializer_list<bool>&`内のすべての値をor結合します。  

- `boolean_xor`
    -   ```C++
        static constexpr bool boolean_xor(const bool& left, const bool& right);
        ```
        `bool`のxor結合を行います。  
        このメソッドはちょうど`left|right`に等しい操作を行います。  

    -   ```C++
        static constexpr bool boolean_xor(const std::initializer_list<bool>& list);
        ```
        `bool`のxor結合を行います。  
        このメソッドは`std::initializer_list<bool>&`内のすべての値をxor結合します。  

- `halfangle_sin`
    ```C++
    template<class T>
    static constexpr T halfangle_sin(const T& cos);
    ```
    半角公式によるsin(x/2)の導出を行います。

    **引数**
    - `cos` - cos(x)の値。

- `halfangle_cos`
    ```C++
    template<class T>
    static constexpr T halfangle_cos(const T& cos);
    ```
    半角公式によるcos(x/2)の導出を行います。

    **引数**
    - `cos` - cos(x)の値。

- `halfangle_tan`
    ```C++
    template<class T>
    static constexpr T halfangle_tan(const T& sin, const T& cos);
    ```
    半角公式によるtan(x/2)の導出を行います。

    **引数**
    - `sin` - sin(x)の値。
    - `cos` - cos(x)の値。
