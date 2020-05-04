#include "stationaryorbit/mathematics/fuzzybool.hpp"
using namespace zawa_ch::StationaryOrbit::Analysis;

FuzzyBool::FuzzyBool(bool value)
    : _value((value?1U:0U), 1U)
{}

FuzzyBool::FuzzyBool(const uintmax_t& num, const uintmax_t& den)
    : _value(num, den)
{}

FuzzyBool::FuzzyBool(const double& value)
    : _value(value)
{}

FuzzyBool::FuzzyBool(const FractionalDec& value)
    : _value(value)
{}

bool FuzzyBool::Binalization(const FractionalDec& value) const
{ return value <= _value; }

FuzzyBool FuzzyBool::Not() const
{ return FuzzyBool(FractionalDec::Max() - _value); }

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
{ return FuzzyBool(_value - (FractionalDec::Max() - value._value)); }

FuzzyBool FuzzyBool::True()
{ return FuzzyBool(true); }

FuzzyBool FuzzyBool::False()
{ return FuzzyBool(false); }
