//	stationaryorbit/graphics-core/pixarray
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
#ifndef __stationaryorbit_graphics_core_pixarray__
#define __stationaryorbit_graphics_core_pixarray__
#include <array>
#include "image.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	template<class Tcolor, int width, int height>
	class PixArray : public WritableImage<Tcolor>
	{
		static_assert(0 <= width, "幅は0以上である必要があります。");
		static_assert(0 <= height, "高さは0以上である必要があります。");
	private:
		static constexpr size_t itemcount = width * height;
		static constexpr RectangleSize _size = RectangleSize(width, height);
	public:
		typedef Tcolor ValueType;
		typedef std::array<ValueType, itemcount> DataType;
	private:
		DataType _data;
	public:
		PixArray() = default;
		template<class fromTcolor>
		PixArray(const Image<fromTcolor>& source, const DisplayRectangle& area) : _data()
		{
			if ((area.Left() < 0)||(area.Top() < 0)||(source.Size().Width() <= area.Right())||(source.Size().Height() <= area.Bottom()))
			{ throw std::out_of_range("指定された領域は境界を超えています。"); }
			for(auto y: area.YRange().GetStdIterator()) for(auto x: area.XRange().GetStdIterator())
			{
				(*this)[DisplayPoint(x-area.Left(), y-area.Top())] = ValueType(source[DisplayPoint(x, y)]);
			}
		}
		template<class fromTcolor>
		PixArray(const Image<fromTcolor>& source, const DisplayPoint& origin) : PixArray(source, DisplayRectangle(origin, _size)) {}
		virtual ~PixArray() = default;

		[[nodiscard]] const DataType& Data() const noexcept { return _data; }
		[[nodiscard]] const RectangleSize& Size() const noexcept { return _size; }
		[[nodiscard]] DisplayRectangle Area() const noexcept { return Rectangle(DisplayPoint(0, 0), _size); }

		[[nodiscard]] ValueType At(const DisplayPoint& index) const { return _data.at(solveindex(index)); }
		[[nodiscard]] ValueType& At(const DisplayPoint& index) { return _data.at(solveindex(index)); }

		[[nodiscard]] ValueType operator[](const DisplayPoint& index) const { return _data[solveindex(index)]; }
		[[nodiscard]] ValueType& operator[](const DisplayPoint& index) { return _data[solveindex(index)]; }

		template<class fromTcolor = Tcolor>
		void Copy(const Image<fromTcolor>& source, const DisplayRectangle& area, const DisplayPoint& destination = DisplayPoint(Zero, Zero))
		{
			if ((0 < area.Left())||(0 < area.Top())||(area.Right() <= source.Size().Width())||(area.Bottom() <= source.Size().Height()))
			{ throw std::invalid_argument("コピー指定された領域はコピー元の境界を超えています。"); }
			auto destarea = DisplayRectangle(destination, area.Size());
			if ((0 < destarea.Left())||(0 < destarea.Top())||(destarea.Right() <= Size().Width())||(destarea.Bottom() <= Size().Height()))
			{ throw std::out_of_range("コピー指定された領域はコピー先の領域を超えています。"); }
			for(auto y: area.Size().YRange().GetStdIterator()) for(auto x: area.Size().XRange().GetStdIterator())
			{
				auto p = DisplayPoint(x, y);
				(*this)[p + destination] = ValueType(source[p + area.Location()]);
			}
		}

		template<class fromTcolor>
		[[nodiscard]] static PixArray<Tcolor, width, height> Convert(const PixArray<fromTcolor, width, height>& value, const std::function<Tcolor(const fromTcolor&)>& pred)
		{
			PixArray<Tcolor, width, height> result = PixArray<Tcolor, width, height>(value.Size());
			auto di = result.Data().begin();
			auto si = value.Data().cbegin();
			auto de = result.Data().end();
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
	};
}
#endif // __stationaryorbit_graphics_core_pixarray__