#ifndef __StationaryOrbit_BitReference__
#define __StationaryOrbit_BitReference__
#include <cstdint>
#include <cstddef>
#include <stdexcept>
namespace StationaryOrbit
{

	///	特定のビットへの参照を保持し、ビット単位でのアクセスを行います。
	class BitReference
	{
	private:

		uint8_t& _ref;	///< 参照先の1バイトビット列。
		size_t _pos;	///< 参照先のビット位置。

	public:

		///	特定のビットへの参照を作成します。
		BitReference(uint8_t& reference, size_t bitpos);

		operator bool() const;

		BitReference& operator=(const bool& value);

	};

}
#endif // __StationaryOrbit_BitReference__