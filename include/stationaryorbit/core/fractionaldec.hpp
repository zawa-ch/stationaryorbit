#ifndef __stationaryorbit_core_fractionaldec__
#define __stationaryorbit_core_fractionaldec__
#include <cstdint>
#include <limits>
#include <stdexcept>
namespace zawa_ch::StationaryOrbit
{

	///	0.0から1.0までの数値を表します。
	///
	///	このオブジェクトは0.0以上1.0以下の数値を @a uintmax_t 型に等分割して格納します。
	///	@a uintmax_t が64ビット幅の場合、分割幅は5.42101086242752e-20です。
	struct FractionalDec final
	{
	private:
		uintmax_t _value;	///< このオブジェクトの内部的な値。
		constexpr FractionalDec(const uintmax_t& value) : _value(value) {}
	public:
		constexpr FractionalDec() : _value() {}
		///	浮動小数点数をこのオブジェクトに変換します。
		///	@param	value
		///	変換元の値。
		///	@exception
		///	std::invalid_argument
		///	変換元の値は0.0以上1.0以下のNaNではない数値である必要があります。
		constexpr explicit FractionalDec(const double& value)
			: _value(uintmax_t(value * double(UINTMAX_MAX)))
		{
			if ((value == std::numeric_limits<double>::quiet_NaN()) || (value == std::numeric_limits<double>::signaling_NaN()))
			{ throw std::invalid_argument("指定する値はNaNであってはなりません。"); }
			if ((value < 0.0) || (1.0 < value)) { throw std::invalid_argument("指定する値は0.0以上1.0以下である必要があります。"); }
		}
		///	分子・分母からこのオブジェクトを初期化します。
		///	@param	numerator
		///	除算時の被除数。
		///	@param	denominator
		///	除算時の除数。
		///	@exception
		///	std::invalid_argument
		///	除算結果がオーバーフローするため、 @a numerator は @a denominator より大きくすることはできません。
		///	また、0で除算することはできません。
		constexpr FractionalDec(const uintmax_t& numerator, const uintmax_t& denominator) : _value(Fraction(numerator, denominator)) {}

		constexpr FractionalDec operator+(const FractionalDec& other) const { return { ((_value) < (UINTMAX_MAX - other._value))?(_value + other._value):(UINTMAX_MAX) }; }
		constexpr FractionalDec operator-(const FractionalDec& other) const { return { ((other._value)<(_value))?(_value - other._value):(0U) }; }
		constexpr FractionalDec operator*(const FractionalDec& other) const { return { Multiple(_value, other._value) }; }
		constexpr FractionalDec& operator+=(const FractionalDec& other) { return *this = *this + other; }
		FractionalDec& operator-=(const FractionalDec& other) { return *this = *this - other; }
		FractionalDec& operator*=(const FractionalDec& other) { return *this = *this * other; }

		///	この値の平方数を取得します。
		constexpr FractionalDec Square() const { return { Multiple(_value, _value) }; }
		///	この値の平方根を取得します。
		constexpr FractionalDec Sqrt() const
		{
			uintmax_t result = _value;
			uintmax_t b = _value;
			do	// X[n+1] = (X[N] + a / X[N]) / 2
			{
				// 0除算の回避(sqrt(0) = 0)
				if (result == 0U) { break; }
				b = result;	///< 前回値(X[N])保持
				// a / X[N] の導出
				uintmax_t delta = Fraction(_value, b);
				// X[N] / 2
				result /= 2;
				// 剰余分の計算
				result += ((result % 2) + (delta % 2)) / 2;
				// (a / X[n]) / 2
				result += delta / 2;
			} while (2U < ((result < b)?(b-result):(result - b)));
			return { result };
		}

		///	このオブジェクトを指定したオブジェクトと比較します。
		constexpr int Compare(const FractionalDec& other) const { if (_value < other._value) { return -1; } else if (_value > other._value) { return 1; } else { return 0; } }
		#if cplusplus > 201703L
		constexpr int operator<=>(const FractionalDec& other) const { return Compare(other); }
		#endif
		constexpr bool operator<(const FractionalDec& other) const { return Compare(other) < 0; }
		constexpr bool operator>(const FractionalDec& other) const { return Compare(other) > 0; }
		constexpr bool operator<=(const FractionalDec& other) const { return Compare(other) <= 0; }
		constexpr bool operator>=(const FractionalDec& other) const { return Compare(other) >= 0; }

		///	指定されたオブジェクトがこのオブジェクトと等価であることを判定します。
		constexpr bool Equals(const FractionalDec& other) const { return _value == other._value; }
		constexpr bool operator==(const FractionalDec& other) const { return Equals(other); }
		constexpr bool operator!=(const FractionalDec& other) const { return !Equals(other); }

		constexpr explicit operator double() const { return double(_value) / double(UINTMAX_MAX); }

		///	このオブジェクトが表現できる最小値を取得します。
		static constexpr FractionalDec Min() { return { 0UL }; }
		///	このオブジェクトが表現できる最大値を取得します。
		static constexpr FractionalDec Max() { return { UINTMAX_MAX }; }
		///	このオブジェクトが表現できる最小刻み幅を取得します。
		static constexpr FractionalDec Epsiron() { return { 1UL }; }

	private:
		///	除算を行います。
		///	除算結果は @a UINTMAX_MAX にスケーリングされます。
		///	@param	numerator
		///	除算時の被除数。
		///	@param	denominator
		///	除算時の除数。
		///	@exception
		///	std::invalid_argument
		///	除算結果がオーバーフローするため、 @a numerator は @a denominator より大きくすることはできません。
		///	また、0で除算することはできません。
		static constexpr uintmax_t Fraction(const uintmax_t& numerator, const uintmax_t& denominator)
		{
			if (denominator == 0U) { throw std::invalid_argument("分母に0を指定することはできません。"); }
			if (denominator < numerator) { throw std::invalid_argument("分子に指定する値は分母以下である必要があります。"); }
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
		static constexpr uintmax_t Multiple(const uintmax_t& left, const uintmax_t& right)
		{
			uintmax_t result = 0UL;
			for(size_t i = 0U; i < UINTMAX_WIDTH; i++)
			{
				uintmax_t ad = 0U;
				if (left & (uintmax_t(1U) << (i)))
				{
					ad = right;
				}
				bool cr = ((ad % 2U) != 0) && ((result % 2U) != 0);
				result >>= 1;
				ad >>= 1;
				result += ad + (cr?1U:0U);
			}
			return result;
		}
	};

	static constexpr double operator*(const double& left, const FractionalDec& right) { return left * right / double(UINTMAX_MAX); }

}
#endif // __stationaryorbit_core_fractionaldec__