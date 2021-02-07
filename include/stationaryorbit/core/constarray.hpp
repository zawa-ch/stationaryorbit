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
	///	@param	T
	///	値の型。
	///	@param	Values
	///	配列の内容。
	template<class T, T ... Values>
	struct ConstArray
	{
	private:
		ConstArray() = delete;
		ConstArray(const ConstArray&) = delete;
		ConstArray(ConstArray&&) = delete;
		~ConstArray() = delete;
	public:
		///	この配列の表す型。
		typedef T type[sizeof...(Values)];

		///	この @a ConstArray の内容。
		static constexpr T values[] = { Values ... };

		///	この @a ConstArray の内容に値を追加します。
		template<T ... ConcatValues>
		struct Concat
		{
			typedef ConstArray<T, Values..., ConcatValues...> type;
		};
	};

	///	constexprな再帰関数を実行するためのイテレータ。
	///	@param	T
	///	値の型。
	///	@param	Expr
	///	実行する関数。
	///	constexprな関数でなくてはなりません。
	///	@param	Init
	///	関数に渡す初期値。
	template<class T, T Expr(T), T Init>
	class ConstExprIterator
	{
	public:
		typedef T ValueType;
	private:
		T _value;
	public:
		constexpr ConstExprIterator() : _value(Init) {}

		[[nodiscard]] constexpr bool Equals(const ConstExprIterator& other) const noexcept { return _value == other._value; }
		[[nodiscard]] constexpr bool Next() noexcept { _value = Expr(_value); return true; }
		[[nodiscard]] constexpr bool HasValue() const noexcept { return true; }
		[[nodiscard]] constexpr const ValueType& Current() const noexcept { return _value; }
	};

	///	コンパイル時に値が決定する数列を式と初期値から生成します。
	///	@param	T
	///	値の型。
	///	@param	Expr
	///	実行する関数。
	///	constexprな関数でなくてはなりません。
	///	@param	Init
	///	関数に渡す初期値。
	///	@param	N
	///	配列の要素数。
	///	N-1回関数が反復され、N個の要素が格納された配列が生成されます。
	template<class T, T Expr(T), T Init, size_t N>
	class ConstProgression : public ConstProgression<T, Expr, Init, N - 1>::template Concat<Expr(ConstProgression<T, Expr, Init, N - 1>::last)>::type
	{
	public:
		static constexpr T last = Expr(ConstProgression<T, Expr, Init, N - 1>::last);
	};
	template<class T, T Expr(T), T Init>
	class ConstProgression<T, Expr, Init, 1> : public ConstArray<T, Init>
	{
	public:
		static constexpr T last = Init;
	};
	template<class T, T Expr(T), T Init>
	class ConstProgression<T, Expr, Init, 0> : public ConstArray<T> {};
}
#endif // __stationaryorbit_core_constarray__
