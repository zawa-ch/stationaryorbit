#ifndef __stationaryorbit_graphics_core_bitmapconverter__
#define __stationaryorbit_graphics_core_bitmapconverter__
#include <functional>
#include "stationaryorbit/exception/soexcept"
#include "stationaryorbit/core/numeral"
#include "fundamental.hpp"
#include "bitmap.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{

	template<class channelT>
	class BitmapConverter final
	{
	public:
		typedef channelT ChannelType;
		typedef BitmapBase<channelT> ContainerType;
		typedef std::function<ChannelType(const ContainerType& bitmap, const DisplayPointF& position, const size_t& ch)> ComplementMethod;
	private:
		BitmapConverter() = delete;
		~BitmapConverter() = delete;
	public:
		///	指定された @a bitmap の上下を入れ替えます。
		static ContainerType FripVertical(const ContainerType& bitmap)
		{
			auto result = ContainerType(bitmap.Size(), bitmap.Channels());
			auto range = bitmap.YRange();
			auto src = range.rbegin();
			auto dst = range.begin();
			auto srcend = range.rend();
			auto dstend = range.end();
			while ((src != srcend)&&(dst != dstend))
			{
				for (auto x : bitmap.XRange()) { result.Index(x, *dst).AssignAt(bitmap.Index(x, *src)); }
				++src;
				++dst;
			}
			return result;
		}
		///	指定された @a bitmap の左右を入れ替えます。
		static ContainerType FripHorizonal(const ContainerType& bitmap)
		{
			auto result = ContainerType(bitmap.Size(), bitmap.Channels());
			auto range = bitmap.XRange();
			auto src = range.rbegin();
			auto dst = range.begin();
			auto srcend = range.rend();
			auto dstend = range.end();
			while ((src != srcend)&&(dst != dstend))
			{
				for (auto y : bitmap.YRange()) { result.Index(*dst, y).AssignAt(bitmap.Index(*src, y)); }
				++src;
				++dst;
			}
			return result;
		}
		///	指定された @a bitmap 拡大・縮小します。
		static ContainerType Resize(const ContainerType& bitmap, const RectangleSize& size, ComplementMethod complement)
		{
			if (complement == nullptr) { throw NullReferenceException("引数 complement にnullを指定することはできません。"); }
			auto srcsize = bitmap.Size();
			auto scalefactor = RectangleSizeF(srcsize - RectangleSize(1, 1)) / RectangleSizeF(size - RectangleSize(1, 1));
			auto result = ContainerType(size, bitmap.Channels());
			auto yrange = size.YRange();
			auto xrange = size.XRange();
			auto chrange = Range(0, bitmap.Channels());
			for (auto y : yrange) for (auto x : xrange)
			{
				auto dstpos = DisplayPointF(scalefactor) * DisplayPointF(x, y);
				for (auto ch : chrange) { result.Index(x, y)[ch] = complement(bitmap, dstpos, ch); }
			}
			return result;
		}
		///	ニアレストネイバー補完。
		static ChannelType Nearest(const ChannelType& bitmap, const DisplayPointF& position, const size_t& ch)
		{
			auto dst = position.Round();
			return bitmap.Index(dst)[ch];
		}
		///	バイリニア補完。
		static ChannelType Bilinear(const ContainerType& bitmap, const DisplayPointF& position, const size_t& ch)
		{
			auto pxi = DisplayRectangle(position.Floor(), RectangleSize(1, 1));
			auto pxupleft = bitmap.Index(pxi.Left(), pxi.Top())[ch];
			auto pxupright = bitmap.Index(pxi.Right(), pxi.Top())[ch];
			auto pxdownleft = bitmap.Index(pxi.Left(), pxi.Bottom())[ch];
			auto pxdownright = bitmap.Index(pxi.Right(), pxi.Bottom())[ch];
			auto pxd = position.Extract();
			auto pxup = pxupleft * ChannelType(channelT(ChannelType::Max() * (1 - pxd.X()))) + pxupright * ChannelType(channelT(ChannelType::Max() * (pxd.X())));
			auto pxdown = pxdownleft * ChannelType(channelT(ChannelType::Max() * (1 - pxd.X()))) + pxdownright * ChannelType(channelT(ChannelType::Max() * (pxd.X())));
			return pxup * ChannelType(channelT(ChannelType::Max() * (1 - pxd.Y()))) + pxdown * ChannelType(channelT(ChannelType::Max() * (pxd.Y())));
		}
		///	指定された @a bitmap を @a area で指定された範囲で切り抜きます。
		static ContainerType Crop(const ContainerType& bitmap, const DisplayRectangle& area)
		{
			if ((area.Left() < 0)||(area.Bottom() < 0)||(bitmap.Size().Width() <= area.Right()) || (bitmap.Size().Height() <= area.Top())) { throw std::invalid_argument("area で指定している範囲がビットマップの範囲を超えています。"); }
			auto yrange = Range(0, area.Size().Height());
			auto xrange = Range(0, area.Size().Width());
			auto chrange = Range(0, bitmap.Channels());
			auto result = ContainerType(area.Size(), bitmap.Channels());
			for (auto y : yrange) for (auto x : xrange)
			{
				auto dstpos = area.Location() + DisplayPoint(x, y);
				for (auto ch : chrange) { result.Index(x, y)[ch] = bitmap.Index(x, y)[ch]; }
			}
			return result;
		}

	};

}
#endif // __stationaryorbit_graphics_core_bitmapconverter__