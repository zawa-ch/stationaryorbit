# ValueType

[ドキュメントルート](../index.md) » [型要件](index.md) » `ValueType`

単一の値として表現される型

## 概要

`ValueType`は固定長のデータを単一の値として表現する型を表します。  

## 要件

以下の要件を満たす場合、`T`は`ValueType`を満たします。  

- [デフォルト構築](https://ja.cppreference.com/w/cpp/types/is_default_constructible)可能であり、その操作がトリビアルかつ`nothrow`である
- [削除されていないデストラクタ](https://ja.cppreference.com/w/cpp/types/is_destructible)を持ち、その操作がトリビアルかつ`nothrow`である
- [コピー構築](https://ja.cppreference.com/w/cpp/types/is_copy_constructible)および[コピー代入](https://ja.cppreference.com/w/cpp/types/is_copy_assignable)が可能であり、その操作がトリビアルかつ`nothrow`である
- [ムーブ構築](https://ja.cppreference.com/w/cpp/types/is_move_constructible)および[ムーブ代入](https://ja.cppreference.com/w/cpp/types/is_move_assignable)が可能であり、その操作がトリビアルかつ`nothrow`である
- [Equatable](equatable.md)である

## 参照

- [zawa_ch::StationaryOrbit::Traits](../objects/core/traits)
