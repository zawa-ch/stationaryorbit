#include <cstddef>
#ifndef __IELEMENTSET_HPP__
#define __IELEMENTSET_HPP__
namespace StationaryOrbit
{

	template <typename elementT>
	class IElementSet
	{
	public:

		elementT IndexOf(size_t index);

	}

}
#endif // __IELEMENTSET_HPP__