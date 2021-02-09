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
		static constexpr DisplayRectSize _size = DisplayRectSize(width, height);
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
			[](const DisplayRectangle& area)
			{
				if ((width < area.Width()) || (height < area.Height())) { throw std::invalid_argument("指定された領域の大きさはこの型が格納できる範囲を超えています。"); }
			} (area);
			for(auto y: area.YRange().GetStdIterator()) for(auto x: area.XRange().GetStdIterator())
			{
				(*this)[DisplayPoint(x-area.Left(), y-area.Top())] = ValueType(source[DisplayPoint(x, y)]);
			}
		}
		template<class fromTcolor>
		PixArray(const Image<fromTcolor>& source, const DisplayPoint& origin) : PixArray(source, DisplayRectangle(origin, _size)) {}
		virtual ~PixArray() = default;

		[[nodiscard]] bool IsReadableAbyss() const noexcept { return false; }

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
			for(auto y: area.Size().YRange().GetStdIterator()) for(auto x: area.Size().XRange().GetStdIterator())
			{
				auto p = DisplayPoint(x, y);
				(*this)[p + destination] = ValueType(source[p + area.Origin()]);
			}
		}

		template<class fromTcolor>
		[[nodiscard]] static PixArray<Tcolor, width, height> Convert(const PixArray<fromTcolor, width, height>& value, const std::function<Tcolor(const fromTcolor&)>& pred)
		{
			PixArray<Tcolor, width, height> result = PixArray<Tcolor, width, height>(value.Size());
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
			if ((point.X() < 0)||(point.Y() < 0)||(_size.Width() <= point.X())||(_size.Height() <= point.Y())) { throw std::out_of_range("指定されたインデックスは境界を超えています。"); }
			return (point.Y() * _size.Width()) + point.X();
		}
	};
}
#endif // __stationaryorbit_graphics_core_pixarray__
