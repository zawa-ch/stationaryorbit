//	stationaryorbit/core/delegate
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
#ifndef __StationaryOrbit_Delegate__
#define __StationaryOrbit_Delegate__
#include <map>
#include <functional>
namespace zawa_ch::StationaryOrbit
{

	///	特定の引数を受け取り操作を行うハンドラーの集合を表します。
	template<class ... argsT>
	class Delegate
	{
	public:

		///	この @a Delegate におけるハンドラーの型。
		typedef std::function<void(const argsT&...)> Action;

	private:

		std::map<void*, Action> actions;

	public:

		///	このオブジェクトに要素を追加します。
		///	要素がすでにこのオブジェクトに含まれていた場合は何も行いません。
		///
		///	@param	action
		///	追加する @a Action 。
		void Add(Action action) { actions.insert(std::pair{action.template target<void*>(), action}); }
		Delegate<argsT...>& operator+=(Action action) { Add(action); return *this; }

		///	このオブジェクトから要素を削除します。
		///	要素がこのオブジェクトに含まれていない場合は何も行いません。
		///
		///	@param	action
		///	削除する @a Action 。
		void Remove(Action action) { actions.erase(action.template target<void*>()); }
		Delegate<argsT...>& operator-=(Action action) { Remove(action); return *this; }

		///	このオブジェクトからすべての要素を削除します。
		void Clear() { actions.clear(); }

		///	このオブジェクトに引数を渡し、ハンドラーを実行します。
		void Invoke(argsT ... args) const { for(auto item : actions) { item.second(args...); } }
		void operator()(argsT ... args) const { Invoke(args...); }

	};

}
#endif // __StationaryOrbit_Delegate__