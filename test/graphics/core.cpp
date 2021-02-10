//	stationaryorbit.test.graphics:/core
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
#include "stationaryorbit/graphics-core.color.hpp"
#include "stationaryorbit/graphics-core.image.hpp"
#include "stationaryorbit/graphics-core.deformation.hpp"
using namespace zawa_ch::StationaryOrbit;

void Test_Core()
{
	auto i1 = Graphics::RGBF32Pixmap_t(10, 10);
	auto i1_hflip = Graphics::ImageHorizonalFlip(i1);
	auto i1_vflip = Graphics::ImageVerticalFlip(i1);
	auto i2 = Graphics::RGBF32Pixmap_t(i1_hflip, i1_hflip.Area());
	auto i3 = Graphics::RGBF32Pixmap_t(i1_vflip, i1_vflip.Area());
	auto i4 = Graphics::RGB8Pixmap_t(i1);
	auto i5 = Graphics::GrayF32Pixmap_t::Convert<Graphics::RGBF32_t>(i1, [](const auto& i) { return Graphics::ColorConvert::ToLuminanceFromSrgb(i); });
	auto i6 = Graphics::Mask1Pixmap_t::Convert<Graphics::RGBF32_t>(i1, 
		[](const auto& i) {return Graphics::Opacity1_t(Proportion1_t(i.R() > 0.5)); }
	);
	auto i7 = Graphics::Mask1Pixmap_t::Convert<Graphics::RGBF32_t>(i1, 
		[](const auto& i) {return Graphics::Opacity1_t(Proportion1_t((i.R() > 0.5)&&(i.G() > 0.5)&&(i.B() > 0.5))); }
	);
}
