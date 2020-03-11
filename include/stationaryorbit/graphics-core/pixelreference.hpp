#ifndef __stationaryorbit_graphics_core_pixelreference__
#define __stationaryorbit_graphics_core_pixelreference__
#include <cstddef>
#include "point.hpp"
#include "rgbcolor.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	class Bitmap;

	/// @a Bitmap 上のピクセルへの読取り専用の参照を表す基本クラスです。
	class ConstPixelReference
	{
	protected: // member
		const Bitmap& _cbitmap;
		size_t _x;
		size_t _y;
	public: // constructor
		ConstPixelReference(const Bitmap& bitmap, const size_t& x, const size_t& y) noexcept;
		ConstPixelReference(const Bitmap& bitmap, const Point& position) noexcept;
	public: // member
		///	この参照が指し示す @a Bitmap を取得します。
		virtual const Bitmap& GetBitmap() const;
		///	この参照が指し示す座標を @a Point で取得します。
		virtual Point Position() const noexcept;
		///	参照先の値を @a RGBColor で取得します。
		virtual RGBColor GetRGBValue() const;
		///	このオブジェクトの参照先が存在するかを取得します。
		virtual bool HasValue() const noexcept;
		///	この参照にオフセットを加えた先に、参照先が存在するかを取得します。
		virtual bool HasOffset(const Point& offset) const noexcept;
		///	この参照に指定されたオフセットを加えた参照を取得します。
		///	@param	[in]offset
		///	座標のオフセット。
		///	@return
		///	オフセットを加えた参照が返ります。
		virtual ConstPixelReference Offset(const Point& offset) const noexcept;
	public: // copy/move/destruct
		virtual ~ConstPixelReference() = default;
	};
	/// @a Bitmap 上のピクセルへの参照を表す基本クラスです。
	class PixelReference
		: virtual public ConstPixelReference
	{
	protected: // member
		Bitmap& _bitmap;
	public: // constructor
		PixelReference(Bitmap& bitmap, const size_t& x, const size_t& y) noexcept;
		PixelReference(Bitmap& bitmap, const Point& position) noexcept;
	public: // member
		///	参照先に @a RGBColor の値を設定します。
		virtual void SetValue(const RGBColor& value);
		///	この参照に指定されたオフセットを加えた参照を取得します。
		///	@param	[in]offset
		///	座標のオフセット。
		///	@return
		///	オフセットを加えた参照が返ります。
		virtual PixelReference Offset(const Point& offset) noexcept;
	public: // copy/move/destruct
		virtual ~PixelReference() = default;
	};

}
#endif // __stationaryorbit_graphics_core_pixelreference__