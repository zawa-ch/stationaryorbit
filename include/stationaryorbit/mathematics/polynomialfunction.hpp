//	stationaryorbit/mathematics/polynomialfunction
//	Copyright 2020 zawa-ch.
//	GPLv3 (or later) license
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//	See the GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program.
//	If not, see <http://www.gnu.org/licenses/>.
//
#ifndef __stationaryorbit_mathematics_polynomialfunction__
#define __stationaryorbit_mathematics_polynomialfunction__
#include <array>
#include "stationaryorbit/core.exception.hpp"
#include "stationaryorbit/core.numeral.hpp"
#include "compensatedfloat.hpp"
#include "mathematicfunction.hpp"
namespace zawa_ch::StationaryOrbit::Mathematics
{
	///	実数の多項式を表します。
	template<typename T, size_t N>
	class PolynomialFunction : public IMathematicFunction<T>
	{
		static_assert(Traits::IsNumericalType<T>, "テンプレート型 T は数値型である必要があります。");
	public:
		typedef T ValueType;
		typedef std::array<T, N> DataType;
	private:
		DataType num;
	public:
		///	空のオブジェクトを作成します。
		PolynomialFunction() = default;
		///	多項式のオブジェクトを初期化します。
		///	x^n * num[n-1] + ... x^2 * num[2] + x * num[1] + num[0] の順で計算されます。
		explicit PolynomialFunction(const DataType& value) : num(value) {}
		///	多項式への参照を取得します。
		const DataType& Polynomial() const { return num; }
		/// この関数に値を代入した解を取得します。
		/// @param  value
		/// 代入する値。
		/// @return
		/// 計算を行い、得られた解が返ります。
		ValueType Calc(const ValueType& value) const
		{
			if constexpr (std::numeric_limits<T>::is_exact)
			{
				auto numvalue = T();
				for(auto i: Range<size_t>(0, num.size()).GetStdReverseIterator())
				{
					numvalue += num[i];
					numvalue *= value;
				}
				numvalue += num[0];
				return numvalue;
			}
			else
			{
				auto numvalue = CompensatedFloat<T>();
				for(auto i: Range<size_t>(0, num.size()).GetStdReverseIterator())
				{
					numvalue += num[i];
					numvalue *= value;
				}
				numvalue += num[0];
				return T(numvalue);
			}
		}
		ValueType operator()(const ValueType& value) const { return Calc(value); }
	};

}
#endif // __stationaryorbit_mathematics_polynomialfunction__