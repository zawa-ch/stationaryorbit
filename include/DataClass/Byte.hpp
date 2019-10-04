#include <cstdint>
#include "Interface/IElementSet.hpp"
#include "LogicClass/BitAccess.hpp"
#ifndef __BYTE_HPP__
#define __BYTE_HPP__
namespace StationaryOrbit
{

	///	ビットの集合を表します。このクラスは継承できません。
	struct Byte final
		: public IElementSet<BitAccess>
	{
	private:

		uint8_t _data;

	public:

		Byte();

		Byte(uint8_t value);

		~Byte();

		BitAccess IndexOf(size_t index);
		
	};

}
#endif // __BYTE_HPP__