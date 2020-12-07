//	stationaryorbit.graphics-core:/cmykcolor
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
#include "stationaryorbit/graphics-core/cmykcolor.hpp"

template struct
zawa_ch::StationaryOrbit::Graphics::CMYKColor<zawa_ch::StationaryOrbit::Proportion8_t>;
template struct
zawa_ch::StationaryOrbit::Graphics::CMYKColor<zawa_ch::StationaryOrbit::Proportion16_t>;
template struct
zawa_ch::StationaryOrbit::Graphics::CMYKColor<zawa_ch::StationaryOrbit::Proportion32_t>;
template struct
zawa_ch::StationaryOrbit::Graphics::CMYKColor<zawa_ch::StationaryOrbit::Proportion64_t>;
template struct
zawa_ch::StationaryOrbit::Graphics::CMYKColor<zawa_ch::StationaryOrbit::FixedPoint16q15_t>;
template struct
zawa_ch::StationaryOrbit::Graphics::CMYKColor<zawa_ch::StationaryOrbit::FixedPoint32q31_t>;
template struct
zawa_ch::StationaryOrbit::Graphics::CMYKColor<zawa_ch::StationaryOrbit::FixedPoint64q63_t>;
template struct
zawa_ch::StationaryOrbit::Graphics::CMYKColor<float>;
template struct
zawa_ch::StationaryOrbit::Graphics::CMYKColor<double>;
template struct
zawa_ch::StationaryOrbit::Graphics::TranslucentColor<zawa_ch::StationaryOrbit::Graphics::CMYKColor<zawa_ch::StationaryOrbit::Proportion8_t>>;
template struct
zawa_ch::StationaryOrbit::Graphics::TranslucentColor<zawa_ch::StationaryOrbit::Graphics::CMYKColor<zawa_ch::StationaryOrbit::Proportion16_t>>;
template struct
zawa_ch::StationaryOrbit::Graphics::TranslucentColor<zawa_ch::StationaryOrbit::Graphics::CMYKColor<zawa_ch::StationaryOrbit::Proportion32_t>>;
template struct
zawa_ch::StationaryOrbit::Graphics::TranslucentColor<zawa_ch::StationaryOrbit::Graphics::CMYKColor<zawa_ch::StationaryOrbit::Proportion64_t>>;
template struct
zawa_ch::StationaryOrbit::Graphics::TranslucentColor<zawa_ch::StationaryOrbit::Graphics::CMYKColor<zawa_ch::StationaryOrbit::FixedPoint16q15_t>>;
template struct
zawa_ch::StationaryOrbit::Graphics::TranslucentColor<zawa_ch::StationaryOrbit::Graphics::CMYKColor<zawa_ch::StationaryOrbit::FixedPoint32q31_t>>;
template struct
zawa_ch::StationaryOrbit::Graphics::TranslucentColor<zawa_ch::StationaryOrbit::Graphics::CMYKColor<zawa_ch::StationaryOrbit::FixedPoint64q63_t>>;
template struct
zawa_ch::StationaryOrbit::Graphics::TranslucentColor<zawa_ch::StationaryOrbit::Graphics::CMYKColor<float>>;
template struct
zawa_ch::StationaryOrbit::Graphics::TranslucentColor<zawa_ch::StationaryOrbit::Graphics::CMYKColor<double>>;

// CMYKColorの型要件
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsCMYKColorType<zawa_ch::StationaryOrbit::Graphics::CMYK8_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsCMYKColorType<zawa_ch::StationaryOrbit::Graphics::CMYK16_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsCMYKColorType<zawa_ch::StationaryOrbit::Graphics::CMYK32_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsCMYKColorType<zawa_ch::StationaryOrbit::Graphics::CMYK64_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsCMYKColorType<zawa_ch::StationaryOrbit::Graphics::CMYKI16_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsCMYKColorType<zawa_ch::StationaryOrbit::Graphics::CMYKI32_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsCMYKColorType<zawa_ch::StationaryOrbit::Graphics::CMYKI64_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsCMYKColorType<zawa_ch::StationaryOrbit::Graphics::CMYKF32_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsCMYKColorType<zawa_ch::StationaryOrbit::Graphics::CMYKF64_t>);
// ACMYKColorの型要件
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsTranslucentColorType<zawa_ch::StationaryOrbit::Graphics::ACMYK8_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsTranslucentColorType<zawa_ch::StationaryOrbit::Graphics::ACMYK16_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsTranslucentColorType<zawa_ch::StationaryOrbit::Graphics::ACMYK32_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsTranslucentColorType<zawa_ch::StationaryOrbit::Graphics::ACMYK64_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsTranslucentColorType<zawa_ch::StationaryOrbit::Graphics::ACMYKI16_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsTranslucentColorType<zawa_ch::StationaryOrbit::Graphics::ACMYKI32_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsTranslucentColorType<zawa_ch::StationaryOrbit::Graphics::ACMYKI64_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsTranslucentColorType<zawa_ch::StationaryOrbit::Graphics::ACMYKF32_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsTranslucentColorType<zawa_ch::StationaryOrbit::Graphics::ACMYKF64_t>);
