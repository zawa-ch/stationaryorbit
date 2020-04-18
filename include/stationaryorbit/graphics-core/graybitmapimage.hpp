#ifndef __stationaryorbit_graphics_core_graybitmapimage__
#define __stationaryorbit_graphics_core_graybitmapimage__
#include <type_traits>
#include <memory>
#include "stationaryorbit/core/numeral"
#include "stationaryorbit/core/property"
#include "fundamental.hpp"
#include "graycolor.hpp"
#include "bitmap.hpp"
#include "binarybitmap.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	template<class channelT> class GrayBitmapImageBase;

	template<class channelT>
	class GrayBitmapImageBase
		: public BitmapBase<channelT>
	{
		static_assert(std::is_arithmetic_v<channelT>, "テンプレート引数 channelT は数値型である必要があります。");
	public: // constants
		static constexpr int Channel = 1;
	public: // constructor
		GrayBitmapImageBase() = default;
		explicit GrayBitmapImageBase(const RectangleSize& size) : BitmapBase<channelT>(size, Channel) {}
		GrayBitmapImageBase(const int& width, const int& height) : BitmapBase<channelT>(RectangleSize(width, height), Channel) {}
		explicit GrayBitmapImageBase(const BitmapBase<channelT>& data) : BitmapBase<channelT>(data) { if (data.Channels() != Channel) { throw std::invalid_argument("指定された data のチャネル数はこのクラスではサポートされていません。"); } }
		explicit GrayBitmapImageBase(BitmapBase<channelT>&& data) : BitmapBase<channelT>(data) { if (data.Channels() != Channel) { throw std::invalid_argument("指定された data のチャネル数はこのクラスではサポートされていません。"); } }
	public: // copy/move/destruct
		virtual ~GrayBitmapImageBase() = default;
	public: // member
		Property<GrayBitmapImageBase<channelT>, GrayColor> Index(const DisplayPoint& position) { return Property<GrayBitmapImageBase<channelT>, GrayColor>(*this, std::bind(getIndex, std::placeholders::_1, position), std::bind(setIndex, std::placeholders::_1, position, std::placeholders::_2)); }
		Property<GrayBitmapImageBase<channelT>, GrayColor> Index(const int& x, const int& y) { return Index(DisplayPoint(x, y)); }
		Property<GrayBitmapImageBase<channelT>, GrayColor> operator[](const DisplayPoint& position) { return Index(position); }
		ReadOnlyProperty<GrayBitmapImageBase<channelT>, GrayColor> Index(const DisplayPoint& position) const { return ReadOnlyProperty<GrayBitmapImageBase<channelT>, GrayColor>(*this, std::bind(getIndex, std::placeholders::_1, position)); }
		ReadOnlyProperty<GrayBitmapImageBase<channelT>, GrayColor> Index(const int& x, const int& y) const { return Index(DisplayPoint(x, y)); }
		ReadOnlyProperty<GrayBitmapImageBase<channelT>, GrayColor> operator[](const DisplayPoint& position) const { return Index(position); }
		///	このビットマップを指定された述語に従って二値化します。
		BinaryBitmap Binalize(const std::function<bool(const GrayColor&)>& predicate)
		{
			auto result = BinaryBitmap(BitmapBase<channelT>::Size());
			for (auto y : BitmapBase<channelT>::YRange()) for (auto x : BitmapBase<channelT>::XRange())
			{
				result.Index(x, y) = ChannelValue<bool>(predicate(Index(x, y).get()));
			}
			return result;
		}
	private: // internal
		static GrayColor getIndex(const GrayBitmapImageBase<channelT>& inst, const DisplayPoint& position)
		{
			auto px = inst.BitmapBase<channelT>::Index(position);
			return GrayColor(ChannelValue<float>(px[0]));
		}
		static void setIndex(GrayBitmapImageBase<channelT>& inst, const DisplayPoint& position, const GrayColor& value)
		{
			auto px = inst.BitmapBase<channelT>::Index(position);
			px[0] = ChannelValue<float>(value.Luminance()).ConvertTo<channelT>();
		}
	};

	typedef GrayBitmapImageBase<uint8_t> GrayBitmapImage;
	typedef GrayBitmapImageBase<float> GrayBitmapImageF;
}
#endif // __stationaryorbit_graphics_core_graybitmapimage__