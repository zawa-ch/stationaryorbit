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
            Point src = Point(x, y);
            Point dst = Point(x, ysize - 1 - y);
            result.IndexAt(dst).setValue(bitmap.getPixel(src).getValue());
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
            Point src = Point(x, y);
            Point dst = Point(xsize - 1 - x, y);
            result.IndexAt(dst).setValue(bitmap.getPixel(src).getValue());
        }
    }
    return result;
}

StationaryOrbit::Graphics::Bitmap StationaryOrbit::Graphics::BitmapSimpleConvert::Resize(const BitmapFrame& bitmap, const Point& size)
{
    ImageInfomation afteriinfo = ImageInfomation(bitmap.getInfomation());
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
    ImageInfomation afteriinfo = ImageInfomation(bitmap.getInfomation());
    Bitmap result = Bitmap(afteriinfo);
    return result;
}
