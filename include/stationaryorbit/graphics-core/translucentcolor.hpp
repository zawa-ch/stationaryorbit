//	stationaryorbit/graphics-core/translucentcolor
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
#ifndef __stationaryorbit_graphics_core_translucentcolor__
#define __stationaryorbit_graphics_core_translucentcolor__
#include "opacity.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	template<class colorT>
	struct TranslucentColor final
	{
	public:
		typedef typename colorT::ValueType::ValueType ValueType;
		typedef colorT ColorType;
		typedef Opacity<typename colorT::ValueType::ValueType> OpacityType;
	private:
		OpacityType _opacity;
		ColorType _color;
	public:
		constexpr TranslucentColor() = default;
		constexpr TranslucentColor(const ColorType& color) : _opacity(OpacityType::Max()), _color(color) {}
		constexpr TranslucentColor(const ColorType& color, const OpacityType& alpha) : _opacity(alpha), _color(color) {}
		constexpr TranslucentColor(const ZeroValue_t&) : _opacity(Zero), _color() {}

		[[nodiscard]] constexpr const OpacityType& Alpha() const { return _opacity; }
		[[nodiscard]] constexpr const ColorType& Color() const { return _color; }

		[[nodiscard]] constexpr bool Equals(const TranslucentColor<colorT>& other) const { return Color().Equals(other.Color()) && Alpha().Equals(other.Alpha()); }
		[[nodiscard]] constexpr bool operator==(const TranslucentColor<colorT>& other) const { return Equals(other); }
		[[nodiscard]] constexpr bool operator!=(const TranslucentColor<colorT>& other) const { return !Equals(other); }
	};
}
#endif // __stationaryorbit_graphics_core_translucentcolor__
