//	stationaryorbit/graphics-core/imageshift
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
#ifndef __stationaryorbit_graphics_core_imageshift__
#define __stationaryorbit_graphics_core_imageshift__
#include "image.hpp"
#include "cmycolor.hpp"
#include "cmykcolor.hpp"
#include "grayscalecolor.hpp"
#include "rgbcolor.hpp"
#include "yuvcolor.hpp"
#include "imageoperationargs.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	///	@a ImageShift で使用する引数。
	class ImageShiftArgs
	{
	private:
		DisplayPoint _amount;
	public:
		ImageShiftArgs() = default;
		ImageShiftArgs(const DisplayPoint& amount) : _amount(amount) {}

		///	移動する大きさ。
		const DisplayPoint& Amount() const { return _amount; }
	};
	///	画像を指定された大きさだけ移動します。
	///	@param	Tcolor
	///	色の表現に用いる型。
	template<class Tcolor>
	class ImageShift : public Image<Tcolor>
	{
	public:
		///	色の表現に用いる型。
		typedef Tcolor ValueType;
		///	画像操作を行うための引数型。
		typedef ImageShiftArgs ArgsType;
	private:
		const Image<Tcolor>& _data;
		ArgsType args;
	public:
		///	オブジェクトを指定してこのオブジェクトを構築します。
		///	@param	source
		///	ソースとなる画像。
		///	@param	args
		///	この画像操作を行うために渡す引数。
		ImageShift(const Image<Tcolor>& source, const ArgsType& args) : _data(source), args(args) {}
		///	オブジェクトを指定してこのオブジェクトを構築します。
		///	@param	source
		///	ソースとなる画像。
		///	@param	amount
		///	移動する大きさ。
		ImageShift(const Image<Tcolor>& source, const DisplayPoint& amount) : ImageShift(source, ArgsType(amount)) {}

		[[nodiscard]] bool IsReadableAbyss() const noexcept { return _data.IsReadableAbyss(); }

		[[nodiscard]] const DisplayRectSize& Size() const noexcept { return _data.Size(); }
		[[nodiscard]] DisplayRectangle Area() const noexcept { return _data.Area().Offset(args.Amount()); }
		[[nodiscard]] ValueType At(const DisplayPoint& index) const { return _data.At(index - args.Amount()); }

		[[nodiscard]] ValueType operator[](const DisplayPoint& index) const { return _data[index - args.Amount()]; }
	};

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
}
#endif // __stationaryorbit_graphics_core_imageshift__
