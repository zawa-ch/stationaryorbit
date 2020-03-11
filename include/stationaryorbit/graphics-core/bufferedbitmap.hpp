#ifndef __stationaryorbit_graphics_core_bufferedbitmap__
#define __stationaryorbit_graphics_core_bufferedbitmap__
#include "bitmapbuffer.hpp"
#include "bufferbindbitmap.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{

	template<class T>
	class BufferedBitmap
		: virtual public Bitmap
		, virtual public BitmapBufferBase<T>
	{
	public: // type
		typedef BitmapBuffer<T> BufferType;
		typedef ChannelValue<T> ChannelValueType;
	private: // contains
		BufferType _buffer;
	public: // constructor
		BufferedBitmap() = default;
		BufferedBitmap(const BufferType& buffer) : _buffer(buffer) {}
		explicit BufferedBitmap(const BufferBindBitmap<T>& bitmap) : _buffer(bitmap.Buffer()) {}
		template<class fromT>
		explicit BufferedBitmap(const BufferedBitmap<fromT>& bitmap) : _buffer(bitmap.Buffer()) {}
		template<class fromT>
		explicit BufferedBitmap(const BufferBindBitmap<fromT>& bitmap) : _buffer(bitmap.Buffer()) {}
		virtual ~BufferedBitmap() = default;
	public: // member
		///	オブジェクトに紐付けられているバッファを取得します。
		BufferType& Buffer() noexcept { return _buffer; }
		///	オブジェクトに紐付けられているバッファを取得します。
		const BufferType& Buffer() const noexcept { return _buffer; }
	public: // implement BitmapBase
		///	このバッファの幅を取得します。
		size_t GetHorizonalSize() const { return _buffer.GetHorizonalSize(); }
		///	このバッファの高さを取得します。
		size_t GetVerticalSize() const { return _buffer.GetVerticalSize(); }
		///	バッファに使用されている色空間を取得します。
		BitmapColorSpace GetColorSpace() const { return _buffer.GetColorSpace(); }
	public: // implement BitmapBufferBase
		///	指定されたピクセルの参照を取得します。
		const ChannelValueType& Index(const size_t& x, const size_t& y, const size_t& ch) const { return _buffer.Index(x, y, ch); }
		///	指定されたピクセルの参照を取得します。
		const ChannelValueType& Index(const Point& position, const size_t& ch) const { return _buffer.Index(position, ch); }
		///	指定されたピクセルの参照を取得します。
		ChannelValueType& Index(const size_t& x, const size_t& y, const size_t& ch) { return _buffer.Index(x, y, ch); }
		///	指定されたピクセルの参照を取得します。
		ChannelValueType& Index(const Point& position, const size_t& ch) { return _buffer.Index(position, ch); }
		///	このバッファのチャネル数を取得します。
		size_t GetChannelCount() const noexcept { return _buffer.GetChannelCount(); }
	public: // implement Bitmap
		///	指定されたピクセルの値をRGBで取得します。
		RGBColor GetRGB(const size_t& x, const size_t& y) const
		{
			switch (GetColorSpace())
			{
			case BitmapColorSpace::ARGB:
				return RGBColor(
					ChannelValue<float>(Index(x, y, 0)).value,
					ChannelValue<float>(Index(x, y, 1)).value,
					ChannelValue<float>(Index(x, y, 2)).value,
					ChannelValue<float>(Index(x, y, 3)).value);
			case BitmapColorSpace::GrayScale:
			case BitmapColorSpace::CMYK:
			case BitmapColorSpace::AXYZ:
			default: throw InvalidOperationException("バッファに指定されている色空間が無効です。");
			}
		}
		///	指定されたピクセルの値をRGBで設定します。
		void SetRGB(const size_t& x, const size_t& y, const RGBColor& value)
		{
			switch (GetColorSpace())
			{
			case BitmapColorSpace::ARGB:
				Index(x, y, 0) = ChannelValue<T>(value.getR());
				Index(x, y, 1) = ChannelValue<T>(value.getG());
				Index(x, y, 2) = ChannelValue<T>(value.getB());
				Index(x, y, 3) = ChannelValue<T>(value.getAlpha());
				break;
			case BitmapColorSpace::GrayScale:
			case BitmapColorSpace::CMYK:
			case BitmapColorSpace::AXYZ:
			default: throw InvalidOperationException("バッファに指定されている色空間が無効です。");
			}
		}
		///	指定されたピクセルの参照を取得します。
		const ConstPixelReference Index(const size_t& x, const size_t& y) const { return ConstPixelReference(*this, x, y); }
		///	指定されたピクセルの参照を取得します。
		const ConstPixelReference Index(const Point& position) const { return ConstPixelReference(*this, position); }
		///	指定されたピクセルの参照を取得します。
		PixelReference Index(const size_t& x, const size_t& y) { return PixelReference(*this, x, y); }
		///	指定されたピクセルの参照を取得します。
		PixelReference Index(const Point& position) { return PixelReference(*this, position); }
	};

}
#endif // __stationaryorbit_graphics_core_bufferedbitmap__