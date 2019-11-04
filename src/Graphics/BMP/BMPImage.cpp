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

size_t StationaryOrbit::Graphics::BMPImage::GetBody(BMPImageBitmap& bitmap, const Rectangle& area)
{
	// note:
	// ビットマップの読み込みフォーマットは
	// - ピクセルあたりのビット数(Bits per Pixel)
	// - 圧縮形式(Compression)
	// - 各チャネルのビットマスク(bitmask)
	// によって変化する
	BMP::CompressionMethod method = _info.getCompressionMethod();
	BMP::BitDepth depth = _info.getBitCount();

	if ((method == BMP::CompressionMethod::RGB)&&(depth == BMP::BitDepth::Bit24))
		return GetBodyRGB24(bitmap, area);
	else // 未サポートのフォーマット
		throw BMP::InvalidFormatException("Not supported");
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

void StationaryOrbit::Graphics::BMPImage::Export(std::ostream& stream, const BitmapFrame& bitmap, const BMPImageInfomation& info)
{
	BMP::CompressionMethod method = info.getCompressionMethod();
	BMP::BitDepth depth = info.getBitCount();

	if ((method == BMP::CompressionMethod::RGB)&&(depth == BMP::BitDepth::Bit24))
		ExportRGB24(stream, bitmap, info);
	else // 未サポートのフォーマット
		throw BMP::InvalidFormatException("Not supported");
}

void StationaryOrbit::Graphics::BMPImage::Export(std::ostream& stream, const BMPImageBitmap& bitmap)
{
	Export(stream, bitmap, bitmap.getBMPInfomation());
}
