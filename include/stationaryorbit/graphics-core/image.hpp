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
	///	このライブラリで使用される画像を表します。
	///	@param	Tcolor
	///	色の表現に用いる型。
	template<class Tcolor>
	class Image
	{
	public:
		///	色の表現に用いる型。
		typedef Tcolor ValueType;

		virtual ~Image() = default;

		///	領域外ピクセルへの読み込みが可能であるかを取得します。
		[[nodiscard]] virtual bool IsReadableAbyss() const noexcept = 0;

		///	画像領域の大きさを取得します。
		[[nodiscard]] virtual const DisplayRectSize& Size() const noexcept = 0;
		///	画像領域を取得します。
		[[nodiscard]] virtual DisplayRectangle Area() const noexcept = 0;
		///	画像の指定されたピクセルの色を取得します。
		///	@param index
		///	参照する座標位置。
		[[nodiscard]] virtual ValueType At(const DisplayPoint& index) const = 0;
		///	画像の指定されたピクセルの色を取得します。
		///	@param x
		///	参照するx座標。
		///	@param y
		///	参照するy座標。
		[[nodiscard]] virtual ValueType At(const int& x, const int& y) const { return At(DisplayPoint(x, y)); }

		///	画像の指定されたピクセルの色を取得します。
		///	@param index
		///	参照する座標位置。
		[[nodiscard]] virtual ValueType operator[](const DisplayPoint& index) const = 0;
	};

	template<class Tcolor>
	class WritableImage : public Image<Tcolor>
	{
	public:
		typedef Tcolor ValueType;

		virtual ~WritableImage() = default;

		///	画像の指定されたピクセルの色を取得します。
		///	@param index
		///	参照する座標位置。
		[[nodiscard]] virtual ValueType& At(const DisplayPoint& index) = 0;
		///	画像の指定されたピクセルの色を取得します。
		///	@param x
		///	参照するx座標。
		///	@param y
		///	参照するy座標。
		[[nodiscard]] virtual ValueType& At(const int& x, const int& y) { return At(DisplayPoint(x, y)); }

		///	画像の指定されたピクセルの色を取得します。
		///	@param index
		///	参照する座標位置。
		[[nodiscard]] virtual ValueType& operator[](const DisplayPoint& index) = 0;
	};
}
#endif // __stationaryorbit_graphics_core_image__