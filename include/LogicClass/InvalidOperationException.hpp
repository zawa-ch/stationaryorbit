#include <stdexcept>
#ifndef __StationaryOrbit_InvalidOperationException__
#define __StationaryOrbit_InvalidOperationException__
namespace StationaryOrbit
{

	class InvalidOperationException
		: public std::logic_error
	{
	public:

		explicit InvalidOperationException(const std::string& what_arg);

		explicit InvalidOperationException(const char* what_arg);

	};

}
#endif // __StationaryOrbit_InvalidOperationException__