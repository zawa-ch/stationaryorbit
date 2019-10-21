#ifndef __StationaryOrbit_Graphics_BMPImageBitmap__
#define __StationaryOrbit_Graphics_BMPImageBitmap__
#include "../Logic/BitmapFrame.hpp"
#include "../Logic/BitmapByteBuffer.hpp"
#include "../Logic/BMPImageInfomation.hpp"
namespace StationaryOrbit::Graphics
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
#endif // __StationaryOrbit_Graphics_BMPImageBitmap__