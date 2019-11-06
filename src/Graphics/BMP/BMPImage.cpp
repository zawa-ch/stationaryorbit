#include "Graphics/BMP/Logic/BMPImage.hpp"

void StationaryOrbit::Graphics::BMP::BMPImage::SeekToFileHeader()
{
	if (0 != _stream.tellg()) { _stream.seekg(0); }
}

void StationaryOrbit::Graphics::BMP::BMPImage::SeekToInfoHeader()
{
	if (FileHeaderSize != _stream.tellg()) { _stream.seekg(FileHeaderSize); }
}

void StationaryOrbit::Graphics::BMP::BMPImage::SeekToFileBody()
{
	if (_bodyoffset != _stream.tellg()) { _stream.seekg(_bodyoffset); }
}

std::vector<std::byte> StationaryOrbit::Graphics::BMP::BMPImage::ReadFileInfomation()
{
	SeekToInfoHeader();
	std::vector<std::byte> result;
	for(size_t i = 0; i < (_bodyoffset - FileHeaderSize); i++)
	{
		result.push_back(std::byte(_stream.get()));
	}
	return result;
}

StationaryOrbit::Graphics::BMP::FileHeader StationaryOrbit::Graphics::BMP::BMPImage::GetFileHeader()
{
	SeekToFileHeader();
	BMP::FileHeader FileHeader;
	_stream.read((char*)&FileHeader, sizeof(FileHeader));
	if (!FileHeader.CheckFileHeader()) throw BMP::InvalidFormatException("");
	return FileHeader;
}

StationaryOrbit::Graphics::BMP::BMPImageInfomation StationaryOrbit::Graphics::BMP::BMPImage::GetBitmapInfomation()
{
	std::vector<std::byte> bmpinfo = ReadFileInfomation();
	union
	{
		uint32_t* headsize;
		BMP::CoreHeader* corehead;
		BMP::InfoHeader* infohead;
	} ref = { (uint32_t*)bmpinfo.data() };
	BMPImageInfomation result;

	switch (*(ref.headsize))
	{
	case CoreHeaderSize:
		if (bmpinfo.size() < CoreHeaderSize) throw BMP::InvalidFormatException("");
		result = BMPImageInfomation(*(ref.corehead));
		break;

	case InfoHeaderSize:
		if (bmpinfo.size() < InfoHeaderSize) throw BMP::InvalidFormatException("");
		result = BMPImageInfomation(*(ref.infohead));
		break;
	
	default:
		break;
	}
	return result;
}

size_t StationaryOrbit::Graphics::BMP::BMPImage::GetBody(BMPImageBitmap& bitmap, const Rectangle& area)
{
	// note:
	// ビットマップの読み込みフォーマットは
	// - ピクセルあたりのビット数(Bits per Pixel)
	// - 圧縮形式(Compression)
	// - 各チャネルのビットマスク(bitmask)
	// によって変化する
	BMP::CompressionMethod method = _info.getCompressionMethod();
	BMP::BitDepth depth = _info.getBitCount();

	SeekToFileBody();

	if ((method == BMP::CompressionMethod::RGB)&&(depth == BMP::BitDepth::Bit24))
		return ReadRGB24(_stream, bitmap, _info, area);
	else // 未サポートのフォーマット
		throw BMP::InvalidFormatException("Not supported");
}

size_t StationaryOrbit::Graphics::BMP::BMPImage::ReadRGB24(std::istream& stream, BMPImageBitmap& bitmap, const BMPImageInfomation& info, const Rectangle& area)
{
	size_t readsize = 0U;	///< ストリームから読み込みを行ったデータのサイズ。
	int sizey = info.getSize().getY();
	int sizex = info.getSize().getX();
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
				uint8_t buffer = uint8_t(stream.get());
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
			(void)stream.get();
			readsize++;
		}
	}
	return readsize;
}

StationaryOrbit::Graphics::BMP::BMPImage::BMPImage(std::istream& stream)
	: _stream(stream)
{
	BMP::FileHeader filehead = GetFileHeader();
	_bodyoffset = filehead.Offset;
	_info = GetBitmapInfomation();
}

StationaryOrbit::Graphics::BMP::BMPImageBitmap StationaryOrbit::Graphics::BMP::BMPImage::getBitmap()
{
	BMPImageBitmap result = BMPImageBitmap(_info);
	GetBody(result, Rectangle(Point(0, 0), _info.getSize()));
	return result;
}
