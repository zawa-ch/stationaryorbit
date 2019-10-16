#ifndef __StationaryOrbit_IElementSet__
#define __StationaryOrbit_IElementSet__
#include <cstddef>
namespace StationaryOrbit
{

	template <typename elementT>
	class IElementSet
	{
	public:

		virtual elementT IndexOf(size_t index) = 0;

	}

}
#endif // __StationaryOrbit_IElementSet__