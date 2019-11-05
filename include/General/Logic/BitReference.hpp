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

		std::byte& _ref;	///< 参照先の1バイトビット列。
		size_t _pos;	///< 参照先のビット位置。

	public:

		///	特定のビットへの参照を作成します。
		BitReference(std::byte& reference, size_t bitpos);

		///	ビット参照の逆参照を行い、boolに変換します。
		operator bool() const;

		///	参照先に値を代入します。
		BitReference& operator=(const bool& value);

	};

}
#endif // __StationaryOrbit_BitReference__