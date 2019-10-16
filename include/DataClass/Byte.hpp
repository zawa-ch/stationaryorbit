#ifndef __StationaryOrbit_Byte__
#define __StationaryOrbit_Byte__
#include <cstdint>
#include <iostream>
#include "LogicClass/BitReference.hpp"
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
		static Byte Or(const Byte& left, const Byte& right);

		///	2つのByteに対し、andによるブーリアン演算を行います。
		static Byte And(const Byte& left, const Byte& right);

		///	Byteの内容を反転します。
		static Byte Not(const Byte& value);

		///	2つのByteに対し、xorによるブーリアン演算を行います。
		static Byte Xor(const Byte& left, const Byte& right);

		Byte& AssignOr(const Byte& value);

		Byte& AssignAnd(const Byte& value);

		Byte& AssignXor(const Byte& value);

		///	Byteを指定されたビット数シフトします。
		Byte Shift(int bits);

		///	Byteを指定されたビット数シフトします。
		///	シフトによってあふれたビットは反対のビットに置かれます。
		Byte Rotate(int bits);

		///	指定された二つのオブジェクトが等しいか比較します。
		static bool Equal(const Byte& left, const Byte& right);



		explicit operator uint8_t() const { return _data; }

		BitReference operator[](size_t index) { return IndexOf(index); }
		Byte operator|(const Byte& value) const { return Or(*this, value); }
		Byte operator&(const Byte& value) const { return And(*this, value); }
		Byte operator~() const { return Not(*this); }
		Byte operator^(const Byte& value) const { return Xor(*this, value); }
		Byte& operator|=(const Byte& value) { return AssignOr(value); }
		Byte& operator&=(const Byte& value) { return AssignAnd(value); }
		Byte& operator^=(const Byte& value) { return AssignXor(value); }
		Byte operator<<(int value) { return Byte(_data << value); }
		Byte operator>>(int value) { return Byte(_data >> value); }
		bool operator==(const Byte& value) { return Equal(*this, value); }
		bool operator!=(const Byte& value) { return !Equal(*this, value); }

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