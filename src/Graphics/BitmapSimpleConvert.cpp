#include "Graphics/Logic/BitmapSimpleConvert.hpp"

static void FripVertical_Process(StationaryOrbit::Graphics::BitmapPixelReference dst, const StationaryOrbit::Graphics::BitmapFrame& src)
{
	int y = dst.getBuffer().getSize().getY() - 1 - dst.getPosition().getY();
	StationaryOrbit::Graphics::BitmapPixelGetter srcpx = src.getPixel(StationaryOrbit::Graphics::Point(dst.getPosition().getX(), y));
	for (size_t ch = 0; ch < dst.getChannelCount(); ch++)
	{ dst.setChannel(ch, srcpx.getChannel(ch)); }
}

StationaryOrbit::Graphics::Bitmap StationaryOrbit::Graphics::BitmapSimpleConvert::FripVertical(const BitmapFrame& bitmap)
{
	Bitmap result = Bitmap(ImageInfomation(bitmap.getInfomation()));
	StationaryOrbit::Delegate<StationaryOrbit::Graphics::BitmapPixelReference, const StationaryOrbit::Graphics::BitmapFrame&> actions;
	actions += FripVertical_Process;
	result.ForEach<const BitmapFrame&>(actions, bitmap);
	return result;
}

static void FripHorizonal_Process(StationaryOrbit::Graphics::BitmapPixelReference dst, const StationaryOrbit::Graphics::BitmapFrame& src)
{
	int x = dst.getBuffer().getSize().getX() - 1 - dst.getPosition().getX();
	StationaryOrbit::Graphics::BitmapPixelGetter srcpx = src.getPixel(StationaryOrbit::Graphics::Point(x, dst.getPosition().getY()));
	for (size_t ch = 0; ch < dst.getChannelCount(); ch++)
	{ dst.setChannel(ch, srcpx.getChannel(ch)); }
}

StationaryOrbit::Graphics::Bitmap StationaryOrbit::Graphics::BitmapSimpleConvert::FripHorizonal(const BitmapFrame& bitmap)
{
	Bitmap result = Bitmap(ImageInfomation(bitmap.getInfomation()));
	StationaryOrbit::Delegate<StationaryOrbit::Graphics::BitmapPixelReference, const StationaryOrbit::Graphics::BitmapFrame&> actions;
	actions += FripHorizonal_Process;
	result.ForEach<const BitmapFrame&>(actions, bitmap);
	return result;
}


void StationaryOrbit::Graphics::BitmapSimpleConvert::Biliner(const BitmapFrame& src, BitmapPixelReference& dst)
{
}

StationaryOrbit::Graphics::Bitmap StationaryOrbit::Graphics::BitmapSimpleConvert::Resize(const BitmapFrame& bitmap, const Point& size, ResizeMethod resizer)
{
	ImageInfomation afteriinfo = ImageInfomation(bitmap.getInfomation());
	afteriinfo.setSize(size);
	Bitmap result = Bitmap(afteriinfo);
	return result;
}

StationaryOrbit::Graphics::Bitmap StationaryOrbit::Graphics::BitmapSimpleConvert::Rescale(const BitmapFrame& bitmap, const PointF& magnification)
{
	ImageInfomation afteriinfo = ImageInfomation(bitmap.getInfomation());
	Bitmap result = Bitmap(afteriinfo);
	return result;
}

static void Crop_Process(StationaryOrbit::Graphics::BitmapPixelReference dst, const StationaryOrbit::Graphics::BitmapFrame& src, const StationaryOrbit::Graphics::Rectangle& area)
{
	StationaryOrbit::Graphics::BitmapPixelGetter srcpx = src.getPixel(area.getTopLeft() + dst.getPosition());
	for (size_t ch = 0; ch < dst.getChannelCount(); ch++)
	{ dst.setChannel(ch, srcpx.getChannel(ch)); }
}

StationaryOrbit::Graphics::Bitmap StationaryOrbit::Graphics::BitmapSimpleConvert::Crop(const BitmapFrame& bitmap, const Rectangle& area)
{
	if ((area.getLeft() < 0)||(area.getTop() < 0)||(bitmap.getInfomation().getSize().getX() <= area.getRight())||(bitmap.getInfomation().getSize().getY() <= area.getBottom()))
	{ throw std::invalid_argument(""); }
	ImageInfomation afteriinfo = ImageInfomation(bitmap.getInfomation());
	afteriinfo.setSize(area.getSize());
	Bitmap result = Bitmap(afteriinfo);
	StationaryOrbit::Delegate<StationaryOrbit::Graphics::BitmapPixelReference, const StationaryOrbit::Graphics::BitmapFrame&, const Rectangle&> actions;
	actions += Crop_Process;
	result.ForEach<const BitmapFrame&, const Rectangle&>(actions, bitmap, area);
	return result;
}
