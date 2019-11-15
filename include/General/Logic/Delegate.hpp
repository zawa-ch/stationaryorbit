#ifndef __StationaryOrbit_Delegate__
#define __StationaryOrbit_Delegate__
#include <set>
namespace StationaryOrbit
{

	template<class ... argsT>
	class Delegate
	{
	public:

		typedef void (*Action)(argsT ... );

	private:

		std::set<Action> actions;

	public:

		void Add(Action action) { actions.insert(action); }

		void Remove(Action action) { actions.erase(action); }

		void Clear() { actions.clear(); }

		void Invoke(argsT ... args) const { for(Action item : actions) { item(args...); } }

	};

}
#endif // __StationaryOrbit_Delegate__