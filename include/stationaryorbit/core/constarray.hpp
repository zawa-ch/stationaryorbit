//	stationaryorbit/core/constarray
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
#ifndef __stationaryorbit_core_constarray__
#define __stationaryorbit_core_constarray__
namespace zawa_ch::StationaryOrbit
{
	///	コンパイル時に内容が決定する値の配列を表します。
	template<class T, T ... Values>
	struct ConstArray
	{
	private:
		ConstArray() = delete;
		ConstArray(const ConstArray&) = delete;
		ConstArray(ConstArray&&) = delete;
		~ConstArray() = delete;
	public:
		typedef T type[sizeof...(Values)];

		static constexpr T values[] = { Values ... };

		template<T ... ConcatValues>
		struct Concat
		{
			typedef ConstArray<T, Values..., ConcatValues...> type;
		};
	};

	template<class T, T Expr(T), T Init>
	class ConstExprIterator
	{
	public:
		typedef T ValueType;
	private:
		T _value;
	public:
		constexpr ConstExprIterator() : _value(Init) {}

		[[nodiscard]] bool Equals(const ConstExprIterator& other) const noexcept { return _value == other._value; }
		[[nodiscard]] bool Next() noexcept { _value = Expr(_value); return true; }
		[[nodiscard]] bool HasValue() const noexcept { return true; }
		[[nodiscard]] const ValueType& Current() const noexcept { return _value; }
	};

	///	コンパイル時に値が決定する数列を式と初期値から生成します。
	template<class T, T Expr(T), T Init, size_t N>
	class ConstProgression : ConstProgression<T, Expr, Init, N - 1>::template Concat<Expr(ConstProgression<T, Expr, Init, N - 1>::last)>::type
	{
	public:
		T last = Expr(ConstProgression<T, Expr, Init, N - 1>::last);
	};
	template<class T, T Expr(T), T Init>
	class ConstProgression<T, Expr, Init, 0> : ConstArray<T, Init>
	{
	public:
		T last = Init;
	};
}
#endif // __stationaryorbit_core_constarray__
