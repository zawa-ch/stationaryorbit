//	stationaryorbit/graphics-core/imageturn
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
#ifndef __stationaryorbit_graphics_core_imageturn__
#define __stationaryorbit_graphics_core_imageturn__
#include "image.hpp"
#include "cmycolor.hpp"
#include "cmykcolor.hpp"
#include "grayscalecolor.hpp"
#include "rgbcolor.hpp"
#include "yuvcolor.hpp"
#include "imageoperationargs.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	///	画像を右方向に90°回転します。
	///	@param	Tcolor
	///	色の表現に用いる型。
	template<class Tcolor>
	class ImageRightTurn : public Image<Tcolor>
	{
	public:
		///	色の表現に用いる型。
		typedef Tcolor ValueType;
		///	画像操作を行うための引数型。
		typedef ImageOperationArgs ArgsType;
	private:
		const Image<Tcolor>& _data;
		DisplayRectangle _area;
	public:
		///	オブジェクトを指定してこのオブジェクトを構築します。
		///	@param	source
		///	ソースとなる画像。
		///	@param	args
		///	この画像操作を行うために渡す引数。
		ImageRightTurn(const Image<Tcolor>& source, const ArgsType& args) : _data(source), _area(DisplayRectangle::FromEdge(-source.Area().Bottom() + 1, -source.Area().Top() + 1, source.Area().Left(), source.Area().Right())) {}
		///	オブジェクトを指定してこのオブジェクトを構築します。
		///	@param	source
		///	ソースとなる画像。
		ImageRightTurn(const Image<Tcolor>& source) : ImageRightTurn(source, ArgsType()) {}

		[[nodiscard]] bool IsReadableAbyss() const noexcept { return _data.IsReadableAbyss(); }

		[[nodiscard]] const DisplayRectSize& Size() const noexcept { return _area.Size(); }
		[[nodiscard]] DisplayRectangle Area() const noexcept { return _area; }
		[[nodiscard]] ValueType At(const DisplayPoint& index) const { return _data.At(DisplayPoint(index.Y(), -index.X())); }

		[[nodiscard]] ValueType operator[](const DisplayPoint& index) const { return _data[DisplayPoint(index.Y(), -index.X())]; }
	};
	///	画像を左方向に90°回転します。
	///	@param	Tcolor
	///	色の表現に用いる型。
	template<class Tcolor>
	class ImageLeftTurn : public Image<Tcolor>
	{
	public:
		///	色の表現に用いる型。
		typedef Tcolor ValueType;
		///	画像操作を行うための引数型。
		typedef ImageOperationArgs ArgsType;
	private:
		const Image<Tcolor>& _data;
		DisplayRectangle _area;
	public:
		///	オブジェクトを指定してこのオブジェクトを構築します。
		///	@param	source
		///	ソースとなる画像。
		///	@param	args
		///	この画像操作を行うために渡す引数。
		ImageLeftTurn(const Image<Tcolor>& source, const ArgsType& args) : _data(source), _area(DisplayRectangle::FromEdge(source.Area().Top(), source.Area().Bottom(), -source.Area().Right() + 1, -source.Area().Left() + 1)) {}
		///	オブジェクトを指定してこのオブジェクトを構築します。
		///	@param	source
		///	ソースとなる画像。
		ImageLeftTurn(const Image<Tcolor>& source) : ImageLeftTurn(source, ArgsType()) {}

		[[nodiscard]] bool IsReadableAbyss() const noexcept { return _data.IsReadableAbyss(); }

		[[nodiscard]] const DisplayRectSize& Size() const noexcept { return _area.Size(); }
		[[nodiscard]] DisplayRectangle Area() const noexcept { return _area; }
		[[nodiscard]] ValueType At(const DisplayPoint& index) const { return _data.At(DisplayPoint(-index.Y(), index.X())); }

		[[nodiscard]] ValueType operator[](const DisplayPoint& index) const { return _data[DisplayPoint(-index.Y(), index.X())]; }
	};
	///	画像を180°回転します。
	///	@param	Tcolor
	///	色の表現に用いる型。
	template<class Tcolor>
	class ImageInvertTurn : public Image<Tcolor>
	{
	public:
		///	色の表現に用いる型。
		typedef Tcolor ValueType;
		///	画像操作を行うための引数型。
		typedef ImageOperationArgs ArgsType;
	private:
		const Image<Tcolor>& _data;
		DisplayRectangle _area;
	public:
		///	オブジェクトを指定してこのオブジェクトを構築します。
		///	@param	source
		///	ソースとなる画像。
		///	@param	args
		///	この画像操作を行うために渡す引数。
		ImageInvertTurn(const Image<Tcolor>& source, const ArgsType& args) : _data(source), _area(DisplayRectangle::FromEdge(-source.Area().Right() + 1, -source.Area().Left() + 1, -source.Area().Bottom() + 1, -source.Area().Top() + 1)) {}
		///	オブジェクトを指定してこのオブジェクトを構築します。
		///	@param	source
		///	ソースとなる画像。
		ImageInvertTurn(const Image<Tcolor>& source) : ImageInvertTurn(source, ArgsType()) {}

		[[nodiscard]] bool IsReadableAbyss() const noexcept { return _data.IsReadableAbyss(); }

		[[nodiscard]] const DisplayRectSize& Size() const noexcept { return _area.Size(); }
		[[nodiscard]] DisplayRectangle Area() const noexcept { return _area; }
		[[nodiscard]] ValueType At(const DisplayPoint& index) const { return _data.At(DisplayPoint(-index.X(), -index.Y())); }

		[[nodiscard]] ValueType operator[](const DisplayPoint& index) const { return _data[DisplayPoint(-index.X(), -index.Y())]; }
	};

	extern template class ImageRightTurn<CMY8_t>;
	extern template class ImageRightTurn<CMY16_t>;
	extern template class ImageRightTurn<CMY32_t>;
	extern template class ImageRightTurn<CMY64_t>;
	extern template class ImageRightTurn<CMYI16_t>;
	extern template class ImageRightTurn<CMYI32_t>;
	extern template class ImageRightTurn<CMYI64_t>;
	extern template class ImageRightTurn<CMYF32_t>;
	extern template class ImageRightTurn<CMYF64_t>;
	extern template class ImageRightTurn<ACMY8_t>;
	extern template class ImageRightTurn<ACMY16_t>;
	extern template class ImageRightTurn<ACMY32_t>;
	extern template class ImageRightTurn<ACMY64_t>;
	extern template class ImageRightTurn<ACMYI16_t>;
	extern template class ImageRightTurn<ACMYI32_t>;
	extern template class ImageRightTurn<ACMYI64_t>;
	extern template class ImageRightTurn<ACMYF32_t>;
	extern template class ImageRightTurn<ACMYF64_t>;
	extern template class ImageRightTurn<CMYK8_t>;
	extern template class ImageRightTurn<CMYK16_t>;
	extern template class ImageRightTurn<CMYK32_t>;
	extern template class ImageRightTurn<CMYK64_t>;
	extern template class ImageRightTurn<CMYKI16_t>;
	extern template class ImageRightTurn<CMYKI32_t>;
	extern template class ImageRightTurn<CMYKI64_t>;
	extern template class ImageRightTurn<CMYKF32_t>;
	extern template class ImageRightTurn<CMYKF64_t>;
	extern template class ImageRightTurn<ACMYK8_t>;
	extern template class ImageRightTurn<ACMYK16_t>;
	extern template class ImageRightTurn<ACMYK32_t>;
	extern template class ImageRightTurn<ACMYK64_t>;
	extern template class ImageRightTurn<ACMYKI16_t>;
	extern template class ImageRightTurn<ACMYKI32_t>;
	extern template class ImageRightTurn<ACMYKI64_t>;
	extern template class ImageRightTurn<ACMYKF32_t>;
	extern template class ImageRightTurn<ACMYKF64_t>;
	extern template class ImageRightTurn<GrayScale1_t>;
	extern template class ImageRightTurn<GrayScale8_t>;
	extern template class ImageRightTurn<GrayScale16_t>;
	extern template class ImageRightTurn<GrayScale32_t>;
	extern template class ImageRightTurn<GrayScale64_t>;
	extern template class ImageRightTurn<GrayScaleI16_t>;
	extern template class ImageRightTurn<GrayScaleI32_t>;
	extern template class ImageRightTurn<GrayScaleI64_t>;
	extern template class ImageRightTurn<GrayScaleF32_t>;
	extern template class ImageRightTurn<GrayScaleF64_t>;
	extern template class ImageRightTurn<RGB8_t>;
	extern template class ImageRightTurn<RGB16_t>;
	extern template class ImageRightTurn<RGB32_t>;
	extern template class ImageRightTurn<RGB64_t>;
	extern template class ImageRightTurn<RGBI16_t>;
	extern template class ImageRightTurn<RGBI32_t>;
	extern template class ImageRightTurn<RGBI64_t>;
	extern template class ImageRightTurn<RGBF32_t>;
	extern template class ImageRightTurn<RGBF64_t>;
	extern template class ImageRightTurn<ARGB8_t>;
	extern template class ImageRightTurn<ARGB16_t>;
	extern template class ImageRightTurn<ARGB32_t>;
	extern template class ImageRightTurn<ARGB64_t>;
	extern template class ImageRightTurn<ARGBI16_t>;
	extern template class ImageRightTurn<ARGBI32_t>;
	extern template class ImageRightTurn<ARGBI64_t>;
	extern template class ImageRightTurn<ARGBF32_t>;
	extern template class ImageRightTurn<ARGBF64_t>;
	extern template class ImageRightTurn<YUV8_t>;
	extern template class ImageRightTurn<YUV16_t>;
	extern template class ImageRightTurn<YUV32_t>;
	extern template class ImageRightTurn<YUV64_t>;
	extern template class ImageRightTurn<YUVI16_t>;
	extern template class ImageRightTurn<YUVI32_t>;
	extern template class ImageRightTurn<YUVI64_t>;
	extern template class ImageRightTurn<YUVF32_t>;
	extern template class ImageRightTurn<YUVF64_t>;
	extern template class ImageRightTurn<AYUV8_t>;
	extern template class ImageRightTurn<AYUV16_t>;
	extern template class ImageRightTurn<AYUV32_t>;
	extern template class ImageRightTurn<AYUV64_t>;
	extern template class ImageRightTurn<AYUVI16_t>;
	extern template class ImageRightTurn<AYUVI32_t>;
	extern template class ImageRightTurn<AYUVI64_t>;
	extern template class ImageRightTurn<AYUVF32_t>;
	extern template class ImageRightTurn<AYUVF64_t>;

	extern template class ImageLeftTurn<CMY8_t>;
	extern template class ImageLeftTurn<CMY16_t>;
	extern template class ImageLeftTurn<CMY32_t>;
	extern template class ImageLeftTurn<CMY64_t>;
	extern template class ImageLeftTurn<CMYI16_t>;
	extern template class ImageLeftTurn<CMYI32_t>;
	extern template class ImageLeftTurn<CMYI64_t>;
	extern template class ImageLeftTurn<CMYF32_t>;
	extern template class ImageLeftTurn<CMYF64_t>;
	extern template class ImageLeftTurn<ACMY8_t>;
	extern template class ImageLeftTurn<ACMY16_t>;
	extern template class ImageLeftTurn<ACMY32_t>;
	extern template class ImageLeftTurn<ACMY64_t>;
	extern template class ImageLeftTurn<ACMYI16_t>;
	extern template class ImageLeftTurn<ACMYI32_t>;
	extern template class ImageLeftTurn<ACMYI64_t>;
	extern template class ImageLeftTurn<ACMYF32_t>;
	extern template class ImageLeftTurn<ACMYF64_t>;
	extern template class ImageLeftTurn<CMYK8_t>;
	extern template class ImageLeftTurn<CMYK16_t>;
	extern template class ImageLeftTurn<CMYK32_t>;
	extern template class ImageLeftTurn<CMYK64_t>;
	extern template class ImageLeftTurn<CMYKI16_t>;
	extern template class ImageLeftTurn<CMYKI32_t>;
	extern template class ImageLeftTurn<CMYKI64_t>;
	extern template class ImageLeftTurn<CMYKF32_t>;
	extern template class ImageLeftTurn<CMYKF64_t>;
	extern template class ImageLeftTurn<ACMYK8_t>;
	extern template class ImageLeftTurn<ACMYK16_t>;
	extern template class ImageLeftTurn<ACMYK32_t>;
	extern template class ImageLeftTurn<ACMYK64_t>;
	extern template class ImageLeftTurn<ACMYKI16_t>;
	extern template class ImageLeftTurn<ACMYKI32_t>;
	extern template class ImageLeftTurn<ACMYKI64_t>;
	extern template class ImageLeftTurn<ACMYKF32_t>;
	extern template class ImageLeftTurn<ACMYKF64_t>;
	extern template class ImageLeftTurn<GrayScale1_t>;
	extern template class ImageLeftTurn<GrayScale8_t>;
	extern template class ImageLeftTurn<GrayScale16_t>;
	extern template class ImageLeftTurn<GrayScale32_t>;
	extern template class ImageLeftTurn<GrayScale64_t>;
	extern template class ImageLeftTurn<GrayScaleI16_t>;
	extern template class ImageLeftTurn<GrayScaleI32_t>;
	extern template class ImageLeftTurn<GrayScaleI64_t>;
	extern template class ImageLeftTurn<GrayScaleF32_t>;
	extern template class ImageLeftTurn<GrayScaleF64_t>;
	extern template class ImageLeftTurn<RGB8_t>;
	extern template class ImageLeftTurn<RGB16_t>;
	extern template class ImageLeftTurn<RGB32_t>;
	extern template class ImageLeftTurn<RGB64_t>;
	extern template class ImageLeftTurn<RGBI16_t>;
	extern template class ImageLeftTurn<RGBI32_t>;
	extern template class ImageLeftTurn<RGBI64_t>;
	extern template class ImageLeftTurn<RGBF32_t>;
	extern template class ImageLeftTurn<RGBF64_t>;
	extern template class ImageLeftTurn<ARGB8_t>;
	extern template class ImageLeftTurn<ARGB16_t>;
	extern template class ImageLeftTurn<ARGB32_t>;
	extern template class ImageLeftTurn<ARGB64_t>;
	extern template class ImageLeftTurn<ARGBI16_t>;
	extern template class ImageLeftTurn<ARGBI32_t>;
	extern template class ImageLeftTurn<ARGBI64_t>;
	extern template class ImageLeftTurn<ARGBF32_t>;
	extern template class ImageLeftTurn<ARGBF64_t>;
	extern template class ImageLeftTurn<YUV8_t>;
	extern template class ImageLeftTurn<YUV16_t>;
	extern template class ImageLeftTurn<YUV32_t>;
	extern template class ImageLeftTurn<YUV64_t>;
	extern template class ImageLeftTurn<YUVI16_t>;
	extern template class ImageLeftTurn<YUVI32_t>;
	extern template class ImageLeftTurn<YUVI64_t>;
	extern template class ImageLeftTurn<YUVF32_t>;
	extern template class ImageLeftTurn<YUVF64_t>;
	extern template class ImageLeftTurn<AYUV8_t>;
	extern template class ImageLeftTurn<AYUV16_t>;
	extern template class ImageLeftTurn<AYUV32_t>;
	extern template class ImageLeftTurn<AYUV64_t>;
	extern template class ImageLeftTurn<AYUVI16_t>;
	extern template class ImageLeftTurn<AYUVI32_t>;
	extern template class ImageLeftTurn<AYUVI64_t>;
	extern template class ImageLeftTurn<AYUVF32_t>;
	extern template class ImageLeftTurn<AYUVF64_t>;

	extern template class ImageInvertTurn<CMY8_t>;
	extern template class ImageInvertTurn<CMY16_t>;
	extern template class ImageInvertTurn<CMY32_t>;
	extern template class ImageInvertTurn<CMY64_t>;
	extern template class ImageInvertTurn<CMYI16_t>;
	extern template class ImageInvertTurn<CMYI32_t>;
	extern template class ImageInvertTurn<CMYI64_t>;
	extern template class ImageInvertTurn<CMYF32_t>;
	extern template class ImageInvertTurn<CMYF64_t>;
	extern template class ImageInvertTurn<ACMY8_t>;
	extern template class ImageInvertTurn<ACMY16_t>;
	extern template class ImageInvertTurn<ACMY32_t>;
	extern template class ImageInvertTurn<ACMY64_t>;
	extern template class ImageInvertTurn<ACMYI16_t>;
	extern template class ImageInvertTurn<ACMYI32_t>;
	extern template class ImageInvertTurn<ACMYI64_t>;
	extern template class ImageInvertTurn<ACMYF32_t>;
	extern template class ImageInvertTurn<ACMYF64_t>;
	extern template class ImageInvertTurn<CMYK8_t>;
	extern template class ImageInvertTurn<CMYK16_t>;
	extern template class ImageInvertTurn<CMYK32_t>;
	extern template class ImageInvertTurn<CMYK64_t>;
	extern template class ImageInvertTurn<CMYKI16_t>;
	extern template class ImageInvertTurn<CMYKI32_t>;
	extern template class ImageInvertTurn<CMYKI64_t>;
	extern template class ImageInvertTurn<CMYKF32_t>;
	extern template class ImageInvertTurn<CMYKF64_t>;
	extern template class ImageInvertTurn<ACMYK8_t>;
	extern template class ImageInvertTurn<ACMYK16_t>;
	extern template class ImageInvertTurn<ACMYK32_t>;
	extern template class ImageInvertTurn<ACMYK64_t>;
	extern template class ImageInvertTurn<ACMYKI16_t>;
	extern template class ImageInvertTurn<ACMYKI32_t>;
	extern template class ImageInvertTurn<ACMYKI64_t>;
	extern template class ImageInvertTurn<ACMYKF32_t>;
	extern template class ImageInvertTurn<ACMYKF64_t>;
	extern template class ImageInvertTurn<GrayScale1_t>;
	extern template class ImageInvertTurn<GrayScale8_t>;
	extern template class ImageInvertTurn<GrayScale16_t>;
	extern template class ImageInvertTurn<GrayScale32_t>;
	extern template class ImageInvertTurn<GrayScale64_t>;
	extern template class ImageInvertTurn<GrayScaleI16_t>;
	extern template class ImageInvertTurn<GrayScaleI32_t>;
	extern template class ImageInvertTurn<GrayScaleI64_t>;
	extern template class ImageInvertTurn<GrayScaleF32_t>;
	extern template class ImageInvertTurn<GrayScaleF64_t>;
	extern template class ImageInvertTurn<RGB8_t>;
	extern template class ImageInvertTurn<RGB16_t>;
	extern template class ImageInvertTurn<RGB32_t>;
	extern template class ImageInvertTurn<RGB64_t>;
	extern template class ImageInvertTurn<RGBI16_t>;
	extern template class ImageInvertTurn<RGBI32_t>;
	extern template class ImageInvertTurn<RGBI64_t>;
	extern template class ImageInvertTurn<RGBF32_t>;
	extern template class ImageInvertTurn<RGBF64_t>;
	extern template class ImageInvertTurn<ARGB8_t>;
	extern template class ImageInvertTurn<ARGB16_t>;
	extern template class ImageInvertTurn<ARGB32_t>;
	extern template class ImageInvertTurn<ARGB64_t>;
	extern template class ImageInvertTurn<ARGBI16_t>;
	extern template class ImageInvertTurn<ARGBI32_t>;
	extern template class ImageInvertTurn<ARGBI64_t>;
	extern template class ImageInvertTurn<ARGBF32_t>;
	extern template class ImageInvertTurn<ARGBF64_t>;
	extern template class ImageInvertTurn<YUV8_t>;
	extern template class ImageInvertTurn<YUV16_t>;
	extern template class ImageInvertTurn<YUV32_t>;
	extern template class ImageInvertTurn<YUV64_t>;
	extern template class ImageInvertTurn<YUVI16_t>;
	extern template class ImageInvertTurn<YUVI32_t>;
	extern template class ImageInvertTurn<YUVI64_t>;
	extern template class ImageInvertTurn<YUVF32_t>;
	extern template class ImageInvertTurn<YUVF64_t>;
	extern template class ImageInvertTurn<AYUV8_t>;
	extern template class ImageInvertTurn<AYUV16_t>;
	extern template class ImageInvertTurn<AYUV32_t>;
	extern template class ImageInvertTurn<AYUV64_t>;
	extern template class ImageInvertTurn<AYUVI16_t>;
	extern template class ImageInvertTurn<AYUVI32_t>;
	extern template class ImageInvertTurn<AYUVI64_t>;
	extern template class ImageInvertTurn<AYUVF32_t>;
	extern template class ImageInvertTurn<AYUVF64_t>;
}
#endif // __stationaryorbit_graphics_core_imageturn__
