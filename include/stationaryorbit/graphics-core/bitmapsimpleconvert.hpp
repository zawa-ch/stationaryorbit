#ifndef __stationaryorbit_graphics_core_bitmapsimpleconvert__
#define __stationaryorbit_graphics_core_bitmapsimpleconvert__
#include <functional>
#include "stationaryorbit/exception/soexcept"
#include "point.hpp"
#include "pointf.hpp"
#include "rectangle.hpp"
#include "bitmapbuffer.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{

	template<class channelT, class destT = BitmapBuffer<channelT>>
	class BitmapSimpleConvert final
	{
	public:
		typedef ChannelValue<channelT> ChannelType;
		typedef BitmapBufferBase<channelT> FrameType;
		typedef destT ContainerType;
		typedef std::function<ChannelType(const FrameType& bitmap, const PointF& position, const size_t& ch)> ComplementMethod;
	private:
		BitmapSimpleConvert() = delete;
		BitmapSimpleConvert(const BitmapSimpleConvert&) = delete;
		BitmapSimpleConvert(BitmapSimpleConvert&&) = delete;
		~BitmapSimpleConvert() = delete;
		BitmapSimpleConvert operator=(const BitmapSimpleConvert&) = delete;
		BitmapSimpleConvert operator=(BitmapSimpleConvert&&) = delete;
	public:
		///	指定された @a bitmap の上下を入れ替えます。
		static ContainerType FripVertical(const FrameType& bitmap)
		{
			auto yrange = Range<size_t>(0, bitmap.GetHeight());
			auto xrange = Range<size_t>(0, bitmap.GetWidth());
			auto chrange = Range<size_t>(0, bitmap.GetChannelCount());
			auto result = ContainerType(bitmap.GetWidth(), bitmap.GetHeight(), bitmap.GetColorSpace());
			auto srcy = yrange.begin();
			auto srcyend = yrange.end();
			auto dsty = yrange.rbegin();
			auto dstyend = yrange.rend();
			while ((srcy != srcyend)&&(dsty != dstyend))
			{
				for (auto x : xrange)
				{
					for (auto ch : chrange)
					{
						result.Index(x, *dsty, ch) = bitmap.Index(x, *srcy, ch);
					}
				}
				++srcy;
				++dsty;
			}
			return result;
		}
		///	指定された @a bitmap の左右を入れ替えます。
		static ContainerType FripHorizonal(const FrameType& bitmap)
		{
			auto xrange = Range<size_t>(0, bitmap.GetWidth());
			auto yrange = Range<size_t>(0, bitmap.GetHeight());
			auto chrange = Range<size_t>(0, bitmap.GetChannelCount());
			auto result = ContainerType(bitmap.GetWidth(), bitmap.GetHeight(), bitmap.GetColorSpace());
			auto srcx = xrange.begin();
			auto srcxend = xrange.end();
			auto dstx = xrange.rbegin();
			auto dstxend = xrange.rend();
			while ((srcx != srcxend)&&(dstx != dstxend))
			{
				for (auto y : yrange)
				{
					for (auto ch : chrange)
					{
						result.Index(*dstx, y, ch) = bitmap.Index(*srcx, y, ch);
					}
				}
				++srcx;
				++dstx;
			}
			return result;
		}
		///	指定された @a bitmap 拡大・縮小します。
		static ContainerType Resize(const FrameType& bitmap, const Point& size, ComplementMethod complement)
		{
			if (complement == nullptr) { throw NullReferenceException("引数 complement にnullを指定することはできません。"); }
			auto srcsize = Point(bitmap.GetWidth(), bitmap.GetHeight());
			auto scalefactor = PointF(srcsize - Point(1, 1)) / PointF(size - Point(1, 1));
			auto xrange = Range<size_t>(0, bitmap.GetWidth());
			auto yrange = Range<size_t>(0, bitmap.GetHeight());
			auto chrange = Range<size_t>(0, bitmap.GetChannelCount());
			auto result = ContainerType(bitmap.GetWidth(), bitmap.GetHeight(), bitmap.GetColorSpace());
			for (auto y : yrange) for (auto x : xrange) for (auto ch : chrange)
			{
				auto dstpos = scalefactor * PointF(x, y);
				result.Index(x, y) = complement(bitmap, dstpos);
			}
			return result;
		}
		///	ニアレストネイバー補完。
		static ChannelType Nearest(const FrameType& bitmap, const PointF& position, const size_t& ch)
		{
			Point dst = Point(position.Round());
			return bitmap.Index(dst.getX(), dst.getY(), ch);
		}
		///	バイリニア補完。
		static ChannelType Bilinear(const FrameType& bitmap, const PointF& position, const size_t& ch)
		{
			auto pxupleft = bitmap.Index(Point(position.Floor()).getY(), Point(position.Floor()).getX(), ch);
			auto pxupright = bitmap.Index(Point(position.Floor()).getY(), Point(position.Ceil()).getX(), ch);
			auto pxdownleft = bitmap.Index(Point(position.Ceil()).getY(), Point(position.Floor()).getX(), ch);
			auto pxdownright = bitmap.Index(Point(position.Ceil()).getY(), Point(position.Ceil()).getX(), ch);
			auto x = position.Extract().getX();
			auto pxup = pxupleft * ChannelType(channelT(ChannelType::Max() * (1 - x))) + pxupright * ChannelType(channelT(ChannelType::Max() * (x)));
			auto pxdown = pxdownleft * ChannelType(channelT(ChannelType::Max() * (1 - x))) + pxdownright * ChannelType(channelT(ChannelType::Max() * (x)));
			auto y = position.Extract().getY();
			return pxup * ChannelType(channelT(ChannelType::Max() * (1 - y))) + pxdown * ChannelType(channelT(ChannelType::Max() * (y)));
		}
		///	指定された @a bitmap を @a area で指定された範囲で切り抜きます。
		static ContainerType Crop(const FrameType& bitmap, const Rectangle& area)
		{
			if ((0 < area.getLeft())||(0 < area.getTop())||(area.getRight() <= bitmap.GetWidth())||(area.getBottom() <= bitmap.GetHeight())) { throw std::invalid_argument("area で指定している範囲がビットマップの範囲を超えています。"); }
			auto srcorigin = area.getTopLeft();
			auto srcend = area.getBottomRight();
			auto dstorigin = Point(0, 0);
			auto dstend = area.getSize();
			auto srcxrange = Range(srcorigin.getX(), srcend.getX());
			auto dstxrange = Range(dstorigin.getX(), dstend.getX());
			auto srcyrange = Range(srcorigin.getY(), srcend.getY());
			auto dstyrange = Range(dstorigin.getY(), dstend.getY());
			auto chrange = Range<size_t>(0, bitmap.GetChannelCount());
			auto result = ContainerType(bitmap.GetWidth(), bitmap.GetHeight(), bitmap.GetColorSpace());
			auto srcy = srcyrange.begin();
			auto srcyend = srcyrange.end();
			auto dsty = dstyrange.begin();
			auto dstyend = dstyrange.end();
			while ((srcy != srcyend)&&(dsty != dstyend))
			{
				auto srcx = srcxrange.begin();
				auto srcxend = srcxrange.end();
				auto dstx = dstxrange.begin();
				auto dstxend = dstxrange.end();
				while ((srcx != srcxend)&&(dstx != dstxend))
				{
					for (auto ch : chrange)
					{
						result.Index(*dstx, *dsty, ch) = bitmap.Index(*srcx, *srcy, ch);
					}
					++srcx;
					++dstx;
				}
				++srcy;
				++dsty;
			}
			return result;
		}

	};

}
#endif // __stationaryorbit_graphics_core_bitmapsimpleconvert__