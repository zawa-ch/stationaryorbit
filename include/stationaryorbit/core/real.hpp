#ifndef __StationaryOrbit_Real__
#define __StationaryOrbit_Real__
#include <cstdint>
#include <vector>
#include <string>
#include "stationaryorbit/exception/soexcept"
namespace zawa_ch::StationaryOrbit
{

	///	可変長のビット配列で表される実数を表します。
	///
	///	@note
	///	この型は可変長のビット配列を用いて(メモリが許す限り)無制限の精度を持つ実数を表現します。
	///	long double でも正確に表すことのできない値を表現することが可能ですが、IEEE 754で定義される浮動小数点数と比較してほとんどの実行環境で実行速度、メモリの使用量の観点で劣ります。
	struct Real final
	{
	private:

		std::vector<bool> data;

		void PlaceExp(intmax_t exp);

	public:

		///	オブジェクトの既定の値で初期化します。
		Real() = default;

		///	符号付き整数型をこの型に変換します。
		///
		///	@param	value
		///	変換元の値。
		Real(intmax_t value);

		///	符号なし整数型をこの型に変換します。
		///
		///	@param	value
		///	変換元の値。
		Real(uintmax_t value);

		///	浮動小数点型をこの型に変換します。
		///
		///	@param	value
		///	変換元の値。
		Real(double value);

		///	この型で表される非数値(NaN)を取得します。
		static Real NaN();

		///	この型で表される零値を取得します。
		static Real Zero();

		///	この型で表される正の無限大を取得します。
		static Real Infinity();

		///	この型で表される負の無限大を取得します。
		static Real NegativeInfinity();

		///	オブジェクトの値が負の値であるかどうかを取得します。
		bool isNegative() const;

		///	オブジェクトの値が非数値(NaN)であるかどうかを取得します。
		bool isNaN() const;

		///	オブジェクトの値が正または負の無限大であるかを取得します。
		bool isInfinity() const;

		///	オブジェクトの指数部分を取得します。
		intmax_t getExp() const;

		///	オブジェクトに2の累乗をかけ合わせた数を求めます。
		Real Ldexp(intmax_t exp) const;

		///	オブジェクトから指数を取り除いた正規化数を求めます。
		Real Frexp() const;

		Real Abs() const;
		Real operator+() const { return Abs(); }

		Real Negative() const;
		Real operator-() const { return Negative(); }

		Real operator+(const Real& value) const;
		Real operator-(const Real& value) const;
		Real operator*(const Real& value) const;
		Real operator/(const Real& value) const;

		Real& operator+=(const Real& value);
		Real& operator-=(const Real& value);
		Real& operator*=(const Real& value);
		Real& operator/=(const Real& value);

		///	指定されたオブジェクトとこのオブジェクトが等価であるか検証します。
		bool Equals(const Real& value) const;
		bool operator==(const Real& value) const;
		bool operator!=(const Real& value) const;

		///	指定されたオブジェクトとこのオブジェクトとの比較を行います。
		int Compare(const Real& value) const;
		bool operator<=(const Real& value) const;
		bool operator>=(const Real& value) const;
		bool operator<(const Real& value) const;
		bool operator>(const Real& value) const;

		static Real Parth(const char* string, size_t length);
		static Real Parth(const std::string string);

		std::string toString() const;
	};

}
#endif // __StationaryOrbit_Real__