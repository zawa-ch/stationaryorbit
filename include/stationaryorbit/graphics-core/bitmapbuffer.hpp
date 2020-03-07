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
#include "imageinfomation.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{

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

		///	このバッファのチャネル数を取得します。
		virtual SizeType getChannel() const = 0;

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
	private: // contains

		SizeType _x;
		SizeType _y;
		SizeType _ch;
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
		BitmapBuffer(const SizeType& x, const SizeType& y, const SizeType& ch) : _x(x), _y(y), _ch(ch), _data(CalcLength(x, y, ch)) {}

		///	指定されたサイズのキャンバスを確保し、このオブジェクトを初期化します。
		///	@param	size
		///	Bitmapの大きさ。
		///	@param	ch
		///	Bitmapのチャネル数。
		BitmapBuffer(const Point& size, const SizeType& ch) : BitmapBuffer(size.getX(), size.getY(), ch)
		{
			if ((size.getX() < 0)||(size.getY() < 0)) { throw std::invalid_argument("負の値を持つsizeを引数に取りました。"); }
		}

		///	指定されたサイズのキャンバスを確保し、このオブジェクトを初期化します。
		///	@param	info
		///	キャンバスの生成時に用いるキャンバス情報。
		explicit BitmapBuffer(const IImageInfomation& info) : BitmapBuffer(info.getSize(), Graphics::GetChannelFromColorSpace(info.getColorSystem())) {}

		///	指定されたキャンバスの内容を複製します。
		///	@param	value
		///	複製元の @a IBitmapBuffer 。
		explicit BitmapBuffer(const IBitmapBuffer<T>& value) : BitmapBuffer(value.getHorizonalSize(), value.getVerticalSize(), value.getChannel())
		{
			for (auto y : Range<size_t>(0, _y))
			{
				for (auto x : Range<size_t>(0, _x))
				{
					for (auto ch : Range<size_t>(0, _ch))
					{
						Index(x, y, ch) = value.Index(x, y, ch);
					}
				}
			}
		}

	public: // member

		///	このバッファの幅を取得します。
		SizeType getHorizonalSize() const { return _x; }

		///	このバッファの高さを取得します。
		SizeType getVerticalSize() const { return _y; }

		///	このバッファのチャネル数を取得します。
		size_t getChannel() const { return _ch; }

		///	指定された1ピクセル・1チャネルにおける値を取得します。
		const ValueType& Index(const SizeType& x, const SizeType& y, const SizeType& ch) const
		{
			if (_x <= x) throw new std::out_of_range("x が画像エリアの範囲外です。");
			if (_y <= y) throw new std::out_of_range("y が画像エリアの範囲外です。");
			if (_ch <= ch) throw new std::out_of_range("ch が画像エリアの範囲外です。");
			return _data[(y*_x + x)*_ch + ch];
		}

		///	指定された1ピクセル・1チャネルにおける値を取得します。
		ValueType& Index(const SizeType& x, const SizeType& y, const SizeType& ch)
		{
			if (_x <= x) throw new std::out_of_range("x が画像エリアの範囲外です。");
			if (_y <= y) throw new std::out_of_range("y が画像エリアの範囲外です。");
			if (_ch <= ch) throw new std::out_of_range("ch が画像エリアの範囲外です。");
			return _data[(y*_x + x)*_ch + ch];
		}

	public: // static

		template<class FromT>
		static BitmapBuffer<T> Convert(const IBitmapBuffer<FromT>& value)
		{
			auto result = BitmapBuffer<T>(value.getHorizonalSize(), value.getVerticalSize(), value.getChannel());
			for (auto y : Range<size_t>(0, result._y))
			{
				for (auto x : Range<size_t>(0, result._x))
				{
					for (auto ch : Range<size_t>(0, result._ch))
					{
						Index(x, y, ch) = value.Index(x, y, ch).ConvertTo<T>();
					}
				}
			}
			return result;
		}

	private: // internal

		///	オブジェクトが使用するオブジェクト数を算出します。
		///	@param	x
		///	Bitmapの幅。
		///	@param	y
		///	Bitmapの高さ。
		///	@param	ch
		///	Bitmapの色チャネル数。
		///	@return
		///	算出されたオブジェクト数が返ります。
		static size_t CalcLength(const size_t& x, const size_t& y, const size_t& ch) noexcept { return x * y * ch; }

	};

}
#endif // __stationaryorbit_graphics_core_bitmapbuffer__