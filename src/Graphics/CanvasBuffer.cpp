#include <algorithm>
#include <stdexcept>
#include "General/Exception"
#include "Graphics/Logic/Graphics.hpp"
#include "Graphics/Logic/CanvasBuffer.hpp"

size_t StationaryOrbit::Graphics::CanvasBuffer::CalcLength(const ImageInfomation& info)
{ return info.getSize().getX() * info.getSize().getY() * Graphics::GetImageFormatLength(info.getFormat()) * info.getChannels(); }

StationaryOrbit::Byte* StationaryOrbit::Graphics::CanvasBuffer::Allocate(const ImageInfomation& info)
{
	// 画像サイズに負の値を設定している場合、std::out_of_rangeを投げる
	if (info.getSize().getX()<0 || info.getSize().getY()<0) { throw std::out_of_range(""); }

	// キャンバスのためのメモリを確保
	// (失敗した場合std::bad_allocが投げられる)
	size_t AllocateLength = CalcLength(info);	///< Allocate()で確保を行うメモリの長さ。
	Byte* data = new Byte[AllocateLength];

	return data;
}

void StationaryOrbit::Graphics::CanvasBuffer::Deallocate(Byte* location)
{
	delete[] location;
}

void StationaryOrbit::Graphics::CanvasBuffer::Copy(Byte* dest, Byte* src, ImageInfomation& info)
{
	std::copy<Byte*, Byte*>(src, src + CalcLength(info), dest);
}

StationaryOrbit::Graphics::CanvasBuffer::CanvasBuffer()
	: _data(), _info()
{}

StationaryOrbit::Graphics::CanvasBuffer::CanvasBuffer(const ImageInfomation& info)
	: _data(Allocate(info)), _info(info)
{}

StationaryOrbit::Graphics::CanvasBuffer::~CanvasBuffer()
{
	if (IsAllocated()) { Deallocate(_data); }
}

bool StationaryOrbit::Graphics::CanvasBuffer::IsAllocated() const
{ return _data != NULL; }

StationaryOrbit::Graphics::ImageInfomation StationaryOrbit::Graphics::CanvasBuffer::getInfomation() const
{ return _info; }

void StationaryOrbit::Graphics::CanvasBuffer::getPixel(void* dest, const Point& pos, size_t ch) const
{
	if (dest == NULL) throw new std::invalid_argument("dest");
	if (_info.getSize().getX() <= pos.getX()) throw new std::out_of_range("x");
	if (_info.getSize().getY() <= pos.getY()) throw new std::out_of_range("y");
	if (_info.getChannels() <= ch) throw new std::out_of_range("ch");
	Byte* spx = _data + (_info.getChannels() * (_info.getSize().getX() * pos.getY() + pos.getX()) + ch);
	Byte* dpx = (Byte*)dest;
	std::copy<Byte*, Byte*>(spx, spx + Graphics::GetImageFormatLength(_info.getFormat()), dpx);
}

void StationaryOrbit::Graphics::CanvasBuffer::setPixel(const void* value, const Point& pos, size_t ch)
{
	if (value == NULL) throw new std::invalid_argument("dest");
	if (_info.getSize().getX() <= pos.getX()) throw new std::out_of_range("x");
	if (_info.getSize().getY() <= pos.getY()) throw new std::out_of_range("y");
	if (_info.getChannels() <= ch) throw new std::out_of_range("ch");
	Byte* spx = (Byte*)value;
	Byte* dpx = _data + (_info.getChannels() * (_info.getSize().getX() * pos.getY() + pos.getX()) + ch);
	std::copy<Byte*, Byte*>(spx, spx + Graphics::GetImageFormatLength(_info.getFormat()), dpx);
}
