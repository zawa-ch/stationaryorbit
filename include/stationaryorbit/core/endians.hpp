#ifndef __stationaryorbit_core_endians__
#define __stationaryorbit_core_endians__
#include <cstdint>
#include <type_traits>
#include <array>
#include "stationaryorbit/exception.hpp"
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

	///	特定のバイトオーダーで格納されることが保証されているスカラー型を表します。
	template<class Tp, Endians order = Endians::native>
	struct EndianValueType final
	{
		static_assert(std::is_literal_type_v<Tp>, "テンプレート引数 Tp はリテラル型である必要があります。");
	public:
		typedef Tp ValueType;
		static constexpr Endians Endian = order;
	private:
		Tp _value;
	public:
		constexpr EndianValueType() : _value() {}
		constexpr EndianValueType(const Tp& value) : _value(EndianConverter<Endians::native, order>::Convert(value)) {}
		template<Endians from>
		constexpr EndianValueType(const EndianValueType<Tp, from>& value) : _value(EndianConverter<from, order>::Convert(value._value)) {}
		constexpr operator Tp() const { return EndianConverter<Endians::native, order>::Convert(_value); }
		constexpr EndianValueType<Tp, order> operator++(int _) const { return EndianValueType(Tp(_value)++); }
		constexpr EndianValueType<Tp, order>& operator++() { return *this = (*this)++; }
		constexpr EndianValueType<Tp, order> operator--(int _) const { return EndianValueType(Tp(_value)--); }
		constexpr EndianValueType<Tp, order>& operator--() { return *this = (*this)--; }
		constexpr EndianValueType<Tp, order> operator+(const EndianValueType<Tp>& other) const { return EndianValueType(Tp(_value) + Tp(other._value)); }
		constexpr EndianValueType<Tp, order> operator+(const Tp& other) const { return EndianValueType(Tp(_value) + other); }
		constexpr EndianValueType<Tp, order>& operator+=(const EndianValueType<Tp, order>& other) { *this = *this + other; }
		constexpr EndianValueType<Tp, order>& operator+=(const Tp& other) { *this = *this + other; }
		constexpr EndianValueType<Tp, order> operator-(const EndianValueType<Tp, order>& other) const { return EndianValueType(Tp(_value) - Tp(other._value)); }
		constexpr EndianValueType<Tp, order> operator-(const Tp& other) const { return EndianValueType(Tp(_value) - other); }
		constexpr EndianValueType<Tp, order>& operator-=(const EndianValueType<Tp, order>& other) { *this = *this - other; }
		constexpr EndianValueType<Tp, order>& operator-=(const Tp& other) { *this = *this - other; }
		constexpr EndianValueType<Tp, order> operator*(const EndianValueType<Tp, order>& other) const { return EndianValueType(Tp(_value) * Tp(other._value)); }
		constexpr EndianValueType<Tp, order> operator*(const Tp& other) const { return EndianValueType(Tp(_value) * other); }
		constexpr EndianValueType<Tp, order>& operator*=(const EndianValueType<Tp, order>& other) { *this = *this * other; }
		constexpr EndianValueType<Tp, order>& operator*=(const Tp& other) { *this = *this * other; }
		constexpr EndianValueType<Tp, order> operator/(const EndianValueType<Tp, order>& other) const { return EndianValueType(Tp(_value) / Tp(other._value)); }
		constexpr EndianValueType<Tp, order> operator/(const Tp& other) const { return EndianValueType(Tp(_value) / other); }
		constexpr EndianValueType<Tp, order>& operator/=(const EndianValueType<Tp, order>& other) { *this = *this / other; }
		constexpr EndianValueType<Tp, order>& operator/=(const Tp& other) { *this = *this / other; }
		constexpr EndianValueType<Tp, order> operator%(const EndianValueType<Tp, order>& other) const { return EndianValueType(Tp(_value) % Tp(other._value)); }
		constexpr EndianValueType<Tp, order> operator%(const Tp& other) const { return EndianValueType(Tp(_value) % other); }
		constexpr EndianValueType<Tp, order>& operator%=(const EndianValueType<Tp, order>& other) { *this = *this % other; }
		constexpr EndianValueType<Tp, order>& operator%=(const Tp& other) { *this = *this % other; }
		constexpr EndianValueType<Tp, order> operator~() const { return EndianValueType(~Tp(_value)); }
		constexpr EndianValueType<Tp, order> operator|(const EndianValueType<Tp, order>& other) const { return EndianValueType(Tp(_value) | Tp(other._value)); }
		constexpr EndianValueType<Tp, order> operator|(const Tp& other) const { return EndianValueType(Tp(_value) | other); }
		constexpr EndianValueType<Tp, order>& operator|=(const EndianValueType<Tp, order>& other) { *this = *this | other; }
		constexpr EndianValueType<Tp, order>& operator|=(const Tp& other) { *this = *this | other; }
		constexpr EndianValueType<Tp, order> operator&(const EndianValueType<Tp, order>& other) const { return EndianValueType(Tp(_value) & Tp(other._value)); }
		constexpr EndianValueType<Tp, order> operator&(const Tp& other) const { return EndianValueType(Tp(_value) & other); }
		constexpr EndianValueType<Tp, order>& operator&=(const EndianValueType<Tp, order>& other) { *this = *this & other; }
		constexpr EndianValueType<Tp, order>& operator&=(const Tp& other) { *this = *this & other; }
		constexpr EndianValueType<Tp, order> operator^(const EndianValueType<Tp, order>& other) const { return EndianValueType(Tp(_value) ^ Tp(other._value)); }
		constexpr EndianValueType<Tp, order> operator^(const Tp& other) const { return EndianValueType(Tp(_value) ^ other); }
		constexpr EndianValueType<Tp, order>& operator^=(const EndianValueType<Tp, order>& other) { *this = *this ^ other; }
		constexpr EndianValueType<Tp, order>& operator^=(const Tp& other) { *this = *this ^ other; }
		constexpr EndianValueType<Tp, order> operator>>(const int& other) const { return EndianValueType(Tp(_value) >> other); }
		constexpr EndianValueType<Tp, order>& operator>>=(const int& other) { *this = *this >> other; }
		constexpr EndianValueType<Tp, order> operator<<(const int& other) const { return EndianValueType(Tp(_value) << other); }
		constexpr EndianValueType<Tp, order>& operator<<=(const int& other) { *this = *this << other; }
		constexpr bool operator==(const EndianValueType<Tp, order>& other) const { return _value == other._value; }
		constexpr bool operator!=(const EndianValueType<Tp, order>& other) const { return _value != other._value; }
		constexpr bool operator>(const EndianValueType<Tp, order>& other) const { return Tp(_value) > Tp(other._value); }
		constexpr bool operator<(const EndianValueType<Tp, order>& other) const { return Tp(_value) < Tp(other._value); }
		constexpr bool operator>=(const EndianValueType<Tp, order>& other) const { return Tp(_value) >= Tp(other._value); }
		constexpr bool operator<=(const EndianValueType<Tp, order>& other) const { return Tp(_value) <= Tp(other._value); }
	};
	typedef EndianValueType<uint8_t, Endians::big> uint8be_t;
	typedef EndianValueType<uint16_t, Endians::big> uint16be_t;
	typedef EndianValueType<uint32_t, Endians::big> uint32be_t;
	typedef EndianValueType<uint64_t, Endians::big> uint64be_t;
	typedef EndianValueType<float, Endians::big> float32be_t;
	typedef EndianValueType<double, Endians::big> float64be_t;
	typedef EndianValueType<uint8_t, Endians::little> uint8le_t;
	typedef EndianValueType<uint16_t, Endians::little> uint16le_t;
	typedef EndianValueType<uint32_t, Endians::little> uint32le_t;
	typedef EndianValueType<uint64_t, Endians::little> uint64le_t;
	typedef EndianValueType<float, Endians::little> float32le_t;
	typedef EndianValueType<double, Endians::little> float64le_t;
}
#endif // __stationaryorbit_core_endians__