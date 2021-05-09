# ObjectHolder

[zawa_ch::StationaryOrbit](../../namespaces/zawa_ch/stationaryorbit.md) 名前空間  
[stationaryorbit/core.utilities.hpp](../../headers/stationaryorbit/core.utilities.hpp.md)で定義  

```C++
template<class T, class = std::enable_if_t<!std::is_const_v<T>>>
class ObjectHolder final;   // #1

template<class T>
class ObjectHolder<T, std::enable_if_t<(!std::is_const_v<T>) && std::is_copy_constructible_v<T>>> final;    // #2
```

オブジェクトの所有権にかかわらず、オブジェクトへの参照を保持します。  

## 概要

`ObjectHolder`は渡された参照の種類によって参照を保持する、または内部にオブジェクトをコピー・ムーブするを決定する参照ハンドラです。  
参照・ポインタを渡された場合のオブジェクトの生存期間は参照先オブジェクトのものとなり、依然タングリング参照が発生する可能性があることに注意してください。  

`ObjectHolder`は[CopyConstructible](https://ja.cppreference.com/w/cpp/named_req/CopyConstructible)の要件を満たす場合の特殊化(#2)が存在します。  

## テンプレート引数

- `T` 参照するオブジェクトの型。[MoveConstructible](https://ja.cppreference.com/w/cpp/named_req/MoveConstructible)の要件を満たす非const型である必要があります。  

## メンバ型

- `ValueType`: `T`  
    保持するオブジェクト`T`の型。  
- `Pointer`: `T*`  
    `T`のポインター型。  
- `Reference`: `T&`  
    オブジェクト`T`への参照。  
- `ConstReference`: `const T&`  
    オブジェクト`T`への不変参照。  
- `ValueMove`: `T&&`  
    オブジェクト`T`の右辺値参照。  

## メンバ関数

### コンストラクタ

- `ObjectHolder()`
    -   ```C++
        constexpr ObjectHolder();
        ```
        規定の`ObjectHolder`を構築します。オブジェクトは参照を保持しません。

    -   ```C++
        constexpr ObjectHolder(std::nullptr_t);
        ```
        参照を保持しない`ObjectHolder`を構築します。

    -   ```C++
        constexpr ObjectHolder(Reference object);
        ```
        指定したオブジェクトを参照する`ObjectHolder`を構築します。  

        **引数**
        - `object` - このオブジェクトの参照先となるオブジェクト。  

    -   ```C++
        ObjectHolder(ConstReference object);
        ```
        (#2のみ)指定したオブジェクトを複製する`ObjectHolder`を構築します。
        `ObjectHolder`はオブジェクト用の領域を確保し、そこにオブジェクトをコピー構築します。

        **引数**
        - `other` - このオブジェクトが複製するオブジェクト。  

    -   ```C++
        ObjectHolder(ValueMove object);
        ```
        指定したオブジェクトを保持する`ObjectHolder`を構築します。
        `ObjectHolder`はオブジェクト用の領域を確保し、そこにオブジェクトをムーブ構築します。

        **引数**
        - `other` - このオブジェクトが保持するオブジェクト。  

    -   ```C++
        ObjectHolder(const ObjectHolder<T>& other);
        ```
        (#2のみ)コピーコンストラクタ。コピー元がオブジェクトを保持していればオブジェクトをコピーし、そうでなければ参照のみをコピーします。  

    -   ```C++
        ObjectHolder(ObjectHolder<T>&& other);
        ```
        ムーブコンストラクタ。指定されたオブジェクトからムーブ構築します。  

### デストラクタ

- `~ObjectHolder()`  
    デストラクタ。オブジェクトを保持していればそれを解放し、参照を破棄します。  

### 観測

- `has_value()`
    ```C++
    constexpr bool has_value() const noexcept;
    ```
    このオブジェクトが参照を持っているかを取得します。  
    note: この関数は参照先が有効であるかの確認は行いません。このオブジェクトの生存期間が参照先オブジェクトの生存期間よりも長い場合、タングリング参照となります。  

- `is_owner()`
    ```C++
    constexpr bool is_owner() const noexcept;
    ```
    このオブジェクトが参照先オブジェクトを所有しているかを取得します。  
    note: この関数の返却値が`true`の場合、参照先をこのオブジェクトが所有しているため、常に参照先オブジェクトの生存期間とこのオブジェクトの生存期間は等しくなります。  

### アクセス

- `value()`
    -   ```C++
        constexpr Reference value();
        ```
        このオブジェクトが参照している参照先にアクセスします。  

    -   ```C++
        constexpr Reference operator*();
        ```
        このオブジェクトが参照している参照先にアクセスします。  

    -   ```C++
        constexpr ConstReference value() const;
        ```
        このオブジェクトが参照している参照先にアクセスします。  

    -   ```C++
        constexpr ConstReference operator*() const;
        ```
        このオブジェクトが参照している参照先にアクセスします。  

    -   ```C++
        constexpr Pointer operator->();
        ```
        このオブジェクトが参照している参照先のメンバーにアクセスします。

    -   ```C++
        constexpr const Pointer operator->() const;
        ```
        このオブジェクトが参照している参照先のメンバーにアクセスします。

    -   ```C++
        constexpr T value_or(ConstReference or_value) const noexcept;
        ```
        (#2のみ)このオブジェクトが参照を持っていれば参照先オブジェクトをコピーし、そうでなければ指定されたオブジェクトを渡します。

        **引数**
        - `or_value` - オブジェクトが参照を持っていなかった場合に渡す代替の値。

### 変更

- `void clear() noexcept`  
    オブジェクトを保持していればそれを解放し、参照を破棄します。  

### 代入

- `operator=()`
    -   ```C++
        ObjectHolder<T>& operator=(std::nullptr_t);
        ```
        オブジェクトを保持していればそれを解放し、参照を破棄します。  

    -   ```C++
        ObjectHolder<T>& operator=(const ObjectHolder<T>& other);
        ```
        (#2のみ)コピー代入。コピー元がオブジェクトを保持していればオブジェクトをコピーし、そうでなければ参照のみをコピーします。代入される前に保持していた内容は(`clear()`が呼ばれたように)破棄されます。  

        **引数**
        - `other` - このオブジェクトが複製するオブジェクト。  

    -   ```C++
        ObjectHolder<T>& operator=(ObjectHolder<T>&& other);
        ```
        ムーブ代入。指定されたオブジェクトからムーブ代入を行います。代入される前に保持していた内容は(`clear()`が呼ばれたように)破棄されます。  

        **引数**
        - `other` - このオブジェクトが保持するオブジェクト。  

## サンプル

```C++
#include <stationaryorbit/core.utilities.hpp>
class A
{
    ObjectHolder<int> n;
public:
    A() : n() {}
    A(const ObjectHolder<int>& n) : n(n) {}
    A(ObjectHolder&& n) : n(std::move(n)) {}

    void f() const
    {
        if (n.has_value()) { std::cout << "has " << *n << std::endl; }
        else { std::cout << "has null" << std::endl; }
    }
};

int main()
{
    std::cout << "a1 ";
    int n1 = 28;
    auto a1 = A(n1);    // n1への参照を保持します。
    a1.f();             // OK, 参照しているn1の値を使用します。

    std::cout << "a2 ";
    auto a2 = A(14);    // ObjectHolderが内部に値を保持します。
    a2.f();             // OK, 内部に保持した値を使用します。

    std::cout << "a3 ";
    A a3;
    {
        int n3 = 46;
        a3 = n3;        // n3への参照を保持します。
    }
    // a3.f();          // 未定義動作。a3はn3を参照しますが、n3は破棄されています。

    a3.clear();         // 参照を破棄。
    a3.f();             // OK, a3は何も参照していません。

    std::cout << "a4 ";
    A a4;
    {
        int n4 = 100;
        a4 = std::as_const(n4); // constでのアクセスを要求される場合は、内部に値を保持します。
    }
    a4.f();             // OK, 内部に保持した値を使用します。

    std::cout << "A() ";
    A().f()             // OK, ObjectHolderの規定のコンストラクタは何も参照しません。

    return 0;
}
```

実行結果
```
a1 has 28
a2 has 14
a3 has null
a4 has 100
A() has null
```
