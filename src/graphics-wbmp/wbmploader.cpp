#include "stationaryorbit/graphics-wbmp/wbmploader.hpp"
#include <algorithm>
using namespace zawa_ch::StationaryOrbit::Graphics;
using namespace zawa_ch::StationaryOrbit::Graphics::WBMP;

FileHeader WbmpLoaderBase::ReadFileHead(std::istream& stream)
{
	FileHeader result;
	stream.read((char*)&result, sizeof(FileHeader));
	if (!result.CheckFileHeader()) { throw InvalidWbmpFormatException("ファイルヘッダのファイルタイプ情報が無効です。"); }
	return result;
}
uint32_t WbmpLoaderBase::ReadHeaderSize(std::istream& stream)
{
	uint32_t result;
	stream.read((char*)&result, sizeof(uint32_t));
	return result;
}
CoreHeader WbmpLoaderBase::ReadCoreHeader(std::istream& stream)
{
	CoreHeader result;
	stream.read((char*)&result, sizeof(CoreHeader));
	return result;
}
InfoHeader WbmpLoaderBase::ReadInfoHeader(std::istream& stream)
{
	InfoHeader result;
	stream.read((char*)&result, sizeof(InfoHeader));
	return result;
}
V4Header WbmpLoaderBase::ReadV4Header(std::istream& stream)
{
	V4Header result;
	stream.read((char*)&result, sizeof(V4Header));
	return result;
}
V5Header WbmpLoaderBase::ReadV5Header(std::istream& stream)
{
	V5Header result;
	stream.read((char*)&result, sizeof(V5Header));
	return result;
}

WbmpLoader::WbmpLoader(std::istream& stream)
{
	auto excbits = stream.exceptions();
	stream.exceptions(std::ios_base::failbit | std::ios_base::eofbit | std::ios_base::badbit);
	auto fileheader = ReadFileHead(stream);
	auto headersize = ReadHeaderSize(stream);
	switch (headersize)
	{
	case CoreHeader::Size: ReadBody(stream, fileheader, ReadCoreHeader(stream)); break;
	case InfoHeader::Size: ReadBody(stream, fileheader, ReadInfoHeader(stream)); break;
	case V4Header::Size: ReadBody(stream, fileheader, ReadV4Header(stream)); break;
	case V5Header::Size: ReadBody(stream, fileheader, ReadV5Header(stream)); break;
	default: throw InvalidWbmpFormatException("ヘッダサイズが無効です。");
	}
	stream.exceptions(excbits);
}
const WbmpBufferBase& WbmpLoader::Buffer() const { return *_buffer; }
void WbmpLoader::ReadBody(std::istream& stream, const FileHeader& filehead, const CoreHeader& header)
{
	switch (header.BitCount)
	{
	case BitDepth::Bit1: case BitDepth::Bit4: case BitDepth::Bit8:
		throw NotImplementedException();
	case BitDepth::Bit24:
		_buffer = std::unique_ptr<WbmpBufferBase>(new WbmpRGBBuffer(header.ImageWidth, header.ImageHeight, header.BitCount));
	default:
		throw InvalidWbmpFormatException("ビット深度が無効です。");
	}
	stream.ignore(filehead.Offset - stream.tellg());
	for (auto item : Range<size_t>(0, _buffer->LinearLength())) { _buffer->LinearIndex(item) = stream.get(); if (stream.eof()) { break; } }
}
void WbmpLoader::ReadBody(std::istream& stream, const FileHeader& filehead, const InfoHeader& header)
{
	_resx = header.ResolutionHolizonal;
	_resy = header.ResolutionVertical;
	// ビットマスクRGB画像の場合はマスク用ビットフィールドを取得
	ColorMask mask;
	if (header.ComplessionMethod == CompressionMethod::BITFIELDS)
	{
		RGBColorMask maskdata;
		stream.read((char*)&maskdata, sizeof(RGBColorMask));
		mask = ColorMask{ BitMask<uint32_t>(maskdata.ColorMaskR), BitMask<uint32_t>(maskdata.ColorMaskG), BitMask<uint32_t>(maskdata.ColorMaskB), std::nullopt };
	}
	else if (header.ComplessionMethod == CompressionMethod::ALPHABITFIELDS)
	{
		RGBAColorMask maskdata;
		stream.read((char*)&maskdata, sizeof(RGBAColorMask));
		mask = ColorMask{ BitMask<uint32_t>(maskdata.ColorMaskR), BitMask<uint32_t>(maskdata.ColorMaskG), BitMask<uint32_t>(maskdata.ColorMaskB), BitMask<uint32_t>(maskdata.ColorMaskA) };
	}
	else { /* do nothing */ }
	/* TODO: カラーパレットの読み込みに対応する */
	// 画像データ保持用バッファの初期化
	switch (header.ComplessionMethod)
	{
	case CompressionMethod::RGB:
		if (header.IndexedColorCount == 0)
		{
			switch (header.BitCount)
			{
			case BitDepth::Bit1: case BitDepth::Bit4: case BitDepth::Bit8:
				// グレースケール画像
				throw NotImplementedException();
			case BitDepth::Bit16: case BitDepth::Bit24: case BitDepth::Bit32:
				// RGBカラー画像
				_buffer = std::unique_ptr<WbmpBufferBase>(new WbmpRGBBuffer(header.ImageWidth, header.ImageHeight, header.BitCount));
				break;
			default:
				throw InvalidWbmpFormatException("ビット深度が無効です。");
			}
		}
		else
		{
			// インデックスカラー画像
			throw NotImplementedException();
		}
		break;
	case CompressionMethod::RLE4:
		// 4ビット/ピクセル ランレングス符号圧縮画像
		throw NotImplementedException();
	case CompressionMethod::RLE8:
		// 8ビット/ピクセル ランレングス符号圧縮画像
		throw NotImplementedException();
	case CompressionMethod::BITFIELDS:
		// RGBカラー画像
		_buffer = std::unique_ptr<WbmpBufferBase>(new WbmpRGBBuffer(header.ImageWidth, header.ImageHeight, header.BitCount, mask));
		break;
	case CompressionMethod::JPEG:
		// JPEG圧縮画像
		throw NotImplementedException();
	case CompressionMethod::PNG:
		// PNG圧縮画像
		throw NotImplementedException();
	case CompressionMethod::ALPHABITFIELDS:
		// RGBカラー画像
		_buffer = std::unique_ptr<WbmpBufferBase>(new WbmpRGBBuffer(header.ImageWidth, header.ImageHeight, header.BitCount, mask));
		break;
	default:
		throw InvalidWbmpFormatException("ビットマップ形式が無効です。");
	}
	stream.ignore(filehead.Offset - stream.tellg());
	for (auto item : Range<size_t>(0, _buffer->LinearLength())) { _buffer->LinearIndex(item) = stream.get(); if (stream.eof()) { break; } }
}
void WbmpLoader::ReadBody(std::istream& stream, const FileHeader& filehead, const V4Header& header)
{
	_resx = header.ResolutionHolizonal;
	_resy = header.ResolutionVertical;
}
void WbmpLoader::ReadBody(std::istream& stream, const FileHeader& filehead, const V5Header& header)
{
	_resx = header.ResolutionHolizonal;
	_resy = header.ResolutionVertical;
}
