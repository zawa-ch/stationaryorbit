//	stationaryorbit/core/logic
//	Copyright 2020 zawa-ch.
//	GPLv3 (or later) license
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//	See the GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program.
//	If not, see <http://www.gnu.org/licenses/>.
//
#ifndef __stationaryorbit_core_logic__
#define __stationaryorbit_core_logic__
#include <stdexcept>
namespace zawa_ch::StationaryOrbit
{
	///	真でも偽でもない値を持つことができる論理値を表します。
	struct Logic final
	{
	private:
		enum { _False = false, _True = true, _Indefinited, _Undefined } _value;
		constexpr Logic(const decltype(_value)& value) : _value(value) {}
	public:
		constexpr Logic() : _value(_Undefined) {}
		explicit constexpr Logic(const bool& value) : _value((value)?(_True):(_False)) {}

		///	真の論理値を表します。
		static constexpr Logic True() { return Logic{ _True }; }
		///	偽の論理値を表します。
		static constexpr Logic False() { return Logic{ _False }; }
		///	真または偽のどちらでもある、あるいはそのどちらでもない中間の論理値を表します。
		static constexpr Logic Indefinited() { return Logic{ _Indefinited }; }
		///	値を持たない論理値を表します。
		static constexpr Logic Undefined() { return Logic{ _Undefined }; }

		constexpr bool IsUndefined() const { return _value == _Undefined; }

		constexpr bool Equals(const Logic& other) const { return (_value == other._value)&&(_value != _Undefined); }
		constexpr bool operator==(const Logic& other) const { return Equals(other); }
		constexpr bool operator!=(const Logic& other) const { return !Equals(other); }
		constexpr bool Equals(const bool& other) const { if (((other == true)&&(_value == _True))||((other == false)&&(_value == _False))) { return true; } else { return false; } }
		constexpr bool operator==(const bool& other) const { return Equals(other); }
		constexpr bool operator!=(const bool& other) const { return !Equals(other); }
		constexpr Logic operator||(const Logic& other) const
		{
			if ((_value == _Undefined)||(other._value == _Undefined)) { return Undefined(); }
			else if ((_value == _True)||(other._value == _True)) { return True(); }
			else if ((_value == _Indefinited)||(other._value == _Indefinited)) { return Indefinited(); }
			else { return False(); }
		}
		constexpr Logic operator&&(const Logic& other) const
		{
			if ((_value == _Undefined)||(other._value == _Undefined)) { return Undefined(); }
			else if ((_value == _False)||(other._value == _False)) { return False(); }
			else if ((_value == _Indefinited)||(other._value == _Indefinited)) { return Indefinited(); }
			else { return True(); }
		}
		constexpr Logic operator!() const
		{
			if (_value == _Undefined) { return Undefined(); }
			else if (_value == _Indefinited) { return Indefinited(); }
			else if (_value == _True) { return False(); }
			else { return True(); }
		}

		explicit constexpr operator bool() const
		{
			if (_value == _True) { return true; }
			else if (_value == _False) { return false; }
			else { throw std::bad_cast(); }
		}
	};

    template<class charT, class Traits = std::char_traits<charT>>
    std::basic_ostream<charT, Traits>& operator<<(std::basic_ostream<charT, Traits>& stream, const Logic& value)
    {
        if (value==Logic::False()) { return stream << "false"; }
        else if (value==Logic::True()) { return stream << "true"; }
        else if (value==Logic::Indefinited()) { return stream << "indefinited"; }
        else { return stream << "Undefined"; }
    }
}
#endif // __stationaryorbit_core_logic__