#ifndef __stationaryorbit_core_iterator__
#define __stationaryorbit_core_iterator__
#include <stdexcept>
#include <utility>
#include <functional>
namespace zawa_ch::StationaryOrbit
{
	template<class T>
	class IIterator
	{
	public:
		typedef T ValueType;
		virtual void Reset() = 0;
		virtual bool HasValue() const = 0;
		virtual const T& Current() const = 0;
		virtual bool Next() = 0;

		void ForEach(const std::function<void(const T&)>& pred)
		{
			Reset();
			while (Next()) { pred(Current()); }
		}
	};

	template<class It, class resultT = typename It::ValueType, class predT = std::function<void(resultT)>>
	constexpr void ForEach(It iter, const predT& pred)
	{
		iter.Reset();
		while(iter.Next()) { pred(iter.Current()); }
	}

	template<class contT, class T = typename contT::value_type>
	class LegacyIterator : public IIterator<T>
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
	class LegacyReverseIterator : public IIterator<T>
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