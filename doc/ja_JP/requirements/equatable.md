# Equatable

[ドキュメントルート](../index.md) » [型要件](index.md) » `Equatable`

オブジェクトの等価比較が可能な型

## 概要

`Equatable`は、自身と他の型(自身と同じ型を含む)との等価比較がサポートされる型を表します。  

## 要件

以下の要件を満たす場合、`T`は`U`に対し`Equatable`を満たします。  

- `T`型の値`a`, `c`, `U`型の値`b`, `d`が与えられた場合、以下の効果を持つ操作が実装されている
    |式|返却値型|効果|
    |--|--------|----|
    |`a == b`|`bool`に暗黙に変換可能|同等関係を満たす(`a == b`, `c == d`, `a == d`がすべて成り立つ場合、`c == b`も成り立つ)|
    |`a != b`|`bool`に暗黙に変換可能|`!(a == b)`と同等である|

## ノート

`T`が`U`に対して`Equatable`を満たす場合、同様に`U`が`T`に対して`Equatable`を満たすべきです。
このときも、同等関係を満たす(`T`型の値`a`, `U`型の値`b`が与えられ、`a == b`が成り立つ場合に`b == a`が成り立つ)必要があります。

`U = T`の場合、この要件が要求する関係はC++名前付き要件:[EqualityComparable](https://ja.cppreference.com/w/cpp/named_req/EqualityComparable)と同等です。  

## 参照

- C++名前付き要件:[EqualityComparable](https://ja.cppreference.com/w/cpp/named_req/EqualityComparable)
- [zawa_ch::StationaryOrbit::Traits](../objects/core/traits)
