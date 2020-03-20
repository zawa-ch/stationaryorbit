#ifndef __stationaryorbit_graphics_wbmp_invalidwbmpformatexception_
#define __stationaryorbit_graphics_wbmp_invalidwbmpformatexception_
#include "stationaryorbit/exception/soexcept"
namespace zawa_ch::StationaryOrbit::Graphics::WBMP
{

	///	Windowsビットマップとしてのアクセスができないデータに対してパースを行おうとした際にスローされる例外。
	class InvalidWbmpFormatException
		: public InvalidOperationException
	{
	public:
		explicit InvalidWbmpFormatException(const std::string& what_arg);
		explicit InvalidWbmpFormatException(const char* what_arg);
	};

}
#endif // __stationaryorbit_graphics_wbmp_invalidwbmpformatexception_