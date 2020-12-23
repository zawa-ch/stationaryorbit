//	stationaryorbit.core:/fixedpoint
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
#include "stationaryorbit/core/fixedpoint.hpp"
using namespace zawa_ch::StationaryOrbit;

template class
zawa_ch::StationaryOrbit::FixedPoint<uint8_t, 7>;
template class
zawa_ch::StationaryOrbit::FixedPoint<uint16_t, 8>;
template class
zawa_ch::StationaryOrbit::FixedPoint<uint16_t, 15>;
template class
zawa_ch::StationaryOrbit::FixedPoint<uint32_t, 16>;
template class
zawa_ch::StationaryOrbit::FixedPoint<uint32_t, 31>;
template class
zawa_ch::StationaryOrbit::FixedPoint<uint64_t, 32>;
template class
zawa_ch::StationaryOrbit::FixedPoint<uint64_t, 63>;

// FixedPointの型要件
// 算術型である
// - 値型である
//   - デフォルトコンストラクタを持つ
//   - デフォルトコンストラクタがnoexceptである
//   - デフォルトコンストラクタがtrivialである
//   - コピーコンストラクタを持つ
//   - コピーコンストラクタがnoexceptである
//   - コピーコンストラクタがtrivialである
//   - ムーブコンストラクタを持つ
//   - ムーブコンストラクタがnoexceptである
//   - ムーブコンストラクタがtrivialである
//   - コピー代入演算子を持つ
//   - コピー代入演算子がnoexceptである
//   - コピー代入演算子がtrivialである
//   - ムーブ代入演算子を持つ
//   - ムーブ代入演算子がnoexceptである
//   - ムーブ代入演算子がtrivialである
//   - デストラクタを持つ
//   - デストラクタがnoexceptである
//   - デストラクタがtrivialである
//   - 等価比較ができる
//     - bool T::operator ==(T) を持つ
//     - bool T::operator !=(T) を持つ
// - 算術演算を行うことができる
//   - 単項演算子を持つ
//     - T T::operator +()を持つ
//     - T T::operator -()を持つ
//   - 加法演算子を持つ
//     - T T::operator +(T)を持つ
//     - T T::operator -(T)を持つ
//   - 乗法演算子を持つ
//     - T T::operator *(T)を持つ
//     - T T::operator /(T)を持つ
// - 比較可能である
//   - bool T::operator <(T)を持つ
//   - bool T::operator >(T)を持つ
//   - bool T::operator <=(T)を持つ
//   - bool T::operator >=(T)を持つ
// - std::numeric_limits<T>::is_specializedがtrueである
static_assert(zawa_ch::StationaryOrbit::Traits::IsNumeralType<zawa_ch::StationaryOrbit::FixedPoint8q7_t>);
static_assert(zawa_ch::StationaryOrbit::Traits::IsNumeralType<zawa_ch::StationaryOrbit::FixedPoint16q8_t>);
static_assert(zawa_ch::StationaryOrbit::Traits::IsNumeralType<zawa_ch::StationaryOrbit::FixedPoint16q15_t>);
static_assert(zawa_ch::StationaryOrbit::Traits::IsNumeralType<zawa_ch::StationaryOrbit::FixedPoint32q16_t>);
static_assert(zawa_ch::StationaryOrbit::Traits::IsNumeralType<zawa_ch::StationaryOrbit::FixedPoint32q31_t>);
static_assert(zawa_ch::StationaryOrbit::Traits::IsNumeralType<zawa_ch::StationaryOrbit::FixedPoint64q32_t>);
static_assert(zawa_ch::StationaryOrbit::Traits::IsNumeralType<zawa_ch::StationaryOrbit::FixedPoint64q63_t>);
// (int)からのコンストラクタを持つ
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::FixedPoint8q7_t, int>);
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::FixedPoint16q8_t, int>);
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::FixedPoint16q15_t, int>);
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::FixedPoint32q16_t, int>);
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::FixedPoint32q31_t, int>);
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::FixedPoint64q32_t, int>);
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::FixedPoint64q63_t, int>);
// (float)からのコンストラクタを持つ
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::FixedPoint8q7_t, float>);
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::FixedPoint16q8_t, float>);
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::FixedPoint16q15_t, float>);
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::FixedPoint32q16_t, float>);
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::FixedPoint32q31_t, float>);
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::FixedPoint64q32_t, float>);
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::FixedPoint64q63_t, float>);
// (double)からのコンストラクタを持つ
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::FixedPoint8q7_t, double>);
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::FixedPoint16q8_t, double>);
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::FixedPoint16q15_t, double>);
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::FixedPoint32q16_t, double>);
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::FixedPoint32q31_t, double>);
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::FixedPoint64q32_t, double>);
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::FixedPoint64q63_t, double>);

// 実体化済みFixedPointに対するArithmeticOperationの実体化
template zawa_ch::StationaryOrbit::ArithmeticOperation::AdditionResult<zawa_ch::StationaryOrbit::FixedPoint8q7_t> zawa_ch::StationaryOrbit::ArithmeticOperation::Add<zawa_ch::StationaryOrbit::FixedPoint8q7_t>(const zawa_ch::StationaryOrbit::FixedPoint8q7_t&, const zawa_ch::StationaryOrbit::FixedPoint8q7_t&);
template zawa_ch::StationaryOrbit::ArithmeticOperation::AdditionResult<zawa_ch::StationaryOrbit::FixedPoint16q8_t> zawa_ch::StationaryOrbit::ArithmeticOperation::Add<zawa_ch::StationaryOrbit::FixedPoint16q8_t>(const zawa_ch::StationaryOrbit::FixedPoint16q8_t&, const zawa_ch::StationaryOrbit::FixedPoint16q8_t&);
template zawa_ch::StationaryOrbit::ArithmeticOperation::AdditionResult<zawa_ch::StationaryOrbit::FixedPoint16q15_t> zawa_ch::StationaryOrbit::ArithmeticOperation::Add<zawa_ch::StationaryOrbit::FixedPoint16q15_t>(const zawa_ch::StationaryOrbit::FixedPoint16q15_t&, const zawa_ch::StationaryOrbit::FixedPoint16q15_t&);
template zawa_ch::StationaryOrbit::ArithmeticOperation::AdditionResult<zawa_ch::StationaryOrbit::FixedPoint32q16_t> zawa_ch::StationaryOrbit::ArithmeticOperation::Add<zawa_ch::StationaryOrbit::FixedPoint32q16_t>(const zawa_ch::StationaryOrbit::FixedPoint32q16_t&, const zawa_ch::StationaryOrbit::FixedPoint32q16_t&);
template zawa_ch::StationaryOrbit::ArithmeticOperation::AdditionResult<zawa_ch::StationaryOrbit::FixedPoint32q31_t> zawa_ch::StationaryOrbit::ArithmeticOperation::Add<zawa_ch::StationaryOrbit::FixedPoint32q31_t>(const zawa_ch::StationaryOrbit::FixedPoint32q31_t&, const zawa_ch::StationaryOrbit::FixedPoint32q31_t&);
template zawa_ch::StationaryOrbit::ArithmeticOperation::AdditionResult<zawa_ch::StationaryOrbit::FixedPoint64q32_t> zawa_ch::StationaryOrbit::ArithmeticOperation::Add<zawa_ch::StationaryOrbit::FixedPoint64q32_t>(const zawa_ch::StationaryOrbit::FixedPoint64q32_t&, const zawa_ch::StationaryOrbit::FixedPoint64q32_t&);
template zawa_ch::StationaryOrbit::ArithmeticOperation::AdditionResult<zawa_ch::StationaryOrbit::FixedPoint64q63_t> zawa_ch::StationaryOrbit::ArithmeticOperation::Add<zawa_ch::StationaryOrbit::FixedPoint64q63_t>(const zawa_ch::StationaryOrbit::FixedPoint64q63_t&, const zawa_ch::StationaryOrbit::FixedPoint64q63_t&);
template zawa_ch::StationaryOrbit::ArithmeticOperation::AdditionResult<zawa_ch::StationaryOrbit::FixedPoint8q7_t> zawa_ch::StationaryOrbit::ArithmeticOperation::Subtract<zawa_ch::StationaryOrbit::FixedPoint8q7_t>(const zawa_ch::StationaryOrbit::FixedPoint8q7_t&, const zawa_ch::StationaryOrbit::FixedPoint8q7_t&);
template zawa_ch::StationaryOrbit::ArithmeticOperation::AdditionResult<zawa_ch::StationaryOrbit::FixedPoint16q8_t> zawa_ch::StationaryOrbit::ArithmeticOperation::Subtract<zawa_ch::StationaryOrbit::FixedPoint16q8_t>(const zawa_ch::StationaryOrbit::FixedPoint16q8_t&, const zawa_ch::StationaryOrbit::FixedPoint16q8_t&);
template zawa_ch::StationaryOrbit::ArithmeticOperation::AdditionResult<zawa_ch::StationaryOrbit::FixedPoint16q15_t> zawa_ch::StationaryOrbit::ArithmeticOperation::Subtract<zawa_ch::StationaryOrbit::FixedPoint16q15_t>(const zawa_ch::StationaryOrbit::FixedPoint16q15_t&, const zawa_ch::StationaryOrbit::FixedPoint16q15_t&);
template zawa_ch::StationaryOrbit::ArithmeticOperation::AdditionResult<zawa_ch::StationaryOrbit::FixedPoint32q16_t> zawa_ch::StationaryOrbit::ArithmeticOperation::Subtract<zawa_ch::StationaryOrbit::FixedPoint32q16_t>(const zawa_ch::StationaryOrbit::FixedPoint32q16_t&, const zawa_ch::StationaryOrbit::FixedPoint32q16_t&);
template zawa_ch::StationaryOrbit::ArithmeticOperation::AdditionResult<zawa_ch::StationaryOrbit::FixedPoint32q31_t> zawa_ch::StationaryOrbit::ArithmeticOperation::Subtract<zawa_ch::StationaryOrbit::FixedPoint32q31_t>(const zawa_ch::StationaryOrbit::FixedPoint32q31_t&, const zawa_ch::StationaryOrbit::FixedPoint32q31_t&);
template zawa_ch::StationaryOrbit::ArithmeticOperation::AdditionResult<zawa_ch::StationaryOrbit::FixedPoint64q32_t> zawa_ch::StationaryOrbit::ArithmeticOperation::Subtract<zawa_ch::StationaryOrbit::FixedPoint64q32_t>(const zawa_ch::StationaryOrbit::FixedPoint64q32_t&, const zawa_ch::StationaryOrbit::FixedPoint64q32_t&);
template zawa_ch::StationaryOrbit::ArithmeticOperation::AdditionResult<zawa_ch::StationaryOrbit::FixedPoint64q63_t> zawa_ch::StationaryOrbit::ArithmeticOperation::Subtract<zawa_ch::StationaryOrbit::FixedPoint64q63_t>(const zawa_ch::StationaryOrbit::FixedPoint64q63_t&, const zawa_ch::StationaryOrbit::FixedPoint64q63_t&);
template zawa_ch::StationaryOrbit::ArithmeticOperation::MultiplicationResult<zawa_ch::StationaryOrbit::FixedPoint8q7_t> zawa_ch::StationaryOrbit::ArithmeticOperation::Multiply<zawa_ch::StationaryOrbit::FixedPoint8q7_t>(const zawa_ch::StationaryOrbit::FixedPoint8q7_t&, const zawa_ch::StationaryOrbit::FixedPoint8q7_t&);
template zawa_ch::StationaryOrbit::ArithmeticOperation::MultiplicationResult<zawa_ch::StationaryOrbit::FixedPoint16q8_t> zawa_ch::StationaryOrbit::ArithmeticOperation::Multiply<zawa_ch::StationaryOrbit::FixedPoint16q8_t>(const zawa_ch::StationaryOrbit::FixedPoint16q8_t&, const zawa_ch::StationaryOrbit::FixedPoint16q8_t&);
template zawa_ch::StationaryOrbit::ArithmeticOperation::MultiplicationResult<zawa_ch::StationaryOrbit::FixedPoint16q15_t> zawa_ch::StationaryOrbit::ArithmeticOperation::Multiply<zawa_ch::StationaryOrbit::FixedPoint16q15_t>(const zawa_ch::StationaryOrbit::FixedPoint16q15_t&, const zawa_ch::StationaryOrbit::FixedPoint16q15_t&);
template zawa_ch::StationaryOrbit::ArithmeticOperation::MultiplicationResult<zawa_ch::StationaryOrbit::FixedPoint32q16_t> zawa_ch::StationaryOrbit::ArithmeticOperation::Multiply<zawa_ch::StationaryOrbit::FixedPoint32q16_t>(const zawa_ch::StationaryOrbit::FixedPoint32q16_t&, const zawa_ch::StationaryOrbit::FixedPoint32q16_t&);
template zawa_ch::StationaryOrbit::ArithmeticOperation::MultiplicationResult<zawa_ch::StationaryOrbit::FixedPoint32q31_t> zawa_ch::StationaryOrbit::ArithmeticOperation::Multiply<zawa_ch::StationaryOrbit::FixedPoint32q31_t>(const zawa_ch::StationaryOrbit::FixedPoint32q31_t&, const zawa_ch::StationaryOrbit::FixedPoint32q31_t&);
template zawa_ch::StationaryOrbit::ArithmeticOperation::MultiplicationResult<zawa_ch::StationaryOrbit::FixedPoint64q32_t> zawa_ch::StationaryOrbit::ArithmeticOperation::Multiply<zawa_ch::StationaryOrbit::FixedPoint64q32_t>(const zawa_ch::StationaryOrbit::FixedPoint64q32_t&, const zawa_ch::StationaryOrbit::FixedPoint64q32_t&);
template zawa_ch::StationaryOrbit::ArithmeticOperation::MultiplicationResult<zawa_ch::StationaryOrbit::FixedPoint64q63_t> zawa_ch::StationaryOrbit::ArithmeticOperation::Multiply<zawa_ch::StationaryOrbit::FixedPoint64q63_t>(const zawa_ch::StationaryOrbit::FixedPoint64q63_t&, const zawa_ch::StationaryOrbit::FixedPoint64q63_t&);
template zawa_ch::StationaryOrbit::ArithmeticOperation::MultiplicationResult<zawa_ch::StationaryOrbit::FixedPoint8q7_t> zawa_ch::StationaryOrbit::ArithmeticOperation::Divide<zawa_ch::StationaryOrbit::FixedPoint8q7_t>(const zawa_ch::StationaryOrbit::FixedPoint8q7_t&, const zawa_ch::StationaryOrbit::FixedPoint8q7_t&);
template zawa_ch::StationaryOrbit::ArithmeticOperation::MultiplicationResult<zawa_ch::StationaryOrbit::FixedPoint16q8_t> zawa_ch::StationaryOrbit::ArithmeticOperation::Divide<zawa_ch::StationaryOrbit::FixedPoint16q8_t>(const zawa_ch::StationaryOrbit::FixedPoint16q8_t&, const zawa_ch::StationaryOrbit::FixedPoint16q8_t&);
template zawa_ch::StationaryOrbit::ArithmeticOperation::MultiplicationResult<zawa_ch::StationaryOrbit::FixedPoint16q15_t> zawa_ch::StationaryOrbit::ArithmeticOperation::Divide<zawa_ch::StationaryOrbit::FixedPoint16q15_t>(const zawa_ch::StationaryOrbit::FixedPoint16q15_t&, const zawa_ch::StationaryOrbit::FixedPoint16q15_t&);
template zawa_ch::StationaryOrbit::ArithmeticOperation::MultiplicationResult<zawa_ch::StationaryOrbit::FixedPoint32q16_t> zawa_ch::StationaryOrbit::ArithmeticOperation::Divide<zawa_ch::StationaryOrbit::FixedPoint32q16_t>(const zawa_ch::StationaryOrbit::FixedPoint32q16_t&, const zawa_ch::StationaryOrbit::FixedPoint32q16_t&);
template zawa_ch::StationaryOrbit::ArithmeticOperation::MultiplicationResult<zawa_ch::StationaryOrbit::FixedPoint32q31_t> zawa_ch::StationaryOrbit::ArithmeticOperation::Divide<zawa_ch::StationaryOrbit::FixedPoint32q31_t>(const zawa_ch::StationaryOrbit::FixedPoint32q31_t&, const zawa_ch::StationaryOrbit::FixedPoint32q31_t&);
template zawa_ch::StationaryOrbit::ArithmeticOperation::MultiplicationResult<zawa_ch::StationaryOrbit::FixedPoint64q32_t> zawa_ch::StationaryOrbit::ArithmeticOperation::Divide<zawa_ch::StationaryOrbit::FixedPoint64q32_t>(const zawa_ch::StationaryOrbit::FixedPoint64q32_t&, const zawa_ch::StationaryOrbit::FixedPoint64q32_t&);
template zawa_ch::StationaryOrbit::ArithmeticOperation::MultiplicationResult<zawa_ch::StationaryOrbit::FixedPoint64q63_t> zawa_ch::StationaryOrbit::ArithmeticOperation::Divide<zawa_ch::StationaryOrbit::FixedPoint64q63_t>(const zawa_ch::StationaryOrbit::FixedPoint64q63_t&, const zawa_ch::StationaryOrbit::FixedPoint64q63_t&);
template zawa_ch::StationaryOrbit::FixedPoint8q7_t zawa_ch::StationaryOrbit::ArithmeticOperation::SaturateAdd<zawa_ch::StationaryOrbit::FixedPoint8q7_t>(const zawa_ch::StationaryOrbit::FixedPoint8q7_t&, const zawa_ch::StationaryOrbit::FixedPoint8q7_t&);
template zawa_ch::StationaryOrbit::FixedPoint16q8_t zawa_ch::StationaryOrbit::ArithmeticOperation::SaturateAdd<zawa_ch::StationaryOrbit::FixedPoint16q8_t>(const zawa_ch::StationaryOrbit::FixedPoint16q8_t&, const zawa_ch::StationaryOrbit::FixedPoint16q8_t&);
template zawa_ch::StationaryOrbit::FixedPoint16q15_t zawa_ch::StationaryOrbit::ArithmeticOperation::SaturateAdd<zawa_ch::StationaryOrbit::FixedPoint16q15_t>(const zawa_ch::StationaryOrbit::FixedPoint16q15_t&, const zawa_ch::StationaryOrbit::FixedPoint16q15_t&);
template zawa_ch::StationaryOrbit::FixedPoint32q16_t zawa_ch::StationaryOrbit::ArithmeticOperation::SaturateAdd<zawa_ch::StationaryOrbit::FixedPoint32q16_t>(const zawa_ch::StationaryOrbit::FixedPoint32q16_t&, const zawa_ch::StationaryOrbit::FixedPoint32q16_t&);
template zawa_ch::StationaryOrbit::FixedPoint32q31_t zawa_ch::StationaryOrbit::ArithmeticOperation::SaturateAdd<zawa_ch::StationaryOrbit::FixedPoint32q31_t>(const zawa_ch::StationaryOrbit::FixedPoint32q31_t&, const zawa_ch::StationaryOrbit::FixedPoint32q31_t&);
template zawa_ch::StationaryOrbit::FixedPoint64q32_t zawa_ch::StationaryOrbit::ArithmeticOperation::SaturateAdd<zawa_ch::StationaryOrbit::FixedPoint64q32_t>(const zawa_ch::StationaryOrbit::FixedPoint64q32_t&, const zawa_ch::StationaryOrbit::FixedPoint64q32_t&);
template zawa_ch::StationaryOrbit::FixedPoint64q63_t zawa_ch::StationaryOrbit::ArithmeticOperation::SaturateAdd<zawa_ch::StationaryOrbit::FixedPoint64q63_t>(const zawa_ch::StationaryOrbit::FixedPoint64q63_t&, const zawa_ch::StationaryOrbit::FixedPoint64q63_t&);
template zawa_ch::StationaryOrbit::FixedPoint8q7_t zawa_ch::StationaryOrbit::ArithmeticOperation::SaturateSubtract<zawa_ch::StationaryOrbit::FixedPoint8q7_t>(const zawa_ch::StationaryOrbit::FixedPoint8q7_t&, const zawa_ch::StationaryOrbit::FixedPoint8q7_t&);
template zawa_ch::StationaryOrbit::FixedPoint16q8_t zawa_ch::StationaryOrbit::ArithmeticOperation::SaturateSubtract<zawa_ch::StationaryOrbit::FixedPoint16q8_t>(const zawa_ch::StationaryOrbit::FixedPoint16q8_t&, const zawa_ch::StationaryOrbit::FixedPoint16q8_t&);
template zawa_ch::StationaryOrbit::FixedPoint16q15_t zawa_ch::StationaryOrbit::ArithmeticOperation::SaturateSubtract<zawa_ch::StationaryOrbit::FixedPoint16q15_t>(const zawa_ch::StationaryOrbit::FixedPoint16q15_t&, const zawa_ch::StationaryOrbit::FixedPoint16q15_t&);
template zawa_ch::StationaryOrbit::FixedPoint32q16_t zawa_ch::StationaryOrbit::ArithmeticOperation::SaturateSubtract<zawa_ch::StationaryOrbit::FixedPoint32q16_t>(const zawa_ch::StationaryOrbit::FixedPoint32q16_t&, const zawa_ch::StationaryOrbit::FixedPoint32q16_t&);
template zawa_ch::StationaryOrbit::FixedPoint32q31_t zawa_ch::StationaryOrbit::ArithmeticOperation::SaturateSubtract<zawa_ch::StationaryOrbit::FixedPoint32q31_t>(const zawa_ch::StationaryOrbit::FixedPoint32q31_t&, const zawa_ch::StationaryOrbit::FixedPoint32q31_t&);
template zawa_ch::StationaryOrbit::FixedPoint64q32_t zawa_ch::StationaryOrbit::ArithmeticOperation::SaturateSubtract<zawa_ch::StationaryOrbit::FixedPoint64q32_t>(const zawa_ch::StationaryOrbit::FixedPoint64q32_t&, const zawa_ch::StationaryOrbit::FixedPoint64q32_t&);
template zawa_ch::StationaryOrbit::FixedPoint64q63_t zawa_ch::StationaryOrbit::ArithmeticOperation::SaturateSubtract<zawa_ch::StationaryOrbit::FixedPoint64q63_t>(const zawa_ch::StationaryOrbit::FixedPoint64q63_t&, const zawa_ch::StationaryOrbit::FixedPoint64q63_t&);
template zawa_ch::StationaryOrbit::FixedPoint8q7_t zawa_ch::StationaryOrbit::ArithmeticOperation::SaturateMultiply<zawa_ch::StationaryOrbit::FixedPoint8q7_t>(const zawa_ch::StationaryOrbit::FixedPoint8q7_t&, const zawa_ch::StationaryOrbit::FixedPoint8q7_t&);
template zawa_ch::StationaryOrbit::FixedPoint16q8_t zawa_ch::StationaryOrbit::ArithmeticOperation::SaturateMultiply<zawa_ch::StationaryOrbit::FixedPoint16q8_t>(const zawa_ch::StationaryOrbit::FixedPoint16q8_t&, const zawa_ch::StationaryOrbit::FixedPoint16q8_t&);
template zawa_ch::StationaryOrbit::FixedPoint16q15_t zawa_ch::StationaryOrbit::ArithmeticOperation::SaturateMultiply<zawa_ch::StationaryOrbit::FixedPoint16q15_t>(const zawa_ch::StationaryOrbit::FixedPoint16q15_t&, const zawa_ch::StationaryOrbit::FixedPoint16q15_t&);
template zawa_ch::StationaryOrbit::FixedPoint32q16_t zawa_ch::StationaryOrbit::ArithmeticOperation::SaturateMultiply<zawa_ch::StationaryOrbit::FixedPoint32q16_t>(const zawa_ch::StationaryOrbit::FixedPoint32q16_t&, const zawa_ch::StationaryOrbit::FixedPoint32q16_t&);
template zawa_ch::StationaryOrbit::FixedPoint32q31_t zawa_ch::StationaryOrbit::ArithmeticOperation::SaturateMultiply<zawa_ch::StationaryOrbit::FixedPoint32q31_t>(const zawa_ch::StationaryOrbit::FixedPoint32q31_t&, const zawa_ch::StationaryOrbit::FixedPoint32q31_t&);
template zawa_ch::StationaryOrbit::FixedPoint64q32_t zawa_ch::StationaryOrbit::ArithmeticOperation::SaturateMultiply<zawa_ch::StationaryOrbit::FixedPoint64q32_t>(const zawa_ch::StationaryOrbit::FixedPoint64q32_t&, const zawa_ch::StationaryOrbit::FixedPoint64q32_t&);
template zawa_ch::StationaryOrbit::FixedPoint64q63_t zawa_ch::StationaryOrbit::ArithmeticOperation::SaturateMultiply<zawa_ch::StationaryOrbit::FixedPoint64q63_t>(const zawa_ch::StationaryOrbit::FixedPoint64q63_t&, const zawa_ch::StationaryOrbit::FixedPoint64q63_t&);
template zawa_ch::StationaryOrbit::FixedPoint8q7_t zawa_ch::StationaryOrbit::ArithmeticOperation::SaturateDivide<zawa_ch::StationaryOrbit::FixedPoint8q7_t>(const zawa_ch::StationaryOrbit::FixedPoint8q7_t&, const zawa_ch::StationaryOrbit::FixedPoint8q7_t&);
template zawa_ch::StationaryOrbit::FixedPoint16q8_t zawa_ch::StationaryOrbit::ArithmeticOperation::SaturateDivide<zawa_ch::StationaryOrbit::FixedPoint16q8_t>(const zawa_ch::StationaryOrbit::FixedPoint16q8_t&, const zawa_ch::StationaryOrbit::FixedPoint16q8_t&);
template zawa_ch::StationaryOrbit::FixedPoint16q15_t zawa_ch::StationaryOrbit::ArithmeticOperation::SaturateDivide<zawa_ch::StationaryOrbit::FixedPoint16q15_t>(const zawa_ch::StationaryOrbit::FixedPoint16q15_t&, const zawa_ch::StationaryOrbit::FixedPoint16q15_t&);
template zawa_ch::StationaryOrbit::FixedPoint32q16_t zawa_ch::StationaryOrbit::ArithmeticOperation::SaturateDivide<zawa_ch::StationaryOrbit::FixedPoint32q16_t>(const zawa_ch::StationaryOrbit::FixedPoint32q16_t&, const zawa_ch::StationaryOrbit::FixedPoint32q16_t&);
template zawa_ch::StationaryOrbit::FixedPoint32q31_t zawa_ch::StationaryOrbit::ArithmeticOperation::SaturateDivide<zawa_ch::StationaryOrbit::FixedPoint32q31_t>(const zawa_ch::StationaryOrbit::FixedPoint32q31_t&, const zawa_ch::StationaryOrbit::FixedPoint32q31_t&);
template zawa_ch::StationaryOrbit::FixedPoint64q32_t zawa_ch::StationaryOrbit::ArithmeticOperation::SaturateDivide<zawa_ch::StationaryOrbit::FixedPoint64q32_t>(const zawa_ch::StationaryOrbit::FixedPoint64q32_t&, const zawa_ch::StationaryOrbit::FixedPoint64q32_t&);
template zawa_ch::StationaryOrbit::FixedPoint64q63_t zawa_ch::StationaryOrbit::ArithmeticOperation::SaturateDivide<zawa_ch::StationaryOrbit::FixedPoint64q63_t>(const zawa_ch::StationaryOrbit::FixedPoint64q63_t&, const zawa_ch::StationaryOrbit::FixedPoint64q63_t&);
template zawa_ch::StationaryOrbit::FixedPoint8q7_t zawa_ch::StationaryOrbit::ArithmeticOperation::CheckedAdd<zawa_ch::StationaryOrbit::FixedPoint8q7_t>(const zawa_ch::StationaryOrbit::FixedPoint8q7_t&, const zawa_ch::StationaryOrbit::FixedPoint8q7_t&);
template zawa_ch::StationaryOrbit::FixedPoint16q8_t zawa_ch::StationaryOrbit::ArithmeticOperation::CheckedAdd<zawa_ch::StationaryOrbit::FixedPoint16q8_t>(const zawa_ch::StationaryOrbit::FixedPoint16q8_t&, const zawa_ch::StationaryOrbit::FixedPoint16q8_t&);
template zawa_ch::StationaryOrbit::FixedPoint16q15_t zawa_ch::StationaryOrbit::ArithmeticOperation::CheckedAdd<zawa_ch::StationaryOrbit::FixedPoint16q15_t>(const zawa_ch::StationaryOrbit::FixedPoint16q15_t&, const zawa_ch::StationaryOrbit::FixedPoint16q15_t&);
template zawa_ch::StationaryOrbit::FixedPoint32q16_t zawa_ch::StationaryOrbit::ArithmeticOperation::CheckedAdd<zawa_ch::StationaryOrbit::FixedPoint32q16_t>(const zawa_ch::StationaryOrbit::FixedPoint32q16_t&, const zawa_ch::StationaryOrbit::FixedPoint32q16_t&);
template zawa_ch::StationaryOrbit::FixedPoint32q31_t zawa_ch::StationaryOrbit::ArithmeticOperation::CheckedAdd<zawa_ch::StationaryOrbit::FixedPoint32q31_t>(const zawa_ch::StationaryOrbit::FixedPoint32q31_t&, const zawa_ch::StationaryOrbit::FixedPoint32q31_t&);
template zawa_ch::StationaryOrbit::FixedPoint64q32_t zawa_ch::StationaryOrbit::ArithmeticOperation::CheckedAdd<zawa_ch::StationaryOrbit::FixedPoint64q32_t>(const zawa_ch::StationaryOrbit::FixedPoint64q32_t&, const zawa_ch::StationaryOrbit::FixedPoint64q32_t&);
template zawa_ch::StationaryOrbit::FixedPoint64q63_t zawa_ch::StationaryOrbit::ArithmeticOperation::CheckedAdd<zawa_ch::StationaryOrbit::FixedPoint64q63_t>(const zawa_ch::StationaryOrbit::FixedPoint64q63_t&, const zawa_ch::StationaryOrbit::FixedPoint64q63_t&);
template zawa_ch::StationaryOrbit::FixedPoint8q7_t zawa_ch::StationaryOrbit::ArithmeticOperation::CheckedSubtract<zawa_ch::StationaryOrbit::FixedPoint8q7_t>(const zawa_ch::StationaryOrbit::FixedPoint8q7_t&, const zawa_ch::StationaryOrbit::FixedPoint8q7_t&);
template zawa_ch::StationaryOrbit::FixedPoint16q8_t zawa_ch::StationaryOrbit::ArithmeticOperation::CheckedSubtract<zawa_ch::StationaryOrbit::FixedPoint16q8_t>(const zawa_ch::StationaryOrbit::FixedPoint16q8_t&, const zawa_ch::StationaryOrbit::FixedPoint16q8_t&);
template zawa_ch::StationaryOrbit::FixedPoint16q15_t zawa_ch::StationaryOrbit::ArithmeticOperation::CheckedSubtract<zawa_ch::StationaryOrbit::FixedPoint16q15_t>(const zawa_ch::StationaryOrbit::FixedPoint16q15_t&, const zawa_ch::StationaryOrbit::FixedPoint16q15_t&);
template zawa_ch::StationaryOrbit::FixedPoint32q16_t zawa_ch::StationaryOrbit::ArithmeticOperation::CheckedSubtract<zawa_ch::StationaryOrbit::FixedPoint32q16_t>(const zawa_ch::StationaryOrbit::FixedPoint32q16_t&, const zawa_ch::StationaryOrbit::FixedPoint32q16_t&);
template zawa_ch::StationaryOrbit::FixedPoint32q31_t zawa_ch::StationaryOrbit::ArithmeticOperation::CheckedSubtract<zawa_ch::StationaryOrbit::FixedPoint32q31_t>(const zawa_ch::StationaryOrbit::FixedPoint32q31_t&, const zawa_ch::StationaryOrbit::FixedPoint32q31_t&);
template zawa_ch::StationaryOrbit::FixedPoint64q32_t zawa_ch::StationaryOrbit::ArithmeticOperation::CheckedSubtract<zawa_ch::StationaryOrbit::FixedPoint64q32_t>(const zawa_ch::StationaryOrbit::FixedPoint64q32_t&, const zawa_ch::StationaryOrbit::FixedPoint64q32_t&);
template zawa_ch::StationaryOrbit::FixedPoint64q63_t zawa_ch::StationaryOrbit::ArithmeticOperation::CheckedSubtract<zawa_ch::StationaryOrbit::FixedPoint64q63_t>(const zawa_ch::StationaryOrbit::FixedPoint64q63_t&, const zawa_ch::StationaryOrbit::FixedPoint64q63_t&);
template zawa_ch::StationaryOrbit::FixedPoint8q7_t zawa_ch::StationaryOrbit::ArithmeticOperation::CheckedMultiply<zawa_ch::StationaryOrbit::FixedPoint8q7_t>(const zawa_ch::StationaryOrbit::FixedPoint8q7_t&, const zawa_ch::StationaryOrbit::FixedPoint8q7_t&);
template zawa_ch::StationaryOrbit::FixedPoint16q8_t zawa_ch::StationaryOrbit::ArithmeticOperation::CheckedMultiply<zawa_ch::StationaryOrbit::FixedPoint16q8_t>(const zawa_ch::StationaryOrbit::FixedPoint16q8_t&, const zawa_ch::StationaryOrbit::FixedPoint16q8_t&);
template zawa_ch::StationaryOrbit::FixedPoint16q15_t zawa_ch::StationaryOrbit::ArithmeticOperation::CheckedMultiply<zawa_ch::StationaryOrbit::FixedPoint16q15_t>(const zawa_ch::StationaryOrbit::FixedPoint16q15_t&, const zawa_ch::StationaryOrbit::FixedPoint16q15_t&);
template zawa_ch::StationaryOrbit::FixedPoint32q16_t zawa_ch::StationaryOrbit::ArithmeticOperation::CheckedMultiply<zawa_ch::StationaryOrbit::FixedPoint32q16_t>(const zawa_ch::StationaryOrbit::FixedPoint32q16_t&, const zawa_ch::StationaryOrbit::FixedPoint32q16_t&);
template zawa_ch::StationaryOrbit::FixedPoint32q31_t zawa_ch::StationaryOrbit::ArithmeticOperation::CheckedMultiply<zawa_ch::StationaryOrbit::FixedPoint32q31_t>(const zawa_ch::StationaryOrbit::FixedPoint32q31_t&, const zawa_ch::StationaryOrbit::FixedPoint32q31_t&);
template zawa_ch::StationaryOrbit::FixedPoint64q32_t zawa_ch::StationaryOrbit::ArithmeticOperation::CheckedMultiply<zawa_ch::StationaryOrbit::FixedPoint64q32_t>(const zawa_ch::StationaryOrbit::FixedPoint64q32_t&, const zawa_ch::StationaryOrbit::FixedPoint64q32_t&);
template zawa_ch::StationaryOrbit::FixedPoint64q63_t zawa_ch::StationaryOrbit::ArithmeticOperation::CheckedMultiply<zawa_ch::StationaryOrbit::FixedPoint64q63_t>(const zawa_ch::StationaryOrbit::FixedPoint64q63_t&, const zawa_ch::StationaryOrbit::FixedPoint64q63_t&);
template zawa_ch::StationaryOrbit::FixedPoint8q7_t zawa_ch::StationaryOrbit::ArithmeticOperation::CheckedDivide<zawa_ch::StationaryOrbit::FixedPoint8q7_t>(const zawa_ch::StationaryOrbit::FixedPoint8q7_t&, const zawa_ch::StationaryOrbit::FixedPoint8q7_t&);
template zawa_ch::StationaryOrbit::FixedPoint16q8_t zawa_ch::StationaryOrbit::ArithmeticOperation::CheckedDivide<zawa_ch::StationaryOrbit::FixedPoint16q8_t>(const zawa_ch::StationaryOrbit::FixedPoint16q8_t&, const zawa_ch::StationaryOrbit::FixedPoint16q8_t&);
template zawa_ch::StationaryOrbit::FixedPoint16q15_t zawa_ch::StationaryOrbit::ArithmeticOperation::CheckedDivide<zawa_ch::StationaryOrbit::FixedPoint16q15_t>(const zawa_ch::StationaryOrbit::FixedPoint16q15_t&, const zawa_ch::StationaryOrbit::FixedPoint16q15_t&);
template zawa_ch::StationaryOrbit::FixedPoint32q16_t zawa_ch::StationaryOrbit::ArithmeticOperation::CheckedDivide<zawa_ch::StationaryOrbit::FixedPoint32q16_t>(const zawa_ch::StationaryOrbit::FixedPoint32q16_t&, const zawa_ch::StationaryOrbit::FixedPoint32q16_t&);
template zawa_ch::StationaryOrbit::FixedPoint32q31_t zawa_ch::StationaryOrbit::ArithmeticOperation::CheckedDivide<zawa_ch::StationaryOrbit::FixedPoint32q31_t>(const zawa_ch::StationaryOrbit::FixedPoint32q31_t&, const zawa_ch::StationaryOrbit::FixedPoint32q31_t&);
template zawa_ch::StationaryOrbit::FixedPoint64q32_t zawa_ch::StationaryOrbit::ArithmeticOperation::CheckedDivide<zawa_ch::StationaryOrbit::FixedPoint64q32_t>(const zawa_ch::StationaryOrbit::FixedPoint64q32_t&, const zawa_ch::StationaryOrbit::FixedPoint64q32_t&);
template zawa_ch::StationaryOrbit::FixedPoint64q63_t zawa_ch::StationaryOrbit::ArithmeticOperation::CheckedDivide<zawa_ch::StationaryOrbit::FixedPoint64q63_t>(const zawa_ch::StationaryOrbit::FixedPoint64q63_t&, const zawa_ch::StationaryOrbit::FixedPoint64q63_t&);
template bool zawa_ch::StationaryOrbit::ArithmeticOperation::MayOverflowWithAddition<zawa_ch::StationaryOrbit::FixedPoint8q7_t>(const zawa_ch::StationaryOrbit::FixedPoint8q7_t&, const zawa_ch::StationaryOrbit::FixedPoint8q7_t&);
template bool zawa_ch::StationaryOrbit::ArithmeticOperation::MayOverflowWithAddition<zawa_ch::StationaryOrbit::FixedPoint16q8_t>(const zawa_ch::StationaryOrbit::FixedPoint16q8_t&, const zawa_ch::StationaryOrbit::FixedPoint16q8_t&);
template bool zawa_ch::StationaryOrbit::ArithmeticOperation::MayOverflowWithAddition<zawa_ch::StationaryOrbit::FixedPoint16q15_t>(const zawa_ch::StationaryOrbit::FixedPoint16q15_t&, const zawa_ch::StationaryOrbit::FixedPoint16q15_t&);
template bool zawa_ch::StationaryOrbit::ArithmeticOperation::MayOverflowWithAddition<zawa_ch::StationaryOrbit::FixedPoint32q16_t>(const zawa_ch::StationaryOrbit::FixedPoint32q16_t&, const zawa_ch::StationaryOrbit::FixedPoint32q16_t&);
template bool zawa_ch::StationaryOrbit::ArithmeticOperation::MayOverflowWithAddition<zawa_ch::StationaryOrbit::FixedPoint32q31_t>(const zawa_ch::StationaryOrbit::FixedPoint32q31_t&, const zawa_ch::StationaryOrbit::FixedPoint32q31_t&);
template bool zawa_ch::StationaryOrbit::ArithmeticOperation::MayOverflowWithAddition<zawa_ch::StationaryOrbit::FixedPoint64q32_t>(const zawa_ch::StationaryOrbit::FixedPoint64q32_t&, const zawa_ch::StationaryOrbit::FixedPoint64q32_t&);
template bool zawa_ch::StationaryOrbit::ArithmeticOperation::MayOverflowWithAddition<zawa_ch::StationaryOrbit::FixedPoint64q63_t>(const zawa_ch::StationaryOrbit::FixedPoint64q63_t&, const zawa_ch::StationaryOrbit::FixedPoint64q63_t&);
template bool zawa_ch::StationaryOrbit::ArithmeticOperation::MayOverflowWithSubtraction<zawa_ch::StationaryOrbit::FixedPoint8q7_t>(const zawa_ch::StationaryOrbit::FixedPoint8q7_t&, const zawa_ch::StationaryOrbit::FixedPoint8q7_t&);
template bool zawa_ch::StationaryOrbit::ArithmeticOperation::MayOverflowWithSubtraction<zawa_ch::StationaryOrbit::FixedPoint16q8_t>(const zawa_ch::StationaryOrbit::FixedPoint16q8_t&, const zawa_ch::StationaryOrbit::FixedPoint16q8_t&);
template bool zawa_ch::StationaryOrbit::ArithmeticOperation::MayOverflowWithSubtraction<zawa_ch::StationaryOrbit::FixedPoint16q15_t>(const zawa_ch::StationaryOrbit::FixedPoint16q15_t&, const zawa_ch::StationaryOrbit::FixedPoint16q15_t&);
template bool zawa_ch::StationaryOrbit::ArithmeticOperation::MayOverflowWithSubtraction<zawa_ch::StationaryOrbit::FixedPoint32q16_t>(const zawa_ch::StationaryOrbit::FixedPoint32q16_t&, const zawa_ch::StationaryOrbit::FixedPoint32q16_t&);
template bool zawa_ch::StationaryOrbit::ArithmeticOperation::MayOverflowWithSubtraction<zawa_ch::StationaryOrbit::FixedPoint32q31_t>(const zawa_ch::StationaryOrbit::FixedPoint32q31_t&, const zawa_ch::StationaryOrbit::FixedPoint32q31_t&);
template bool zawa_ch::StationaryOrbit::ArithmeticOperation::MayOverflowWithSubtraction<zawa_ch::StationaryOrbit::FixedPoint64q32_t>(const zawa_ch::StationaryOrbit::FixedPoint64q32_t&, const zawa_ch::StationaryOrbit::FixedPoint64q32_t&);
template bool zawa_ch::StationaryOrbit::ArithmeticOperation::MayOverflowWithSubtraction<zawa_ch::StationaryOrbit::FixedPoint64q63_t>(const zawa_ch::StationaryOrbit::FixedPoint64q63_t&, const zawa_ch::StationaryOrbit::FixedPoint64q63_t&);
template bool zawa_ch::StationaryOrbit::ArithmeticOperation::MayOverflowWithMultiplication<zawa_ch::StationaryOrbit::FixedPoint8q7_t>(const zawa_ch::StationaryOrbit::FixedPoint8q7_t&, const zawa_ch::StationaryOrbit::FixedPoint8q7_t&);
template bool zawa_ch::StationaryOrbit::ArithmeticOperation::MayOverflowWithMultiplication<zawa_ch::StationaryOrbit::FixedPoint16q8_t>(const zawa_ch::StationaryOrbit::FixedPoint16q8_t&, const zawa_ch::StationaryOrbit::FixedPoint16q8_t&);
template bool zawa_ch::StationaryOrbit::ArithmeticOperation::MayOverflowWithMultiplication<zawa_ch::StationaryOrbit::FixedPoint16q15_t>(const zawa_ch::StationaryOrbit::FixedPoint16q15_t&, const zawa_ch::StationaryOrbit::FixedPoint16q15_t&);
template bool zawa_ch::StationaryOrbit::ArithmeticOperation::MayOverflowWithMultiplication<zawa_ch::StationaryOrbit::FixedPoint32q16_t>(const zawa_ch::StationaryOrbit::FixedPoint32q16_t&, const zawa_ch::StationaryOrbit::FixedPoint32q16_t&);
template bool zawa_ch::StationaryOrbit::ArithmeticOperation::MayOverflowWithMultiplication<zawa_ch::StationaryOrbit::FixedPoint32q31_t>(const zawa_ch::StationaryOrbit::FixedPoint32q31_t&, const zawa_ch::StationaryOrbit::FixedPoint32q31_t&);
template bool zawa_ch::StationaryOrbit::ArithmeticOperation::MayOverflowWithMultiplication<zawa_ch::StationaryOrbit::FixedPoint64q32_t>(const zawa_ch::StationaryOrbit::FixedPoint64q32_t&, const zawa_ch::StationaryOrbit::FixedPoint64q32_t&);
template bool zawa_ch::StationaryOrbit::ArithmeticOperation::MayOverflowWithMultiplication<zawa_ch::StationaryOrbit::FixedPoint64q63_t>(const zawa_ch::StationaryOrbit::FixedPoint64q63_t&, const zawa_ch::StationaryOrbit::FixedPoint64q63_t&);
template bool zawa_ch::StationaryOrbit::ArithmeticOperation::MayOverflowWithDivision<zawa_ch::StationaryOrbit::FixedPoint8q7_t>(const zawa_ch::StationaryOrbit::FixedPoint8q7_t&, const zawa_ch::StationaryOrbit::FixedPoint8q7_t&);
template bool zawa_ch::StationaryOrbit::ArithmeticOperation::MayOverflowWithDivision<zawa_ch::StationaryOrbit::FixedPoint16q8_t>(const zawa_ch::StationaryOrbit::FixedPoint16q8_t&, const zawa_ch::StationaryOrbit::FixedPoint16q8_t&);
template bool zawa_ch::StationaryOrbit::ArithmeticOperation::MayOverflowWithDivision<zawa_ch::StationaryOrbit::FixedPoint16q15_t>(const zawa_ch::StationaryOrbit::FixedPoint16q15_t&, const zawa_ch::StationaryOrbit::FixedPoint16q15_t&);
template bool zawa_ch::StationaryOrbit::ArithmeticOperation::MayOverflowWithDivision<zawa_ch::StationaryOrbit::FixedPoint32q16_t>(const zawa_ch::StationaryOrbit::FixedPoint32q16_t&, const zawa_ch::StationaryOrbit::FixedPoint32q16_t&);
template bool zawa_ch::StationaryOrbit::ArithmeticOperation::MayOverflowWithDivision<zawa_ch::StationaryOrbit::FixedPoint32q31_t>(const zawa_ch::StationaryOrbit::FixedPoint32q31_t&, const zawa_ch::StationaryOrbit::FixedPoint32q31_t&);
template bool zawa_ch::StationaryOrbit::ArithmeticOperation::MayOverflowWithDivision<zawa_ch::StationaryOrbit::FixedPoint64q32_t>(const zawa_ch::StationaryOrbit::FixedPoint64q32_t&, const zawa_ch::StationaryOrbit::FixedPoint64q32_t&);
template bool zawa_ch::StationaryOrbit::ArithmeticOperation::MayOverflowWithDivision<zawa_ch::StationaryOrbit::FixedPoint64q63_t>(const zawa_ch::StationaryOrbit::FixedPoint64q63_t&, const zawa_ch::StationaryOrbit::FixedPoint64q63_t&);
