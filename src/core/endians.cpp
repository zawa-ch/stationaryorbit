//	stationaryorbit.core:/endians
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
#include "stationaryorbit/core/endians.hpp"
using namespace zawa_ch::StationaryOrbit;

template struct
zawa_ch::StationaryOrbit::EndianValueType<uint8_t, zawa_ch::StationaryOrbit::Endians::big>;
template struct
zawa_ch::StationaryOrbit::EndianValueType<uint16_t, zawa_ch::StationaryOrbit::Endians::big>;
template struct
zawa_ch::StationaryOrbit::EndianValueType<uint32_t, zawa_ch::StationaryOrbit::Endians::big>;
template struct
zawa_ch::StationaryOrbit::EndianValueType<uint64_t, zawa_ch::StationaryOrbit::Endians::big>;
template struct
zawa_ch::StationaryOrbit::EndianValueType<float, zawa_ch::StationaryOrbit::Endians::big>;
template struct
zawa_ch::StationaryOrbit::EndianValueType<double, zawa_ch::StationaryOrbit::Endians::big>;
template struct
zawa_ch::StationaryOrbit::EndianValueType<uint8_t, zawa_ch::StationaryOrbit::Endians::little>;
template struct
zawa_ch::StationaryOrbit::EndianValueType<uint16_t, zawa_ch::StationaryOrbit::Endians::little>;
template struct
zawa_ch::StationaryOrbit::EndianValueType<uint32_t, zawa_ch::StationaryOrbit::Endians::little>;
template struct
zawa_ch::StationaryOrbit::EndianValueType<uint64_t, zawa_ch::StationaryOrbit::Endians::little>;
template struct
zawa_ch::StationaryOrbit::EndianValueType<float, zawa_ch::StationaryOrbit::Endians::little>;
template struct
zawa_ch::StationaryOrbit::EndianValueType<double, zawa_ch::StationaryOrbit::Endians::little>;

static_assert(sizeof(zawa_ch::StationaryOrbit::uint8be_t) == sizeof(uint8_t), "EndianValueType<uint8_t, Endians::big> の型サイズが元の型のサイズと一致しません。");
static_assert(sizeof(zawa_ch::StationaryOrbit::uint16be_t) == sizeof(uint16_t), "EndianValueType<uint16_t, Endians::big> の型サイズが元の型のサイズと一致しません。");
static_assert(sizeof(zawa_ch::StationaryOrbit::uint32be_t) == sizeof(uint32_t), "EndianValueType<uint32_t, Endians::big> の型サイズが元の型のサイズと一致しません。");
static_assert(sizeof(zawa_ch::StationaryOrbit::uint64be_t) == sizeof(uint64_t), "EndianValueType<uint64_t, Endians::big> の型サイズが元の型のサイズと一致しません。");
static_assert(sizeof(zawa_ch::StationaryOrbit::float32be_t) == sizeof(float), "EndianValueType<float, Endians::big> の型サイズが元の型のサイズと一致しません。");
static_assert(sizeof(zawa_ch::StationaryOrbit::float64be_t) == sizeof(double), "EndianValueType<double, Endians::big> の型サイズが元の型のサイズと一致しません。");

static_assert(sizeof(zawa_ch::StationaryOrbit::uint8le_t) == sizeof(uint8_t), "EndianValueType<uint8_t, Endians::little> の型サイズが元の型のサイズと一致しません。");
static_assert(sizeof(zawa_ch::StationaryOrbit::uint16le_t) == sizeof(uint16_t), "EndianValueType<uint16_t, Endians::little> の型サイズが元の型のサイズと一致しません。");
static_assert(sizeof(zawa_ch::StationaryOrbit::uint32le_t) == sizeof(uint32_t), "EndianValueType<uint32_t, Endians::little> の型サイズが元の型のサイズと一致しません。");
static_assert(sizeof(zawa_ch::StationaryOrbit::uint64le_t) == sizeof(uint64_t), "EndianValueType<uint64_t, Endians::little> の型サイズが元の型のサイズと一致しません。");
static_assert(sizeof(zawa_ch::StationaryOrbit::float32le_t) == sizeof(float), "EndianValueType<float, Endians::little> の型サイズが元の型のサイズと一致しません。");
static_assert(sizeof(zawa_ch::StationaryOrbit::float64le_t) == sizeof(double), "EndianValueType<double, Endians::little> の型サイズが元の型のサイズと一致しません。");

static_assert(alignof(zawa_ch::StationaryOrbit::uint8be_t) == alignof(uint8_t), "EndianValueType<uint8_t, Endians::big> の型アライメントが元の型のアライメントと一致しません。");
static_assert(alignof(zawa_ch::StationaryOrbit::uint16be_t) == alignof(uint16_t), "EndianValueType<uint16_t, Endians::big> の型アライメントが元の型のアライメントと一致しません。");
static_assert(alignof(zawa_ch::StationaryOrbit::uint32be_t) == alignof(uint32_t), "EndianValueType<uint32_t, Endians::big> の型アライメントが元の型のアライメントと一致しません。");
static_assert(alignof(zawa_ch::StationaryOrbit::uint64be_t) == alignof(uint64_t), "EndianValueType<uint64_t, Endians::big> の型アライメントが元の型のアライメントと一致しません。");
static_assert(alignof(zawa_ch::StationaryOrbit::float32be_t) == alignof(float), "EndianValueType<float, Endians::big> の型アライメントが元の型のアライメントと一致しません。");
static_assert(alignof(zawa_ch::StationaryOrbit::float64be_t) == alignof(double), "EndianValueType<double, Endians::big> の型アライメントが元の型のアライメントと一致しません。");

static_assert(alignof(zawa_ch::StationaryOrbit::uint8le_t) == alignof(uint8_t), "EndianValueType<uint8_t, Endians::little> の型アライメントが元の型のアライメントと一致しません。");
static_assert(alignof(zawa_ch::StationaryOrbit::uint16le_t) == alignof(uint16_t), "EndianValueType<uint16_t, Endians::little> の型アライメントが元の型のアライメントと一致しません。");
static_assert(alignof(zawa_ch::StationaryOrbit::uint32le_t) == alignof(uint32_t), "EndianValueType<uint32_t, Endians::little> の型アライメントが元の型のアライメントと一致しません。");
static_assert(alignof(zawa_ch::StationaryOrbit::uint64le_t) == alignof(uint64_t), "EndianValueType<uint64_t, Endians::little> の型アライメントが元の型のアライメントと一致しません。");
static_assert(alignof(zawa_ch::StationaryOrbit::float32le_t) == alignof(float), "EndianValueType<float, Endians::little> の型アライメントが元の型のアライメントと一致しません。");
static_assert(alignof(zawa_ch::StationaryOrbit::float64le_t) == alignof(double), "EndianValueType<double, Endians::little> の型アライメントが元の型のアライメントと一致しません。");
