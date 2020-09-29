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
namespace zawa_ch::StationaryOrbit
{
	enum class IteratorTraits
	{
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
			while(iter.Next()) { pred(iter.Current()); }
		}
	};
	template<class contT, class T = typename contT::value_type>
	class LegacyIterator
	{
	public:
		typedef contT ContainerType;
		typedef T ValueType;
		typedef typename contT::const_iterator IteratorType;
	private:
		const ContainerType& _cont;
		IteratorType _itr;
		bool _start;
	public:
		LegacyIterator(const ContainerType& container) : _cont(container), _start(false) {}
		virtual void Reset()
		{
			_start = false;
		}
		virtual bool HasValue() const
		{
			if (_start) { return _itr != _cont.cend(); } else { return false; }
		}
		virtual const T& Current() const
		{
			if (HasValue()) { return *_itr; } else { throw std::out_of_range("要素の範囲外にあるイテレータに対して逆参照を試みました。"); }
		}
		virtual bool Next()
		{
			if (HasValue()) { ++_itr; } else { _itr = _cont.cbegin(); _start = true; }
			return _itr != _cont.cend();
		}
	};
	template<class contT, class T = typename contT::value_type>
	class LegacyReverseIterator
	{
	public:
		typedef contT ContainerType;
		typedef T ValueType;
		typedef typename contT::const_reverse_iterator IteratorType;
	private:
		const ContainerType& _cont;
		IteratorType _itr;
		bool _start;
	public:
		LegacyReverseIterator(const ContainerType& container) : _cont(container), _start(false) {}
		virtual void Reset()
		{
			_start = false;
		}
		virtual bool HasValue() const
		{
			if (_start) { return _itr != _cont.crend(); } else { return false; }
		}
		virtual const T& Current() const
		{
			if (HasValue()) { return *_itr; } else { throw std::out_of_range("要素の範囲外にあるイテレータに対して逆参照を試みました。"); }
		}
		virtual bool Next()
		{
			if (HasValue()) { ++_itr; } else { _itr = _cont.crbegin(); _start = true; }
			return _itr != _cont.crend();
		}
	};
}
#endif // __stationaryorbit_core_iterator__