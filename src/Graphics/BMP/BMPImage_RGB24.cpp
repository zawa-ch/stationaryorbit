#include <algorithm>
#include "Graphics/Logic/BMPImage.hpp"

size_t StationaryOrbit::Graphics::BMPImage::GetBodyRGB24(BMPImageBitmap& bitmap, const Rectangle& area)
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
	return readsize;
}

size_t StationaryOrbit::Graphics::BMPImage::ExportRGB24(std::ostream& stream, const BitmapFrame& bitmap, const BMPImageInfomation& info)
{
	BMP::InfoHeader ihead = BMP::InfoHeader(info);
	uint32_t xsize = ihead.ImageWidth * 3;
	xsize += xsize % 4;
	ihead.ImageSize = ihead.ImageHeight * xsize;
	uint32_t palsize = ihead.IndexedColorCount * 4;
	if (palsize != 0) throw InvalidOperationException("Not Supported");
	BMP::FileHeader fhead;
	fhead.FileType[0] = BMP::FileHeader::FileType_Signature[0];
	fhead.FileType[1] = BMP::FileHeader::FileType_Signature[1];
	fhead.Offset = FileHeaderSize + InfoHeaderSize + palsize;
	fhead.Offset += fhead.Offset % 4;
	fhead.FileSize = fhead.Offset + ihead.ImageSize;

	size_t writesize = 0U;
	stream.write((char*)&fhead, FileHeaderSize);
	writesize += FileHeaderSize;
	stream.write((char*)&ihead, ihead.Size);
	writesize += ihead.Size;
	while((writesize % 4) != 0)
	{
		stream.put(0);
		writesize++;
	}
	// y軸の書き込み。(下から上)
	for(int y = ihead.ImageHeight - 1; 0 <= y; y--)
	{
		// x軸の書き込み。(左から右)
		for(int x = 0; x < ihead.ImageWidth; x++)
		{
			Point point = Point(x, y);
			Color color = bitmap.getPixel(point);
			// 各チャネルの書き込み。
			// LittleEndianのため0xRRGGBBがBB GG RRと格納される
			stream.put(char(color.getRGB().getB() * UINT8_MAX));
			writesize++;
			stream.put(char(color.getRGB().getG() * UINT8_MAX));
			writesize++;
			stream.put(char(color.getRGB().getR() * UINT8_MAX));
			writesize++;
		}
		while((writesize % 4) != 0)
		{
			stream.put(0);
			writesize++;
		}
	}
	return writesize;
}
