//	stationaryorbit/core/fundamental
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
#ifndef __stationaryorbit_core_fundamental__
#define __stationaryorbit_core_fundamental__
#include <cstdint>
namespace zawa_ch::StationaryOrbit
{
	///	対応する値が存在しない型を表します。
	struct Unit final {};
	///	@a Unit の唯一のインスタンスを表します。
	static constexpr Unit UnitValue = {};

	///	決してインスタンス化することのできない型を表します。
	typedef void Bottom;

	//	<-- C++基本型に対して与えられる型エイリアスの定義 -->

	typedef float float32_t;
	typedef double float64_t;
	typedef long double floatmax_t;
}
#endif // __stationaryorbit_core_fundamental__
