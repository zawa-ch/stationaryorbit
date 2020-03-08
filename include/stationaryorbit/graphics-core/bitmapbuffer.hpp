#ifndef __stationaryorbit_graphics_core_bitmapbuffer__
#define __stationaryorbit_graphics_core_bitmapbuffer__
#include <cstddef>
#include <vector>
#include <stdexcept>
#include <functional>
#include "stationaryorbit/core/numeral"
#include "channelvalue.hpp"
#include "graphicscore.hpp"
#include "point.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{

	///	バッファ内部のデータ構造として用いる色空間を表します。
	enum class BufferColorSpace
	{
		///	グレースケール。
		GrayScale,
		///	RGB(+アルファ)色空間。
		ARGB,
		///	CMYK色空間。
		CMYK,
		///	XYZ(+アルファ)色空間。
		AXYZ
	};

	///	画像情報を保持するための記憶領域を提供し、アクセスを行うためのメソッドを実装します。
	///	@param	T
	///	値の表現に使用する型。
	template<class T>
    class IBitmapBuffer
    {
    public:

		typedef ChannelValue<T> ValueType;
		typedef size_t SizeType;

		///	このバッファの幅を取得します。
		virtual SizeType getHorizonalSize() const = 0;

		///	このバッファの高さを取得します。
		virtual SizeType getVerticalSize() const = 0;

		///	バッファに使用されている色空間を取得します。
		virtual BufferColorSpace getColorSpace() const = 0;

		///	指定された1ピクセル・1チャネルにおける値を取得します。
		virtual const ValueType& Index(const SizeType& x, const SizeType& y, const SizeType& ch) const = 0;

		///	指定された1ピクセル・1チャネルにおける値を取得します。
		virtual ValueType& Index(const SizeType& x, const SizeType& y, const SizeType& ch) = 0;

    };

	///	画像情報を保持するためのメモリ空間を提供します。
	///	@param	T
	///	値の表現に使用する型。
	template<class T = float>
	class BitmapBuffer
		: virtual public IBitmapBuffer<T>
	{
    public: // type

		typedef ChannelValue<T> ValueType;
		typedef size_t SizeType;

	private: // contains

		SizeType _x;
		SizeType _y;
		BufferColorSpace _space;
		std::vector<ValueType> _data;

	public: // constructor

		///	既定の @a BitmapBuffer を初期化します。
		BitmapBuffer() = default;

		///	指定されたサイズのキャンバスを確保し、このオブジェクトを初期化します。
		///	@param	x
		///	Bitmapの幅。
		///	@param	y
		///	Bitmapの高さ。
		///	@param	ch
		///	Bitmapのチャネル数。
		BitmapBuffer(const SizeType& x, const SizeType& y, const BufferColorSpace& space) : _x(x), _y(y), _space(space), _data(CalcLength(x, y, space)) {}

		///	指定されたサイズのキャンバスを確保し、このオブジェクトを初期化します。
		///	@param	size
		///	Bitmapの大きさ。
		///	@param	ch
		///	Bitmapのチャネル数。
		BitmapBuffer(const Point& size, const BufferColorSpace& space) : BitmapBuffer(size.getX(), size.getY(), space)
		{
			if ((size.getX() < 0)||(size.getY() < 0)) { throw std::invalid_argument("負の値を持つsizeを引数に取りました。"); }
		}

		///	指定されたキャンバスの内容を複製します。
		///	@param	value
		///	複製元の @a IBitmapBuffer 。
		explicit BitmapBuffer(const IBitmapBuffer<T>& value) : BitmapBuffer(value.getHorizonalSize(), value.getVerticalSize(), value.getColorSpace())
		{
			for (auto y : Range<size_t>(0, _y))
			{
				for (auto x : Range<size_t>(0, _x))
				{
					for (auto ch : Range<size_t>(0, CalcChCount(_space)))
					{
						Index(x, y, ch) = value.Index(x, y, ch);
					}
				}
			}
		}

	public: // member

		///	このバッファの幅を取得します。
		SizeType getHorizonalSize() const noexcept { return _x; }

		///	このバッファの高さを取得します。
		SizeType getVerticalSize() const noexcept { return _y; }

		///	バッファに使用されている色空間を取得します。
		BufferColorSpace getColorSpace() const noexcept { return _space; }

		///	指定された1ピクセル・1チャネルにおける値を取得します。
		const ValueType& Index(const SizeType& x, const SizeType& y, const SizeType& ch) const
		{
			if (_x <= x) throw new std::out_of_range("x が画像エリアの範囲外です。");
			if (_y <= y) throw new std::out_of_range("y が画像エリアの範囲外です。");
			if (CalcChCount(_space) <= ch) throw new std::out_of_range("ch が画像エリアの範囲外です。");
			return _data[(y*_x + x)*CalcChCount(_space) + ch];
		}

		///	指定された1ピクセル・1チャネルにおける値を取得します。
		ValueType& Index(const SizeType& x, const SizeType& y, const SizeType& ch)
		{
			if (_x <= x) throw new std::out_of_range("x が画像エリアの範囲外です。");
			if (_y <= y) throw new std::out_of_range("y が画像エリアの範囲外です。");
			if (CalcChCount(_space) <= ch) throw new std::out_of_range("ch が画像エリアの範囲外です。");
			return _data[(y*_x + x)*CalcChCount(_space) + ch];
		}

		template<class destT>
		BitmapBuffer<destT> ConvertTo() const
		{
			auto result = BitmapBuffer<destT>(_x, _y, _space);
			for (auto y : Range<size_t>(0, _y))
			{
				for (auto x : Range<size_t>(0, _x))
				{
					for (auto ch : Range<size_t>(0, CalcChCount(_space)))
					{
						result.Index(x, y, ch) = ChannelValue<destT>(Index(x, y, ch));
					}
				}
			}
			return result;
		}

	public: // static

		template<class FromT>
		static BitmapBuffer<T> ConvertFrom(const IBitmapBuffer<FromT>& value)
		{
			auto result = BitmapBuffer<T>(value.getHorizonalSize(), value.getVerticalSize(), value.getColorSpace());
			for (auto y : Range<size_t>(0, result._y))
			{
				for (auto x : Range<size_t>(0, result._x))
				{
					for (auto ch : Range<size_t>(0, CalcChCount(result._space)))
					{
						result.Index(x, y, ch) = ChannelValue<T>(value.Index(x, y, ch));
					}
				}
			}
			return result;
		}

	private: // internal

		///	各色空間が使用するチャネル数を取得します。
		constexpr static size_t CalcChCount(const BufferColorSpace& space)
		{
			switch(space)
			{
			case BufferColorSpace::GrayScale: return 1;
			case BufferColorSpace::ARGB: return 4;
			case BufferColorSpace::CMYK: return 4;
			case BufferColorSpace::AXYZ: return 4;
			}
		}

		///	オブジェクトが使用するオブジェクト数を算出します。
		///	@param	x
		///	Bitmapの幅。
		///	@param	y
		///	Bitmapの高さ。
		///	@param	space
		///	Bitmapの色空間。
		///	@return
		///	算出されたオブジェクト数が返ります。
		constexpr static size_t CalcLength(const size_t& x, const size_t& y, const BufferColorSpace& space) noexcept { return x * y * CalcChCount(space); }

	};

}
#endif // __stationaryorbit_graphics_core_bitmapbuffer__