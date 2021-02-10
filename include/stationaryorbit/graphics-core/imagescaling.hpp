//	stationaryorbit/graphics-core/imagescaling
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
#ifndef __stationaryorbit_graphics_core_imagescaaling__
#define __stationaryorbit_graphics_core_imagescaaling__
#include "image.hpp"
#include "cmycolor.hpp"
#include "cmykcolor.hpp"
#include "grayscalecolor.hpp"
#include "rgbcolor.hpp"
#include "yuvcolor.hpp"
#include "imageoperationargs.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	///	画像を拡大・縮小します。
	///	@param	Tcolor
	///	色の表現に用いる型。
	template<class Tcolor>
	class ImageScaling : public Image<Tcolor>
	{
	public:
		///	色の表現に用いる型。
		typedef Tcolor ValueType;
		///	ピクセル補完関数。
		typedef std::function<Tcolor(const Image<Tcolor>&, const DisplayPointF&)> InterpolationMethod;
		///	@a ImageScaling で使用する引数。
		class ArgsType
		{
		private:
			InterpolationMethod _imethod;
			DisplayRectSizeF _amount;
		public:
			ArgsType() = default;
			ArgsType(const InterpolationMethod& imethod, const DisplayRectSizeF& scale) : _imethod(imethod), _amount(scale) {}
			ArgsType(const InterpolationMethod& imethod, float scale) : _imethod(imethod), _amount(scale, scale) {}
			ArgsType(const InterpolationMethod& imethod, float xscale, float yscale) : _imethod(imethod), _amount(xscale, yscale) {}

			///	ピクセル補完関数。
			const InterpolationMethod& Method() const { return _imethod; }
			///	拡大・縮小のスケールファクター。
			const DisplayRectSizeF& Amount() const { return _amount; }
		};
	private:
		const Image<Tcolor>& _data;
		ArgsType args;
		DisplayRectangle _newarea;
	public:
		///	オブジェクトを指定してこのオブジェクトを構築します。
		///	@param	source
		///	ソースとなる画像。
		///	@param	args
		///	この画像操作を行うために渡す引数。
		ImageScaling(const Image<Tcolor>& source, const ArgsType& args) : _data(source), args(args), _newarea(DisplayRectangle::FromEdge(int(source.Area().Left() * args.Amount().Width()), int(source.Area().Right() * args.Amount().Width()), int(source.Area().Top() * args.Amount().Height()), int(source.Area().Bottom() * args.Amount().Height()))) {}
		///	オブジェクトを指定してこのオブジェクトを構築します。
		///	@param	source
		///	ソースとなる画像。
		///	@param	imethod
		///	ピクセル補完関数。
		///	@param	scale
		///	拡大・縮小のスケールファクター。
		ImageScaling(const Image<Tcolor>& source, const InterpolationMethod& imethod, float scale) : ImageScaling(source, ArgsType(imethod, scale)) {}
		///	オブジェクトを指定してこのオブジェクトを構築します。
		///	@param	source
		///	ソースとなる画像。
		///	@param	imethod
		///	ピクセル補完関数。
		///	@param	xscale
		///	x軸拡大・縮小のスケールファクター。
		///	@param	yscale
		///	y軸拡大・縮小のスケールファクター。
		ImageScaling(const Image<Tcolor>& source, const InterpolationMethod& imethod, float xscale, float yscale) : ImageScaling(source, ArgsType(imethod, xscale, yscale)) {}

		[[nodiscard]] bool IsReadableAbyss() const noexcept { return _data.IsReadableAbyss(); }

		[[nodiscard]] const DisplayRectSize& Size() const noexcept { return _newarea.Size(); }
		[[nodiscard]] DisplayRectangle Area() const noexcept { return _newarea; }
		[[nodiscard]] ValueType At(const DisplayPoint& index) const { return args.Method()(_data, DisplayPointF(index.X() / args.Amount().Width(), index.Y() / args.Amount().Height())); }

		[[nodiscard]] ValueType operator[](const DisplayPoint& index) const { return args.Method()(_data, DisplayPointF(index.X() / args.Amount().Width(), index.Y() / args.Amount().Height())); }
	};

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
}
#endif // __stationaryorbit_graphics_core_imagescaaling__
