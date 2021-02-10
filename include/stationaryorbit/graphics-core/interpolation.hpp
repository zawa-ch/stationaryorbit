//	stationaryorbit/graphics-core/interpolation
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
#ifndef __stationaryorbit_geaphics_core_interpolation__
#define __stationaryorbit_geaphics_core_interpolation__
#include "image.hpp"
#include "pixarray.hpp"
#include "cmycolor.hpp"
#include "cmykcolor.hpp"
#include "grayscalecolor.hpp"
#include "rgbcolor.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	class ImageInterpolation final
	{
		ImageInterpolation() = delete;
		ImageInterpolation(const ImageInterpolation&) = delete;
		ImageInterpolation(ImageInterpolation&&) = delete;
		~ImageInterpolation() = delete;
	public:
		template<class Tcolor>
		static Tcolor NearestNeighbor(const Image<Tcolor>& image, const DisplayPointF& pos)
		{
			return image[pos.Round()];
		}
		template<class Tcolor, std::enable_if_t<ColorTraits::IsColorType<Tcolor> && !ColorTraits::IsTranslucentColorType<Tcolor>, int> = 0>
		static Tcolor Bilinear(const Image<Tcolor>& image, const DisplayPointF& pos)
		{
			typedef typename Tcolor::ValueType::ValueType ChannelType;
			static_assert(ColorTraits::IsColorType<Tcolor>, "指定する型は ColorTraits::IsColorType の要件を満たす必要があります。");
			if (pos == DisplayPointF(pos.Floor())) { return image[pos.Floor()]; }
			auto buffer = PixArray<Tcolor, 2, 2>(image, pos.Floor());
			auto fpos = pos.Extract();
			auto pxup = (buffer.At(DisplayPoint(0, 0)) * ChannelType(1 - fpos.X()) + buffer.At(DisplayPoint(1, 0)) * ChannelType(fpos.X()));
			auto pxdown = (buffer.At(DisplayPoint(0, 1)) * ChannelType(1 - fpos.X()) + buffer.At(DisplayPoint(1, 1)) * ChannelType(fpos.X()));
			return (pxup * ChannelType(1 - fpos.Y()) + pxdown * ChannelType(fpos.Y()));
		}
		template<class Tcolor, std::enable_if_t<ColorTraits::IsTranslucentColorType<Tcolor>, int> = 0>
		static Tcolor Bilinear(const Image<Tcolor>& image, const DisplayPointF& pos)
		{
			typedef typename Tcolor::ValueType::ValueType ChannelType;
			if (pos == DisplayPointF(pos.Floor())) { return image[pos.Floor()]; }
			auto buffer = PixArray<Tcolor, 2, 2>(image, pos.Floor());
			auto fpos = pos.Extract();
			auto apxup = (buffer.At(DisplayPoint(0, 0)).Alpha() * typename Tcolor::OpacityType(ChannelType(1 - fpos.X())) + buffer.At(DisplayPoint(1, 0)).Alpha() * typename Tcolor::OpacityType(ChannelType(fpos.X())));
			auto cpxup = (buffer.At(DisplayPoint(0, 0)).Color() * ChannelType(1 - fpos.X()) + buffer.At(DisplayPoint(1, 0)).Color() * ChannelType(fpos.X()));
			auto apxdown = (buffer.At(DisplayPoint(0, 1)).Alpha() * typename Tcolor::OpacityType(ChannelType(1 - fpos.X())) + buffer.At(DisplayPoint(1, 1)).Alpha() * typename Tcolor::OpacityType(ChannelType(fpos.X())));
			auto cpxdown = (buffer.At(DisplayPoint(0, 1)).Color() * ChannelType(1 - fpos.X()) + buffer.At(DisplayPoint(1, 1)).Color() * ChannelType(fpos.X()));
			return Tcolor(cpxup * ChannelType(1 - fpos.Y()) + cpxdown * ChannelType(fpos.Y()), apxup * typename Tcolor::OpacityType(ChannelType(1 - fpos.Y())) + apxdown * typename Tcolor::OpacityType(ChannelType(fpos.Y())));
		}
	};

	extern template GrayScale1_t ImageInterpolation::NearestNeighbor(const Image<GrayScale1_t>&, const DisplayPointF&);
	extern template GrayScale8_t ImageInterpolation::NearestNeighbor(const Image<GrayScale8_t>&, const DisplayPointF&);
	extern template GrayScale16_t ImageInterpolation::NearestNeighbor(const Image<GrayScale16_t>&, const DisplayPointF&);
	extern template GrayScale32_t ImageInterpolation::NearestNeighbor(const Image<GrayScale32_t>&, const DisplayPointF&);
	extern template GrayScale64_t ImageInterpolation::NearestNeighbor(const Image<GrayScale64_t>&, const DisplayPointF&);
	extern template GrayScaleI16_t ImageInterpolation::NearestNeighbor(const Image<GrayScaleI16_t>&, const DisplayPointF&);
	extern template GrayScaleI32_t ImageInterpolation::NearestNeighbor(const Image<GrayScaleI32_t>&, const DisplayPointF&);
	extern template GrayScaleI64_t ImageInterpolation::NearestNeighbor(const Image<GrayScaleI64_t>&, const DisplayPointF&);
	extern template GrayScaleF32_t ImageInterpolation::NearestNeighbor(const Image<GrayScaleF32_t>&, const DisplayPointF&);
	extern template GrayScaleF64_t ImageInterpolation::NearestNeighbor(const Image<GrayScaleF64_t>&, const DisplayPointF&);
	extern template CMY8_t ImageInterpolation::NearestNeighbor(const Image<CMY8_t>&, const DisplayPointF&);
	extern template CMY16_t ImageInterpolation::NearestNeighbor(const Image<CMY16_t>&, const DisplayPointF&);
	extern template CMY32_t ImageInterpolation::NearestNeighbor(const Image<CMY32_t>&, const DisplayPointF&);
	extern template CMY64_t ImageInterpolation::NearestNeighbor(const Image<CMY64_t>&, const DisplayPointF&);
	extern template CMYI16_t ImageInterpolation::NearestNeighbor(const Image<CMYI16_t>&, const DisplayPointF&);
	extern template CMYI32_t ImageInterpolation::NearestNeighbor(const Image<CMYI32_t>&, const DisplayPointF&);
	extern template CMYI64_t ImageInterpolation::NearestNeighbor(const Image<CMYI64_t>&, const DisplayPointF&);
	extern template CMYF32_t ImageInterpolation::NearestNeighbor(const Image<CMYF32_t>&, const DisplayPointF&);
	extern template CMYF64_t ImageInterpolation::NearestNeighbor(const Image<CMYF64_t>&, const DisplayPointF&);
	extern template ACMY8_t ImageInterpolation::NearestNeighbor(const Image<ACMY8_t>&, const DisplayPointF&);
	extern template ACMY16_t ImageInterpolation::NearestNeighbor(const Image<ACMY16_t>&, const DisplayPointF&);
	extern template ACMY32_t ImageInterpolation::NearestNeighbor(const Image<ACMY32_t>&, const DisplayPointF&);
	extern template ACMY64_t ImageInterpolation::NearestNeighbor(const Image<ACMY64_t>&, const DisplayPointF&);
	extern template ACMYI16_t ImageInterpolation::NearestNeighbor(const Image<ACMYI16_t>&, const DisplayPointF&);
	extern template ACMYI32_t ImageInterpolation::NearestNeighbor(const Image<ACMYI32_t>&, const DisplayPointF&);
	extern template ACMYI64_t ImageInterpolation::NearestNeighbor(const Image<ACMYI64_t>&, const DisplayPointF&);
	extern template ACMYF32_t ImageInterpolation::NearestNeighbor(const Image<ACMYF32_t>&, const DisplayPointF&);
	extern template ACMYF64_t ImageInterpolation::NearestNeighbor(const Image<ACMYF64_t>&, const DisplayPointF&);
	extern template CMYK8_t ImageInterpolation::NearestNeighbor(const Image<CMYK8_t>&, const DisplayPointF&);
	extern template CMYK16_t ImageInterpolation::NearestNeighbor(const Image<CMYK16_t>&, const DisplayPointF&);
	extern template CMYK32_t ImageInterpolation::NearestNeighbor(const Image<CMYK32_t>&, const DisplayPointF&);
	extern template CMYK64_t ImageInterpolation::NearestNeighbor(const Image<CMYK64_t>&, const DisplayPointF&);
	extern template CMYKI16_t ImageInterpolation::NearestNeighbor(const Image<CMYKI16_t>&, const DisplayPointF&);
	extern template CMYKI32_t ImageInterpolation::NearestNeighbor(const Image<CMYKI32_t>&, const DisplayPointF&);
	extern template CMYKI64_t ImageInterpolation::NearestNeighbor(const Image<CMYKI64_t>&, const DisplayPointF&);
	extern template CMYKF32_t ImageInterpolation::NearestNeighbor(const Image<CMYKF32_t>&, const DisplayPointF&);
	extern template CMYKF64_t ImageInterpolation::NearestNeighbor(const Image<CMYKF64_t>&, const DisplayPointF&);
	extern template ACMYK8_t ImageInterpolation::NearestNeighbor(const Image<ACMYK8_t>&, const DisplayPointF&);
	extern template ACMYK16_t ImageInterpolation::NearestNeighbor(const Image<ACMYK16_t>&, const DisplayPointF&);
	extern template ACMYK32_t ImageInterpolation::NearestNeighbor(const Image<ACMYK32_t>&, const DisplayPointF&);
	extern template ACMYK64_t ImageInterpolation::NearestNeighbor(const Image<ACMYK64_t>&, const DisplayPointF&);
	extern template ACMYKI16_t ImageInterpolation::NearestNeighbor(const Image<ACMYKI16_t>&, const DisplayPointF&);
	extern template ACMYKI32_t ImageInterpolation::NearestNeighbor(const Image<ACMYKI32_t>&, const DisplayPointF&);
	extern template ACMYKI64_t ImageInterpolation::NearestNeighbor(const Image<ACMYKI64_t>&, const DisplayPointF&);
	extern template ACMYKF32_t ImageInterpolation::NearestNeighbor(const Image<ACMYKF32_t>&, const DisplayPointF&);
	extern template ACMYKF64_t ImageInterpolation::NearestNeighbor(const Image<ACMYKF64_t>&, const DisplayPointF&);
	extern template RGB8_t ImageInterpolation::NearestNeighbor(const Image<RGB8_t>&, const DisplayPointF&);
	extern template RGB16_t ImageInterpolation::NearestNeighbor(const Image<RGB16_t>&, const DisplayPointF&);
	extern template RGB32_t ImageInterpolation::NearestNeighbor(const Image<RGB32_t>&, const DisplayPointF&);
	extern template RGB64_t ImageInterpolation::NearestNeighbor(const Image<RGB64_t>&, const DisplayPointF&);
	extern template RGBI16_t ImageInterpolation::NearestNeighbor(const Image<RGBI16_t>&, const DisplayPointF&);
	extern template RGBI32_t ImageInterpolation::NearestNeighbor(const Image<RGBI32_t>&, const DisplayPointF&);
	extern template RGBI64_t ImageInterpolation::NearestNeighbor(const Image<RGBI64_t>&, const DisplayPointF&);
	extern template RGBF32_t ImageInterpolation::NearestNeighbor(const Image<RGBF32_t>&, const DisplayPointF&);
	extern template RGBF64_t ImageInterpolation::NearestNeighbor(const Image<RGBF64_t>&, const DisplayPointF&);
	extern template ARGB8_t ImageInterpolation::NearestNeighbor(const Image<ARGB8_t>&, const DisplayPointF&);
	extern template ARGB16_t ImageInterpolation::NearestNeighbor(const Image<ARGB16_t>&, const DisplayPointF&);
	extern template ARGB32_t ImageInterpolation::NearestNeighbor(const Image<ARGB32_t>&, const DisplayPointF&);
	extern template ARGB64_t ImageInterpolation::NearestNeighbor(const Image<ARGB64_t>&, const DisplayPointF&);
	extern template ARGBI16_t ImageInterpolation::NearestNeighbor(const Image<ARGBI16_t>&, const DisplayPointF&);
	extern template ARGBI32_t ImageInterpolation::NearestNeighbor(const Image<ARGBI32_t>&, const DisplayPointF&);
	extern template ARGBI64_t ImageInterpolation::NearestNeighbor(const Image<ARGBI64_t>&, const DisplayPointF&);
	extern template ARGBF32_t ImageInterpolation::NearestNeighbor(const Image<ARGBF32_t>&, const DisplayPointF&);
	extern template ARGBF64_t ImageInterpolation::NearestNeighbor(const Image<ARGBF64_t>&, const DisplayPointF&);
	extern template GrayScale1_t ImageInterpolation::Bilinear(const Image<GrayScale1_t>&, const DisplayPointF&);
	extern template GrayScale8_t ImageInterpolation::Bilinear(const Image<GrayScale8_t>&, const DisplayPointF&);
	extern template GrayScale16_t ImageInterpolation::Bilinear(const Image<GrayScale16_t>&, const DisplayPointF&);
	extern template GrayScale32_t ImageInterpolation::Bilinear(const Image<GrayScale32_t>&, const DisplayPointF&);
	extern template GrayScale64_t ImageInterpolation::Bilinear(const Image<GrayScale64_t>&, const DisplayPointF&);
	extern template GrayScaleI16_t ImageInterpolation::Bilinear(const Image<GrayScaleI16_t>&, const DisplayPointF&);
	extern template GrayScaleI32_t ImageInterpolation::Bilinear(const Image<GrayScaleI32_t>&, const DisplayPointF&);
	extern template GrayScaleI64_t ImageInterpolation::Bilinear(const Image<GrayScaleI64_t>&, const DisplayPointF&);
	extern template GrayScaleF32_t ImageInterpolation::Bilinear(const Image<GrayScaleF32_t>&, const DisplayPointF&);
	extern template GrayScaleF64_t ImageInterpolation::Bilinear(const Image<GrayScaleF64_t>&, const DisplayPointF&);
	extern template CMY8_t ImageInterpolation::Bilinear(const Image<CMY8_t>&, const DisplayPointF&);
	extern template CMY16_t ImageInterpolation::Bilinear(const Image<CMY16_t>&, const DisplayPointF&);
	extern template CMY32_t ImageInterpolation::Bilinear(const Image<CMY32_t>&, const DisplayPointF&);
	extern template CMY64_t ImageInterpolation::Bilinear(const Image<CMY64_t>&, const DisplayPointF&);
	extern template CMYI16_t ImageInterpolation::Bilinear(const Image<CMYI16_t>&, const DisplayPointF&);
	extern template CMYI32_t ImageInterpolation::Bilinear(const Image<CMYI32_t>&, const DisplayPointF&);
	extern template CMYI64_t ImageInterpolation::Bilinear(const Image<CMYI64_t>&, const DisplayPointF&);
	extern template CMYF32_t ImageInterpolation::Bilinear(const Image<CMYF32_t>&, const DisplayPointF&);
	extern template CMYF64_t ImageInterpolation::Bilinear(const Image<CMYF64_t>&, const DisplayPointF&);
	extern template ACMY8_t ImageInterpolation::Bilinear(const Image<ACMY8_t>&, const DisplayPointF&);
	extern template ACMY16_t ImageInterpolation::Bilinear(const Image<ACMY16_t>&, const DisplayPointF&);
	extern template ACMY32_t ImageInterpolation::Bilinear(const Image<ACMY32_t>&, const DisplayPointF&);
	extern template ACMY64_t ImageInterpolation::Bilinear(const Image<ACMY64_t>&, const DisplayPointF&);
	extern template ACMYI16_t ImageInterpolation::Bilinear(const Image<ACMYI16_t>&, const DisplayPointF&);
	extern template ACMYI32_t ImageInterpolation::Bilinear(const Image<ACMYI32_t>&, const DisplayPointF&);
	extern template ACMYI64_t ImageInterpolation::Bilinear(const Image<ACMYI64_t>&, const DisplayPointF&);
	extern template ACMYF32_t ImageInterpolation::Bilinear(const Image<ACMYF32_t>&, const DisplayPointF&);
	extern template ACMYF64_t ImageInterpolation::Bilinear(const Image<ACMYF64_t>&, const DisplayPointF&);
	extern template CMYK8_t ImageInterpolation::Bilinear(const Image<CMYK8_t>&, const DisplayPointF&);
	extern template CMYK16_t ImageInterpolation::Bilinear(const Image<CMYK16_t>&, const DisplayPointF&);
	extern template CMYK32_t ImageInterpolation::Bilinear(const Image<CMYK32_t>&, const DisplayPointF&);
	extern template CMYK64_t ImageInterpolation::Bilinear(const Image<CMYK64_t>&, const DisplayPointF&);
	extern template CMYKI16_t ImageInterpolation::Bilinear(const Image<CMYKI16_t>&, const DisplayPointF&);
	extern template CMYKI32_t ImageInterpolation::Bilinear(const Image<CMYKI32_t>&, const DisplayPointF&);
	extern template CMYKI64_t ImageInterpolation::Bilinear(const Image<CMYKI64_t>&, const DisplayPointF&);
	extern template CMYKF32_t ImageInterpolation::Bilinear(const Image<CMYKF32_t>&, const DisplayPointF&);
	extern template CMYKF64_t ImageInterpolation::Bilinear(const Image<CMYKF64_t>&, const DisplayPointF&);
	extern template ACMYK8_t ImageInterpolation::Bilinear(const Image<ACMYK8_t>&, const DisplayPointF&);
	extern template ACMYK16_t ImageInterpolation::Bilinear(const Image<ACMYK16_t>&, const DisplayPointF&);
	extern template ACMYK32_t ImageInterpolation::Bilinear(const Image<ACMYK32_t>&, const DisplayPointF&);
	extern template ACMYK64_t ImageInterpolation::Bilinear(const Image<ACMYK64_t>&, const DisplayPointF&);
	extern template ACMYKI16_t ImageInterpolation::Bilinear(const Image<ACMYKI16_t>&, const DisplayPointF&);
	extern template ACMYKI32_t ImageInterpolation::Bilinear(const Image<ACMYKI32_t>&, const DisplayPointF&);
	extern template ACMYKI64_t ImageInterpolation::Bilinear(const Image<ACMYKI64_t>&, const DisplayPointF&);
	extern template ACMYKF32_t ImageInterpolation::Bilinear(const Image<ACMYKF32_t>&, const DisplayPointF&);
	extern template ACMYKF64_t ImageInterpolation::Bilinear(const Image<ACMYKF64_t>&, const DisplayPointF&);
	extern template RGB8_t ImageInterpolation::Bilinear(const Image<RGB8_t>&, const DisplayPointF&);
	extern template RGB16_t ImageInterpolation::Bilinear(const Image<RGB16_t>&, const DisplayPointF&);
	extern template RGB32_t ImageInterpolation::Bilinear(const Image<RGB32_t>&, const DisplayPointF&);
	extern template RGB64_t ImageInterpolation::Bilinear(const Image<RGB64_t>&, const DisplayPointF&);
	extern template RGBI16_t ImageInterpolation::Bilinear(const Image<RGBI16_t>&, const DisplayPointF&);
	extern template RGBI32_t ImageInterpolation::Bilinear(const Image<RGBI32_t>&, const DisplayPointF&);
	extern template RGBI64_t ImageInterpolation::Bilinear(const Image<RGBI64_t>&, const DisplayPointF&);
	extern template RGBF32_t ImageInterpolation::Bilinear(const Image<RGBF32_t>&, const DisplayPointF&);
	extern template RGBF64_t ImageInterpolation::Bilinear(const Image<RGBF64_t>&, const DisplayPointF&);
	extern template ARGB8_t ImageInterpolation::Bilinear(const Image<ARGB8_t>&, const DisplayPointF&);
	extern template ARGB16_t ImageInterpolation::Bilinear(const Image<ARGB16_t>&, const DisplayPointF&);
	extern template ARGB32_t ImageInterpolation::Bilinear(const Image<ARGB32_t>&, const DisplayPointF&);
	extern template ARGB64_t ImageInterpolation::Bilinear(const Image<ARGB64_t>&, const DisplayPointF&);
	extern template ARGBI16_t ImageInterpolation::Bilinear(const Image<ARGBI16_t>&, const DisplayPointF&);
	extern template ARGBI32_t ImageInterpolation::Bilinear(const Image<ARGBI32_t>&, const DisplayPointF&);
	extern template ARGBI64_t ImageInterpolation::Bilinear(const Image<ARGBI64_t>&, const DisplayPointF&);
	extern template ARGBF32_t ImageInterpolation::Bilinear(const Image<ARGBF32_t>&, const DisplayPointF&);
	extern template ARGBF64_t ImageInterpolation::Bilinear(const Image<ARGBF64_t>&, const DisplayPointF&);
}
#endif // __stationaryorbit_geaphics_core_interpolation__
