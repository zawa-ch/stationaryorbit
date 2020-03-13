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