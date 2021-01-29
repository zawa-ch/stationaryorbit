//	stationaryorbit.graphics-dib:/dibloader
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
#include "stationaryorbit/graphics-dib/dibloader.hpp"
using namespace zawa_ch::StationaryOrbit;
using namespace zawa_ch::StationaryOrbit::Graphics::DIB;

DIBFileLoader::DIBFileLoader() : stream(), fhead(), headersize() {}
DIBFileLoader::DIBFileLoader(std::fstream&& stream) : stream(std::move(stream)), fhead(), headersize() { Reload(); }
DIBFileLoader::DIBFileLoader(const char* filename, std::ios_base::openmode mode) : DIBFileLoader(std::move(std::fstream(filename, mode))) {}
DIBFileLoader::DIBFileLoader(const std::string& filename, std::ios_base::openmode mode) : DIBFileLoader(std::move(std::fstream(filename, mode))) {}
bool DIBFileLoader::IsEnable() const { return fhead.CheckFileHeader(); }
void DIBFileLoader::Reload()
{
	//	ストリームの状態を確認、利用できない場合は処理を終了
	if (stream.bad()) { return; }
	//	読み取り準備
	auto sentry = std::istream::sentry(stream, true);
	if (!sentry) { return; }
	//	ファイル先頭へシーク、できなければ std::fstream::failure をスロー
	if (stream.seekg(0).fail()) { stream.clear(); throw std::fstream::failure("ストリームのシークに失敗しました。"); }
	//	ファイルヘッダ・情報ヘッダサイズを読み取り
	if (stream.read((char*)&fhead, sizeof(DIBFileHeader)).fail()) { stream.clear(); return; }
	if (stream.read((char*)&headersize, sizeof(int32_t)).fail()) { stream.clear(); return; }
}
void DIBFileLoader::Read(char* dest, size_t pos, size_t length)
{
	if (stream.bad()) { throw InvalidOperationException("ストリームの状態が無効です。"); }
	auto sentry = std::istream::sentry(stream, true);
	if (!sentry) { throw std::ios_base::failure("ストリームの準備に失敗しました。"); }
	if (stream.seekg(pos).fail()) { stream.clear(); throw std::ios_base::failure("ストリームのシークに失敗しました。"); }
	if (stream.read(dest, length).fail())
	{
		if (stream.eof()) { stream.clear(); throw InvalidDIBFormatException("データの読み取り中にストリーム終端に到達しました。"); }
		stream.clear();
		throw std::ios_base::failure("ストリームの読み取りに失敗しました。");
	}
}
void DIBFileLoader::Write(const char* source, size_t pos, size_t length)
{
	if (stream.bad()) { throw InvalidOperationException("ストリームの状態が無効です。"); }
	auto sentry = std::ostream::sentry(stream);
	if (!sentry) { throw std::ios_base::failure("ストリームの準備に失敗しました。"); }
	if (stream.seekp(pos).fail()) { stream.clear(); throw std::ios_base::failure("ストリームのシークに失敗しました。"); }
	if (stream.write(source, length).fail()) { stream.clear(); throw std::ios_base::failure("ストリームの書き込みに失敗しました。"); }
}

DIBCoreBitmapDecoder::DIBCoreBitmapDecoder(DIBLoader& loader, size_t offset, DIBBitDepth bitdepth, const DisplayRectSize& size)
	: loader(loader), offset(offset), bitdepth(bitdepth), size(size), length(size.Width() * size.Height())
{
	Reset();
}
bool DIBCoreBitmapDecoder::Next()
{
	if (IsAfterEnd()) { return false; }
	++current;
	if (IsAfterEnd()) { current = length; return false; }
	current_value = Get(ResolvePos(current));
	return true;
}
bool DIBCoreBitmapDecoder::Next(const IteratorTraits::IteratorDiff_t& count)
{
	if (IsAfterEnd()) { return false; }
	current += count;
	if (IsAfterEnd()) { current = length; return false; }
	current_value = Get(ResolvePos(current));
	return true;
}
bool DIBCoreBitmapDecoder::Previous()
{
	if (IsBeforeBegin()) { return false; }
	--current;
	if (IsBeforeBegin()) { current = -1; return false; }
	current_value = Get(ResolvePos(current));
	return true;
}
bool DIBCoreBitmapDecoder::Previous(const IteratorTraits::IteratorDiff_t& count)
{
	if (IsBeforeBegin()) { return false; }
	current -= count;
	if (IsBeforeBegin()) { current = -1; return false; }
	current_value = Get(ResolvePos(current));
	return true;
}
void DIBCoreBitmapDecoder::JumpTo(const DisplayPoint& pos)
{
	if ( (pos.X() < 0)||(pos.Y() < 0) ) { throw std::invalid_argument("posに指定されている座標が無効です。"); }
	current = ResolveIndex(pos);
	current_value = Get(pos);
}
void DIBCoreBitmapDecoder::Reset() { Reset(IteratorOrigin::Begin); }
void DIBCoreBitmapDecoder::Reset(const IteratorOrigin& origin)
{
	switch(origin)
	{
		default:
		case IteratorOrigin::Begin: { current = 0; break; }
		case IteratorOrigin::End: { current = length - 1; break; }
	}
	current_value = Get(ResolvePos(current));
}
bool DIBCoreBitmapDecoder::HasValue() const { return (0 <= current)&&(current < length); }
bool DIBCoreBitmapDecoder::IsBeforeBegin() const { return current < 0; }
bool DIBCoreBitmapDecoder::IsAfterEnd() const { return length <= current; }
Graphics::DisplayPoint DIBCoreBitmapDecoder::CurrentPos() const { return ResolvePos(current); }
DIBCoreBitmapDecoder::ValueType DIBCoreBitmapDecoder::Current() const { if (HasValue()) { return current_value; } else { throw InvalidOperationException("このイテレータは領域の範囲外を指しています。"); } }
void DIBCoreBitmapDecoder::Write(const DIBPixelData<DIBBitDepth::Bit1>& value)
{
	if (bitdepth != DIBBitDepth::Bit1) { throw InvalidOperationException("現在のBitCountではこの型で書き込みを行うことはできません。"); }
	size_t tgt = offset + ResolveOffset(ResolvePos(current));
	DIBLoaderHelper::Write(loader, &value, tgt);
	current_value = value;
}
void DIBCoreBitmapDecoder::Write(const DIBPixelData<DIBBitDepth::Bit4>& value)
{
	if (bitdepth != DIBBitDepth::Bit4) { throw InvalidOperationException("現在のBitCountではこの型で書き込みを行うことはできません。"); }
	size_t tgt = offset + ResolveOffset(ResolvePos(current));
	DIBLoaderHelper::Write(loader, &value, tgt);
	current_value = value;
}
void DIBCoreBitmapDecoder::Write(const DIBPixelData<DIBBitDepth::Bit8>& value)
{
	if (bitdepth != DIBBitDepth::Bit8) { throw InvalidOperationException("現在のBitCountではこの型で書き込みを行うことはできません。"); }
	size_t tgt = offset + ResolveOffset(ResolvePos(current));
	DIBLoaderHelper::Write(loader, &value, tgt);
	current_value = value;
}
void DIBCoreBitmapDecoder::Write(const DIBPixelData<DIBBitDepth::Bit24>& value)
{
	if (bitdepth != DIBBitDepth::Bit24) { throw InvalidOperationException("現在のBitCountではこの型で書き込みを行うことはできません。"); }
	size_t tgt = offset + ResolveOffset(ResolvePos(current));
	DIBLoaderHelper::Write(loader, &value, tgt);
	current_value = value;
}
IteratorTraits::IteratorDiff_t DIBCoreBitmapDecoder::Distance(const DIBCoreBitmapDecoder& other) const { return current - other.current; }
bool DIBCoreBitmapDecoder::Equals(const DIBCoreBitmapDecoder& other) const { return current == other.current; }
int DIBCoreBitmapDecoder::Compare(const DIBCoreBitmapDecoder& other) const
{
	if (current == other.current) { return 0; }
	else if (other.current < current) { return 1; }
	else { return -1; }
}
DIBCoreBitmapDecoder::ValueType DIBCoreBitmapDecoder::Get(const DisplayPoint& pos)
{
	size_t tgt = offset + ResolveOffset(pos);
	switch(bitdepth)
	{
		case DIBBitDepth::Bit1:
		{
			auto result = DIBPixelData<DIBBitDepth::Bit1>();
			DIBLoaderHelper::Read(loader, &result, tgt);
			return ValueType(result);
		}
		case DIBBitDepth::Bit4:
		{
			auto result = DIBPixelData<DIBBitDepth::Bit4>();
			DIBLoaderHelper::Read(loader, &result, tgt);
			return ValueType(result);
		}
		case DIBBitDepth::Bit8:
		{
			auto result = DIBPixelData<DIBBitDepth::Bit8>();
			DIBLoaderHelper::Read(loader, &result, tgt);
			return ValueType(result);
		}
		case DIBBitDepth::Bit24:
		{
			auto result = DIBPixelData<DIBBitDepth::Bit24>();
			DIBLoaderHelper::Read(loader, &result, tgt);
			return ValueType(result);
		}
		default: { throw InvalidOperationException("情報ヘッダのBitCountの内容が無効です。"); }
	}
}
size_t DIBCoreBitmapDecoder::ResolveIndex(const DisplayPoint& pos) const { return ((size.Height() - 1 - pos.Y()) * size.Width()) + pos.X(); }
Graphics::DisplayPoint DIBCoreBitmapDecoder::ResolvePos(size_t index) const { return DisplayPoint(index % size.Width(), size.Height() - 1 - (index / size.Width())); }
size_t DIBCoreBitmapDecoder::ResolveOffset(const DisplayPoint& pos) const
{
	if ( (pos.X() < 0)||(pos.Y() < 0) ) { throw std::invalid_argument("posに指定されている座標が無効です。"); }
	if ( (size.Width() <= pos.X())||(size.Height() <= pos.Y()) ) { throw std::out_of_range("指定された座標はこの画像領域を超えています。"); }
	size_t pxl = (uint16_t(bitdepth)/sizeof(uint8_t)) + (((uint16_t(bitdepth)%sizeof(uint8_t)) != 0)?1:0);
	size_t w = pxl * size.Width() + ((((pxl * size.Width()) % 4) != 0)?(4-((pxl * size.Width())%4)):0);
	return (w * (size.Height() - pos.Y())) + (pxl * pos.X());
}

DIBCoreBitmapFileLoader::DIBCoreBitmapFileLoader(DIBLoader&& loader) : loader(std::forward<DIBLoader>(loader))
{
	if (this->loader.IsEnable()) { throw InvalidOperationException("無効な状態のloaderが渡されました。"); }
	if (this->loader.HeaderSize() < DIBCoreHeader::Size) { throw InvalidDIBFormatException("情報ヘッダの長さはCoreHeaderでサポートされる最小の長さよりも短いです。"); }
	DIBLoaderHelper::Read(this->loader, &ihead, sizeof(DIBFileHeader) + sizeof(int32_t));
	size_t palettesize = 0;
	switch(ihead.BitCount)
	{
		case DIBBitDepth::Bit1: { palettesize = 2; break; }
		case DIBBitDepth::Bit4: { palettesize = 16; break; }
		case DIBBitDepth::Bit8: { palettesize = 256; break; }
		case DIBBitDepth::Bit24: { palettesize = 0; break; }
		default: { throw InvalidDIBFormatException("情報ヘッダのBitCountの内容が無効です。"); }
	}
	if (palettesize != 0)
	{
		auto p = std::vector<RGBTriple_t>();
		p.reserve(palettesize);
		DIBLoaderHelper::Read(this->loader, p.data(), sizeof(DIBFileHeader) + DIBCoreHeader::Size, palettesize);
		for (auto i: p) { palette.push_back(RGB8_t(i)); }
	}
}
DIBCoreBitmapFileLoader::ValueType DIBCoreBitmapFileLoader::GetPixel(const DisplayPoint& pos)
{
	auto decoder = DIBCoreBitmapDecoder(loader, sizeof(DIBFileHeader) + loader.FileHead().Offset(), ihead.BitCount, DisplayRectSize(ihead.ImageWidth, ihead.ImageHeight));
	decoder.JumpTo(pos);
	auto data = decoder.Current();
	switch(ihead.BitCount)
	{
		case DIBBitDepth::Bit1:
		case DIBBitDepth::Bit4:
		case DIBBitDepth::Bit8:
		{
			return palette[std::visit([](auto i)->uint32_t { return uint32_t(i); }, data)];
		}
		case DIBBitDepth::Bit24:
		{
			return DIBPixelPerser::ToRGB(std::get<DIBPixelData<DIBBitDepth::Bit24>>(data));
		}
		default: { throw InvalidDIBFormatException("情報ヘッダのBitCountの内容が無効です。"); }
	}
}
std::vector<DIBCoreBitmapFileLoader::ValueType> DIBCoreBitmapFileLoader::GetPixel(const DisplayPoint& pos, size_t count)
{
	auto decoder = DIBCoreBitmapDecoder(loader, sizeof(DIBFileHeader) + loader.FileHead().Offset(), ihead.BitCount, DisplayRectSize(ihead.ImageWidth, ihead.ImageHeight));
	decoder.JumpTo(pos);
	auto result = std::vector<DIBCoreBitmapFileLoader::ValueType>();
	result.reserve(count);
	for (auto _: Range<size_t>(0, count).GetStdIterator())
	{
		auto data = decoder.Current();
		switch(ihead.BitCount)
		{
			case DIBBitDepth::Bit1:
			case DIBBitDepth::Bit4:
			case DIBBitDepth::Bit8:
			{
				result.push_back(palette[std::visit([](auto i)->uint32_t { return uint32_t(i); }, data)]);
				break;
			}
			case DIBBitDepth::Bit24:
			{
				result.push_back(DIBPixelPerser::ToRGB(std::get<DIBPixelData<DIBBitDepth::Bit24>>(data)));
				break;
			}
			default: { throw InvalidOperationException("情報ヘッダのBitCountの内容が無効です。"); }
		}
	}
	return result;
}
void DIBCoreBitmapFileLoader::SetPixel(const DisplayPoint& pos, const ValueType& value)
{
	auto decoder = DIBCoreBitmapDecoder(loader, sizeof(DIBFileHeader) + loader.FileHead().Offset(), ihead.BitCount, DisplayRectSize(ihead.ImageWidth, ihead.ImageHeight));
	decoder.JumpTo(pos);
	switch(ihead.BitCount)
	{
		case DIBBitDepth::Bit1:
		case DIBBitDepth::Bit4:
		case DIBBitDepth::Bit8:
		//	TODO: Implement
		{ throw NotImplementedException(); }
		case DIBBitDepth::Bit24: { decoder.Write(DIBPixelPerser::ToPixel24(value)); break; }
		default: { throw InvalidOperationException("情報ヘッダのBitCountの内容が無効です。"); }
	}
}
void DIBCoreBitmapFileLoader::SetPixel(const DisplayPoint& pos, const std::vector<ValueType>& value)
{
	auto decoder = DIBCoreBitmapDecoder(loader, sizeof(DIBFileHeader) + loader.FileHead().Offset(), ihead.BitCount, DisplayRectSize(ihead.ImageWidth, ihead.ImageHeight));
	decoder.JumpTo(pos);
	for(auto i: value)
	{
		switch(ihead.BitCount)
		{
			case DIBBitDepth::Bit1:
			case DIBBitDepth::Bit4:
			case DIBBitDepth::Bit8:
			//	TODO: Implement
			{ throw NotImplementedException(); }
			case DIBBitDepth::Bit24: { decoder.Write(DIBPixelPerser::ToPixel24(i)); break; }
			default: { throw InvalidOperationException("情報ヘッダのBitCountの内容が無効です。"); }
		}
	}
}
uint32_t DIBCoreBitmapFileLoader::GetPixelRaw(const DisplayPoint& pos)
{
	auto decoder = DIBCoreBitmapDecoder(loader, sizeof(DIBFileHeader) + loader.FileHead().Offset(), ihead.BitCount, DisplayRectSize(ihead.ImageWidth, ihead.ImageHeight));
	decoder.JumpTo(pos);
	auto data = decoder.Current();
	switch(ihead.BitCount)
	{
		case DIBBitDepth::Bit1:
		case DIBBitDepth::Bit4:
		case DIBBitDepth::Bit8:
		case DIBBitDepth::Bit24:
		{
			return std::visit([](auto i)->uint32_t { return uint32_t(i); }, data);
		}
		default: { throw InvalidDIBFormatException("情報ヘッダのBitCountの内容が無効です。"); }
	}
}
std::vector<uint32_t> DIBCoreBitmapFileLoader::GetPixelRaw(const DisplayPoint& pos, size_t count)
{
	auto decoder = DIBCoreBitmapDecoder(loader, sizeof(DIBFileHeader) + loader.FileHead().Offset(), ihead.BitCount, DisplayRectSize(ihead.ImageWidth, ihead.ImageHeight));
	decoder.JumpTo(pos);
	auto result = std::vector<uint32_t>();
	result.reserve(count);
	for (auto _: Range<size_t>(0, count).GetStdIterator())
	{
		auto data = decoder.Current();
		switch(ihead.BitCount)
		{
			case DIBBitDepth::Bit1:
			case DIBBitDepth::Bit4:
			case DIBBitDepth::Bit8:
			case DIBBitDepth::Bit24:
			{
				result.push_back(std::visit([](auto i)->uint32_t { return uint32_t(i); }, data));
				break;
			}
			default: { throw InvalidOperationException("情報ヘッダのBitCountの内容が無効です。"); }
		}
	}
	return result;
}
void DIBCoreBitmapFileLoader::SetPixelRaw(const DisplayPoint& pos, const uint32_t& value)
{
	auto decoder = DIBCoreBitmapDecoder(loader, sizeof(DIBFileHeader) + loader.FileHead().Offset(), ihead.BitCount, DisplayRectSize(ihead.ImageWidth, ihead.ImageHeight));
	decoder.JumpTo(pos);
	switch(ihead.BitCount)
	{
		case DIBBitDepth::Bit1: { decoder.Write(DIBPixelData<DIBBitDepth::Bit1>(value)); break; }
		case DIBBitDepth::Bit4: { decoder.Write(DIBPixelData<DIBBitDepth::Bit4>(value)); break; }
		case DIBBitDepth::Bit8: { decoder.Write(DIBPixelData<DIBBitDepth::Bit8>(value)); break; }
		case DIBBitDepth::Bit24: { decoder.Write(DIBPixelData<DIBBitDepth::Bit24>(value)); break; }
		default: { throw InvalidOperationException("情報ヘッダのBitCountの内容が無効です。"); }
	}
}
void DIBCoreBitmapFileLoader::SetPixelRaw(const DisplayPoint& pos, const std::vector<uint32_t>& value)
{
	auto decoder = DIBCoreBitmapDecoder(loader, sizeof(DIBFileHeader) + loader.FileHead().Offset(), ihead.BitCount, DisplayRectSize(ihead.ImageWidth, ihead.ImageHeight));
	decoder.JumpTo(pos);
	for(auto i: value)
	{
		switch(ihead.BitCount)
		{
			case DIBBitDepth::Bit1: { decoder.Write(DIBPixelData<DIBBitDepth::Bit1>(i)); break; }
			case DIBBitDepth::Bit4: { decoder.Write(DIBPixelData<DIBBitDepth::Bit4>(i)); break; }
			case DIBBitDepth::Bit8: { decoder.Write(DIBPixelData<DIBBitDepth::Bit8>(i)); break; }
			case DIBBitDepth::Bit24: { decoder.Write(DIBPixelData<DIBBitDepth::Bit24>(i)); break; }
			default: { throw InvalidOperationException("情報ヘッダのBitCountの内容が無効です。"); }
		}
	}
}
void DIBCoreBitmapFileLoader::CopyTo(WritableImage<RGB8_t>& dest)
{
	auto decoder = DIBCoreBitmapDecoder(loader, sizeof(DIBFileHeader) + loader.FileHead().Offset(), ihead.BitCount, DisplayRectSize(ihead.ImageWidth, ihead.ImageHeight));
	for (decoder.Reset(); decoder.HasValue(); decoder.Next())
	{
		switch(ihead.BitCount)
		{
			case DIBBitDepth::Bit1:
			case DIBBitDepth::Bit4:
			case DIBBitDepth::Bit8:
			{
				dest.At(decoder.CurrentPos()) = palette[std::visit([](auto i)->uint32_t { return uint32_t(i); }, decoder.Current())];
				break;
			}
			case DIBBitDepth::Bit24:
			{
				dest.At(decoder.CurrentPos()) =  DIBPixelPerser::ToRGB(std::get<DIBPixelData<DIBBitDepth::Bit24>>(decoder.Current()));
				break;
			}
			default: { throw InvalidDIBFormatException("情報ヘッダのBitCountの内容が無効です。"); }
		}
	}
}
void DIBCoreBitmapFileLoader::CopyTo(WritableImage<RGB8_t>& dest, const DisplayRectangle& area, const DisplayPoint& destorigin)
{
	if ((area.Left() < 0)||(area.Top() < 0)||(ihead.ImageWidth < area.Right())||(ihead.ImageHeight < area.Bottom())) { throw std::out_of_range("areaで指定された領域がビットマップの画像領域を超えています。"); }
	auto decoder = DIBCoreBitmapDecoder(loader, sizeof(DIBFileHeader) + loader.FileHead().Offset(), ihead.BitCount, DisplayRectSize(ihead.ImageWidth, ihead.ImageHeight));
	for (decoder.JumpTo(DisplayPoint(area.Left(), area.Bottom())); decoder.HasValue(); decoder.Next())
	{
		if (area.Contains(decoder.CurrentPos())) { decoder.Next(ihead.ImageWidth - area.Width()); }
		switch(ihead.BitCount)
		{
			case DIBBitDepth::Bit1:
			case DIBBitDepth::Bit4:
			case DIBBitDepth::Bit8:
			{
				dest.At(decoder.CurrentPos() - area.Origin() + destorigin) = palette[std::visit([](auto i)->uint32_t { return uint32_t(i); }, decoder.Current())];
				break;
			}
			case DIBBitDepth::Bit24:
			{
				dest.At(decoder.CurrentPos() - area.Origin() + destorigin) =  DIBPixelPerser::ToRGB(std::get<DIBPixelData<DIBBitDepth::Bit24>>(decoder.Current()));
				break;
			}
			default: { throw InvalidDIBFormatException("情報ヘッダのBitCountの内容が無効です。"); }
		}
	}
}
DIBCoreBitmapFileLoader::Pixmap DIBCoreBitmapFileLoader::ToPixmap()
{
	auto result = Pixmap(DisplayRectSize(ihead.ImageWidth, ihead.ImageHeight));
	CopyTo(result);
	return result;
}
DIBCoreBitmapFileLoader::Pixmap DIBCoreBitmapFileLoader::ToPixmap(const DisplayRectangle& area)
{
	auto result = Pixmap(area.Size());
	CopyTo(result, area);
	return result;
}

DIBInfoBitmapFileLoader::DIBInfoBitmapFileLoader(DIBLoader&& loader) : loader(std::forward<DIBLoader>(loader))
{
	if (this->loader.IsEnable()) { throw InvalidOperationException("無効な状態のloaderが渡されました。"); }
	if (this->loader.HeaderSize() < DIBInfoHeader::Size) { throw InvalidDIBFormatException("情報ヘッダの長さはInfoHeaderでサポートされる最小の長さよりも短いです。"); }
	DIBLoaderHelper::Read(this->loader, &ihead, sizeof(DIBFileHeader) + sizeof(int32_t));
	if (ihead.ComplessionMethod == BMPCompressionMethod::BITFIELDS)
	{
		auto colormaskdata = DIBRGBColorMask();
		DIBLoaderHelper::Read(this->loader, &colormaskdata, sizeof(DIBFileHeader) + DIBInfoHeader::Size);
		colormask = DIBColorMask(colormaskdata);
	}
	else if (ihead.ComplessionMethod == BMPCompressionMethod::ALPHABITFIELDS)
	{
		auto colormaskdata = DIBRGBAColorMask();
		DIBLoaderHelper::Read(this->loader, &colormaskdata, sizeof(DIBFileHeader) + DIBInfoHeader::Size);
		colormask = DIBColorMask(colormaskdata);
	}
	if (ihead.IndexedColorCount != 0)
	{
		auto lpal = std::vector<RGBTriple_t>();
		lpal.reserve(ihead.IndexedColorCount);
		DIBLoaderHelper::Read(this->loader, &lpal, sizeof(DIBFileHeader) + sizeof(DIBInfoHeader), ihead.IndexedColorCount);
		palette.reserve(ihead.IndexedColorCount);
		for(auto i: lpal) { palette.push_back(RGB8_t(i)); }
	}
}
DIBInfoBitmapFileLoader::PixelData DIBInfoBitmapFileLoader::Get(const DisplayPoint& index)
{
	auto pos = sizeof(DIBFileHeader) + loader.FileHead().Offset() + ResolvePos(index);
	switch(ihead.BitCount)
	{
		case DIBBitDepth::Bit1:
		{
			DIBPixelData<DIBBitDepth::Bit1> result;
			DIBLoaderHelper::Read(loader, &result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit4:
		{
			DIBPixelData<DIBBitDepth::Bit4> result;
			DIBLoaderHelper::Read(loader, &result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit8:
		{
			DIBPixelData<DIBBitDepth::Bit8> result;
			DIBLoaderHelper::Read(loader, &result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit16:
		{
			DIBPixelData<DIBBitDepth::Bit16> result;
			DIBLoaderHelper::Read(loader, &result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit24:
		{
			DIBPixelData<DIBBitDepth::Bit24> result;
			DIBLoaderHelper::Read(loader, &result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit32:
		{
			DIBPixelData<DIBBitDepth::Bit32> result;
			DIBLoaderHelper::Read(loader, &result, pos);
			return PixelData(result);
		}
		default: { throw InvalidDIBFormatException("BitCountの内容が無効です。"); }
	}
}
DIBInfoBitmapFileLoader::PixelVector DIBInfoBitmapFileLoader::Get(const DisplayPoint& index, const size_t& length)
{
	if (ihead.ImageWidth <= (index.X() + length)) { throw std::out_of_range("画像の幅を超える領域を指定することはできません。"); }
	auto pos = sizeof(DIBFileHeader) + loader.FileHead().Offset() + ResolvePos(index);
	switch(ihead.BitCount)
	{
		case DIBBitDepth::Bit1:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit1>>();
			result.reserve(length);
			DIBLoaderHelper::Read(loader, result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit4:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit4>>();
			result.reserve(length);
			DIBLoaderHelper::Read(loader, result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit8:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit8>>();
			result.reserve(length);
			DIBLoaderHelper::Read(loader, result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit16:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit16>>();
			result.reserve(length);
			DIBLoaderHelper::Read(loader, result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit24:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit24>>();
			result.reserve(length);
			DIBLoaderHelper::Read(loader, result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit32:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit32>>();
			result.reserve(length);
			DIBLoaderHelper::Read(loader, result.data(), pos, length);
			return PixelVector(result);
		}
		default: { throw InvalidDIBFormatException("情報ヘッダのBitCountの内容が無効です。"); }
	}
}
size_t DIBInfoBitmapFileLoader::ResolvePos(const DisplayPoint& pos) const
{
	if ( (pos.X() < 0)||(pos.Y() < 0) ) { throw InvalidOperationException("posに指定されている座標が無効です。"); }
	if ( (ihead.ImageWidth <= pos.X())||(ihead.ImageHeight <= pos.Y()) ) { throw std::out_of_range("指定された座標はこの画像領域を超えています。"); }
	size_t pxl = (uint16_t(ihead.BitCount)/sizeof(uint8_t)) + (((uint16_t(ihead.BitCount)%sizeof(uint8_t)) != 0)?1:0);
	size_t w = pxl * ihead.ImageWidth + ((((pxl * ihead.ImageWidth) % 4) != 0)?(4-((pxl * ihead.ImageWidth)%4)):0);
	return (w * pos.Y()) + (pxl * pos.X());
}

DIBV4BitmapFileLoader::DIBV4BitmapFileLoader(DIBLoader&& loader) : loader(std::forward<DIBLoader>(loader))
{
	if (loader.HeaderSize() < DIBV4Header::Size) { throw InvalidDIBFormatException("情報ヘッダの長さはV4Headerでサポートされる最小の長さよりも短いです。"); }
	DIBLoaderHelper::Read(loader, &ihead, sizeof(DIBFileHeader) + sizeof(int32_t));
	if (ihead.IndexedColorCount != 0)
	{
		auto lpal = std::vector<RGBTriple_t>();
		lpal.reserve(ihead.IndexedColorCount);
		DIBLoaderHelper::Read(loader, &lpal, sizeof(DIBFileHeader) + sizeof(DIBInfoHeader), ihead.IndexedColorCount);
		palette.reserve(ihead.IndexedColorCount);
		for(auto i: lpal) { palette.push_back(RGB8_t(i)); }
	}
}
DIBV4BitmapFileLoader::PixelData DIBV4BitmapFileLoader::Get(const DisplayPoint& index)
{
	auto pos = sizeof(DIBFileHeader) + loader.FileHead().Offset() + ResolvePos(index);
	switch(ihead.BitCount)
	{
		case DIBBitDepth::Bit1:
		{
			DIBPixelData<DIBBitDepth::Bit1> result;
			DIBLoaderHelper::Read(loader, &result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit4:
		{
			DIBPixelData<DIBBitDepth::Bit4> result;
			DIBLoaderHelper::Read(loader, &result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit8:
		{
			DIBPixelData<DIBBitDepth::Bit8> result;
			DIBLoaderHelper::Read(loader, &result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit16:
		{
			DIBPixelData<DIBBitDepth::Bit16> result;
			DIBLoaderHelper::Read(loader, &result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit24:
		{
			DIBPixelData<DIBBitDepth::Bit24> result;
			DIBLoaderHelper::Read(loader, &result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit32:
		{
			DIBPixelData<DIBBitDepth::Bit32> result;
			DIBLoaderHelper::Read(loader, &result, pos);
			return PixelData(result);
		}
		default: { throw InvalidDIBFormatException("BitCountの内容が無効です。"); }
	}
}
DIBV4BitmapFileLoader::PixelVector DIBV4BitmapFileLoader::Get(const DisplayPoint& index, const size_t& length)
{
	if (ihead.ImageWidth <= (index.X() + length)) { throw std::out_of_range("画像の幅を超える領域を指定することはできません。"); }
	auto pos = sizeof(DIBFileHeader) + loader.FileHead().Offset() + ResolvePos(index);
	switch(ihead.BitCount)
	{
		case DIBBitDepth::Bit1:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit1>>();
			result.reserve(length);
			DIBLoaderHelper::Read(loader, result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit4:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit4>>();
			result.reserve(length);
			DIBLoaderHelper::Read(loader, result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit8:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit8>>();
			result.reserve(length);
			DIBLoaderHelper::Read(loader, result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit16:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit16>>();
			result.reserve(length);
			DIBLoaderHelper::Read(loader, result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit24:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit24>>();
			result.reserve(length);
			DIBLoaderHelper::Read(loader, result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit32:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit32>>();
			result.reserve(length);
			DIBLoaderHelper::Read(loader, result.data(), pos, length);
			return PixelVector(result);
		}
		default: { throw InvalidDIBFormatException("情報ヘッダのBitCountの内容が無効です。"); }
	}
}
size_t DIBV4BitmapFileLoader::ResolvePos(const DisplayPoint& pos) const
{
	if ( (pos.X() < 0)||(pos.Y() < 0) ) { throw InvalidOperationException("posに指定されている座標が無効です。"); }
	if ( (ihead.ImageWidth <= pos.X())||(ihead.ImageHeight <= pos.Y()) ) { throw std::out_of_range("指定された座標はこの画像領域を超えています。"); }
	size_t pxl = (uint16_t(ihead.BitCount)/sizeof(uint8_t)) + (((uint16_t(ihead.BitCount)%sizeof(uint8_t)) != 0)?1:0);
	size_t w = pxl * ihead.ImageWidth + ((((pxl * ihead.ImageWidth) % 4) != 0)?(4-((pxl * ihead.ImageWidth)%4)):0);
	return (w * pos.Y()) + (pxl * pos.X());
}

DIBV5BitmapFileLoader::DIBV5BitmapFileLoader(DIBLoader&& loader) : loader(std::forward<DIBLoader>(loader))
{
	if (loader.HeaderSize() < DIBV4Header::Size) { throw InvalidDIBFormatException("情報ヘッダの長さはV4Headerでサポートされる最小の長さよりも短いです。"); }
	DIBLoaderHelper::Read(loader, &ihead, sizeof(DIBFileHeader) + sizeof(int32_t));
	if (ihead.IndexedColorCount != 0)
	{
		auto lpal = std::vector<RGBTriple_t>();
		lpal.reserve(ihead.IndexedColorCount);
		DIBLoaderHelper::Read(loader, &lpal, sizeof(DIBFileHeader) + sizeof(DIBInfoHeader), ihead.IndexedColorCount);
		palette.reserve(ihead.IndexedColorCount);
		for(auto i: lpal) { palette.push_back(RGB8_t(i)); }
	}
}
DIBV5BitmapFileLoader::PixelData DIBV5BitmapFileLoader::Get(const DisplayPoint& index)
{
	auto pos = sizeof(DIBFileHeader) + loader.FileHead().Offset() + ResolvePos(index);
	switch(ihead.BitCount)
	{
		case DIBBitDepth::Bit1:
		{
			DIBPixelData<DIBBitDepth::Bit1> result;
			DIBLoaderHelper::Read(loader, &result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit4:
		{
			DIBPixelData<DIBBitDepth::Bit4> result;
			DIBLoaderHelper::Read(loader, &result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit8:
		{
			DIBPixelData<DIBBitDepth::Bit8> result;
			DIBLoaderHelper::Read(loader, &result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit16:
		{
			DIBPixelData<DIBBitDepth::Bit16> result;
			DIBLoaderHelper::Read(loader, &result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit24:
		{
			DIBPixelData<DIBBitDepth::Bit24> result;
			DIBLoaderHelper::Read(loader, &result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit32:
		{
			DIBPixelData<DIBBitDepth::Bit32> result;
			DIBLoaderHelper::Read(loader, &result, pos);
			return PixelData(result);
		}
		default: { throw InvalidDIBFormatException("BitCountの内容が無効です。"); }
	}
}
DIBV5BitmapFileLoader::PixelVector DIBV5BitmapFileLoader::Get(const DisplayPoint& index, const size_t& length)
{
	if (ihead.ImageWidth <= (index.X() + length)) { throw std::out_of_range("画像の幅を超える領域を指定することはできません。"); }
	auto pos = sizeof(DIBFileHeader) + loader.FileHead().Offset() + ResolvePos(index);
	switch(ihead.BitCount)
	{
		case DIBBitDepth::Bit1:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit1>>();
			result.reserve(length);
			DIBLoaderHelper::Read(loader, result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit4:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit4>>();
			result.reserve(length);
			DIBLoaderHelper::Read(loader, result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit8:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit8>>();
			result.reserve(length);
			DIBLoaderHelper::Read(loader, result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit16:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit16>>();
			result.reserve(length);
			DIBLoaderHelper::Read(loader, result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit24:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit24>>();
			result.reserve(length);
			DIBLoaderHelper::Read(loader, result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit32:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit32>>();
			result.reserve(length);
			DIBLoaderHelper::Read(loader, result.data(), pos, length);
			return PixelVector(result);
		}
		default: { throw InvalidDIBFormatException("情報ヘッダのBitCountの内容が無効です。"); }
	}
}
size_t DIBV5BitmapFileLoader::ResolvePos(const DisplayPoint& pos) const
{
	if ( (pos.X() < 0)||(pos.Y() < 0) ) { throw InvalidOperationException("posに指定されている座標が無効です。"); }
	if ( (ihead.ImageWidth <= pos.X())||(ihead.ImageHeight <= pos.Y()) ) { throw std::out_of_range("指定された座標はこの画像領域を超えています。"); }
	size_t pxl = (uint16_t(ihead.BitCount)/sizeof(uint8_t)) + (((uint16_t(ihead.BitCount)%sizeof(uint8_t)) != 0)?1:0);
	size_t w = pxl * ihead.ImageWidth + ((((pxl * ihead.ImageWidth) % 4) != 0)?(4-((pxl * ihead.ImageWidth)%4)):0);
	return (w * pos.Y()) + (pxl * pos.X());
}
