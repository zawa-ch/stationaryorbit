#ifndef __stationaryorbit_graphics_core_bitmapbuffer__
#define __stationaryorbit_graphics_core_bitmapbuffer__
#include <cstddef>
#include <vector>
#include "stationaryorbit/exception/soexcept"
#include "stationaryorbit/core/property"
#include "stationaryorbit/core/numeral"
#include "bitmap.hpp"
#include "point.hpp"
#include "channelvalue.hpp"
#include "pixelreference.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{

	template<class T> class BitmapBufferIterator;
	template<class T> class BitmapBufferConstIterator;
	template<class T> class BitmapBufferReverceIterator;
	template<class T> class BitmapBufferConstReverceIterator;

	///	画像情報を保持するための記憶領域を提供し、アクセスを行うためのメソッドを実装します。
	///	@param	T
	///	値の表現に使用する型。
	template<class T>
    class BitmapBufferBase
		: virtual public BitmapBase
    {
    public: // type
		typedef ChannelValue<T> ValueType;
		typedef BitmapBufferIterator<T> Iterator;
		typedef BitmapBufferConstIterator<T> ConstIterator;
		typedef BitmapBufferReverceIterator<T> ReverceIterator;
		typedef BitmapBufferConstReverceIterator<T> ConstReverceIterator;
    public: // interface
		///	指定された1ピクセル・1チャネルにおける値を取得します。
		virtual ReadOnlyProperty<BitmapBufferBase<T>, ValueType> Index(const size_t& x, const size_t& y, const size_t& ch) const = 0;
		///	指定された1ピクセル・1チャネルにおける値を取得します。
		virtual ReadOnlyProperty<BitmapBufferBase<T>, ValueType> Index(const Point& pos, const size_t& ch) const = 0;
		///	指定された1ピクセル・1チャネルにおける値を取得します。
		virtual Property<BitmapBufferBase<T>, ValueType> Index(const size_t& x, const size_t& y, const size_t& ch) = 0;
		///	指定された1ピクセル・1チャネルにおける値を取得します。
		virtual Property<BitmapBufferBase<T>, ValueType> Index(const Point& pos, const size_t& ch) = 0;
		///	このバッファのチャネル数を取得します。
		virtual size_t GetChannelCount() const noexcept = 0;
		virtual ~BitmapBufferBase() = default;
	public: // iterator
		///	このオブジェクトの最初の要素を示すイテレータを取得します。
		virtual Iterator begin() noexcept { return Iterator(*this, 0); }
		///	このオブジェクトの最後の要素を示すイテレータを取得します。
		virtual Iterator end() noexcept { return Iterator(*this, GetWidth() * GetHeight() * GetChannelCount()); }
		///	このオブジェクトの最初の要素を示す変更できないイテレータを取得します。
		virtual ConstIterator cbegin() const noexcept { return ConstIterator(*this, 0); }
		///	このオブジェクトの最後の要素を示す変更できないイテレータを取得します。
		virtual ConstIterator cend() const noexcept { return ConstIterator(*this, GetWidth() * GetHeight() * GetChannelCount()); }
		///	このオブジェクトの最初の要素を示す逆イテレータを取得します。
		virtual ReverceIterator rbegin() noexcept { return ReverceIterator(*this, GetWidth() * GetHeight() * GetChannelCount()); }
		///	このオブジェクトの最後の要素を示す逆イテレータを取得します。
		virtual ReverceIterator rend() noexcept { return ReverceIterator(*this, 0); }
		///	このオブジェクトの最初の要素を示す変更できない逆イテレータを取得します。
		virtual ConstReverceIterator crbegin() const noexcept { return ConstReverceIterator(*this, GetWidth() * GetHeight() * GetChannelCount()); }
		///	このオブジェクトの最後の要素を示す変更できない逆イテレータを取得します。
		virtual ConstReverceIterator crend() const noexcept { return ConstReverceIterator(*this, 0); }
    };
	///	@a BitmapBufferBase の内容を反復して処理するための参照を表します。
	template<class T>
	class BitmapBufferIterator final
	{
	public:
		typedef BitmapBufferBase<T> ContainerType;
		typedef ChannelValue<T> ValueType;
	private: // contains
		ContainerType& _container;
		size_t _pos;
	public: // constructor
		BitmapBufferIterator(ContainerType& container, const size_t position) noexcept : _container(container), _pos(position) {}
	public: // member
		Property<BitmapBufferBase<T>, ValueType> Current() { return _container.Index((_pos / _container.GetChannelCount()) % _container.GetWidth(), _pos / (_container.GetWidth() * _container.GetChannelCount()), _pos % _container.GetChannelCount()); }
		bool Equals(const BitmapBufferIterator& other) const noexcept { return _pos == other._pos; }
	public: // implement LegacyIterator
		Property<BitmapBufferBase<T>, ValueType> operator*() { return Current(); }
		BitmapBufferIterator& operator++() noexcept { _pos++; return *this; }
	public: // implement LegacyInputIterator
		bool operator==(const BitmapBufferIterator& other) const noexcept { return Equals(other); }
		bool operator!=(const BitmapBufferIterator& other) const noexcept { return !Equals(other); }
		Property<BitmapBufferBase<T>, ValueType> operator->() { return Current(); }
	public: // implement LegacyBidirectionalIterator
		BitmapBufferIterator& operator--() noexcept { _pos--; return *this; }
	};
	///	@a BitmapBufferBase の内容を反復して処理するための参照を表します。
	template<class T>
	class BitmapBufferConstIterator final
	{
	public:
		typedef BitmapBufferBase<T> ContainerType;
		typedef ChannelValue<T> ValueType;
	private: // contains
		const ContainerType& _container;
		size_t _pos;
	public: // constructor
		BitmapBufferConstIterator(const ContainerType& container, const size_t position) noexcept : _container(container), _pos(position) {}
	public: // member
		ReadOnlyProperty<BitmapBufferBase<T>, ValueType> Current() const { return _container.Index((_pos / _container.GetChannelCount()) % _container.GetWidth(), _pos / (_container.GetWidth() * _container.GetChannelCount()), _pos % _container.GetChannelCount()); }
		bool Equals(const BitmapBufferConstIterator& other) const noexcept { return _pos == other._pos; }
	public: // implement LegacyIterator
		ReadOnlyProperty<BitmapBufferBase<T>, ValueType> operator*() const { return Current(); }
		BitmapBufferConstIterator& operator++() noexcept { _pos++; return *this; }
	public: // implement LegacyInputIterator
		bool operator==(const BitmapBufferConstIterator& other) const noexcept { return Equals(other); }
		bool operator!=(const BitmapBufferConstIterator& other) const noexcept { return !Equals(other); }
		ReadOnlyProperty<BitmapBufferBase<T>, ValueType> operator->() const { return Current(); }
	public: // implement LegacyBidirectionalIterator
		BitmapBufferConstIterator& operator--() noexcept { _pos--; return *this; }
	};
	///	@a BitmapBufferBase の内容を反復して処理するための参照を表します。
	template<class T>
	class BitmapBufferReverceIterator final
	{
	public:
		typedef BitmapBufferBase<T> ContainerType;
		typedef ChannelValue<T> ValueType;
	private: // contains
		ContainerType& _container;
		size_t _pos;
	public: // constructor
		BitmapBufferReverceIterator(ContainerType& container, const size_t position) noexcept : _container(container), _pos(position) {}
	public: // member
		Property<BitmapBufferBase<T>, ValueType> Current() { return _container.Index(((_pos - 1) / _container.GetChannelCount()) % _container.GetWidth(), (_pos - 1) / (_container.GetWidth() * _container.GetChannelCount()), (_pos - 1) % _container.GetChannelCount()); }
		bool Equals(const BitmapBufferReverceIterator& other) const noexcept { return _pos == other._pos; }
	public: // implement LegacyIterator
		Property<BitmapBufferBase<T>, ValueType> operator*() { return Current(); }
		BitmapBufferReverceIterator& operator++() noexcept { _pos--; return *this; }
	public: // implement LegacyInputIterator
		bool operator==(const BitmapBufferReverceIterator& other) const noexcept { return Equals(other); }
		bool operator!=(const BitmapBufferReverceIterator& other) const noexcept { return !Equals(other); }
		Property<BitmapBufferBase<T>, ValueType> operator->() { return Current(); }
	public: // implement LegacyBidirectionalIterator
		BitmapBufferReverceIterator& operator--() noexcept { _pos++; return *this; }
	};
	///	@a BitmapBufferBase の内容を反復して処理するための参照を表します。
	template<class T>
	class BitmapBufferConstReverceIterator final
	{
	public:
		typedef BitmapBufferBase<T> ContainerType;
		typedef ChannelValue<T> ValueType;
	private: // contains
		const ContainerType& _container;
		size_t _pos;
	public: // constructor
		BitmapBufferConstReverceIterator(const ContainerType& container, const size_t position) noexcept : _container(container), _pos(position) {}
	public: // member
		ReadOnlyProperty<BitmapBufferBase<T>, ValueType> Current() const { return _container.Index(((_pos - 1) / _container.GetChannelCount()) % _container.GetWidth(), (_pos - 1) / (_container.GetWidth() * _container.GetChannelCount()), (_pos - 1) % _container.GetChannelCount()); }
		bool Equals(const BitmapBufferConstReverceIterator& other) const noexcept { return _pos == other._pos; }
	public: // implement LegacyIterator
		ReadOnlyProperty<BitmapBufferBase<T>, ValueType> operator*() const { return Current(); }
		BitmapBufferConstReverceIterator& operator++() noexcept { _pos--; return *this; }
	public: // implement LegacyInputIterator
		bool operator==(const BitmapBufferConstReverceIterator& other) const noexcept { return Equals(other); }
		bool operator!=(const BitmapBufferConstReverceIterator& other) const noexcept { return !Equals(other); }
		ReadOnlyProperty<BitmapBufferBase<T>, ValueType> operator->() const { return Current(); }
	public: // implement LegacyBidirectionalIterator
		BitmapBufferConstReverceIterator& operator--() noexcept { _pos++; return *this; }
	};
	///	画像情報を保持するためのメモリ空間を提供します。
	///	@param	T
	///	値の表現に使用する型。
	template<class T = float>
	class BitmapBuffer
		: virtual public BitmapBufferBase<T>
	{
    public: // type
		typedef ChannelValue<T> ValueType;
		typedef size_t SizeType;
		typedef BitmapBufferIterator<T> Iterator;
		typedef BitmapBufferConstIterator<T> ConstIterator;
		typedef BitmapBufferReverceIterator<T> ReverceIterator;
		typedef BitmapBufferConstReverceIterator<T> ConstReverceIterator;
	private: // contains
		SizeType _x;
		SizeType _y;
		BitmapColorSpace _space;
		std::vector<ValueType> _data;
	public: // constructor
		///	既定の @a BitmapBuffer を初期化します。
		BitmapBuffer() = default;
		///	指定されたサイズのキャンバスを確保し、このオブジェクトを初期化します。
		///	@param	x
		///	Bitmapの幅。
		///	@param	y
		///	Bitmapの高さ。
		///	@param	ch
		///	Bitmapのチャネル数。
		BitmapBuffer(const SizeType& x, const SizeType& y, const BitmapColorSpace& space) : _x(x), _y(y), _space(space), _data(CalcLength(x, y, space)) {}
		///	指定されたサイズのキャンバスを確保し、このオブジェクトを初期化します。
		///	@param	size
		///	Bitmapの大きさ。
		///	@param	ch
		///	Bitmapのチャネル数。
		BitmapBuffer(const Point& size, const BitmapColorSpace& space) : BitmapBuffer(size.getX(), size.getY(), space)
		{
			if ((size.getX() < 0)||(size.getY() < 0)) { throw std::invalid_argument("負の値を持つsizeを引数に取りました。"); }
		}
		///	指定されたキャンバスの内容を複製します。
		///	@param	value
		///	複製元の @a BitmapBufferBase 。
		explicit BitmapBuffer(const BitmapBufferBase<T>& value) : BitmapBuffer(value.GetWidth(), value.GetHeight(), value.GetColorSpace())
		{
			auto srcpx = value.cbegin();
			auto srcend = value.cend();
			auto destpx = this->begin();
			auto destend = this->end();
			while ((destpx != destend)&&(srcpx != srcend))
			{
				*destpx = *srcpx;
				++destpx;
				++srcpx;
			}
		}
		virtual ~BitmapBuffer() = default;
	public: // implement BitmapBase
		///	このバッファの幅を取得します。
		SizeType GetWidth() const noexcept { return _x; }
		///	このバッファの高さを取得します。
		SizeType GetHeight() const noexcept { return _y; }
		///	バッファに使用されている色空間を取得します。
		BitmapColorSpace GetColorSpace() const noexcept { return _space; }
	public: // implement BitmapBufferBase
		///	指定された1ピクセル・1チャネルにおける値を取得します。
		ReadOnlyProperty<BitmapBufferBase<T>, ValueType> Index(const SizeType& x, const SizeType& y, const SizeType& ch) const { return ReadOnlyProperty<BitmapBufferBase<T>, ValueType>(*this, std::bind(getIndex, std::placeholders::_1, x, y, ch)); }
		///	指定された1ピクセル・1チャネルにおける値を取得します。
		ReadOnlyProperty<BitmapBufferBase<T>, ValueType> Index(const Point& pos, const SizeType& ch) const { return Index(pos.getX(), pos.getY(), ch); }
		///	指定された1ピクセル・1チャネルにおける値を取得します。
		Property<BitmapBufferBase<T>, ValueType> Index(const SizeType& x, const SizeType& y, const SizeType& ch) { return Property<BitmapBufferBase<T>, ValueType>(*this, std::bind(getIndex, std::placeholders::_1, x, y, ch), std::bind(setIndex, std::placeholders::_1, x, y, ch, std::placeholders::_2)); }
		///	指定された1ピクセル・1チャネルにおける値を取得します。
		Property<BitmapBufferBase<T>, ValueType> Index(const Point& pos, const SizeType& ch) { return Index(pos.getX(), pos.getY(), ch); }
		///	このバッファのチャネル数を取得します。
		SizeType GetChannelCount() const noexcept { return CalcChCount(_space); }
	public: // convert
		///	このオブジェクトを指定された型の @a BitmapBuffer に変換します。
		template<class destT>
		BitmapBuffer<destT> ConvertTo() const
		{
			auto result = BitmapBuffer<destT>(_x, _y, _space);
			auto srcpx = this->cbegin();
			auto srcend = this->cend();
			auto destpx = result.begin();
			auto destend = result.end();
			while ((destpx != destend)&&(srcpx != srcend))
			{
				*destpx = ChannelValue<destT>((*srcpx).get());
				++destpx;
				++srcpx;
			}
			return result;
		}
	public: // static
		///	指定されたオブジェクトと幅・高さ・色空間が同じ空のオブジェクトを取得します。
		static BitmapBuffer<T> Resemble(const BitmapBufferBase<T>& from) { return BitmapBuffer<T>(from.GetWidth(), from.GetHeight(), from.GetColorSpace()); }
		///	異なる型の @a BitmapBufferBase をこの型に変換します。
		template<class FromT>
		static BitmapBuffer<T> ConvertFrom(const BitmapBufferBase<FromT>& from)
		{
			auto result = Resemble(from);
			auto srcpx = from.cbegin();
			auto srcend = from.cend();
			auto destpx = result.begin();
			auto destend = result.end();
			while ((destpx != destend)&&(srcpx != srcend))
			{
				*destpx = ChannelValue<T>(*srcpx);
				++destpx;
				++srcpx;
			}
			return result;
		}
	private: // internal
		///	各色空間が使用するチャネル数を取得します。
		constexpr static size_t CalcChCount(const BitmapColorSpace& space)
		{
			switch(space)
			{
			case BitmapColorSpace::GrayScale: return 1;
			case BitmapColorSpace::ARGB: return 4;
			case BitmapColorSpace::CMYK: return 4;
			case BitmapColorSpace::AXYZ: return 4;
			}
		}
		///	オブジェクトが使用するオブジェクト数を算出します。
		///	@param	x
		///	Bitmapの幅。
		///	@param	y
		///	Bitmapの高さ。
		///	@param	space
		///	Bitmapの色空間。
		///	@return
		///	算出されたオブジェクト数が返ります。
		constexpr static size_t CalcLength(const size_t& x, const size_t& y, const BitmapColorSpace& space) noexcept { return x * y * CalcChCount(space); }
		///	指定された1ピクセル・1チャネルにおける値を取得します。
		static ValueType getIndex(const BitmapBufferBase<T>& inst, const SizeType& x, const SizeType& y, const SizeType& ch)
		{
			auto cinst = dynamic_cast<const BitmapBuffer<T>&>(inst);
			if (cinst._x <= x) throw new std::out_of_range("x が画像エリアの範囲外です。");
			if (cinst._y <= y) throw new std::out_of_range("y が画像エリアの範囲外です。");
			if (cinst.GetChannelCount() <= ch) throw new std::out_of_range("ch が画像エリアの範囲外です。");
			return cinst._data[(y*cinst._x + x)*cinst.GetChannelCount() + ch];
		}
		///	指定された1ピクセル・1チャネルにおける値を設定します。
		static void setIndex(BitmapBufferBase<T>& inst, const SizeType& x, const SizeType& y, const SizeType& ch, const ValueType& value)
		{
			auto cinst = dynamic_cast<BitmapBuffer<T>&>(inst);
			if (cinst._x <= x) throw new std::out_of_range("x が画像エリアの範囲外です。");
			if (cinst._y <= y) throw new std::out_of_range("y が画像エリアの範囲外です。");
			if (cinst.GetChannelCount() <= ch) throw new std::out_of_range("ch が画像エリアの範囲外です。");
			cinst._data[(y*cinst._x + x)*cinst.GetChannelCount() + ch] = value;
		}
	};

}
#endif // __stationaryorbit_graphics_core_bitmapbuffer__