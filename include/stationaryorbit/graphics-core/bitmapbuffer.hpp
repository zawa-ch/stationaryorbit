#ifndef __stationaryorbit_graphics_core_bitmapbuffer__
#define __stationaryorbit_graphics_core_bitmapbuffer__
#include <cstddef>
#include <vector>
#include "stationaryorbit/exception/soexcept"
#include "stationaryorbit/core/numeral"
#include "basetypes.hpp"
#include "point.hpp"
#include "channelvalue.hpp"
#include "pixelreference.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{

	///	画像情報を保持するための記憶領域を提供し、アクセスを行うためのメソッドを実装します。
	///	@param	T
	///	値の表現に使用する型。
	template<class T>
    class BitmapBufferBase
		: virtual public BitmapBase
    {
    public:
		///	指定された1ピクセル・1チャネルにおける値を取得します。
		virtual const ChannelValue<T>& Index(const size_t& x, const size_t& y, const size_t& ch) const = 0;
		///	指定された1ピクセル・1チャネルにおける値を取得します。
		virtual ChannelValue<T>& Index(const size_t& x, const size_t& y, const size_t& ch) = 0;
		///	このバッファのチャネル数を取得します。
		virtual size_t GetChannelCount() const noexcept = 0;
		virtual ~BitmapBufferBase() = default;
    };
	///	@a BitmapBufferBase の内容を反復して処理するための参照を表します。
	template<class T>
	class BitmapBufferIterator final
	{
	public:
		typedef BitmapBufferBase<T> ContainerType;
		typedef ChannelValue<T> ValueType;
	private: // contains
		ContainerType& _container;
		size_t _pos;
	public: // constructor
		BitmapBufferIterator(ContainerType& container, const size_t position) noexcept : _container(container), _pos(position) {}
	public: // member
		ValueType& Current() { return _container.Index((_pos / _container.GetChannelCount()) % _container.GetHorizonalSize(), _pos / (_container.GetHorizonalSize() * _container.GetChannelCount()), _pos % _container.GetChannelCount()); }
		bool Equals(const BitmapBufferIterator& other) const noexcept { return _pos == other._pos; }
	public: // implement LegacyIterator
		ValueType& operator*() { return Current(); }
		BitmapBufferIterator& operator++() noexcept { _pos++; return *this; }
	public: // implement LegacyInputIterator
		bool operator==(const BitmapBufferIterator& other) const noexcept { return Equals(other); }
		bool operator!=(const BitmapBufferIterator& other) const noexcept { return !Equals(other); }
		ValueType* operator->() { return &(Current()); }
	public: // implement LegacyBidirectionalIterator
		BitmapBufferIterator& operator--() noexcept { _pos--; return *this; }
	};
	///	@a BitmapBufferBase の内容を反復して処理するための参照を表します。
	template<class T>
	class BitmapBufferConstIterator final
	{
	public:
		typedef BitmapBufferBase<T> ContainerType;
		typedef ChannelValue<T> ValueType;
	private: // contains
		const ContainerType& _container;
		size_t _pos;
	public: // constructor
		BitmapBufferConstIterator(const ContainerType& container, const size_t position) noexcept : _container(container), _pos(position) {}
	public: // member
		const ValueType& Current() const { return _container.Index((_pos / _container.GetChannelCount()) % _container.GetHorizonalSize(), _pos / (_container.GetHorizonalSize() * _container.GetChannelCount()), _pos % _container.GetChannelCount()); }
		bool Equals(const BitmapBufferConstIterator& other) const noexcept { return _pos == other._pos; }
	public: // implement LegacyIterator
		const ValueType& operator*() const { return Current(); }
		BitmapBufferConstIterator& operator++() noexcept { _pos++; return *this; }
	public: // implement LegacyInputIterator
		bool operator==(const BitmapBufferConstIterator& other) const noexcept { return Equals(other); }
		bool operator!=(const BitmapBufferConstIterator& other) const noexcept { return !Equals(other); }
		const ValueType* operator->() const { return &(Current()); }
	public: // implement LegacyBidirectionalIterator
		BitmapBufferConstIterator& operator--() noexcept { _pos--; return *this; }
	};
	///	@a BitmapBufferBase の内容を反復して処理するための参照を表します。
	template<class T>
	class BitmapBufferReverceIterator final
	{
	public:
		typedef BitmapBufferBase<T> ContainerType;
		typedef ChannelValue<T> ValueType;
	private: // contains
		ContainerType& _container;
		size_t _pos;
	public: // constructor
		BitmapBufferReverceIterator(ContainerType& container, const size_t position) noexcept : _container(container), _pos(position) {}
	public: // member
		ValueType& Current() { return _container.Index(((_pos - 1) / _container.GetChannelCount()) % _container.GetHorizonalSize(), (_pos - 1) / (_container.GetHorizonalSize() * _container.GetChannelCount()), (_pos - 1) % _container.GetChannelCount()); }
		bool Equals(const BitmapBufferReverceIterator& other) const noexcept { return _pos == other._pos; }
	public: // implement LegacyIterator
		ValueType& operator*() { return Current(); }
		BitmapBufferReverceIterator& operator++() noexcept { _pos--; return *this; }
	public: // implement LegacyInputIterator
		bool operator==(const BitmapBufferReverceIterator& other) const noexcept { return Equals(other); }
		bool operator!=(const BitmapBufferReverceIterator& other) const noexcept { return !Equals(other); }
		ValueType* operator->() { return &(Current()); }
	public: // implement LegacyBidirectionalIterator
		BitmapBufferReverceIterator& operator--() noexcept { _pos++; return *this; }
	};
	///	@a BitmapBufferBase の内容を反復して処理するための参照を表します。
	template<class T>
	class BitmapBufferConstReverceIterator final
	{
	public:
		typedef BitmapBufferBase<T> ContainerType;
		typedef ChannelValue<T> ValueType;
	private: // contains
		const ContainerType& _container;
		size_t _pos;
	public: // constructor
		BitmapBufferConstReverceIterator(const ContainerType& container, const size_t position) noexcept : _container(container), _pos(position) {}
	public: // member
		const ValueType& Current() const { return _container.Index(((_pos - 1) / _container.GetChannelCount()) % _container.GetHorizonalSize(), (_pos - 1) / (_container.GetHorizonalSize() * _container.GetChannelCount()), (_pos - 1) % _container.GetChannelCount()); }
		bool Equals(const BitmapBufferConstReverceIterator& other) const noexcept { return _pos == other._pos; }
	public: // implement LegacyIterator
		const ValueType& operator*() const { return Current(); }
		BitmapBufferConstReverceIterator& operator++() noexcept { _pos--; return *this; }
	public: // implement LegacyInputIterator
		bool operator==(const BitmapBufferConstReverceIterator& other) const noexcept { return Equals(other); }
		bool operator!=(const BitmapBufferConstReverceIterator& other) const noexcept { return !Equals(other); }
		const ValueType* operator->() const { return &(Current()); }
	public: // implement LegacyBidirectionalIterator
		BitmapBufferConstReverceIterator& operator--() noexcept { _pos++; return *this; }
	};
	///	画像情報を保持するためのメモリ空間を提供します。
	///	@param	T
	///	値の表現に使用する型。
	template<class T = float>
	class BitmapBuffer
		: virtual public BitmapBufferBase<T>
	{
    public: // type
		typedef ChannelValue<T> ValueType;
		typedef size_t SizeType;
		typedef BitmapBufferIterator<T> Iterator;
		typedef BitmapBufferConstIterator<T> ConstIterator;
		typedef BitmapBufferReverceIterator<T> ReverceIterator;
		typedef BitmapBufferConstReverceIterator<T> ConstReverceIterator;
	private: // contains
		SizeType _x;
		SizeType _y;
		BitmapColorSpace _space;
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
		BitmapBuffer(const SizeType& x, const SizeType& y, const BitmapColorSpace& space) : _x(x), _y(y), _space(space), _data(CalcLength(x, y, space)) {}
		///	指定されたサイズのキャンバスを確保し、このオブジェクトを初期化します。
		///	@param	size
		///	Bitmapの大きさ。
		///	@param	ch
		///	Bitmapのチャネル数。
		BitmapBuffer(const Point& size, const BitmapColorSpace& space) : BitmapBuffer(size.getX(), size.getY(), space)
		{
			if ((size.getX() < 0)||(size.getY() < 0)) { throw std::invalid_argument("負の値を持つsizeを引数に取りました。"); }
		}
		///	指定されたキャンバスの内容を複製します。
		///	@param	value
		///	複製元の @a BitmapBufferBase 。
		explicit BitmapBuffer(const BitmapBufferBase<T>& value) : BitmapBuffer(value.GetHorizonalSize(), value.GetVerticalSize(), value.GetColorSpace())
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
		virtual ~BitmapBuffer() = default;
	public: // member
		///	このバッファの幅を取得します。
		SizeType GetHorizonalSize() const noexcept { return _x; }
		///	このバッファの高さを取得します。
		SizeType GetVerticalSize() const noexcept { return _y; }
		///	バッファに使用されている色空間を取得します。
		BitmapColorSpace GetColorSpace() const noexcept { return _space; }
		///	このバッファのチャネル数を取得します。
		SizeType GetChannelCount() const noexcept { return CalcChCount(_space); }
		///	指定された1ピクセル・1チャネルにおける値を取得します。
		const ValueType& Index(const SizeType& x, const SizeType& y, const SizeType& ch) const
		{
			if (_x <= x) throw new std::out_of_range("x が画像エリアの範囲外です。");
			if (_y <= y) throw new std::out_of_range("y が画像エリアの範囲外です。");
			if (GetChannelCount() <= ch) throw new std::out_of_range("ch が画像エリアの範囲外です。");
			return _data[(y*_x + x)*GetChannelCount() + ch];
		}
		///	指定された1ピクセル・1チャネルにおける値を取得します。
		const ValueType& Index(const Point& pos, const SizeType& ch) const { return Index(pos.getX(), pos.getY(), ch); }
		///	指定された1ピクセル・1チャネルにおける値を取得します。
		ValueType& Index(const SizeType& x, const SizeType& y, const SizeType& ch)
		{
			if (_x <= x) throw new std::out_of_range("x が画像エリアの範囲外です。");
			if (_y <= y) throw new std::out_of_range("y が画像エリアの範囲外です。");
			if (GetChannelCount() <= ch) throw new std::out_of_range("ch が画像エリアの範囲外です。");
			return _data[(y*_x + x)*GetChannelCount() + ch];
		}
		///	指定された1ピクセル・1チャネルにおける値を取得します。
		ValueType& Index(const Point& pos, const SizeType& ch) { return Index(pos.getX(), pos.getY(), ch); }
		///	このオブジェクトを指定された型の @a BitmapBuffer に変換します。
		template<class destT>
		BitmapBuffer<destT> ConvertTo() const
		{
			auto result = BitmapBuffer<destT>(_x, _y, _space);
			auto srcpx = cbegin();
			auto srcend = cend();
			auto destpx = result.begin();
			auto destend = result.end();
			while ((destpx != destend)&&(srcpx != srcend))
			{
				*destpx = ChannelValue<destT>(*srcpx);
				++destpx;
				++srcpx;
			}
			return result;
		}
	public: // static
		///	異なる型の @a BitmapBufferBase をこの型に変換します。
		template<class FromT>
		static BitmapBuffer<T> ConvertFrom(const BitmapBufferBase<FromT>& from)
		{
			auto result = BitmapBuffer<T>(from.GetHorizonalSize(), from.GetVerticalSize(), from.GetColorSpace());
			auto srcpx = from.cbegin();
			auto srcend = from.cend();
			auto destpx = result.begin();
			auto destend = result.end();
			while ((destpx != destend)&&(srcpx != srcend))
			{
				*destpx = ChannelValue<T>(*srcpx);
				++destpx;
				++srcpx;
			}
			return result;
		}
	private: // internal
		///	各色空間が使用するチャネル数を取得します。
		constexpr static size_t CalcChCount(const BitmapColorSpace& space)
		{
			switch(space)
			{
			case BitmapColorSpace::GrayScale: return 1;
			case BitmapColorSpace::ARGB: return 4;
			case BitmapColorSpace::CMYK: return 4;
			case BitmapColorSpace::AXYZ: return 4;
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
		constexpr static size_t CalcLength(const size_t& x, const size_t& y, const BitmapColorSpace& space) noexcept { return x * y * CalcChCount(space); }
	public: // iterator
		///	このオブジェクトの最初の要素を示すイテレータを取得します。
		Iterator begin() noexcept { return Iterator(*this, 0); }
		///	このオブジェクトの最後の要素を示すイテレータを取得します。
		Iterator end() noexcept { return Iterator(*this, GetHorizonalSize() * GetVerticalSize() * GetChannelCount()); }
		///	このオブジェクトの最初の要素を示す変更できないイテレータを取得します。
		ConstIterator cbegin() const noexcept { return ConstIterator(*this, 0); }
		///	このオブジェクトの最後の要素を示す変更できないイテレータを取得します。
		ConstIterator cend() const noexcept { return ConstIterator(*this, GetHorizonalSize() * GetVerticalSize() * GetChannelCount()); }
		///	このオブジェクトの最初の要素を示す逆イテレータを取得します。
		ReverceIterator rbegin() noexcept { return ReverceIterator(*this, GetHorizonalSize() * GetVerticalSize() * GetChannelCount()); }
		///	このオブジェクトの最後の要素を示す逆イテレータを取得します。
		ReverceIterator rend() noexcept { return ReverceIterator(*this, 0); }
		///	このオブジェクトの最初の要素を示す変更できない逆イテレータを取得します。
		ConstReverceIterator crbegin() const noexcept { return ConstReverceIterator(*this, GetHorizonalSize() * GetVerticalSize() * GetChannelCount()); }
		///	このオブジェクトの最後の要素を示す変更できない逆イテレータを取得します。
		ConstReverceIterator crend() const noexcept { return ConstReverceIterator(*this, 0); }
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
#endif // __stationaryorbit_graphics_core_bitmapbuffer__