//	stationaryorbit/graphics-core/bitmapconverter
//	Copyright 2020 zawa-ch.
//	GPLv3 (or later) license
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//	See the GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program.
//	If not, see <http://www.gnu.org/licenses/>.
//
#ifndef __stationaryorbit_graphics_core_bitmapconverter__
#define __stationaryorbit_graphics_core_bitmapconverter__
#include <functional>
#include "stationaryorbit/exception.hpp"
#include "stationaryorbit/core.numeral.hpp"
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
		static ChannelType Nearest(const ContainerType& bitmap, const DisplayPointF& position, const size_t& ch)
		{
			auto dst = position.Round();
			return bitmap.Index(dst)[ch];
		}
		///	バイリニア補完。
		static ChannelType Bilinear(const ContainerType& bitmap, const DisplayPointF& position, const size_t& ch)
		{
			auto pxi = DisplayRectangle(position.Floor(), RectangleSize(1, 1));
			auto xrange = bitmap.XRange();
			auto yrange = bitmap.YRange();
			auto pxupleft = (xrange.isIncluded(pxi.Left())&&yrange.isIncluded(pxi.Top()))?(bitmap.Index(pxi.Left(), pxi.Top())[ch]):(0);
			auto pxupright = (xrange.isIncluded(pxi.Right())&&yrange.isIncluded(pxi.Top()))?(bitmap.Index(pxi.Right(), pxi.Top())[ch]):(0);
			auto pxdownleft = (xrange.isIncluded(pxi.Left())&&yrange.isIncluded(pxi.Bottom()))?(bitmap.Index(pxi.Left(), pxi.Bottom())[ch]):(0);
			auto pxdownright = (xrange.isIncluded(pxi.Right())&&yrange.isIncluded(pxi.Bottom()))?(bitmap.Index(pxi.Right(), pxi.Bottom())[ch]):(0);
			auto pxd = position.Extract();
			auto pxup = ChannelType(pxupleft * (1 - pxd.X()) + pxupright * (pxd.X()));
			auto pxdown = ChannelType(pxdownleft * (1 - pxd.X()) + pxdownright * (pxd.X()));
			return ChannelType(pxup * (1 - pxd.Y()) + pxdown * (pxd.Y()));
		}
		///	指定された @a bitmap を @a area で指定された範囲で切り抜きます。
		static ContainerType Crop(const ContainerType& bitmap, const DisplayRectangle& area)
		{
			if (!bitmap.Region().Contains(area)) { throw std::invalid_argument("area で指定している範囲がビットマップの範囲を超えています。"); }
			auto result = ContainerType(area.Size(), bitmap.Channels());
			bitmap.Copy(result, area.Location(), DisplayPoint(0, 0), area.Size());
			return result;
		}

	};

}
#endif // __stationaryorbit_graphics_core_bitmapconverter__