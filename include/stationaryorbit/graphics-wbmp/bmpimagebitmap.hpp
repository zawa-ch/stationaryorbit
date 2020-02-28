#ifndef __StationaryOrbit_Graphics_BMP_BMPImageBitmap__
#define __StationaryOrbit_Graphics_BMP_BMPImageBitmap__
#include "stationaryorbit/graphics-core/bitmap"
#include "bmpimageinfomation.hpp"
namespace zawa_ch::StationaryOrbit::Graphics::BMP
{

    class BMPImageBitmap
        : virtual public BitmapFrame
    {
	private:

		BitmapByteBuffer buf;
		BMPImageInfomation info;
	
	public:

		BMPImageBitmap() = default;

		explicit BMPImageBitmap(const BMPImageInfomation& infomation);

		BMPImageBitmap(const BMPImageBitmap& value) { Assign(value); }

		BMPImageBitmap(const BitmapFrame& value) { Assign(value); }

		const IBitmapBuffer& getBuffer() const { return buf; }

		const BitmapByteBuffer& getBMPBuffer() const { return buf; }

		const IImageInfomation& getInfomation() const { return info; }

		const BMPImageInfomation& getBMPInfomation() const { return info; }

		const BitmapPixelGetter getPixel(const Point& position) const { return BitmapPixelGetter(buf, info, position); }

		IBitmapBuffer& Buffer() { return buf; }

		BitmapByteBuffer& BMPBuffer() { return buf; }

		BitmapPixelReference Index(const Point& position) { return BitmapPixelReference(buf, info, position); }

		BMPImageBitmap& Assign(const BMPImageBitmap& value);

		BitmapFrame& Assign(const BitmapFrame& value);

		BMPImageBitmap& operator=(const BMPImageBitmap& value) { return Assign(value); }

		BitmapFrame& operator=(const BitmapFrame& value) { return Assign(value); }

    };

}
#endif // __StationaryOrbit_Graphics_BMP_BMPImageBitmap__