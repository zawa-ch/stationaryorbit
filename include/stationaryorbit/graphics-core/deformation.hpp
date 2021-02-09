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
	///	画像を左右反転します。
	///	@param	Tcolor
	///	色の表現に用いる型。
	template<class Tcolor>
	class ImageHorizonalFlip : public Image<Tcolor>
	{
	public:
		///	色の表現に用いる型。
		typedef Tcolor ValueType;
		///	画像操作を行うための引数型。
		typedef ImageOperationArgs ArgsType;
	private:
		const Image<Tcolor>& _data;
		DisplayPoint _orig;
	public:
		///	オブジェクトを指定してこのオブジェクトを構築します。
		///	@param	source
		///	ソースとなる画像。
		///	@param	args
		///	この画像操作を行うために渡す引数。
		ImageHorizonalFlip(const Image<Tcolor>& source, const ArgsType& args) : _data(source), _orig(1-_data.Area().Right(), _data.Area().Top()) {}
		///	オブジェクトを指定してこのオブジェクトを構築します。
		///	@param	source
		///	ソースとなる画像。
		ImageHorizonalFlip(const Image<Tcolor>& source) : ImageHorizonalFlip(source, ArgsType()) {}

		[[nodiscard]] bool IsReadableAbyss() const noexcept { return _data.IsReadableAbyss(); }

		[[nodiscard]] const DisplayRectSize& Size() const noexcept { return _data.Size(); }
		[[nodiscard]] DisplayRectangle Area() const noexcept { return DisplayRectangle(_orig, _data.Size()); }
		[[nodiscard]] ValueType At(const DisplayPoint& index) const { return _data.At(DisplayPoint(-index.X(), index.Y())); }

		[[nodiscard]] ValueType operator[](const DisplayPoint& index) const { return _data[DisplayPoint(-index.X(), index.Y())]; }
	};
	///	画像を上下反転します。
	///	@param	Tcolor
	///	色の表現に用いる型。
	template<class Tcolor>
	class ImageVerticalFlip : public Image<Tcolor>
	{
	public:
		///	色の表現に用いる型。
		typedef Tcolor ValueType;
		///	画像操作を行うための引数型。
		typedef ImageOperationArgs ArgsType;
	private:
		const Image<Tcolor>& _data;
		DisplayPoint _orig;
	public:
		///	オブジェクトを指定してこのオブジェクトを構築します。
		///	@param	source
		///	ソースとなる画像。
		///	@param	args
		///	この画像操作を行うために渡す引数。
		ImageVerticalFlip(const Image<Tcolor>& source, const ArgsType& args) : _data(source), _orig(_data.Area().Left(), 1-_data.Area().Bottom()) {}
		///	オブジェクトを指定してこのオブジェクトを構築します。
		///	@param	source
		///	ソースとなる画像。
		ImageVerticalFlip(const Image<Tcolor>& source) : ImageVerticalFlip(source, ArgsType()) {}

		[[nodiscard]] bool IsReadableAbyss() const noexcept { return _data.IsReadableAbyss(); }

		[[nodiscard]] const DisplayRectSize& Size() const noexcept { return _data.Size(); }
		[[nodiscard]] DisplayRectangle Area() const noexcept { return DisplayRectangle(_orig, _data.Size()); }
		[[nodiscard]] ValueType At(const DisplayPoint& index) const { return _data.At(DisplayPoint(index.X(), -index.Y())); }

		[[nodiscard]] ValueType operator[](const DisplayPoint& index) const { return _data[DisplayPoint(index.X(), -index.Y())]; }
	};
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
#endif // __stationaryorbit_graphics_core_deformation__