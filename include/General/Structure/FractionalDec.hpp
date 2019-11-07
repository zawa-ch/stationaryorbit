#ifndef __StationaryOrbit_FractionalDec__
#define __StationaryOrbit_FractionalDec__
#include <cstdint>
#include <limits>
#include <stdexcept>
namespace StationaryOrbit
{

	///	0.0から1.0までの数値を表します。
	struct FractionalDec final
	{
	private:

		uintmax_t _value;

		static uintmax_t Fraction(const uintmax_t& numerator, const uintmax_t& denominator);

	public:

		///	既定の値でオブジェクトを初期化します。
		FractionalDec() = default;

		///	浮動小数点数をこのオブジェクトに変換します。
		explicit FractionalDec(const double& value);

		///	分子・分母からこのオブジェクトを初期化します。
		FractionalDec(const uintmax_t& numerator, const uintmax_t& denominator);

		FractionalDec operator+(const FractionalDec& value) const;

		FractionalDec operator-(const FractionalDec& value) const;

		FractionalDec operator*(const FractionalDec& value) const;

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

		///	このオブジェクトの最小値を取得します。
		static FractionalDec Min();

		///	このオブジェクトの最大値を取得します。
		static FractionalDec Max();

		///	このオブジェクトの最小刻み幅を取得します。
		static FractionalDec Epsiron();

		explicit operator double() const;

	};

}
#endif // __StationaryOrbit_FractionalDec__