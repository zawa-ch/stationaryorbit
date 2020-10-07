//	stationaryorbit/core/iterator
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
#ifndef __stationaryorbit_core_iterator__
#define __stationaryorbit_core_iterator__
#include <stdexcept>
#include <utility>
#include <functional>
#include <optional>
#include "stationaryorbit/exception.hpp"
#include "traits.hpp"
namespace zawa_ch::StationaryOrbit
{
	///	イテレータの初期位置。
	enum class IteratorOrigin
	{
		///	範囲の先頭。
		Begin = 0,
		///	範囲の末尾。
		End = -1,
	};

	///	このライブラリで用いられるイテレータの型特性を識別します。
	class IteratorTraits
	{
	private:
		IteratorTraits() = delete;
		IteratorTraits(const IteratorTraits&) = delete;
		IteratorTraits& operator=(const IteratorTraits&) = delete;
		IteratorTraits&& operator=(IteratorTraits&&) = delete;
		IteratorTraits(IteratorTraits&&) = delete;
		~IteratorTraits() = delete;

	public:
		///	イテレータの間隔を表すために用いる型。
		typedef std::make_signed_t<size_t> IteratorDiff_t;

	private:

		///	イテレータを識別します。
		template<class, class = std::void_t<>>
		struct IsIterator_t : std::false_type {};
		template<class T>
		struct IsIterator_t
		<
			T,
			std::void_t
			<
				typename T::ValueType,
				decltype( std::declval<T&>().Equals(std::declval<const T&>()) ),
				decltype( std::declval<T&>().Next() ),
				decltype( std::declval<T&>().Current() ),
				decltype( std::declval<T&>().HasValue() )
			>
		>
			: std::conjunction
			<
				std::is_convertible<decltype( std::declval<T&>().Equals(std::declval<const T&>()) ), bool>,
				std::is_convertible<decltype( std::declval<T&>().Next() ), bool>,
				std::is_convertible<decltype( std::declval<T&>().HasValue() ), bool>,
				std::is_convertible<decltype( std::declval<T&>().Current() ), typename T::ValueType>,
				std::is_copy_constructible<T>
			>
		{};

		///	始点および単方向の順序を持つイテレータを識別します。
		template<class, class = std::void_t<>>
		struct IsSequencialOrderIterator_t : std::false_type {};
		template<class T>
		struct IsSequencialOrderIterator_t
		<
			T,
			std::void_t
			<
				decltype( std::declval<T&>().Reset() )
			>
		>
			: std::conjunction
			<
				IsIterator_t<T>
			>
		{};

		///	始点・終点および双方向の順序を持つイテレータを識別します。
		template<class, class = std::void_t<>>
		struct IsBidirectionalOrderIterator_t : std::false_type {};
		template<class T>
		struct IsBidirectionalOrderIterator_t
		<
			T,
			std::void_t
			<
				decltype( std::declval<T&>().Previous() ),
				decltype( std::declval<T&>().Reset(std::declval<const IteratorOrigin&>()) ),
				decltype( std::declval<T&>().IsBeforeBegin() ),
				decltype( std::declval<T&>().IsAfterEnd() )
			>
		>
			: std::conjunction
			<
				IsSequencialOrderIterator_t<T>,
				std::is_convertible<decltype( std::declval<T&>().IsBeforeBegin() ), bool>,
				std::is_convertible<decltype( std::declval<T&>().IsAfterEnd() ), bool>,
				std::is_convertible<decltype( std::declval<T&>().Previous() ), bool>
			>
		{};

		///	要素が線形に配置されているイテレータを識別します。
		template<class, class = std::void_t<>>
		struct IsLinearOrderIterator_t : std::false_type {};
		template<class T>
		struct IsLinearOrderIterator_t
		<
			T,
			std::void_t
			<
				decltype( std::declval<T&>().Compare(std::declval<const T&>()) ),
				decltype( std::declval<T&>().Next(std::declval<const IteratorDiff_t&>()) ),
				decltype( std::declval<T&>().Previous(std::declval<const IteratorDiff_t&>()) )
			>
		>
			: std::conjunction
			<
				IsBidirectionalOrderIterator_t<T>,
				std::is_convertible<decltype( std::declval<T&>().Compare(std::declval<const T&>()) ), bool>,
				std::is_convertible<decltype( std::declval<T&>().Next(std::declval<const IteratorDiff_t&>()) ), bool>,
				std::is_convertible<decltype( std::declval<T&>().Previous(std::declval<const IteratorDiff_t&>()) ), bool>
			>
		{};
	public:
		///	イテレータを識別します。
		template<class T> inline constexpr static bool IsIterator = IsIterator_t<T>::value;
		///	始点および単方向の順序を持つイテレータを識別します。
		template<class T> inline constexpr static bool IsSequencialOrderIterator = IsSequencialOrderIterator_t<T>::value;
		///	始点・終点および双方向の順序を持つイテレータを識別します。
		template<class T> inline constexpr static bool IsBidirectionalOrderIterator = IsBidirectionalOrderIterator_t<T>::value;
		///	要素が線形に配置されているイテレータを識別します。
		template<class T> inline constexpr static bool IsLinearOrderIterator = IsLinearOrderIterator_t<T>::value;
	};

	///	イテレータを使用した処理を行います。
	class ItrProcesser
	{
	public:
		///	イテレータで列挙されるすべての要素に対して、指定された述語を適用します。
		///	@note
		///	計算時間はイテレータの要素数に比例。
		template<class It, class resultT = typename It::ValueType, class predT = std::function<void(resultT)>>
		constexpr static void ForEach(It iter, const predT& pred)
		{
			iter.Reset();
			while(iter.HasValue()) { pred(iter.Current()); (void)iter.Next(); }
		}
	};

	///	このライブラリで使用されるイテレータをC++標準のイテレータに変換します。
	///	@param	T
	///	変換するイテレータの型。 @a IteratorTraits::IsIterator を満たす必要があります。
	template<class T, class = void>
	class IteratorAdapter
	{
		static_assert(IteratorTraits::IsIterator<T>, "テンプレート型 T はIteratorTraits::IsIteratorを満たす必要があります。");
		template<class, class> friend class IteratorAdaptContainer;
	private:
		std::optional<T> _itr;
	public:
		///	イテレータを渡してオブジェクトを生成します。
		constexpr explicit IteratorAdapter(const T& itr) : _itr(itr) {}
	private:
		///	イテレータの持たないオブジェクトを生成します。
		constexpr explicit IteratorAdapter(const std::nullptr_t& itr) : _itr(std::nullopt) {}

	public:
		///	指定されたオブジェクトと等価であるか比較します。
		constexpr bool Equals(const IteratorAdapter<T>& other) const
		{
			if (!_itr.has_value()) { return _itr == other._itr; }
			if (other._itr.has_value()) { return _itr->Equals(*(other._itr)); }
			else { return !_itr->HasValue(); }
		}
		constexpr bool operator==(const IteratorAdapter<T>& other) const { return Equals(other); }
		constexpr bool operator!=(const IteratorAdapter<T>& other) const { return !Equals(other); }
		constexpr typename std::iterator_traits<IteratorAdapter<T>>::reference operator*() const
		{
			if (!_itr.has_value()) { throw InvalidOperationException("このオブジェクトはイテレータを持ちません。"); }
			return _itr->Current();
		}
		constexpr IteratorAdapter<T>& operator++()
		{
			if (!_itr.has_value()) { throw InvalidOperationException("このオブジェクトはイテレータを持ちません。"); }
			(void)_itr->Next();
			return *this;
		}
		constexpr IteratorAdapter<T> operator++(int)
		{
			if (!_itr.has_value()) { throw InvalidOperationException("このオブジェクトはイテレータを持ちません。"); }
			auto result = *this;
			(void)_itr->Next();
			return result;
		}
	};
	///	このライブラリで使用されるイテレータをC++標準のイテレータに変換します。
	///	@param	T
	///	変換するイテレータの型。 @a IteratorTraits::IsBidirectionalOrderIterator を満たす場合の拡張が存在します。
	template<class T>
	class IteratorAdapter<T, std::enable_if_t<IteratorTraits::IsBidirectionalOrderIterator<T>>>
	{
		static_assert(IteratorTraits::IsBidirectionalOrderIterator<T>, "テンプレート型 T はIteratorTraits::IsBidirectionalOrderIteratorを満たす必要があります。");
		template<class, class> friend class IteratorAdaptContainer;
	private:
		std::optional<T> _itr;
	public:
		///	イテレータを渡してオブジェクトを生成します。
		constexpr explicit IteratorAdapter(const T& itr) : _itr(itr) {}
	private:
		///	イテレータの持たないオブジェクトを生成します。
		constexpr explicit IteratorAdapter(const std::nullptr_t& itr) : _itr(std::nullopt) {}

	public:
		///	指定されたオブジェクトと等価であるか比較します。
		constexpr bool Equals(const IteratorAdapter<T>& other) const
		{
			if (!_itr.has_value()) { return _itr == other._itr; }
			if (other._itr.has_value()) { return _itr->Equals(*(other._itr)); }
			else { return !_itr->HasValue(); }
		}
		constexpr bool operator==(const IteratorAdapter<T>& other) const { return Equals(other); }
		constexpr bool operator!=(const IteratorAdapter<T>& other) const { return !Equals(other); }
		constexpr typename std::iterator_traits<IteratorAdapter<T>>::reference operator*() const
		{
			if (!_itr.has_value()) { throw InvalidOperationException("このオブジェクトはイテレータを持ちません。"); }
			return _itr->Current();
		}
		constexpr IteratorAdapter<T>& operator++()
		{
			if (!_itr.has_value()) { throw InvalidOperationException("このオブジェクトはイテレータを持ちません。"); }
			(void)_itr->Next();
			return *this;
		}
		constexpr IteratorAdapter<T> operator++(int)
		{
			if (!_itr.has_value()) { throw InvalidOperationException("このオブジェクトはイテレータを持ちません。"); }
			auto result = *this;
			(void)_itr->Next();
			return result;
		}
		constexpr IteratorAdapter<T>& operator--()
		{
			if (!_itr.has_value()) { throw InvalidOperationException("このオブジェクトはイテレータを持ちません。"); }
			(void)_itr->Previous();
			return *this;
		}
		constexpr IteratorAdapter<T> operator--(int)
		{
			if (!_itr.has_value()) { throw InvalidOperationException("このオブジェクトはイテレータを持ちません。"); }
			auto result = *this;
			(void)_itr->Previous();
			return result;
		}
	};

	///	このライブラリで使用されるイテレータをC++標準の逆イテレータに変換します。
	///	@param	T
	///	変換するイテレータの型。 @a IteratorTraits::IsBidirectionalOrderIterator を満たす必要があります。
	template<class T>
	class IteratorReverseAdapter
	{
		static_assert(IteratorTraits::IsBidirectionalOrderIterator<T>, "テンプレート型 T はIteratorTraits::IsBidirectionalOrderIteratorを満たす必要があります。");
		template<class, class> friend class IteratorAdaptContainer;
	private:
		std::optional<T> _itr;
	public:
		///	イテレータを渡してオブジェクトを生成します。
		constexpr explicit IteratorReverseAdapter(const T& itr) : _itr(itr) {}
	private:
		///	イテレータの持たないオブジェクトを生成します。
		constexpr explicit IteratorReverseAdapter(const std::nullptr_t& itr) : _itr(std::nullopt) {}

	public:
		///	指定されたオブジェクトと等価であるか比較します。
		bool Equals(const IteratorReverseAdapter<T>& other) const
		{
			if (!_itr.has_value()) { return _itr == other._itr; }
			if (other._itr.has_value()) { return _itr->Equals(*(other._itr)); }
			else { return !_itr->HasValue(); }
		}
		bool operator==(const IteratorReverseAdapter<T>& other) const { return Equals(other); }
		bool operator!=(const IteratorReverseAdapter<T>& other) const { return !Equals(other); }
		typename std::iterator_traits<IteratorReverseAdapter<T>>::reference operator*() const
		{
			if (!_itr.has_value()) { throw InvalidOperationException("このオブジェクトはイテレータを持ちません。"); }
			return _itr->Current();
		}
		IteratorReverseAdapter<T>& operator++()
		{
			if (!_itr.has_value()) { throw InvalidOperationException("このオブジェクトはイテレータを持ちません。"); }
			(void)_itr->Previous();
			return *this;
		}
		IteratorReverseAdapter<T> operator++(int)
		{
			if (!_itr.has_value()) { throw InvalidOperationException("このオブジェクトはイテレータを持ちません。"); }
			auto result = *this;
			(void)_itr->Previous();
			return result;
		}
		IteratorReverseAdapter<T>& operator--()
		{
			if (!_itr.has_value()) { throw InvalidOperationException("このオブジェクトはイテレータを持ちません。"); }
			(void)_itr->Next();
			return *this;
		}
		IteratorReverseAdapter<T> operator--(int)
		{
			if (!_itr.has_value()) { throw InvalidOperationException("このオブジェクトはイテレータを持ちません。"); }
			auto result = *this;
			(void)_itr->Next();
			return result;
		}
	};

	///	このライブラリで使用されるイテレータをC++範囲ベースforで使用できるようにします。
	///	@param	T
	///	変換するイテレータの型。 @a IteratorTraits::IsSequencialOrderIterator を満たす必要があります。
	template<class T, class = void>
	class IteratorAdaptContainer
	{
		static_assert(IteratorTraits::IsSequencialOrderIterator<T>, "テンプレート型 T はIteratorTraits::IsSequencialOrderIteratorを満たす必要があります。");
	public:
		typedef typename T::ValueType value_type;
		typedef typename T::ValueType& reference;
		typedef const typename T::ValueType& const_reference;
		typedef IteratorAdapter<T> iterator;
		typedef IteratorAdapter<T> const_iterator;
		typedef typename IteratorTraits::IteratorDiff_t difference_type;
		typedef size_t size_type;
	private:
		T _itr;
	public:
		explicit IteratorAdaptContainer(const T& itr) : _itr(itr) {}

		///	最初の要素を指すイテレータを取得します。
		iterator begin() const { auto result = _itr; result.Reset(); return iterator(result); }
		///	最後の要素を指すイテレータを取得します。
		iterator end() const { return IteratorAdapter<T>(nullptr); }
		///	最初の要素を指すイテレータを取得します。
		const_iterator cbegin() const { return begin(); }
		///	最後の要素を指すイテレータを取得します。
		const_iterator cend() const { return end(); }
	};
	///	このライブラリで使用されるイテレータをC++範囲ベースforで使用できるようにします。
	///	@param	T
	///	変換するイテレータの型。 @a IteratorTraits::IsBidirectionalOrderIterator を満たす場合の拡張が存在します。
	template<class T>
	class IteratorAdaptContainer<T, std::enable_if_t<IteratorTraits::IsBidirectionalOrderIterator<T>>>
	{
		static_assert(IteratorTraits::IsBidirectionalOrderIterator<T>, "テンプレート型 T はIteratorTraits::IsBidirectionalOrderIteratorを満たす必要があります。");
	public:
		typedef typename T::ValueType value_type;
		typedef typename T::ValueType& reference;
		typedef const typename T::ValueType& const_reference;
		typedef IteratorAdapter<T> iterator;
		typedef IteratorAdapter<T> const_iterator;
		typedef IteratorReverseAdapter<T> reverse_iterator;
		typedef IteratorReverseAdapter<T> reverse_const_iterator;
		typedef typename IteratorTraits::IteratorDiff_t difference_type;
		typedef size_t size_type;
	private:
		T _itr;
	public:
		explicit IteratorAdaptContainer(const T& itr) : _itr(itr) {}

		///	最初の要素を指すイテレータを取得します。
		iterator begin() const { auto result = _itr; result.Reset(); return iterator(result); }
		///	最後の要素を指すイテレータを取得します。
		iterator end() const { return iterator(nullptr); }
		///	最初の要素を指すイテレータを取得します。
		const_iterator cbegin() const { return begin(); }
		///	最後の要素を指すイテレータを取得します。
		const_iterator cend() const { return end(); }
		///	最初の要素を指す逆イテレータを取得します。
		reverse_iterator rbegin() const { auto result = _itr; result.Reset(IteratorOrigin::End); return reverse_iterator(result); }
		///	最後の要素を指す逆イテレータを取得します。
		reverse_iterator rend() const { return reverse_iterator(nullptr); }
		///	最初の要素を指す逆イテレータを取得します。
		reverse_const_iterator crbegin() const { return rbegin(); }
		///	最後の要素を指す逆イテレータを取得します。
		reverse_const_iterator crend() const { return rend(); }
	};

	template<class contT, class T = typename contT::value_type>
	class LegacyIterator
	{
	public:
		typedef contT ContainerType;
		typedef T ValueType;
	private:
		const ContainerType& _cont;
		typename contT::const_iterator _itr;
	public:
		LegacyIterator(const ContainerType& container) : _cont(container) {}
		virtual void Reset() { _itr = _cont.cbegin(); }
		virtual bool HasValue() const { return _itr != _cont.cend(); }
		virtual const T& Current() const { if (HasValue()) { return *_itr; } else { throw std::out_of_range("要素の範囲外にあるイテレータに対して逆参照を試みました。"); } }
		virtual bool Next() { if (HasValue()) { ++_itr; } return _itr != _cont.cend(); }
	};

	template<class contT, class T = typename contT::value_type>
	class LegacyReverseIterator
	{
	public:
		typedef contT ContainerType;
		typedef T ValueType;
	private:
		const ContainerType& _cont;
		typename contT::const_reverse_iterator _itr;
	public:
		LegacyReverseIterator(const ContainerType& container) : _cont(container) {}
		virtual void Reset() { _itr = _cont.crbegin(); }
		virtual bool HasValue() const { return _itr != _cont.crend(); }
		virtual const T& Current() const { if (HasValue()) { return *_itr; } else { throw std::out_of_range("要素の範囲外にあるイテレータに対して逆参照を試みました。"); } }
		virtual bool Next() { if (HasValue()) { ++_itr; } return _itr != _cont.crend(); }
	};
}
namespace std
{
	template<class T>
	class iterator_traits<zawa_ch::StationaryOrbit::IteratorAdapter<T>>
	{
	public:
		typedef typename T::ValueType value_type;
		typedef zawa_ch::StationaryOrbit::IteratorTraits::IteratorDiff_t difference_type;
		typedef const value_type& reference;
		typedef const value_type* pointer;
		typedef std::input_iterator_tag iteretor_category;
	};
	template<class T>
	class iterator_traits<zawa_ch::StationaryOrbit::IteratorReverseAdapter<T>>
	{
	public:
		typedef typename T::ValueType value_type;
		typedef zawa_ch::StationaryOrbit::IteratorTraits::IteratorDiff_t difference_type;
		typedef const value_type& reference;
		typedef const value_type* pointer;
		typedef std::input_iterator_tag iteretor_category;
	};
}
#endif // __stationaryorbit_core_iterator__