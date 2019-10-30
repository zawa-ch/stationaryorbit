#ifndef __StationaryOrbit_NumericAnalysis_CompensatedFloat__
#define __StationaryOrbit_NumericAnalysis_CompensatedFloat__
#include <cmath>
namespace StationaryOrbit::NumericAnalysis
{

	/// 計算時に誤差の補償が行われる浮動小数点数を表します。
	template<class T>
	struct CompensatedFloat final
	{
	public:

		T value;
		T c;

		constexpr CompensatedFloat() = default;

		explicit constexpr CompensatedFloat(const T& value) : value(value), c() {}

	private:

		constexpr CompensatedFloat(const T& value, const T& c) : value(value), c(c) {}

	public:

		constexpr CompensatedFloat<T> operator+() const
		{
			return CompensatedFloat<T>(((value - c) < 0)?(-value):(value), ((value - c) < 0)?(-c):(c));
		}

		constexpr CompensatedFloat<T> operator-() const
		{
			return CompensatedFloat<T>(-value, -c);
		}

		constexpr CompensatedFloat<T> operator+(const T& value) const
		{
			T comp = value - c;
			T sum = this->value + comp;
			return CompensatedFloat<T>(sum, (sum - this->value) - comp);
		}

		constexpr CompensatedFloat<T> operator-(const T& value) const
		{
			return operator+(-value);
		}

		constexpr CompensatedFloat<T> operator*(const T& value) const
		{
			return CompensatedFloat<T>(this->value * value, c * value);
		}

		constexpr CompensatedFloat<T> operator/(const T& value) const
		{
			return CompensatedFloat<T>(this->value / value, c / value);
		}

		constexpr CompensatedFloat<T> operator^(const T& value) const
		{
			return CompensatedFloat<T>(this->value ^ value, c ^ value);
		}

		explicit constexpr operator T() const
		{
			return value;
		}

	};

}
#endif // __StationaryOrbit_NumericAnalysis_CompensatedFloat__