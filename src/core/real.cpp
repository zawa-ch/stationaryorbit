#include <cmath>
#include "stationaryorbit/core/real.hpp"
using namespace zawa_ch::StationaryOrbit;

void Real::PlaceExp(intmax_t exp)
{
	exp++;
	while (exp != 0)
	{
		if (0 < exp)
		{
			data.push_back(true);
			exp--;
		}
		else
		{
			data.push_back(false);
			exp++;
		}
	}
	data.push_back(false);
}

Real::Real(intmax_t value)
	: data()
{
	// 符号
	if (value < 0)
	{
		data.push_back(true);
		value = -value;
	}
	else
	{
		data.push_back(false);
	}
	// 指数
	size_t exp = 0U;
	while ((value >> ++exp) != 0);
	PlaceExp(exp);
	// 仮数
	exp--;
	while (exp != 0)
	{
		data.push_back((value & (1U << (--exp))) != 0U);
	}
}

Real::Real(uintmax_t value)
	: data()
{
	// 符号
	data.push_back(false);
	// 指数
	size_t exp = 0U;
	while ((value >> ++exp) != 0);
	PlaceExp(exp);
	// 仮数
	exp--;
	while (exp != 0)
	{
		data.push_back((value & (1U << (--exp))) != 0U);
	}
}

Real::Real(double value)
	: data()
{
	switch(std::fpclassify(value))
	{
		// 正または負の無限大
		case FP_INFINITE:
			if (value < 0)
			{
				data.push_back(true);
				data.push_back(true);
			}
			else
			{
				data.push_back(false);
				data.push_back(true);
			}
		return;

		// 非数値(Not a Number)
		case FP_NAN:
				data.push_back(true);
				data.push_back(false);
		return;

		// 正規化数
		case FP_NORMAL:
		// 非正規化数
		case FP_SUBNORMAL:
			// 符号
			if (value < 0)
			{
				data.push_back(true);
				value = -value;
			}
			else
			{
				data.push_back(false);
			}
			// 指数
			int exp;
			value = std::frexp(value, &exp);
			PlaceExp(exp);
			// 仮数
			value = std::fmod(value, 1.0);
			while (value != 0.0)
			{
				data.push_back((1.0 <= value)?(true):(false));
				value = std::fmod(value, 1.0);
			}
		return;

		// 零
		case FP_ZERO:
			data.push_back(false);
			data.push_back(false);
		return;

		default:
		throw InvalidOperationException("指定された値が無効です。");
	}
}

Real Real::NaN()
{
	Real result = Real();
	result.data.push_back(true);
	result.data.push_back(false);
	return result;
}

Real Real::Zero()
{
	Real result = Real();
	result.data.push_back(false);
	result.data.push_back(false);
	return result;
}

Real Real::Infinity()
{
	Real result = Real();
	result.data.push_back(false);
	result.data.push_back(true);
	return result;
}

Real Real::NegativeInfinity()
{
	Real result = Real();
	result.data.push_back(true);
	result.data.push_back(true);
	return result;
}

bool Real::isNegative() const
{
	if ((0 < data.size())&&(!isNaN())) { return data[0]; }
	else { return false; }
}

bool Real::isNaN() const
{
	if (data.size() <= 0U) { return false; }
	if (data[0] != true) { return false; }
	for (size_t i = 1; i < data.size(); i++)
	{
		if (data[i] != false) { return false; }
	}
	return true;
}

bool Real::isInfinity() const
{
	if (data.size() < 2U) { return false; }
	for (size_t i = 1; i < data.size(); i++)
	{
		if (data[i] != true) { return false; }
	}
	return true;
}

intmax_t Real::getExp() const
{
	// ビット列長が2以下の場合は常に非数値あるいはゼロのため0を返す
	if (data.size() <= 2U) { return 0; }
	// 1ビット目以降連続するビット数を数える
	bool watcher = data[1];
	intmax_t count = 0U;
	for (size_t i = 2; i < data.size(); i++)
	{
		if (data[i] != watcher) { break; }
		count++;
	}
	// +-inf, NaN, 0の場合の処理
	if ((data.size() - 2U) <= count)
	{
		count = 0;
	}
	// 0の場合は数値を反転し、-1する
	else if (watcher == false)
	{
		count = -count - 1;
	}
	else { /* do nothing */ }

	return count;
}

Real Real::Ldexp(intmax_t exp) const
{
	if (isNaN()) { return NaN(); }
	if (isInfinity())
	{
		if (isNegative()) { return NegativeInfinity(); }
		else { return Infinity(); }
	}
	auto result = Real();
	auto thisexp = getExp();
	result.data.push_back(isNegative());
	result.PlaceExp(thisexp + exp);
	size_t index;
	if (thisexp < 0) { index = size_t(-thisexp) + 1U; }
	else { index = size_t(thisexp) + 3U; }
	for (size_t i = index; i < data.size(); i++) { result.data.push_back(data[i]); }
	return result;
}

Real Real::Frexp() const
{ return Ldexp(-getExp()); }

Real Real::Abs() const
{
	if (isNegative())
	{
		return Negative();
	}
	else
	{
		return *this;
	}
}

Real Real::Negative() const
{
	if (data.size() <= 0U) { return *this; }
	for (size_t i = 1U; i < data.size(); i++)
	{
		if (data[i] != false) { break; }
		if (data.size() <= i) { return *this; }
	}
	auto result = Real(*this);
	result.data[0] = !result.data[0];
	return result;
}
