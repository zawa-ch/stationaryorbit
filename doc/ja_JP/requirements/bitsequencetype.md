# BitSequenceType

[ドキュメントルート](../index.md) » [型要件](index.md) » `BitSequenceType`

ビット列としてのアクセスが可能な型

## 概要

`BitSequenceType`は、1個以上のビットの順序付きの集合であり、それらビット列への基本的な操作をサポートする値型を表します。  

## 要件

以下の要件を満たす場合、`T`は`BitSequenceType`を満たします。  

- [Equatable](equatable.md)である
- [ValueType](valuetype.md)である
- `uint8_t`から変換可能、または`uint8_t`による集成体初期化が可能である
- `T`型の値`a`, `b`, `IntegralType`を満たす型`N`の値`n`が与えられた場合、以下の効果を持つ操作が実装されている
    |式|返却値型|効果|
    |--|--------|----|
    |`~a`|`T`に暗黙に変換可能|ビット列内全てのビットが反転される|
    |`a & b`|`T`に暗黙に変換可能|ビット列内の各ビットに対して論理積結合が行われる|
    |`a \| b`|`T`に暗黙に変換可能|ビット列内の各ビットに対して論理和結合が行われる|
    |`a ^ b`|`T`に暗黙に変換可能|ビット列内の各ビットに対して排他的論理和結合が行われる|
    |`a << n`|`T`に暗黙に変換可能|ビット列がMSB方向に`n`ビットシフトする|
    |`a << n`|`T`に暗黙に変換可能|ビット列がLSB方向に`n`ビットシフトする|
    |`a &= b`|`T&`|`a & b`の結果が`a`に代入される|
    |`a \|= b`|`T&`|`a \| b`の結果が`a`に代入される|
    |`a ^= b`|`T&`|`a ^ b`の結果が`a`に代入される|
    |`a <<= n`|`T&`|`a << n`の結果が`a`に代入される|
    |`a <<= n`|`T&`|`a >> n`の結果が`a`に代入される|
- 符号付き型*ではない*([std::is_signed](https://ja.cppreference.com/w/cpp/types/is_signed)が[std::false_type](http://ja.cppreference.com/w/cpp/types/integral_constant)に等しい型を提供する,
[std::numeric_limits](https://ja.cppreference.com/w/cpp/types/numeric_limits)の特殊化を提供する場合は`std::numeric_limits<T>::is_signed`が`false`となる)

## 参照

- [zawa_ch::StationaryOrbit::Traits](../objects/core/traits)
