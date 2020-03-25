#ifndef __stationaryorbit_graphics_core_rgbbitmapimage__
#define __stationaryorbit_graphics_core_rgbbitmapimage__
#include <type_traits>
#include <limits>
#include <memory>
#include "stationaryorbit/core/numeral"
#include "stationaryorbit/core/property"
#include "fundamental.hpp"
#include "rgbcolor.hpp"
#include "image.hpp"
#include "bitmap.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{
	template<class channelT> class RGBBitmapImageBase;
	template<class channelT> class ARGBBitmapImageBase;

	template<class channelT>
	class RGBBitmapImageBase
		: public BitmapBase<channelT>
	{
		static_assert(std::is_arithmetic_v<channelT>, "テンプレート引数 channelT は数値型である必要があります。");
	public: // constants
		static constexpr int Channel = 3;
	public: // constructor
		RGBBitmapImageBase() = default;
		explicit RGBBitmapImageBase(const RectangleSize& size) : BitmapBase<channelT>(size, Channel) {}
		RGBBitmapImageBase(const int& width, const int& height) : BitmapBase<channelT>(RectangleSize(width, height), Channel) {}
		explicit RGBBitmapImageBase(const BitmapBase<channelT>& data) : BitmapBase<channelT>(data) { if (data.Channels() != Channel) { throw std::invalid_argument("指定された data のチャネル数はこのクラスではサポートされていません。"); } }
		explicit RGBBitmapImageBase(BitmapBase<channelT>&& data) : BitmapBase<channelT>(data) { if (data.Channels() != Channel) { throw std::invalid_argument("指定された data のチャネル数はこのクラスではサポートされていません。"); } }
	public: // copy/move/destruct
		virtual ~RGBBitmapImageBase() = default;
	public: // member
		Property<RGBBitmapImageBase<channelT>, RGBColor> Index(const DisplayPoint& position) { return Property<RGBBitmapImageBase<channelT>, RGBColor>(*this, std::bind(getIndex, std::placeholders::_1, position), std::bind(setIndex, std::placeholders::_1, position, std::placeholders::_2)); }
		Property<RGBBitmapImageBase<channelT>, RGBColor> Index(const int& x, const int& y) { return Index(DisplayPoint(x, y)); }
		Property<RGBBitmapImageBase<channelT>, RGBColor> operator[](const DisplayPoint& position) { return Index(position); }
		ReadOnlyProperty<RGBBitmapImageBase<channelT>, RGBColor> Index(const DisplayPoint& position) const { return ReadOnlyProperty<RGBBitmapImageBase<channelT>, RGBColor>(*this, std::bind(getIndex, std::placeholders::_1, position)); }
		ReadOnlyProperty<RGBBitmapImageBase<channelT>, RGBColor> Index(const int& x, const int& y) const { return Index(DisplayPoint(x, y)); }
		ReadOnlyProperty<RGBBitmapImageBase<channelT>, RGBColor> operator[](const DisplayPoint& position) const { return Index(position); }
	private: // internal
		static RGBColor getIndex(const RGBBitmapImageBase<channelT>& inst, const DisplayPoint& position)
		{
			auto px = inst.BitmapBase<channelT>::Index(position);
			if constexpr (std::is_floating_point_v<channelT>) { return RGBColor(px[0], px[1], px[2]); }
			if constexpr (std::is_integral_v<channelT>) { return RGBColor(float(px[0]) / std::numeric_limits<channelT>::max(), float(px[1] / std::numeric_limits<channelT>::max()), float(px[2] / std::numeric_limits<channelT>::max())); }
		}
		static void setIndex(RGBBitmapImageBase<channelT>& inst, const DisplayPoint& position, const RGBColor& value)
		{
			auto px = inst.BitmapBase<channelT>::Index(position);
			if constexpr (std::is_floating_point_v<channelT>)
			{
				px[0] = value.R();
				px[1] = value.G();
				px[2] = value.B();
				return;
			}
			if constexpr (std::is_integral_v<channelT>)
			{
				px[0] = channelT(value.R() / std::numeric_limits<channelT>::max());
				px[1] = channelT(value.G() / std::numeric_limits<channelT>::max());
				px[2] = channelT(value.B() / std::numeric_limits<channelT>::max());
				return;
			}
		}
	};

	template<class channelT>
	class ARGBBitmapImageBase
		: public BitmapBase<channelT>
	{
		static_assert(std::is_arithmetic_v<channelT>, "テンプレート引数 channelT は数値型である必要があります。");
	public: // constants
		static constexpr int Channel = 4;
	public: // constructor
		ARGBBitmapImageBase() = default;
		explicit ARGBBitmapImageBase(const RectangleSize& size) : BitmapBase<channelT>(size, Channel) {}
		ARGBBitmapImageBase(const int& width, const int& height) : BitmapBase<channelT>(RectangleSize(width, height), Channel) {}
		explicit ARGBBitmapImageBase(const BitmapBase<channelT>& data) : BitmapBase<channelT>(data) { if (data.Channels() != Channel) { throw std::invalid_argument("指定された data のチャネル数はこのクラスではサポートされていません。"); } }
		explicit ARGBBitmapImageBase(BitmapBase<channelT>&& data) : BitmapBase<channelT>(data) { if (data.Channels() != Channel) { throw std::invalid_argument("指定された data のチャネル数はこのクラスではサポートされていません。"); } }
	public: // copy/move/destruct
		virtual ~ARGBBitmapImageBase() = default;
	public: // member
		Property<ARGBBitmapImageBase<channelT>, ARGBColor> Index(const DisplayPoint& position) { return Property<ARGBBitmapImageBase<channelT>, ARGBColor>(*this, std::bind(getIndex, std::placeholders::_1, position), std::bind(setIndex, std::placeholders::_1, position, std::placeholders::_2)); }
		Property<ARGBBitmapImageBase<channelT>, ARGBColor> Index(const int& x, const int& y) { return Index(DisplayPoint(x, y)); }
		Property<ARGBBitmapImageBase<channelT>, ARGBColor> operator[](const DisplayPoint& position) { return Index(position); }
		ReadOnlyProperty<ARGBBitmapImageBase<channelT>, ARGBColor> Index(const DisplayPoint& position) const { return ReadOnlyProperty<ARGBBitmapImageBase<channelT>, ARGBColor>(*this, std::bind(getIndex, std::placeholders::_1, position)); }
		ReadOnlyProperty<ARGBBitmapImageBase<channelT>, ARGBColor> Index(const int& x, const int& y) const { return Index(DisplayPoint(x, y)); }
		ReadOnlyProperty<ARGBBitmapImageBase<channelT>, ARGBColor> operator[](const DisplayPoint& position) const { return Index(position); }
	private: // internal
		static ARGBColor getIndex(const ARGBBitmapImageBase<channelT>& inst, const DisplayPoint& position)
		{
			auto px = inst.BitmapBase<channelT>::Index(position);
			if constexpr (std::is_floating_point_v<channelT>) { return ARGBColor(px[0], px[1], px[2], px[3]); }
			if constexpr (std::is_integral_v<channelT>) { return ARGBColor(float(px[0]) / std::numeric_limits<channelT>::max(), float(px[1] / std::numeric_limits<channelT>::max()), float(px[2] / std::numeric_limits<channelT>::max()), float(px[3] / std::numeric_limits<channelT>::max())); }
		}
		static void setIndex(ARGBBitmapImageBase<channelT>& inst, const DisplayPoint& position, const ARGBColor& value)
		{
			auto px = inst.BitmapBase<channelT>::Index(position);
			if constexpr (std::is_floating_point_v<channelT>)
			{
				px[0] = value.R();
				px[1] = value.G();
				px[2] = value.B();
				px[3] = value.Alpha();
				return;
			}
			if constexpr (std::is_integral_v<channelT>)
			{
				px[0] = channelT(value.R() / std::numeric_limits<channelT>::max());
				px[1] = channelT(value.G() / std::numeric_limits<channelT>::max());
				px[2] = channelT(value.B() / std::numeric_limits<channelT>::max());
				px[3] = channelT(value.Alpha() / std::numeric_limits<channelT>::max());
				return;
			}
		}
	};

	typedef RGBBitmapImageBase<uint8_t> RGBBitmapImage;
	typedef RGBBitmapImageBase<float> RGBBitmapImageF;
	typedef ARGBBitmapImageBase<uint8_t> ARGBBitmapImage;
	typedef ARGBBitmapImageBase<float> ARGBBitmapImageF;
}
#endif // __stationaryorbit_graphics_core_rgbbitmapimage__