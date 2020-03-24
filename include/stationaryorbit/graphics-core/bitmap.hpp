#ifndef __stationaryorbit_graphics_core_bitmap__
#define __stationaryorbit_graphics_core_bitmap__
#include <type_traits>
#include <vector>
#include "stationaryorbit/exception/soexcept"
#include "fundamental.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	template<class Tp> class BitmapConstPixelRef;
	template<class Tp> class BitmapPixelRef;
	class BitmapIterators;
	template<class Tp> class BitmapBase;

	template<class Tp>
	class BitmapConstPixelRef
	{
		static_assert(std::is_arithmetic_v<Tp>, "テンプレート引数 Tp は数値型である必要があります。");
		friend class BitmapBase<Tp>;
	private: // contains
		const Tp* _ref;
		const int _ch;
	private: // construct
		BitmapConstPixelRef(const Tp* ref, const int& ch) : _ref(ref), _ch(ch) {}
	public: // copy/move/destruct
		~BitmapConstPixelRef() = default;
	public: // member
		const Tp& Index(const int& ch) const { if ((ch < 0)||(_ch <= ch)) { throw std::out_of_range("指定されたインデックスは境界を超えています。"); } return _ref[ch]; }
		const Tp& operator[](const size_t& index) const { return Index(index); }
	};
	template<class Tp>
	class BitmapPixelRef
	{
		static_assert(std::is_arithmetic_v<Tp>, "テンプレート引数 Tp は数値型である必要があります。");
		friend class BitmapBase<Tp>;
	private: // contains
		Tp* _ref;
		const int _ch;
	private: // construct
		BitmapPixelRef(Tp* ref, const int& ch) : _ref(ref), _ch(ch) {}
	public: // copy/move/destruct
		~BitmapPixelRef() = default;
	public: // member
		const Tp& Index(const int& ch) const { if ((ch < 0)||(_ch <= ch)) { throw std::out_of_range("指定されたインデックスは境界を超えています。"); } return _ref[ch]; }
		const Tp& operator[](const size_t& index) const { return Index(index); }
		Tp& Index(const int& ch) { if ((ch < 0)||(_ch <= ch)) { throw std::out_of_range("指定されたインデックスは境界を超えています。"); } return _ref[ch]; }
		Tp& operator[](const size_t& index) { return Index(index); }
	};
	class BitmapIterators
	{
	public:
		template<class Tp>
		class Iterator
		{
		private:
			BitmapBase<Tp>& _inst;
			size_t _pos;
		public:
			Iterator(BitmapBase<Tp>& inst, const size_t& position) noexcept : _inst(inst), _pos(position) {}
			BitmapPixelRef<Tp> Current()
			{
				auto size = _inst.Size();
				return _inst.Index(DisplayPoint(_pos % size.Width(), _pos / size.Width()));
			}
			Iterator<Tp>& Forward() { ++_pos; return *this; }
			Iterator<Tp>& Forward(const int& count) { _pos += count; return *this; }
			Iterator<Tp>& Backward() { --_pos; return *this; }
			Iterator<Tp>& Backward(const int& count) { _pos -= count; return *this; }
			bool Equals(const Iterator<Tp>& other) const noexcept { return (&_inst == &other._inst)&&(_pos == other._pos); }
			BitmapPixelRef<Tp> operator*() { return Current(); }
			Iterator<Tp> operator++() { return Forward(); }
			Iterator<Tp> operator--() { return Backward(); }
			bool operator==(const Iterator<Tp>& other) const noexcept { return Equals(other); }
			bool operator!=(const Iterator<Tp>& other) const noexcept { return !Equals(other); }
		};
		template<class Tp>
		class ConstIterator
		{
		private:
			const BitmapBase<Tp>& _inst;
			size_t _pos;
		public:
			ConstIterator(const BitmapBase<Tp>& inst, const size_t& position) noexcept : _inst(inst), _pos(position) {}
			BitmapConstPixelRef<Tp> Current()
			{
				auto size = _inst.Size();
				return _inst.Index(DisplayPoint(_pos % size.Width(), _pos / size.Width()));
			}
			ConstIterator<Tp>& Forward() { ++_pos; return *this; }
			ConstIterator<Tp>& Forward(const int& count) { _pos += count; return *this; }
			ConstIterator<Tp>& Backward() { --_pos; return *this; }
			ConstIterator<Tp>& Backward(const int& count) { _pos -= count; return *this; }
			bool Equals(const ConstIterator<Tp>& other) const noexcept { return (&_inst == &other._inst)&&(_pos == other._pos); }
			BitmapConstPixelRef<Tp> operator*() { return Current(); }
			ConstIterator<Tp> operator++() { return Forward(); }
			ConstIterator<Tp> operator--() { return Backward(); }
			bool operator==(const ConstIterator<Tp>& other) const noexcept { return Equals(other); }
			bool operator!=(const ConstIterator<Tp>& other) const noexcept { return !Equals(other); }
		};
		template<class Tp>
		class ReverceIterator
		{
		private:
			BitmapBase<Tp>& _inst;
			size_t _pos;
		public:
			ReverceIterator(BitmapBase<Tp>& inst, const size_t& position) noexcept : _inst(inst), _pos(position) {}
			BitmapPixelRef<Tp> Current()
			{
				auto size = _inst.Size();
				return _inst.Index(DisplayPoint((_pos - 1) % size.Width(), (_pos - 1) / size.Width()));
			}
			ReverceIterator<Tp>& Forward() { --_pos; return *this; }
			ReverceIterator<Tp>& Forward(const int& count) { _pos -= count; return *this; }
			ReverceIterator<Tp>& Backward() { ++_pos; return *this; }
			ReverceIterator<Tp>& Backward(const int& count) { _pos += count; return *this; }
			bool Equals(const ReverceIterator<Tp>& other) const noexcept { return (&_inst == &other._inst)&&(_pos == other._pos); }
			BitmapPixelRef<Tp> operator*() { return Current(); }
			ReverceIterator<Tp> operator++() { return Forward(); }
			ReverceIterator<Tp> operator--() { return Backward(); }
			bool operator==(const ReverceIterator<Tp>& other) const noexcept { return Equals(other); }
			bool operator!=(const ReverceIterator<Tp>& other) const noexcept { return !Equals(other); }
		};
		template<class Tp>
		class ConstReverceIterator
		{
		private:
			const BitmapBase<Tp>& _inst;
			size_t _pos;
		public:
			ConstReverceIterator(const BitmapBase<Tp>& inst, const size_t& position) noexcept : _inst(inst), _pos(position) {}
			BitmapConstPixelRef<Tp> Current()
			{
				auto size = _inst.Size();
				return _inst.Index(DisplayPoint((_pos - 1) % size.Width(), (_pos - 1) / size.Width()));
			}
			ConstReverceIterator<Tp>& Forward() { --_pos; return *this; }
			ConstReverceIterator<Tp>& Forward(const int& count) { _pos -= count; return *this; }
			ConstReverceIterator<Tp>& Backward() { ++_pos; return *this; }
			ConstReverceIterator<Tp>& Backward(const int& count) { _pos += count; return *this; }
			bool Equals(const ConstReverceIterator<Tp>& other) const noexcept { return (&_inst == &other._inst)&&(_pos == other._pos); }
			BitmapConstPixelRef<Tp> operator*() { return Current(); }
			ConstReverceIterator<Tp> operator++() { return Forward(); }
			ConstReverceIterator<Tp> operator--() { return Backward(); }
			bool operator==(const ConstReverceIterator<Tp>& other) const noexcept { return Equals(other); }
			bool operator!=(const ConstReverceIterator<Tp>& other) const noexcept { return !Equals(other); }
		};
		template<class Tp>
		class VerticalIterator
		{
		private:
			BitmapBase<Tp>& _inst;
			size_t _pos;
		public:
			VerticalIterator(BitmapBase<Tp>& inst, const size_t& position) noexcept : _inst(inst), _pos(position) {}
			BitmapPixelRef<Tp> Current()
			{
				auto size = _inst.Size();
				return _inst.Index(DisplayPoint(_pos / size.Height(), _pos % size.Height()));
			}
			VerticalIterator<Tp>& Forward() { ++_pos; return *this; }
			VerticalIterator<Tp>& Forward(const int& count) { _pos += count; return *this; }
			VerticalIterator<Tp>& Backward() { --_pos; return *this; }
			VerticalIterator<Tp>& Backward(const int& count) { _pos -= count; return *this; }
			bool Equals(const VerticalIterator<Tp>& other) const noexcept { return (&_inst == &other._inst)&&(_pos == other._pos); }
			BitmapPixelRef<Tp> operator*() { return Current(); }
			VerticalIterator<Tp> operator++() { return Forward(); }
			VerticalIterator<Tp> operator--() { return Backward(); }
			bool operator==(const VerticalIterator<Tp>& other) const noexcept { return Equals(other); }
			bool operator!=(const VerticalIterator<Tp>& other) const noexcept { return !Equals(other); }
		};
		template<class Tp>
		class VerticalConstIterator
		{
		private:
			const BitmapBase<Tp>& _inst;
			size_t _pos;
		public:
			VerticalConstIterator(const BitmapBase<Tp>& inst, const size_t& position) noexcept : _inst(inst), _pos(position) {}
			BitmapConstPixelRef<Tp> Current()
			{
				auto size = _inst.Size();
				return _inst.Index(DisplayPoint(_pos / size.Height(), _pos % size.Height()));
			}
			VerticalConstIterator<Tp>& Forward() { ++_pos; return *this; }
			VerticalConstIterator<Tp>& Forward(const int& count) { _pos += count; return *this; }
			VerticalConstIterator<Tp>& Backward() { --_pos; return *this; }
			VerticalConstIterator<Tp>& Backward(const int& count) { _pos -= count; return *this; }
			bool Equals(const VerticalConstIterator<Tp>& other) const noexcept { return (&_inst == &other._inst)&&(_pos == other._pos); }
			BitmapConstPixelRef<Tp> operator*() { return Current(); }
			VerticalConstIterator<Tp> operator++() { return Forward(); }
			VerticalConstIterator<Tp> operator--() { return Backward(); }
			bool operator==(const VerticalConstIterator<Tp>& other) const noexcept { return Equals(other); }
			bool operator!=(const VerticalConstIterator<Tp>& other) const noexcept { return !Equals(other); }
		};
		template<class Tp>
		class VerticalReverceIterator
		{
		private:
			BitmapBase<Tp>& _inst;
			size_t _pos;
		public:
			VerticalReverceIterator(BitmapBase<Tp>& inst, const size_t& position) noexcept : _inst(inst), _pos(position) {}
			BitmapPixelRef<Tp> Current()
			{
				auto size = _inst.Size();
				return _inst.Index(DisplayPoint((_pos - 1) / size.Height(), (_pos - 1) % size.Height()));
			}
			VerticalReverceIterator<Tp>& Forward() { --_pos; return *this; }
			VerticalReverceIterator<Tp>& Forward(const int& count) { _pos -= count; return *this; }
			VerticalReverceIterator<Tp>& Backward() { ++_pos; return *this; }
			VerticalReverceIterator<Tp>& Backward(const int& count) { _pos += count; return *this; }
			bool Equals(const VerticalReverceIterator<Tp>& other) const noexcept { return (&_inst == &other._inst)&&(_pos == other._pos); }
			BitmapPixelRef<Tp> operator*() { return Current(); }
			VerticalReverceIterator<Tp> operator++() { return Forward(); }
			VerticalReverceIterator<Tp> operator--() { return Backward(); }
			bool operator==(const VerticalReverceIterator<Tp>& other) const noexcept { return Equals(other); }
			bool operator!=(const VerticalReverceIterator<Tp>& other) const noexcept { return !Equals(other); }
		};
		template<class Tp>
		class VerticalConstReverceIterator
		{
		private:
			const BitmapBase<Tp>& _inst;
			size_t _pos;
		public:
			VerticalConstReverceIterator(const BitmapBase<Tp>& inst, const size_t& position) noexcept : _inst(inst), _pos(position) {}
			BitmapConstPixelRef<Tp> Current()
			{
				auto size = _inst.Size();
				return _inst.Index(DisplayPoint((_pos - 1) / size.Height(), (_pos - 1) % size.Height()));
			}
			VerticalConstReverceIterator<Tp>& Forward() { --_pos; return *this; }
			VerticalConstReverceIterator<Tp>& Forward(const int& count) { _pos -= count; return *this; }
			VerticalConstReverceIterator<Tp>& Backward() { ++_pos; return *this; }
			VerticalConstReverceIterator<Tp>& Backward(const int& count) { _pos += count; return *this; }
			bool Equals(const VerticalConstReverceIterator<Tp>& other) const noexcept { return (&_inst == &other._inst)&&(_pos == other._pos); }
			BitmapConstPixelRef<Tp> operator*() { return Current(); }
			VerticalConstReverceIterator<Tp> operator++() { return Forward(); }
			VerticalConstReverceIterator<Tp> operator--() { return Backward(); }
			bool operator==(const VerticalConstReverceIterator<Tp>& other) const noexcept { return Equals(other); }
			bool operator!=(const VerticalConstReverceIterator<Tp>& other) const noexcept { return !Equals(other); }
		};
	};
	template<class Tp>
	class BitmapBase
	{
		static_assert(std::is_arithmetic_v<Tp>, "テンプレート引数 Tp は数値型である必要があります。");
	public:
		typedef Tp ValueType;
		typedef BitmapConstPixelRef<Tp> ConstRefType;
		typedef BitmapPixelRef<Tp> RefType;
		typedef BitmapIterators::Iterator<Tp> IteratorType;
		typedef BitmapIterators::ConstIterator<Tp> ConstIteratorType;
		typedef BitmapIterators::ReverceIterator<Tp> ReverceIteratorType;
		typedef BitmapIterators::ConstReverceIterator<Tp> ConstReverceIteratorType;
		typedef BitmapIterators::VerticalIterator<Tp> VerticalIteratorType;
		typedef BitmapIterators::VerticalConstIterator<Tp> VerticalConstIteratorType;
		typedef BitmapIterators::VerticalReverceIterator<Tp> VerticalReverceIteratorType;
		typedef BitmapIterators::VerticalConstReverceIterator<Tp> VerticalConstReverceIteratorType;
	private: // contains
		std::vector<ValueType> _data;
		RectangleSize _size;
		int _ch;
	private: // internal
		size_t SolveIndex(const DisplayPoint& position) const
		{
			if ((position.X() < 0)||(position.Y() < 0)) { throw std::invalid_argument("position の要素のいずれかが負です。"); }
			if ((_size.Width() <= position.X())||(_size.Height() <= position.Y())) { throw std::out_of_range("指定されたインデックスは境界を超えています。"); }
			return (position.Y() * _size.Width()) + position.X();
		}
		static size_t SolveCount(const RectangleSize& size)
		{
			if ((0 <= size.Height())&&(0 <= size.Width())) { return size.Width() * size.Height(); }
			else { throw std::invalid_argument("size の要素のいずれかが負です。"); }
		}
		static size_t SolveCount(const RectangleSize& size, const int& channel)
		{
			if ((0 <= size.Height())&&(0 <= size.Width())&&(0 <= channel)) { return size.Width() * size.Height() * channel; }
			else { throw std::invalid_argument("size 、または channel の要素のいずれかが負です。"); }
		}
	public: // construct
		BitmapBase() : _data(), _size(RectangleSize::Empty()), _ch() {}
		BitmapBase(const RectangleSize& size, const int& channel) : _data(SolveCount(size, channel)), _size(size), _ch(channel) {}
		BitmapBase(const int& width, const int& height, const int& channel) : BitmapBase(RectangleSize(width, height), channel) {}
	public: // copy/move/destruct
		virtual ~BitmapBase() = default;
	public: // member
		RectangleSize Size() const { return _size; }
		int Channels() const { return _ch; }
		ConstRefType Index(const DisplayPoint& position) const { return ConstRefType(_data.data() + SolveIndex(position), _ch); }
		ConstRefType operator[](const DisplayPoint& index) const { return Index(index); }
		ConstRefType Index(const int& x, const int& y) const { return Index(DisplayPoint(x, y)); }
		RefType Index(const DisplayPoint& position) { return RefType(_data.data() + SolveIndex(position), _ch); }
		RefType operator[](const DisplayPoint& index) { return Index(index); }
		RefType Index(const int& x, const int& y) { return Index(DisplayPoint(x, y)); }
		IteratorType begin() { return IteratorType(*this, 0); }
		IteratorType end() { return IteratorType(*this, SolveCount(_size)); }
		ConstIteratorType cbegin() const { return ConstIteratorType(*this, 0); }
		ConstIteratorType cend() const { return ConstIteratorType(*this, SolveCount(_size)); }
		ReverceIteratorType rbegin() { return ReverceIteratorType(*this, SolveCount(_size)); }
		ReverceIteratorType rend() { return ReverceIteratorType(*this, 0); }
		ConstReverceIteratorType crbegin() const { return ConstReverceIteratorType(*this, SolveCount(_size)); }
		ConstReverceIteratorType crend() const { return ConstReverceIteratorType(*this, 0); }
		VerticalIteratorType vbegin() { return VerticalIteratorType(*this, 0); }
		VerticalIteratorType vend() { return VerticalIteratorType(*this, SolveCount(_size)); }
		VerticalConstIteratorType vcbegin() const { return VerticalConstIteratorType(*this, 0); }
		VerticalConstIteratorType vcend() const { return VerticalConstIteratorType(*this, SolveCount(_size)); }
		VerticalReverceIteratorType vrbegin() { return VerticalReverceIteratorType(*this, SolveCount(_size)); }
		VerticalReverceIteratorType vrend() { return VerticalReverceIteratorType(*this, 0); }
		VerticalConstReverceIteratorType vcrbegin() const { return VerticalConstReverceIteratorType(*this, SolveCount(_size)); }
		VerticalConstReverceIteratorType vcrend() const { return VerticalConstReverceIteratorType(*this, 0); }
	};

	typedef BitmapBase<uint8_t> Bitmap8;
	typedef BitmapBase<uint16_t> Bitmap16;
	typedef BitmapBase<uint32_t> Bitmap32;
	typedef BitmapBase<float> BitmapF32;
	typedef BitmapBase<double> BitmapF64;
}
#endif // __stationaryorbit_graphics_core_bitmap__