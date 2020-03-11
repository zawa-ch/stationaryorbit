#ifndef __stationaryorbit_graphics_core_bufferbindbitmap__
#define __stationaryorbit_graphics_core_bufferbindbitmap__
#include "bitmap.hpp"
#include "bitmapbuffer.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{

	template<class T>
	class BufferBindBitmapBase
		: virtual public Bitmap
		, virtual public BitmapBufferBase<T>
	{
	public: // types
		typedef BitmapBufferBase<T> BufferType;
		typedef ChannelValue<T> ChannelValueType;
	public: // member
		///	オブジェクトに紐付けられているバッファを取得します。
		virtual BufferType& Buffer() noexcept = 0;
		///	オブジェクトに紐付けられているバッファを取得します。
		virtual const BufferType& Buffer() const noexcept = 0;
	public: // implement BitmapBase
		///	このバッファの幅を取得します。
		virtual size_t GetWidth() const { return Buffer().GetWidth(); }
		///	このバッファの高さを取得します。
		virtual size_t GetHeight() const { return Buffer().GetHeight(); }
		///	バッファに使用されている色空間を取得します。
		virtual BitmapColorSpace GetColorSpace() const { return Buffer().GetColorSpace(); }
	public: // implement BitmapBufferBase
		///	指定された1ピクセル・1チャネルにおける値を取得します。
		virtual ReadOnlyProperty<BitmapBufferBase<T>, ChannelValueType> Index(const size_t& x, const size_t& y, const size_t& ch) const { return Buffer().Index(x, y, ch); }
		///	指定された1ピクセル・1チャネルにおける値を取得します。
		virtual ReadOnlyProperty<BitmapBufferBase<T>, ChannelValueType> Index(const Point& position, const size_t& ch) const { return Buffer().Index(position, ch); }
		///	指定された1ピクセル・1チャネルにおける値を取得します。
		virtual Property<BitmapBufferBase<T>, ChannelValueType> Index(const size_t& x, const size_t& y, const size_t& ch) { return Buffer().Index(x, y, ch); }
		///	指定された1ピクセル・1チャネルにおける値を取得します。
		virtual Property<BitmapBufferBase<T>, ChannelValueType> Index(const Point& position, const size_t& ch) { return Buffer().Index(position, ch); }
		///	このバッファのチャネル数を取得します。
		virtual size_t GetChannelCount() const noexcept { return Buffer().GetChannelCount(); }
	public: // implement Bitmap
		///	指定されたピクセルの値をRGBで取得します。
		virtual RGBColor GetRGB(const size_t& x, const size_t& y) const
		{
			switch (GetColorSpace())
			{
			case BitmapColorSpace::ARGB:
				return RGBColor(
					ChannelValue<float>(Index(x, y, 0).get()).value,
					ChannelValue<float>(Index(x, y, 1).get()).value,
					ChannelValue<float>(Index(x, y, 2).get()).value,
					ChannelValue<float>(Index(x, y, 3).get()).value);
			case BitmapColorSpace::GrayScale:
			case BitmapColorSpace::CMYK:
			case BitmapColorSpace::AXYZ:
			default: throw InvalidOperationException("バッファに指定されている色空間が無効です。");
			}
		}
		///	指定されたピクセルの値をRGBで設定します。
		virtual void SetRGB(const size_t& x, const size_t& y, const RGBColor& value)
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
		virtual const ConstPixelReference Index(const size_t& x, const size_t& y) const { return ConstPixelReference(*this, x, y); }
		///	指定されたピクセルの参照を取得します。
		virtual const ConstPixelReference Index(const Point& position) const { return ConstPixelReference(*this, position); }
		///	指定されたピクセルの参照を取得します。
		virtual PixelReference Index(const size_t& x, const size_t& y) { return PixelReference(*this, x, y); }
		///	指定されたピクセルの参照を取得します。
		virtual PixelReference Index(const Point& position) { return PixelReference(*this, position); }
	public: // copy/move/destruct
		virtual ~BufferBindBitmapBase() = default;
	};

	template<class T>
	class BufferBindBitmap
		: virtual public BufferBindBitmapBase<T>
	{
	public: // types
		typedef BitmapBufferBase<T> BufferType;
		typedef ChannelValue<T> ChannelValueType;
	private: // contains
		BufferType& _buffer;
	public: // constructor
		BufferBindBitmap(BufferType& buffer) noexcept : _buffer(buffer) {}
		explicit BufferBindBitmap(BufferBindBitmapBase<T>& bitmap) noexcept : _buffer(bitmap.Buffer()) {}
		virtual ~BufferBindBitmap() = default;
	public: // member
		///	オブジェクトに紐付けられているバッファを取得します。
		BufferType& Buffer() noexcept { return _buffer; }
		///	オブジェクトに紐付けられているバッファを取得します。
		const BufferType& Buffer() const noexcept { return _buffer; }
	};

}
#endif // __stationaryorbit_graphics_core_bufferbindbitmap__