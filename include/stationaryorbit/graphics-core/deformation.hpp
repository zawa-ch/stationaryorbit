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
	template<class Tcolor>
	class ImageAlign : public Image<Tcolor>
	{
	public:
		typedef Tcolor ValueType;
	private:
		const Image<Tcolor>& _data;
	public:
		ImageAlign(const Image<Tcolor>& source) : _data(source) {}

		[[nodiscard]] virtual const DisplayRectSize& Size() const noexcept { return _data.Size(); }
		[[nodiscard]] virtual DisplayRectangle Area() const noexcept { return DisplayRectangle(DisplayPoint(0, 0), _data.Size()); }
		[[nodiscard]] virtual ValueType At(const DisplayPoint& index) const { return _data.At(_data.Area().Origin() + index); }

		[[nodiscard]] virtual ValueType operator[](const DisplayPoint& index) const { return _data[_data.Area().Origin() + index]; }
	};
	template<class Tcolor>
	class ImageShift : public Image<Tcolor>
	{
	public:
		typedef Tcolor ValueType;
	private:
		const Image<Tcolor>& _data;
		DisplayPoint _amount;
	public:
		ImageShift(const Image<Tcolor>& source, const DisplayPoint& amount) : _data(source), _amount(amount) {}

		[[nodiscard]] virtual const DisplayRectSize& Size() const noexcept { return _data.Size(); }
		[[nodiscard]] virtual DisplayRectangle Area() const noexcept { return _data.Area().Offset(_amount); }
		[[nodiscard]] virtual ValueType At(const DisplayPoint& index) const { return _data.At(index - _amount); }

		[[nodiscard]] virtual ValueType operator[](const DisplayPoint& index) const { return _data[index - _amount]; }
	};
	template<class Tcolor>
	class ImageScaling : public Image<Tcolor>
	{
	public:
		typedef Tcolor ValueType;
		typedef std::function<Tcolor(const Image<Tcolor>&, const DisplayPointF&)> InterpolationMethod;
	private:
		const Image<Tcolor>& _data;
		InterpolationMethod _imethod;
		DisplayRectSizeF _amount;
		DisplayRectangle _newarea;
	public:
		ImageScaling(const Image<Tcolor>& source, const InterpolationMethod& imethod, const float& scale) : _data(source), _imethod(imethod), _amount(scale, scale), _newarea(DisplayRectangle::FromEdge(int(source.Area().Left() * scale), int(source.Area().Right() * scale), int(source.Area().Top() * scale), int(source.Area().Bottom() * scale))) {}
		ImageScaling(const Image<Tcolor>& source, const InterpolationMethod& imethod, const float& xscale, const float& yscale) : _data(source), _imethod(imethod), _amount(xscale, yscale), _newarea(DisplayRectangle::FromEdge(int(source.Area().Left() * xscale), int(source.Area().Right() * xscale), int(source.Area().Top() * yscale), int(source.Area().Bottom() * yscale))) {}

		[[nodiscard]] virtual const DisplayRectSize& Size() const noexcept { return _newarea.Size(); }
		[[nodiscard]] virtual DisplayRectangle Area() const noexcept { return _newarea; }
		[[nodiscard]] virtual ValueType At(const DisplayPoint& index) const { return _imethod(_data, DisplayPointF(index.X() / _amount.Width(), index.Y() / _amount.Height())); }

		[[nodiscard]] virtual ValueType operator[](const DisplayPoint& index) const { return _imethod(_data, DisplayPointF(index.X() / _amount.Width(), index.Y() / _amount.Height())); }
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
		ImageHorizonalFlip(const Image<Tcolor>& source) : _data(source), _orig(1-_data.Area().Right(), _data.Area().Top()) {}

		[[nodiscard]] virtual const DisplayRectSize& Size() const noexcept { return _data.Size(); }
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
		ImageVerticalFlip(const Image<Tcolor>& source) : _data(source), _orig(_data.Area().Left(), 1-_data.Area().Bottom()) {}

		[[nodiscard]] virtual const DisplayRectSize& Size() const noexcept { return _data.Size(); }
		[[nodiscard]] virtual DisplayRectangle Area() const noexcept { return DisplayRectangle(_orig, _data.Size()); }
		[[nodiscard]] virtual ValueType At(const DisplayPoint& index) const { return _data.At(DisplayPoint(index.X(), -index.Y())); }

		[[nodiscard]] virtual ValueType operator[](const DisplayPoint& index) const { return _data[DisplayPoint(index.X(), -index.Y())]; }
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

	extern template class ImageShift<CMY8_t>;
	extern template class ImageShift<CMY16_t>;
	extern template class ImageShift<CMY32_t>;
	extern template class ImageShift<CMY64_t>;
	extern template class ImageShift<CMYI16_t>;
	extern template class ImageShift<CMYI32_t>;
	extern template class ImageShift<CMYI64_t>;
	extern template class ImageShift<CMYF32_t>;
	extern template class ImageShift<CMYF64_t>;
	extern template class ImageShift<ACMY8_t>;
	extern template class ImageShift<ACMY16_t>;
	extern template class ImageShift<ACMY32_t>;
	extern template class ImageShift<ACMY64_t>;
	extern template class ImageShift<ACMYI16_t>;
	extern template class ImageShift<ACMYI32_t>;
	extern template class ImageShift<ACMYI64_t>;
	extern template class ImageShift<ACMYF32_t>;
	extern template class ImageShift<ACMYF64_t>;
	extern template class ImageShift<CMYK8_t>;
	extern template class ImageShift<CMYK16_t>;
	extern template class ImageShift<CMYK32_t>;
	extern template class ImageShift<CMYK64_t>;
	extern template class ImageShift<CMYKI16_t>;
	extern template class ImageShift<CMYKI32_t>;
	extern template class ImageShift<CMYKI64_t>;
	extern template class ImageShift<CMYKF32_t>;
	extern template class ImageShift<CMYKF64_t>;
	extern template class ImageShift<ACMYK8_t>;
	extern template class ImageShift<ACMYK16_t>;
	extern template class ImageShift<ACMYK32_t>;
	extern template class ImageShift<ACMYK64_t>;
	extern template class ImageShift<ACMYKI16_t>;
	extern template class ImageShift<ACMYKI32_t>;
	extern template class ImageShift<ACMYKI64_t>;
	extern template class ImageShift<ACMYKF32_t>;
	extern template class ImageShift<ACMYKF64_t>;
	extern template class ImageShift<GrayScale1_t>;
	extern template class ImageShift<GrayScale8_t>;
	extern template class ImageShift<GrayScale16_t>;
	extern template class ImageShift<GrayScale32_t>;
	extern template class ImageShift<GrayScale64_t>;
	extern template class ImageShift<GrayScaleI16_t>;
	extern template class ImageShift<GrayScaleI32_t>;
	extern template class ImageShift<GrayScaleI64_t>;
	extern template class ImageShift<GrayScaleF32_t>;
	extern template class ImageShift<GrayScaleF64_t>;
	extern template class ImageShift<RGB8_t>;
	extern template class ImageShift<RGB16_t>;
	extern template class ImageShift<RGB32_t>;
	extern template class ImageShift<RGB64_t>;
	extern template class ImageShift<RGBI16_t>;
	extern template class ImageShift<RGBI32_t>;
	extern template class ImageShift<RGBI64_t>;
	extern template class ImageShift<RGBF32_t>;
	extern template class ImageShift<RGBF64_t>;
	extern template class ImageShift<ARGB8_t>;
	extern template class ImageShift<ARGB16_t>;
	extern template class ImageShift<ARGB32_t>;
	extern template class ImageShift<ARGB64_t>;
	extern template class ImageShift<ARGBI16_t>;
	extern template class ImageShift<ARGBI32_t>;
	extern template class ImageShift<ARGBI64_t>;
	extern template class ImageShift<ARGBF32_t>;
	extern template class ImageShift<ARGBF64_t>;
	extern template class ImageShift<YUV8_t>;
	extern template class ImageShift<YUV16_t>;
	extern template class ImageShift<YUV32_t>;
	extern template class ImageShift<YUV64_t>;
	extern template class ImageShift<YUVI16_t>;
	extern template class ImageShift<YUVI32_t>;
	extern template class ImageShift<YUVI64_t>;
	extern template class ImageShift<YUVF32_t>;
	extern template class ImageShift<YUVF64_t>;
	extern template class ImageShift<AYUV8_t>;
	extern template class ImageShift<AYUV16_t>;
	extern template class ImageShift<AYUV32_t>;
	extern template class ImageShift<AYUV64_t>;
	extern template class ImageShift<AYUVI16_t>;
	extern template class ImageShift<AYUVI32_t>;
	extern template class ImageShift<AYUVI64_t>;
	extern template class ImageShift<AYUVF32_t>;
	extern template class ImageShift<AYUVF64_t>;

	extern template class ImageScaling<CMY8_t>;
	extern template class ImageScaling<CMY16_t>;
	extern template class ImageScaling<CMY32_t>;
	extern template class ImageScaling<CMY64_t>;
	extern template class ImageScaling<CMYI16_t>;
	extern template class ImageScaling<CMYI32_t>;
	extern template class ImageScaling<CMYI64_t>;
	extern template class ImageScaling<CMYF32_t>;
	extern template class ImageScaling<CMYF64_t>;
	extern template class ImageScaling<ACMY8_t>;
	extern template class ImageScaling<ACMY16_t>;
	extern template class ImageScaling<ACMY32_t>;
	extern template class ImageScaling<ACMY64_t>;
	extern template class ImageScaling<ACMYI16_t>;
	extern template class ImageScaling<ACMYI32_t>;
	extern template class ImageScaling<ACMYI64_t>;
	extern template class ImageScaling<ACMYF32_t>;
	extern template class ImageScaling<ACMYF64_t>;
	extern template class ImageScaling<CMYK8_t>;
	extern template class ImageScaling<CMYK16_t>;
	extern template class ImageScaling<CMYK32_t>;
	extern template class ImageScaling<CMYK64_t>;
	extern template class ImageScaling<CMYKI16_t>;
	extern template class ImageScaling<CMYKI32_t>;
	extern template class ImageScaling<CMYKI64_t>;
	extern template class ImageScaling<CMYKF32_t>;
	extern template class ImageScaling<CMYKF64_t>;
	extern template class ImageScaling<ACMYK8_t>;
	extern template class ImageScaling<ACMYK16_t>;
	extern template class ImageScaling<ACMYK32_t>;
	extern template class ImageScaling<ACMYK64_t>;
	extern template class ImageScaling<ACMYKI16_t>;
	extern template class ImageScaling<ACMYKI32_t>;
	extern template class ImageScaling<ACMYKI64_t>;
	extern template class ImageScaling<ACMYKF32_t>;
	extern template class ImageScaling<ACMYKF64_t>;
	extern template class ImageScaling<GrayScale1_t>;
	extern template class ImageScaling<GrayScale8_t>;
	extern template class ImageScaling<GrayScale16_t>;
	extern template class ImageScaling<GrayScale32_t>;
	extern template class ImageScaling<GrayScale64_t>;
	extern template class ImageScaling<GrayScaleI16_t>;
	extern template class ImageScaling<GrayScaleI32_t>;
	extern template class ImageScaling<GrayScaleI64_t>;
	extern template class ImageScaling<GrayScaleF32_t>;
	extern template class ImageScaling<GrayScaleF64_t>;
	extern template class ImageScaling<RGB8_t>;
	extern template class ImageScaling<RGB16_t>;
	extern template class ImageScaling<RGB32_t>;
	extern template class ImageScaling<RGB64_t>;
	extern template class ImageScaling<RGBI16_t>;
	extern template class ImageScaling<RGBI32_t>;
	extern template class ImageScaling<RGBI64_t>;
	extern template class ImageScaling<RGBF32_t>;
	extern template class ImageScaling<RGBF64_t>;
	extern template class ImageScaling<ARGB8_t>;
	extern template class ImageScaling<ARGB16_t>;
	extern template class ImageScaling<ARGB32_t>;
	extern template class ImageScaling<ARGB64_t>;
	extern template class ImageScaling<ARGBI16_t>;
	extern template class ImageScaling<ARGBI32_t>;
	extern template class ImageScaling<ARGBI64_t>;
	extern template class ImageScaling<ARGBF32_t>;
	extern template class ImageScaling<ARGBF64_t>;
	extern template class ImageScaling<YUV8_t>;
	extern template class ImageScaling<YUV16_t>;
	extern template class ImageScaling<YUV32_t>;
	extern template class ImageScaling<YUV64_t>;
	extern template class ImageScaling<YUVI16_t>;
	extern template class ImageScaling<YUVI32_t>;
	extern template class ImageScaling<YUVI64_t>;
	extern template class ImageScaling<YUVF32_t>;
	extern template class ImageScaling<YUVF64_t>;
	extern template class ImageScaling<AYUV8_t>;
	extern template class ImageScaling<AYUV16_t>;
	extern template class ImageScaling<AYUV32_t>;
	extern template class ImageScaling<AYUV64_t>;
	extern template class ImageScaling<AYUVI16_t>;
	extern template class ImageScaling<AYUVI32_t>;
	extern template class ImageScaling<AYUVI64_t>;
	extern template class ImageScaling<AYUVF32_t>;
	extern template class ImageScaling<AYUVF64_t>;

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