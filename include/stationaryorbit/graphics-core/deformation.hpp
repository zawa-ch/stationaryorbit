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
	class ImageAlign : public Image<Tcolor>
	{
	public:
		typedef Tcolor ValueType;
	private:
		const Image<Tcolor>& _data;
	public:
		ImageAlign(const Image<Tcolor>& source) : _data(source) {}

		[[nodiscard]] virtual const RectangleSize& Size() const noexcept { return _data.Size(); }
		[[nodiscard]] virtual DisplayRectangle Area() const noexcept { return DisplayRectangle(DisplayPoint(0, 0), _data.Size()); }
		[[nodiscard]] virtual ValueType At(const DisplayPoint& index) const { return _data.At(_data.Area().Location() + index); }

		[[nodiscard]] virtual ValueType operator[](const DisplayPoint& index) const { return _data[_data.Area().Location() + index]; }
	};
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
	template<class Tcolor>
	class ImageVerticalFlip : public Image<Tcolor>
	{
	public:
		typedef Tcolor ValueType;
	private:
		const Image<Tcolor>& _data;
		DisplayPoint _orig;
	public:
		ImageVerticalFlip(const Image<Tcolor>& source) : _data(source), _orig(_data.Area().Left(), -_data.Area().Bottom()) {}

		[[nodiscard]] virtual const RectangleSize& Size() const noexcept { return _data.Size(); }
		[[nodiscard]] virtual DisplayRectangle Area() const noexcept { return DisplayRectangle(_orig, _data.Size()); }
		[[nodiscard]] virtual ValueType At(const DisplayPoint& index) const { return _data.At(DisplayPoint(index.X(), -index.Y())); }

		[[nodiscard]] virtual ValueType operator[](const DisplayPoint& index) const { return _data[DisplayPoint(index.X(), -index.Y())]; }
	};

	extern template class ImageAlign<CMY8_t>;
	extern template class ImageAlign<CMY16_t>;
	extern template class ImageAlign<CMY32_t>;
	extern template class ImageAlign<CMY64_t>;
	extern template class ImageAlign<CMYI16_t>;
	extern template class ImageAlign<CMYI32_t>;
	extern template class ImageAlign<CMYI64_t>;
	extern template class ImageAlign<CMYF32_t>;
	extern template class ImageAlign<CMYF64_t>;
	extern template class ImageAlign<ACMY8_t>;
	extern template class ImageAlign<ACMY16_t>;
	extern template class ImageAlign<ACMY32_t>;
	extern template class ImageAlign<ACMY64_t>;
	extern template class ImageAlign<ACMYI16_t>;
	extern template class ImageAlign<ACMYI32_t>;
	extern template class ImageAlign<ACMYI64_t>;
	extern template class ImageAlign<ACMYF32_t>;
	extern template class ImageAlign<ACMYF64_t>;
	extern template class ImageAlign<CMYK8_t>;
	extern template class ImageAlign<CMYK16_t>;
	extern template class ImageAlign<CMYK32_t>;
	extern template class ImageAlign<CMYK64_t>;
	extern template class ImageAlign<CMYKI16_t>;
	extern template class ImageAlign<CMYKI32_t>;
	extern template class ImageAlign<CMYKI64_t>;
	extern template class ImageAlign<CMYKF32_t>;
	extern template class ImageAlign<CMYKF64_t>;
	extern template class ImageAlign<ACMYK8_t>;
	extern template class ImageAlign<ACMYK16_t>;
	extern template class ImageAlign<ACMYK32_t>;
	extern template class ImageAlign<ACMYK64_t>;
	extern template class ImageAlign<ACMYKI16_t>;
	extern template class ImageAlign<ACMYKI32_t>;
	extern template class ImageAlign<ACMYKI64_t>;
	extern template class ImageAlign<ACMYKF32_t>;
	extern template class ImageAlign<ACMYKF64_t>;
	extern template class ImageAlign<GrayScale1_t>;
	extern template class ImageAlign<GrayScale8_t>;
	extern template class ImageAlign<GrayScale16_t>;
	extern template class ImageAlign<GrayScale32_t>;
	extern template class ImageAlign<GrayScale64_t>;
	extern template class ImageAlign<GrayScaleI16_t>;
	extern template class ImageAlign<GrayScaleI32_t>;
	extern template class ImageAlign<GrayScaleI64_t>;
	extern template class ImageAlign<GrayScaleF32_t>;
	extern template class ImageAlign<GrayScaleF64_t>;
	extern template class ImageAlign<RGB8_t>;
	extern template class ImageAlign<RGB16_t>;
	extern template class ImageAlign<RGB32_t>;
	extern template class ImageAlign<RGB64_t>;
	extern template class ImageAlign<RGBI16_t>;
	extern template class ImageAlign<RGBI32_t>;
	extern template class ImageAlign<RGBI64_t>;
	extern template class ImageAlign<RGBF32_t>;
	extern template class ImageAlign<RGBF64_t>;
	extern template class ImageAlign<ARGB8_t>;
	extern template class ImageAlign<ARGB16_t>;
	extern template class ImageAlign<ARGB32_t>;
	extern template class ImageAlign<ARGB64_t>;
	extern template class ImageAlign<ARGBI16_t>;
	extern template class ImageAlign<ARGBI32_t>;
	extern template class ImageAlign<ARGBI64_t>;
	extern template class ImageAlign<ARGBF32_t>;
	extern template class ImageAlign<ARGBF64_t>;
	extern template class ImageAlign<YUV8_t>;
	extern template class ImageAlign<YUV16_t>;
	extern template class ImageAlign<YUV32_t>;
	extern template class ImageAlign<YUV64_t>;
	extern template class ImageAlign<YUVI16_t>;
	extern template class ImageAlign<YUVI32_t>;
	extern template class ImageAlign<YUVI64_t>;
	extern template class ImageAlign<YUVF32_t>;
	extern template class ImageAlign<YUVF64_t>;
	extern template class ImageAlign<AYUV8_t>;
	extern template class ImageAlign<AYUV16_t>;
	extern template class ImageAlign<AYUV32_t>;
	extern template class ImageAlign<AYUV64_t>;
	extern template class ImageAlign<AYUVI16_t>;
	extern template class ImageAlign<AYUVI32_t>;
	extern template class ImageAlign<AYUVI64_t>;
	extern template class ImageAlign<AYUVF32_t>;
	extern template class ImageAlign<AYUVF64_t>;

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

	extern template class ImageVerticalFlip<CMY8_t>;
	extern template class ImageVerticalFlip<CMY16_t>;
	extern template class ImageVerticalFlip<CMY32_t>;
	extern template class ImageVerticalFlip<CMY64_t>;
	extern template class ImageVerticalFlip<CMYI16_t>;
	extern template class ImageVerticalFlip<CMYI32_t>;
	extern template class ImageVerticalFlip<CMYI64_t>;
	extern template class ImageVerticalFlip<CMYF32_t>;
	extern template class ImageVerticalFlip<CMYF64_t>;
	extern template class ImageVerticalFlip<ACMY8_t>;
	extern template class ImageVerticalFlip<ACMY16_t>;
	extern template class ImageVerticalFlip<ACMY32_t>;
	extern template class ImageVerticalFlip<ACMY64_t>;
	extern template class ImageVerticalFlip<ACMYI16_t>;
	extern template class ImageVerticalFlip<ACMYI32_t>;
	extern template class ImageVerticalFlip<ACMYI64_t>;
	extern template class ImageVerticalFlip<ACMYF32_t>;
	extern template class ImageVerticalFlip<ACMYF64_t>;
	extern template class ImageVerticalFlip<CMYK8_t>;
	extern template class ImageVerticalFlip<CMYK16_t>;
	extern template class ImageVerticalFlip<CMYK32_t>;
	extern template class ImageVerticalFlip<CMYK64_t>;
	extern template class ImageVerticalFlip<CMYKI16_t>;
	extern template class ImageVerticalFlip<CMYKI32_t>;
	extern template class ImageVerticalFlip<CMYKI64_t>;
	extern template class ImageVerticalFlip<CMYKF32_t>;
	extern template class ImageVerticalFlip<CMYKF64_t>;
	extern template class ImageVerticalFlip<ACMYK8_t>;
	extern template class ImageVerticalFlip<ACMYK16_t>;
	extern template class ImageVerticalFlip<ACMYK32_t>;
	extern template class ImageVerticalFlip<ACMYK64_t>;
	extern template class ImageVerticalFlip<ACMYKI16_t>;
	extern template class ImageVerticalFlip<ACMYKI32_t>;
	extern template class ImageVerticalFlip<ACMYKI64_t>;
	extern template class ImageVerticalFlip<ACMYKF32_t>;
	extern template class ImageVerticalFlip<ACMYKF64_t>;
	extern template class ImageVerticalFlip<GrayScale1_t>;
	extern template class ImageVerticalFlip<GrayScale8_t>;
	extern template class ImageVerticalFlip<GrayScale16_t>;
	extern template class ImageVerticalFlip<GrayScale32_t>;
	extern template class ImageVerticalFlip<GrayScale64_t>;
	extern template class ImageVerticalFlip<GrayScaleI16_t>;
	extern template class ImageVerticalFlip<GrayScaleI32_t>;
	extern template class ImageVerticalFlip<GrayScaleI64_t>;
	extern template class ImageVerticalFlip<GrayScaleF32_t>;
	extern template class ImageVerticalFlip<GrayScaleF64_t>;
	extern template class ImageVerticalFlip<RGB8_t>;
	extern template class ImageVerticalFlip<RGB16_t>;
	extern template class ImageVerticalFlip<RGB32_t>;
	extern template class ImageVerticalFlip<RGB64_t>;
	extern template class ImageVerticalFlip<RGBI16_t>;
	extern template class ImageVerticalFlip<RGBI32_t>;
	extern template class ImageVerticalFlip<RGBI64_t>;
	extern template class ImageVerticalFlip<RGBF32_t>;
	extern template class ImageVerticalFlip<RGBF64_t>;
	extern template class ImageVerticalFlip<ARGB8_t>;
	extern template class ImageVerticalFlip<ARGB16_t>;
	extern template class ImageVerticalFlip<ARGB32_t>;
	extern template class ImageVerticalFlip<ARGB64_t>;
	extern template class ImageVerticalFlip<ARGBI16_t>;
	extern template class ImageVerticalFlip<ARGBI32_t>;
	extern template class ImageVerticalFlip<ARGBI64_t>;
	extern template class ImageVerticalFlip<ARGBF32_t>;
	extern template class ImageVerticalFlip<ARGBF64_t>;
	extern template class ImageVerticalFlip<YUV8_t>;
	extern template class ImageVerticalFlip<YUV16_t>;
	extern template class ImageVerticalFlip<YUV32_t>;
	extern template class ImageVerticalFlip<YUV64_t>;
	extern template class ImageVerticalFlip<YUVI16_t>;
	extern template class ImageVerticalFlip<YUVI32_t>;
	extern template class ImageVerticalFlip<YUVI64_t>;
	extern template class ImageVerticalFlip<YUVF32_t>;
	extern template class ImageVerticalFlip<YUVF64_t>;
	extern template class ImageVerticalFlip<AYUV8_t>;
	extern template class ImageVerticalFlip<AYUV16_t>;
	extern template class ImageVerticalFlip<AYUV32_t>;
	extern template class ImageVerticalFlip<AYUV64_t>;
	extern template class ImageVerticalFlip<AYUVI16_t>;
	extern template class ImageVerticalFlip<AYUVI32_t>;
	extern template class ImageVerticalFlip<AYUVI64_t>;
	extern template class ImageVerticalFlip<AYUVF32_t>;
	extern template class ImageVerticalFlip<AYUVF64_t>;
}
#endif // __stationaryorbit_graphics_core_deformation__