# Traits

[zawa_ch::StationaryOrbit](../../namespaces/zawa_ch/stationaryorbit.md) 名前空間  
[stationaryorbit/core.traits.hpp](../../headers/stationaryorbit/core.traits.hpp.md)で定義  

```C++
class Traits final;
```

このライブラリで用いられる型特性の識別を行います。  

## 概要

`Traits`は、このライブラリで定義されるオブジェクトの期待を実装するものです。  
このクラスのインスタンスを作成することはできません。また、継承することもできません。  

## メンバ型

- `SubstitutionResult<T, U>`  
    代入演算子`T::operator=(U)`の結果を表す型
- `SubstitutionAddResult<T, U>`  
    複合代入演算子`T::operator+=(U)`の結果を表す型
- `SubstitutionSubtractResult<T, U>`  
    複合代入演算子`T::operator-=(U)`の結果を表す型
- `SubstitutionMultipleResult<T, U>`  
    複合代入演算子`T::operator*=(U)`の結果を表す型
- `SubstitutionDivideResult<T, U>`  
    複合代入演算子`T::operator/=(U)`の結果を表す型
- `SubstitutionModulateResult<T, U>`  
    複合代入演算子`T::operator%=(U)`の結果を表す型
- `SubstitutionArithmeticAndResult<T, U>`  
    複合代入演算子`T::operator&=(U)`の結果を表す型
- `SubstitutionArithmeticOrResult<T, U>`  
    複合代入演算子`T::operator|=(U)`の結果を表す型
- `SubstitutionArithmeticXorResult<T, U>`  
    複合代入演算子`T::operator^=(U)`の結果を表す型
- `SubstitutionLShiftResult<T, U>`  
    複合代入演算子`T::operator<<=(U)`の結果を表す型
- `SubstitutionRShiftResult<T, U>`  
    複合代入演算子`T::operator>>=(U)`の結果を表す型
- `PreincrementResult<T>`  
    前置インクリメント演算子`T::operator++()`の結果を表す型
- `PredecrementResult<T>`  
    前置インクリメント演算子`T::operator--()`の結果を表す型
- `PostincrementResult<T>`  
    後置インクリメント演算子`T::operator++(int)`の結果を表す型
- `PostdecrementResult<T>`  
    後置インクリメント演算子`T::operator--(int)`の結果を表す型
- `PromotionResult<T>`  
    算術演算子`T::operator+()`の結果を表す型
- `InverseResult<T>`  
    算術演算子`T::operator-()`の結果を表す型
- `AdditionResult<T, U>`  
    算術演算子`T::operator+(U)`の結果を表す型
- `SubtractionResult<T, U>`  
    算術演算子`T::operator-(U)`の結果を表す型
- `MultiplicationResult<T, U>`  
    算術演算子`T::operator*(U)`の結果を表す型
- `DivisionResult<T, U>`  
    算術演算子`T::operator/(U)`の結果を表す型
- `ModulationResult<T, U>`  
    算術演算子`T::operator%(U)`の結果を表す型
- `ArithmeticNotResult<T>`  
    ビット演算子`T::operator~()`の結果を表す型
- `ArithmeticAndResult<T, U>`  
    ビット演算子`T::operator&(U)`の結果を表す型
- `ArithmeticOrResult<T, U>`  
    ビット演算子`T::operator|(U)`の結果を表す型
- `ArithmeticXorResult<T, U>`  
    ビット演算子`T::operator^(U)`の結果を表す型
- `LShiftResult<T, U>`  
    ビット演算子`T::operator<<(U)`の結果を表す型
- `RShiftResult<T, U>`  
    ビット演算子`T::operator>>(U)`の結果を表す型
- `LogicalNotResult<T>`  
    論理演算子`T::operator!()`の結果を表す型
- `LogicalOrResult<T, U>`  
    論理演算子`T::operator&&(U)`の結果を表す型
- `LogicalAndResult<T, U>`  
    論理演算子`T::operator||(U)`の結果を表す型
- `EqualResult<T, U>`  
    比較演算子`T::operator==(U)`の結果を表す型
- `NotEqualResult<T, U>`  
    比較演算子`T::operator!=(U)`の結果を表す型
- `LargerCompareResult<T, U>`  
    比較演算子`T::operator>(U)`の結果を表す型
- `SmallerCompareResult<T, U>`  
    比較演算子`T::operator<(U)`の結果を表す型
- `LeastCompareResult<T, U>`  
    比較演算子`T::operator>=(U)`の結果を表す型
- `MostCompareResult<T, U>`  
    比較演算子`T::operator<=(U)`の結果を表す型
- `SubscriptResult<T, U>`  
    添字演算子`T::operator[](U)`の結果を表す型
- `DereferenceResult<T>`  
    間接参照演算子`T::operator*()`の結果を表す型
- `ReferenceResult<T>`  
    アドレス取得演算子`T::operator&()`の結果を表す型
- `CommaResult<T, U>`  
    カンマ演算子`T::operator,(U)`の結果を表す型

## 静的メンバ定数

### 演算子実装の識別

- `bool HasSubstitution<T, U>`  
    代入演算子`T::operator=(U)`を実装しているかを識別します
- `bool HasSubstitutionAdd<T, U>`  
    複合代入演算子`T::operator+=(U)`を実装しているかを識別します
- `bool HasSubstitutionSubtract<T, U>`  
    複合代入演算子`T::operator-=(U)`を実装しているかを識別します
- `bool HasSubstitutionMultiple<T, U>`  
    複合代入演算子`T::operator*=(U)`を実装しているかを識別します
- `bool HasSubstitutionDivide<T, U>`  
    複合代入演算子`T::operator/=(U)`を実装しているかを識別します
- `bool HasSubstitutionModulate<T, U>`  
    複合代入演算子`T::operator%=(U)`を実装しているかを識別します
- `bool HasSubstitutionArithmeticAnd<T, U>`  
    複合代入演算子`T::operator&=(U)`を実装しているかを識別します
- `bool HasSubstitutionArithmeticOr<T, U>`  
    複合代入演算子`T::operator|=(U)`を実装しているかを識別します
- `bool HasSubstitutionArithmeticXor<T, U>`  
    複合代入演算子`T::operator^=(U)`を実装しているかを識別します
- `bool HasSubstitutionLShift<T, U>`  
    複合代入演算子`T::operator<<=(U)`を実装しているかを識別します
- `bool HasSubstitutionRShift<T, U>`  
    複合代入演算子`T::operator>>=(U)`を実装しているかを識別します
- `bool HasPreincrement<T>`  
    前置インクリメント演算子`T::operator++()`を実装しているかを識別します
- `bool HasPredecrement<T>`  
    前置インクリメント演算子`T::operator--()`を実装しているかを識別します
- `bool HasPostincrement<T>`  
    後置インクリメント演算子`T::operator++(int)`を実装しているかを識別します
- `bool HasPostdecrement<T>`  
    後置インクリメント演算子`T::operator--(int)`を実装しているかを識別します
- `bool HasPromotion<T>`  
    算術演算子`T::operator+()`を実装しているかを識別します
- `bool HasInverse<T>`  
    算術演算子`T::operator-()`を実装しているかを識別します
- `bool HasAddition<T, U>`  
    算術演算子`T::operator+(U)`を実装しているかを識別します
- `bool HasSubtraction<T, U>`  
    算術演算子`T::operator-(U)`を実装しているかを識別します
- `bool HasMultiplication<T, U>`  
    算術演算子`T::operator*(U)`を実装しているかを識別します
- `bool HasDivision<T, U>`  
    算術演算子`T::operator/(U)`を実装しているかを識別します
- `bool HasModulation<T, U>`  
    算術演算子`T::operator%(U)`を実装しているかを識別します
- `bool HasArithmeticNot<T, U>`  
    ビット演算子`T::operator~()`を実装しているかを識別します
- `bool HasArithmeticAnd<T, U>`  
    ビット演算子`T::operator&(U)`を実装しているかを識別します
- `bool HasArithmeticOr<T, U>`  
    ビット演算子`T::operator|(U)`を実装しているかを識別します
- `bool HasArithmeticXor<T, U>`  
    ビット演算子`T::operator^(U)`を実装しているかを識別します
- `bool HasLShift<T, U>`  
    ビット演算子`T::operator<<(U)`を実装しているかを識別します
- `bool HasRShift<T, U>`  
    ビット演算子`T::operator>>(U)`を実装しているかを識別します
- `bool HasLogicalNot<T>`  
    論理演算子`T::operator!()`を実装しているかを識別します
- `bool HasLogicalOr<T, U>`  
    論理演算子`T::operator&&(U)`を実装しているかを識別します
- `bool HasLogicalAnd<T, U>`  
    論理演算子`T::operator||(U)`を実装しているかを識別します
- `bool HasEqual<T, U>`  
    比較演算子`T::operator==(U)`を実装しているかを識別します
- `bool HasNotEqual<T, U>`  
    比較演算子`T::operator!=(U)`を実装しているかを識別します
- `bool HasLargerCompare<T, U>`  
    比較演算子`T::operator>(U)`を実装しているかを識別します
- `bool HasSmallerCompare<T, U>`  
    比較演算子`T::operator<(U)`を実装しているかを識別します
- `bool HasLeastCompare<T, U>`  
    比較演算子`T::operator>=(U)`を実装しているかを識別します
- `bool HasMostCompare<T, U>`  
    比較演算子`T::operator<=(U)`を実装しているかを識別します
- `bool HasSubscript<T, U>`  
    添字演算子`T::operator[](U)`を実装しているかを識別します
- `bool HasDereference<T>`  
    間接参照演算子`T::operator*()`を実装しているかを識別します
- `bool HasReference<T>`  
    アドレス取得演算子`T::operator&()`を実装しているかを識別します
- `bool HasComma<T, U>`  
    カンマ演算子`T::operator,(U)`を実装しているかを識別します

### 型一致の識別

- `bool SubstitutionResultIsSame<T, U, R>`  
    代入演算子`T::operator=(U)`の返却値型が`R`に一致するかを識別します
- `bool SubstitutionAddResultIsSame<T, U, R>`  
    複合代入演算子`T::operator+=(U)`の返却値型が`R`に一致するかを識別します
- `bool SubstitutionSubtractResultIsSame<T, U, R>`  
    複合代入演算子`T::operator-=(U)`の返却値型が`R`に一致するかを識別します
- `bool SubstitutionMultipleResultIsSame<T, U, R>`  
    複合代入演算子`T::operator*=(U)`の返却値型が`R`に一致するかを識別します
- `bool SubstitutionDivideResultIsSame<T, U, R>`  
    複合代入演算子`T::operator/=(U)`の返却値型が`R`に一致するかを識別します
- `bool SubstitutionModulateResultIsSame<T, U, R>`  
    複合代入演算子`T::operator%=(U)`の返却値型が`R`に一致するかを識別します
- `bool SubstitutionArithmeticAndResultIsSame<T, U, R>`  
    複合代入演算子`T::operator&=(U)`の返却値型が`R`に一致するかを識別します
- `bool SubstitutionArithmeticOrResultIsSame<T, U, R>`  
    複合代入演算子`T::operator|=(U)`の返却値型が`R`に一致するかを識別します
- `bool SubstitutionArithmeticXorResultIsSame<T, U, R>`  
    複合代入演算子`T::operator^=(U)`の返却値型が`R`に一致するかを識別します
- `bool SubstitutionLShiftResultIsSame<T, U, R>`  
    複合代入演算子`T::operator<<=(U)`の返却値型が`R`に一致するかを識別します
- `bool SubstitutionRShiftResultIsSame<T, U, R>`  
    複合代入演算子`T::operator>>=(U)`の返却値型が`R`に一致するかを識別します
- `bool PreincrementResultIsSame<T, R>`  
    前置インクリメント演算子`T::operator++()`の返却値型が`R`に一致するかを識別します
- `bool PredecrementResultIsSame<T, R>`  
    前置インクリメント演算子`T::operator--()`の返却値型が`R`に一致するかを識別します
- `bool PostincrementResultIsSame<T, R>`  
    後置インクリメント演算子`T::operator++(int)`の返却値型が`R`に一致するかを識別します
- `bool PostdecrementResultIsSame<T, R>`  
    後置インクリメント演算子`T::operator--(int)`の返却値型が`R`に一致するかを識別します
- `bool PromotionResultIsSame<T, R>`  
    算術演算子`T::operator+()`の返却値型が`R`に一致するかを識別します
- `bool InverseResultIsSame<T, R>`  
    算術演算子`T::operator-()`の返却値型が`R`に一致するかを識別します
- `bool AdditionResultIsSame<T, U, R>`  
    算術演算子`T::operator+(U)`の返却値型が`R`に一致するかを識別します
- `bool SubtractionResultIsSame<T, U, R>`  
    算術演算子`T::operator-(U)`の返却値型が`R`に一致するかを識別します
- `bool MultiplicationResultIsSame<T, U, R>`  
    算術演算子`T::operator*(U)`の返却値型が`R`に一致するかを識別します
- `bool DivisionResultIsSame<T, U, R>`  
    算術演算子`T::operator/(U)`の返却値型が`R`に一致するかを識別します
- `bool ModulationResultIsSame<T, U, R>`  
    算術演算子`T::operator%(U)`の返却値型が`R`に一致するかを識別します
- `bool ArithmeticNotResultIsSame<T, U, R>`  
    ビット演算子`T::operator~()`の返却値型が`R`に一致するかを識別します
- `bool ArithmeticAndResultIsSame<T, U, R>`  
    ビット演算子`T::operator&(U)`の返却値型が`R`に一致するかを識別します
- `bool ArithmeticOrResultIsSame<T, U, R>`  
    ビット演算子`T::operator|(U)`の返却値型が`R`に一致するかを識別します
- `bool ArithmeticXorResultIsSame<T, U, R>`  
    ビット演算子`T::operator^(U)`の返却値型が`R`に一致するかを識別します
- `bool LShiftResultIsSame<T, U, R>`  
    ビット演算子`T::operator<<(U)`の返却値型が`R`に一致するかを識別します
- `bool RShiftResultIsSame<T, U, R>`  
    ビット演算子`T::operator>>(U)`の返却値型が`R`に一致するかを識別します
- `bool LogicalNotResultIsSame<T, R>`  
    論理演算子`T::operator!()`の返却値型が`R`に一致するかを識別します
- `bool LogicalOrResultIsSame<T, U, R>`  
    論理演算子`T::operator&&(U)`の返却値型が`R`に一致するかを識別します
- `bool LogicalAndResultIsSame<T, U, R>`  
    論理演算子`T::operator||(U)`の返却値型が`R`に一致するかを識別します
- `bool EqualResultIsSame<T, U, R>`  
    比較演算子`T::operator==(U)`の返却値型が`R`に一致するかを識別します
- `bool NotEqualResultIsSame<T, U, R>`  
    比較演算子`T::operator!=(U)`の返却値型が`R`に一致するかを識別します
- `bool LargerCompareResultIsSame<T, U, R>`  
    比較演算子`T::operator>(U)`の返却値型が`R`に一致するかを識別します
- `bool SmallerCompareResultIsSame<T, U, R>`  
    比較演算子`T::operator<(U)`の返却値型が`R`に一致するかを識別します
- `bool LeastCompareResultIsSame<T, U, R>`  
    比較演算子`T::operator>=(U)`の返却値型が`R`に一致するかを識別します
- `bool MostCompareResultIsSame<T, U, R>`  
    比較演算子`T::operator<=(U)`の返却値型が`R`に一致するかを識別します
- `bool SubscriptResultIsSame<T, U, R>`  
    添字演算子`T::operator[](U)`の返却値型が`R`に一致するかを識別します
- `bool DereferenceResultIsSame<T, R>`  
    間接参照演算子`T::operator*()`の返却値型が`R`に一致するかを識別します
- `bool ReferenceResultIsSame<T, R>`  
    アドレス取得演算子`T::operator&()`の返却値型が`R`に一致するかを識別します
- `bool CommaResultIsSame<T, U, R>`  
    カンマ演算子`T::operator,(U)`の返却値型が`R`に一致するかを識別します

### 型変換可能性の識別

- `bool SubstitutionResultIsConvertible<T, U, R>`  
    代入演算子`T::operator=(U)`の返却値型が`R`に変換可能かを識別します
- `bool SubstitutionAddResultIsConvertible<T, U, R>`  
    複合代入演算子`T::operator+=(U)`の返却値型が`R`に変換可能かを識別します
- `bool SubstitutionSubtractResultIsConvertible<T, U, R>`  
    複合代入演算子`T::operator-=(U)`の返却値型が`R`に変換可能かを識別します
- `bool SubstitutionMultipleResultIsConvertible<T, U, R>`  
    複合代入演算子`T::operator*=(U)`の返却値型が`R`に変換可能かを識別します
- `bool SubstitutionDivideResultIsConvertible<T, U, R>`  
    複合代入演算子`T::operator/=(U)`の返却値型が`R`に変換可能かを識別します
- `bool SubstitutionModulateResultIsConvertible<T, U, R>`  
    複合代入演算子`T::operator%=(U)`の返却値型が`R`に変換可能かを識別します
- `bool SubstitutionArithmeticAndResultIsConvertible<T, U, R>`  
    複合代入演算子`T::operator&=(U)`の返却値型が`R`に変換可能かを識別します
- `bool SubstitutionArithmeticOrResultIsConvertible<T, U, R>`  
    複合代入演算子`T::operator|=(U)`の返却値型が`R`に変換可能かを識別します
- `bool SubstitutionArithmeticXorResultIsConvertible<T, U, R>`  
    複合代入演算子`T::operator^=(U)`の返却値型が`R`に変換可能かを識別します
- `bool SubstitutionLShiftResultIsConvertible<T, U, R>`  
    複合代入演算子`T::operator<<=(U)`の返却値型が`R`に変換可能かを識別します
- `bool SubstitutionRShiftResultIsConvertible<T, U, R>`  
    複合代入演算子`T::operator>>=(U)`の返却値型が`R`に変換可能かを識別します
- `bool PreincrementResultIsConvertible<T, R>`  
    前置インクリメント演算子`T::operator++()`の返却値型が`R`に変換可能かを識別します
- `bool PredecrementResultIsConvertible<T, R>`  
    前置インクリメント演算子`T::operator--()`の返却値型が`R`に変換可能かを識別します
- `bool PostincrementResultIsConvertible<T, R>`  
    後置インクリメント演算子`T::operator++(int)`の返却値型が`R`に変換可能かを識別します
- `bool PostdecrementResultIsConvertible<T, R>`  
    後置インクリメント演算子`T::operator--(int)`の返却値型が`R`に変換可能かを識別します
- `bool PromotionResultIsConvertible<T, R>`  
    算術演算子`T::operator+()`の返却値型が`R`に変換可能かを識別します
- `bool InverseResultIsConvertible<T, R>`  
    算術演算子`T::operator-()`の返却値型が`R`に変換可能かを識別します
- `bool AdditionResultIsConvertible<T, U, R>`  
    算術演算子`T::operator+(U)`の返却値型が`R`に変換可能かを識別します
- `bool SubtractionResultIsConvertible<T, U, R>`  
    算術演算子`T::operator-(U)`の返却値型が`R`に変換可能かを識別します
- `bool MultiplicationResultIsConvertible<T, U, R>`  
    算術演算子`T::operator*(U)`の返却値型が`R`に変換可能かを識別します
- `bool DivisionResultIsConvertible<T, U, R>`  
    算術演算子`T::operator/(U)`の返却値型が`R`に変換可能かを識別します
- `bool ModulationResultIsConvertible<T, U, R>`  
    算術演算子`T::operator%(U)`の返却値型が`R`に変換可能かを識別します
- `bool ArithmeticNotResultIsConvertible<T, U, R>`  
    ビット演算子`T::operator~()`の返却値型が`R`に変換可能かを識別します
- `bool ArithmeticAndResultIsConvertible<T, U, R>`  
    ビット演算子`T::operator&(U)`の返却値型が`R`に変換可能かを識別します
- `bool ArithmeticOrResultIsConvertible<T, U, R>`  
    ビット演算子`T::operator|(U)`の返却値型が`R`に変換可能かを識別します
- `bool ArithmeticXorResultIsConvertible<T, U, R>`  
    ビット演算子`T::operator^(U)`の返却値型が`R`に変換可能かを識別します
- `bool LShiftResultIsConvertible<T, U, R>`  
    ビット演算子`T::operator<<(U)`の返却値型が`R`に変換可能かを識別します
- `bool RShiftResultIsConvertible<T, U, R>`  
    ビット演算子`T::operator>>(U)`の返却値型が`R`に変換可能かを識別します
- `bool LogicalNotResultIsConvertible<T, R>`  
    論理演算子`T::operator!()`の返却値型が`R`に変換可能かを識別します
- `bool LogicalOrResultIsConvertible<T, U, R>`  
    論理演算子`T::operator&&(U)`の返却値型が`R`に変換可能かを識別します
- `bool LogicalAndResultIsConvertible<T, U, R>`  
    論理演算子`T::operator||(U)`の返却値型が`R`に変換可能かを識別します
- `bool EqualResultIsConvertible<T, U, R>`  
    比較演算子`T::operator==(U)`の返却値型が`R`に変換可能かを識別します
- `bool NotEqualResultIsConvertible<T, U, R>`  
    比較演算子`T::operator!=(U)`の返却値型が`R`に変換可能かを識別します
- `bool LargerCompareResultIsConvertible<T, U, R>`  
    比較演算子`T::operator>(U)`の返却値型が`R`に変換可能かを識別します
- `bool SmallerCompareResultIsConvertible<T, U, R>`  
    比較演算子`T::operator<(U)`の返却値型が`R`に変換可能かを識別します
- `bool LeastCompareResultIsConvertible<T, U, R>`  
    比較演算子`T::operator>=(U)`の返却値型が`R`に変換可能かを識別します
- `bool MostCompareResultIsConvertible<T, U, R>`  
    比較演算子`T::operator<=(U)`の返却値型が`R`に変換可能かを識別します
- `bool SubscriptResultIsConvertible<T, U, R>`  
    添字演算子`T::operator[](U)`の返却値型が`R`に変換可能かを識別します
- `bool DereferenceResultIsConvertible<T, R>`  
    間接参照演算子`T::operator*()`の返却値型が`R`に変換可能かを識別します
- `bool ReferenceResultIsConvertible<T, R>`  
    アドレス取得演算子`T::operator&()`の返却値型が`R`に変換可能かを識別します
- `bool CommaResultIsConvertible<T, U, R>`  
    カンマ演算子`T::operator,(U)`の返却値型が`R`に変換可能かを識別します

### CVRef除去型一致の識別

- `bool SubstitutionResultRemoveCVRefIsSame<T, U, R>`  
    代入演算子`T::operator=(U)`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool SubstitutionAddResultRemoveCVRefIsSame<T, U, R>`  
    複合代入演算子`T::operator+=(U)`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool SubstitutionSubtractResultRemoveCVRefIsSame<T, U, R>`  
    複合代入演算子`T::operator-=(U)`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool SubstitutionMultipleResultRemoveCVRefIsSame<T, U, R>`  
    複合代入演算子`T::operator*=(U)`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool SubstitutionDivideResultRemoveCVRefIsSame<T, U, R>`  
    複合代入演算子`T::operator/=(U)`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool SubstitutionModulateResultRemoveCVRefIsSame<T, U, R>`  
    複合代入演算子`T::operator%=(U)`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool SubstitutionArithmeticAndResultRemoveCVRefIsSame<T, U, R>`  
    複合代入演算子`T::operator&=(U)`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool SubstitutionArithmeticOrResultRemoveCVRefIsSame<T, U, R>`  
    複合代入演算子`T::operator|=(U)`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool SubstitutionArithmeticXorResultRemoveCVRefIsSame<T, U, R>`  
    複合代入演算子`T::operator^=(U)`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool SubstitutionLShiftResultRemoveCVRefIsSame<T, U, R>`  
    複合代入演算子`T::operator<<=(U)`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool SubstitutionRShiftResultRemoveCVRefIsSame<T, U, R>`  
    複合代入演算子`T::operator>>=(U)`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool PreincrementResultRemoveCVRefIsSame<T, R>`  
    前置インクリメント演算子`T::operator++()`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool PredecrementResultRemoveCVRefIsSame<T, R>`  
    前置インクリメント演算子`T::operator--()`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool PostincrementResultRemoveCVRefIsSame<T, R>`  
    後置インクリメント演算子`T::operator++(int)`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool PostdecrementResultRemoveCVRefIsSame<T, R>`  
    後置インクリメント演算子`T::operator--(int)`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool PromotionResultRemoveCVRefIsSame<T, R>`  
    算術演算子`T::operator+()`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool InverseResultRemoveCVRefIsSame<T, R>`  
    算術演算子`T::operator-()`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool AdditionResultRemoveCVRefIsSame<T, U, R>`  
    算術演算子`T::operator+(U)`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool SubtractionResultRemoveCVRefIsSame<T, U, R>`  
    算術演算子`T::operator-(U)`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool MultiplicationResultRemoveCVRefIsSame<T, U, R>`  
    算術演算子`T::operator*(U)`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool DivisionResultRemoveCVRefIsSame<T, U, R>`  
    算術演算子`T::operator/(U)`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool ModulationResultRemoveCVRefIsSame<T, U, R>`  
    算術演算子`T::operator%(U)`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool ArithmeticNotResultRemoveCVRefIsSame<T, U, R>`  
    ビット演算子`T::operator~()`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool ArithmeticAndResultRemoveCVRefIsSame<T, U, R>`  
    ビット演算子`T::operator&(U)`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool ArithmeticOrResultRemoveCVRefIsSame<T, U, R>`  
    ビット演算子`T::operator|(U)`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool ArithmeticXorResultRemoveCVRefIsSame<T, U, R>`  
    ビット演算子`T::operator^(U)`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool LShiftResultRemoveCVRefIsSame<T, U, R>`  
    ビット演算子`T::operator<<(U)`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool RShiftResultRemoveCVRefIsSame<T, U, R>`  
    ビット演算子`T::operator>>(U)`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool LogicalNotResultRemoveCVRefIsSame<T, R>`  
    論理演算子`T::operator!()`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool LogicalOrResultRemoveCVRefIsSame<T, U, R>`  
    論理演算子`T::operator&&(U)`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool LogicalAndResultRemoveCVRefIsSame<T, U, R>`  
    論理演算子`T::operator||(U)`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool EqualResultRemoveCVRefIsSame<T, U, R>`  
    比較演算子`T::operator==(U)`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool NotEqualResultRemoveCVRefIsSame<T, U, R>`  
    比較演算子`T::operator!=(U)`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool LargerCompareResultRemoveCVRefIsSame<T, U, R>`  
    比較演算子`T::operator>(U)`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool SmallerCompareResultRemoveCVRefIsSame<T, U, R>`  
    比較演算子`T::operator<(U)`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool LeastCompareResultRemoveCVRefIsSame<T, U, R>`  
    比較演算子`T::operator>=(U)`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool MostCompareResultRemoveCVRefIsSame<T, U, R>`  
    比較演算子`T::operator<=(U)`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool SubscriptResultRemoveCVRefIsSame<T, U, R>`  
    添字演算子`T::operator[](U)`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool DereferenceResultRemoveCVRefIsSame<T, R>`  
    間接参照演算子`T::operator*()`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool ReferenceResultRemoveCVRefIsSame<T, R>`  
    アドレス取得演算子`T::operator&()`の返却値(CVRef除去)型が`R`に一致するかを識別します
- `bool CommaResultRemoveCVRefIsSame<T, U, R>`  
    カンマ演算子`T::operator,(U)`の返却値(CVRef除去)型が`R`に一致するかを識別します

### その他の実装の識別

- `bool HasArrow<T, R>`  
    アロー演算子`->`のオーバーロード実装を識別します
- `bool HasArrowDereference<T, R>`  
    アロー間接参照演算子`->*`のオーバーロード実装を識別します
- `bool IsAggregatable<T, Targs>`  
    指定された型の波括弧による初期化が可能な型を識別します

### 要件の識別

- `bool IsEquatable<T, U = T>`  
    [型要件](../../requirements/index.md):[Equatable](../../requirements/equatable.md)を満たす型を識別します
- `bool IsComparable<T, U = T>`  
    [型要件](../../requirements/index.md):[Comparable](../../requirements/comparable.md)を満たす型を識別します
- `bool IsValueType<T>`  
    [型要件](../../requirements/index.md):[ValueType](../../requirements/valuetype.md)を満たす型を識別します
- `bool IsPointableType<T>`  
    [型要件](../../requirements/index.md):[PointableType](../../requirements/pointabletype.md)を満たす型を識別します
- `bool HasArithmeticOperation<T>`  
    基本的な算術演算子の実装を識別します
- `bool IsArithmeticType<T>`  
    [型要件](../../requirements/index.md):[ArithmeticType](../../requirements/arithmetictype.md)を満たす型を識別します
- `bool IsNumericalType<T>`  
    [型要件](../../requirements/index.md):[NumericalType](../../requirements/numericaltype.md)を満たす型を識別します
- `bool IsIntegralType<T>`  
    [型要件](../../requirements/index.md):[IntegralType](../../requirements/integraltype.md)を満たす型を識別します
- `bool IsSequencialOrderType<T>`  
    [型要件](../../requirements/index.md):[SequencialOrderType](../../requirements/sequencialordertype.md)を満たす型を識別します
- `bool IsBidirectionalOrderType<T>`  
    [型要件](../../requirements/index.md):[BidirectionalOrderType](../../requirements/bidirectionalordertype.md)を満たす型を識別します
- `bool IsLinearOrderType<T, N>`  
    [型要件](../../requirements/index.md):[LinearOrderType](../../requirements/linearordertype.md)を満たす型を識別します
- `bool HasBitSequenceOperation<T, N>`  
    基本的なビット演算子の実装を識別します
- `bool IsBitSequenceType<T, N>`  
    [型要件](../../requirements/index.md):[BitSequenceType](../../requirements/bitsequencetype.md)を満たす型を識別します
- `bool IsStdLegacyIterator<It>`  
    C++標準名前付き要件:[LegacyIterator](https://ja.cppreference.com/w/cpp/named_req/Iterator)を満たす型を識別します
- `bool IsStdLegacyInputIterator<It>`  
    C++標準名前付き要件:[LegacyInputIterator](https://ja.cppreference.com/w/cpp/named_req/InputIterator)を満たす型を識別します
- `bool IsStdLegacyForwardIterator<It>`  
    C++標準名前付き要件:[LegacyForwardIterator](https://ja.cppreference.com/w/cpp/named_req/ForwardIterator)を満たす型を識別します
- `bool IsStdLegacyBidirectionalIterator<It>`  
    C++標準名前付き要件:[LegacyBidirectionalIterator](https://ja.cppreference.com/w/cpp/named_req/BidirectionalIterator)を満たす型を識別します
- `bool IsStdLegacyRandomAccessIterator<It>`  
    C++標準名前付き要件:[LegacyRandomAccessIterator](https://ja.cppreference.com/w/cpp/named_req/RandomAccessIterator)を満たす型を識別します
- `bool IsStdLegacyOutputIterator<It>`  
    C++標準名前付き要件:[LegacyOutputIterator](https://ja.cppreference.com/w/cpp/named_req/OutputIterator)を満たす型を識別します

## 関連項目

- [型要件](../../requirements/index.md)
