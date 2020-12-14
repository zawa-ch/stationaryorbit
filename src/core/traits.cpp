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
static_assert(Traits::Equatable<bool>, "bool が Equatable 型特性を満たしませんでした。");
static_assert(Traits::Equatable<uint8_t>, "uint8_t が Equatable 型特性を満たしませんでした。");
static_assert(Traits::Equatable<uint16_t>, "uint16_t が Equatable 型特性を満たしませんでした。");
static_assert(Traits::Equatable<uint32_t>, "uint32_t が Equatable 型特性を満たしませんでした。");
static_assert(Traits::Equatable<uint64_t>, "uint64_t が Equatable 型特性を満たしませんでした。");
static_assert(Traits::Equatable<uintmax_t>, "uintmax_t が Equatable 型特性を満たしませんでした。");
static_assert(Traits::Equatable<uintptr_t>, "uintptr_t が Equatable 型特性を満たしませんでした。");
static_assert(Traits::Equatable<int8_t>, "int8_t が Equatable 型特性を満たしませんでした。");
static_assert(Traits::Equatable<int16_t>, "int16_t が Equatable 型特性を満たしませんでした。");
static_assert(Traits::Equatable<int32_t>, "int32_t が Equatable 型特性を満たしませんでした。");
static_assert(Traits::Equatable<int64_t>, "int64_t が Equatable 型特性を満たしませんでした。");
static_assert(Traits::Equatable<intmax_t>, "intmax_t が Equatable 型特性を満たしませんでした。");
static_assert(Traits::Equatable<intptr_t>, "intptr_t が Equatable 型特性を満たしませんでした。");
static_assert(Traits::Equatable<float>, "float が Equatable 型特性を満たしませんでした。");
static_assert(Traits::Equatable<double>, "double が Equatable 型特性を満たしませんでした。");
static_assert(Traits::Equatable<size_t>, "size_t が Equatable 型特性を満たしませんでした。");
static_assert(Traits::Equatable<std::nullptr_t>, "std::nullptr_t が Equatable 型特性を満たしませんでした。");
static_assert(Traits::Equatable<std::byte>, "std::byte が Equatable 型特性を満たしませんでした。");
static_assert(Traits::Equatable<std::string>, "std::string が Equatable 型特性を満たしませんでした。");

static_assert(Traits::Comparable<uint8_t>, "uint8_t が Comparable 型特性を満たしませんでした。");
static_assert(Traits::Comparable<uint16_t>, "uint16_t が Comparable 型特性を満たしませんでした。");
static_assert(Traits::Comparable<uint32_t>, "uint32_t が Comparable 型特性を満たしませんでした。");
static_assert(Traits::Comparable<uint64_t>, "uint64_t が Comparable 型特性を満たしませんでした。");
static_assert(Traits::Comparable<uintmax_t>, "uintmax_t が Comparable 型特性を満たしませんでした。");
static_assert(Traits::Comparable<uintptr_t>, "uintptr_t が Comparable 型特性を満たしませんでした。");
static_assert(Traits::Comparable<int8_t>, "int8_t が Comparable 型特性を満たしませんでした。");
static_assert(Traits::Comparable<int16_t>, "int16_t が Comparable 型特性を満たしませんでした。");
static_assert(Traits::Comparable<int32_t>, "int32_t が Comparable 型特性を満たしませんでした。");
static_assert(Traits::Comparable<int64_t>, "int64_t が Comparable 型特性を満たしませんでした。");
static_assert(Traits::Comparable<intmax_t>, "intmax_t が Comparable 型特性を満たしませんでした。");
static_assert(Traits::Comparable<intptr_t>, "intptr_t が Comparable 型特性を満たしませんでした。");
static_assert(Traits::Comparable<float>, "float が Comparable 型特性を満たしませんでした。");
static_assert(Traits::Comparable<double>, "double が Comparable 型特性を満たしませんでした。");
static_assert(Traits::Comparable<size_t>, "size_t が Comparable 型特性を満たしませんでした。");
static_assert(Traits::Comparable<std::string>, "std::string が Comparable 型特性を満たしませんでした。");

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

static_assert(Traits::IsNumeralType<bool>, "bool が IsNumeralType 型特性を満たしませんでした。");
static_assert(Traits::IsNumeralType<uint8_t>, "uint8_t が IsNumeralType 型特性を満たしませんでした。");
static_assert(Traits::IsNumeralType<uint16_t>, "uint16_t が IsNumeralType 型特性を満たしませんでした。");
static_assert(Traits::IsNumeralType<uint32_t>, "uint32_t が IsNumeralType 型特性を満たしませんでした。");
static_assert(Traits::IsNumeralType<uint64_t>, "uint64_t が IsNumeralType 型特性を満たしませんでした。");
static_assert(Traits::IsNumeralType<uintmax_t>, "uintmax_t が IsNumeralType 型特性を満たしませんでした。");
static_assert(Traits::IsNumeralType<uintptr_t>, "uintptr_t が IsNumeralType 型特性を満たしませんでした。");
static_assert(Traits::IsNumeralType<int8_t>, "int8_t が IsNumeralType 型特性を満たしませんでした。");
static_assert(Traits::IsNumeralType<int16_t>, "int16_t が IsNumeralType 型特性を満たしませんでした。");
static_assert(Traits::IsNumeralType<int32_t>, "int32_t が IsNumeralType 型特性を満たしませんでした。");
static_assert(Traits::IsNumeralType<int64_t>, "int64_t が IsNumeralType 型特性を満たしませんでした。");
static_assert(Traits::IsNumeralType<intmax_t>, "intmax_t が IsNumeralType 型特性を満たしませんでした。");
static_assert(Traits::IsNumeralType<intptr_t>, "intptr_t が IsNumeralType 型特性を満たしませんでした。");
static_assert(Traits::IsNumeralType<float>, "float が IsNumeralType 型特性を満たしませんでした。");
static_assert(Traits::IsNumeralType<double>, "double が IsNumeralType 型特性を満たしませんでした。");
static_assert(Traits::IsNumeralType<size_t>, "size_t が IsNumeralType 型特性を満たしませんでした。");
static_assert(!Traits::IsNumeralType<std::byte>, "std::byte が IsNumeralType 型特性を満たしました。");
static_assert(!Traits::IsNumeralType<std::string>, "std::string が IsNumeralType 型特性を満たしました。");

static_assert(!Traits::IsIntegerType<bool>, "bool が IsIntegerType 型特性を満たしました。");
static_assert(Traits::IsIntegerType<uint8_t>, "uint8_t が IsIntegerType 型特性を満たしませんでした。");
static_assert(Traits::IsIntegerType<uint16_t>, "uint16_t が IsIntegerType 型特性を満たしませんでした。");
static_assert(Traits::IsIntegerType<uint32_t>, "uint32_t が IsIntegerType 型特性を満たしませんでした。");
static_assert(Traits::IsIntegerType<uint64_t>, "uint64_t が IsIntegerType 型特性を満たしませんでした。");
static_assert(Traits::IsIntegerType<uintmax_t>, "uintmax_t が IsIntegerType 型特性を満たしませんでした。");
static_assert(Traits::IsIntegerType<uintptr_t>, "uintptr_t が IsIntegerType 型特性を満たしませんでした。");
static_assert(Traits::IsIntegerType<int8_t>, "int8_t が IsIntegerType 型特性を満たしませんでした。");
static_assert(Traits::IsIntegerType<int16_t>, "int16_t が IsIntegerType 型特性を満たしませんでした。");
static_assert(Traits::IsIntegerType<int32_t>, "int32_t が IsIntegerType 型特性を満たしませんでした。");
static_assert(Traits::IsIntegerType<int64_t>, "int64_t が IsIntegerType 型特性を満たしませんでした。");
static_assert(Traits::IsIntegerType<intmax_t>, "intmax_t が IsIntegerType 型特性を満たしませんでした。");
static_assert(Traits::IsIntegerType<intptr_t>, "intptr_t が IsIntegerType 型特性を満たしませんでした。");
static_assert(!Traits::IsIntegerType<float>, "float が IsIntegerType 型特性を満たしました。");
static_assert(!Traits::IsIntegerType<double>, "double が IsIntegerType 型特性を満たしました。");
static_assert(Traits::IsIntegerType<size_t>, "size_t が IsIntegerType 型特性を満たしませんでした。");
static_assert(!Traits::IsIntegerType<std::byte>, "std::byte が IsIntegerType 型特性を満たしました。");
static_assert(!Traits::IsIntegerType<std::string>, "std::string が IsIntegerType 型特性を満たしました。");

static_assert(Traits::IsBitSequence<bool>, "bool が IsBitSequence 型特性を満たしませんでした。");
static_assert(Traits::IsBitSequence<uint8_t>, "uint8_t が IsBitSequence 型特性を満たしませんでした。");
static_assert(Traits::IsBitSequence<uint16_t>, "uint16_t が IsBitSequence 型特性を満たしませんでした。");
static_assert(Traits::IsBitSequence<uint32_t>, "uint32_t が IsBitSequence 型特性を満たしませんでした。");
static_assert(Traits::IsBitSequence<uint64_t>, "uint64_t が IsBitSequence 型特性を満たしませんでした。");
static_assert(Traits::IsBitSequence<uintmax_t>, "uintmax_t が IsBitSequence 型特性を満たしませんでした。");
static_assert(!Traits::IsBitSequence<int8_t>, "int8_t が IsBitSequence 型特性を満たしました。");
static_assert(!Traits::IsBitSequence<int16_t>, "int16_t が IsBitSequence 型特性を満たしました。");
static_assert(!Traits::IsBitSequence<int32_t>, "int32_t が IsBitSequence 型特性を満たしました。");
static_assert(!Traits::IsBitSequence<int64_t>, "int64_t が IsBitSequence 型特性を満たしました。");
static_assert(!Traits::IsBitSequence<intmax_t>, "intmax_t が IsBitSequence 型特性を満たしませんでした。");
static_assert(!Traits::IsBitSequence<float>, "float が IsBitSequence 型特性を満たしました。");
static_assert(!Traits::IsBitSequence<double>, "double が IsBitSequence 型特性を満たしました。");
static_assert(Traits::IsBitSequence<std::byte>, "std::byte が IsBitSequence 型特性を満たしませんでした。");
static_assert(!Traits::IsBitSequence<std::string>, "std::string が IsBitSequence 型特性を満たしました。");

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

static_assert(Traits::HasSubScript<std::array<uint8_t, 20>, size_t, uint8_t>, "std::array<uint8_t, 20> に operator[](size_t) -> uint8_t がありません");
static_assert(Traits::HasDereference<int*, int>, "int* に operator*() -> int がありません");

static_assert(BitWidth<bool> == 1UL, "bool のビット幅が 1 ではありません");
static_assert(BitWidth<uint8_t> == 8UL, "uint8_t のビット幅が 8 ではありません");
static_assert(BitWidth<uint16_t> == 16UL, "uint16_t のビット幅が 16 ではありません");
static_assert(BitWidth<uint32_t> == 32UL, "uint32_t のビット幅が 32 ではありません");
static_assert(BitWidth<uint64_t> == 64UL, "uint64_t のビット幅が 64 ではありません");
static_assert(BitWidth<std::bitset<14>> == 14UL, "std::bitset<14> のビット幅が 14 ではありません");
