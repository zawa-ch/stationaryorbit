#include <algorithm>
#include <stdexcept>
#include "General/Exception"
#include "Graphics/Logic/Graphics.hpp"
#include "Graphics/Logic/CanvasBuffer.hpp"

size_t StationaryOrbit::Graphics::CanvasBuffer::CalcLength(const ImageInfomation& info)
{ return info.getSize().getX() * info.getSize().getY() * Graphics::GetLengthFromColorDepth(info.getColorDepth()) * Graphics::GetChannelFromColorSpace(info.getColorSystem()); }

std::byte* StationaryOrbit::Graphics::CanvasBuffer::Allocate(const ImageInfomation& info)
{
	// 画像サイズに負の値を設定している場合、std::out_of_rangeを投げる
	if (info.getSize().getX()<0 || info.getSize().getY()<0) { throw std::out_of_range(""); }

	// キャンバスのためのメモリを確保
	// (失敗した場合std::bad_allocが投げられる)
	size_t AllocateLength = CalcLength(info);	///< Allocate()で確保を行うメモリの長さ。
	std::byte* data = new std::byte[AllocateLength];

	return data;
}

void StationaryOrbit::Graphics::CanvasBuffer::Deallocate(std::byte* location)
{
	delete[] location;
}

void StationaryOrbit::Graphics::CanvasBuffer::Copy(std::byte* dest, std::byte* src, ImageInfomation& info)
{
	std::copy<std::byte*, std::byte*>(src, src + CalcLength(info), dest);
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
	if (Graphics::GetChannelFromColorSpace(_info.getColorSystem()) <= ch) throw new std::out_of_range("ch");
	std::byte* spx = _data + (Graphics::GetChannelFromColorSpace(_info.getColorSystem()) * (_info.getSize().getX() * pos.getY() + pos.getX()) + ch);
	std::byte* dpx = (std::byte*)dest;
	std::copy<std::byte*, std::byte*>(spx, spx + Graphics::GetLengthFromColorDepth(_info.getColorDepth()), dpx);
}

void StationaryOrbit::Graphics::CanvasBuffer::setPixel(const void* value, const Point& pos, size_t ch)
{
	if (value == NULL) throw new std::invalid_argument("dest");
	if (_info.getSize().getX() <= pos.getX()) throw new std::out_of_range("x");
	if (_info.getSize().getY() <= pos.getY()) throw new std::out_of_range("y");
	if (Graphics::GetChannelFromColorSpace(_info.getColorSystem()) <= ch) throw new std::out_of_range("ch");
	std::byte* spx = (std::byte*)value;
	std::byte* dpx = _data + (Graphics::GetChannelFromColorSpace(_info.getColorSystem()) * (_info.getSize().getX() * pos.getY() + pos.getX()) + ch);
	std::copy<std::byte*, std::byte*>(spx, spx + Graphics::GetLengthFromColorDepth(_info.getColorDepth()), dpx);
}
