#ifndef __stationaryorbit_graphics_core_graybitmapimage__
#define __stationaryorbit_graphics_core_graybitmapimage__
#include <type_traits>
#include <limits>
#include <memory>
#include "stationaryorbit/core/numeral"
#include "stationaryorbit/core/property"
#include "fundamental.hpp"
#include "graycolor.hpp"
#include "image.hpp"
#include "bitmap.hpp"
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
	private: // internal
		static GrayColor getIndex(const GrayBitmapImageBase<channelT>& inst, const DisplayPoint& position)
		{
			auto px = inst.BitmapBase<channelT>::Index(position);
			if constexpr (std::is_floating_point_v<channelT>) { return GrayColor(px[0]); }
			if constexpr (std::is_integral_v<channelT>) { return GrayColor(float(px[0]) / std::numeric_limits<channelT>::max()); }
		}
		static void setIndex(GrayBitmapImageBase<channelT>& inst, const DisplayPoint& position, const GrayColor& value)
		{
			auto px = inst.BitmapBase<channelT>::Index(position);
			if constexpr (std::is_floating_point_v<channelT>)
			{
				px[0] = value.Luminance();
				return;
			}
			if constexpr (std::is_integral_v<channelT>)
			{
				px[0] = channelT(value.Luminance() * std::numeric_limits<channelT>::max());
				return;
			}
		}
	};

	typedef GrayBitmapImageBase<uint8_t> GrayBitmapImage;
	typedef GrayBitmapImageBase<float> GrayBitmapImageF;
}
#endif // __stationaryorbit_graphics_core_graybitmapimage__