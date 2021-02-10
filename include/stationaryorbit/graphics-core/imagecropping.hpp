//	stationaryorbit/graphics-core/imagecropping
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
#ifndef __stationaryorbit_graphics_core_imagecropping__
#define __stationaryorbit_graphics_core_imagecropping__
#include "image.hpp"
#include "cmycolor.hpp"
#include "cmykcolor.hpp"
#include "grayscalecolor.hpp"
#include "rgbcolor.hpp"
#include "yuvcolor.hpp"
#include "imageoperationargs.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	///	@a ImageCropping で使用する引数。
	class ImageCroppingArgs
	{
	private:
		DisplayRectangle _area;
	public:
		ImageCroppingArgs() = default;
		ImageCroppingArgs(const DisplayRectangle& area) : _area(area) {}

		///	切り抜きをする範囲。
		const DisplayRectangle& Area() const { return _area; }
	};
	///	画像を指定した範囲で切り抜きます。
	///	@param	Tcolor
	///	色の表現に用いる型。
	template<class Tcolor>
	class ImageCropping : public Image<Tcolor>
	{
	public:
		///	色の表現に用いる型。
		typedef Tcolor ValueType;
		///	画像操作を行うための引数型。
		typedef ImageCroppingArgs ArgsType;
	private:
		const Image<Tcolor>& _data;
		ArgsType args;
	public:
		///	オブジェクトを指定してこのオブジェクトを構築します。
		///	@param	source
		///	ソースとなる画像。
		///	@param	args
		///	この画像操作を行うために渡す引数。
		ImageCropping(const Image<Tcolor>& source, const ArgsType& args) : _data(source), args(args) {}
		///	オブジェクトを指定してこのオブジェクトを構築します。
		///	@param	source
		///	ソースとなる画像。
		///	@param	area
		///	切り抜きをする範囲。
		ImageCropping(const Image<Tcolor>& source, const DisplayRectangle& area) : ImageCropping(source, ArgsType(area)) {}

		[[nodiscard]] bool IsReadableAbyss() const noexcept { return false; }

		[[nodiscard]] const DisplayRectSize& Size() const noexcept { return args.Area().Size(); }
		[[nodiscard]] DisplayRectangle Area() const noexcept { return args.Area(); }
		[[nodiscard]] ValueType At(const DisplayPoint& index) const { if (args.Area().Contains(index)) { return _data.At(index); } else { throw std::out_of_range("指定されたインデックスは境界を超えています。"); } }

		[[nodiscard]] ValueType operator[](const DisplayPoint& index) const { if (args.Area().Contains(index)) { return _data[index]; } else { throw std::out_of_range("指定されたインデックスは境界を超えています。"); } }
	};

	extern template class ImageCropping<CMY8_t>;
	extern template class ImageCropping<CMY16_t>;
	extern template class ImageCropping<CMY32_t>;
	extern template class ImageCropping<CMY64_t>;
	extern template class ImageCropping<CMYI16_t>;
	extern template class ImageCropping<CMYI32_t>;
	extern template class ImageCropping<CMYI64_t>;
	extern template class ImageCropping<CMYF32_t>;
	extern template class ImageCropping<CMYF64_t>;
	extern template class ImageCropping<ACMY8_t>;
	extern template class ImageCropping<ACMY16_t>;
	extern template class ImageCropping<ACMY32_t>;
	extern template class ImageCropping<ACMY64_t>;
	extern template class ImageCropping<ACMYI16_t>;
	extern template class ImageCropping<ACMYI32_t>;
	extern template class ImageCropping<ACMYI64_t>;
	extern template class ImageCropping<ACMYF32_t>;
	extern template class ImageCropping<ACMYF64_t>;
	extern template class ImageCropping<CMYK8_t>;
	extern template class ImageCropping<CMYK16_t>;
	extern template class ImageCropping<CMYK32_t>;
	extern template class ImageCropping<CMYK64_t>;
	extern template class ImageCropping<CMYKI16_t>;
	extern template class ImageCropping<CMYKI32_t>;
	extern template class ImageCropping<CMYKI64_t>;
	extern template class ImageCropping<CMYKF32_t>;
	extern template class ImageCropping<CMYKF64_t>;
	extern template class ImageCropping<ACMYK8_t>;
	extern template class ImageCropping<ACMYK16_t>;
	extern template class ImageCropping<ACMYK32_t>;
	extern template class ImageCropping<ACMYK64_t>;
	extern template class ImageCropping<ACMYKI16_t>;
	extern template class ImageCropping<ACMYKI32_t>;
	extern template class ImageCropping<ACMYKI64_t>;
	extern template class ImageCropping<ACMYKF32_t>;
	extern template class ImageCropping<ACMYKF64_t>;
	extern template class ImageCropping<GrayScale1_t>;
	extern template class ImageCropping<GrayScale8_t>;
	extern template class ImageCropping<GrayScale16_t>;
	extern template class ImageCropping<GrayScale32_t>;
	extern template class ImageCropping<GrayScale64_t>;
	extern template class ImageCropping<GrayScaleI16_t>;
	extern template class ImageCropping<GrayScaleI32_t>;
	extern template class ImageCropping<GrayScaleI64_t>;
	extern template class ImageCropping<GrayScaleF32_t>;
	extern template class ImageCropping<GrayScaleF64_t>;
	extern template class ImageCropping<RGB8_t>;
	extern template class ImageCropping<RGB16_t>;
	extern template class ImageCropping<RGB32_t>;
	extern template class ImageCropping<RGB64_t>;
	extern template class ImageCropping<RGBI16_t>;
	extern template class ImageCropping<RGBI32_t>;
	extern template class ImageCropping<RGBI64_t>;
	extern template class ImageCropping<RGBF32_t>;
	extern template class ImageCropping<RGBF64_t>;
	extern template class ImageCropping<ARGB8_t>;
	extern template class ImageCropping<ARGB16_t>;
	extern template class ImageCropping<ARGB32_t>;
	extern template class ImageCropping<ARGB64_t>;
	extern template class ImageCropping<ARGBI16_t>;
	extern template class ImageCropping<ARGBI32_t>;
	extern template class ImageCropping<ARGBI64_t>;
	extern template class ImageCropping<ARGBF32_t>;
	extern template class ImageCropping<ARGBF64_t>;
	extern template class ImageCropping<YUV8_t>;
	extern template class ImageCropping<YUV16_t>;
	extern template class ImageCropping<YUV32_t>;
	extern template class ImageCropping<YUV64_t>;
	extern template class ImageCropping<YUVI16_t>;
	extern template class ImageCropping<YUVI32_t>;
	extern template class ImageCropping<YUVI64_t>;
	extern template class ImageCropping<YUVF32_t>;
	extern template class ImageCropping<YUVF64_t>;
	extern template class ImageCropping<AYUV8_t>;
	extern template class ImageCropping<AYUV16_t>;
	extern template class ImageCropping<AYUV32_t>;
	extern template class ImageCropping<AYUV64_t>;
	extern template class ImageCropping<AYUVI16_t>;
	extern template class ImageCropping<AYUVI32_t>;
	extern template class ImageCropping<AYUVI64_t>;
	extern template class ImageCropping<AYUVF32_t>;
	extern template class ImageCropping<AYUVF64_t>;
}
#endif // __stationaryorbit_graphics_core_imagecropping__
