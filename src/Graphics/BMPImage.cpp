#include "Graphics/Logic/BMPImage.hpp"

void StationaryOrbit::Graphics::BMPImage::SeekToFileHeader()
{
	if (0 != _stream.tellg()) { _stream.seekg(0); }
}

void StationaryOrbit::Graphics::BMPImage::SeekToInfoHeader()
{
	if (FileHeaderSize != _stream.tellg()) { _stream.seekg(FileHeaderSize); }
}

void StationaryOrbit::Graphics::BMPImage::SeekToFileBody()
{
	if (_bodyoffset != _stream.tellg()) { _stream.seekg(_bodyoffset); }
}

std::vector<std::byte> StationaryOrbit::Graphics::BMPImage::ReadFileInfomation()
{
	SeekToInfoHeader();
	std::vector<std::byte> result;
	for(size_t i = 0; i < (_bodyoffset - FileHeaderSize); i++)
	{
		result.push_back(std::byte(_stream.get()));
	}
	return result;
}

StationaryOrbit::Graphics::BMP::FileHeader StationaryOrbit::Graphics::BMPImage::GetFileHeader()
{
	SeekToFileHeader();
	BMP::FileHeader FileHeader;
	_stream.read((char*)&FileHeader, sizeof(FileHeader));
	if (!FileHeader.CheckFileHeader()) throw BMP::InvalidFormatException("");
	return FileHeader;
}

StationaryOrbit::Graphics::BMPImageInfomation StationaryOrbit::Graphics::BMPImage::GetBitmapInfomation()
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

void StationaryOrbit::Graphics::BMPImage::GetBody(BMPImageBitmap& bitmap, const Rectangle& area)
{
	// note:
	// ビットマップの読み込みフォーマットは
	// - ピクセルあたりのビット数(Bits per Pixel)
	// - 圧縮形式(Compression)
	// - 各チャネルのビットマスク(bitmask)
	// によって変化する
	switch (_info.getCompressionMethod())
	{
	case BMP::CompressionMethod::RGB:
		GetBodyRGB(bitmap, area);
		break;

	case BMP::CompressionMethod::RLE8:
	case BMP::CompressionMethod::RLE4:
	case BMP::CompressionMethod::BITFIELDS:
	case BMP::CompressionMethod::JPEG:
	case BMP::CompressionMethod::PNG:
	case BMP::CompressionMethod::ALPHABITFIELDS:
	default:
		// 未サポートのフォーマット
		throw BMP::InvalidFormatException("Not supported");
	}
}

void StationaryOrbit::Graphics::BMPImage::GetBodyRGB(BMPImageBitmap& bitmap, const Rectangle& area)
{
	switch (_info.getBitCount())
	{
	case BMP::BitDepth::Bit24:
		GetBodyRGB24(bitmap, area);
		break;

		// 未サポートのフォーマット
	case BMP::BitDepth::Bit1:
	case BMP::BitDepth::Bit4:
	case BMP::BitDepth::Bit8:
	case BMP::BitDepth::Bit16:
	case BMP::BitDepth::Bit32:
	default:
		throw BMP::InvalidFormatException("Not supported");
	}
}

void StationaryOrbit::Graphics::BMPImage::GetBodyRGB24(BMPImageBitmap& bitmap, const Rectangle& area)
{
	size_t readsize = 0U;	///< ストリームから読み込みを行ったデータのサイズ。
	SeekToFileBody();
	int sizey = _info.getSize().getY();
	int sizex = _info.getSize().getX();
	for(int y = sizey - 1; 0 <= y; y--)
	{
		for(int x = 0; x < sizex; x++)
		{
			Point point = Point(x, y);
			for(int ch = 2; 0 <= ch; ch--)
			{
				uint8_t buffer = uint8_t(_stream.get());
				readsize++;
				if (area.InRange(point))
				{
					bitmap.getBMPBuffer().setPixel(point - area.getTopLeft(), ch, float(buffer) / 255.0f);
				}
			}
			if (area.InRange(point))
			{
				bitmap.getBMPBuffer().setPixel(point - area.getTopLeft(), 3, 1.0f);
			}
		}
		while((readsize % 4) != 0)
		{
			(void)_stream.get();
			readsize++;
		}
	}
}

StationaryOrbit::Graphics::BMPImage::BMPImage(std::istream& stream)
	: _stream(stream)
{
	BMP::FileHeader filehead = GetFileHeader();
	_bodyoffset = filehead.Offset;
	_info = GetBitmapInfomation();
}

StationaryOrbit::Graphics::BMPImageBitmap StationaryOrbit::Graphics::BMPImage::getBitmap()
{
	BMPImageBitmap result = BMPImageBitmap(_info);
	GetBody(result, Rectangle(Point(0, 0), _info.getSize()));
	return result;
}
