#ifndef __StationaryOrbit_Graphics_Bitmap__
#define __StationaryOrbit_Graphics_Bitmap__
#include "../Logic/BitmapFrame.hpp"
#include "../Logic/BitmapBuffer.hpp"
namespace StationaryOrbit::Graphics
{

	class Bitmap
		: public BitmapFrame
	{
	private:

		BitmapBuffer _buffer;

		ImageInfomation _info;
	
	public:

		Bitmap();

		Bitmap(const ImageInfomation& info);

	};

}
#endif // __StationaryOrbit_Graphics_Bitmap__