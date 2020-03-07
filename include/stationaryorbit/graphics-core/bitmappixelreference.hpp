#ifndef __StationaryOrbit_Graphics_BitmapPixelReference__
#define __StationaryOrbit_Graphics_BitmapPixelReference__
#include "stationaryorbit/exception/soexcept"
#include "point.hpp"
#include "rgbcolor.hpp"
#include "bitmapbuffer.hpp"
#include "imageinfomation.hpp"
#include "graphicscore.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{

	///	Bitmapのピクセルへの参照を表します。
	///	@note
	///	このオブジェクトは指定されたオブジェクトへの参照を保持します。
	///	このとき、参照先にオブジェクトが存在するかどうかは確認されません。
	template<class T>
	class BitmapPixelReference final
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
		BitmapPixelReference(IBufferType& buffer, const size_t& x, const size_t& y) : _buf(buffer), _x(x), _y(y)
		{
			if (!HasValue(buffer, x, y)) { throw std::out_of_range("指定された参照はビットマップ領域の範囲外です。"); }
		}

		///	@a Bitmap のピクセルへの参照を作成します。
		///	@param	buffer
		///	参照先の @a BitmapBuffer 。
		///	@param	position
		///	参照先の座標。
		BitmapPixelReference(IBufferType& buffer, const Point& position) : BitmapPixelReference(buffer, position.getX(), position.getY())
		{
			if ((position.getX() < 0)||(position.getY() < 0)) { throw std::invalid_argument("負の値を持つpositionを引数に取りました。"); }
		}

	public: // member

		///	この参照が指し示す @a BitmapBuffer を取得します。
		const IBufferType& Buffer() const noexcept { return _buf; }

		///	この参照が指し示す @a BitmapBuffer を取得します。
		IBufferType& Buffer() noexcept { return _buf; }

		///	この参照が指し示す座標を @a Point で取得します。
		Point getPosition() const noexcept { return Point(_x, _y); }

		///	参照先の値を @a RGBColor で取得します。
		RGBColor getRGBValue() const
		{
			switch (_buf.getColorSpace())
			{
				case BufferColorSpace::ARGB: return RGBColor(refChannel(0).ConvertTo<float>().value, refChannel(1).ConvertTo<float>().value, refChannel(2).ConvertTo<float>().value, refChannel(3).ConvertTo<float>().value);
				case BufferColorSpace::GrayScale:
				case BufferColorSpace::CMYK:
				case BufferColorSpace::AXYZ:
				default: throw InvalidOperationException("バッファに指定されている色空間が無効です。");
			}
		}

		///	参照先の値に @a BitmapPixelGetter の参照先の値を設定します。
		void setValue(const RGBColor& value)
		{
			switch (_buf.getColorSpace())
			{
				case BufferColorSpace::ARGB:
					refChannel(0) = ChannelValue<T>::ConvertFrom(value.getR());
					refChannel(1) = ChannelValue<T>::ConvertFrom(value.getG());
					refChannel(2) = ChannelValue<T>::ConvertFrom(value.getB());
					refChannel(3) = ChannelValue<T>::ConvertFrom(value.getAlpha());
					break;
				case BufferColorSpace::GrayScale:
				case BufferColorSpace::CMYK:
				case BufferColorSpace::AXYZ:
				default: throw InvalidOperationException("バッファに指定されている色空間が無効です。");
			}
		}

		///	この参照に指定されたオフセットを加えた参照に、参照先が存在するかを取得します。
		///
		///	@param	[in]offset
		///	座標のオフセット。
		///
		///	@return
		///	参照先が存在すれば @a true 、存在しなければ @a false が返ります。
		bool HasOffset(const Point& offset) const noexcept { return HasValue(_buf, getPosition() + offset); }

		///	この参照に指定されたオフセットを加えた参照を取得します。
		///	@param	[in]offset
		///	座標のオフセット。
		///	@return
		///	オフセットを加えた参照が返ります。
		BitmapPixelReference Offset(const Point& offset) { return BitmapPixelReference<T>(_buf, getPosition() + offset); }

		///	この参照に指定されたオフセットを加えた参照を取得します。
		///	@param	[in]offset
		///	座標のオフセット。
		///	@return
		///	オフセットを加えた参照が返ります。
		const BitmapPixelReference Offset(const Point& offset) const { return BitmapPixelReference<T>(_buf, getPosition() + offset); }

	private: // internal

		///	指定したBitmapBufferの指定した座標が存在するかを取得します。
		///	@param	buffer
		///	参照先の @a BitmapBuffer 。
		///	@param	x
		///	参照先のx座標。
		///	@param	y
		///	参照先のy座標。
		///	@return
		///	参照先にピクセルが存在すれば @a true 、そうでなければ @a false が返ります。
		static bool HasValue(const IBufferType& buffer, const size_t& x, const size_t& y) noexcept
		{
			if ((buffer.getHorizonalSize() > x)&&(buffer.getVerticalSize() > y)) { return true; }
			else { return false; }
		}

		///	指定したBitmapBufferの指定した座標が存在するかを取得します。
		///	@param	buffer
		///	参照先の @a BitmapBuffer 。
		///	@param	pos
		///	参照先の座標。
		///	@return
		///	参照先にピクセルが存在すれば @a true 、そうでなければ @a false が返ります。
		static bool HasValue(const IBufferType& buffer, const Point& pos) noexcept
		{
			if ((pos.getX() < 0)||(pos.getY() < 0)) { return false; }
			return HasValue(buffer, pos.getX(), pos.getY());
		}

		const ChannelValue<T>& refChannel(const size_t& channel) const { return _buf.Index(_x, _y, channel); }

		ChannelValue<T>& refChannel(const size_t& channel) { return _buf.Index(_x, _y, channel); }

	};

}
#endif // __StationaryOrbit_Graphics_BitmapPixelReference__