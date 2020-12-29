//	stationaryorbit/core/constarray
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
#ifndef __stationaryorbit_core_constarray__
#define __stationaryorbit_core_constarray__
namespace zawa_ch::StationaryOrbit
{
	///	コンパイル時に内容が決定する値の配列を表します。
	template<class T, T ... Values>
	struct ConstArray
	{
	private:
		ConstArray() = delete;
		ConstArray(const ConstArray&) = delete;
		ConstArray(ConstArray&&) = delete;
		~ConstArray() = delete;
	public:
		static constexpr T values[] = { Values ... };

		template<T ... ConcatValues>
		struct Concat
		{
			typedef ConstArray<T, Values..., ConcatValues...> type;
		};
	};
}
#endif // __stationaryorbit_core_constarray__
