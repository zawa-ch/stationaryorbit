#ifndef __stationaryorbit_graphics_wbmp_wbmpbuffer__
#define __stationaryorbit_graphics_wbmp_wbmpbuffer__
#include <vector>
#include "stationaryorbit/graphics-core/bitmap"
#include "colormask.hpp"
#include "wbmpheaders.hpp"
namespace zawa_ch::StationaryOrbit::Graphics::WBMP
{
	///	Windowsビットマップとしてデータにアクセスするための基本クラスです。
	class WbmpBufferBase
		: virtual public BitmapBufferBase<uint8_t>
	{
	public: // interface
		///	バッファのビット深度を取得します。
		virtual BitDepth GetBitDepth() const noexcept = 0;
		virtual size_t LinearLength() const noexcept = 0;
		virtual uint8_t& LinearIndex(const size_t& position) = 0;
		virtual const uint8_t& LinearIndex(const size_t& position) const = 0;
	public: // copy/move/destruct
		virtual ~WbmpBufferBase() = default;
	};
	///	非圧縮RGBのWindowsビットマップとしてデータにアクセスします。
	class WbmpRGBData
		: virtual public WbmpBufferBase
	{
	public: // types
		typedef ChannelValue<uint8_t> ChannelValueType;
	public: // interface
		///	このバッファから値を取得する際の色マスクを取得します。
		virtual ColorMask GetColorMask() const = 0;
	public: // inplement BitmapBase
		///	バッファに使用されている色空間を取得します。 @a WbmpRGBData では常に @a BitmapColorSpace::ARGB が返ります。
		virtual BitmapColorSpace GetColorSpace() const;
	public: // implement BitmapBufferBase
		///	このバッファのチャネル数を取得します。 @a WbmpRGBData では色空間に必ず @a BitmapColorSpace::ARGB を使用するため、常に4が返ります。
		virtual size_t GetChannelCount() const noexcept;
		///	指定された1ピクセル・1チャネルにおける値を取得します。
		virtual ReadOnlyProperty<BitmapBufferBase<uint8_t>, ChannelValueType> Index(const size_t& x, const size_t& y, const size_t& ch) const;
		///	指定された1ピクセル・1チャネルにおける値を取得します。
		virtual ReadOnlyProperty<BitmapBufferBase<uint8_t>, ChannelValueType> Index(const Point& pos, const size_t& ch) const;
		///	指定された1ピクセル・1チャネルにおける値を取得します。
		virtual Property<BitmapBufferBase<uint8_t>, ChannelValueType> Index(const size_t& x, const size_t& y, const size_t& ch);
		///	指定された1ピクセル・1チャネルにおける値を取得します。
		virtual Property<BitmapBufferBase<uint8_t>, ChannelValueType> Index(const Point& pos, const size_t& ch);
	public: // static
		static size_t CalcLength(const size_t& x, const size_t& y, const BitDepth& depth) noexcept;
		static size_t CalcLineLength(const size_t& x, const BitDepth& depth) noexcept;
		static ColorMask DefaultColorMask(const BitDepth& depth);
	private: // internal
		size_t calcIndex(const size_t& x, const size_t& y) const noexcept;
		static ChannelValueType getIndex(const BitmapBufferBase<uint8_t>& inst, const size_t& x, const size_t& y, const size_t& ch);
		static void setIndex(BitmapBufferBase<uint8_t>& inst, const size_t& x, const size_t& y, const size_t& ch, const ChannelValueType& value);
	};
	///	非圧縮RGBのWindowsビットマップとしてデータを保持します。
	class WbmpRGBBuffer
		: virtual public WbmpRGBData
	{
	private: // contains
		size_t _x;
		size_t _y;
		BitDepth _depth;
		ColorMask _mask;
		std::vector<uint8_t> _data;
	public: // construct
		WbmpRGBBuffer() = default;
		WbmpRGBBuffer(const size_t& x, const size_t& y, const BitDepth& depth);
		WbmpRGBBuffer(const Point& size, const BitDepth& depth);
		WbmpRGBBuffer(const size_t& x, const size_t& y, const BitDepth& depth, const ColorMask& mask);
		WbmpRGBBuffer(const Point& size, const BitDepth& depth, const ColorMask& mask);
	public: // implement BitmapBase
		///	このバッファの幅を取得します。
		size_t GetWidth() const noexcept;
		///	このバッファの高さを取得します。
		size_t GetHeight() const noexcept;
	public: // implement WbmpBufferBase
		BitDepth GetBitDepth() const noexcept;
		size_t LinearLength() const noexcept;
		uint8_t& LinearIndex(const size_t& position);
		const uint8_t& LinearIndex(const size_t& position) const;
	public: // implement WbmpRGBData
		///	このバッファから値を取得する際の色マスクを取得します。
		ColorMask GetColorMask() const;
	};
}
#endif // __stationaryorbit_graphics_wbmp_wbmpbuffer__