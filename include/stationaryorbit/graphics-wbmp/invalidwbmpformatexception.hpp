#ifndef __stationaryorbit_graphics_dib_invaliddibformatexception_
#define __stationaryorbit_graphics_dib_invaliddibformatexception_
#include "stationaryorbit/exception/soexcept"
namespace zawa_ch::StationaryOrbit::Graphics::DIB
{

	///	Windowsビットマップとしてのアクセスができないデータに対してパースを行おうとした際にスローされる例外。
	class InvalidDIBFormatException
		: public InvalidOperationException
	{
	public:
		explicit InvalidDIBFormatException(const std::string& what_arg);
		explicit InvalidDIBFormatException(const char* what_arg);
	};

}
#endif // __stationaryorbit_graphics_dib_invaliddibformatexception_
