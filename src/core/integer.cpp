//	stationaryorbit.core:/integer
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
#include "stationaryorbit/core/integer.hpp"
using namespace zawa_ch::StationaryOrbit;

template struct zawa_ch::StationaryOrbit::Integer<std::byte>;
template struct zawa_ch::StationaryOrbit::Integer<uint8_t>;
template struct zawa_ch::StationaryOrbit::Integer<uint16_t>;
template struct zawa_ch::StationaryOrbit::Integer<uint32_t>;
template struct zawa_ch::StationaryOrbit::Integer<uint64_t>;

template zawa_ch::StationaryOrbit::Integer<std::byte>::Integer(const uint8_t&);
template zawa_ch::StationaryOrbit::Integer<std::byte>::Integer(const uint16_t&);
template zawa_ch::StationaryOrbit::Integer<std::byte>::Integer(const uint32_t&);
template zawa_ch::StationaryOrbit::Integer<std::byte>::Integer(const uint64_t&);
template zawa_ch::StationaryOrbit::Integer<uint8_t>::Integer(const uint8_t&);
template zawa_ch::StationaryOrbit::Integer<uint8_t>::Integer(const uint16_t&);
template zawa_ch::StationaryOrbit::Integer<uint8_t>::Integer(const uint32_t&);
template zawa_ch::StationaryOrbit::Integer<uint8_t>::Integer(const uint64_t&);
template zawa_ch::StationaryOrbit::Integer<uint16_t>::Integer(const uint8_t&);
template zawa_ch::StationaryOrbit::Integer<uint16_t>::Integer(const uint16_t&);
template zawa_ch::StationaryOrbit::Integer<uint16_t>::Integer(const uint32_t&);
template zawa_ch::StationaryOrbit::Integer<uint16_t>::Integer(const uint64_t&);
template zawa_ch::StationaryOrbit::Integer<uint32_t>::Integer(const uint8_t&);
template zawa_ch::StationaryOrbit::Integer<uint32_t>::Integer(const uint16_t&);
template zawa_ch::StationaryOrbit::Integer<uint32_t>::Integer(const uint32_t&);
template zawa_ch::StationaryOrbit::Integer<uint32_t>::Integer(const uint64_t&);
template zawa_ch::StationaryOrbit::Integer<uint64_t>::Integer(const uint8_t&);
template zawa_ch::StationaryOrbit::Integer<uint64_t>::Integer(const uint16_t&);
template zawa_ch::StationaryOrbit::Integer<uint64_t>::Integer(const uint32_t&);
template zawa_ch::StationaryOrbit::Integer<uint64_t>::Integer(const uint64_t&);

template struct zawa_ch::StationaryOrbit::SignedInteger<std::byte>;
template struct zawa_ch::StationaryOrbit::SignedInteger<uint8_t>;
template struct zawa_ch::StationaryOrbit::SignedInteger<uint16_t>;
template struct zawa_ch::StationaryOrbit::SignedInteger<uint32_t>;
template struct zawa_ch::StationaryOrbit::SignedInteger<uint64_t>;

template zawa_ch::StationaryOrbit::SignedInteger<std::byte>::SignedInteger(const int8_t&);
template zawa_ch::StationaryOrbit::SignedInteger<std::byte>::SignedInteger(const int16_t&);
template zawa_ch::StationaryOrbit::SignedInteger<std::byte>::SignedInteger(const int32_t&);
template zawa_ch::StationaryOrbit::SignedInteger<std::byte>::SignedInteger(const int64_t&);
template zawa_ch::StationaryOrbit::SignedInteger<uint8_t>::SignedInteger(const int8_t&);
template zawa_ch::StationaryOrbit::SignedInteger<uint8_t>::SignedInteger(const int16_t&);
template zawa_ch::StationaryOrbit::SignedInteger<uint8_t>::SignedInteger(const int32_t&);
template zawa_ch::StationaryOrbit::SignedInteger<uint8_t>::SignedInteger(const int64_t&);
template zawa_ch::StationaryOrbit::SignedInteger<uint16_t>::SignedInteger(const int8_t&);
template zawa_ch::StationaryOrbit::SignedInteger<uint16_t>::SignedInteger(const int16_t&);
template zawa_ch::StationaryOrbit::SignedInteger<uint16_t>::SignedInteger(const int32_t&);
template zawa_ch::StationaryOrbit::SignedInteger<uint16_t>::SignedInteger(const int64_t&);
template zawa_ch::StationaryOrbit::SignedInteger<uint32_t>::SignedInteger(const int8_t&);
template zawa_ch::StationaryOrbit::SignedInteger<uint32_t>::SignedInteger(const int16_t&);
template zawa_ch::StationaryOrbit::SignedInteger<uint32_t>::SignedInteger(const int32_t&);
template zawa_ch::StationaryOrbit::SignedInteger<uint32_t>::SignedInteger(const int64_t&);
template zawa_ch::StationaryOrbit::SignedInteger<uint64_t>::SignedInteger(const int8_t&);
template zawa_ch::StationaryOrbit::SignedInteger<uint64_t>::SignedInteger(const int16_t&);
template zawa_ch::StationaryOrbit::SignedInteger<uint64_t>::SignedInteger(const int32_t&);
template zawa_ch::StationaryOrbit::SignedInteger<uint64_t>::SignedInteger(const int64_t&);

static_assert(Traits::IsIntegralType<Integer<std::byte>>, "Integer<std::byte> は整数型ですが、型特性検査結果は false でした。");
static_assert(Traits::IsIntegralType<Integer<uint8_t>>, "Integer<uint8_t> は整数型ですが、型特性検査結果は false でした。");
static_assert(Traits::IsIntegralType<Integer<uint16_t>>, "Integer<uint16_t> は整数型ですが、型特性検査結果は false でした。");
static_assert(Traits::IsIntegralType<Integer<uint32_t>>, "Integer<uint32_t> は整数型ですが、型特性検査結果は false でした。");
static_assert(Traits::IsIntegralType<Integer<uint64_t>>, "Integer<uint64_t> は整数型ですが、型特性検査結果は false でした。");

static_assert(Traits::IsIntegralType<SignedInteger<std::byte>>, "SignedInteger<std::byte> は整数型ですが、型特性検査結果は false でした。");
static_assert(Traits::IsIntegralType<SignedInteger<uint8_t>>, "SignedInteger<uint8_t> は整数型ですが、型特性検査結果は false でした。");
static_assert(Traits::IsIntegralType<SignedInteger<uint16_t>>, "SignedInteger<uint16_t> は整数型ですが、型特性検査結果は false でした。");
static_assert(Traits::IsIntegralType<SignedInteger<uint32_t>>, "SignedInteger<uint32_t> は整数型ですが、型特性検査結果は false でした。");
static_assert(Traits::IsIntegralType<SignedInteger<uint64_t>>, "SignedInteger<uint64_t> は整数型ですが、型特性検査結果は false でした。");
