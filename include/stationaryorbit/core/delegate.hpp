#ifndef __StationaryOrbit_Delegate__
#define __StationaryOrbit_Delegate__
#include <set>
namespace zawa_ch::StationaryOrbit
{

	///	特定の引数を受け取り操作を行うハンドラーの集合を表します。
	template<class ... argsT>
	class Delegate
	{
	public:

		///	この @a Delegate におけるハンドラーの型。
		typedef void (*Action)(argsT ... );

	private:

		std::set<Action> actions;

	public:

		///	このオブジェクトに要素を追加します。
		///	要素がすでにこのオブジェクトに含まれていた場合は何も行いません。
		///
		///	@param	[in]action
		///	追加する @a Action 。
		///
		///	@return
		///	このオブジェクトが返ります。
		constexpr Delegate<argsT...>& Add(Action action) { actions.insert(action); return *this; }
		constexpr Delegate<argsT...>& operator+=(Action action) { return Add(action); }

		///	このオブジェクトから要素を削除します。
		///	要素がこのオブジェクトに含まれていない場合は何も行いません。
		///
		///	@param	[in]action
		///	削除する @a Action 。
		///
		///	@return
		///	このオブジェクトが返ります。
		constexpr Delegate<argsT...>& Remove(Action action) { actions.erase(action); return *this; }
		constexpr Delegate<argsT...>& operator-=(Action action) { return Remove(action); }

		///	このオブジェクトからすべての要素を削除します。
		///
		///	@return
		///	このオブジェクトが返ります。
		constexpr Delegate<argsT...>& Clear() { actions.clear(); return *this; }

		///	このオブジェクトに引数を渡し、ハンドラーを実行します。
		constexpr void Invoke(argsT ... args) const { for(Action item : actions) { item(args...); } }
		constexpr void operator()(argsT ... args) const { Invoke(args...); }

	};

}
#endif // __StationaryOrbit_Delegate__