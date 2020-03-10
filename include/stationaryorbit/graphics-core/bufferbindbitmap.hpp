#ifndef __stationaryorbit_graphics_core_bufferbindbitmap__
#define __stationaryorbit_graphics_core_bufferbindbitmap__
#include "bitmap.hpp"
#include "bitmapbuffer.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{

	template<class T> class BufferBindBitmap;
	template<class T> class BufferBindBitmapIterator;
	template<class T> class BufferBindBitmapConstIterator;
	template<class T> class BufferBindBitmapReverceIterator;
	template<class T> class BufferBindBitmapReverceConstIterator;

	template<class T>
	class BufferBindBitmap
		: virtual public Bitmap
	{
	public: // types
		typedef BitmapBufferBase<T> BufferType;
		typedef BitmapPixelReference<T> PixelRefType;
		typedef BufferBindBitmapIterator<T> Iterator;
		typedef BufferBindBitmapConstIterator<T> ConstIterator;
		typedef BufferBindBitmapReverceIterator<T> ReverceIterator;
		typedef BufferBindBitmapReverceConstIterator<T> ReverceConstIterator;
	private: // contains
		BufferType& _buffer;
	public: // constructor
		BufferBindBitmap(BufferType& buffer) : _buffer(buffer) {}
		virtual ~BufferBindBitmap() = default;
	public: // member
		///	オブジェクトに紐付けられているバッファを取得します。
		BufferType& Buffer() noexcept { return _buffer; }
		///	オブジェクトに紐付けられているバッファを取得します。
		const BufferType& Buffer() const noexcept { return _buffer; }
		///	指定されたピクセルの参照を取得します。
		const PixelRefType Index(const size_t& x, const size_t& y) const { return PixelRefType(_buffer, x, y); }
		///	指定されたピクセルの参照を取得します。
		const PixelRefType Index(const Point& position) const { return PixelRefType(_buffer, position); }
		///	指定されたピクセルの参照を取得します。
		PixelRefType Index(const size_t& x, const size_t& y) { return PixelRefType(_buffer, x, y); }
		///	指定されたピクセルの参照を取得します。
		PixelRefType Index(const Point& position) { return PixelRefType(_buffer, position); }
	public: // implement BitmapBase
		///	このバッファの幅を取得します。
		size_t GetHorizonalSize() const { return _buffer.GetHorizonalSize(); }
		///	このバッファの高さを取得します。
		size_t GetVerticalSize() const { return _buffer.GetVerticalSize(); }
		///	バッファに使用されている色空間を取得します。
		BitmapColorSpace GetColorSpace() const { return _buffer.GetColorSpace(); }
	public: // implement Bitmap
		///	指定されたピクセルの値をRGBで取得します。
		RGBColor GetRGB(const size_t& x, const size_t& y) const { return Index(x, y).GetRGBValue(); }
		///	指定されたピクセルの値をRGBで設定します。
		void SetRGB(const size_t& x, const size_t& y, const RGBColor& value) { Index(x, y).SetValue(value); }
	public: // iterator
		Iterator begin() noexcept { return Iterator(*this, 0); }
		Iterator end() noexcept { return Iterator(*this, GetHorizonalSize() * GetVerticalSize()); }
		ConstIterator cbegin() const noexcept { return ConstIterator(*this, 0); }
		ConstIterator cend() const noexcept { return ConstIterator(*this, GetHorizonalSize() * GetVerticalSize()); }
		ReverceIterator rbegin() noexcept { return ReverceIterator(*this, GetHorizonalSize() * GetVerticalSize()); }
		ReverceIterator rend() noexcept { return ReverceIterator(*this, 0); }
		ReverceConstIterator crbegin() const noexcept { return ReverceConstIterator(*this, GetHorizonalSize() * GetVerticalSize()); }
		ReverceConstIterator crend() const noexcept { return ReverceConstIterator(*this, 0); }
	};

	template<class T>
	class BufferBindBitmapIterator
	{
	public:
		typedef BufferBindBitmap<T> ContainerType;
		typedef BitmapPixelReference<T> ValueType;
	private: // contains
		ContainerType& _container;
		size_t _pos;
	public: // constructor
		BufferBindBitmapIterator(ContainerType& container, const size_t position) noexcept : _container(container), _pos(position) {}
	public: // member
		ValueType Current() { return _container.Index(_pos % _container.GetHorizonalSize(), _pos / _container.GetHorizonalSize()); }
		bool Equals(const BufferBindBitmapIterator& other) const noexcept { return _pos == other._pos; }
	public: // implement LegacyIterator
		ValueType operator*() { return Current(); }
		BufferBindBitmapIterator& operator++() noexcept { _pos++; return *this; }
	public: // implement LegacyInputIterator
		bool operator==(const BufferBindBitmapIterator& other) const noexcept { return Equals(other); }
		bool operator!=(const BufferBindBitmapIterator& other) const noexcept { return !Equals(other); }
		ValueType operator->() { return Current(); }
	public: // implement LegacyBidirectionalIterator
		BufferBindBitmapIterator& operator--() noexcept { _pos--; return *this; }
	};

	template<class T>
	class BufferBindBitmapConstIterator
	{
	public:
		typedef BufferBindBitmap<T> ContainerType;
		typedef BitmapPixelReference<T> ValueType;
	private: // contains
		const ContainerType& _container;
		size_t _pos;
	public: // constructor
		BufferBindBitmapConstIterator(const ContainerType& container, const size_t position) noexcept : _container(container), _pos(position) {}
	public: // member
		const ValueType Current() const { return _container.Index(_pos % _container.GetHorizonalSize(), _pos / _container.GetHorizonalSize()); }
		bool Equals(const BufferBindBitmapConstIterator& other) const noexcept { return _pos == other._pos; }
	public: // implement LegacyIterator
		const ValueType operator*() const { return Current(); }
		BufferBindBitmapConstIterator& operator++() noexcept { _pos++; return *this; }
	public: // implement LegacyInputIterator
		bool operator==(const BufferBindBitmapConstIterator& other) const noexcept { return Equals(other); }
		bool operator!=(const BufferBindBitmapConstIterator& other) const noexcept { return !Equals(other); }
		const ValueType operator->() const { return Current(); }
	public: // implement LegacyBidirectionalIterator
		BufferBindBitmapConstIterator& operator--() noexcept { _pos--; return *this; }
	};

	template<class T>
	class BufferBindBitmapReverceIterator
	{
	public:
		typedef BufferBindBitmap<T> ContainerType;
		typedef BitmapPixelReference<T> ValueType;
	private: // contains
		ContainerType& _container;
		size_t _pos;
	public: // constructor
		BufferBindBitmapReverceIterator(ContainerType& container, const size_t position) noexcept : _container(container), _pos(position) {}
	public: // member
		ValueType Current() { return _container.Index((_pos - 1) % _container.GetHorizonalSize(), (_pos - 1) / _container.GetHorizonalSize()); }
		bool Equals(const BufferBindBitmapReverceIterator& other) const noexcept { return _pos == other._pos; }
	public: // implement LegacyIterator
		ValueType operator*() { return Current(); }
		BufferBindBitmapReverceIterator& operator++() noexcept { _pos--; return *this; }
	public: // implement LegacyInputIterator
		bool operator==(const BufferBindBitmapReverceIterator& other) const noexcept { return Equals(other); }
		bool operator!=(const BufferBindBitmapReverceIterator& other) const noexcept { return !Equals(other); }
		ValueType operator->() { return Current(); }
	public: // implement LegacyBidirectionalIterator
		BufferBindBitmapReverceIterator& operator--() noexcept { _pos++; return *this; }
	};

	template<class T>
	class BufferBindBitmapReverceConstIterator
	{
	public:
		typedef BufferBindBitmap<T> ContainerType;
		typedef BitmapPixelReference<T> ValueType;
	private: // contains
		const ContainerType& _container;
		size_t _pos;
	public: // constructor
		BufferBindBitmapReverceConstIterator(const ContainerType& container, const size_t position) noexcept : _container(container), _pos(position) {}
	public: // member
		const ValueType Current() const { return _container.Index((_pos - 1) % _container.GetHorizonalSize(), (_pos - 1) / _container.GetHorizonalSize()); }
		bool Equals(const BufferBindBitmapReverceConstIterator& other) const noexcept { return _pos == other._pos; }
	public: // implement LegacyIterator
		const ValueType operator*() const { return Current(); }
		BufferBindBitmapReverceConstIterator& operator++() noexcept { _pos--; return *this; }
	public: // implement LegacyInputIterator
		bool operator==(const BufferBindBitmapReverceConstIterator& other) const noexcept { return Equals(other); }
		bool operator!=(const BufferBindBitmapReverceConstIterator& other) const noexcept { return !Equals(other); }
		const ValueType operator->() const { return Current(); }
	public: // implement LegacyBidirectionalIterator
		BufferBindBitmapReverceConstIterator& operator--() noexcept { _pos++; return *this; }
	};

}
#endif // __stationaryorbit_graphics_core_bufferbindbitmap__