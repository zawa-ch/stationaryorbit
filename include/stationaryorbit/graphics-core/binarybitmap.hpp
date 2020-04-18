#ifndef __stationaryorbit_graphics_core_binarybitmap__
#define __stationaryorbit_graphics_core_binarybitmap__
#include "stationaryorbit/core/property"
#include "fundamental.hpp"
#include "bitmap.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	class BinaryBitmap
		: public BitmapBase<bool>
	{
	public: // constants
		static constexpr int Channel = 1;
	public: // constructor
		BinaryBitmap() = default;
		explicit BinaryBitmap(const RectangleSize& size);
		BinaryBitmap(const int& width, const int& height);
		template<class fromCh>
		BinaryBitmap(const BitmapBase<fromCh>& from, const std::function<bool(const typename BitmapBase<fromCh>::ConstRefType&)>& predecate) : BitmapBase<bool>(from.Size(), Channel)
		{
			for (auto y : YRange()) for (auto x : XRange()) { Index(x, y) = ChannelValue<bool>(predecate(from.Index(x, y))); }
		}
	private: // constructor
		explicit BinaryBitmap(const BitmapBase<bool>& data);
		explicit BinaryBitmap(BitmapBase<bool>&& data);
	public: // copy/move/destruct
		virtual ~BinaryBitmap() = default;
	public: // member
		Property<BinaryBitmap, ChannelValue<bool>> Index(const DisplayPoint& position);
		Property<BinaryBitmap, ChannelValue<bool>> Index(const int& x, const int& y);
		Property<BinaryBitmap, ChannelValue<bool>> operator[](const DisplayPoint& position);
		ReadOnlyProperty<BinaryBitmap, ChannelValue<bool>> Index(const DisplayPoint& position) const;
		ReadOnlyProperty<BinaryBitmap, ChannelValue<bool>> Index(const int& x, const int& y) const;
		ReadOnlyProperty<BinaryBitmap, ChannelValue<bool>> operator[](const DisplayPoint& position) const;
		static BinaryBitmap ReinterpretFrom(const BitmapBase<bool>& data);
		static BinaryBitmap ReinterpretFrom(BitmapBase<bool>&& data);
	private: // internal
		static ChannelValue<bool> getIndex(const BinaryBitmap& inst, const DisplayPoint& position);
		static void setIndex(BinaryBitmap& inst, const DisplayPoint& position, const ChannelValue<bool>& value);
	};
}
#endif // __stationaryorbit_graphics_core_binarybitmap__