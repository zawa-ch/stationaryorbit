//	stationaryorbit.mathematics:/fuzzybool
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
#include "stationaryorbit/mathematics/fuzzybool.hpp"
using namespace zawa_ch::StationaryOrbit::Mathematics;

FuzzyBool::FuzzyBool(bool value)
    : _value((value?1U:0U), 1U)
{}

FuzzyBool::FuzzyBool(const uintmax_t& num, const uintmax_t& den)
    : _value(num, den)
{}

FuzzyBool::FuzzyBool(const double& value)
    : _value(value)
{}

FuzzyBool::FuzzyBool(const Proportion64_t& value)
    : _value(value)
{}

bool FuzzyBool::Binalization(const Proportion64_t& value) const
{ return value <= _value; }

FuzzyBool FuzzyBool::Not() const
{ return FuzzyBool(Proportion64_t::Max() - _value); }

FuzzyBool FuzzyBool::Or(const FuzzyBool& value) const
{ return FuzzyBool((value._value<_value)?_value:value._value); }

FuzzyBool FuzzyBool::And(const FuzzyBool& value) const
{ return FuzzyBool((_value<value._value)?_value:value._value); }

FuzzyBool FuzzyBool::AlgebraAdd(const FuzzyBool& value) const
{ return FuzzyBool(_value + (value._value - _value * value._value)); }

FuzzyBool FuzzyBool::AlgebraProduct(const FuzzyBool& value) const
{ return FuzzyBool(_value * value._value); }

FuzzyBool FuzzyBool::LimitAdd(const FuzzyBool& value) const
{ return FuzzyBool(_value + value._value); }

FuzzyBool FuzzyBool::LimitProduct(const FuzzyBool& value) const
{ return FuzzyBool(_value - (Proportion64_t::Max() - value._value)); }

FuzzyBool FuzzyBool::True()
{ return FuzzyBool(true); }

FuzzyBool FuzzyBool::False()
{ return FuzzyBool(false); }
