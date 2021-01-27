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

DIBCoreBitmapFileLoader::DIBCoreBitmapFileLoader(DIBLoader&& loader) : loader(std::forward<DIBLoader>(loader))
{
	if (this->loader.IsEnable()) { throw InvalidOperationException("無効な状態のloaderが渡されました。"); }
	if (this->loader.HeaderSize() < DIBCoreHeader::Size) { throw InvalidDIBFormatException("情報ヘッダの長さはCoreHeaderでサポートされる最小の長さよりも短いです。"); }
	DIBLoaderHelper::Read(this->loader, &ihead, sizeof(DIBFileHeader) + sizeof(int32_t));
}
[[nodiscard]] DIBCoreBitmapFileLoader::ValueType DIBCoreBitmapFileLoader::Get(const DisplayPoint& pos)
{
	auto data = GetData(pos);
	switch(ihead.BitCount)
	{
		case DIBBitDepth::Bit1: { return ColorConvert::ToRgbFromLuminance(DIBPixelPerser::ToGrayScale(std::get<DIBPixelData<DIBBitDepth::Bit1>>(data))); }
		case DIBBitDepth::Bit4: { return ColorConvert::ToRgbFromLuminance(DIBPixelPerser::ToGrayScale(std::get<DIBPixelData<DIBBitDepth::Bit4>>(data))); }
		case DIBBitDepth::Bit8: { return ColorConvert::ToRgbFromLuminance(DIBPixelPerser::ToGrayScale(std::get<DIBPixelData<DIBBitDepth::Bit8>>(data))); }
		case DIBBitDepth::Bit24: { return DIBPixelPerser::ToRGB(std::get<DIBPixelData<DIBBitDepth::Bit24>>(data)); }
		default: { throw InvalidDIBFormatException("情報ヘッダのBitCountの内容が無効です。"); }
	}
}
void DIBCoreBitmapFileLoader::Set(const DisplayPoint& pos, const ValueType& value)
{
	switch(ihead.BitCount)
	{
		case DIBBitDepth::Bit1: { SetData(pos, DIBPixelPerser::ToPixel1(ColorConvert::ToLuminanceFromSrgb(value))); return; }
		case DIBBitDepth::Bit4: { SetData(pos, DIBPixelPerser::ToPixel4(ColorConvert::ToLuminanceFromSrgb(value))); return; }
		case DIBBitDepth::Bit8: { SetData(pos, DIBPixelPerser::ToPixel8(ColorConvert::ToLuminanceFromSrgb(value))); return; }
		case DIBBitDepth::Bit24: { SetData(pos, DIBPixelPerser::ToPixel24(value)); }
		default: { throw InvalidDIBFormatException("情報ヘッダのBitCountの内容が無効です。"); }
	}
}
DIBCoreBitmapFileLoader::PixelData DIBCoreBitmapFileLoader::GetData(const DisplayPoint& pos)
{
	size_t index = sizeof(DIBFileHeader) + loader.FileHead().Offset() + ResolvePos(pos);
	switch(ihead.BitCount)
	{
		case DIBBitDepth::Bit1:
		{
			auto result = DIBPixelData<DIBBitDepth::Bit1>();
			DIBLoaderHelper::Read(loader, &result, index);
			return PixelData(result);
		}
		case DIBBitDepth::Bit4:
		{
			auto result = DIBPixelData<DIBBitDepth::Bit4>();
			DIBLoaderHelper::Read(loader, &result, index);
			return PixelData(result);
		}
		case DIBBitDepth::Bit8:
		{
			auto result = DIBPixelData<DIBBitDepth::Bit8>();
			DIBLoaderHelper::Read(loader, &result, index);
			return PixelData(result);
		}
		case DIBBitDepth::Bit24:
		{
			auto result = DIBPixelData<DIBBitDepth::Bit24>();
			DIBLoaderHelper::Read(loader, &result, index);
			return PixelData(result);
		}
		default: { throw InvalidDIBFormatException("情報ヘッダのBitCountの内容が無効です。"); }
	}
}
DIBCoreBitmapFileLoader::PixelVector DIBCoreBitmapFileLoader::GetData(const DisplayPoint& pos, const size_t& length)
{
	if (ihead.ImageWidth <= (pos.X() + length)) { throw std::out_of_range("画像の幅を超える領域を指定することはできません。"); }
	size_t index = sizeof(DIBFileHeader) + loader.FileHead().Offset() + ResolvePos(pos);
	switch(ihead.BitCount)
	{
		case DIBBitDepth::Bit1:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit1>>();
			result.reserve(length);
			DIBLoaderHelper::Read(loader, result.data(), index, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit4:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit4>>();
			result.reserve(length);
			DIBLoaderHelper::Read(loader, result.data(), index, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit8:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit8>>();
			result.reserve(length);
			DIBLoaderHelper::Read(loader, result.data(), index, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit24:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit24>>();
			result.reserve(length);
			DIBLoaderHelper::Read(loader, result.data(), index, length);
			return PixelVector(result);
		}
		default: { throw InvalidDIBFormatException("情報ヘッダのBitCountの内容が無効です。"); }
	}
}
void DIBCoreBitmapFileLoader::SetData(const DisplayPoint& pos, const DIBPixelData<DIBBitDepth::Bit1>& data)
{
	size_t index = sizeof(DIBFileHeader) + loader.FileHead().Offset() + ResolvePos(pos);
	if (ihead.BitCount != DIBBitDepth::Bit1) { throw InvalidOperationException("現在のBitCountではこの型で書き込みを行うことはできません。"); }
	DIBLoaderHelper::Write(loader, &data, index);
}
void DIBCoreBitmapFileLoader::SetData(const DisplayPoint& pos, const DIBPixelData<DIBBitDepth::Bit4>& data)
{
	size_t index = sizeof(DIBFileHeader) + loader.FileHead().Offset() + ResolvePos(pos);
	if (ihead.BitCount != DIBBitDepth::Bit4) { throw InvalidOperationException("現在のBitCountではこの型で書き込みを行うことはできません。"); }
	DIBLoaderHelper::Write(loader, &data, index);
}
void DIBCoreBitmapFileLoader::SetData(const DisplayPoint& pos, const DIBPixelData<DIBBitDepth::Bit8>& data)
{
	size_t index = sizeof(DIBFileHeader) + loader.FileHead().Offset() + ResolvePos(pos);
	if (ihead.BitCount != DIBBitDepth::Bit8) { throw InvalidOperationException("現在のBitCountではこの型で書き込みを行うことはできません。"); }
	DIBLoaderHelper::Write(loader, &data, index);
}
void DIBCoreBitmapFileLoader::SetData(const DisplayPoint& pos, const DIBPixelData<DIBBitDepth::Bit24>& data)
{
	size_t index = sizeof(DIBFileHeader) + loader.FileHead().Offset() + ResolvePos(pos);
	if (ihead.BitCount != DIBBitDepth::Bit24) { throw InvalidOperationException("現在のBitCountではこの型で書き込みを行うことはできません。"); }
	DIBLoaderHelper::Write(loader, &data, index);
}
void DIBCoreBitmapFileLoader::SetData(const DisplayPoint& pos, const std::vector<DIBPixelData<DIBBitDepth::Bit1>>& data)
{
	if (ihead.ImageWidth <= (pos.X() + data.size())) { throw std::out_of_range("画像の幅を超える領域を指定することはできません。"); }
	size_t index = sizeof(DIBFileHeader) + loader.FileHead().Offset() + ResolvePos(pos);
	if (ihead.BitCount != DIBBitDepth::Bit1) { throw InvalidOperationException("現在のBitCountではこの型で書き込みを行うことはできません。"); }
	DIBLoaderHelper::Write(loader, data.data(), index);
}
void DIBCoreBitmapFileLoader::SetData(const DisplayPoint& pos, const std::vector<DIBPixelData<DIBBitDepth::Bit4>>& data)
{
	if (ihead.ImageWidth <= (pos.X() + data.size())) { throw std::out_of_range("画像の幅を超える領域を指定することはできません。"); }
	size_t index = sizeof(DIBFileHeader) + loader.FileHead().Offset() + ResolvePos(pos);
	if (ihead.BitCount != DIBBitDepth::Bit4) { throw InvalidOperationException("現在のBitCountではこの型で書き込みを行うことはできません。"); }
	DIBLoaderHelper::Write(loader, data.data(), index);
}
void DIBCoreBitmapFileLoader::SetData(const DisplayPoint& pos, const std::vector<DIBPixelData<DIBBitDepth::Bit8>>& data)
{
	if (ihead.ImageWidth <= (pos.X() + data.size())) { throw std::out_of_range("画像の幅を超える領域を指定することはできません。"); }
	size_t index = sizeof(DIBFileHeader) + loader.FileHead().Offset() + ResolvePos(pos);
	if (ihead.BitCount != DIBBitDepth::Bit8) { throw InvalidOperationException("現在のBitCountではこの型で書き込みを行うことはできません。"); }
	DIBLoaderHelper::Write(loader, data.data(), index);
}
void DIBCoreBitmapFileLoader::SetData(const DisplayPoint& pos, const std::vector<DIBPixelData<DIBBitDepth::Bit24>>& data)
{
	if (ihead.ImageWidth <= (pos.X() + data.size())) { throw std::out_of_range("画像の幅を超える領域を指定することはできません。"); }
	size_t index = sizeof(DIBFileHeader) + loader.FileHead().Offset() + ResolvePos(pos);
	if (ihead.BitCount != DIBBitDepth::Bit24) { throw InvalidOperationException("現在のBitCountではこの型で書き込みを行うことはできません。"); }
	DIBLoaderHelper::Write(loader, data.data(), index);
}
size_t DIBCoreBitmapFileLoader::ResolvePos(const DisplayPoint& pos) const
{
	if ( (pos.X() < 0)||(pos.Y() < 0) ) { throw std::invalid_argument("posに指定されている座標が無効です。"); }
	if ( (ihead.ImageWidth <= pos.X())||(ihead.ImageHeight <= pos.Y()) ) { throw std::out_of_range("指定された座標はこの画像領域を超えています。"); }
	size_t pxl = (uint16_t(ihead.BitCount)/sizeof(uint8_t)) + (((uint16_t(ihead.BitCount)%sizeof(uint8_t)) != 0)?1:0);
	size_t w = pxl * ihead.ImageWidth + ((((pxl * ihead.ImageWidth) % 4) != 0)?(4-((pxl * ihead.ImageWidth)%4)):0);
	return (w * (ihead.ImageHeight - pos.Y())) + (pxl * pos.X());
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
