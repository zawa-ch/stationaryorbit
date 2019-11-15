#ifndef __StationaryOrbit_FractionalDec__
#define __StationaryOrbit_FractionalDec__
#include <cstdint>
#include <limits>
#include <stdexcept>
namespace StationaryOrbit
{

	///	0.0から1.0までの数値を表します。
	///
	///	このオブジェクトは0.0以上1.0以下の数値を @a uintmax_t 型に等分割して格納します。
	///	@a uintmax_t が64ビット幅の場合、分割幅は5.42101086242752e-20です。
	struct FractionalDec final
	{
	private:

		uintmax_t _value;	///< このオブジェクトの内部的な値。

		///	除算を行います。
		///	除算結果は @a UINTMAX_MAX にスケーリングされます。
		///
		///	@param	[in]numerator
		///	除算時の被除数。
		///
		///	@param	[in]denominator
		///	除算時の除数。
		///
		///	@exception	std::invalid_argument
		///	除算結果がオーバーフローするため、 @a numerator は @a denominator より大きくすることはできません。
		///	また、0で除算することはできません。
		static uintmax_t Fraction(const uintmax_t& numerator, const uintmax_t& denominator);

	public:

		///	既定の値でオブジェクトを初期化します。
		FractionalDec() = default;

		///	浮動小数点数をこのオブジェクトに変換します。
		///
		///	@param	[in]value
		///	変換元の値。
		///
		///	@exception	std::invalid_argument
		///	変換元の値は0.0以上1.0以下のNaNではない数値である必要があります。
		explicit FractionalDec(const double& value);

		///	分子・分母からこのオブジェクトを初期化します。
		///
		///	@param	[in]numerator
		///	除算時の被除数。
		///
		///	@param	[in]denominator
		///	除算時の除数。
		///
		///	@exception	std::invalid_argument
		///	除算結果がオーバーフローするため、 @a numerator は @a denominator より大きくすることはできません。
		///	また、0で除算することはできません。
		FractionalDec(const uintmax_t& numerator, const uintmax_t& denominator);

		FractionalDec operator+(const FractionalDec& value) const;

		FractionalDec operator-(const FractionalDec& value) const;

		FractionalDec operator*(const FractionalDec& value) const;

		///	この値の平方数を取得します。
		FractionalDec Square() const;

		///	この値の平方根を取得します。
		FractionalDec Sqrt() const;

		FractionalDec& operator+=(const FractionalDec& value);

		FractionalDec& operator-=(const FractionalDec& value);

		FractionalDec& operator*=(const FractionalDec& value);

		///	このオブジェクトを指定したオブジェクトと比較します。
		int Compare(const FractionalDec& value) const;
		#if cplusplus > 201703L
		int operator<=>(const FractionalDec& value) const { return Compare(value); }
		#endif
		bool operator<(const FractionalDec& value) const { return Compare(value) < 0; }
		bool operator>(const FractionalDec& value) const { return Compare(value) > 0; }
		bool operator<=(const FractionalDec& value) const { return Compare(value) <= 0; }
		bool operator>=(const FractionalDec& value) const { return Compare(value) >= 0; }

		///	指定されたオブジェクトがこのオブジェクトと等価であることを判定します。
		bool Equals(const FractionalDec& value) const;
		bool operator==(const FractionalDec& value) const { return Equals(value); }
		bool operator!=(const FractionalDec& value) const { return !Equals(value); }

		///	このオブジェクトが表現できる最小値を取得します。
		static FractionalDec Min();

		///	このオブジェクトが表現できる最大値を取得します。
		static FractionalDec Max();

		///	このオブジェクトが表現できる最小刻み幅を取得します。
		static FractionalDec Epsiron();

		explicit operator double() const;

	};

	static double operator*(const double& left, const FractionalDec& right);

}
#endif // __StationaryOrbit_FractionalDec__