#ifndef __stationaryorbit_graphics_core_maskbitmap__
#define __stationaryorbit_graphics_core_maskbitmap__
#include "channelvalue.hpp"
#include "bitmap.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	template<class Tp>
	class MaskBitmapBase
		: public BitmapBase<Tp>
	{
	public: // constants
		static constexpr int Channel = 1;
		MaskBitmapBase() = default;
		explicit MaskBitmapBase(const RectangleSize& size) : BitmapBase<channelT>(size, Channel) {}
		MaskBitmapBase(const int& width, const int& height) : BitmapBase<channelT>(RectangleSize(width, height), Channel) {}
		explicit MaskBitmapBase(const BitmapBase<channelT>& data) : BitmapBase<channelT>(data) {}
		explicit MaskBitmapBase(BitmapBase<channelT>&& data) : BitmapBase<channelT>(data) {}
	public: // copy/move/destruct
		virtual ~MaskBitmapBase() = default;
	public: // member
		Property<MaskBitmapBase<channelT>, ChannelValue<Tp>> Index(const DisplayPoint& position) { return Property<MaskBitmapBase<channelT>, ChannelValue<Tp>>(*this, std::bind(getIndex, std::placeholders::_1, position), std::bind(setIndex, std::placeholders::_1, position, std::placeholders::_2)); }
		Property<MaskBitmapBase<channelT>, ChannelValue<Tp>> Index(const int& x, const int& y) { return Index(DisplayPoint(x, y)); }
		Property<MaskBitmapBase<channelT>, ChannelValue<Tp>> operator[](const DisplayPoint& position) { return Index(position); }
		ReadOnlyProperty<MaskBitmapBase<channelT>, ChannelValue<Tp>> Index(const DisplayPoint& position) const { return ReadOnlyProperty<MaskBitmapBase<channelT>, ChannelValue<Tp>>(*this, std::bind(getIndex, std::placeholders::_1, position)); }
		ReadOnlyProperty<MaskBitmapBase<channelT>, ChannelValue<Tp>> Index(const int& x, const int& y) const { return Index(DisplayPoint(x, y)); }
		ReadOnlyProperty<MaskBitmapBase<channelT>, ChannelValue<Tp>> operator[](const DisplayPoint& position) const { return Index(position); }
		///	このビットマップを指定された述語に従って二値化します。
		BinaryBitmap Binalize(const std::function<bool(const ChannelValue<Tp>&)>& predicate)
		{
			auto result = BinaryBitmap(BitmapBase<channelT>::Size());
			for (auto y : BitmapBase<channelT>::YRange()) for (auto x : BitmapBase<channelT>::XRange())
			{
				result.Index(x, y) = ChannelValue<bool>(predicate(Index(x, y).get()));
			}
			return result;
		}
		static MaskBitmapBase<channelT> ReinterpretFrom(const BitmapBase<channelT>& data)
		{
			if (data.Channels() != Channel) { throw std::invalid_argument("指定された data のチャネル数はこのクラスではサポートされていません。"); }
			return MaskBitmapBase<channelT>(data, colorspace);
		}
		static MaskBitmapBase<channelT> ReinterpretFrom(BitmapBase<channelT>&& data)
		{
			if (data.Channels() != Channel) { throw std::invalid_argument("指定された data のチャネル数はこのクラスではサポートされていません。"); }
			return MaskBitmapBase<channelT>(data, colorspace);
		}
	private: // internal
		static ChannelValue<Tp> getIndex(const MaskBitmapBase<channelT>& inst, const DisplayPoint& position)
		{
			auto px = inst.BitmapBase<channelT>::Index(position);
			return px[0];
		}
		static void setIndex(MaskBitmapBase<channelT>& inst, const DisplayPoint& position, const ChannelValue<Tp>& value)
		{
			auto px = inst.BitmapBase<channelT>::Index(position);
			px[0] = value;
		}
	};

	typedef MaskBitmapBase<uint8_t> MaskBitmap;
	typedef MaskBitmapBase<float> MaskBitmapF;
}
#endif // __stationaryorbit_graphics_core_maskbitmap__