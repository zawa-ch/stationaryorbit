#ifndef __StationaryOrbit_Byte__
#define __StationaryOrbit_Byte__
#include <cstdint>
#include <iostream>
#include "../Logic/BitReference.hpp"
namespace StationaryOrbit
{

	///	ビットの集合を表します。このクラスは継承できません。
	struct Byte final
	{
	private:

		uint8_t _data;

	public:

		Byte() = default;

		Byte(uint8_t value);

		~Byte() = default;

		BitReference IndexOf(size_t index);

		///	2つのByteに対し、orによるブーリアン演算を行います。
		Byte Or(const Byte& value) const;

		///	2つのByteに対し、andによるブーリアン演算を行います。
		Byte And(const Byte& value) const;

		///	Byteの内容を反転します。
		Byte Not() const;

		///	2つのByteに対し、xorによるブーリアン演算を行います。
		Byte Xor(const Byte& value) const;

		Byte& AssignOr(const Byte& value);

		Byte& AssignAnd(const Byte& value);

		Byte& AssignXor(const Byte& value);

		///	Byteを指定されたビット数シフトします。
		Byte Shift(int bits) const;

		///	Byteを指定されたビット数シフトします。
		///	シフトによってあふれたビットは反対のビットに置かれます。
		Byte Rotate(int bits) const;

		///	指定されたオブジェクトがこのオブジェクトと等価であることを判定します。
		bool Equals(const Byte& value) const;


		explicit operator uint8_t() const { return _data; }

		BitReference operator[](size_t index) { return IndexOf(index); }
		Byte operator|(const Byte& value) const { return Or(value); }
		Byte operator&(const Byte& value) const { return And(value); }
		Byte operator~() const { return Not(); }
		Byte operator^(const Byte& value) const { return Xor(value); }
		Byte& operator|=(const Byte& value) { return AssignOr(value); }
		Byte& operator&=(const Byte& value) { return AssignAnd(value); }
		Byte& operator^=(const Byte& value) { return AssignXor(value); }
		Byte operator<<(int value) const { return Byte(_data << value); }
		Byte operator>>(int value) const { return Byte(_data >> value); }
		bool operator==(const Byte& value) const { return Equals(value); }
		bool operator!=(const Byte& value) const { return !Equals(value); }

	};

	template<class CharT, class Traits = std::char_traits<CharT> >
	std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& stream, const Byte& value)
	{
		uint8_t d1 = (uint8_t(value) & 0xF0)>>4;
		uint8_t d2 = (uint8_t(value) & 0x0F);
		stream << uint8_t((d1 >= 10) ? ('A' - 10 + d1) : ('0' + d1));
		stream << uint8_t((d2 >= 10) ? ('A' - 10 + d2) : ('0' + d2));
		return stream;
	}

}
#endif // __StationaryOrbit_Byte__