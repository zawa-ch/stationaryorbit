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
// 値型である
// - デフォルトコンストラクタを持つ
// - デフォルトコンストラクタがnoexceptである
// - デフォルトコンストラクタがtrivialである
// - コピーコンストラクタを持つ
// - コピーコンストラクタがnoexceptである
// - コピーコンストラクタがtrivialである
// - ムーブコンストラクタを持つ
// - ムーブコンストラクタがnoexceptである
// - ムーブコンストラクタがtrivialである
// - コピー代入演算子を持つ
// - コピー代入演算子がnoexceptである
// - コピー代入演算子がtrivialである
// - ムーブ代入演算子を持つ
// - ムーブ代入演算子がnoexceptである
// - ムーブ代入演算子がtrivialである
// - デストラクタを持つ
// - デストラクタがnoexceptである
// - デストラクタがtrivialである
static_assert(zawa_ch::StationaryOrbit::Traits::IsValueType<zawa_ch::StationaryOrbit::FixedPoint8q7_t>);
static_assert(zawa_ch::StationaryOrbit::Traits::IsValueType<zawa_ch::StationaryOrbit::FixedPoint16q8_t>);
static_assert(zawa_ch::StationaryOrbit::Traits::IsValueType<zawa_ch::StationaryOrbit::FixedPoint16q15_t>);
static_assert(zawa_ch::StationaryOrbit::Traits::IsValueType<zawa_ch::StationaryOrbit::FixedPoint32q16_t>);
static_assert(zawa_ch::StationaryOrbit::Traits::IsValueType<zawa_ch::StationaryOrbit::FixedPoint32q31_t>);
static_assert(zawa_ch::StationaryOrbit::Traits::IsValueType<zawa_ch::StationaryOrbit::FixedPoint64q32_t>);
static_assert(zawa_ch::StationaryOrbit::Traits::IsValueType<zawa_ch::StationaryOrbit::FixedPoint64q63_t>);
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
// 基本的な算術演算子を持つ
static_assert(zawa_ch::StationaryOrbit::Traits::HasArithmeticOperation<zawa_ch::StationaryOrbit::FixedPoint8q7_t>);
static_assert(zawa_ch::StationaryOrbit::Traits::HasArithmeticOperation<zawa_ch::StationaryOrbit::FixedPoint16q8_t>);
static_assert(zawa_ch::StationaryOrbit::Traits::HasArithmeticOperation<zawa_ch::StationaryOrbit::FixedPoint16q15_t>);
static_assert(zawa_ch::StationaryOrbit::Traits::HasArithmeticOperation<zawa_ch::StationaryOrbit::FixedPoint32q16_t>);
static_assert(zawa_ch::StationaryOrbit::Traits::HasArithmeticOperation<zawa_ch::StationaryOrbit::FixedPoint32q31_t>);
static_assert(zawa_ch::StationaryOrbit::Traits::HasArithmeticOperation<zawa_ch::StationaryOrbit::FixedPoint64q32_t>);
static_assert(zawa_ch::StationaryOrbit::Traits::HasArithmeticOperation<zawa_ch::StationaryOrbit::FixedPoint64q63_t>);
