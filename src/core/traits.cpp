//	stationaryorbit.core:/traits
//	Copyright 2020 zawa-ch.
//	GPLv3 (or later) license
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//	See the GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program.
//	If not, see <http://www.gnu.org/licenses/>.
//
#include <cstddef>
#include <cstdint>
#include <string>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include "stationaryorbit/core/traits.hpp"
using namespace zawa_ch::StationaryOrbit;

//	コンパイル時型特性アサーション
static_assert(Traits::IsEquatable<bool>, "bool が IsEquatable 型特性を満たしませんでした。");
static_assert(Traits::IsEquatable<uint8_t>, "uint8_t が IsEquatable 型特性を満たしませんでした。");
static_assert(Traits::IsEquatable<uint16_t>, "uint16_t が IsEquatable 型特性を満たしませんでした。");
static_assert(Traits::IsEquatable<uint32_t>, "uint32_t が IsEquatable 型特性を満たしませんでした。");
static_assert(Traits::IsEquatable<uint64_t>, "uint64_t が IsEquatable 型特性を満たしませんでした。");
static_assert(Traits::IsEquatable<uintmax_t>, "uintmax_t が IsEquatable 型特性を満たしませんでした。");
static_assert(Traits::IsEquatable<uintptr_t>, "uintptr_t が IsEquatable 型特性を満たしませんでした。");
static_assert(Traits::IsEquatable<int8_t>, "int8_t が IsEquatable 型特性を満たしませんでした。");
static_assert(Traits::IsEquatable<int16_t>, "int16_t が IsEquatable 型特性を満たしませんでした。");
static_assert(Traits::IsEquatable<int32_t>, "int32_t が IsEquatable 型特性を満たしませんでした。");
static_assert(Traits::IsEquatable<int64_t>, "int64_t が IsEquatable 型特性を満たしませんでした。");
static_assert(Traits::IsEquatable<intmax_t>, "intmax_t が IsEquatable 型特性を満たしませんでした。");
static_assert(Traits::IsEquatable<intptr_t>, "intptr_t が IsEquatable 型特性を満たしませんでした。");
static_assert(Traits::IsEquatable<float>, "float が IsEquatable 型特性を満たしませんでした。");
static_assert(Traits::IsEquatable<double>, "double が IsEquatable 型特性を満たしませんでした。");
static_assert(Traits::IsEquatable<size_t>, "size_t が IsEquatable 型特性を満たしませんでした。");
static_assert(Traits::IsEquatable<std::nullptr_t>, "std::nullptr_t が IsEquatable 型特性を満たしませんでした。");
static_assert(Traits::IsEquatable<std::byte>, "std::byte が IsEquatable 型特性を満たしませんでした。");
static_assert(Traits::IsEquatable<std::string>, "std::string が IsEquatable 型特性を満たしませんでした。");

static_assert(Traits::IsComparable<uint8_t>, "uint8_t が IsComparable 型特性を満たしませんでした。");
static_assert(Traits::IsComparable<uint16_t>, "uint16_t が IsComparable 型特性を満たしませんでした。");
static_assert(Traits::IsComparable<uint32_t>, "uint32_t が IsComparable 型特性を満たしませんでした。");
static_assert(Traits::IsComparable<uint64_t>, "uint64_t が IsComparable 型特性を満たしませんでした。");
static_assert(Traits::IsComparable<uintmax_t>, "uintmax_t が IsComparable 型特性を満たしませんでした。");
static_assert(Traits::IsComparable<uintptr_t>, "uintptr_t が IsComparable 型特性を満たしませんでした。");
static_assert(Traits::IsComparable<int8_t>, "int8_t が IsComparable 型特性を満たしませんでした。");
static_assert(Traits::IsComparable<int16_t>, "int16_t が IsComparable 型特性を満たしませんでした。");
static_assert(Traits::IsComparable<int32_t>, "int32_t が IsComparable 型特性を満たしませんでした。");
static_assert(Traits::IsComparable<int64_t>, "int64_t が IsComparable 型特性を満たしませんでした。");
static_assert(Traits::IsComparable<intmax_t>, "intmax_t が IsComparable 型特性を満たしませんでした。");
static_assert(Traits::IsComparable<intptr_t>, "intptr_t が IsComparable 型特性を満たしませんでした。");
static_assert(Traits::IsComparable<float>, "float が IsComparable 型特性を満たしませんでした。");
static_assert(Traits::IsComparable<double>, "double が IsComparable 型特性を満たしませんでした。");
static_assert(Traits::IsComparable<size_t>, "size_t が IsComparable 型特性を満たしませんでした。");
static_assert(Traits::IsComparable<std::string>, "std::string が IsComparable 型特性を満たしませんでした。");

static_assert(Traits::IsValueType<bool>, "bool が IsValueType 型特性を満たしませんでした。");
static_assert(Traits::IsValueType<uint8_t>, "uint8_t が IsValueType 型特性を満たしませんでした。");
static_assert(Traits::IsValueType<uint16_t>, "uint16_t が IsValueType 型特性を満たしませんでした。");
static_assert(Traits::IsValueType<uint32_t>, "uint32_t が IsValueType 型特性を満たしませんでした。");
static_assert(Traits::IsValueType<uint64_t>, "uint64_t が IsValueType 型特性を満たしませんでした。");
static_assert(Traits::IsValueType<uintmax_t>, "uintmax_t が IsValueType 型特性を満たしませんでした。");
static_assert(Traits::IsValueType<uintptr_t>, "uintptr_t が IsValueType 型特性を満たしませんでした。");
static_assert(Traits::IsValueType<int8_t>, "int8_t が IsValueType 型特性を満たしませんでした。");
static_assert(Traits::IsValueType<int16_t>, "int16_t が IsValueType 型特性を満たしませんでした。");
static_assert(Traits::IsValueType<int32_t>, "int32_t が IsValueType 型特性を満たしませんでした。");
static_assert(Traits::IsValueType<int64_t>, "int64_t が IsValueType 型特性を満たしませんでした。");
static_assert(Traits::IsValueType<intmax_t>, "intmax_t が IsValueType 型特性を満たしませんでした。");
static_assert(Traits::IsValueType<intptr_t>, "intptr_t が IsValueType 型特性を満たしませんでした。");
static_assert(Traits::IsValueType<float>, "float が IsValueType 型特性を満たしませんでした。");
static_assert(Traits::IsValueType<double>, "double が IsValueType 型特性を満たしませんでした。");
static_assert(Traits::IsValueType<size_t>, "size_t が IsValueType 型特性を満たしませんでした。");
static_assert(Traits::IsValueType<std::nullptr_t>, "std::nullptr_t が IsValueType 型特性を満たしませんでした。");
static_assert(Traits::IsValueType<std::byte>, "std::byte が IsValueType 型特性を満たしませんでした。");
static_assert(!Traits::IsValueType<std::string>, "std::string が IsValueType 型特性を満たしました。");

static_assert(Traits::IsNumericalType<bool>, "bool が IsNumericalType 型特性を満たしませんでした。");
static_assert(Traits::IsNumericalType<uint8_t>, "uint8_t が IsNumericalType 型特性を満たしませんでした。");
static_assert(Traits::IsNumericalType<uint16_t>, "uint16_t が IsNumericalType 型特性を満たしませんでした。");
static_assert(Traits::IsNumericalType<uint32_t>, "uint32_t が IsNumericalType 型特性を満たしませんでした。");
static_assert(Traits::IsNumericalType<uint64_t>, "uint64_t が IsNumericalType 型特性を満たしませんでした。");
static_assert(Traits::IsNumericalType<uintmax_t>, "uintmax_t が IsNumericalType 型特性を満たしませんでした。");
static_assert(Traits::IsNumericalType<uintptr_t>, "uintptr_t が IsNumericalType 型特性を満たしませんでした。");
static_assert(Traits::IsNumericalType<int8_t>, "int8_t が IsNumericalType 型特性を満たしませんでした。");
static_assert(Traits::IsNumericalType<int16_t>, "int16_t が IsNumericalType 型特性を満たしませんでした。");
static_assert(Traits::IsNumericalType<int32_t>, "int32_t が IsNumericalType 型特性を満たしませんでした。");
static_assert(Traits::IsNumericalType<int64_t>, "int64_t が IsNumericalType 型特性を満たしませんでした。");
static_assert(Traits::IsNumericalType<intmax_t>, "intmax_t が IsNumericalType 型特性を満たしませんでした。");
static_assert(Traits::IsNumericalType<intptr_t>, "intptr_t が IsNumericalType 型特性を満たしませんでした。");
static_assert(Traits::IsNumericalType<float>, "float が IsNumericalType 型特性を満たしませんでした。");
static_assert(Traits::IsNumericalType<double>, "double が IsNumericalType 型特性を満たしませんでした。");
static_assert(Traits::IsNumericalType<size_t>, "size_t が IsNumericalType 型特性を満たしませんでした。");
static_assert(!Traits::IsNumericalType<std::byte>, "std::byte が IsNumericalType 型特性を満たしました。");
static_assert(!Traits::IsNumericalType<std::string>, "std::string が IsNumericalType 型特性を満たしました。");

static_assert(!Traits::IsIntegralType<bool>, "bool が IsIntegralType 型特性を満たしました。");
static_assert(Traits::IsIntegralType<uint8_t>, "uint8_t が IsIntegralType 型特性を満たしませんでした。");
static_assert(Traits::IsIntegralType<uint16_t>, "uint16_t が IsIntegralType 型特性を満たしませんでした。");
static_assert(Traits::IsIntegralType<uint32_t>, "uint32_t が IsIntegralType 型特性を満たしませんでした。");
static_assert(Traits::IsIntegralType<uint64_t>, "uint64_t が IsIntegralType 型特性を満たしませんでした。");
static_assert(Traits::IsIntegralType<uintmax_t>, "uintmax_t が IsIntegralType 型特性を満たしませんでした。");
static_assert(Traits::IsIntegralType<uintptr_t>, "uintptr_t が IsIntegralType 型特性を満たしませんでした。");
static_assert(Traits::IsIntegralType<int8_t>, "int8_t が IsIntegralType 型特性を満たしませんでした。");
static_assert(Traits::IsIntegralType<int16_t>, "int16_t が IsIntegralType 型特性を満たしませんでした。");
static_assert(Traits::IsIntegralType<int32_t>, "int32_t が IsIntegralType 型特性を満たしませんでした。");
static_assert(Traits::IsIntegralType<int64_t>, "int64_t が IsIntegralType 型特性を満たしませんでした。");
static_assert(Traits::IsIntegralType<intmax_t>, "intmax_t が IsIntegralType 型特性を満たしませんでした。");
static_assert(Traits::IsIntegralType<intptr_t>, "intptr_t が IsIntegralType 型特性を満たしませんでした。");
static_assert(!Traits::IsIntegralType<float>, "float が IsIntegralType 型特性を満たしました。");
static_assert(!Traits::IsIntegralType<double>, "double が IsIntegralType 型特性を満たしました。");
static_assert(Traits::IsIntegralType<size_t>, "size_t が IsIntegralType 型特性を満たしませんでした。");
static_assert(!Traits::IsIntegralType<std::byte>, "std::byte が IsIntegralType 型特性を満たしました。");
static_assert(!Traits::IsIntegralType<std::string>, "std::string が IsIntegralType 型特性を満たしました。");

static_assert(Traits::IsBitSequenceType<bool>, "bool が IsBitSequenceType 型特性を満たしませんでした。");
static_assert(Traits::IsBitSequenceType<uint8_t>, "uint8_t が IsBitSequenceType 型特性を満たしませんでした。");
static_assert(Traits::IsBitSequenceType<uint16_t>, "uint16_t が IsBitSequenceType 型特性を満たしませんでした。");
static_assert(Traits::IsBitSequenceType<uint32_t>, "uint32_t が IsBitSequenceType 型特性を満たしませんでした。");
static_assert(Traits::IsBitSequenceType<uint64_t>, "uint64_t が IsBitSequenceType 型特性を満たしませんでした。");
static_assert(Traits::IsBitSequenceType<uintmax_t>, "uintmax_t が IsBitSequenceType 型特性を満たしませんでした。");
static_assert(!Traits::IsBitSequenceType<int8_t>, "int8_t が IsBitSequenceType 型特性を満たしました。");
static_assert(!Traits::IsBitSequenceType<int16_t>, "int16_t が IsBitSequenceType 型特性を満たしました。");
static_assert(!Traits::IsBitSequenceType<int32_t>, "int32_t が IsBitSequenceType 型特性を満たしました。");
static_assert(!Traits::IsBitSequenceType<int64_t>, "int64_t が IsBitSequenceType 型特性を満たしました。");
static_assert(!Traits::IsBitSequenceType<intmax_t>, "intmax_t が IsBitSequenceType 型特性を満たしませんでした。");
static_assert(!Traits::IsBitSequenceType<float>, "float が IsBitSequenceType 型特性を満たしました。");
static_assert(!Traits::IsBitSequenceType<double>, "double が IsBitSequenceType 型特性を満たしました。");
static_assert(Traits::IsBitSequenceType<std::byte>, "std::byte が IsBitSequenceType 型特性を満たしませんでした。");
static_assert(!Traits::IsBitSequenceType<std::string>, "std::string が IsBitSequenceType 型特性を満たしました。");

static_assert(Traits::IsStdLegacyIterator<std::array<int, 16>::iterator>, "std::array のイテレータは LegacyIterator を満たしますが、識別結果は false  を返しました。");
static_assert(Traits::IsStdLegacyInputIterator<std::array<int, 16>::iterator>, "std::array のイテレータは LegacyInputIterator を満たしますが、識別結果は false を返しました。");
static_assert(Traits::IsStdLegacyForwardIterator<std::array<int, 16>::iterator>, "std::array のイテレータは LegacyForwardIterator を満たしますが、識別結果は false を返しました。");
static_assert(Traits::IsStdLegacyBidirectionalIterator<std::array<int, 16>::iterator>, "std::array のイテレータは LegacyBidirectionalIterator を満たしますが、識別結果は false を返しました。");
static_assert(Traits::IsStdLegacyRandomAccessIterator<std::array<int, 16>::iterator>, "std::array のイテレータは LegacyRandomAccessIterator を満たしますが、識別結果は false を返しました。");
static_assert(Traits::IsStdLegacyOutputIterator<std::array<int, 16>::iterator, int>, "std::array のイテレータは LegacyOutputIterator を満たしますが、識別結果は false を返しました。");

static_assert(Traits::IsStdLegacyIterator<std::vector<int>::iterator>, "std::vector のイテレータは LegacyIterator を満たしますが、識別結果は false を返しました。");
static_assert(Traits::IsStdLegacyInputIterator<std::vector<int>::iterator>, "std::vector のイテレータは LegacyInputIterator を満たしますが、識別結果は false を返しました。");
static_assert(Traits::IsStdLegacyForwardIterator<std::vector<int>::iterator>, "std::vector のイテレータは LegacyForwardIterator を満たしますが、識別結果は false を返しました。");
static_assert(Traits::IsStdLegacyBidirectionalIterator<std::vector<int>::iterator>, "std::vector のイテレータは LegacyBidirectionalIterator を満たしますが、識別結果は false を返しました。");
static_assert(Traits::IsStdLegacyRandomAccessIterator<std::vector<int>::iterator>, "std::vector のイテレータは LegacyRandomAccessIterator を満たしますが、識別結果は false を返しました。");
static_assert(Traits::IsStdLegacyOutputIterator<std::vector<int>::iterator, int>, "std::vector のイテレータは LegacyOutputIterator を満たしますが、識別結果は false を返しました。");

static_assert(Traits::IsStdLegacyIterator<std::deque<int>::iterator>, "std::deque のイテレータは LegacyIterator を満たしますが、識別結果は false を返しました。");
static_assert(Traits::IsStdLegacyInputIterator<std::deque<int>::iterator>, "std::deque のイテレータは LegacyInputIterator を満たしますが、識別結果は false を返しました。");
static_assert(Traits::IsStdLegacyForwardIterator<std::deque<int>::iterator>, "std::deque のイテレータは LegacyForwardIterator を満たしますが、識別結果は false を返しました。");
static_assert(Traits::IsStdLegacyBidirectionalIterator<std::deque<int>::iterator>, "std::deque のイテレータは LegacyBidirectionalIterator を満たしますが、識別結果は false を返しました。");
static_assert(Traits::IsStdLegacyRandomAccessIterator<std::deque<int>::iterator>, "std::deque のイテレータは LegacyRandomAccessIterator を満たしますが、識別結果は false を返しました。");
static_assert(Traits::IsStdLegacyOutputIterator<std::deque<int>::iterator, int>, "std::deque のイテレータは LegacyOutputIterator を満たしますが、識別結果は false を返しました。");

static_assert(Traits::IsStdLegacyIterator<std::list<int>::iterator>, "std::list のイテレータは LegacyIterator を満たしますが、識別結果は false を返しました。");
static_assert(Traits::IsStdLegacyInputIterator<std::list<int>::iterator>, "std::list のイテレータは LegacyInputIterator を満たしますが、識別結果は false を返しました。");
static_assert(Traits::IsStdLegacyForwardIterator<std::list<int>::iterator>, "std::list のイテレータは LegacyForwardIterator を満たしますが、識別結果は false を返しました。");
static_assert(Traits::IsStdLegacyBidirectionalIterator<std::list<int>::iterator>, "std::list のイテレータは LegacyBidirectionalIterator を満たしますが、識別結果は false を返しました。");
static_assert(!Traits::IsStdLegacyRandomAccessIterator<std::list<int>::iterator>, "std::list のイテレータは LegacyRandomAccessIterator を満たしませんが、識別結果は true を返しました。");
static_assert(Traits::IsStdLegacyOutputIterator<std::list<int>::iterator, int>, "std::list のイテレータは LegacyOutputIterator を満たしますが、識別結果は false を返しました。");

static_assert(Traits::SubscriptResultIsConvertible<std::array<uint8_t, 20>, size_t, uint8_t>, "std::array<uint8_t, 20> に operator[](size_t) -> uint8_t がありません");
static_assert(Traits::DereferenceResultIsConvertible<int*, int>, "int* に operator*() -> int がありません");

static_assert(BitWidth<bool> == 1UL, "bool のビット幅が 1 ではありません");
static_assert(BitWidth<uint8_t> == 8UL, "uint8_t のビット幅が 8 ではありません");
static_assert(BitWidth<uint16_t> == 16UL, "uint16_t のビット幅が 16 ではありません");
static_assert(BitWidth<uint32_t> == 32UL, "uint32_t のビット幅が 32 ではありません");
static_assert(BitWidth<uint64_t> == 64UL, "uint64_t のビット幅が 64 ではありません");
static_assert(BitWidth<std::bitset<14>> == 14UL, "std::bitset<14> のビット幅が 14 ではありません");
