#include "General/Structure/FractionalDec.hpp"

StationaryOrbit::FractionalDec::FractionalDec(const double& value)
    : _value(uintmax_t(value * UINTMAX_MAX))
{
    if ((value == std::numeric_limits<double>::quiet_NaN()) || (value == std::numeric_limits<double>::signaling_NaN()))
    { throw std::invalid_argument("value don't contain NaN."); }
    if ((value < 0.0) || (1.0 < value)) { throw std::invalid_argument("value must between 0.0 to 1.0."); }
}

StationaryOrbit::FractionalDec::FractionalDec(const uintmax_t& numerator, const uintmax_t& denominator)
{
    if (denominator == 0U) { throw std::invalid_argument("denominator don't contain 0."); }
    if (denominator < numerator) { throw std::invalid_argument("numerator must smaller than denominator."); }
    uintmax_t unit = UINTMAX_MAX / denominator;
    uintmax_t surplus = UINTMAX_MAX % denominator;
    uintmax_t mod = denominator / numerator;
    _value = unit * numerator;
    _value += surplus / mod;
}

StationaryOrbit::FractionalDec StationaryOrbit::FractionalDec::operator+(const FractionalDec& value) const
{
    FractionalDec result;
    result._value = ((_value) < (UINTMAX_MAX - value._value))?(_value + value._value):(UINTMAX_MAX);
    return result;
}

StationaryOrbit::FractionalDec StationaryOrbit::FractionalDec::operator-(const FractionalDec& value) const
{
    FractionalDec result;
    result._value = ((value._value)<(_value))?(_value - value._value):(0U);
    return result;
}

StationaryOrbit::FractionalDec StationaryOrbit::FractionalDec::operator*(const FractionalDec& value) const
{
    FractionalDec result;
    result._value = (_value >> (UINTMAX_WIDTH / 2)) * (value._value >> (UINTMAX_WIDTH / 2));
    return result;
}

StationaryOrbit::FractionalDec StationaryOrbit::FractionalDec::Sqrt() const
{
    // TODO: 何故かx/2を出力しているため修正
    FractionalDec result;
    result._value = _value;
    uintmax_t b;
    do
    {
        b = result._value;
        uintmax_t delta = (_value / result._value);
        result._value /= 2;
        result._value += ((result._value % 2) + (delta % 2)) / 2;
        result._value += delta / 2;
    } while (result._value - b < 2);
    return result;
}

StationaryOrbit::FractionalDec& StationaryOrbit::FractionalDec::operator+=(const FractionalDec& value)
{
    _value = ((_value) < (UINTMAX_MAX - value._value))?(_value + value._value):(UINTMAX_MAX);
    return *this;
}

StationaryOrbit::FractionalDec& StationaryOrbit::FractionalDec::operator-=(const FractionalDec& value)
{
    _value = ((value._value)<(_value))?(_value - value._value):(0U);
    return *this;
}

StationaryOrbit::FractionalDec& StationaryOrbit::FractionalDec::operator*=(const FractionalDec& value)
{
    FractionalDec result = (*this) * value;
    return *this = result;
}

int StationaryOrbit::FractionalDec::Compare(const FractionalDec& value) const
{
    if (_value < value._value) return -1;
    else if (_value > value._value) return 1;
    else return 0;
}

bool StationaryOrbit::FractionalDec::Equals(const FractionalDec& value) const
{
    return _value == value._value;
}

StationaryOrbit::FractionalDec StationaryOrbit::FractionalDec::Min()
{
    FractionalDec result;
    result._value = 0U;
    return result;
}

StationaryOrbit::FractionalDec StationaryOrbit::FractionalDec::Max()
{
    FractionalDec result;
    result._value = UINTMAX_MAX;
    return result;
}

StationaryOrbit::FractionalDec::operator double() const
{
    return double(_value) / UINTMAX_MAX;
}
