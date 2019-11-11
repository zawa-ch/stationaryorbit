#ifndef __StationaryOrbit_Graphics_Bitmap__
#define __StationaryOrbit_Graphics_Bitmap__
#include "../Logic/BitmapFrame.hpp"
#include "../Logic/BitmapBuffer.hpp"
namespace StationaryOrbit::Graphics
{

	class Bitmap final
		: virtual public BitmapFrame
	{
	private:

		BitmapBuffer buf;
		ImageInfomation info;
	
	public:

		Bitmap() = default;

		explicit Bitmap(const ImageInfomation& infomation);

		Bitmap(const Bitmap& value) { Assign(value); }

		Bitmap(const BitmapFrame& value) { Assign(value); }

		const IBitmapBuffer& getBuffer() const { return buf; }

		const IImageInfomation& getInfomation() const { return info; }

		const BitmapPixelGetter getPixel(const Point& position) const { return BitmapPixelGetter(buf, info, position); }

		IBitmapBuffer& Buffer() { return buf; }

		BitmapPixelReference IndexAt(const Point& position) { return BitmapPixelReference(buf, info, position); }

		Bitmap& Assign(const Bitmap& value);

		BitmapFrame& Assign(const BitmapFrame& value);

		BitmapFrame& operator=(const BitmapFrame& value) { return Assign(value); }

	};

}
#endif // __StationaryOrbit_Graphics_Bitmap__