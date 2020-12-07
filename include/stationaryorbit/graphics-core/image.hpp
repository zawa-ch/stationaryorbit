//	stationaryorbit/graphics-core/image
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
#ifndef __stationaryorbit_graphics_core_image__
#define __stationaryorbit_graphics_core_image__
#include "fundamental.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	template<class Tcolor>
	class Image
	{
	public:
		typedef Tcolor ValueType;

		virtual ~Image() = default;

		[[nodiscard]] virtual const RectangleSize& Size() const noexcept = 0;
		[[nodiscard]] virtual DisplayRectangle Area() const noexcept = 0;
		[[nodiscard]] virtual ValueType At(const DisplayPoint& index) const = 0;
		[[nodiscard]] virtual ValueType At(const int& x, const int& y) const { return At(DisplayPoint(x, y)); }

		[[nodiscard]] virtual ValueType operator[](const DisplayPoint& index) const = 0;
	};

	template<class Tcolor>
	class WritableImage : public Image<Tcolor>
	{
	public:
		typedef Tcolor ValueType;

		virtual ~WritableImage() = default;

		[[nodiscard]] virtual ValueType& At(const DisplayPoint& index) = 0;
		[[nodiscard]] virtual ValueType& At(const int& x, const int& y) { return At(DisplayPoint(x, y)); }

		[[nodiscard]] virtual ValueType& operator[](const DisplayPoint& index) = 0;
	};
}
#endif // __stationaryorbit_graphics_core_image__