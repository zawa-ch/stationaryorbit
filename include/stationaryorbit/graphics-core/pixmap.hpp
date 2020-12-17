//	stationaryorbit/graphics-core/pixmap
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
#ifndef __stationaryorbit_graphics_core_pixmap__
#define __stationaryorbit_graphics_core_pixmap__
#include <vector>
#include "stationaryorbit/core.numeral.hpp"
#include "fundamental.hpp"
#include "relativecolor.hpp"
#include "grayscalecolor.hpp"
#include "rgbcolor.hpp"
#include "cmycolor.hpp"
#include "cmykcolor.hpp"
#include "opacity.hpp"
#include "image.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	template<class Tcolor, class Allocator = typename std::vector<Tcolor>::allocator_type>
	class Pixmap : public WritableImage<Tcolor>
	{
	public:
		typedef Tcolor ValueType;
		typedef std::vector<ValueType, Allocator> DataType;
	private:
		DataType _data;
		DisplayRectSize _size;
	public:
		Pixmap() = default;
		explicit Pixmap(const DisplayRectSize& size) : _size(size), _data(solveItemcount(size)) {}
		Pixmap(const int& width, const int& height) : Pixmap(DisplayRectSize(width, height)) {}
		Pixmap(const Pixmap<Tcolor, Allocator>& source, const DisplayRectangle& area)
			: Pixmap
			(
				// areaで指定された領域がsourceの境界を超えていないか検査、境界を超えていなければareaの大きさ(DisplayRectSize)を返す
				[](const DisplayRectangle& bound, const DisplayRectangle& area) -> DisplayRectSize
				{
					if ((area.Left() < bound.Left())||(area.Top() < bound.Top())||(bound.Right() < area.Right())||(bound.Bottom() < area.Bottom()))
					{ throw std::out_of_range("指定された領域は境界を超えています。"); }
					else { return area.Size(); }
				}(source.Area(), area)
			)
		{
			for(auto y: area.YRange().GetStdIterator()) for(auto x: area.XRange().GetStdIterator())
			{
				(*this)[DisplayPoint(x-area.Left(), y-area.Top())] = source[DisplayPoint(x, y)];
			}
		}
		template<class fromTcolor, class fromAllocator>
		explicit Pixmap(const Pixmap<fromTcolor, fromAllocator>& from) : _size(from.Size()), _data(solveItemcount(from.Size()))
		{
			auto di = _data.begin();
			auto si = from.Data().cbegin();
			auto de = _data.end();
			auto se = from.Data().cend();
			while((di != de)&&(si != se))
			{
				*di = ValueType(*si);
				++di;
				++si;
			}
		}
		template<class fromTcolor>
		Pixmap(const Image<fromTcolor>& source, const DisplayRectangle& area)
			: Pixmap
			(
				// areaで指定された領域がsourceの境界を超えていないか検査、境界を超えていなければareaの大きさ(DisplayRectSize)を返す
				[](const DisplayRectangle& bound, const DisplayRectangle& area) -> DisplayRectSize
				{
					if ((area.Left() < bound.Left())||(area.Top() < bound.Top())||(bound.Right() < area.Right())||(bound.Bottom() < area.Bottom()))
					{ throw std::out_of_range("指定された領域は境界を超えています。"); }
					else { return area.Size(); }
				}(source.Area(), area)
			)
		{
			for(auto y: area.YRange().GetStdIterator()) for(auto x: area.XRange().GetStdIterator())
			{
				(*this)[DisplayPoint(x-area.Left(), y-area.Top())] = ValueType(source[DisplayPoint(x, y)]);
			}
		}
		virtual ~Pixmap() = default;

		[[nodiscard]] const DataType& Data() const noexcept { return _data; }
		[[nodiscard]] const DisplayRectSize& Size() const noexcept { return _size; }
		[[nodiscard]] DisplayRectangle Area() const noexcept { return DisplayRectangle(DisplayPoint(0, 0), _size); }

		[[nodiscard]] ValueType At(const DisplayPoint& index) const { return _data.at(solveindex(index)); }
		[[nodiscard]] ValueType& At(const DisplayPoint& index) { return _data.at(solveindex(index)); }

		[[nodiscard]] ValueType operator[](const DisplayPoint& index) const { return _data[solveindex(index)]; }
		[[nodiscard]] ValueType& operator[](const DisplayPoint& index) { return _data[solveindex(index)]; }

		template<class fromTcolor = Tcolor>
		void Copy(const Image<fromTcolor>& source, const DisplayRectangle& area, const DisplayPoint& destination = DisplayPoint(Zero, Zero))
		{
			if ((area.Left() < source.Area().Left())||(area.Top() < source.Area().Top())||(source.Area().Right() < area.Right())||(source.Area().Bottom() < area.Bottom()))
			{ throw std::invalid_argument("コピー指定された領域はコピー元の境界を超えています。"); }
			auto destarea = DisplayRectangle(destination, area.Size());
			if ((0 < destarea.Left())||(0 < destarea.Top())||(destarea.Right() < Size().Width())||(destarea.Bottom() < Size().Height()))
			{ throw std::out_of_range("コピー指定された領域はコピー先の領域を超えています。"); }
			for(auto y: area.Size().YRange().GetStdIterator()) for(auto x: area.Size().XRange().GetStdIterator())
			{
				auto p = DisplayPoint(x, y);
				(*this)[p + destination] = ValueType(source[p + area.Origin()]);
			}
		}

		template<class fromTcolor, class fromAllocator>
		[[nodiscard]] static Pixmap<Tcolor, Allocator> Convert(const Pixmap<fromTcolor, fromAllocator>& value, const std::function<Tcolor(const fromTcolor&)>& pred)
		{
			Pixmap<Tcolor, Allocator> result = Pixmap<Tcolor, Allocator>(value.Size());
			auto di = result._data.begin();
			auto si = value.Data().cbegin();
			auto de = result._data.end();
			auto se = value.Data().cend();
			while((di != de)&&(si != se))
			{
				*di = pred(*si);
				++di;
				++si;
			}
			return result;
		}

	private:
		size_t solveindex(const DisplayPoint& point) const
		{
			if ((point.X() < 0)||(point.Y() < 0)) { throw std::invalid_argument("pointの値が無効です。"); }
			if ((_size.Width() <= point.X())||(_size.Height() <= point.Y())) { throw std::out_of_range("指定されたインデックスは境界を超えています。"); }
			return (point.Y() * _size.Width()) + point.X();
		}
		static size_t solveItemcount(const DisplayRectSize& size)
		{
			if ((size.Height() < 0)||(size.Width() < 0)) { throw std::invalid_argument("sizeの値が無効です。"); }
			return size_t(size.Height()) * size_t(size.Width());
		}
	};

	typedef Pixmap<Opacity1_t> Mask1Pixmap_t;
	typedef Pixmap<Opacity8_t> Mask8Pixmap_t;
	typedef Pixmap<Opacity16_t> Mask16Pixmap_t;
	typedef Pixmap<Opacity32_t> Mask32Pixmap_t;
	typedef Pixmap<Opacity64_t> Mask64Pixmap_t;
	typedef Pixmap<OpacityI16_t> MaskI16Pixmap_t;
	typedef Pixmap<OpacityI32_t> MaskI32Pixmap_t;
	typedef Pixmap<OpacityI64_t> MaskI64Pixmap_t;
	typedef Pixmap<OpacityF32_t> MaskF32Pixmap_t;
	typedef Pixmap<OpacityF64_t> MaskF64Pixmap_t;
	typedef Pixmap<GrayScale1_t> Gray1Pixmap_t;
	typedef Pixmap<GrayScale8_t> Gray8Pixmap_t;
	typedef Pixmap<GrayScale16_t> Gray16Pixmap_t;
	typedef Pixmap<GrayScale32_t> Gray32Pixmap_t;
	typedef Pixmap<GrayScale64_t> Gray64Pixmap_t;
	typedef Pixmap<GrayScaleI16_t> GrayI16Pixmap_t;
	typedef Pixmap<GrayScaleI32_t> GrayI32Pixmap_t;
	typedef Pixmap<GrayScaleI64_t> GrayI64Pixmap_t;
	typedef Pixmap<GrayScaleF32_t> GrayF32Pixmap_t;
	typedef Pixmap<GrayScaleF64_t> GrayF64Pixmap_t;
	typedef Pixmap<RGB8_t> RGB8Pixmap_t;
	typedef Pixmap<RGB16_t> RGB16Pixmap_t;
	typedef Pixmap<RGB32_t> RGB32Pixmap_t;
	typedef Pixmap<RGB64_t> RGB64Pixmap_t;
	typedef Pixmap<RGBI16_t> RGBI16Pixmap_t;
	typedef Pixmap<RGBI32_t> RGBI32Pixmap_t;
	typedef Pixmap<RGBI64_t> RGBI64Pixmap_t;
	typedef Pixmap<RGBF32_t> RGBF32Pixmap_t;
	typedef Pixmap<RGBF64_t> RGBF64Pixmap_t;
	typedef Pixmap<ARGB8_t> ARGB8Pixmap_t;
	typedef Pixmap<ARGB16_t> ARGB16Pixmap_t;
	typedef Pixmap<ARGB32_t> ARGB32Pixmap_t;
	typedef Pixmap<ARGB64_t> ARGB64Pixmap_t;
	typedef Pixmap<ARGBI16_t> ARGBI16Pixmap_t;
	typedef Pixmap<ARGBI32_t> ARGBI32Pixmap_t;
	typedef Pixmap<ARGBI64_t> ARGBI64Pixmap_t;
	typedef Pixmap<ARGBF32_t> ARGBF32Pixmap_t;
	typedef Pixmap<ARGBF64_t> ARGBF64Pixmap_t;
	typedef Pixmap<CMY8_t> CMY8Pixmap_t;
	typedef Pixmap<CMY16_t> CMY16Pixmap_t;
	typedef Pixmap<CMY32_t> CMY32Pixmap_t;
	typedef Pixmap<CMY64_t> CMY64Pixmap_t;
	typedef Pixmap<CMYI16_t> CMYI16Pixmap_t;
	typedef Pixmap<CMYI32_t> CMYI32Pixmap_t;
	typedef Pixmap<CMYI64_t> CMYI64Pixmap_t;
	typedef Pixmap<CMYF32_t> CMYF32Pixmap_t;
	typedef Pixmap<CMYF64_t> CMYF64Pixmap_t;
	typedef Pixmap<ACMY8_t> ACMY8Pixmap_t;
	typedef Pixmap<ACMY16_t> ACMY16Pixmap_t;
	typedef Pixmap<ACMY32_t> ACMY32Pixmap_t;
	typedef Pixmap<ACMY64_t> ACMY64Pixmap_t;
	typedef Pixmap<ACMYI16_t> ACMYI16Pixmap_t;
	typedef Pixmap<ACMYI32_t> ACMYI32Pixmap_t;
	typedef Pixmap<ACMYI64_t> ACMYI64Pixmap_t;
	typedef Pixmap<ACMYF32_t> ACMYF32Pixmap_t;
	typedef Pixmap<ACMYF64_t> ACMYF64Pixmap_t;
	typedef Pixmap<CMYK8_t> CMYK8Pixmap_t;
	typedef Pixmap<CMYK16_t> CMYK16Pixmap_t;
	typedef Pixmap<CMYK32_t> CMYK32Pixmap_t;
	typedef Pixmap<CMYK64_t> CMYK64Pixmap_t;
	typedef Pixmap<CMYKI16_t> CMYKI16Pixmap_t;
	typedef Pixmap<CMYKI32_t> CMYKI32Pixmap_t;
	typedef Pixmap<CMYKI64_t> CMYKI64Pixmap_t;
	typedef Pixmap<CMYKF32_t> CMYKF32Pixmap_t;
	typedef Pixmap<CMYKF64_t> CMYKF64Pixmap_t;
	typedef Pixmap<ACMYK8_t> ACMYK8Pixmap_t;
	typedef Pixmap<ACMYK16_t> ACMYK16Pixmap_t;
	typedef Pixmap<ACMYK32_t> ACMYK32Pixmap_t;
	typedef Pixmap<ACMYK64_t> ACMYK64Pixmap_t;
	typedef Pixmap<ACMYKI16_t> ACMYKI16Pixmap_t;
	typedef Pixmap<ACMYKI32_t> ACMYKI32Pixmap_t;
	typedef Pixmap<ACMYKI64_t> ACMYKI64Pixmap_t;
	typedef Pixmap<ACMYKF32_t> ACMYKF32Pixmap_t;
	typedef Pixmap<ACMYKF64_t> ACMYKF64Pixmap_t;

	extern template class Pixmap<Opacity8_t>;
	extern template class Pixmap<Opacity16_t>;
	extern template class Pixmap<Opacity32_t>;
	extern template class Pixmap<Opacity64_t>;
	extern template class Pixmap<OpacityI16_t>;
	extern template class Pixmap<OpacityI32_t>;
	extern template class Pixmap<OpacityI64_t>;
	extern template class Pixmap<OpacityF32_t>;
	extern template class Pixmap<OpacityF64_t>;
	extern template class Pixmap<GrayScale8_t>;
	extern template class Pixmap<GrayScale16_t>;
	extern template class Pixmap<GrayScale32_t>;
	extern template class Pixmap<GrayScale64_t>;
	extern template class Pixmap<GrayScaleI16_t>;
	extern template class Pixmap<GrayScaleI32_t>;
	extern template class Pixmap<GrayScaleI64_t>;
	extern template class Pixmap<GrayScaleF32_t>;
	extern template class Pixmap<GrayScaleF64_t>;
	extern template class Pixmap<RGB8_t>;
	extern template class Pixmap<RGB16_t>;
	extern template class Pixmap<RGB32_t>;
	extern template class Pixmap<RGB64_t>;
	extern template class Pixmap<RGBI16_t>;
	extern template class Pixmap<RGBI32_t>;
	extern template class Pixmap<RGBI64_t>;
	extern template class Pixmap<RGBF32_t>;
	extern template class Pixmap<RGBF64_t>;
	extern template class Pixmap<ARGB8_t>;
	extern template class Pixmap<ARGB16_t>;
	extern template class Pixmap<ARGB32_t>;
	extern template class Pixmap<ARGB64_t>;
	extern template class Pixmap<ARGBI16_t>;
	extern template class Pixmap<ARGBI32_t>;
	extern template class Pixmap<ARGBI64_t>;
	extern template class Pixmap<ARGBF32_t>;
	extern template class Pixmap<ARGBF64_t>;
	extern template class Pixmap<CMY8_t>;
	extern template class Pixmap<CMY16_t>;
	extern template class Pixmap<CMY32_t>;
	extern template class Pixmap<CMY64_t>;
	extern template class Pixmap<CMYI16_t>;
	extern template class Pixmap<CMYI32_t>;
	extern template class Pixmap<CMYI64_t>;
	extern template class Pixmap<CMYF32_t>;
	extern template class Pixmap<CMYF64_t>;
	extern template class Pixmap<ACMY8_t>;
	extern template class Pixmap<ACMY16_t>;
	extern template class Pixmap<ACMY32_t>;
	extern template class Pixmap<ACMY64_t>;
	extern template class Pixmap<ACMYI16_t>;
	extern template class Pixmap<ACMYI32_t>;
	extern template class Pixmap<ACMYI64_t>;
	extern template class Pixmap<ACMYF32_t>;
	extern template class Pixmap<ACMYF64_t>;
	extern template class Pixmap<CMYK8_t>;
	extern template class Pixmap<CMYK16_t>;
	extern template class Pixmap<CMYK32_t>;
	extern template class Pixmap<CMYK64_t>;
	extern template class Pixmap<CMYKI16_t>;
	extern template class Pixmap<CMYKI32_t>;
	extern template class Pixmap<CMYKI64_t>;
	extern template class Pixmap<CMYKF32_t>;
	extern template class Pixmap<CMYKF64_t>;
	extern template class Pixmap<ACMYK8_t>;
	extern template class Pixmap<ACMYK16_t>;
	extern template class Pixmap<ACMYK32_t>;
	extern template class Pixmap<ACMYK64_t>;
	extern template class Pixmap<ACMYKI16_t>;
	extern template class Pixmap<ACMYKI32_t>;
	extern template class Pixmap<ACMYKI64_t>;
	extern template class Pixmap<ACMYKF32_t>;
	extern template class Pixmap<ACMYKF64_t>;
}
#endif // __stationaryorbit_graphics_core_pixmap__
