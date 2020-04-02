#ifndef __stationaryorbit_core_endians__
#define __stationaryorbit_core_endians__
#include <type_traits>
#include <array>
#include "stationaryorbit/exception/soexcept"
namespace zawa_ch::StationaryOrbit
{
	///	すべてのスカラー型のエンディアンを表します。
	enum class Endians
	{
		#ifdef _WIN32
			little = 0,
			big    = 1,
			native = little
		#else
			little = __ORDER_LITTLE_ENDIAN__,
			big    = __ORDER_BIG_ENDIAN__,
			native = __BYTE_ORDER__
		#endif
	};
	template<Endians from, Endians dest>
	class EndianConverter final
	{
	public:
		template<class T>
		static constexpr T Convert(const T& value)
		{
			static_assert(std::is_literal_type_v<T>, "テンプレート引数 T はリテラル型である必要があります。");
			if constexpr (from == dest) { return value; }
			if constexpr ((from != dest)&&((from == Endians::little)||(from == Endians::big))&&((dest == Endians::little)||(dest == Endians::big)))
			{
				T result = T();
				for (auto i = 0; i < sizeof(T); i++) { ((uint8_t*)&result)[sizeof(T) - i - 1] = ((uint8_t*)&value)[i]; }
				return result;
			}
			if constexpr ((from != dest)&&(from != Endians::little)&&(from != Endians::big)&&(dest != Endians::little)&&(dest != Endians::big))
			{ throw InvalidOperationException("指定されたエンディアンの適切な変換が存在しません。"); }
		}
	};
	typedef EndianConverter<Endians::native, Endians::little> LittleEndian;
	typedef EndianConverter<Endians::native, Endians::big> BigEndian;
}
#endif // __stationaryorbit_core_endians__