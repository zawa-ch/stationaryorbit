#ifndef __stationaryorbit_graphics_core_bitmap__
#define __stationaryorbit_graphics_core_bitmap__
#include <type_traits>
#include <vector>
#include "stationaryorbit/exception.hpp"
#include "channelvalue.hpp"
#include "fundamental.hpp"
#include "image.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	template<class Tp> class BitmapConstPixelRef;
	template<class Tp> class BitmapPixelRef;
	template<class Tp> class BitmapBase;

	template<class Tp>
	class BitmapConstPixelRef
	{
		friend class BitmapBase<Tp>;
	public:
		typedef ChannelValue<Tp> ValueType;
	protected: // contains
		const std::vector<ValueType>& _ref;
		const size_t _bidx;
		const int _ch;
	protected: // construct
		BitmapConstPixelRef(const std::vector<ValueType>& ref, const size_t& index, const int& ch) : _ref(ref), _bidx(index), _ch(ch) {}
	public: // copy/move/destruct
		virtual ~BitmapConstPixelRef() = default;
	public: // member
		const ValueType& Index(const int& ch) const { if ((ch < 0)||(_ch <= ch)) { throw std::out_of_range("指定されたインデックスは境界を超えています。"); } return _ref[_bidx + ch]; }
		const ValueType& operator[](const size_t& index) const { return Index(index); }
		int Count() const { return _ch; }
	};
	template<class Tp>
	class BitmapPixelRef
		: public BitmapConstPixelRef<Tp>
	{
		friend class BitmapBase<Tp>;
	public:
		typedef ChannelValue<Tp> ValueType;
	private: // contains
		std::vector<ValueType>& _ref;
	private: // construct
		BitmapPixelRef(std::vector<ValueType>& ref, const size_t& index, const int& ch) : BitmapConstPixelRef<Tp>(ref, index, ch), _ref(ref) {}
	public: // copy/move/destruct
		virtual ~BitmapPixelRef() = default;
	public: // member
		ValueType& Index(const int& ch) { if ((ch < 0)||(BitmapConstPixelRef<Tp>::_ch <= ch)) { throw std::out_of_range("指定されたインデックスは境界を超えています。"); } return _ref[BitmapConstPixelRef<Tp>::_bidx + ch]; }
		ValueType& operator[](const size_t& index) { return Index(index); }
		void AssignAt(const BitmapConstPixelRef<Tp>& ref)
		{
			if (this->Count() != ref.Count()) { throw InvalidOperationException("チャネル数が異なるオブジェクトに対してこのメソッドを呼び出すことはできません。"); }
			for (auto ch : Range(0, this->Count())) { Index(ch) = ref.Index(ch); }
		}
		template<class fromT>
		void AssignAt(const BitmapConstPixelRef<fromT>& ref)
		{
			if (this->Count() != ref.Count()) { throw InvalidOperationException("チャネル数が異なるオブジェクトに対してこのメソッドを呼び出すことはできません。"); }
			for (auto ch : Range(0, this->Count())) { Index(ch) = ValueType(ref.Index(ch)); }
		}
	};
	template<class Tp>
	class BitmapBase
		: public Image
	{
	public:
		typedef ChannelValue<Tp> ValueType;
		typedef BitmapConstPixelRef<Tp> ConstRefType;
		typedef BitmapPixelRef<Tp> RefType;
	private: // contains
		std::vector<ValueType> _data;
		RectangleSize _size;
		int _ch;
	private: // internal
		size_t SolveIndex(const DisplayPoint& position) const
		{
			if ((position.X() < 0)||(position.Y() < 0)) { throw std::invalid_argument("position の要素のいずれかが負です。"); }
			if ((_size.Width() <= position.X())||(_size.Height() <= position.Y())) { throw std::out_of_range("指定されたインデックスは境界を超えています。"); }
			return ((position.Y() * _size.Width()) + position.X()) * _ch;
		}
		static size_t SolveCount(const RectangleSize& size)
		{
			if ((0 <= size.Height())&&(0 <= size.Width())) { return size.Width() * size.Height(); }
			else { throw std::invalid_argument("size の要素のいずれかが負です。"); }
		}
		static size_t SolveCount(const RectangleSize& size, const int& channel)
		{
			if ((0 <= size.Height())&&(0 <= size.Width())&&(0 <= channel)) { return size.Width() * size.Height() * channel; }
			else { throw std::invalid_argument("size 、または channel の要素のいずれかが負です。"); }
		}
	public: // construct
		BitmapBase() : _data(), _size(RectangleSize::Empty()), _ch() {}
		BitmapBase(const RectangleSize& size, const int& channel) : _data(SolveCount(size, channel)), _size(size), _ch(channel) {}
		BitmapBase(const int& width, const int& height, const int& channel) : BitmapBase(RectangleSize(width, height), channel) {}
		template<class fromT>
		explicit BitmapBase(const BitmapBase<fromT>& from) : BitmapBase<Tp>(from.Size(), from.Channels())
		{
			for (auto y : YRange()) for (auto x : XRange()) { Index(x, y).AssignAt(from.Index(x, y)); }
		}
	public: // copy/move/destruct
		virtual ~BitmapBase() = default;
	public: // member
		int Channels() const { return _ch; }
		Range<int> XRange() const { return _size.XRange(); }
		Range<int> YRange() const { return _size.YRange(); }
		DisplayRectangle Region() const { return DisplayRectangle(DisplayPoint(0, 0), _size); }
		ConstRefType Index(const DisplayPoint& position) const { return ConstRefType(_data, SolveIndex(position), _ch); }
		ConstRefType operator[](const DisplayPoint& index) const { return Index(index); }
		ConstRefType Index(const int& x, const int& y) const { return Index(DisplayPoint(x, y)); }
		RefType Index(const DisplayPoint& position) { return RefType(_data, SolveIndex(position), _ch); }
		RefType operator[](const DisplayPoint& index) { return Index(index); }
		RefType Index(const int& x, const int& y) { return Index(DisplayPoint(x, y)); }
		void Copy(BitmapBase<Tp>& destbmp, const DisplayPoint& srclocation, const DisplayPoint& destlocation, const RectangleSize& areasize) const
		{
			if (!Region().Contains(DisplayRectangle(srclocation, areasize))) { throw std::invalid_argument("指定された srclocation と areasize の組み合わせはビットマップ領域を超えています。"); }
			if (!destbmp.Region().Contains(DisplayRectangle(destlocation, areasize))) { throw std::invalid_argument("指定された destlocation と areasize の組み合わせは destbmp のビットマップ領域を超えています。"); }
			for (auto y : areasize.YRange()) for (auto x : areasize.XRange())
			{
				auto src = DisplayPoint(x, y) + srclocation;
				auto dest = DisplayPoint(x, y) + destlocation;
				destbmp[dest].AssignAt(Index(src));
			}
		}
		void Copy(BitmapBase<Tp>& destbmp, const DisplayPoint& destlocation) const { Copy(destbmp, DisplayPoint(0, 0), destlocation, _size); }
		void Copy(BitmapBase<Tp>& destbmp) const { Copy(destbmp, DisplayPoint(0, 0), DisplayPoint(0, 0), _size); }
	public: // implement Image
		RectangleSize Size() const { return _size; }
	};

	typedef BitmapBase<uint8_t> Bitmap8;
	typedef BitmapBase<uint16_t> Bitmap16;
	typedef BitmapBase<uint32_t> Bitmap32;
	typedef BitmapBase<float> BitmapF32;
	typedef BitmapBase<double> BitmapF64;
}
#endif // __stationaryorbit_graphics_core_bitmap__