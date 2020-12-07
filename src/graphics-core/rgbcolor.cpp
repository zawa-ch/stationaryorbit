//	stationaryorbit.graphics-core:/rgbcolor
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
#include "stationaryorbit/graphics-core/rgbcolor.hpp"

template struct
zawa_ch::StationaryOrbit::Graphics::RGBColor<zawa_ch::StationaryOrbit::Proportion8_t>;
template struct
zawa_ch::StationaryOrbit::Graphics::RGBColor<zawa_ch::StationaryOrbit::Proportion16_t>;
template struct
zawa_ch::StationaryOrbit::Graphics::RGBColor<zawa_ch::StationaryOrbit::Proportion32_t>;
template struct
zawa_ch::StationaryOrbit::Graphics::RGBColor<zawa_ch::StationaryOrbit::Proportion64_t>;
template struct
zawa_ch::StationaryOrbit::Graphics::RGBColor<zawa_ch::StationaryOrbit::FixedPoint16q15_t>;
template struct
zawa_ch::StationaryOrbit::Graphics::RGBColor<zawa_ch::StationaryOrbit::FixedPoint32q31_t>;
template struct
zawa_ch::StationaryOrbit::Graphics::RGBColor<zawa_ch::StationaryOrbit::FixedPoint64q63_t>;
template struct
zawa_ch::StationaryOrbit::Graphics::RGBColor<float>;
template struct
zawa_ch::StationaryOrbit::Graphics::RGBColor<double>;
template struct
zawa_ch::StationaryOrbit::Graphics::TranslucentColor<zawa_ch::StationaryOrbit::Graphics::RGBColor<zawa_ch::StationaryOrbit::Proportion8_t>>;
template struct
zawa_ch::StationaryOrbit::Graphics::TranslucentColor<zawa_ch::StationaryOrbit::Graphics::RGBColor<zawa_ch::StationaryOrbit::Proportion16_t>>;
template struct
zawa_ch::StationaryOrbit::Graphics::TranslucentColor<zawa_ch::StationaryOrbit::Graphics::RGBColor<zawa_ch::StationaryOrbit::Proportion32_t>>;
template struct
zawa_ch::StationaryOrbit::Graphics::TranslucentColor<zawa_ch::StationaryOrbit::Graphics::RGBColor<zawa_ch::StationaryOrbit::Proportion64_t>>;
template struct
zawa_ch::StationaryOrbit::Graphics::TranslucentColor<zawa_ch::StationaryOrbit::Graphics::RGBColor<zawa_ch::StationaryOrbit::FixedPoint16q15_t>>;
template struct
zawa_ch::StationaryOrbit::Graphics::TranslucentColor<zawa_ch::StationaryOrbit::Graphics::RGBColor<zawa_ch::StationaryOrbit::FixedPoint32q31_t>>;
template struct
zawa_ch::StationaryOrbit::Graphics::TranslucentColor<zawa_ch::StationaryOrbit::Graphics::RGBColor<zawa_ch::StationaryOrbit::FixedPoint64q63_t>>;
template struct
zawa_ch::StationaryOrbit::Graphics::TranslucentColor<zawa_ch::StationaryOrbit::Graphics::RGBColor<float>>;
template struct
zawa_ch::StationaryOrbit::Graphics::TranslucentColor<zawa_ch::StationaryOrbit::Graphics::RGBColor<double>>;

// RGBColorの型要件
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsColorType<zawa_ch::StationaryOrbit::Graphics::RGB8_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsColorType<zawa_ch::StationaryOrbit::Graphics::RGB16_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsColorType<zawa_ch::StationaryOrbit::Graphics::RGB32_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsColorType<zawa_ch::StationaryOrbit::Graphics::RGB64_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsColorType<zawa_ch::StationaryOrbit::Graphics::RGBI16_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsColorType<zawa_ch::StationaryOrbit::Graphics::RGBI32_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsColorType<zawa_ch::StationaryOrbit::Graphics::RGBI64_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsColorType<zawa_ch::StationaryOrbit::Graphics::RGBF32_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsColorType<zawa_ch::StationaryOrbit::Graphics::RGBF64_t>);
// ARGBColorの型要件
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsTranslucentColorType<zawa_ch::StationaryOrbit::Graphics::ARGB8_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsTranslucentColorType<zawa_ch::StationaryOrbit::Graphics::ARGB16_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsTranslucentColorType<zawa_ch::StationaryOrbit::Graphics::ARGB32_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsTranslucentColorType<zawa_ch::StationaryOrbit::Graphics::ARGB64_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsTranslucentColorType<zawa_ch::StationaryOrbit::Graphics::ARGBI16_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsTranslucentColorType<zawa_ch::StationaryOrbit::Graphics::ARGBI32_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsTranslucentColorType<zawa_ch::StationaryOrbit::Graphics::ARGBI64_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsTranslucentColorType<zawa_ch::StationaryOrbit::Graphics::ARGBF32_t>);
static_assert(zawa_ch::StationaryOrbit::Graphics::ColorTraits::IsTranslucentColorType<zawa_ch::StationaryOrbit::Graphics::ARGBF64_t>);
