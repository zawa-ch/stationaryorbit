//	stationaryorbit/exception/notimplemented
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
#ifndef __stationaryorbit_exception_notimplemented__
#define __stationaryorbit_exception_notimplemented__
#include <stdexcept>
namespace zawa_ch::StationaryOrbit
{
	///	実装されていない定義を参照した場合に発生する例外。
	class NotImplementedException
		: public std::exception
	{};
}
#endif // __stationaryorbit_exception_notimplemented__