//	stationaryorbit/graphics-core/deformation
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
#ifndef __stationaryorbit_graphics_core_deformation__
#define __stationaryorbit_graphics_core_deformation__
#include "image.hpp"
#include "cmycolor.hpp"
#include "cmykcolor.hpp"
#include "grayscalecolor.hpp"
#include "rgbcolor.hpp"
#include "yuvcolor.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	template<class Tcolor>
	class ImageHorizonalFlip : public Image<Tcolor>
	{
	public:
		typedef Tcolor ValueType;
	private:
		const Image<Tcolor>& _data;
		DisplayPoint _orig;
	public:
		ImageHorizonalFlip(const Image<Tcolor>& source) : _data(source), _orig(-_data.Area().Right(), _data.Area().Top()) {}

		[[nodiscard]] virtual const RectangleSize& Size() const noexcept { return _data.Size(); }
		[[nodiscard]] virtual DisplayRectangle Area() const noexcept { return DisplayRectangle(_orig, _data.Size()); }
		[[nodiscard]] virtual ValueType At(const DisplayPoint& index) const { return _data.At(DisplayPoint(-index.X(), index.Y())); }

		[[nodiscard]] virtual ValueType operator[](const DisplayPoint& index) const { return _data[DisplayPoint(-index.X(), index.Y())]; }
	};

	extern template class ImageHorizonalFlip<CMY8_t>;
	extern template class ImageHorizonalFlip<CMY16_t>;
	extern template class ImageHorizonalFlip<CMY32_t>;
	extern template class ImageHorizonalFlip<CMY64_t>;
	extern template class ImageHorizonalFlip<CMYI16_t>;
	extern template class ImageHorizonalFlip<CMYI32_t>;
	extern template class ImageHorizonalFlip<CMYI64_t>;
	extern template class ImageHorizonalFlip<CMYF32_t>;
	extern template class ImageHorizonalFlip<CMYF64_t>;
	extern template class ImageHorizonalFlip<ACMY8_t>;
	extern template class ImageHorizonalFlip<ACMY16_t>;
	extern template class ImageHorizonalFlip<ACMY32_t>;
	extern template class ImageHorizonalFlip<ACMY64_t>;
	extern template class ImageHorizonalFlip<ACMYI16_t>;
	extern template class ImageHorizonalFlip<ACMYI32_t>;
	extern template class ImageHorizonalFlip<ACMYI64_t>;
	extern template class ImageHorizonalFlip<ACMYF32_t>;
	extern template class ImageHorizonalFlip<ACMYF64_t>;
	extern template class ImageHorizonalFlip<CMYK8_t>;
	extern template class ImageHorizonalFlip<CMYK16_t>;
	extern template class ImageHorizonalFlip<CMYK32_t>;
	extern template class ImageHorizonalFlip<CMYK64_t>;
	extern template class ImageHorizonalFlip<CMYKI16_t>;
	extern template class ImageHorizonalFlip<CMYKI32_t>;
	extern template class ImageHorizonalFlip<CMYKI64_t>;
	extern template class ImageHorizonalFlip<CMYKF32_t>;
	extern template class ImageHorizonalFlip<CMYKF64_t>;
	extern template class ImageHorizonalFlip<ACMYK8_t>;
	extern template class ImageHorizonalFlip<ACMYK16_t>;
	extern template class ImageHorizonalFlip<ACMYK32_t>;
	extern template class ImageHorizonalFlip<ACMYK64_t>;
	extern template class ImageHorizonalFlip<ACMYKI16_t>;
	extern template class ImageHorizonalFlip<ACMYKI32_t>;
	extern template class ImageHorizonalFlip<ACMYKI64_t>;
	extern template class ImageHorizonalFlip<ACMYKF32_t>;
	extern template class ImageHorizonalFlip<ACMYKF64_t>;
	extern template class ImageHorizonalFlip<GrayScale1_t>;
	extern template class ImageHorizonalFlip<GrayScale8_t>;
	extern template class ImageHorizonalFlip<GrayScale16_t>;
	extern template class ImageHorizonalFlip<GrayScale32_t>;
	extern template class ImageHorizonalFlip<GrayScale64_t>;
	extern template class ImageHorizonalFlip<GrayScaleI16_t>;
	extern template class ImageHorizonalFlip<GrayScaleI32_t>;
	extern template class ImageHorizonalFlip<GrayScaleI64_t>;
	extern template class ImageHorizonalFlip<GrayScaleF32_t>;
	extern template class ImageHorizonalFlip<GrayScaleF64_t>;
	extern template class ImageHorizonalFlip<RGB8_t>;
	extern template class ImageHorizonalFlip<RGB16_t>;
	extern template class ImageHorizonalFlip<RGB32_t>;
	extern template class ImageHorizonalFlip<RGB64_t>;
	extern template class ImageHorizonalFlip<RGBI16_t>;
	extern template class ImageHorizonalFlip<RGBI32_t>;
	extern template class ImageHorizonalFlip<RGBI64_t>;
	extern template class ImageHorizonalFlip<RGBF32_t>;
	extern template class ImageHorizonalFlip<RGBF64_t>;
	extern template class ImageHorizonalFlip<ARGB8_t>;
	extern template class ImageHorizonalFlip<ARGB16_t>;
	extern template class ImageHorizonalFlip<ARGB32_t>;
	extern template class ImageHorizonalFlip<ARGB64_t>;
	extern template class ImageHorizonalFlip<ARGBI16_t>;
	extern template class ImageHorizonalFlip<ARGBI32_t>;
	extern template class ImageHorizonalFlip<ARGBI64_t>;
	extern template class ImageHorizonalFlip<ARGBF32_t>;
	extern template class ImageHorizonalFlip<ARGBF64_t>;
	extern template class ImageHorizonalFlip<YUV8_t>;
	extern template class ImageHorizonalFlip<YUV16_t>;
	extern template class ImageHorizonalFlip<YUV32_t>;
	extern template class ImageHorizonalFlip<YUV64_t>;
	extern template class ImageHorizonalFlip<YUVI16_t>;
	extern template class ImageHorizonalFlip<YUVI32_t>;
	extern template class ImageHorizonalFlip<YUVI64_t>;
	extern template class ImageHorizonalFlip<YUVF32_t>;
	extern template class ImageHorizonalFlip<YUVF64_t>;
	extern template class ImageHorizonalFlip<AYUV8_t>;
	extern template class ImageHorizonalFlip<AYUV16_t>;
	extern template class ImageHorizonalFlip<AYUV32_t>;
	extern template class ImageHorizonalFlip<AYUV64_t>;
	extern template class ImageHorizonalFlip<AYUVI16_t>;
	extern template class ImageHorizonalFlip<AYUVI32_t>;
	extern template class ImageHorizonalFlip<AYUVI64_t>;
	extern template class ImageHorizonalFlip<AYUVF32_t>;
	extern template class ImageHorizonalFlip<AYUVF64_t>;
}
#endif // __stationaryorbit_graphics_core_deformation__