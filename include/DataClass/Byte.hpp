#include <cstdint>
#include "LogicClass/BitReference.hpp"
#ifndef __BYTE_HPP__
#define __BYTE_HPP__
namespace StationaryOrbit
{

	///	ビットの集合を表します。このクラスは継承できません。
	struct Byte final
	{
	private:

		uint8_t _data;

	public:

		Byte();

		Byte(uint8_t value);

		~Byte();

		BitReference IndexOf(size_t index);

		static Byte Or(const Byte& left, const Byte& right);

		static Byte And(const Byte& left, const Byte& right);

		static Byte Not(const Byte& value);

		static Byte Xor(const Byte& left, const Byte& right);

		Byte& AssignOr(const Byte& value);

		Byte& AssignAnd(const Byte& value);

		Byte& AssignXor(const Byte& value);

		explicit operator uint8_t() const;

		BitReference operator [](size_t index) { return IndexOf(index); }
		Byte operator |(const Byte& value) const { return Or(*this, value); }
		Byte operator &(const Byte& value) const { return And(*this, value); }
		Byte operator ~() const { return Not(*this); }
		Byte operator ^(const Byte& value) const { return Xor(*this, value); }
		Byte& operator |=(const Byte& value) { return AssignOr(value); }
		Byte& operator &=(const Byte& value) { return AssignAnd(value); }
		Byte& operator ^=(const Byte& value) { return AssignXor(value); }

	};

}
#endif // __BYTE_HPP__