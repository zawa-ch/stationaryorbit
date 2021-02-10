//	stationaryorbit/graphics-core/imagealign
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
#ifndef __stationaryorbit_graphics_core_imagealign__
#define __stationaryorbit_graphics_core_imagealign__
#include "image.hpp"
#include "cmycolor.hpp"
#include "cmykcolor.hpp"
#include "grayscalecolor.hpp"
#include "rgbcolor.hpp"
#include "yuvcolor.hpp"
#include "imageoperationargs.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	///	画像の位置を原点に合わせます。
	///	@param	Tcolor
	///	色の表現に用いる型。
	template<class Tcolor>
	class ImageAlign : public Image<Tcolor>
	{
	public:
		///	色の表現に用いる型。
		typedef Tcolor ValueType;
		///	画像操作を行うための引数型。
		typedef ImageOperationArgs ArgsType;
	private:
		const Image<Tcolor>& _data;
	public:
		///	オブジェクトを指定してこのオブジェクトを構築します。
		///	@param	source
		///	ソースとなる画像。
		///	@param	args
		///	この画像操作を行うために渡す引数。
		ImageAlign(const Image<Tcolor>& source, const ArgsType& args) : _data(source) {}
		///	オブジェクトを指定してこのオブジェクトを構築します。
		///	@param	source
		///	ソースとなる画像。
		ImageAlign(const Image<Tcolor>& source) : ImageAlign(source, ArgsType()) {}

		[[nodiscard]] bool IsReadableAbyss() const noexcept { return _data.IsReadableAbyss(); }

		[[nodiscard]] const DisplayRectSize& Size() const noexcept { return _data.Size(); }
		[[nodiscard]] DisplayRectangle Area() const noexcept { return DisplayRectangle(DisplayPoint(0, 0), _data.Size()); }
		[[nodiscard]] ValueType At(const DisplayPoint& index) const { return _data.At(_data.Area().Origin() + index); }

		[[nodiscard]] ValueType operator[](const DisplayPoint& index) const { return _data[_data.Area().Origin() + index]; }
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
}
#endif // __stationaryorbit_graphics_core_imagealign__
