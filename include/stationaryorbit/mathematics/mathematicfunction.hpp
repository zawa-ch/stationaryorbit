//	stationaryorbit/mathematics/mathematicfunction
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
#ifndef __stationaryorbit_mathematics_mathematicfunction__
#define __stationaryorbit_mathematics_mathematicfunction__
#include "stationaryorbit/core.traits.hpp"
#include <functional>
namespace zawa_ch::StationaryOrbit::Mathematics
{

	/// @a T 型の値を受け取り、 @a T 型の値を返す数学的な関数を実装します。
	template<class T>
	class IMathematicFunction
	{
		static_assert(Traits::IsNumericalType<T>, "テンプレート型 T は数値型である必要があります。");
	public:
		/// この関数に値を代入した解を取得します。
		/// @param  value
		/// 代入する値。
		/// @return
		/// 計算を行い、得られた解が返ります。
		virtual T Calc(const T& value) const = 0;
	};
	/// @a T 型の値を受け取り、 @a T 型の値を返す数学的な関数を表します。
	template<class T>
	class MathematicFunction
		: public IMathematicFunction<T>
	{
		static_assert(Traits::IsNumericalType<T>, "テンプレート型 T は数値型である必要があります。");
	public:
		///	@a T 型の値を受け取り、 @a T 型の値を返す数学的な関数の実体。
		typedef std::function<T(T)> HandlerType;
	private:
		HandlerType func;
	public:
		///	実体となる関数を指定してこのオブジェクトを初期化します。
		explicit MathematicFunction(HandlerType function) : func(function) {}
		/// この関数に値を代入した解を取得します。
		/// @param  value
		/// 代入する値。
		/// @return
		/// 計算を行い、得られた解が返ります。
		T Calc(const T& value) const { return func(value); }
		T operator()(const T& value) const { return Calc(value); }
	};

}
#endif // __stationaryorbit_mathematics_mathematicfunction_