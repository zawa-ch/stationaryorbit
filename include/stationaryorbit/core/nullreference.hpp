//	stationaryorbit/exception/nullreference
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
#ifndef __StationaryOrbit_NullReferenceException__
#define __StationaryOrbit_NullReferenceException__
#include <stdexcept>
namespace zawa_ch::StationaryOrbit
{

	///	無効な参照を逆参照しようとした場合にスローされる例外。
	class NullReferenceException
		: public std::logic_error
	{
	public:

		///	例外の説明を付け、このオブジェクトを初期化します。
		explicit NullReferenceException(const std::string& what_arg) noexcept;

		///	例外の説明を付け、このオブジェクトを初期化します。
		explicit NullReferenceException(const char* what_arg) noexcept;

	};

}
#endif // __StationaryOrbit_NullReferenceException__