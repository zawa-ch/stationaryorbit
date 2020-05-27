#ifndef __stationaryorbit_core_bitreference__
#define __stationaryorbit_core_bitreference__
#include <cstddef>
#include <stdexcept>
namespace zawa_ch::StationaryOrbit
{
	///	特定のビットへの参照を保持し、ビット単位でのアクセスを行います。
	class BitReference
	{
	private:
		std::byte& _ref;	///< 参照先の1バイトビット列。
		size_t _pos;	///< 参照先のビット位置。
	public:
		///	特定のビットへの参照を作成します。
		constexpr BitReference(std::byte& reference, const size_t& bitpos) : _ref(reference), _pos(bitpos) { if (8 <= bitpos) throw std::out_of_range("bitpos は0から7の範囲内である必要があります。"); }
		///	このオブジェクトが参照しているstd::byteの参照を取得します。
		constexpr std::byte& getByte() { return _ref; }
		///	ビット参照の逆参照を行い、boolに変換します。
		constexpr bool getValue() const { return (_ref & std::byte(0x01 << _pos)) != std::byte(0); }
		constexpr operator bool() const { return getValue(); }
		///	参照先に値を代入します。
		constexpr BitReference& Assign(const bool& value)
		{
			_ref = (_ref & std::byte(~(0x01 << _pos))) | std::byte(value & (0x01 << _pos));
			return *this;
		}
		constexpr BitReference& operator=(const bool& value) { return Assign(value); }
	};

}
#endif // __stationaryorbit_core_bitreference__