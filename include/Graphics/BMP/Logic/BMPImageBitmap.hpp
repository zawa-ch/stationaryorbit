#ifndef __StationaryOrbit_Graphics_BMP_BMPImageBitmap__
#define __StationaryOrbit_Graphics_BMP_BMPImageBitmap__
#include "Graphics/Bitmap"
#include "../Logic/BMPImageInfomation.hpp"
namespace StationaryOrbit::Graphics::BMP
{

    class BMPImageBitmap
        : public BitmapFrame
    {
	private:

		BitmapByteBuffer _buffer;

		BMPImageInfomation _info;
	
	public:

		BMPImageBitmap();

		explicit BMPImageBitmap(const BMPImageInfomation& info);

		BitmapByteBuffer& getBMPBuffer() { return _buffer; }

		const BMPImageInfomation& getBMPInfomation() const { return _info; }

    };

}
#endif // __StationaryOrbit_Graphics_BMP_BMPImageBitmap__