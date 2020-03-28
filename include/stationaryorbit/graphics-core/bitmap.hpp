#ifndef __stationaryorbit_graphics_core_bitmap__
#define __stationaryorbit_graphics_core_bitmap__
#include <type_traits>
#include <vector>
#include "stationaryorbit/exception/soexcept"
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
		static_assert(std::is_arithmetic_v<Tp>, "テンプレート引数 Tp は数値型である必要があります。");
		friend class BitmapBase<Tp>;
	protected: // contains
		const Tp* _ref;
		const int _ch;
	protected: // construct
		BitmapConstPixelRef(const Tp* ref, const int& ch) : _ref(ref), _ch(ch) {}
	public: // copy/move/destruct
		virtual ~BitmapConstPixelRef() = default;
	public: // member
		const Tp& Index(const int& ch) const { if ((ch < 0)||(_ch <= ch)) { throw std::out_of_range("指定されたインデックスは境界を超えています。"); } return _ref[ch]; }
		const Tp& operator[](const size_t& index) const { return Index(index); }
		int Count() const { return _ch; }
	};
	template<class Tp>
	class BitmapPixelRef
		: public BitmapConstPixelRef<Tp>
	{
		static_assert(std::is_arithmetic_v<Tp>, "テンプレート引数 Tp は数値型である必要があります。");
		friend class BitmapBase<Tp>;
	private: // contains
		Tp* _ref;
	private: // construct
		BitmapPixelRef(Tp* ref, const int& ch) : BitmapConstPixelRef<Tp>(ref, ch), _ref(ref) {}
	public: // copy/move/destruct
		virtual ~BitmapPixelRef() = default;
	public: // member
		Tp& Index(const int& ch) { if ((ch < 0)||(this->Count() <= ch)) { throw std::out_of_range("指定されたインデックスは境界を超えています。"); } return _ref[ch]; }
		Tp& operator[](const size_t& index) { return Index(index); }
		void AssignAt(const BitmapConstPixelRef<Tp>& ref)
		{
			if (this->Count() != ref.Count()) { throw InvalidOperationException("チャネル数が異なるオブジェクトに対してこのメソッドを呼び出すことはできません。"); }
			for (auto ch : Range(0, this->Count())) { Index(ch) = ref.Index(ch); }
		}
	};
	template<class Tp>
	class BitmapBase
		: public Image
	{
		static_assert(std::is_arithmetic_v<Tp>, "テンプレート引数 Tp は数値型である必要があります。");
	public:
		typedef Tp ValueType;
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
	public: // copy/move/destruct
		virtual ~BitmapBase() = default;
	public: // member
		int Channels() const { return _ch; }
		Range<int> XRange() const { return _size.XRange(); }
		Range<int> YRange() const { return _size.YRange(); }
		ConstRefType Index(const DisplayPoint& position) const { return ConstRefType(_data.data() + SolveIndex(position), _ch); }
		ConstRefType operator[](const DisplayPoint& index) const { return Index(index); }
		ConstRefType Index(const int& x, const int& y) const { return Index(DisplayPoint(x, y)); }
		RefType Index(const DisplayPoint& position) { return RefType(_data.data() + SolveIndex(position), _ch); }
		RefType operator[](const DisplayPoint& index) { return Index(index); }
		RefType Index(const int& x, const int& y) { return Index(DisplayPoint(x, y)); }
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