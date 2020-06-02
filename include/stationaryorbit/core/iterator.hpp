#ifndef __stationaryorbit_core_iterator__
#define __stationaryorbit_core_iterator__
#include <stdexcept>
#include <utility>
#include <functional>
namespace zawa_ch::StationaryOrbit
{
	template<class T>
	class IIterator
	{
	public:
		typedef T ValueType;
		virtual void Reset() = 0;
		virtual bool HasValue() const = 0;
		virtual const T& Current() const = 0;
		virtual bool Next() = 0;

		void ForEach(const std::function<void(const T&)>& pred)
		{
			Reset();
			while (Next()) { pred(Current()); }
		}
	};
}
#endif // __stationaryorbit_core_iterator__