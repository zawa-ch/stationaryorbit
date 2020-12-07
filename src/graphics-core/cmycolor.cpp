//	stationaryorbit.graphics-core:/cmycolor
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
#include "stationaryorbit/graphics-core/cmycolor.hpp"

template struct
zawa_ch::StationaryOrbit::Graphics::CMYColor<zawa_ch::StationaryOrbit::Proportion8_t>;
template struct
zawa_ch::StationaryOrbit::Graphics::CMYColor<zawa_ch::StationaryOrbit::Proportion16_t>;
template struct
zawa_ch::StationaryOrbit::Graphics::CMYColor<zawa_ch::StationaryOrbit::Proportion32_t>;
template struct
zawa_ch::StationaryOrbit::Graphics::CMYColor<zawa_ch::StationaryOrbit::Proportion64_t>;
template struct
zawa_ch::StationaryOrbit::Graphics::CMYColor<zawa_ch::StationaryOrbit::FixedPoint16q15_t>;
template struct
zawa_ch::StationaryOrbit::Graphics::CMYColor<zawa_ch::StationaryOrbit::FixedPoint32q31_t>;
template struct
zawa_ch::StationaryOrbit::Graphics::CMYColor<zawa_ch::StationaryOrbit::FixedPoint64q63_t>;
template struct
zawa_ch::StationaryOrbit::Graphics::CMYColor<float>;
template struct
zawa_ch::StationaryOrbit::Graphics::CMYColor<double>;
template struct
zawa_ch::StationaryOrbit::Graphics::TranslucentColor<zawa_ch::StationaryOrbit::Graphics::CMYColor<zawa_ch::StationaryOrbit::Proportion8_t>>;
template struct
zawa_ch::StationaryOrbit::Graphics::TranslucentColor<zawa_ch::StationaryOrbit::Graphics::CMYColor<zawa_ch::StationaryOrbit::Proportion16_t>>;
template struct
zawa_ch::StationaryOrbit::Graphics::TranslucentColor<zawa_ch::StationaryOrbit::Graphics::CMYColor<zawa_ch::StationaryOrbit::Proportion32_t>>;
template struct
zawa_ch::StationaryOrbit::Graphics::TranslucentColor<zawa_ch::StationaryOrbit::Graphics::CMYColor<zawa_ch::StationaryOrbit::Proportion64_t>>;
template struct
zawa_ch::StationaryOrbit::Graphics::TranslucentColor<zawa_ch::StationaryOrbit::Graphics::CMYColor<zawa_ch::StationaryOrbit::FixedPoint16q15_t>>;
template struct
zawa_ch::StationaryOrbit::Graphics::TranslucentColor<zawa_ch::StationaryOrbit::Graphics::CMYColor<zawa_ch::StationaryOrbit::FixedPoint32q31_t>>;
template struct
zawa_ch::StationaryOrbit::Graphics::TranslucentColor<zawa_ch::StationaryOrbit::Graphics::CMYColor<zawa_ch::StationaryOrbit::FixedPoint64q63_t>>;
template struct
zawa_ch::StationaryOrbit::Graphics::TranslucentColor<zawa_ch::StationaryOrbit::Graphics::CMYColor<float>>;
template struct
zawa_ch::StationaryOrbit::Graphics::TranslucentColor<zawa_ch::StationaryOrbit::Graphics::CMYColor<double>>;

// CMYColorの型要件
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsCMYColorType<zawa_ch::StationaryOrbit::Graphics::CMY8_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsCMYColorType<zawa_ch::StationaryOrbit::Graphics::CMY16_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsCMYColorType<zawa_ch::StationaryOrbit::Graphics::CMY32_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsCMYColorType<zawa_ch::StationaryOrbit::Graphics::CMY64_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsCMYColorType<zawa_ch::StationaryOrbit::Graphics::CMYI16_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsCMYColorType<zawa_ch::StationaryOrbit::Graphics::CMYI32_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsCMYColorType<zawa_ch::StationaryOrbit::Graphics::CMYI64_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsCMYColorType<zawa_ch::StationaryOrbit::Graphics::CMYF32_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsCMYColorType<zawa_ch::StationaryOrbit::Graphics::CMYF64_t>);
// ACMYColorの型要件
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsTranslucentColorType<zawa_ch::StationaryOrbit::Graphics::ACMY8_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsTranslucentColorType<zawa_ch::StationaryOrbit::Graphics::ACMY16_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsTranslucentColorType<zawa_ch::StationaryOrbit::Graphics::ACMY32_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsTranslucentColorType<zawa_ch::StationaryOrbit::Graphics::ACMY64_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsTranslucentColorType<zawa_ch::StationaryOrbit::Graphics::ACMYI16_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsTranslucentColorType<zawa_ch::StationaryOrbit::Graphics::ACMYI32_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsTranslucentColorType<zawa_ch::StationaryOrbit::Graphics::ACMYI64_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsTranslucentColorType<zawa_ch::StationaryOrbit::Graphics::ACMYF32_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsTranslucentColorType<zawa_ch::StationaryOrbit::Graphics::ACMYF64_t>);
