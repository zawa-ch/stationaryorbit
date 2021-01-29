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
	: loader(loader), offset(offset), bitdepth(bitdepth), size(size), length(size.Width() * size.Height())
{
	Reset();
}
bool DIBBitmapRGBDecoder::Next()
{
	if (IsAfterEnd()) { return false; }
	++current;
	if (IsAfterEnd()) { current = length; return false; }
	current_value = Get(ResolvePos(current));
	return true;
}
bool DIBBitmapRGBDecoder::Next(const IteratorTraits::IteratorDiff_t& count)
{
	if (IsAfterEnd()) { return false; }
	current += count;
	if (IsAfterEnd()) { current = length; return false; }
	current_value = Get(ResolvePos(current));
	return true;
}
bool DIBBitmapRGBDecoder::Previous()
{
	if (IsBeforeBegin()) { return false; }
	--current;
	if (IsBeforeBegin()) { current = -1; return false; }
	current_value = Get(ResolvePos(current));
	return true;
}
bool DIBBitmapRGBDecoder::Previous(const IteratorTraits::IteratorDiff_t& count)
{
	if (IsBeforeBegin()) { return false; }
	current -= count;
	if (IsBeforeBegin()) { current = -1; return false; }
	current_value = Get(ResolvePos(current));
	return true;
}
void DIBBitmapRGBDecoder::JumpTo(const DisplayPoint& pos)
{
	if ( (pos.X() < 0)||(pos.Y() < 0) ) { throw std::invalid_argument("posに指定されている座標が無効です。"); }
	current = ResolveIndex(pos);
	current_value = Get(pos);
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
	current_value = Get(ResolvePos(current));
}
bool DIBBitmapRGBDecoder::HasValue() const { return (0 <= current)&&(current < length); }
bool DIBBitmapRGBDecoder::IsBeforeBegin() const { return current < 0; }
bool DIBBitmapRGBDecoder::IsAfterEnd() const { return length <= current; }
Graphics::DisplayPoint DIBBitmapRGBDecoder::CurrentPos() const { return ResolvePos(current); }
DIBBitmapRGBDecoder::ValueType DIBBitmapRGBDecoder::Current() const { if (HasValue()) { return current_value; } else { throw InvalidOperationException("このイテレータは領域の範囲外を指しています。"); } }
void DIBBitmapRGBDecoder::Write(const ValueType& value)
{
	size_t tgt = offset + ResolveOffset(ResolvePos(current));
	switch(bitdepth)
	{
		case DIBBitDepth::Bit1:
		{
			auto w = std::get<DIBPixelData<DIBBitDepth::Bit1>>(value);
			DIBLoaderHelper::Write(loader, &w, tgt);
			break;
		}
		case DIBBitDepth::Bit4:
		{
			auto w = std::get<DIBPixelData<DIBBitDepth::Bit4>>(value);
			DIBLoaderHelper::Write(loader, &w, tgt);
			break;
		}
		case DIBBitDepth::Bit8:
		{
			auto w = std::get<DIBPixelData<DIBBitDepth::Bit8>>(value);
			DIBLoaderHelper::Write(loader, &w, tgt);
			break;
		}
		case DIBBitDepth::Bit16:
		{
			auto w = std::get<DIBPixelData<DIBBitDepth::Bit24>>(value);
			DIBLoaderHelper::Write(loader, &w, tgt);
			break;
		}
		case DIBBitDepth::Bit24:
		{
			auto w = std::get<DIBPixelData<DIBBitDepth::Bit24>>(value);
			DIBLoaderHelper::Write(loader, &w, tgt);
			break;
		}
		case DIBBitDepth::Bit32:
		{
			auto w = std::get<DIBPixelData<DIBBitDepth::Bit32>>(value);
			DIBLoaderHelper::Write(loader, &w, tgt);
			break;
		}
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
DIBBitmapRGBDecoder::ValueType DIBBitmapRGBDecoder::Get(const DisplayPoint& pos)
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
		case DIBBitDepth::Bit16:
		{
			auto result = DIBPixelData<DIBBitDepth::Bit16>();
			DIBLoaderHelper::Read(loader, &result, tgt);
			return ValueType(result);
		}
		case DIBBitDepth::Bit24:
		{
			auto result = DIBPixelData<DIBBitDepth::Bit24>();
			DIBLoaderHelper::Read(loader, &result, tgt);
			return ValueType(result);
		}
		case DIBBitDepth::Bit32:
		{
			auto result = DIBPixelData<DIBBitDepth::Bit32>();
			DIBLoaderHelper::Read(loader, &result, tgt);
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
	size_t pxl = (uint16_t(bitdepth)/sizeof(uint8_t)) + (((uint16_t(bitdepth)%sizeof(uint8_t)) != 0)?1:0);
	size_t w = pxl * size.Width() + ((((pxl * size.Width()) % 4) != 0)?(4-((pxl * size.Width())%4)):0);
	return (w * (size.Height() - pos.Y())) + (pxl * pos.X());
}
