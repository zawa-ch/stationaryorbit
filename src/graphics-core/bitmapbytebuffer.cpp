#include <algorithm>
#include <stdexcept>
#include "General/Exception"
#include "Graphics/Logic/Graphics.hpp"
#include "Graphics/Logic/BitmapByteBuffer.hpp"

size_t StationaryOrbit::Graphics::BitmapByteBuffer::CalcLength(const Point& size, const size_t& ch)
{
	return size.getX() * size.getY() * ch * sizeof(uint8_t);
}

uint8_t* StationaryOrbit::Graphics::BitmapByteBuffer::Allocate(const Point& size, const size_t& ch)
{
	// 画像サイズに負の値を設定している場合、std::out_of_rangeを投げる
	if (size.getX()<0 || size.getY()<0) { throw std::out_of_range(""); }

	// キャンバスのためのメモリを確保
	// (失敗した場合std::bad_allocが投げられる)
	size_t AllocateLength = CalcLength(size, ch);	///< Allocate()で確保を行うメモリの長さ。
	uint8_t* data = new uint8_t[AllocateLength];

	return data;
}

void StationaryOrbit::Graphics::BitmapByteBuffer::Deallocate(uint8_t* location)
{
	delete[] location;
}

StationaryOrbit::Graphics::BitmapByteBuffer::BitmapByteBuffer(const Point& size, const size_t& ch)
	: _size(size), _ch(ch), _data(Allocate(size, ch))
{}

StationaryOrbit::Graphics::BitmapByteBuffer::BitmapByteBuffer(const IImageInfomation& info)
	: BitmapByteBuffer(
		info.getSize(),
		Graphics::GetChannelFromColorSpace(info.getColorSystem())
	)
{}

StationaryOrbit::Graphics::BitmapByteBuffer::BitmapByteBuffer(const IBitmapBuffer& value)
	: BitmapByteBuffer(value.getSize(), value.getChannel())
{
	for (int x = 0; x < _size.getX(); x++)
	{
		for (int y = 0; y < _size.getY(); y++)
		{
			Point pos = Point(x, y);
			for (size_t ch = 0; ch < _ch; ch++)
			{
				setPixel(pos, ch, value.getPixel(pos, ch));
			}
		}
	}
}

StationaryOrbit::Graphics::BitmapByteBuffer::~BitmapByteBuffer()
{
	if (IsAllocated()) { Deallocate(_data); }
}

bool StationaryOrbit::Graphics::BitmapByteBuffer::IsAllocated() const
{
	return _data != NULL;
}

float StationaryOrbit::Graphics::BitmapByteBuffer::getPixel(const Point& pos, size_t ch) const
{
	if (_size.getX() <= pos.getX()) throw new std::out_of_range("x");
	if (_size.getY() <= pos.getY()) throw new std::out_of_range("y");
	if (_ch <= ch) throw new std::out_of_range("ch");
	uint8_t& target = _data[(pos.getY()*_size.getX() + pos.getX())*_ch + ch];
	return float(target) / UINT8_MAX;
}

std::byte StationaryOrbit::Graphics::BitmapByteBuffer::getPixelRaw(const Point& pos, size_t ch) const
{
	if (_size.getX() <= pos.getX()) throw new std::out_of_range("x");
	if (_size.getY() <= pos.getY()) throw new std::out_of_range("y");
	if (_ch <= ch) throw new std::out_of_range("ch");
	uint8_t& target = _data[(pos.getY()*_size.getX() + pos.getX())*_ch + ch];
	return std::byte(target);
}

void StationaryOrbit::Graphics::BitmapByteBuffer::setPixel(const Point& pos, size_t ch, const float& value)
{
	if (_size.getX() <= pos.getX()) throw new std::out_of_range("x");
	if (_size.getY() <= pos.getY()) throw new std::out_of_range("y");
	if (_ch <= ch) throw new std::out_of_range("ch");
	uint8_t& target = _data[(pos.getY()*_size.getX() + pos.getX())*_ch + ch];
	target = uint8_t(value * UINT8_MAX);
}

void StationaryOrbit::Graphics::BitmapByteBuffer::setPixelRaw(const Point& pos, size_t ch, const std::byte& value)
{
	if (_size.getX() <= pos.getX()) throw new std::out_of_range("x");
	if (_size.getY() <= pos.getY()) throw new std::out_of_range("y");
	if (_ch <= ch) throw new std::out_of_range("ch");
	uint8_t& target = _data[(pos.getY()*_size.getX() + pos.getX())*_ch + ch];
	target = uint8_t(value);
}

StationaryOrbit::Graphics::BitmapByteBuffer& StationaryOrbit::Graphics::BitmapByteBuffer::operator=(const BitmapByteBuffer& value)
{
	// 確保済みの領域をすべて破棄する
	if (IsAllocated()) { Deallocate(_data); }
	// メモリ再確保
	_data = Allocate(value._size, value._ch);
	// 内容コピー
	_size = value._size;
	_ch = value._ch;
	std::copy<uint8_t*, uint8_t*>(value._data, value._data + CalcLength(value._size, value._ch), _data);

	return *this;
}
