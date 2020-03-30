#include "stationaryorbit/graphics-dib/dibbitmap.hpp"
#include "stationaryorbit/graphics-dib/fileheader.hpp"
#include "stationaryorbit/graphics-dib/colormask.hpp"
using namespace zawa_ch::StationaryOrbit;
using namespace zawa_ch::StationaryOrbit::Graphics;
using namespace zawa_ch::StationaryOrbit::Graphics::DIB;

DIBBitmap::DIBBitmap() : BitmapBase<uint8_t>(), _cindex() {}
DIBBitmap::DIBBitmap(const BitmapBase<uint8_t>& data) : BitmapBase<uint8_t>(data), _cindex() { if ((data.Channels() != 4)&&(data.Channels() != 1)) { throw std::invalid_argument("指定された data のチャネル数はこのクラスではサポートされていません。"); } }
DIBBitmap::DIBBitmap(const BitmapBase<uint8_t>& data, const std::vector<RGBTriple_t>& pal) : BitmapBase<uint8_t>(data), _cindex(pal) { if (data.Channels() != 1) { throw std::invalid_argument("指定された data のチャネル数はこのクラスではサポートされていません。"); } }
DIBBitmap::DIBBitmap(const RectangleSize& size, const DataTypes& datatype) : BitmapBase<uint8_t>(size, (datatype==DataTypes::ARGB)?4:1), _cindex() {}
DIBBitmap::DIBBitmap(const RectangleSize& size, const int& palsize) : BitmapBase<uint8_t>(size, 1), _cindex(palsize) {}
DIBBitmap::DIBBitmap(const RectangleSize& size, const std::vector<RGBTriple_t>& pal) : BitmapBase<uint8_t>(size, 1), _cindex(pal) {}
DIBBitmap::DataTypes DIBBitmap::DataType() const
{
	if (Channels() == 4) { return DataTypes::ARGB; }
	else if (_cindex.size() == 0) { return DataTypes::GrayScale; }
	else { return DataTypes::IndexedColor; }
}
std::vector<RGBTriple_t>& DIBBitmap::ColorIndex() { return _cindex; }
const std::vector<RGBTriple_t>& DIBBitmap::ColorIndex() const { return _cindex; }
int& DIBBitmap::HorizonalResolution() { return _resh; }
const int& DIBBitmap::HorizonalResolution() const { return _resh; }
int& DIBBitmap::VerticalResolution() { return _resv; }
const int& DIBBitmap::VerticalResolution() const { return _resv; }
Property<DIBBitmap, ARGBColor> DIBBitmap::Index(const DisplayPoint& position) { return Property<DIBBitmap, ARGBColor>(*this, std::bind(getIndex, std::placeholders::_1, position), std::bind(setIndex, std::placeholders::_1, position, std::placeholders::_2)); }
Property<DIBBitmap, ARGBColor> DIBBitmap::Index(const int& x, const int& y) { return Index(DisplayPoint(x, y)); }
Property<DIBBitmap, ARGBColor> DIBBitmap::operator[](const DisplayPoint& index) { return Index(index); }
ReadOnlyProperty<DIBBitmap, ARGBColor> DIBBitmap::Index(const DisplayPoint& position) const { return ReadOnlyProperty<DIBBitmap, ARGBColor>(*this, std::bind(getIndex, std::placeholders::_1, position)); }
ReadOnlyProperty<DIBBitmap, ARGBColor> DIBBitmap::Index(const int& x, const int& y) const { return Index(DisplayPoint(x, y)); }
ReadOnlyProperty<DIBBitmap, ARGBColor> DIBBitmap::operator[](const DisplayPoint& index) const { return Index(index); }
void DIBBitmap::WriteTo(std::ostream& stream, const BitDepth& depth) const
{
	switch (DataType())
	{
		case DataTypes::ARGB: { writeRGB(stream, depth); break; }
		case DataTypes::GrayScale: { throw NotImplementedException(); break; }
		case DataTypes::IndexedColor: { throw NotImplementedException(); break; }
		default: { throw InvalidOperationException("このオブジェクトのデータ型が無効です。"); }
	}
}
DIBBitmap DIBBitmap::CreateRGBColor(const RectangleSize& size) { return DIBBitmap(size, DataTypes::ARGB); }
DIBBitmap DIBBitmap::CreateRGBColor(const int& width, const int& height) { return DIBBitmap(RectangleSize(width, height), DataTypes::ARGB); }
DIBBitmap DIBBitmap::CreateGlayScale(const RectangleSize& size) { return DIBBitmap(size, DataTypes::GrayScale); }
DIBBitmap DIBBitmap::CreateGlayScale(const int& width, const int& height) { return DIBBitmap(RectangleSize(width, height), DataTypes::GrayScale); }
DIBBitmap DIBBitmap::CreateIndexedColor(const RectangleSize& size, const int& palsize) { return DIBBitmap(size, palsize); }
DIBBitmap DIBBitmap::CreateIndexedColor(const int& width, const int& height, const int& palsize) { return DIBBitmap(RectangleSize(width, height), palsize); }
DIBBitmap DIBBitmap::CreateIndexedColor(const RectangleSize& size, const std::vector<RGBTriple_t>& pal) { return DIBBitmap(size, pal); }
DIBBitmap DIBBitmap::CreateIndexedColor(const int& width, const int& height, const std::vector<RGBTriple_t>& pal) { return DIBBitmap(RectangleSize(width, height), pal); }
DIBBitmap DIBBitmap::FromStream(std::istream& stream)
{
	FileHeader fileheader;
	stream.read((char*)&fileheader, sizeof(FileHeader));
	if (!fileheader.CheckFileHeader()) { throw InvalidDIBFormatException("ファイルヘッダのファイルタイプ情報が無効です。"); }
	int32_t headersize;
	stream.read((char*)&headersize, sizeof(int32_t));
	switch (headersize)
	{
		case CoreHeader::Size:
		{
			CoreHeader header;
			stream.read((char*)&header, sizeof(CoreHeader));
			if (header.PlaneCount != 1) { throw InvalidDIBFormatException("指定されたプレーン数のビットマップはライブラリでサポートされていません。"); }
			stream.ignore(fileheader.Offset - sizeof(FileHeader) - CoreHeader::Size);
			switch (header.BitCount)
			{
			case BitDepth::Bit1: case BitDepth::Bit4: case BitDepth::Bit8:
				return readGray(stream, header.ImageWidth, header.ImageHeight, header.BitCount);
			case BitDepth::Bit24:
				return readRGB(stream, header.ImageWidth, header.ImageWidth, header.BitCount);
			default:
				throw InvalidDIBFormatException("ビット深度が無効です。");
			}
		}
		case InfoHeader::Size:
		{
			InfoHeader header;
			stream.read((char*)&header, sizeof(InfoHeader));
			if (header.PlaneCount != 1) { throw InvalidDIBFormatException("指定されたプレーン数のビットマップはライブラリでサポートされていません。"); }
			size_t readsize = sizeof(FileHeader) + InfoHeader::Size;
			// ビットマスクRGB画像の場合はマスク用ビットフィールドを取得
			ColorMask mask;
			if (header.ComplessionMethod == CompressionMethod::BITFIELDS)
			{
				RGBColorMask maskdata;
				stream.read((char*)&maskdata, sizeof(RGBColorMask));
				readsize += sizeof(RGBColorMask);
				mask = ColorMask{ BitMask<uint32_t>(maskdata.ColorMaskR), BitMask<uint32_t>(maskdata.ColorMaskG), BitMask<uint32_t>(maskdata.ColorMaskB), std::nullopt };
			}
			else if (header.ComplessionMethod == CompressionMethod::ALPHABITFIELDS)
			{
				RGBAColorMask maskdata;
				stream.read((char*)&maskdata, sizeof(RGBAColorMask));
				readsize += sizeof(RGBAColorMask);
				mask = ColorMask{ BitMask<uint32_t>(maskdata.ColorMaskR), BitMask<uint32_t>(maskdata.ColorMaskG), BitMask<uint32_t>(maskdata.ColorMaskB), BitMask<uint32_t>(maskdata.ColorMaskA) };
			}
			else { /* do nothing */ }
			/* TODO: カラーパレットの読み込みに対応する */
			stream.ignore(fileheader.Offset - readsize);
			DIBBitmap result;
			switch (header.ComplessionMethod)
			{
			case CompressionMethod::RGB:
				if (header.IndexedColorCount == 0)
				{
					switch (header.BitCount)
					{
					case BitDepth::Bit1: case BitDepth::Bit4: case BitDepth::Bit8:
						// グレースケール画像
						result = readGray(stream, header.ImageWidth, header.ImageHeight, header.BitCount);
					case BitDepth::Bit16: case BitDepth::Bit24: case BitDepth::Bit32:
						// RGBカラー画像
						result = readRGB(stream, header.ImageWidth, header.ImageHeight, header.BitCount);
						break;
					default:
						throw InvalidDIBFormatException("サポートされないビット深度が選択されました。");
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
				// ビットフィールドRGBカラー画像
				throw NotImplementedException();
			case CompressionMethod::JPEG:
				// JPEG圧縮画像
				throw NotImplementedException();
			case CompressionMethod::PNG:
				// PNG圧縮画像
				throw NotImplementedException();
			case CompressionMethod::ALPHABITFIELDS:
				// アルファ付きビットフィールドRGBカラー画像
				throw NotImplementedException();
			default:
				throw InvalidDIBFormatException("サポートされないビットマップ形式が選択されました。");
			}
			result._resh = header.ResolutionHolizonal;
			result._resv = header.ResolutionVertical;
			return result;
		}
		case V4Header::Size:
		{
			V4Header header;
			stream.read((char*)&header, sizeof(V4Header));
			if (header.PlaneCount != 1) { throw InvalidDIBFormatException("指定されたプレーン数のビットマップはライブラリでサポートされていません。"); }
			throw NotImplementedException();
		}
		case V5Header::Size:
		{
			V5Header header;
			stream.read((char*)&header, sizeof(V5Header));
			if (header.PlaneCount != 1) { throw InvalidDIBFormatException("指定されたプレーン数のビットマップはライブラリでサポートされていません。"); }
			throw NotImplementedException();
		}
		default:
		{ throw InvalidDIBFormatException("ヘッダサイズが無効です。"); }
	}
}
ARGBColor DIBBitmap::getIndex(const DIBBitmap& inst, const DisplayPoint& position)
{
	auto px = inst.BitmapBase::Index(position);
	RGBTriple_t index;
	switch (inst.DataType())
	{
		case DataTypes::ARGB:
		{ return ARGBColor(float(px[0]) / 255, float(px[1]) / 255, float(px[2]) / 255, float(px[3]) / 255); }
		case DataTypes::GrayScale:
		{
			// TODO: 輝度->RGB導出のアルゴリズム改善
			return ARGBColor(float(px[0]) / 255, float(px[0]) / 255, float(px[0]) / 255, float(px[0]) / 255);
		}
		case DataTypes::IndexedColor:
		{
			index = inst._cindex[px[0]];
			return ARGBColor(float(index.Red) / 255, float(index.Green) / 255, float(index.Blue) / 255);
		}
		default:
		{ throw InvalidOperationException("このオブジェクトの DataType が無効です。"); }
	}
}
void DIBBitmap::setIndex(DIBBitmap& inst, const DisplayPoint& position, const ARGBColor& value)
{
	auto px = inst.BitmapBase::Index(position);
	switch (inst.DataType())
	{
		case DataTypes::ARGB:
		{
			px[0] = uint8_t(value.R() * 255);
			px[1] = uint8_t(value.G() * 255);
			px[2] = uint8_t(value.B() * 255);
			px[3] = uint8_t(value.Alpha() * 255);
			return;
		}
		case DataTypes::GrayScale:
		{
			// TODO: RGB->輝度導出のアルゴリズム改善
			float lm = (value.R() + value.G() + value.B()) / 3;
			px[0] = uint8_t(lm * 255);
			return;
		}
		case DataTypes::IndexedColor:
		{
			uint8_t index = 0;
			float mindist;
			for (auto i : Range(0UL, inst._cindex.size()))
			{
			// TODO: 色差導出のアルゴリズム改善
				float dr = value.R() - 255.f * inst._cindex[i].Red;
				float dg = value.G() - 255.f * inst._cindex[i].Green;
				float db = value.B() - 255.f * inst._cindex[i].Blue;
				float dist = std::sqrt((dr * dr) + (dg * dg) + (db * db));
				if (dist < mindist)
				{
					mindist = dist;
					index = i;
				}
			}
			px[0] = index;
			return;
		}
		default: { throw InvalidOperationException("このオブジェクトの DataType が無効です。"); }
	}
}
DIBBitmap DIBBitmap::readGray(std::istream& stream, const int& width, const int& height, const BitDepth& bitdepth)
{
	if ((bitdepth!=BitDepth::Bit1)&&(bitdepth!=BitDepth::Bit4)&&(bitdepth!=BitDepth::Bit8)) { throw std::invalid_argument("サポートされない bitdepth を選択しました。"); }
	auto result = CreateGlayScale(width, height);
	auto readwidth = (size_t(bitdepth) / 8U) + (((size_t(bitdepth) % 8U) != 0)?1:0);
	auto yrange = result.YRange();
	auto xrange = result.XRange();
	auto yend = yrange.rend();
	for (auto y = yrange.rbegin(); y != yend; ++y)
	{
		for (auto x : xrange)
		{
			uint32_t readdata;
			stream.read((char*)&readdata, readwidth);
			auto px = result.BitmapBase::Index(x, *y);
			switch (bitdepth)
			{
				case BitDepth::Bit1:
				{
					px[0] = (readdata & 0x1) << 7;
					break;
				}
				case BitDepth::Bit4:
				{
					px[0] = (readdata & 0xF) << 4;
					break;
				}
				case BitDepth::Bit8:
				{
					px[0] = (readdata & 0xFF);
					break;
				}
				default:
				{ throw InvalidOperationException("到達できないコードに到達しました。 bitdepth の値が無効です。"); }
			}
		}
		auto padding = (4 - ((readwidth * width) % 4)) % 4;
		if (padding != 0) { stream.ignore(padding); }
	}
	return result;
}
DIBBitmap DIBBitmap::readRGB(std::istream& stream, const int& width, const int& height, const BitDepth& bitdepth)
{
	if ((bitdepth!=BitDepth::Bit16)&&(bitdepth!=BitDepth::Bit24)&&(bitdepth!=BitDepth::Bit32)) { throw std::invalid_argument("サポートされない bitdepth を選択しました。"); }
	auto result = CreateRGBColor(width, height);
	auto readwidth = (size_t(bitdepth) / 8U) + (((size_t(bitdepth) % 8U) != 0)?1:0);
	auto yrange = result.YRange();
	auto xrange = result.XRange();
	auto yend = yrange.rend();
	for (auto y = yrange.rbegin(); y != yend; ++y)
	{
		for (auto x : xrange)
		{
			uint32_t readdata;
			stream.read((char*)&readdata, readwidth);
			auto px = result.BitmapBase::Index(x, *y);
			switch (bitdepth)
			{
				case BitDepth::Bit16:
				{
					px[0] = (readdata & 0x7C00) >> 7;
					px[1] = (readdata & 0x03E0) >> 2;
					px[2] = (readdata & 0x001F) << 3;
					px[3] = 0;
					break;
				}
				case BitDepth::Bit24:
				{
					px[0] = (readdata & 0x00FF0000) >> 16;
					px[1] = (readdata & 0x0000FF00) >> 8;
					px[2] = (readdata & 0x000000FF);
					px[3] = 0;
					break;
				}
				case BitDepth::Bit32:
				{
					px[0] = (readdata & 0x00FF0000) >> 16;
					px[1] = (readdata & 0x0000FF00) >> 8;
					px[2] = (readdata & 0x000000FF);
					px[3] = 0;
					break;
				}
				default:
				{ throw InvalidOperationException("到達できないコードに到達しました。 bitdepth の値が無効です。"); }
			}
		}
		auto padding = (4 - ((readwidth * width) % 4)) % 4;
		if (padding != 0) { stream.ignore(padding); }
	}
	return result;
}
void DIBBitmap::writeRGB(std::ostream& stream, const BitDepth& depth) const
{
	auto bitdepth = (depth != BitDepth::Null)?depth:BitDepth::Bit24;
	if ((bitdepth != BitDepth::Bit16)&&(bitdepth != BitDepth::Bit24)&&(bitdepth != BitDepth::Bit32)) { throw std::invalid_argument("サポートされない depth を選択しました。"); }
	auto writewidth = (size_t(bitdepth) / 8U) + (((size_t(bitdepth) % 8U) != 0)?1:0);
	FileHeader fileheader;
	std::copy<const uint8_t*, uint8_t*>(&fileheader.FileType_Signature[0], &fileheader.FileType_Signature[2], &fileheader.FileType[0]);
	/* TODO: 状況に応じてV4ヘッダ/V5ヘッダを使用する */
	InfoHeader dataheader;
	fileheader.Offset = InfoHeader::Size + sizeof(FileHeader) + ((((InfoHeader::Size + sizeof(FileHeader))%4)!=0)?(4-(((InfoHeader::Size + sizeof(FileHeader))%4))):(0));
	dataheader.ImageHeight = Height();
	dataheader.ImageWidth = Width();
	dataheader.PlaneCount = 1;
	dataheader.BitCount = bitdepth;
	dataheader.ComplessionMethod = CompressionMethod::RGB;
	dataheader.ImageSize = (writewidth * Width());
	dataheader.ImageSize += ((dataheader.ImageSize % 4)!=0)?1:0;
	dataheader.ImageSize *= Height();
	dataheader.ResolutionHolizonal = _resh;
	dataheader.ResolutionVertical = _resv;
	dataheader.IndexedColorCount = 0;
	dataheader.ImportantColorCount = 0;
	fileheader.FileSize = fileheader.Offset + dataheader.ImageSize;
	size_t writesize = 0;
	stream.write((char*)&fileheader, sizeof(FileHeader));
	writesize += sizeof(FileHeader);
	stream.write((char*)&InfoHeader::Size, sizeof(uint32_t));
	stream.write((char*)&dataheader, sizeof(InfoHeader));
	writesize += InfoHeader::Size;
	for (auto item : Range<size_t>(0, fileheader.Offset - writesize)) { stream.put(char()); }
	auto yrange = YRange();
	auto xrange = XRange();
	auto y = yrange.rbegin();
	auto yend = yrange.rend();
	while (y != yend)
	{
		for (auto x : xrange)
		{
			auto px = BitmapBase::Index(x, *y);
			uint32_t writedata = 0;
			switch (bitdepth)
			{
				case BitDepth::Bit16:
				{
					writedata |= (uint32_t(px[0]) << 7) & 0x7C00;
					writedata |= (uint32_t(px[1]) << 2) & 0x03E0;
					writedata |= (uint32_t(px[2]) >> 3) & 0x001F;
					break;
				}
				case BitDepth::Bit24:
				{
					writedata |= (uint32_t(px[0]) << 16) & 0x00FF0000;
					writedata |= (uint32_t(px[1]) << 8) & 0x0000FF00;
					writedata |= (uint32_t(px[2])) & 0x000000FF;
					break;
				}
				case BitDepth::Bit32:
				{
					writedata |= (uint32_t(px[0]) << 16) & 0x00FF0000;
					writedata |= (uint32_t(px[1]) << 8) & 0x0000FF00;
					writedata |= (uint32_t(px[2])) & 0x000000FF;
					break;
				}
				default:
				{ throw InvalidOperationException("到達できないコードに到達しました。 bitdepth の値が無効です。"); }
			}
			stream.write((char*)&writedata, writewidth);
		}
		auto padding = (4 - ((writewidth * Width()) % 4)) % 4;
		for (auto i : Range(0UL, padding)) { stream.put(0); }
		++y;
	}
}
