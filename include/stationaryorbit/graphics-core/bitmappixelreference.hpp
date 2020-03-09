#ifndef __stationaryorbit_graphics_core_bitmappixelreference__
#define __stationaryorbit_graphics_core_bitmappixelreference__
#include "stationaryorbit/exception/soexcept"
#include "point.hpp"
#include "channelvalue.hpp"
#include "rgbcolor.hpp"
#include "bitmapbuffer.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{

	/// @a Bitmap 上のピクセルへの読取り専用の参照を表す基本クラスです。
	class ConstPixelReference
	{
	public:
		///	参照先の値を @a RGBColor で取得します。
		virtual RGBColor GetRGBValue() const = 0;
		///	このオブジェクトの参照先が存在するかを取得します。
		virtual bool HasValue() const noexcept = 0;
		///	この参照にオフセットを加えた先に、参照先が存在するかを取得します。
		virtual bool HasOffset(const Point& offset) const noexcept = 0;
		///	この参照にオフセットを加えた先の値を @a RGBColor で取得します。
		virtual RGBColor GetOffsetRGBValue(const Point& offset) const = 0;
		virtual ~ConstPixelReference() = default;
	};
	/// @a Bitmap 上のピクセルへの参照を表す基本クラスです。
	class PixelReference
		: virtual public ConstPixelReference
	{
	public:
		///	参照先に @a RGBColor の値を設定します。
		virtual void SetValue(const RGBColor& value) = 0;
		///	参照先の値に @a BitmapPixelGetter の参照先の値を設定します。
		virtual void SetValue(const PixelReference& value) = 0;
		///	この参照にオフセットを加えた先に @a RGBColor の値を設定します。
		virtual void SetOffsetRGBValue(const Point& offset, const RGBColor& value) = 0;
		///	この参照にオフセットを加えた先の値に @a BitmapPixelGetter の参照先の値を設定します。
		virtual void SetOffsetRGBValue(const Point& offset, const PixelReference& value) = 0;
		virtual ~PixelReference() = default;
	};
	///	@a BitmapBufferBase を使用した @a Bitmap 上のピクセルへの読み取り専用の参照を表します。
	template<class T>
	class BitmapConstPixelReference final
		: virtual public ConstPixelReference
	{
	public: // type
		typedef BitmapBufferBase<T> IBufferType;
	private: // contains
		///	参照先の @a BitmapBuffer 。
		const IBufferType& _buf;
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
		BitmapConstPixelReference(const IBufferType& buffer, const size_t& x, const size_t& y) : _buf(buffer), _x(x), _y(y) {}
		///	@a Bitmap のピクセルへの参照を作成します。
		///	@param	buffer
		///	参照先の @a BitmapBuffer 。
		///	@param	position
		///	参照先の座標。
		BitmapConstPixelReference(const IBufferType& buffer, const Point& position) : BitmapConstPixelReference(buffer, position.getX(), position.getY())
		{
			if ((position.getX() < 0)||(position.getY() < 0)) { throw std::invalid_argument("負の値を持つ position を引数に取りました。"); }
		}
		virtual ~BitmapConstPixelReference() = default;
	public: // member
		///	この参照が指し示す @a BitmapBuffer を取得します。
		const IBufferType& Buffer() const noexcept { return _buf; }
		///	この参照が指し示す座標を @a Point で取得します。
		Point Position() const noexcept { return Point(_x, _y); }
		///	この参照に指定されたオフセットを加えた参照を取得します。
		///	@param	[in]offset
		///	座標のオフセット。
		///	@return
		///	オフセットを加えた参照が返ります。
		const BitmapConstPixelReference<T> Offset(const Point& offset) const { return BitmapConstPixelReference<T>(_buf, Position() + offset); }
		///	指定されたチャネルの値を取得します。
		const ChannelValue<T>& Dereference(const size_t& channel) const { return _buf.Index(_x, _y, channel); }
	public: // implement ConstPixelReference
		///	参照先の値を @a RGBColor で取得します。
		RGBColor GetRGBValue() const
		{
			switch (_buf.GetColorSpace())
			{
			case BitmapColorSpace::ARGB:
				return RGBColor(
					ChannelValue<float>(Dereference(0)).value,
					ChannelValue<float>(Dereference(1)).value,
					ChannelValue<float>(Dereference(2)).value,
					ChannelValue<float>(Dereference(3)).value);
			case BitmapColorSpace::GrayScale:
			case BitmapColorSpace::CMYK:
			case BitmapColorSpace::AXYZ:
			default: throw InvalidOperationException("バッファに指定されている色空間が無効です。");
			}
		}
		///	このオブジェクトの参照先が存在するかを取得します。
		bool HasValue() const noexcept
		{
			if ((_buf.GetHorizonalSize() > _x)&&(_buf.GetVerticalSize() > _y)) { return true; }
			else { return false; }
		}
		///	この参照にオフセットを加えた先に、参照先が存在するかを取得します。
		bool HasOffset(const Point& offset) const noexcept { return Offset(offset).HasValue(); }
		///	この参照にオフセットを加えた先の値を @a RGBColor で取得します。
		RGBColor GetOffsetRGBValue(const Point& offset) const { return Offset(offset).GetRGBValue(); }
	};
	///	@a BitmapBufferBase を使用した @a Bitmap 上のピクセルへの参照を表します。
	template<class T>
	class BitmapPixelReference final
		: virtual public PixelReference
	{
	public: // type
		typedef BitmapBufferBase<T> IBufferType;
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
		virtual ~BitmapPixelReference() = default;
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
		BitmapPixelReference<T> Offset(const Point& offset) { return BitmapPixelReference<T>(_buf, Position() + offset); }
		///	この参照に指定されたオフセットを加えた参照を取得します。
		///	@param	[in]offset
		///	座標のオフセット。
		///	@return
		///	オフセットを加えた参照が返ります。
		const BitmapPixelReference<T> Offset(const Point& offset) const { return BitmapPixelReference<T>(_buf, Position() + offset); }
		///	指定されたチャネルの値を取得します。
		const ChannelValue<T>& Dereference(const size_t& channel) const { return _buf.Index(_x, _y, channel); }
		///	指定されたチャネルの値を取得します。
		ChannelValue<T>& Dereference(const size_t& channel) { return _buf.Index(_x, _y, channel); }
	public: // implement PixelReference
		///	参照先の値を @a RGBColor で取得します。
		RGBColor GetRGBValue() const
		{
			switch (_buf.GetColorSpace())
			{
			case BitmapColorSpace::ARGB:
				return RGBColor(
					ChannelValue<float>(Dereference(0)).value,
					ChannelValue<float>(Dereference(1)).value,
					ChannelValue<float>(Dereference(2)).value,
					ChannelValue<float>(Dereference(3)).value);
			case BitmapColorSpace::GrayScale:
			case BitmapColorSpace::CMYK:
			case BitmapColorSpace::AXYZ:
			default: throw InvalidOperationException("バッファに指定されている色空間が無効です。");
			}
		}
		///	参照先に @a RGBColor の値を設定します。
		void SetValue(const RGBColor& value)
		{
			switch (_buf.GetColorSpace())
			{
			case BitmapColorSpace::ARGB:
				Dereference(0) = ChannelValue<T>(value.getR());
				Dereference(1) = ChannelValue<T>(value.getG());
				Dereference(2) = ChannelValue<T>(value.getB());
				Dereference(3) = ChannelValue<T>(value.getAlpha());
				break;
			case BitmapColorSpace::GrayScale:
			case BitmapColorSpace::CMYK:
			case BitmapColorSpace::AXYZ:
			default: throw InvalidOperationException("バッファに指定されている色空間が無効です。");
			}
		}
		///	参照先の値に @a BitmapPixelGetter の参照先の値を設定します。
		void SetValue(const PixelReference& value)
		{
			switch(_buf.GetColorSpace())
			{
			case BitmapColorSpace::ARGB:
				SetValue(value.GetRGBValue());
				break;
			case BitmapColorSpace::GrayScale:
			case BitmapColorSpace::CMYK:
			case BitmapColorSpace::AXYZ:
			default: throw InvalidOperationException("バッファに指定されている色空間が無効です。");
			}
		}
		///	このオブジェクトの参照先が存在するかを取得します。
		bool HasValue() const noexcept
		{
			if ((_buf.GetHorizonalSize() > _x)&&(_buf.GetVerticalSize() > _y)) { return true; }
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
	};

}
#endif // __stationaryorbit_graphics_core_bitmappixelreference__