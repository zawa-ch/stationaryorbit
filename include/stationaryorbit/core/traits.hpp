#ifndef __stationaryorbit_core_traits__
#define __stationaryorbit_core_traits__
#include <type_traits>
#include <bitset>
namespace zawa_ch::StationaryOrbit
{
	///	このライブラリで用いられる型特性の識別を行います。
	class Traits final
	{
	private:
		Traits() = delete;
		Traits(const Traits&) = delete;
		Traits& operator=(const Traits&) = delete;
		Traits&& operator=(Traits&&) = delete;
		Traits(Traits&&) = delete;
		~Traits() = delete;

		template<class, class, class = std::void_t<>>
		struct Addable_t : std::false_type {};
		template<class T, class U>
		struct Addable_t<T, U, std::void_t< decltype( std::declval<T&>() + std::declval<U&>() ) > > : std::true_type {};

		template<class, class, class = std::void_t<>>
		struct Subtractable_t : std::false_type {};
		template<class T, class U>
		struct Subtractable_t<T, U, std::void_t< decltype( std::declval<T&>() - std::declval<U&>() ) > > : std::true_type {};

		template<class, class, class = std::void_t<>>
		struct HasMultiplication_t : std::false_type {};
		template<class T, class U>
		struct HasMultiplication_t<T, U, std::void_t< decltype( std::declval<T&>() * std::declval<U&>() ) > > : std::true_type {};

		template<class, class, class = std::void_t<>>
		struct HasDivision_t : std::false_type {};
		template<class T, class U>
		struct HasDivision_t<T, U, std::void_t< decltype( std::declval<T&>() / std::declval<U&>() ) > > : std::true_type {};

		template<class T, class U>
		struct ArithmeticOperatable_t : std::conjunction<Addable_t<T, U>, Subtractable_t<T, U>, HasMultiplication_t<T, U>, HasDivision_t<T, U>> {};

		template<class, class, class = std::void_t<>>
		struct HasComparamentLarger : std::false_type {};
		template<class T, class U>
		struct HasComparamentLarger<T, U, std::void_t< decltype( std::declval<T&>() > std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() > std::declval<U&>() ), bool> {};

		template<class, class, class = std::void_t<>>
		struct HasComparamentSmaller : std::false_type {};
		template<class T, class U>
		struct HasComparamentSmaller<T, U, std::void_t< decltype( std::declval<T&>() < std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() < std::declval<U&>() ), bool> {};

		template<class, class, class = std::void_t<>>
		struct HasComparamentLeast : std::false_type {};
		template<class T, class U>
		struct HasComparamentLeast<T, U, std::void_t< decltype( std::declval<T&>() >= std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() >= std::declval<U&>() ), bool> {};

		template<class, class, class = std::void_t<>>
		struct HasComparamentMost : std::false_type {};
		template<class T, class U>
		struct HasComparamentMost<T, U, std::void_t< decltype( std::declval<T&>() <= std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() <= std::declval<U&>() ), bool> {};

		template<class T, class U>
		struct Comparable_t : std::conjunction< HasComparamentLarger<T, U>, HasComparamentSmaller<T, U>, HasComparamentLeast<T, U>, HasComparamentMost<T, U> > {};

		template<class, class, class = std::void_t<>>
		struct HasEqual : std::false_type {};
		template<class T, class U>
		struct HasEqual<T, U, std::void_t< decltype( std::declval<T&>() == std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() == std::declval<U&>() ), bool> {};

		template<class, class, class = std::void_t<>>
		struct HasNotEqual : std::false_type {};
		template<class T, class U>
		struct HasNotEqual<T, U, std::void_t< decltype( std::declval<T&>() != std::declval<U&>() ) > >
			: std::is_convertible< decltype( std::declval<T&>() != std::declval<U&>() ), bool> {};

		template<class T, class U>
		struct Equatable_t : std::conjunction< HasEqual<T, U>, HasNotEqual<T, U> > {};

	public:
		///	基本的な四則演算を持つ型を識別します。
		template<class T, class U = T> inline constexpr static bool ArithmeticOperatable = ArithmeticOperatable_t<T, U>::value;
		///	指定された型のオブジェクトとの比較が可能な型を識別します。
		template<class T, class U = T> inline constexpr static bool Comparable = Comparable_t<T, U>::value;
		///	指定された型のオブジェクトとの比較が可能な型を識別します。
		template<class T, class U = T> inline constexpr static bool Equatable = Equatable_t<T, U>::value;
	};

	///	指定された型の有効なビット幅を識別するための機能を提供します。
	template<class T> struct BitWidth_t : std::integral_constant<size_t, 8U * sizeof(T)>
	{
		static_assert(std::is_integral_v<T>, "ビット幅の計数は整数型、boolなどの固定幅のビットシーケンスでのみ有効です。");
	};
	template<> struct BitWidth_t<bool> : std::integral_constant<size_t, 1U> {};
	template<std::size_t N> struct BitWidth_t<std::bitset<N>> : std::integral_constant<size_t, N> {};
	///	指定された型の有効なビット幅を識別します。
	template<class T> inline constexpr size_t BitWidth = BitWidth_t<T>::value;
}
#endif // __stationaryorbit_core_traits__