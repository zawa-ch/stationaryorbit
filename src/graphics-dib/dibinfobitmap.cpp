//	stationaryorbit.graphics-dib:/dibinfobitmap
//	Copyright 2020 zawa-ch.
//	GPLv3 (or later) license
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//	See the GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program.
//	If not, see <http://www.gnu.org/licenses/>.
//
#include "stationaryorbit/graphics-dib/dibinfobitmap.hpp"
using namespace zawa_ch::StationaryOrbit;
using namespace zawa_ch::StationaryOrbit::Graphics::DIB;

DIBBitmapRGBDecoder::DIBBitmapRGBDecoder(DIBLoader& loader, size_t offset, DIBBitDepth bitdepth, const DisplayRectSize& size)
	: loader(loader), offset(offset), bitdepth(bitdepth), size(size), length(size.Width() * size.Height()), pixellength(DIBBitmapRGBEncoder::GetPxLength(bitdepth)), stridelength(DIBBitmapRGBEncoder::GetStrideLength(bitdepth, size))
{
	Reset();
}
bool DIBBitmapRGBDecoder::Next()
{
	if (IsAfterEnd()) { return false; }
	++current;
	if (IsAfterEnd()) { current = length; return false; }
	current_value = Get(current);
	return true;
}
bool DIBBitmapRGBDecoder::Next(const IteratorTraits::IteratorDiff_t& count)
{
	if (IsAfterEnd()) { return false; }
	current += count;
	if (IsAfterEnd()) { current = length; return false; }
	current_value = Get(current);
	return true;
}
bool DIBBitmapRGBDecoder::Previous()
{
	if (IsBeforeBegin()) { return false; }
	--current;
	if (IsBeforeBegin()) { current = -1; return false; }
	current_value = Get(current);
	return true;
}
bool DIBBitmapRGBDecoder::Previous(const IteratorTraits::IteratorDiff_t& count)
{
	if (IsBeforeBegin()) { return false; }
	current -= count;
	if (IsBeforeBegin()) { current = -1; return false; }
	current_value = Get(current);
	return true;
}
void DIBBitmapRGBDecoder::JumpTo(const DisplayPoint& pos)
{
	if ( (pos.X() < 0)||(pos.Y() < 0) ) { throw std::invalid_argument("posに指定されている座標が無効です。"); }
	current = ResolveIndex(pos);
	current_value = Get(ResolveIndex(pos));
}
void DIBBitmapRGBDecoder::Reset() { Reset(IteratorOrigin::Begin); }
void DIBBitmapRGBDecoder::Reset(const IteratorOrigin& origin)
{
	switch(origin)
	{
		default:
		case IteratorOrigin::Begin: { current = 0; break; }
		case IteratorOrigin::End: { current = length - 1; break; }
	}
	current_value = Get(current);
}
bool DIBBitmapRGBDecoder::HasValue() const { return (0 <= current)&&(current < length); }
bool DIBBitmapRGBDecoder::IsBeforeBegin() const { return current < 0; }
bool DIBBitmapRGBDecoder::IsAfterEnd() const { return length <= current; }
Graphics::DisplayPoint DIBBitmapRGBDecoder::CurrentPos() const { return ResolvePos(current); }
DIBBitmapRGBDecoder::ValueType DIBBitmapRGBDecoder::Current() const { if (HasValue()) { return current_value; } else { throw InvalidOperationException("このイテレータは領域の範囲外を指しています。"); } }
void DIBBitmapRGBDecoder::Write(const ValueType& value)
{
	size_t tgt = offset + ResolveOffset(current);
	switch(bitdepth)
	{
		case DIBBitDepth::Bit1: { DIBLoaderHelper::Write(loader, std::get<DIBPixelData<DIBBitDepth::Bit1>>(value), tgt); break; }
		case DIBBitDepth::Bit4: { DIBLoaderHelper::Write(loader, std::get<DIBPixelData<DIBBitDepth::Bit4>>(value), tgt); break; }
		case DIBBitDepth::Bit8: { DIBLoaderHelper::Write(loader, std::get<DIBPixelData<DIBBitDepth::Bit8>>(value), tgt); break; }
		case DIBBitDepth::Bit16: { DIBLoaderHelper::Write(loader, std::get<DIBPixelData<DIBBitDepth::Bit24>>(value), tgt); break; }
		case DIBBitDepth::Bit24: { DIBLoaderHelper::Write(loader, std::get<DIBPixelData<DIBBitDepth::Bit24>>(value), tgt); break; }
		case DIBBitDepth::Bit32: { DIBLoaderHelper::Write(loader, std::get<DIBPixelData<DIBBitDepth::Bit32>>(value), tgt); break; }
		default: { throw InvalidOperationException("情報ヘッダのBitCountの内容が無効です。"); }
	}
	current_value = value;
}
IteratorTraits::IteratorDiff_t DIBBitmapRGBDecoder::Distance(const DIBBitmapRGBDecoder& other) const { return current - other.current; }
bool DIBBitmapRGBDecoder::Equals(const DIBBitmapRGBDecoder& other) const { return current == other.current; }
int DIBBitmapRGBDecoder::Compare(const DIBBitmapRGBDecoder& other) const
{
	if (current == other.current) { return 0; }
	else if (other.current < current) { return 1; }
	else { return -1; }
}
DIBBitmapRGBDecoder::ValueType DIBBitmapRGBDecoder::Get(size_t index)
{
	size_t tgt = offset + ResolveOffset(index);
	switch(bitdepth)
	{
		case DIBBitDepth::Bit1:
		{
			auto result = DIBPixelData<DIBBitDepth::Bit1>();
			DIBLoaderHelper::Read(loader, result, tgt);
			return ValueType(result);
		}
		case DIBBitDepth::Bit4:
		{
			auto result = DIBPixelData<DIBBitDepth::Bit4>();
			DIBLoaderHelper::Read(loader, result, tgt);
			return ValueType(result);
		}
		case DIBBitDepth::Bit8:
		{
			auto result = DIBPixelData<DIBBitDepth::Bit8>();
			DIBLoaderHelper::Read(loader, result, tgt);
			return ValueType(result);
		}
		case DIBBitDepth::Bit16:
		{
			auto result = DIBPixelData<DIBBitDepth::Bit16>();
			DIBLoaderHelper::Read(loader, result, tgt);
			return ValueType(result);
		}
		case DIBBitDepth::Bit24:
		{
			auto result = DIBPixelData<DIBBitDepth::Bit24>();
			DIBLoaderHelper::Read(loader, result, tgt);
			return ValueType(result);
		}
		case DIBBitDepth::Bit32:
		{
			auto result = DIBPixelData<DIBBitDepth::Bit32>();
			DIBLoaderHelper::Read(loader, result, tgt);
			return ValueType(result);
		}
		default: { throw InvalidOperationException("情報ヘッダのBitCountの内容が無効です。"); }
	}
}
size_t DIBBitmapRGBDecoder::ResolveIndex(const DisplayPoint& pos) const { return ((size.Height() - 1 - pos.Y()) * size.Width()) + pos.X(); }
Graphics::DisplayPoint DIBBitmapRGBDecoder::ResolvePos(size_t index) const { return DisplayPoint(index % size.Width(), size.Height() - 1 - (index / size.Width())); }
size_t DIBBitmapRGBDecoder::ResolveOffset(const DisplayPoint& pos) const
{
	if ( (pos.X() < 0)||(pos.Y() < 0) ) { throw std::invalid_argument("posに指定されている座標が無効です。"); }
	if ( (size.Width() <= pos.X())||(size.Height() <= pos.Y()) ) { throw std::out_of_range("指定された座標はこの画像領域を超えています。"); }
	return (stridelength * (size.Height() - 1 - pos.Y())) + (pixellength * pos.X());
}
size_t DIBBitmapRGBDecoder::ResolveOffset(size_t index) const
{
	if (length <= index) { throw std::out_of_range("指定されたインデックスはこの画像領域を超えています。"); }
	return (stridelength * (index / size.Width())) + (pixellength * (index % size.Width()));
}

DIBBitmapRGBEncoder::DIBBitmapRGBEncoder(DIBLoader& loader, size_t offset, DIBBitDepth bitdepth, const DisplayRectSize& size)
	: loader(loader), offset(offset), bitdepth(bitdepth), size(size), length(size.Width() * size.Height()), current(0), pixellength(GetPxLength(bitdepth)), stridelength(GetStrideLength(bitdepth, size))
{}
void DIBBitmapRGBEncoder::Write(const ValueType& value)
{
	size_t tgt = offset + ResolveOffset(ResolvePos(current));
	switch(bitdepth)
	{
		case DIBBitDepth::Bit1: { DIBLoaderHelper::Write(loader, std::get<DIBPixelData<DIBBitDepth::Bit1>>(value), tgt); break; }
		case DIBBitDepth::Bit4: { DIBLoaderHelper::Write(loader, std::get<DIBPixelData<DIBBitDepth::Bit4>>(value), tgt); break; }
		case DIBBitDepth::Bit8: { DIBLoaderHelper::Write(loader, std::get<DIBPixelData<DIBBitDepth::Bit8>>(value), tgt); break; }
		case DIBBitDepth::Bit16: { DIBLoaderHelper::Write(loader, std::get<DIBPixelData<DIBBitDepth::Bit16>>(value), tgt); break; }
		case DIBBitDepth::Bit24: { DIBLoaderHelper::Write(loader, std::get<DIBPixelData<DIBBitDepth::Bit24>>(value), tgt); break; }
		case DIBBitDepth::Bit32: { DIBLoaderHelper::Write(loader, std::get<DIBPixelData<DIBBitDepth::Bit32>>(value), tgt); break; }
		default: { throw InvalidOperationException("情報ヘッダのBitCountの内容が無効です。"); }
	}
	if (CurrentPos().X() == (size.Width() - 1))
	{
		size_t ci = size.Width() * pixellength;
		for (auto i: Range<size_t>(ci, stridelength).GetStdIterator()) { DIBLoaderHelper::Write(loader, char(), offset + i); }
	}
	++current;
}
void DIBBitmapRGBEncoder::Reset() { current = 0; }
bool DIBBitmapRGBEncoder::HasValue() const { return (0 <= current)&&(current < length); }
Graphics::DisplayPoint DIBBitmapRGBEncoder::CurrentPos() const { return ResolvePos(current); }
bool DIBBitmapRGBEncoder::Equals(const DIBBitmapRGBEncoder& other) const { return current == other.current; }
int DIBBitmapRGBEncoder::Compare(const DIBBitmapRGBEncoder& other) const 
{
	if (current == other.current) { return 0; }
	else if (other.current < current) { return 1; }
	else { return -1; }
}
size_t DIBBitmapRGBEncoder::ResolveIndex(const DisplayPoint& pos) const { return ((size.Height() - 1 - pos.Y()) * size.Width()) + pos.X(); }
Graphics::DisplayPoint DIBBitmapRGBEncoder::ResolvePos(size_t index) const { return DisplayPoint(index % size.Width(), size.Height() - 1 - (index / size.Width())); }
size_t DIBBitmapRGBEncoder::ResolveOffset(const DisplayPoint& pos) const
{
	if ( (pos.X() < 0)||(pos.Y() < 0) ) { throw std::invalid_argument("posに指定されている座標が無効です。"); }
	if ( (size.Width() <= pos.X())||(size.Height() <= pos.Y()) ) { throw std::out_of_range("指定された座標はこの画像領域を超えています。"); }
	return (stridelength * (size.Height() - 1 - pos.Y())) + (pixellength * pos.X());
}
size_t DIBBitmapRGBEncoder::GetPxLength(DIBBitDepth bitdepth) { return (uint16_t(bitdepth) + 7) / 8; }
size_t DIBBitmapRGBEncoder::GetStrideLength(DIBBitDepth bitdepth, const DisplayRectSize& size) { return (((GetPxLength(bitdepth) * size.Width()) + 3) / 4) * 4; }
size_t DIBBitmapRGBEncoder::GetImageLength(DIBBitDepth bitdepth, const DisplayRectSize& size) { return GetStrideLength(bitdepth, size) * size.Height(); }

DIBInfoBitmap::DIBInfoBitmap(DIBLoader&& loader) : loader(std::forward<DIBLoader>(loader))
{
	if (!this->loader.IsEnable()) { throw InvalidOperationException("無効な状態のloaderが渡されました。"); }
	if (this->loader.HeaderSize() < DIBInfoHeader::Size) { throw InvalidDIBFormatException("情報ヘッダの長さはInfoHeaderでサポートされる最小の長さよりも短いです。"); }
	DIBLoaderHelper::Read(this->loader, &ihead, sizeof(DIBFileHeader) + sizeof(int32_t));
	if (ihead.ComplessionMethod == BMPCompressionMethod::BITFIELDS)
	{
		auto colormaskdata = DIBRGBColorMask();
		DIBLoaderHelper::Read(this->loader, colormaskdata, sizeof(DIBFileHeader) + DIBInfoHeader::Size);
		colormask = DIBColorMask(colormaskdata);
	}
	else if (ihead.ComplessionMethod == BMPCompressionMethod::ALPHABITFIELDS)
	{
		auto colormaskdata = DIBRGBAColorMask();
		DIBLoaderHelper::Read(this->loader, colormaskdata, sizeof(DIBFileHeader) + DIBInfoHeader::Size);
		colormask = DIBColorMask(colormaskdata);
	}
	if ((ihead.ComplessionMethod == BMPCompressionMethod::RGB)&&(uint16_t(ihead.BitCount) <= uint16_t(DIBBitDepth::Bit8)))
	{
		size_t palsize = ihead.IndexedColorCount;
		if (palsize == 0) { palsize = 1 << uint16_t(ihead.BitCount); }
		auto lpal = std::vector<RGBQuad_t>(palsize);
		DIBLoaderHelper::Read(this->loader, lpal.data(), sizeof(DIBFileHeader) + sizeof(DIBInfoHeader), palsize);
		palette.reserve(palsize);
		for(auto i: lpal) { palette.push_back(RGB8_t(i)); }
	}
}
std::optional<std::reference_wrapper<const DIBColorMask>> DIBInfoBitmap::ColorMask() const
{
	switch(ihead.ComplessionMethod)
	{
		case BMPCompressionMethod::BITFIELDS:
		case BMPCompressionMethod::ALPHABITFIELDS:
		{ return colormask; }
		case BMPCompressionMethod::RGB:
		case BMPCompressionMethod::RLE4:
		case BMPCompressionMethod::RLE8:
		case BMPCompressionMethod::JPEG:
		case BMPCompressionMethod::PNG:
		{ return std::nullopt; }
		default: { throw InvalidOperationException("情報ヘッダのComplessionMethodの内容が無効です。"); }
	}
}
std::optional<std::reference_wrapper<const std::vector<Graphics::RGB8_t>>> DIBInfoBitmap::Palette() const
{
	if (ihead.IndexedColorCount != 0) { return palette; }
	else { return std::nullopt; }
}
DIBInfoBitmap::ValueType DIBInfoBitmap::GetPixel(const DisplayPoint& pos)
{
	switch(ihead.ComplessionMethod)
	{
		case BMPCompressionMethod::RGB:
		{
			auto decoder = DIBBitmapRGBDecoder(loader, loader.FileHead().Offset(), ihead.BitCount, DisplayRectSize(ihead.ImageWidth, ihead.ImageHeight));
			decoder.JumpTo(pos);
			return ConvertToRGB(decoder.Current());
			break;
		}
		case BMPCompressionMethod::RLE4:
		case BMPCompressionMethod::RLE8:
		case BMPCompressionMethod::BITFIELDS:
		case BMPCompressionMethod::JPEG:
		case BMPCompressionMethod::PNG:
		case BMPCompressionMethod::ALPHABITFIELDS:
		//	TODO: Implement
		{ throw NotImplementedException(); }
		default: { throw InvalidOperationException("情報ヘッダのComplessionMethodの内容が無効です。"); }
	}
}
std::vector<DIBInfoBitmap::ValueType> DIBInfoBitmap::GetPixel(const DisplayPoint& pos, size_t count)
{
	switch(ihead.ComplessionMethod)
	{
		case BMPCompressionMethod::RGB:
		{
			auto decoder = DIBBitmapRGBDecoder(loader, loader.FileHead().Offset(), ihead.BitCount, DisplayRectSize(ihead.ImageWidth, ihead.ImageHeight));
			decoder.JumpTo(pos);
			auto result = std::vector<DIBInfoBitmap::ValueType>();
			result.reserve(count);
			for (auto _: Range<size_t>(0, count).GetStdIterator()) { result.push_back(ConvertToRGB(decoder.Current())); }
			return result;
		}
		case BMPCompressionMethod::RLE4:
		case BMPCompressionMethod::RLE8:
		case BMPCompressionMethod::BITFIELDS:
		case BMPCompressionMethod::JPEG:
		case BMPCompressionMethod::PNG:
		case BMPCompressionMethod::ALPHABITFIELDS:
		//	TODO: Implement
		{ throw NotImplementedException(); }
		default: { throw InvalidOperationException("情報ヘッダのComplessionMethodの内容が無効です。"); }
	}
}
void DIBInfoBitmap::SetPixel(const DisplayPoint& pos, const ValueType& value)
{
	switch(ihead.ComplessionMethod)
	{
		case BMPCompressionMethod::RGB:
		{
			auto decoder = DIBBitmapRGBDecoder(loader, loader.FileHead().Offset(), ihead.BitCount, DisplayRectSize(ihead.ImageWidth, ihead.ImageHeight));
			decoder.JumpTo(pos);
			decoder.Write(ConvertToRGBDecoderValue(value));
			break;
		}
		case BMPCompressionMethod::RLE4: { throw InvalidOperationException("現在のComplessionMethodでの書き込みはサポートされていません。"); }
		case BMPCompressionMethod::RLE8: { throw InvalidOperationException("現在のComplessionMethodでの書き込みはサポートされていません。"); }
		case BMPCompressionMethod::BITFIELDS:
		//	TODO: Implement
		{ throw NotImplementedException(); }
		case BMPCompressionMethod::JPEG: { throw InvalidOperationException("現在のComplessionMethodでの書き込みはサポートされていません。"); }
		case BMPCompressionMethod::PNG: { throw InvalidOperationException("現在のComplessionMethodでの書き込みはサポートされていません。"); }
		case BMPCompressionMethod::ALPHABITFIELDS:
		//	TODO: Implement
		{ throw NotImplementedException(); }
		default: { throw InvalidOperationException("情報ヘッダのComplessionMethodの内容が無効です。"); }
	}
}
void DIBInfoBitmap::SetPixel(const DisplayPoint& pos, const std::vector<ValueType>& value)
{
	switch(ihead.ComplessionMethod)
	{
		case BMPCompressionMethod::RGB:
		{
			auto decoder = DIBBitmapRGBDecoder(loader, loader.FileHead().Offset(), ihead.BitCount, DisplayRectSize(ihead.ImageWidth, ihead.ImageHeight));
			decoder.JumpTo(pos);
			for(auto i: value) { decoder.Write(ConvertToRGBDecoderValue(i)); }
			break;
		}
		case BMPCompressionMethod::RLE4: { throw InvalidOperationException("現在のComplessionMethodでの書き込みはサポートされていません。"); }
		case BMPCompressionMethod::RLE8: { throw InvalidOperationException("現在のComplessionMethodでの書き込みはサポートされていません。"); }
		case BMPCompressionMethod::BITFIELDS:
		//	TODO: Implement
		{ throw NotImplementedException(); }
		case BMPCompressionMethod::JPEG: { throw InvalidOperationException("現在のComplessionMethodでの書き込みはサポートされていません。"); }
		case BMPCompressionMethod::PNG: { throw InvalidOperationException("現在のComplessionMethodでの書き込みはサポートされていません。"); }
		case BMPCompressionMethod::ALPHABITFIELDS:
		//	TODO: Implement
		{ throw NotImplementedException(); }
		default: { throw InvalidOperationException("情報ヘッダのComplessionMethodの内容が無効です。"); }
	}
}
DIBInfoBitmap::RawDataType DIBInfoBitmap::GetPixelRaw(const DisplayPoint& pos)
{
	switch(ihead.ComplessionMethod)
	{
		case BMPCompressionMethod::RGB:
		case BMPCompressionMethod::BITFIELDS:
		case BMPCompressionMethod::ALPHABITFIELDS:
		{
			auto decoder = DIBBitmapRGBDecoder(loader, loader.FileHead().Offset(), ihead.BitCount, DisplayRectSize(ihead.ImageWidth, ihead.ImageHeight));
			decoder.JumpTo(pos);
			return ConvertToRawData(decoder.Current());
		}
		case BMPCompressionMethod::RLE4:
		case BMPCompressionMethod::RLE8:
		case BMPCompressionMethod::JPEG:
		case BMPCompressionMethod::PNG:
		//	TODO: Implement
		{ throw NotImplementedException(); }
		default: { throw InvalidOperationException("情報ヘッダのComplessionMethodの内容が無効です。"); }
	}
}
std::vector<DIBInfoBitmap::RawDataType> DIBInfoBitmap::GetPixelRaw(const DisplayPoint& pos, size_t count)
{
	switch(ihead.ComplessionMethod)
	{
		case BMPCompressionMethod::RGB:
		case BMPCompressionMethod::BITFIELDS:
		case BMPCompressionMethod::ALPHABITFIELDS:
		{
			auto decoder = DIBBitmapRGBDecoder(loader, loader.FileHead().Offset(), ihead.BitCount, DisplayRectSize(ihead.ImageWidth, ihead.ImageHeight));
			decoder.JumpTo(pos);
			auto result = std::vector<RawDataType>();
			result.reserve(count);
			for (auto _: Range<size_t>(0, count).GetStdIterator()) { result.push_back(ConvertToRawData(decoder.Current())); }
			return result;
		}
		case BMPCompressionMethod::RLE4:
		case BMPCompressionMethod::RLE8:
		case BMPCompressionMethod::JPEG:
		case BMPCompressionMethod::PNG:
		//	TODO: Implement
		{ throw NotImplementedException(); }
		default: { throw InvalidOperationException("情報ヘッダのComplessionMethodの内容が無効です。"); }
	}
}
void DIBInfoBitmap::SetPixelRaw(const DisplayPoint& pos, const RawDataType& value)
{
	switch(ihead.ComplessionMethod)
	{
		case BMPCompressionMethod::RGB:
		case BMPCompressionMethod::BITFIELDS:
		case BMPCompressionMethod::ALPHABITFIELDS:
		{
			auto decoder = DIBBitmapRGBDecoder(loader, loader.FileHead().Offset(), ihead.BitCount, DisplayRectSize(ihead.ImageWidth, ihead.ImageHeight));
			decoder.JumpTo(pos);
			decoder.Write(ConvertToRGBDecoderValue(value));
			break;
		}
		case BMPCompressionMethod::RLE4: { throw InvalidOperationException("現在のComplessionMethodでの書き込みはサポートされていません。"); }
		case BMPCompressionMethod::RLE8: { throw InvalidOperationException("現在のComplessionMethodでの書き込みはサポートされていません。"); }
		case BMPCompressionMethod::JPEG: { throw InvalidOperationException("現在のComplessionMethodでの書き込みはサポートされていません。"); }
		case BMPCompressionMethod::PNG: { throw InvalidOperationException("現在のComplessionMethodでの書き込みはサポートされていません。"); }
		default: { throw InvalidOperationException("情報ヘッダのComplessionMethodの内容が無効です。"); }
	}
}
void DIBInfoBitmap::SetPixelRaw(const DisplayPoint& pos, const std::vector<RawDataType>& value)
{
	switch(ihead.ComplessionMethod)
	{
		case BMPCompressionMethod::RGB:
		case BMPCompressionMethod::BITFIELDS:
		case BMPCompressionMethod::ALPHABITFIELDS:
		{
			auto decoder = DIBBitmapRGBDecoder(loader, loader.FileHead().Offset(), ihead.BitCount, DisplayRectSize(ihead.ImageWidth, ihead.ImageHeight));
			decoder.JumpTo(pos);
			for(auto i: value) { decoder.Write(ConvertToRGBDecoderValue(i)); }
			break;
		}
		case BMPCompressionMethod::RLE4: { throw InvalidOperationException("現在のComplessionMethodでの書き込みはサポートされていません。"); }
		case BMPCompressionMethod::RLE8: { throw InvalidOperationException("現在のComplessionMethodでの書き込みはサポートされていません。"); }
		case BMPCompressionMethod::JPEG: { throw InvalidOperationException("現在のComplessionMethodでの書き込みはサポートされていません。"); }
		case BMPCompressionMethod::PNG: { throw InvalidOperationException("現在のComplessionMethodでの書き込みはサポートされていません。"); }
		default: { throw InvalidOperationException("情報ヘッダのComplessionMethodの内容が無効です。"); }
	}
}
void DIBInfoBitmap::CopyTo(WritableImage<RGB8_t>& dest)
{
	switch(ihead.ComplessionMethod)
	{
		case BMPCompressionMethod::RGB:
		{
			auto decoder = DIBBitmapRGBDecoder(loader, loader.FileHead().Offset(), ihead.BitCount, DisplayRectSize(ihead.ImageWidth, ihead.ImageHeight));
			for (decoder.Reset(); decoder.HasValue(); decoder.Next()) { dest.At(decoder.CurrentPos()) = ConvertToRGB(decoder.Current()); }
			break;
		}
		case BMPCompressionMethod::RLE4:
		case BMPCompressionMethod::RLE8:
		case BMPCompressionMethod::BITFIELDS:
		case BMPCompressionMethod::JPEG:
		case BMPCompressionMethod::PNG:
		case BMPCompressionMethod::ALPHABITFIELDS:
		//	TODO: Implement
		{ throw NotImplementedException(); }
		default: { throw InvalidOperationException("情報ヘッダのComplessionMethodの内容が無効です。"); }
	}
}
void DIBInfoBitmap::CopyTo(WritableImage<RGB8_t>& dest, const DisplayRectangle& area, const DisplayPoint& destorigin)
{
	if ((area.Left() < 0)||(area.Top() < 0)||(ihead.ImageWidth < area.Right())||(ihead.ImageHeight < area.Bottom())) { throw std::out_of_range("areaで指定された領域がビットマップの画像領域を超えています。"); }
	switch(ihead.ComplessionMethod)
	{
		case BMPCompressionMethod::RGB:
		{
			auto decoder = DIBBitmapRGBDecoder(loader, loader.FileHead().Offset(), ihead.BitCount, DisplayRectSize(ihead.ImageWidth, ihead.ImageHeight));
			for (decoder.JumpTo(DisplayPoint(area.Left(), area.Bottom())); decoder.HasValue(); decoder.Next())
			{
				if (area.Contains(decoder.CurrentPos())) { decoder.Next(ihead.ImageWidth - area.Width() - 1); continue; }
				dest.At(decoder.CurrentPos() - area.Origin() + destorigin) = ConvertToRGB(decoder.Current());
			}
			break;
		}
		case BMPCompressionMethod::RLE4:
		case BMPCompressionMethod::RLE8:
		case BMPCompressionMethod::BITFIELDS:
		case BMPCompressionMethod::JPEG:
		case BMPCompressionMethod::PNG:
		case BMPCompressionMethod::ALPHABITFIELDS:
		//	TODO: Implement
		{ throw NotImplementedException(); }
		default: { throw InvalidOperationException("情報ヘッダのComplessionMethodの内容が無効です。"); }
	}
}
DIBInfoBitmap::Pixmap DIBInfoBitmap::ToPixmap()
{
	auto result = Pixmap(DisplayRectSize(ihead.ImageWidth, ihead.ImageHeight));
	CopyTo(result);
	return result;
}
DIBInfoBitmap::Pixmap DIBInfoBitmap::ToPixmap(const DisplayRectangle& area)
{
	auto result = Pixmap(area.Size());
	CopyTo(result, area);
	return result;
}
std::optional<DIBInfoBitmap> DIBInfoBitmap::Generate(DIBLoader&& loader, const DIBInfoHeader& header, const Image<RGB8_t>& image) { return Generate(std::forward<DIBLoader>(loader), header, std::vector<RGB8_t>(), image); }
std::optional<DIBInfoBitmap> DIBInfoBitmap::Generate(DIBLoader&& loader, const DIBInfoHeader& header, const std::vector<RGB8_t> palette, const Image<RGB8_t>& image)
{
	auto fhead = DIBFileHeader();
	std::copy(&(fhead.FileType_Signature[0]), &(fhead.FileType_Signature[2]), &(fhead.FileType[0]));
	switch(header.ComplessionMethod)
	{
		case BMPCompressionMethod::RGB:
		{
			size_t palsize;
			switch(header.BitCount)
			{
				case DIBBitDepth::Bit1:
				case DIBBitDepth::Bit4:
				case DIBBitDepth::Bit8:
				{
					throw NotImplementedException();
					palsize = header.IndexedColorCount;
					if (palsize == 0) { palsize = 1 << uint16_t(header.BitCount); }
					if ((1 << uint16_t(header.BitCount)) < palsize) { throw std::invalid_argument("biClrUsedの値が指定されたbiBitCountでサポートされている値を超えています。"); }
					break;
				}
				case DIBBitDepth::Bit16:
				case DIBBitDepth::Bit24:
				case DIBBitDepth::Bit32:
				{ palsize = 0; break; }
				default: { throw std::invalid_argument("BitCountの内容が無効です。"); }
			}
			fhead.Offset(int32_t(sizeof(DIBFileHeader) + DIBInfoHeader::Size) + (sizeof(RGBQuad_t) * palsize));
			fhead.FileSize(int32_t(sizeof(DIBFileHeader) + DIBInfoHeader::Size + (sizeof(RGBQuad_t) * palsize) + (DIBBitmapRGBEncoder::GetStrideLength(header.BitCount, DisplayRectSize(header.ImageWidth, header.ImageHeight)) * header.ImageHeight)));
			DIBLoaderHelper::Write(loader, fhead, 0);
			DIBLoaderHelper::Write(loader, DIBInfoHeader::Size, sizeof(DIBFileHeader));
			DIBLoaderHelper::Write(loader, header, sizeof(DIBFileHeader) + sizeof(uint32_t));
			for (auto i: Range<size_t>(0, palsize).GetStdIterator())
			{
				if (palette.size() < i) { DIBLoaderHelper::Write(loader, RGBQuad_t(palette[i]), sizeof(DIBFileHeader) + DIBInfoHeader::Size + (sizeof(RGBQuad_t) * i)); }
				else { DIBLoaderHelper::Write(loader, RGBQuad_t(), sizeof(DIBFileHeader) + DIBInfoHeader::Size + (sizeof(RGBQuad_t) * i)); }
			}
			auto encoder = DIBBitmapRGBEncoder(loader, fhead.Offset(), header.BitCount, DisplayRectSize(header.ImageWidth, header.ImageHeight));
			switch(header.BitCount)
			{
				case DIBBitDepth::Bit1: { while (encoder.HasValue()) { encoder.Write(DIBPixelData<DIBBitDepth::Bit1>()); } break; }
				case DIBBitDepth::Bit4: { while (encoder.HasValue()) { encoder.Write(DIBPixelData<DIBBitDepth::Bit4>()); } break; }
				case DIBBitDepth::Bit8: { while (encoder.HasValue()) { encoder.Write(DIBPixelData<DIBBitDepth::Bit8>()); } break; }
				case DIBBitDepth::Bit16: { while (encoder.HasValue()) { encoder.Write(DIBPixelPerser::ToPixel16(image.At(encoder.CurrentPos()))); } break; }
				case DIBBitDepth::Bit24: { while (encoder.HasValue()) { encoder.Write(DIBPixelPerser::ToPixel24(image.At(encoder.CurrentPos()))); } break; }
				case DIBBitDepth::Bit32: { while (encoder.HasValue()) { encoder.Write(DIBPixelPerser::ToPixel32(image.At(encoder.CurrentPos()))); } break; }
				default: { throw std::invalid_argument("BitCountの内容が無効です。"); }
			}
			try
			{
				loader.Sync();
				return DIBInfoBitmap(std::forward<DIBLoader>(loader));
			}
			catch (std::exception e)
			{
				return std::nullopt;
			}
		}
		case BMPCompressionMethod::RLE8:
		case BMPCompressionMethod::RLE4:
		case BMPCompressionMethod::BITFIELDS:
		case BMPCompressionMethod::JPEG:
		case BMPCompressionMethod::PNG:
		case BMPCompressionMethod::ALPHABITFIELDS:
		{ throw NotImplementedException(); }
		default: { throw std::invalid_argument("CompressionMethodの内容が無効です。"); }
	}
}
DIBInfoBitmap::ValueType DIBInfoBitmap::ConvertToRGB(const DIBBitmapRGBDecoder::ValueType& data) const
{
	switch(ihead.ComplessionMethod)
	{
		case BMPCompressionMethod::RGB:
			switch(ihead.BitCount)
			{
				case DIBBitDepth::Bit1:
				case DIBBitDepth::Bit4:
				case DIBBitDepth::Bit8:
				{
					return palette.at(std::visit([](auto i)->uint32_t { return uint32_t(i); }, data));
				}
				case DIBBitDepth::Bit16: { return DIBPixelPerser::ToRGB(std::get<DIBPixelData<DIBBitDepth::Bit16>>(data)); }
				case DIBBitDepth::Bit24: { return DIBPixelPerser::ToRGB(std::get<DIBPixelData<DIBBitDepth::Bit24>>(data)); }
				case DIBBitDepth::Bit32: { return DIBPixelPerser::ToRGB(std::get<DIBPixelData<DIBBitDepth::Bit32>>(data)); }
				default: { throw InvalidDIBFormatException("情報ヘッダのBitCountの内容が無効です。"); }
			}
			break;
		case BMPCompressionMethod::BITFIELDS:
		case BMPCompressionMethod::ALPHABITFIELDS:
		//	TODO: Implement
		{ throw NotImplementedException(); }
		case BMPCompressionMethod::RLE8:
		case BMPCompressionMethod::RLE4:
		case BMPCompressionMethod::JPEG:
		case BMPCompressionMethod::PNG:
		default: { throw InvalidOperationException("情報ヘッダのComressionMethodの内容が無効です。"); }
	}
}
DIBInfoBitmap::RawDataType DIBInfoBitmap::ConvertToRawData(const DIBBitmapRGBDecoder::ValueType& data) const
{
	switch(ihead.BitCount)
	{
		case DIBBitDepth::Bit1:
		case DIBBitDepth::Bit4:
		case DIBBitDepth::Bit8:
		case DIBBitDepth::Bit16:
		case DIBBitDepth::Bit24:
		case DIBBitDepth::Bit32:
		{
			return std::visit([](auto i)->RawDataType { return RawDataType(i); }, data);
		}
		default: { throw InvalidDIBFormatException("情報ヘッダのBitCountの内容が無効です。"); }
	}
}
DIBBitmapRGBDecoder::ValueType DIBInfoBitmap::ConvertToRGBDecoderValue(const ValueType& value) const
{
	switch(ihead.ComplessionMethod)
	{
		case BMPCompressionMethod::RGB:
			switch(ihead.BitCount)
			{
				case DIBBitDepth::Bit1:
				case DIBBitDepth::Bit4:
				case DIBBitDepth::Bit8:
				//	TODO: Implement
				{ throw NotImplementedException(); }
				case DIBBitDepth::Bit16: { return DIBPixelPerser::ToPixel16(value); }
				case DIBBitDepth::Bit24: { return DIBPixelPerser::ToPixel24(value); }
				case DIBBitDepth::Bit32: { return DIBPixelPerser::ToPixel32(value); }
				default: { throw InvalidOperationException("情報ヘッダのBitCountの内容が無効です。"); }
			}
			break;
		case BMPCompressionMethod::BITFIELDS:
		case BMPCompressionMethod::ALPHABITFIELDS:
		//	TODO: Implement
		{ throw NotImplementedException(); }
		case BMPCompressionMethod::RLE8:
		case BMPCompressionMethod::RLE4:
		case BMPCompressionMethod::JPEG:
		case BMPCompressionMethod::PNG:
		default: { throw InvalidOperationException("情報ヘッダのComressionMethodの内容が無効です。"); }
	}
}
DIBBitmapRGBDecoder::ValueType DIBInfoBitmap::ConvertToRGBDecoderValue(const RawDataType& value) const
{
	switch(ihead.BitCount)
	{
		case DIBBitDepth::Bit1: { return DIBPixelData<DIBBitDepth::Bit1>(value); }
		case DIBBitDepth::Bit4: { return DIBPixelData<DIBBitDepth::Bit4>(value); }
		case DIBBitDepth::Bit8: { return DIBPixelData<DIBBitDepth::Bit8>(value); }
		case DIBBitDepth::Bit16: { return DIBPixelData<DIBBitDepth::Bit16>(value); }
		case DIBBitDepth::Bit24: { return DIBPixelData<DIBBitDepth::Bit24>(value); }
		case DIBBitDepth::Bit32: { return DIBPixelData<DIBBitDepth::Bit32>(value); }
		default: { throw InvalidOperationException("情報ヘッダのBitCountの内容が無効です。"); }
	}
}
