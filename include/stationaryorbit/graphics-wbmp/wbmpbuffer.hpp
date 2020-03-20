#ifndef __stationaryorbit_graphics_wbmp_wbmpbuffer__
#define __stationaryorbit_graphics_wbmp_wbmpbuffer__
#include <vector>
#include <iostream>
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
		///	バッファの大きさを取得します。
		virtual size_t LinearLength() const noexcept = 0;
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
		///	指定された1ピクセルの値を取得します。
		virtual uint32_t GetPixel(const size_t& x, const size_t& y) const = 0;
		///	指定された1ピクセルに値を設定します。
		virtual void SetPixel(const size_t& x, const size_t& y, const uint32_t& value) = 0;
	public: // member
		///	このバッファでのピクセルへの読み書きに用いるビットマスクを取得します。 @a WbmpRGBData では常に @a BitDepth の値によって決定されます。
		ColorMask GetColorMask() const;
	public: // inplement BitmapBase
		///	バッファに使用されている色空間を取得します。 @a WbmpRGBData では常に @a BitmapColorSpace::ARGB が返ります。
		BitmapColorSpace GetColorSpace() const;
	public: // implement BitmapBufferBase
		///	このバッファのチャネル数を取得します。 @a WbmpRGBData では色空間に必ず @a BitmapColorSpace::ARGB を使用するため、常に4が返ります。
		size_t GetChannelCount() const noexcept;
		///	指定された1ピクセル・1チャネルにおける値を取得します。
		ReadOnlyProperty<BitmapBufferBase<uint8_t>, ChannelValueType> Index(const size_t& x, const size_t& y, const size_t& ch) const;
		///	指定された1ピクセル・1チャネルにおける値を取得します。
		ReadOnlyProperty<BitmapBufferBase<uint8_t>, ChannelValueType> Index(const Point& pos, const size_t& ch) const;
		///	指定された1ピクセル・1チャネルにおける値を取得します。
		Property<BitmapBufferBase<uint8_t>, ChannelValueType> Index(const size_t& x, const size_t& y, const size_t& ch);
		///	指定された1ピクセル・1チャネルにおける値を取得します。
		Property<BitmapBufferBase<uint8_t>, ChannelValueType> Index(const Point& pos, const size_t& ch);
	public: // static
		static ColorMask DefaultColorMask(const BitDepth& depth);
	private: // internal
		static ChannelValueType getIndex(const BitmapBufferBase<uint8_t>& inst, const size_t& x, const size_t& y, const size_t& ch);
		static void setIndex(BitmapBufferBase<uint8_t>& inst, const size_t& x, const size_t& y, const size_t& ch, const ChannelValueType& value);
	public: // copy/move/destruct
		virtual ~WbmpRGBData() = default;
	};
	///	非圧縮RGBのWindowsビットマップとしてデータを保持します。
	class WbmpRGBBuffer
		: virtual public WbmpRGBData
	{
	private: // contains
		size_t _width;
		size_t _height;
		BitDepth _depth;
		std::vector<uint8_t> _data;
	public: // construct
		WbmpRGBBuffer() = default;
		WbmpRGBBuffer(const size_t& width, const size_t& height, const BitDepth& depth);
		WbmpRGBBuffer(const Point& size, const BitDepth& depth);
	public: // member
		std::vector<uint8_t>& Data();
		const std::vector<uint8_t>& Data() const;
	public: // implement BitmapBase
		///	このバッファの幅を取得します。
		size_t GetWidth() const noexcept;
		///	このバッファの高さを取得します。
		size_t GetHeight() const noexcept;
	public: // implement WbmpBufferBase
		///	バッファの大きさを取得します。
		size_t LinearLength() const noexcept;
		BitDepth GetBitDepth() const noexcept;
	public: // implement WbmpRGBData
		uint32_t GetPixel(const size_t& x, const size_t& y) const;
		void SetPixel(const size_t& x, const size_t& y, const uint32_t& value);
	private: // internal
		static size_t CalcLength(const size_t& x, const size_t& y, const BitDepth& depth) noexcept;
		static size_t CalcLineLength(const size_t& x, const BitDepth& depth) noexcept;
		size_t CalcIndex(const size_t& x, const size_t& y) const noexcept;
	};
	class WbmpRGBStreamData
		: virtual public WbmpRGBData
	{
	private: // contains
		std::iostream& _stream;
		std::streampos _offset;
		size_t _width;
		size_t _height;
		BitDepth _depth;
	public: // construct
		WbmpRGBStreamData(std::iostream& stream, const size_t& width, const size_t& height, const BitDepth& depth, std::streampos offset = 0U);
		WbmpRGBStreamData(std::iostream& stream, const Point& size, const BitDepth& depth, std::streampos offset = 0U);
	public: // member
		std::iostream& Stream();
	public: // implement BitmapBase
		///	このバッファの幅を取得します。
		size_t GetWidth() const noexcept;
		///	このバッファの高さを取得します。
		size_t GetHeight() const noexcept;
	public: // implement WbmpBufferBase
		///	バッファの大きさを取得します。
		size_t LinearLength() const noexcept;
		BitDepth GetBitDepth() const noexcept;
	public: // implement WbmpRGBData
		uint32_t GetPixel(const size_t& x, const size_t& y) const;
		void SetPixel(const size_t& x, const size_t& y, const uint32_t& value);
	private: // internal
		static size_t CalcLength(const size_t& x, const size_t& y, const BitDepth& depth) noexcept;
		static size_t CalcLineLength(const size_t& x, const BitDepth& depth) noexcept;
		size_t CalcIndex(const size_t& x, const size_t& y) const noexcept;
	};
}
#endif // __stationaryorbit_graphics_wbmp_wbmpbuffer__