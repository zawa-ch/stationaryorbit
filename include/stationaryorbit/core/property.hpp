//	stationaryorbit/core/property
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
#ifndef __stationaryorbit_core_property__
#define __stationaryorbit_core_property__
#include <functional>
namespace zawa_ch::StationaryOrbit
{

	template<class classT, class T>
	class ReadOnlyProperty
	{
	public: // types
		typedef std::function<T(const classT&)> GetterFunction;
	private: // contains
		const classT& _inst;
		const GetterFunction _getter;
	public: // constructor
		constexpr ReadOnlyProperty(const classT& inst, const GetterFunction& getter) : _inst(inst), _getter(getter) {}
	public: // member
		constexpr T get() const { return _getter(_inst); }
		constexpr operator T() const { return _getter(_inst); }
	};

	template<class classT, class T>
	class Property
	{
	public: // types
		typedef std::function<T(const classT&)> GetterFunction;
		typedef std::function<void(classT&, const T&)> SetterFunction;
	private: // contains
		classT& _inst;
		const GetterFunction _getter;
		const SetterFunction _setter;
	public: // constructor
		constexpr Property(classT& inst, const SetterFunction& setter) : _inst(inst), _getter(nullptr), _setter(setter) {}
		constexpr Property(classT& inst, const GetterFunction& getter, const SetterFunction& setter) : _inst(inst), _getter(getter), _setter(setter) {}
	public: // member
		constexpr T get() const { return _getter(_inst); }
		constexpr operator T() const { return _getter(_inst); }
		constexpr void set(const T& value) const { return _setter(_inst, value); }
		constexpr const Property<classT, T>& operator=(const T& value) const { _setter(_inst, value); return *this; }
	};

}
#endif // __stationaryorbit_core_property__