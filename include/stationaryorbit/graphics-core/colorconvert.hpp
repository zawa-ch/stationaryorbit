//	stationaryorbit/graphics-core/colorconvert
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
#ifndef __stationaryorbit_graphics_core_colorconvert__
#define __stationaryorbit_graphics_core_colorconvert__
#include "cmycolor.hpp"
#include "cmykcolor.hpp"
#include "grayscalecolor.hpp"
#include "rgbcolor.hpp"
#include "yuvcolor.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	class ColorConvert final
	{
		ColorConvert() = delete;
		~ColorConvert() = delete;
	public:
		template<class Tp>
		static constexpr GrayScaleColor<Tp> ToLuminanceFromSrgb(const RGBColor<Tp>& color)
		{
			static_assert(std::is_constructible_v<Tp, float>, "テンプレート型 Tp は(float)を引数に取るコンストラクタを持つ必要があります。");
			return GrayScaleColor<Tp>(color.R() * Tp(0.2989f) + color.G() * Tp(0.5866f) + color.B() * Tp(0.1144f));
		}
		template<class Tp>
		static constexpr RGBColor<Tp> ToRgbFromLuminance(const GrayScaleColor<Tp>& color)
		{
			return RGBColor<Tp>(RGBColor<Tp>::DataType::Expand(color.Luminance()));
		}
	};

	extern template GrayScale8_t ColorConvert::ToLuminanceFromSrgb(const RGB8_t& color);
	extern template GrayScale16_t ColorConvert::ToLuminanceFromSrgb(const RGB16_t& color);
	extern template GrayScale32_t ColorConvert::ToLuminanceFromSrgb(const RGB32_t& color);
	extern template GrayScale64_t ColorConvert::ToLuminanceFromSrgb(const RGB64_t& color);
	extern template GrayScaleI16_t ColorConvert::ToLuminanceFromSrgb(const RGBI16_t& color);
	extern template GrayScaleI32_t ColorConvert::ToLuminanceFromSrgb(const RGBI32_t& color);
	extern template GrayScaleI64_t ColorConvert::ToLuminanceFromSrgb(const RGBI64_t& color);
	extern template GrayScaleF32_t ColorConvert::ToLuminanceFromSrgb(const RGBF32_t& color);
	extern template GrayScaleF64_t ColorConvert::ToLuminanceFromSrgb(const RGBF64_t& color);
	extern template RGB8_t ColorConvert::ToRgbFromLuminance(const GrayScale8_t& color);
	extern template RGB16_t ColorConvert::ToRgbFromLuminance(const GrayScale16_t& color);
	extern template RGB32_t ColorConvert::ToRgbFromLuminance(const GrayScale32_t& color);
	extern template RGB64_t ColorConvert::ToRgbFromLuminance(const GrayScale64_t& color);
	extern template RGBI16_t ColorConvert::ToRgbFromLuminance(const GrayScaleI16_t& color);
	extern template RGBI32_t ColorConvert::ToRgbFromLuminance(const GrayScaleI32_t& color);
	extern template RGBI64_t ColorConvert::ToRgbFromLuminance(const GrayScaleI64_t& color);
	extern template RGBF32_t ColorConvert::ToRgbFromLuminance(const GrayScaleF32_t& color);
	extern template RGBF64_t ColorConvert::ToRgbFromLuminance(const GrayScaleF64_t& color);
}
#endif // __stationaryorbit_graphics_core_colorconvert__
