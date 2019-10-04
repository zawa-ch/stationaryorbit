#include <cstddef>
#ifndef __IELEMENTSET_HPP__
#define __IELEMENTSET_HPP__
namespace StationaryOrbit
{

	template <typename elementT>
	class IElementSet
	{
	public:

		virtual elementT IndexOf(size_t index) = 0;

	}

}
#endif // __IELEMENTSET_HPP__