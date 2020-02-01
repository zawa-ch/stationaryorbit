#include "stationaryorbit/graphics-core/bitmapsimpleconvert.hpp"
using namespace zawa_ch::StationaryOrbit;

static void FripVertical_Process(zawa_ch::StationaryOrbit::Graphics::BitmapPixelReference dst, const zawa_ch::StationaryOrbit::Graphics::BitmapFrame& src)
{
	int y = dst.getBuffer().getSize().getY() - 1 - dst.getPosition().getY();
	zawa_ch::StationaryOrbit::Graphics::BitmapPixelGetter srcpx = src.getPixel(zawa_ch::StationaryOrbit::Graphics::Point(dst.getPosition().getX(), y));
	for (size_t ch = 0; ch < dst.getChannelCount(); ch++)
	{ dst.setChannel(ch, srcpx.getChannel(ch)); }
}

zawa_ch::StationaryOrbit::Graphics::Bitmap zawa_ch::StationaryOrbit::Graphics::BitmapSimpleConvert::FripVertical(const BitmapFrame& bitmap)
{
	Bitmap result = Bitmap(ImageInfomation(bitmap.getInfomation()));
	Delegate<BitmapPixelReference, const BitmapFrame&> actions;
	actions += FripVertical_Process;
	result.ForEach<const BitmapFrame&>(actions, bitmap);
	return result;
}

static void FripHorizonal_Process(zawa_ch::StationaryOrbit::Graphics::BitmapPixelReference dst, const zawa_ch::StationaryOrbit::Graphics::BitmapFrame& src)
{
	int x = dst.getBuffer().getSize().getX() - 1 - dst.getPosition().getX();
	zawa_ch::StationaryOrbit::Graphics::BitmapPixelGetter srcpx = src.getPixel(zawa_ch::StationaryOrbit::Graphics::Point(x, dst.getPosition().getY()));
	for (size_t ch = 0; ch < dst.getChannelCount(); ch++)
	{ dst.setChannel(ch, srcpx.getChannel(ch)); }
}

zawa_ch::StationaryOrbit::Graphics::Bitmap zawa_ch::StationaryOrbit::Graphics::BitmapSimpleConvert::FripHorizonal(const BitmapFrame& bitmap)
{
	Bitmap result = Bitmap(ImageInfomation(bitmap.getInfomation()));
	Delegate<BitmapPixelReference, const BitmapFrame&> actions;
	actions += FripHorizonal_Process;
	result.ForEach<const BitmapFrame&>(actions, bitmap);
	return result;
}

void zawa_ch::StationaryOrbit::Graphics::BitmapSimpleConvert::Nearest(BitmapPixelReference dst, const BitmapFrame& src)
{
	Point srcsize = src.getBuffer().getSize();
	Point dstsize = dst.getBuffer().getSize();
	PointF scalefactor = PointF(srcsize) / PointF(dstsize);
	PointF srcpoint = scalefactor * dst.getPosition();
	BitmapPixelGetter srcpx = src.getPixel( srcpoint.Floor().operator Point() );
	dst.setValue(srcpx);
}

static zawa_ch::StationaryOrbit::Graphics::PointF GetResizedPoint(zawa_ch::StationaryOrbit::Graphics::BitmapPixelReference dst, const zawa_ch::StationaryOrbit::Graphics::BitmapFrame& src)
{
	zawa_ch::StationaryOrbit::Graphics::Point srcsize = src.getBuffer().getSize();
	zawa_ch::StationaryOrbit::Graphics::Point dstsize = dst.getBuffer().getSize();
	zawa_ch::StationaryOrbit::Graphics::PointF scalefactor = zawa_ch::StationaryOrbit::Graphics::PointF(srcsize - zawa_ch::StationaryOrbit::Graphics::Point(1, 1)) / zawa_ch::StationaryOrbit::Graphics::PointF(dstsize - zawa_ch::StationaryOrbit::Graphics::Point(1, 1));
	zawa_ch::StationaryOrbit::Graphics::PointF result = scalefactor * dst.getPosition();
	return result;
}

void zawa_ch::StationaryOrbit::Graphics::BitmapSimpleConvert::Bilinear(BitmapPixelReference dst, const BitmapFrame& src)
{
	PointF srcpoint = GetResizedPoint(dst, src);
	Rectangle srcarea = Rectangle(srcpoint.Floor().operator Point(), srcpoint.Ceil().operator Point());
	PointF map = srcpoint.Extract();
	BitmapPixelGetter srcpx1 = src.getPixel( srcarea.getTopLeft() );
	BitmapPixelGetter srcpx2 = src.getPixel( srcarea.getTopRight() );
	BitmapPixelGetter srcpx3 = src.getPixel( srcarea.getBottomLeft() );
	BitmapPixelGetter srcpx4 = src.getPixel( srcarea.getBottomRight() );
	dst.setValue(srcpx1);
}

zawa_ch::StationaryOrbit::Graphics::Bitmap zawa_ch::StationaryOrbit::Graphics::BitmapSimpleConvert::Resize(const BitmapFrame& bitmap, const Point& size, ResizeMethod resizer)
{
	if (resizer == nullptr) { throw NullReferenceException("引数'resizer'にnullを指定することはできません。"); }
	ImageInfomation afteriinfo = ImageInfomation(bitmap.getInfomation());
	afteriinfo.setSize(size);
	Bitmap result = Bitmap(afteriinfo);
	Delegate<BitmapPixelReference, const BitmapFrame&> actions;
	actions += resizer;
	result.ForEach<const BitmapFrame&>(actions, bitmap);
	return result;
}

static void Crop_Process(zawa_ch::StationaryOrbit::Graphics::BitmapPixelReference dst, const zawa_ch::StationaryOrbit::Graphics::BitmapFrame& src, const zawa_ch::StationaryOrbit::Graphics::Rectangle& area)
{
	zawa_ch::StationaryOrbit::Graphics::BitmapPixelGetter srcpx = src.getPixel(area.getTopLeft() + dst.getPosition());
	for (size_t ch = 0; ch < dst.getChannelCount(); ch++)
	{ dst.setChannel(ch, srcpx.getChannel(ch)); }
}

zawa_ch::StationaryOrbit::Graphics::Bitmap zawa_ch::StationaryOrbit::Graphics::BitmapSimpleConvert::Crop(const BitmapFrame& bitmap, const Rectangle& area)
{
	if ((area.getLeft() < 0)||(area.getTop() < 0)||(bitmap.getInfomation().getSize().getX() <= area.getRight())||(bitmap.getInfomation().getSize().getY() <= area.getBottom()))
	{ throw std::invalid_argument(""); }
	ImageInfomation afteriinfo = ImageInfomation(bitmap.getInfomation());
	afteriinfo.setSize(area.getSize());
	Bitmap result = Bitmap(afteriinfo);
	Delegate<BitmapPixelReference, const BitmapFrame&, const Rectangle&> actions;
	actions += Crop_Process;
	result.ForEach<const BitmapFrame&, const Rectangle&>(actions, bitmap, area);
	return result;
}
