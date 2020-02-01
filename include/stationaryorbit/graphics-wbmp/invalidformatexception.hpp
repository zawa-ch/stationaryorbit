#ifndef __StationaryOrbit_Graphics_BMP_InvalidFormatException__
#define __StationaryOrbit_Graphics_BMP_InvalidFormatException__
#include <stdexcept>
namespace StationaryOrbit::Graphics::BMP
{

	///	BMPへの変換ができないデータに対してパースを行おうとした際にスローされる例外。
	class InvalidFormatException
		: public std::logic_error
	{
	public:

		explicit InvalidFormatException(const std::string& what_arg);

		explicit InvalidFormatException(const char* what_arg);

	};

}
#endif // __StationaryOrbit_Graphics_BMP_InvalidFormatException__