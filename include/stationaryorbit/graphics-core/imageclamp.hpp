//	stationaryorbit/graphics-core/imageclamp
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
#ifndef __stationaryorbit_graphics_core_imageclamp__
#define __stationaryorbit_graphics_core_imageclamp__
#include "image.hpp"
#include "cmycolor.hpp"
#include "cmykcolor.hpp"
#include "grayscalecolor.hpp"
#include "rgbcolor.hpp"
#include "yuvcolor.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	template<class Tcolor>
	class ImageClamp : public Image<Tcolor>
	{
	public:
		typedef Tcolor ValueType;
	private:
		const Image<Tcolor>& _data;
	public:
		ImageClamp(const Image<Tcolor>& source) : _data(source) {}

		[[nodiscard]] virtual const DisplayRectSize& Size() const noexcept { return _data.Size(); }
		[[nodiscard]] virtual DisplayRectangle Area() const noexcept { return _data.Area(); }
		[[nodiscard]] virtual ValueType At(const DisplayPoint& index) const { return _data.At(DisplayPoint((_data.Area().XRange().isIncluded(index.X())?(index.X()):((_data.Area().XRange().isAbove(index.X()))?(_data.Area().XRange().GetCeiling() - 1):(_data.Area().XRange().GetFloor()))), (_data.Area().YRange().isIncluded(index.Y())?(index.Y()):((_data.Area().YRange().isAbove(index.Y()))?(_data.Area().YRange().GetCeiling() - 1):(_data.Area().YRange().GetFloor()))))); }

		[[nodiscard]] virtual ValueType operator[](const DisplayPoint& index) const { return At(index); }
	};

	extern template class ImageClamp<CMY8_t>;
	extern template class ImageClamp<CMY16_t>;
	extern template class ImageClamp<CMY32_t>;
	extern template class ImageClamp<CMY64_t>;
	extern template class ImageClamp<CMYI16_t>;
	extern template class ImageClamp<CMYI32_t>;
	extern template class ImageClamp<CMYI64_t>;
	extern template class ImageClamp<CMYF32_t>;
	extern template class ImageClamp<CMYF64_t>;
	extern template class ImageClamp<ACMY8_t>;
	extern template class ImageClamp<ACMY16_t>;
	extern template class ImageClamp<ACMY32_t>;
	extern template class ImageClamp<ACMY64_t>;
	extern template class ImageClamp<ACMYI16_t>;
	extern template class ImageClamp<ACMYI32_t>;
	extern template class ImageClamp<ACMYI64_t>;
	extern template class ImageClamp<ACMYF32_t>;
	extern template class ImageClamp<ACMYF64_t>;
	extern template class ImageClamp<CMYK8_t>;
	extern template class ImageClamp<CMYK16_t>;
	extern template class ImageClamp<CMYK32_t>;
	extern template class ImageClamp<CMYK64_t>;
	extern template class ImageClamp<CMYKI16_t>;
	extern template class ImageClamp<CMYKI32_t>;
	extern template class ImageClamp<CMYKI64_t>;
	extern template class ImageClamp<CMYKF32_t>;
	extern template class ImageClamp<CMYKF64_t>;
	extern template class ImageClamp<ACMYK8_t>;
	extern template class ImageClamp<ACMYK16_t>;
	extern template class ImageClamp<ACMYK32_t>;
	extern template class ImageClamp<ACMYK64_t>;
	extern template class ImageClamp<ACMYKI16_t>;
	extern template class ImageClamp<ACMYKI32_t>;
	extern template class ImageClamp<ACMYKI64_t>;
	extern template class ImageClamp<ACMYKF32_t>;
	extern template class ImageClamp<ACMYKF64_t>;
	extern template class ImageClamp<GrayScale1_t>;
	extern template class ImageClamp<GrayScale8_t>;
	extern template class ImageClamp<GrayScale16_t>;
	extern template class ImageClamp<GrayScale32_t>;
	extern template class ImageClamp<GrayScale64_t>;
	extern template class ImageClamp<GrayScaleI16_t>;
	extern template class ImageClamp<GrayScaleI32_t>;
	extern template class ImageClamp<GrayScaleI64_t>;
	extern template class ImageClamp<GrayScaleF32_t>;
	extern template class ImageClamp<GrayScaleF64_t>;
	extern template class ImageClamp<RGB8_t>;
	extern template class ImageClamp<RGB16_t>;
	extern template class ImageClamp<RGB32_t>;
	extern template class ImageClamp<RGB64_t>;
	extern template class ImageClamp<RGBI16_t>;
	extern template class ImageClamp<RGBI32_t>;
	extern template class ImageClamp<RGBI64_t>;
	extern template class ImageClamp<RGBF32_t>;
	extern template class ImageClamp<RGBF64_t>;
	extern template class ImageClamp<ARGB8_t>;
	extern template class ImageClamp<ARGB16_t>;
	extern template class ImageClamp<ARGB32_t>;
	extern template class ImageClamp<ARGB64_t>;
	extern template class ImageClamp<ARGBI16_t>;
	extern template class ImageClamp<ARGBI32_t>;
	extern template class ImageClamp<ARGBI64_t>;
	extern template class ImageClamp<ARGBF32_t>;
	extern template class ImageClamp<ARGBF64_t>;
	extern template class ImageClamp<YUV8_t>;
	extern template class ImageClamp<YUV16_t>;
	extern template class ImageClamp<YUV32_t>;
	extern template class ImageClamp<YUV64_t>;
	extern template class ImageClamp<YUVI16_t>;
	extern template class ImageClamp<YUVI32_t>;
	extern template class ImageClamp<YUVI64_t>;
	extern template class ImageClamp<YUVF32_t>;
	extern template class ImageClamp<YUVF64_t>;
	extern template class ImageClamp<AYUV8_t>;
	extern template class ImageClamp<AYUV16_t>;
	extern template class ImageClamp<AYUV32_t>;
	extern template class ImageClamp<AYUV64_t>;
	extern template class ImageClamp<AYUVI16_t>;
	extern template class ImageClamp<AYUVI32_t>;
	extern template class ImageClamp<AYUVI64_t>;
	extern template class ImageClamp<AYUVF32_t>;
	extern template class ImageClamp<AYUVF64_t>;
}
#endif // __stationaryorbit_graphics_core_imageclamp__
