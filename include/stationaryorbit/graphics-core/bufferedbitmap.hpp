#ifndef __stationaryorbit_graphics_core_bufferedbitmap__
#define __stationaryorbit_graphics_core_bufferedbitmap__
#include "bitmapbuffer.hpp"
#include "bufferbindbitmap.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{

	template<class T>
	class BufferedBitmap
		: virtual public Bitmap
	{
	public: // type
		typedef BitmapBuffer<T> BufferType;
		typedef BitmapPixelReference<T> PixelRefType;
		typedef BitmapConstPixelReference<T> CPixelRefType;
		typedef BufferBindBitmapIterator<T> Iterator;
		typedef BufferBindBitmapConstIterator<T> ConstIterator;
		typedef BufferBindBitmapReverceIterator<T> ReverceIterator;
		typedef BufferBindBitmapReverceConstIterator<T> ReverceConstIterator;
	private: // contains
		BufferType _buffer;
	public: // constructor
		BufferedBitmap() = default;
		BufferedBitmap(const BufferType& buffer) : _buffer(buffer) {}
		BufferedBitmap(const BufferBindBitmap<T>& bitmap) : _buffer(bitmap.Buffer()) {}
		virtual ~BufferedBitmap() = default;
	public: // member
		///	オブジェクトに紐付けられているバッファを取得します。
		BufferType& Buffer() noexcept { return _buffer; }
		///	オブジェクトに紐付けられているバッファを取得します。
		const BufferType& Buffer() const noexcept { return _buffer; }
		///	指定されたピクセルの参照を取得します。
		const CPixelRefType Index(const size_t& x, const size_t& y) const { return CPixelRefType(_buffer, x, y); }
		///	指定されたピクセルの参照を取得します。
		const CPixelRefType Index(const Point& position) const { return CPixelRefType(_buffer, position); }
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

}
#endif // __stationaryorbit_graphics_core_bufferedbitmap__