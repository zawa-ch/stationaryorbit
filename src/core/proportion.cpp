//	stationaryorbit.core:/proportion
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
#include "stationaryorbit/core/proportion.hpp"
using namespace zawa_ch::StationaryOrbit;

template class
zawa_ch::StationaryOrbit::Proportion<bool>;
template class
zawa_ch::StationaryOrbit::Proportion<uint8_t>;
template class
zawa_ch::StationaryOrbit::Proportion<uint16_t>;
template class
zawa_ch::StationaryOrbit::Proportion<uint32_t>;
template class
zawa_ch::StationaryOrbit::Proportion<uint64_t>;

// Proportionの型要件
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
static_assert(zawa_ch::StationaryOrbit::Traits::IsValueType<zawa_ch::StationaryOrbit::Proportion1_t>);
static_assert(zawa_ch::StationaryOrbit::Traits::IsValueType<zawa_ch::StationaryOrbit::Proportion8_t>);
static_assert(zawa_ch::StationaryOrbit::Traits::IsValueType<zawa_ch::StationaryOrbit::Proportion16_t>);
static_assert(zawa_ch::StationaryOrbit::Traits::IsValueType<zawa_ch::StationaryOrbit::Proportion32_t>);
static_assert(zawa_ch::StationaryOrbit::Traits::IsValueType<zawa_ch::StationaryOrbit::Proportion64_t>);
// (int)からのコンストラクタを持つ
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::Proportion1_t, int>);
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::Proportion8_t, int>);
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::Proportion16_t, int>);
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::Proportion32_t, int>);
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::Proportion64_t, int>);
// (float)からのコンストラクタを持つ
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::Proportion1_t, float>);
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::Proportion8_t, float>);
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::Proportion16_t, float>);
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::Proportion32_t, float>);
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::Proportion64_t, float>);
// (double)からのコンストラクタを持つ
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::Proportion1_t, double>);
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::Proportion8_t, double>);
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::Proportion16_t, double>);
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::Proportion32_t, double>);
static_assert(std::is_constructible_v<zawa_ch::StationaryOrbit::Proportion64_t, double>);
// 基本的な算術演算子を持つ
static_assert(zawa_ch::StationaryOrbit::Traits::HasArithmeticOperation<zawa_ch::StationaryOrbit::Proportion1_t>);
static_assert(zawa_ch::StationaryOrbit::Traits::HasArithmeticOperation<zawa_ch::StationaryOrbit::Proportion8_t>);
static_assert(zawa_ch::StationaryOrbit::Traits::HasArithmeticOperation<zawa_ch::StationaryOrbit::Proportion16_t>);
static_assert(zawa_ch::StationaryOrbit::Traits::HasArithmeticOperation<zawa_ch::StationaryOrbit::Proportion32_t>);
static_assert(zawa_ch::StationaryOrbit::Traits::HasArithmeticOperation<zawa_ch::StationaryOrbit::Proportion64_t>);
