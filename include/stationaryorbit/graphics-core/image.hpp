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
namespace zawa_ch::StationaryOrbit::Graphics
{
	class Image
	{
	public:
		virtual ~Image() = default;
	public:
		virtual RectangleSize Size() const = 0;
		virtual int Width() const { return Size().Width(); }
		virtual int Height() const{ return Size().Height(); }
		virtual Range<int> XRange() const { return Size().XRange(); }
		virtual Range<int> YRange() const { return Size().YRange(); }
	};
}
#endif // __stationaryorbit_graphics_core_image__