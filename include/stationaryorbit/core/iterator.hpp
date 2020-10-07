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
#include "traits.hpp"
namespace zawa_ch::StationaryOrbit
{
	///	イテレータの初期位置。
	enum class IteratorOrigin
	{
		Begin = 0,
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
#endif // __stationaryorbit_core_iterator__