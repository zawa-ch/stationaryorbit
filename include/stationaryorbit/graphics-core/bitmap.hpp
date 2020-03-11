#ifndef __stationaryorbit_graphics_core_bitmap__
#define __stationaryorbit_graphics_core_bitmap__
#include <cstddef>
#include "channelvalue.hpp"
#include "point.hpp"
#include "rgbcolor.hpp"
#include "pixelreference.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{

	///	ビットマップ画像のデータ構造として用いる色空間を表します。
	enum class BitmapColorSpace
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

	///	ビットマップの基本となるメソッドを実装します。
	class BitmapBase
	{
	public:
		///	このバッファの幅を取得します。
		virtual size_t GetWidth() const = 0;
		///	このバッファの高さを取得します。
		virtual size_t GetHeight() const = 0;
		///	バッファに使用されている色空間を取得します。
		virtual BitmapColorSpace GetColorSpace() const = 0;
		virtual ~BitmapBase() = default;
	};

	///	ビットマップ画像を表す基本クラスです。
	class Bitmap
		: virtual public BitmapBase
	{
	public: // types
		class Iterator;
		class ConstIterator;
		class ReverceIterator;
		class ConstReverceIterator;
	public: // interface
		///	指定されたピクセルの値をRGBで取得します。
		virtual RGBColor GetRGB(const size_t& x, const size_t& y) const = 0;
		///	指定されたピクセルの値をRGBで設定します。
		virtual void SetRGB(const size_t& x, const size_t& y, const RGBColor& value) = 0;
		///	指定されたピクセルの参照を取得します。
		virtual const ConstPixelReference Index(const size_t& x, const size_t& y) const = 0;
		///	指定されたピクセルの参照を取得します。
		virtual const ConstPixelReference Index(const Point& position) const = 0;
		///	指定されたピクセルの参照を取得します。
		virtual PixelReference Index(const size_t& x, const size_t& y) = 0;
		///	指定されたピクセルの参照を取得します。
		virtual PixelReference Index(const Point& position) = 0;
	public: // copy/move/destruct
		virtual ~Bitmap() = default;
	public: // iterators
		class Iterator
		{
		private: // contains
			Bitmap& _container;
			size_t _pos;
		public: // constructor
			Iterator(Bitmap& container, const size_t& position) noexcept;
		public: // member
			PixelReference Current();
			bool Equals(const Iterator& other) const noexcept;
		public: // implement LegacyIterator
			PixelReference operator*();
			Iterator& operator++() noexcept;
		public: // implement LegacyInputIterator
			bool operator==(const Iterator& other) const noexcept;
			bool operator!=(const Iterator& other) const noexcept;
			PixelReference operator->();
		public: // implement LegacyBidirectionalIterator
			Iterator& operator--() noexcept;
		};
		class ConstIterator
		{
		private: // contains
			const Bitmap& _container;
			size_t _pos;
		public: // constructor
			ConstIterator(const Bitmap& container, const size_t& position) noexcept;
		public: // member
			ConstPixelReference Current() const;
			bool Equals(const ConstIterator& other) const noexcept;
		public: // implement LegacyIterator
			ConstPixelReference operator*() const;
			ConstIterator& operator++() noexcept;
		public: // implement LegacyInputIterator
			bool operator==(const ConstIterator& other) const noexcept;
			bool operator!=(const ConstIterator& other) const noexcept;
			ConstPixelReference operator->() const;
		public: // implement LegacyBidirectionalIterator
			ConstIterator& operator--() noexcept;
		};
		class ReverceIterator
		{
		private: // contains
			Bitmap& _container;
			size_t _pos;
		public: // constructor
			ReverceIterator(Bitmap& container, const size_t& position) noexcept;
		public: // member
			PixelReference Current();
			bool Equals(const ReverceIterator& other) const noexcept;
		public: // implement LegacyIterator
			PixelReference operator*();
			ReverceIterator& operator++() noexcept;
		public: // implement LegacyInputIterator
			bool operator==(const ReverceIterator& other) const noexcept;
			bool operator!=(const ReverceIterator& other) const noexcept;
			PixelReference operator->();
		public: // implement LegacyBidirectionalIterator
			ReverceIterator& operator--() noexcept;
		};
		class ConstReverceIterator
		{
		private: // contains
			const Bitmap& _container;
			size_t _pos;
		public: // constructor
			ConstReverceIterator(const Bitmap& container, const size_t& position) noexcept;
		public: // member
			ConstPixelReference Current() const;
			bool Equals(const ConstReverceIterator& other) const noexcept;
		public: // implement LegacyIterator
			ConstPixelReference operator*() const;
			ConstReverceIterator& operator++() noexcept;
		public: // implement LegacyInputIterator
			bool operator==(const ConstReverceIterator& other) const noexcept;
			bool operator!=(const ConstReverceIterator& other) const noexcept;
			ConstPixelReference operator->() const;
		public: // implement LegacyBidirectionalIterator
			ConstReverceIterator& operator--() noexcept;
		};
		Iterator begin() noexcept;
		Iterator end() noexcept;
		ConstIterator cbegin() const noexcept;
		ConstIterator cend() const noexcept;
		ReverceIterator rbegin() noexcept;
		ReverceIterator rend() noexcept;
		ConstReverceIterator crbegin() const noexcept;
		ConstReverceIterator crend() const noexcept;
	};

}
#endif // __stationaryorbit_graphics_core_bitmap__