#ifndef __StationaryOrbit_BitReference__
#define __StationaryOrbit_BitReference__
#include <cstdint>
#include <cstddef>
namespace StationaryOrbit
{

	///	特定のビットへの参照を保持し、ビット単位でのアクセスを行います。
	class BitReference
	{
	private:

		uint8_t& _ref;
		size_t _pos;

	public:

		BitReference(uint8_t& reference, size_t bitpos);

		operator bool() const;

		BitReference& operator =(const bool& value);

	};

}
#endif // __StationaryOrbit_BitReference__