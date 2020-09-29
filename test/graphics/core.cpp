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
using namespace zawa_ch::StationaryOrbit;

void Test_Core()
{
	auto fbitmap1 = Graphics::BitmapF32(10, 10, 1);
	auto fbitmap2 = Graphics::BitmapConverter<float>::FripVertical(fbitmap1);
	auto fbitmap3 = Graphics::BitmapConverter<float>::FripHorizonal(fbitmap2);
	auto ibitmap = Graphics::Bitmap8(fbitmap1);
	auto rgbbitmap = Graphics::RGBBitmapImage(10, 10);
	auto graybitmap = rgbbitmap;
	graybitmap.Monotone();
	auto bbitmap1 = Graphics::BinaryBitmap(fbitmap1, (
		[](const Graphics::BitmapF32::ConstRefType & value) -> bool { return (value[0] > 0.5)?true:false; }
	));
	auto bbitmap2 = rgbbitmap.Binalize(
		[](const Graphics::RGBColor& color) -> bool { return ((color.R() > 0.5)&&(color.G() > 0.5)&&(color.B() > 0.5))?true:false; }
	);
}
