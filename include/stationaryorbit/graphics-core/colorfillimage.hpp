//	stationaryorbit/graphics-core/colorfillimage
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
#ifndef __stationaryorbit_graphics_core_colorfillimage__
#define __stationaryorbit_graphics_core_colorfillimage__
#include "fundamental.hpp"
#include "relativecolor.hpp"
#include "grayscalecolor.hpp"
#include "rgbcolor.hpp"
#include "cmycolor.hpp"
#include "cmykcolor.hpp"
#include "opacity.hpp"
#include "image.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	///	単色で塗りつぶされた @a Image を表します。
	///	@param	Tcolor
	///	色の表現に用いる型。
	template<class Tcolor>
	class ColorFillImage : public Image<Tcolor>
	{
	public:
		///	色の表現に用いる型。
		typedef Tcolor ValueType;
	private:
		ValueType color;
		DisplayRectangle area;
	public:
		///	既定の @a ColorFillImage を構築します。
		ColorFillImage() = default;
		ColorFillImage(const ValueType& color) : color(color), area() {}
		ColorFillImage(const ValueType& color, const DisplayRectangle& area) : color(color), area(area) {}

		[[nodiscard]] bool IsReadableAbyss() const noexcept { return true; }

		[[nodiscard]] const DisplayRectSize& Size() const noexcept { return area.Size(); }
		[[nodiscard]] DisplayRectangle Area() const noexcept { return area; }
		[[nodiscard]] ValueType At(const DisplayPoint& index) const { return color; }

		[[nodiscard]] ValueType operator[](const DisplayPoint& index) const { return color; }
	};

	extern template class ColorFillImage<Opacity8_t>;
	extern template class ColorFillImage<Opacity16_t>;
	extern template class ColorFillImage<Opacity32_t>;
	extern template class ColorFillImage<Opacity64_t>;
	extern template class ColorFillImage<OpacityI16_t>;
	extern template class ColorFillImage<OpacityI32_t>;
	extern template class ColorFillImage<OpacityI64_t>;
	extern template class ColorFillImage<OpacityF32_t>;
	extern template class ColorFillImage<OpacityF64_t>;
	extern template class ColorFillImage<GrayScale8_t>;
	extern template class ColorFillImage<GrayScale16_t>;
	extern template class ColorFillImage<GrayScale32_t>;
	extern template class ColorFillImage<GrayScale64_t>;
	extern template class ColorFillImage<GrayScaleI16_t>;
	extern template class ColorFillImage<GrayScaleI32_t>;
	extern template class ColorFillImage<GrayScaleI64_t>;
	extern template class ColorFillImage<GrayScaleF32_t>;
	extern template class ColorFillImage<GrayScaleF64_t>;
	extern template class ColorFillImage<RGB8_t>;
	extern template class ColorFillImage<RGB16_t>;
	extern template class ColorFillImage<RGB32_t>;
	extern template class ColorFillImage<RGB64_t>;
	extern template class ColorFillImage<RGBI16_t>;
	extern template class ColorFillImage<RGBI32_t>;
	extern template class ColorFillImage<RGBI64_t>;
	extern template class ColorFillImage<RGBF32_t>;
	extern template class ColorFillImage<RGBF64_t>;
	extern template class ColorFillImage<ARGB8_t>;
	extern template class ColorFillImage<ARGB16_t>;
	extern template class ColorFillImage<ARGB32_t>;
	extern template class ColorFillImage<ARGB64_t>;
	extern template class ColorFillImage<ARGBI16_t>;
	extern template class ColorFillImage<ARGBI32_t>;
	extern template class ColorFillImage<ARGBI64_t>;
	extern template class ColorFillImage<ARGBF32_t>;
	extern template class ColorFillImage<ARGBF64_t>;
	extern template class ColorFillImage<CMY8_t>;
	extern template class ColorFillImage<CMY16_t>;
	extern template class ColorFillImage<CMY32_t>;
	extern template class ColorFillImage<CMY64_t>;
	extern template class ColorFillImage<CMYI16_t>;
	extern template class ColorFillImage<CMYI32_t>;
	extern template class ColorFillImage<CMYI64_t>;
	extern template class ColorFillImage<CMYF32_t>;
	extern template class ColorFillImage<CMYF64_t>;
	extern template class ColorFillImage<ACMY8_t>;
	extern template class ColorFillImage<ACMY16_t>;
	extern template class ColorFillImage<ACMY32_t>;
	extern template class ColorFillImage<ACMY64_t>;
	extern template class ColorFillImage<ACMYI16_t>;
	extern template class ColorFillImage<ACMYI32_t>;
	extern template class ColorFillImage<ACMYI64_t>;
	extern template class ColorFillImage<ACMYF32_t>;
	extern template class ColorFillImage<ACMYF64_t>;
	extern template class ColorFillImage<CMYK8_t>;
	extern template class ColorFillImage<CMYK16_t>;
	extern template class ColorFillImage<CMYK32_t>;
	extern template class ColorFillImage<CMYK64_t>;
	extern template class ColorFillImage<CMYKI16_t>;
	extern template class ColorFillImage<CMYKI32_t>;
	extern template class ColorFillImage<CMYKI64_t>;
	extern template class ColorFillImage<CMYKF32_t>;
	extern template class ColorFillImage<CMYKF64_t>;
	extern template class ColorFillImage<ACMYK8_t>;
	extern template class ColorFillImage<ACMYK16_t>;
	extern template class ColorFillImage<ACMYK32_t>;
	extern template class ColorFillImage<ACMYK64_t>;
	extern template class ColorFillImage<ACMYKI16_t>;
	extern template class ColorFillImage<ACMYKI32_t>;
	extern template class ColorFillImage<ACMYKI64_t>;
	extern template class ColorFillImage<ACMYKF32_t>;
	extern template class ColorFillImage<ACMYKF64_t>;
}
#endif // __stationaryorbit_graphics_core_colorfillimage__
