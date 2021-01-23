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

namespace zawa_ch::StationaryOrbit::Graphics::DIB
{
	class DIBLoadHelper
	{
	public:
		///	現在のストリームの位置からデータを取得します。
		///	@param	T
		///	読み込むデータの型。
		///	@param	dest
		///	読み込んだデータの格納先。
		///	@a sizeof(T)*length の長さの領域が確保されている必要があります。
		///	@param	length
		///	読み込むデータの個数。
		template<class T>
		static std::istream& Read(std::istream& stream, T* dest, const size_t& length = 1U)
		{
			if (stream.fail()) { throw InvalidOperationException("ストリームの状態が無効です。"); }
			auto sentry = std::istream::sentry(stream, true);
			if (!sentry) { throw std::fstream::failure("ストリームの準備に失敗しました。"); }
			if (stream.read((char*)dest, sizeof(T) * length).fail())
			{
				if (stream.eof()) { stream.clear(); throw InvalidDIBFormatException("データの読み取り中にストリーム終端に到達しました。"); }
				stream.clear();
				throw std::fstream::failure("ストリームの読み取りに失敗しました。");
			}
			return stream;
		}
		///	ストリームの指定された位置からデータを取得します。
		///	@param	T
		///	読み込むデータの型。
		///	@param	dest
		///	読み込んだデータの格納先。
		///	@a sizeof(T)*length の長さの領域が確保されている必要があります。
		///	@param	length
		///	読み込むデータの個数。
		template<class T>
		static std::istream& ReadFrom(std::istream& stream, T* dest, const size_t& index, const size_t& length = 1U)
		{
			if (stream.fail()) { throw InvalidOperationException("ストリームの状態が無効です。"); }
			auto sentry = std::istream::sentry(stream, true);
			if (!sentry) { throw std::fstream::failure("ストリームの準備に失敗しました。"); }
			if (stream.seekg(index).fail()) { stream.clear(); throw std::fstream::failure("ストリームのシークに失敗しました。"); }
			if (stream.read((char*)dest, sizeof(T) * length).fail())
			{
				if (stream.eof()) { stream.clear(); throw InvalidDIBFormatException("データの読み取り中にストリーム終端に到達しました。"); }
				stream.clear();
				throw std::fstream::failure("ストリームの読み取りに失敗しました。");
			}
			return stream;
		}
	};
}

DIBFileLoader::DIBFileLoader(std::fstream&& stream)
	: stream(std::move(stream))
{
	if (this->stream.fail()) { throw InvalidOperationException("ストリームの状態が無効です。"); }
	auto sentry = std::istream::sentry(this->stream, true);
	if (!sentry) { throw std::fstream::failure("ストリームの準備に失敗しました。"); }
	if (this->stream.seekg(0).fail()) { this->stream.clear(); throw std::fstream::failure("ストリームのシークに失敗しました。"); }
	if (this->stream.read((char*)&fhead, sizeof(DIBFileHeader)).fail())
	{
		if (this->stream.eof()) { this->stream.clear(); throw InvalidDIBFormatException("ファイルヘッダの読み取り中にストリーム終端に到達しました。"); }
		this->stream.clear();
		throw std::fstream::failure("ストリームの読み取りに失敗しました。");
	}
	if (!fhead.CheckFileHeader()) { throw InvalidDIBFormatException("ファイルヘッダのマジックナンバーを認識できませんでした。"); }
	if (this->stream.read((char*)&headersize, sizeof(int32_t)).fail())
	{
		if (this->stream.eof()) { this->stream.clear(); throw InvalidDIBFormatException("ヘッダサイズの読み取り中にストリーム終端に到達しました。"); }
		this->stream.clear();
		throw std::fstream::failure("ストリームの読み取りに失敗しました。");
	}
}
DIBFileLoader::DIBFileLoader(const char* filename, std::ios_base::openmode mode) : DIBFileLoader(std::move(std::fstream(filename, mode))) {}
DIBFileLoader::DIBFileLoader(const std::string& filename, std::ios_base::openmode mode) : DIBFileLoader(std::move(std::fstream(filename, mode))) {}

DIBCoreBitmapFileLoader::DIBCoreBitmapFileLoader(DIBFileLoader&& loader) : loader(std::move(loader))
{
	if (loader.HeaderSize() < DIBCoreHeader::Size) { throw InvalidDIBFormatException("情報ヘッダの長さはCoreHeaderでサポートされる最小の長さよりも短いです。"); }
	DIBLoadHelper::ReadFrom(loader.Stream(), &ihead, sizeof(DIBFileHeader) + sizeof(int32_t));
}
DIBCoreBitmapFileLoader::PixelData DIBCoreBitmapFileLoader::Get(const DisplayPoint& index)
{
	size_t pos = sizeof(DIBFileHeader) + loader.FileHead().Offset() + ResolvePos(index);
	switch(ihead.BitCount)
	{
		case DIBBitDepth::Bit1:
		{
			auto result = DIBPixelData<DIBBitDepth::Bit1>();
			DIBLoadHelper::ReadFrom(loader.Stream(), &result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit4:
		{
			auto result = DIBPixelData<DIBBitDepth::Bit4>();
			DIBLoadHelper::ReadFrom(loader.Stream(), &result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit8:
		{
			auto result = DIBPixelData<DIBBitDepth::Bit8>();
			DIBLoadHelper::ReadFrom(loader.Stream(), &result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit24:
		{
			auto result = DIBPixelData<DIBBitDepth::Bit24>();
			DIBLoadHelper::ReadFrom(loader.Stream(), &result, pos);
			return PixelData(result);
		}
		default: { throw InvalidDIBFormatException("情報ヘッダのBitCountの内容が無効です。"); }
	}
}
DIBCoreBitmapFileLoader::PixelVector DIBCoreBitmapFileLoader::Get(const DisplayPoint& index, const size_t& length)
{
	if (ihead.ImageWidth <= (index.X() + length)) { throw std::out_of_range("画像の幅を超える領域を指定することはできません。"); }
	size_t pos = sizeof(DIBFileHeader) + loader.FileHead().Offset() + ResolvePos(index);
	switch(ihead.BitCount)
	{
		case DIBBitDepth::Bit1:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit1>>();
			result.reserve(length);
			DIBLoadHelper::ReadFrom(loader.Stream(), result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit4:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit4>>();
			result.reserve(length);
			DIBLoadHelper::ReadFrom(loader.Stream(), result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit8:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit8>>();
			result.reserve(length);
			DIBLoadHelper::ReadFrom(loader.Stream(), result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit24:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit24>>();
			result.reserve(length);
			DIBLoadHelper::ReadFrom(loader.Stream(), result.data(), pos, length);
			return PixelVector(result);
		}
		default: { throw InvalidDIBFormatException("情報ヘッダのBitCountの内容が無効です。"); }
	}
}
size_t DIBCoreBitmapFileLoader::ResolvePos(const DisplayPoint& pos) const
{
	if ( (pos.X() < 0)||(pos.Y() < 0) ) { throw InvalidOperationException("posに指定されている座標が無効です。"); }
	if ( (ihead.ImageWidth <= pos.X())||(ihead.ImageHeight <= pos.Y()) ) { throw std::out_of_range("指定された座標はこの画像領域を超えています。"); }
	size_t pxl = (uint16_t(ihead.BitCount)/sizeof(uint8_t)) + (((uint16_t(ihead.BitCount)%sizeof(uint8_t)) != 0)?1:0);
	size_t w = pxl * ihead.ImageWidth + ((((pxl * ihead.ImageWidth) % 4) != 0)?(4-((pxl * ihead.ImageWidth)%4)):0);
	return (w * pos.Y()) + (pxl * pos.X());
}

DIBInfoBitmapFileLoader::DIBInfoBitmapFileLoader(DIBFileLoader&& loader) : loader(std::move(loader))
{
	if (loader.HeaderSize() < DIBInfoHeader::Size) { throw InvalidDIBFormatException("情報ヘッダの長さはInfoHeaderでサポートされる最小の長さよりも短いです。"); }
	DIBLoadHelper::ReadFrom(loader.Stream(), &ihead, sizeof(DIBFileHeader) + sizeof(int32_t));
	if (ihead.ComplessionMethod == BMPCompressionMethod::BITFIELDS)
	{
		auto colormaskdata = DIBRGBColorMask();
		DIBLoadHelper::Read(loader.Stream(), &colormaskdata);
		colormask = DIBColorMask(colormaskdata);
	}
	else if (ihead.ComplessionMethod == BMPCompressionMethod::ALPHABITFIELDS)
	{
		auto colormaskdata = DIBRGBAColorMask();
		DIBLoadHelper::Read(loader.Stream(), &colormaskdata);
		colormask = DIBColorMask(colormaskdata);
	}
	if (ihead.IndexedColorCount != 0)
	{
		auto lpal = std::vector<RGBTriple_t>();
		lpal.reserve(ihead.IndexedColorCount);
		DIBLoadHelper::ReadFrom(loader.Stream(), &lpal, sizeof(DIBFileHeader) + sizeof(DIBInfoHeader), ihead.IndexedColorCount);
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
			DIBLoadHelper::ReadFrom(loader.Stream(), &result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit4:
		{
			DIBPixelData<DIBBitDepth::Bit4> result;
			DIBLoadHelper::ReadFrom(loader.Stream(), &result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit8:
		{
			DIBPixelData<DIBBitDepth::Bit8> result;
			DIBLoadHelper::ReadFrom(loader.Stream(), &result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit16:
		{
			DIBPixelData<DIBBitDepth::Bit16> result;
			DIBLoadHelper::ReadFrom(loader.Stream(), &result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit24:
		{
			DIBPixelData<DIBBitDepth::Bit24> result;
			DIBLoadHelper::ReadFrom(loader.Stream(), &result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit32:
		{
			DIBPixelData<DIBBitDepth::Bit32> result;
			DIBLoadHelper::ReadFrom(loader.Stream(), &result, pos);
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
			DIBLoadHelper::ReadFrom(loader.Stream(), result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit4:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit4>>();
			result.reserve(length);
			DIBLoadHelper::ReadFrom(loader.Stream(), result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit8:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit8>>();
			result.reserve(length);
			DIBLoadHelper::ReadFrom(loader.Stream(), result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit16:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit16>>();
			result.reserve(length);
			DIBLoadHelper::ReadFrom(loader.Stream(), result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit24:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit24>>();
			result.reserve(length);
			DIBLoadHelper::ReadFrom(loader.Stream(), result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit32:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit32>>();
			result.reserve(length);
			DIBLoadHelper::ReadFrom(loader.Stream(), result.data(), pos, length);
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

DIBV4BitmapFileLoader::DIBV4BitmapFileLoader(DIBFileLoader&& loader) : loader(std::move(loader))
{
	if (loader.HeaderSize() < DIBV4Header::Size) { throw InvalidDIBFormatException("情報ヘッダの長さはV4Headerでサポートされる最小の長さよりも短いです。"); }
	DIBLoadHelper::ReadFrom(loader.Stream(), &ihead, sizeof(DIBFileHeader) + sizeof(int32_t));
	if (ihead.IndexedColorCount != 0)
	{
		auto lpal = std::vector<RGBTriple_t>();
		lpal.reserve(ihead.IndexedColorCount);
		DIBLoadHelper::ReadFrom(loader.Stream(), &lpal, sizeof(DIBFileHeader) + sizeof(DIBInfoHeader), ihead.IndexedColorCount);
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
			DIBLoadHelper::ReadFrom(loader.Stream(),&result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit4:
		{
			DIBPixelData<DIBBitDepth::Bit4> result;
			DIBLoadHelper::ReadFrom(loader.Stream(),&result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit8:
		{
			DIBPixelData<DIBBitDepth::Bit8> result;
			DIBLoadHelper::ReadFrom(loader.Stream(),&result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit16:
		{
			DIBPixelData<DIBBitDepth::Bit16> result;
			DIBLoadHelper::ReadFrom(loader.Stream(),&result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit24:
		{
			DIBPixelData<DIBBitDepth::Bit24> result;
			DIBLoadHelper::ReadFrom(loader.Stream(),&result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit32:
		{
			DIBPixelData<DIBBitDepth::Bit32> result;
			DIBLoadHelper::ReadFrom(loader.Stream(),&result, pos);
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
			DIBLoadHelper::ReadFrom(loader.Stream(),result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit4:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit4>>();
			result.reserve(length);
			DIBLoadHelper::ReadFrom(loader.Stream(),result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit8:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit8>>();
			result.reserve(length);
			DIBLoadHelper::ReadFrom(loader.Stream(),result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit16:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit16>>();
			result.reserve(length);
			DIBLoadHelper::ReadFrom(loader.Stream(),result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit24:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit24>>();
			result.reserve(length);
			DIBLoadHelper::ReadFrom(loader.Stream(),result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit32:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit32>>();
			result.reserve(length);
			DIBLoadHelper::ReadFrom(loader.Stream(),result.data(), pos, length);
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

DIBV5BitmapFileLoader::DIBV5BitmapFileLoader(DIBFileLoader&& loader) : loader(std::move(loader))
{
	if (loader.HeaderSize() < DIBV4Header::Size) { throw InvalidDIBFormatException("情報ヘッダの長さはV4Headerでサポートされる最小の長さよりも短いです。"); }
	DIBLoadHelper::ReadFrom(loader.Stream(), &ihead, sizeof(DIBFileHeader) + sizeof(int32_t));
	if (ihead.IndexedColorCount != 0)
	{
		auto lpal = std::vector<RGBTriple_t>();
		lpal.reserve(ihead.IndexedColorCount);
		DIBLoadHelper::ReadFrom(loader.Stream(), &lpal, sizeof(DIBFileHeader) + sizeof(DIBInfoHeader), ihead.IndexedColorCount);
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
			DIBLoadHelper::ReadFrom(loader.Stream(), &result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit4:
		{
			DIBPixelData<DIBBitDepth::Bit4> result;
			DIBLoadHelper::ReadFrom(loader.Stream(), &result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit8:
		{
			DIBPixelData<DIBBitDepth::Bit8> result;
			DIBLoadHelper::ReadFrom(loader.Stream(), &result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit16:
		{
			DIBPixelData<DIBBitDepth::Bit16> result;
			DIBLoadHelper::ReadFrom(loader.Stream(), &result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit24:
		{
			DIBPixelData<DIBBitDepth::Bit24> result;
			DIBLoadHelper::ReadFrom(loader.Stream(), &result, pos);
			return PixelData(result);
		}
		case DIBBitDepth::Bit32:
		{
			DIBPixelData<DIBBitDepth::Bit32> result;
			DIBLoadHelper::ReadFrom(loader.Stream(), &result, pos);
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
			DIBLoadHelper::ReadFrom(loader.Stream(), result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit4:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit4>>();
			result.reserve(length);
			DIBLoadHelper::ReadFrom(loader.Stream(), result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit8:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit8>>();
			result.reserve(length);
			DIBLoadHelper::ReadFrom(loader.Stream(), result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit16:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit16>>();
			result.reserve(length);
			DIBLoadHelper::ReadFrom(loader.Stream(), result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit24:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit24>>();
			result.reserve(length);
			DIBLoadHelper::ReadFrom(loader.Stream(), result.data(), pos, length);
			return PixelVector(result);
		}
		case DIBBitDepth::Bit32:
		{
			auto result = std::vector<DIBPixelData<DIBBitDepth::Bit32>>();
			result.reserve(length);
			DIBLoadHelper::ReadFrom(loader.Stream(), result.data(), pos, length);
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
