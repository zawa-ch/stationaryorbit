#ifndef __StationaryOrbit_Analysis_CompensatedFloat__
#define __StationaryOrbit_Analysis_CompensatedFloat__
#include <type_traits>
namespace zawa_ch::StationaryOrbit::Analysis
{
	/// 計算時に誤差の補償が行われる浮動小数点数を表します。
	template<class T>
	struct CompensatedFloat final
	{
		static_assert(std::is_floating_point_v<T>, "テンプレート引数 T は浮動小数点数である必要があります。");
	private:
		T value;	///< このオブジェクトの値
		T c;	///< 計算時に発生した誤差
	public:
		///	オブジェクトを既定の値で初期化します。
		constexpr CompensatedFloat() = default;
		///	指定された値でオブジェクトを初期化します。
		explicit constexpr CompensatedFloat(const T& value) : value(value), c() {}
	private:
		///	値からこのオブジェクトを直接構築します。
		constexpr CompensatedFloat(const T& value, const T& c) : value(value), c(c) {}
	public:
		///	このオブジェクトが指す値を取得します。
		constexpr T getValue() const { return value; }
		///	このオブジェクトの計算時に用いられる誤差の値を取得します。
		constexpr T getError() const { return c; }
		constexpr CompensatedFloat<T> operator+() const { return CompensatedFloat<T>(((value - c) < 0)?(-value):(value), ((value - c) < 0)?(-c):(c)); }
		constexpr CompensatedFloat<T> operator-() const { return CompensatedFloat<T>(-value, -c); }
		constexpr CompensatedFloat<T> operator+(const T& value) const
		{
			T comp = value - c;
			T sum = this->value + comp;
			return CompensatedFloat<T>(sum, (sum - this->value) - comp);
		}
		constexpr CompensatedFloat<T>& operator+=(const T& value) { return *this = *this + value; }
		constexpr CompensatedFloat<T> operator-(const T& value) const { return operator+(-value); }
		constexpr CompensatedFloat<T>& operator-=(const T& value) { return operator+=(-value); }
		constexpr CompensatedFloat<T> operator*(const T& value) const { return CompensatedFloat<T>(this->value * value, c * value); }
		constexpr CompensatedFloat<T>& operator*=(const T& value) { return *this = *this * value; }
		constexpr CompensatedFloat<T> operator/(const T& value) const { return CompensatedFloat<T>(this->value / value, c / value); }
		constexpr CompensatedFloat<T>& operator/=(const T& value) { return *this = *this / value; }
		constexpr CompensatedFloat<T> operator^(const T& value) const { return CompensatedFloat<T>(this->value ^ value, c ^ value); }
		constexpr CompensatedFloat<T>& operator^=(const T& value) { return *this = *this ^ value; }
		explicit constexpr operator T() const { return value; }
	};

	/// 計算時に誤差の補償が行われる @a float を表します。
	typedef CompensatedFloat<float> CompensatedSingle;
	/// 計算時に誤差の補償が行われる @a double を表します。
	typedef CompensatedFloat<double> CompensatedDouble;

}
#endif // __StationaryOrbit_NumericAnalysis_CompensatedFloat__