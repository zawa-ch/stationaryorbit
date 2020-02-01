#include "stationaryorbit/core/fractionaldec.hpp"
using namespace zawa_ch::StationaryOrbit;

uintmax_t FractionalDec::Fraction(const uintmax_t& numerator, const uintmax_t& denominator)
{
	if (denominator == 0U) { throw std::invalid_argument("denominator don't contain 0."); }
	if (denominator < numerator) { throw std::invalid_argument("numerator must smaller than denominator."); }
	uintmax_t unit = UINTMAX_MAX / denominator;
	uintmax_t result = unit * numerator;
	uintmax_t surplus = UINTMAX_MAX % denominator;
	if (surplus != 0U)
	{
		uintmax_t dv = 0U;
		uintmax_t md = 0U;
		for(size_t i = UINT64_WIDTH; 0 < i; i--)
		{
			dv *= 2U;
			md *= 2U;
			if (numerator & (uintmax_t(1U) << (i - 1)))
			{
				md += surplus;
			}
			dv += md / denominator;
			md %= denominator;
		}
		result += dv;
	}
	return result;
}

FractionalDec::FractionalDec(const double& value)
	: _value(uintmax_t(value * UINTMAX_MAX))
{
	if ((value == std::numeric_limits<double>::quiet_NaN()) || (value == std::numeric_limits<double>::signaling_NaN()))
	{ throw std::invalid_argument("value don't contain NaN."); }
	if ((value < 0.0) || (1.0 < value)) { throw std::invalid_argument("value must between 0.0 to 1.0."); }
}

FractionalDec::FractionalDec(const uintmax_t& numerator, const uintmax_t& denominator)
	: _value(Fraction(numerator, denominator))
{}

FractionalDec FractionalDec::operator+(const FractionalDec& value) const
{
	FractionalDec result;
	result._value = ((_value) < (UINTMAX_MAX - value._value))?(_value + value._value):(UINTMAX_MAX);
	return result;
}

FractionalDec FractionalDec::operator-(const FractionalDec& value) const
{
	FractionalDec result;
	result._value = ((value._value)<(_value))?(_value - value._value):(0U);
	return result;
}

FractionalDec FractionalDec::operator*(const FractionalDec& value) const
{
	FractionalDec result;
	result._value = 0U;
	for(size_t i = 0U; i < UINTMAX_WIDTH; i++)
	{
		uintmax_t ad = 0U;
		if (value._value & (uintmax_t(1U) << (i)))
		{
			ad = _value;
		}
		bool cr = ((ad % 2U) != 0) && ((result._value % 2U) != 0);
		result._value >>= 1;
		ad >>= 1;
		result._value += ad + (cr?1U:0U);
	}
	return result;
}

FractionalDec FractionalDec::Square() const
{ return (*this) * (*this); }

FractionalDec FractionalDec::Sqrt() const
{
	FractionalDec result;
	result._value = _value;
	uintmax_t b;
	do	// X[n+1] = (X[N] + a / X[N]) / 2
	{
		// 0除算の回避(sqrt(0) = 0)
		if (result._value == 0U) { break; }
		b = result._value;	///< 前回値(X[N])保持
		// a / X[N] の導出
		uintmax_t delta = Fraction(_value, b);
		// X[N] / 2
		result._value /= 2;
		// 剰余分の計算
		result._value += ((result._value % 2) + (delta % 2)) / 2;
		// (a / X[n]) / 2
		result._value += delta / 2;
	} while (2U < ((result._value < b)?(b-result._value):(result._value - b)));
	return result;
}

FractionalDec& FractionalDec::operator+=(const FractionalDec& value)
{
	_value = ((_value) < (UINTMAX_MAX - value._value))?(_value + value._value):(UINTMAX_MAX);
	return *this;
}

FractionalDec& FractionalDec::operator-=(const FractionalDec& value)
{
	_value = ((value._value)<(_value))?(_value - value._value):(0U);
	return *this;
}

FractionalDec& FractionalDec::operator*=(const FractionalDec& value)
{
	FractionalDec result = (*this) * value;
	return *this = result;
}

int FractionalDec::Compare(const FractionalDec& value) const
{
	if (_value < value._value) return -1;
	else if (_value > value._value) return 1;
	else return 0;
}

bool FractionalDec::Equals(const FractionalDec& value) const
{
	return _value == value._value;
}

FractionalDec FractionalDec::Min()
{
	FractionalDec result;
	result._value = 0U;
	return result;
}

FractionalDec FractionalDec::Max()
{
	FractionalDec result;
	result._value = UINTMAX_MAX;
	return result;
}

FractionalDec FractionalDec::Epsiron()
{
	FractionalDec result;
	result._value = 1U;
	return result;
}

FractionalDec::operator double() const
{
	return double(_value) / UINTMAX_MAX;
}

double zawa_ch::StationaryOrbit::operator*(const double& left, const FractionalDec& right)
{
	return left * right / UINTMAX_MAX;
}
