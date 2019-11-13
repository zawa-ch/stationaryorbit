#include "Graphics/Logic/BitmapSimpleConvert.hpp"

StationaryOrbit::Graphics::Bitmap StationaryOrbit::Graphics::BitmapSimpleConvert::FripVertical(const BitmapFrame& bitmap)
{
	int xsize = bitmap.getInfomation().getSize().getX();
	int ysize = bitmap.getInfomation().getSize().getY();
	Bitmap result = Bitmap(ImageInfomation(bitmap.getInfomation()));
	for (int y = 0; y < ysize; y++)
	{
		for (int x = 0; x < xsize; x++)
		{
			BitmapPixelGetter src = bitmap.getPixel(Point(x, y));
			BitmapPixelReference dst = result.IndexAt(Point(x, ysize - 1 - y));
			dst.setValue(src);
		}
	}
	return result;
}

StationaryOrbit::Graphics::Bitmap StationaryOrbit::Graphics::BitmapSimpleConvert::FripHorizonal(const BitmapFrame& bitmap)
{
	int xsize = bitmap.getInfomation().getSize().getX();
	int ysize = bitmap.getInfomation().getSize().getY();
	Bitmap result = Bitmap(ImageInfomation(bitmap.getInfomation()));
	for (int y = 0; y < ysize; y++)
	{
		for (int x = 0; x < xsize; x++)
		{
			BitmapPixelGetter src = bitmap.getPixel(Point(x, y));
			BitmapPixelReference dst = result.IndexAt(Point(xsize - 1 - x, y));
			dst.setValue(src);
		}
	}
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

StationaryOrbit::Graphics::Bitmap StationaryOrbit::Graphics::BitmapSimpleConvert::Crop(const BitmapFrame& bitmap, const Rectangle& area)
{
	if ((area.getLeft() < 0)||(area.getTop() < 0)||(bitmap.getInfomation().getSize().getX() <= area.getRight())||(bitmap.getInfomation().getSize().getY() <= area.getBottom()))
	{ throw std::invalid_argument(""); }
	ImageInfomation afteriinfo = ImageInfomation(bitmap.getInfomation());
	afteriinfo.setSize(area.getSize());
	int xsize = area.getWidth();
	int ysize = area.getHeight();
	Bitmap result = Bitmap(afteriinfo);
	for (int y = 0; y < ysize; y++)
	{
		for (int x = 0; x < xsize; x++)
		{
			BitmapPixelGetter src = bitmap.getPixel(area.getTopLeft() + Point(x, y));
			BitmapPixelReference dst = result.IndexAt(Point(x, y));
			dst.setValue(src);
		}
	}
	return result;
}
