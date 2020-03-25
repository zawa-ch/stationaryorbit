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

	template<class channelT>
	class RGBBitmapImageBase
		: public Image
	{
		static_assert(std::is_arithmetic_v<channelT>, "テンプレート引数 channelT は数値型である必要があります。");
	public: // types
		typedef BitmapBase<channelT> DataType;
	private: // constains
		DataType _data;
	public: // constants
		static constexpr int Channel = 3;
	public: // constructor
		RGBBitmapImageBase() = default;
		explicit RGBBitmapImageBase(const RectangleSize& size) : _data(size, Channel) {}
		RGBBitmapImageBase(const int& width, const int& height) : _data(RectangleSize(width, height), Channel) {}
		explicit RGBBitmapImageBase(const DataType& data) : _data(data) { if (data.Channels() != Channel) { throw std::invalid_argument("指定された data のチャネル数はこのクラスではサポートされていません。"); } }
	public: // copy/move/destruct
		virtual ~RGBBitmapImageBase() = default;
	public: // member
		const DataType& Data() const { return _data; }
		RectangleSize Size() const { return _data.Size(); }
		Range<int> XRange() const { return _data.XRange(); }
		Range<int> YRange() const { return _data.YRange(); }
		Property<RGBBitmapImageBase<channelT>, RGBColor> Index(const DisplayPoint& position) { return Property<RGBBitmapImageBase<channelT>, RGBColor>(*this, std::bind(getIndex, std::placeholders::_1, position), std::bind(setIndex, std::placeholders::_1, position, std::placeholders::_2)); }
		Property<RGBBitmapImageBase<channelT>, RGBColor> Index(const int& x, const int& y) { return Index(DisplayPoint(x, y)); }
		Property<RGBBitmapImageBase<channelT>, RGBColor> operator[](const DisplayPoint& position) { return Index(position); }
		ReadOnlyProperty<RGBBitmapImageBase<channelT>, RGBColor> Index(const DisplayPoint& position) const { return ReadOnlyProperty<RGBBitmapImageBase<channelT>, RGBColor>(*this, std::bind(getIndex, std::placeholders::_1, position)); }
		ReadOnlyProperty<RGBBitmapImageBase<channelT>, RGBColor> Index(const int& x, const int& y) const { return Index(DisplayPoint(x, y)); }
		ReadOnlyProperty<RGBBitmapImageBase<channelT>, RGBColor> operator[](const DisplayPoint& position) const { return Index(position); }
	private: // internal
		static RGBColor getIndex(const RGBBitmapImageBase<channelT>& inst, const DisplayPoint& position)
		{
			auto px = inst._data[position];
			if constexpr (std::is_floating_point_v<channelT>) { return RGBColor(px[0], px[1], px[2]); }
			if constexpr (std::is_integral_v<channelT>) { return RGBColor(float(px[0]) / std::numeric_limits<channelT>::max(), float(px[1] / std::numeric_limits<channelT>::max()), float(px[2] / std::numeric_limits<channelT>::max())); }
		}
		static void setIndex(RGBBitmapImageBase<channelT>& inst, const DisplayPoint& position, const RGBColor& value)
		{
			auto px = inst._data[position];
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

	typedef RGBBitmapImageBase<uint8_t> RGBBitmapImage;
	typedef RGBBitmapImageBase<float> RGBBitmapImageF;
}
#endif // __stationaryorbit_graphics_core_rgbbitmapimage__