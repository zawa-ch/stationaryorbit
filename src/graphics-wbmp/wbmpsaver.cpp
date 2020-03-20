#include "stationaryorbit/graphics-wbmp/wbmpsaver.hpp"
#include <algorithm>
using namespace zawa_ch::StationaryOrbit::Graphics::WBMP;

void WbmpSaverBase::WriteFileHeader(std::ostream& stream, const FileHeader& data)
{
	stream.write((const char*)&data, sizeof(FileHeader));
}
void WbmpSaverBase::WriteCoreHeader(std::ostream& stream, const CoreHeader& data)
{
	stream.write((const char*)&CoreHeader::Size, sizeof(uint32_t));
	stream.write((const char*)&data, sizeof(CoreHeader));
}
void WbmpSaverBase::WriteInfoHeader(std::ostream& stream, const InfoHeader& data)
{
	stream.write((const char*)&InfoHeader::Size, sizeof(uint32_t));
	stream.write((const char*)&data, sizeof(InfoHeader));
}
void WbmpSaverBase::WriteV4Header(std::ostream& stream, const V4Header& data)
{
	stream.write((const char*)&V4Header::Size, sizeof(uint32_t));
	stream.write((const char*)&data, sizeof(V4Header));
}
void WbmpSaverBase::WriteV5Header(std::ostream& stream, const V5Header& data)
{
	stream.write((const char*)&V5Header::Size, sizeof(uint32_t));
	stream.write((const char*)&data, sizeof(V5Header));
}

WbmpRGBSaver::WbmpRGBSaver(const WbmpBufferBase& data) noexcept
	: _data(data)
{}
uint32_t& WbmpRGBSaver::HorizonalResolution() noexcept { return _resx; }
const uint32_t& WbmpRGBSaver::HorizonalResolution() const noexcept { return _resx; }
uint32_t& WbmpRGBSaver::VerticalResolution() noexcept { return _resy; }
const uint32_t& WbmpRGBSaver::VerticalResolution() const noexcept { return _resy; }
void WbmpRGBSaver::WriteTo(std::ostream& stream) const
{
	FileHeader fileheader;
	std::copy<const uint8_t*, uint8_t*>(&fileheader.FileType_Signature[0], &fileheader.FileType_Signature[2], &fileheader.FileType[0]);
	/* TODO: 状況に応じてV4ヘッダ/V5ヘッダを使用する */
	InfoHeader dataheader;
	fileheader.Offset = InfoHeader::Size + sizeof(FileHeader) + ((((InfoHeader::Size + sizeof(FileHeader))%4)!=0)?(4-(((InfoHeader::Size + sizeof(FileHeader))%4))):(0));
	dataheader.ImageHeight = _data.GetHeight();
	dataheader.ImageWidth = _data.GetWidth();
	dataheader.PlaneCount = 1;
	dataheader.BitCount = _data.GetBitDepth();
	dataheader.ComplessionMethod = CompressionMethod::RGB;
	dataheader.ImageSize = _data.LinearLength();
	dataheader.ResolutionHolizonal = _resx;
	dataheader.ResolutionVertical = _resy;
	dataheader.IndexedColorCount = 0;
	dataheader.ImportantColorCount = 0;
	fileheader.FileSize = fileheader.Offset + dataheader.ImageSize;
	size_t writesize = 0;
	WriteFileHeader(stream, fileheader);
	stream.flush();
	writesize += sizeof(FileHeader);
	WriteInfoHeader(stream, dataheader);
	stream.flush();
	writesize += InfoHeader::Size;
	for (auto item : Range<size_t>(0, fileheader.Offset - writesize)) { stream.put(char()); }
	auto yrange = Range<size_t>(0, _data.GetHeight());
	auto y = yrange.rbegin();
	auto yend = yrange.rend();
	while (y != yend)
	{
		WriteLine(stream, _data, *y);
		++y;
	}
}
uint32_t WbmpRGBSaver::CreatePxData(const WbmpBufferBase& data, const size_t& x, const size_t& y)
{
	uint32_t result = 0;
	if (data.GetColorSpace() == BitmapColorSpace::GrayScale)
	{
		result = data.Index(x, y, 0).get();
	}
	else if (data.GetColorSpace() == BitmapColorSpace::ARGB)
	{
		uint8_t value = data.Index(x, y, 0).get();
		result = WbmpRGBData::DefaultColorMask(data.GetBitDepth()).RedMask.SetAlignedTo(result, value >> (8 - WbmpRGBData::DefaultColorMask(data.GetBitDepth()).RedMask.Length()));
		value = data.Index(x, y, 1).get();
		result = WbmpRGBData::DefaultColorMask(data.GetBitDepth()).GreenMask.SetAlignedTo(result, value >> (8 - WbmpRGBData::DefaultColorMask(data.GetBitDepth()).GreenMask.Length()));
		value = data.Index(x, y, 2).get();
		result = WbmpRGBData::DefaultColorMask(data.GetBitDepth()).BlueMask.SetAlignedTo(result, value >> (8 - WbmpRGBData::DefaultColorMask(data.GetBitDepth()).BlueMask.Length()));
		// アルファチャンネルのサポートはアルファチャンネル付きビットフィールドでの対応
	}
	else
	{
		throw InvalidOperationException("色空間の値が無効です。");
	}
	return result;
}
void WbmpRGBSaver::WriteLine(std::ostream& stream, const WbmpBufferBase& data, const size_t& y)
{
	auto lengthbit = size_t(data.GetBitDepth());
	auto lengthbyte = (lengthbit / 8) + (((lengthbit%8)!=0)?(1):(0));
	auto lengthline = lengthbyte * data.GetWidth();
	for (auto x : Range<size_t>(0, data.GetWidth()))
	{
		auto pixel = CreatePxData(data, x, y);
		stream.write((const char*)&pixel, lengthbyte);
	}
	for (auto i : Range<size_t>(0, (((lengthline%4)!=0)?((4-(lengthline%4))):(0))))
	{
		stream.put(0);
	}
}
