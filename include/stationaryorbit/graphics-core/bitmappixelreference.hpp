#ifndef __stationaryorbit_graphics_core_bitmappixelreference__
#define __stationaryorbit_graphics_core_bitmappixelreference__
#include "stationaryorbit/exception/soexcept"
#include "point.hpp"
#include "rgbcolor.hpp"
#include "pixelreference.hpp"
#include "bitmapbuffer.hpp"
#include "imageinfomation.hpp"
#include "graphicscore.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{

	///	@a BitmapBuffer 上のピクセルへの参照を表します。
	template<class T>
	class BitmapPixelReference final
		: virtual public PixelReference
	{
	public: // type

		typedef IBitmapBuffer<T> IBufferType;

	private: // contains

		///	参照先の @a BitmapBuffer 。
		IBufferType& _buf;
		///	参照先のx座標。
		size_t _x;
		///	参照先のy座標。
		size_t _y;

	public: // constructor

		///	@a Bitmap のピクセルへの参照を作成します。
		///	@param	buffer
		///	参照先の @a BitmapBuffer 。
		///	@param	x
		///	参照先のx座標。
		///	@param	y
		///	参照先のy座標。
		BitmapPixelReference(IBufferType& buffer, const size_t& x, const size_t& y) : _buf(buffer), _x(x), _y(y) {}

		///	@a Bitmap のピクセルへの参照を作成します。
		///	@param	buffer
		///	参照先の @a BitmapBuffer 。
		///	@param	position
		///	参照先の座標。
		BitmapPixelReference(IBufferType& buffer, const Point& position) : BitmapPixelReference(buffer, position.getX(), position.getY())
		{
			if ((position.getX() < 0)||(position.getY() < 0)) { throw std::invalid_argument("負の値を持つ position を引数に取りました。"); }
		}

	public: // member

		///	この参照が指し示す @a BitmapBuffer を取得します。
		const IBufferType& Buffer() const noexcept { return _buf; }

		///	この参照が指し示す @a BitmapBuffer を取得します。
		IBufferType& Buffer() noexcept { return _buf; }

		///	この参照が指し示す座標を @a Point で取得します。
		Point Position() const noexcept { return Point(_x, _y); }

		///	この参照に指定されたオフセットを加えた参照を取得します。
		///	@param	[in]offset
		///	座標のオフセット。
		///	@return
		///	オフセットを加えた参照が返ります。
		BitmapPixelReference Offset(const Point& offset) { return BitmapPixelReference<T>(_buf, Position() + offset); }

		///	この参照に指定されたオフセットを加えた参照を取得します。
		///	@param	[in]offset
		///	座標のオフセット。
		///	@return
		///	オフセットを加えた参照が返ります。
		const BitmapPixelReference Offset(const Point& offset) const { return BitmapPixelReference<T>(_buf, Position() + offset); }

	public: // implement PixelReference

		///	参照先の値を @a RGBColor で取得します。
		RGBColor GetRGBValue() const
		{
			if (!HasValue()) { throw std::out_of_range("参照先が無効です。"); }
			switch (_buf.getColorSpace())
			{
			case BufferColorSpace::ARGB:
				return RGBColor(
					ChannelValue<float>(refChannel(0)).value,
					ChannelValue<float>(refChannel(1)).value,
					ChannelValue<float>(refChannel(2)).value,
					ChannelValue<float>(refChannel(3)).value);
			case BufferColorSpace::GrayScale:
			case BufferColorSpace::CMYK:
			case BufferColorSpace::AXYZ:
			default: throw InvalidOperationException("バッファに指定されている色空間が無効です。");
			}
		}

		///	参照先に @a RGBColor の値を設定します。
		void SetValue(const RGBColor& value)
		{
			if (!HasValue()) { throw std::out_of_range("参照先が無効です。"); }
			switch (_buf.getColorSpace())
			{
			case BufferColorSpace::ARGB:
				refChannel(0) = ChannelValue<T>(value.getR());
				refChannel(1) = ChannelValue<T>(value.getG());
				refChannel(2) = ChannelValue<T>(value.getB());
				refChannel(3) = ChannelValue<T>(value.getAlpha());
				break;
			case BufferColorSpace::GrayScale:
			case BufferColorSpace::CMYK:
			case BufferColorSpace::AXYZ:
			default: throw InvalidOperationException("バッファに指定されている色空間が無効です。");
			}
		}

		///	参照先の値に @a BitmapPixelGetter の参照先の値を設定します。
		void SetValue(const PixelReference& value)
		{
			if (!HasValue()) { throw std::out_of_range("参照先が無効です。"); }
			switch(_buf.getColorSpace())
			{
			case BufferColorSpace::ARGB:
				SetValue(value.GetRGBValue());
				break;
			case BufferColorSpace::GrayScale:
			case BufferColorSpace::CMYK:
			case BufferColorSpace::AXYZ:
			default: throw InvalidOperationException("バッファに指定されている色空間が無効です。");
			}
		}

		///	このオブジェクトの参照先が存在するかを取得します。
		bool HasValue() const noexcept
		{
			if ((_buf.getHorizonalSize() > _x)&&(_buf.getVerticalSize() > _y)) { return true; }
			else { return false; }
		}

		///	この参照にオフセットを加えた先に、参照先が存在するかを取得します。
		bool HasOffset(const Point& offset) const noexcept { return Offset(offset).HasValue(); }

		///	この参照にオフセットを加えた先の値を @a RGBColor で取得します。
		RGBColor GetOffsetRGBValue(const Point& offset) const { return Offset(offset).GetRGBValue(); }

		///	この参照にオフセットを加えた先に @a RGBColor の値を設定します。
		void SetOffsetRGBValue(const Point& offset, const RGBColor& value) { return Offset(offset).SetValue(value); }

		///	この参照にオフセットを加えた先の値に @a BitmapPixelGetter の参照先の値を設定します。
		void SetOffsetRGBValue(const Point& offset, const PixelReference& value) { return Offset(offset).SetValue(value); }

	private: // internal

		const ChannelValue<T>& refChannel(const size_t& channel) const { return _buf.Index(_x, _y, channel); }

		ChannelValue<T>& refChannel(const size_t& channel) { return _buf.Index(_x, _y, channel); }

	};

}
#endif // __stationaryorbit_graphics_core_bitmappixelreference__