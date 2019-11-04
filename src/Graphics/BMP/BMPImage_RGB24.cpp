#include "Graphics/Logic/BMPImage.hpp"

void StationaryOrbit::Graphics::BMPImage::GetBodyRGB24(BMPImageBitmap& bitmap, const Rectangle& area)
{
	size_t readsize = 0U;	///< ストリームから読み込みを行ったデータのサイズ。
	SeekToFileBody();
	int sizey = _info.getSize().getY();
	int sizex = _info.getSize().getX();
	// y軸の読取り。(下から上)
	for(int y = sizey - 1; 0 <= y; y--)
	{
		// x軸の読取り。(左から右)
		for(int x = 0; x < sizex; x++)
		{
			Point point = Point(x, y);
			// 各チャネルの読取り。
			// LittleEndianのため0xRRGGBBがBB GG RRと格納される
			for(int ch = 2; 0 <= ch; ch--)
			{
				uint8_t buffer = uint8_t(_stream.get());
				readsize++;
				if (area.InRange(point))
				{
					bitmap.getBMPBuffer().setPixelRaw(point - area.getTopLeft(), ch, std::byte(buffer));
				}
			}
			if (area.InRange(point))
			{
				bitmap.getBMPBuffer().setPixelRaw(point - area.getTopLeft(), 3, std::byte(255));
			}
		}
		while((readsize % 4) != 0)
		{
			(void)_stream.get();
			readsize++;
		}
	}
}