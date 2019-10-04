#include <cstdint>
#include <cstddef>
#ifndef __BITACCESS_HPP__
#define __BITACCESS_HPP__
namespace StationaryOrbit
{

	///	特定のビットへの参照を保持し、ビット単位でのアクセスを行います。
	class BitAccess
	{
	private:

		uint8_t& _ref;
		size_t _pos;

	public:

		BitAccess(uint8_t& reference, size_t bitpos);

		operator bool() const;

		BitAccess& operator =(const bool& value);

	};

}
#endif // __BITACCESS_HPP__