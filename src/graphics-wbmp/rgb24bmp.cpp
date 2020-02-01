#include <algorithm>
#include "stationaryorbit/graphics-wbmp/rgb24bmp.hpp"
using namespace zawa_ch::StationaryOrbit;

size_t Graphics::BMP::RGB24BMP::Export(std::ostream& stream, const BitmapFrame& bitmap, const BMPImageInfomation& info)
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
	fhead.Offset = FileHeader::Size + InfoHeader::Size + palsize;
	fhead.Offset += fhead.Offset % 4;
	fhead.FileSize = fhead.Offset + ihead.ImageSize;

	size_t writesize = 0U;
	stream.write((char*)&fhead, FileHeader::Size);
	writesize += FileHeader::Size;
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
			RGBColor color = bitmap.getPixel(point).getRGBValue();
			// 各チャネルの書き込み。
			// LittleEndianのため0xRRGGBBがBB GG RRと格納される
			stream.put(char(color.getB() * UINT8_MAX));
			writesize++;
			stream.put(char(color.getG() * UINT8_MAX));
			writesize++;
			stream.put(char(color.getR() * UINT8_MAX));
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

size_t Graphics::BMP::RGB24BMP::Export(std::ostream& stream, const BMPImageBitmap& bitmap)
{
	return Export(stream, bitmap, bitmap.getBMPInfomation());
}
