#include <algorithm>
#include <stdexcept>
#include "General/Exception"
#include "Graphics/Logic/Graphics.hpp"
#include "Graphics/Logic/BitmapBuffer.hpp"

size_t StationaryOrbit::Graphics::BitmapBuffer::CalcLength(const Point& size, const size_t& ch)
{
	return size.getX() * size.getY() * ch * sizeof(float);
}

float* StationaryOrbit::Graphics::BitmapBuffer::Allocate(const Point& size, const size_t& ch)
{
	// 画像サイズに負の値を設定している場合、std::out_of_rangeを投げる
	if (size.getX()<0 || size.getY()<0) { throw std::out_of_range(""); }

	// キャンバスのためのメモリを確保
	// (失敗した場合std::bad_allocが投げられる)
	size_t AllocateLength = CalcLength(size, ch);	///< Allocate()で確保を行うメモリの長さ。
	float* data = new float[AllocateLength];

	return data;
}

void StationaryOrbit::Graphics::BitmapBuffer::Deallocate(float* location)
{
	delete[] location;
}

StationaryOrbit::Graphics::BitmapBuffer::BitmapBuffer(const Point& size, const size_t& ch)
	: _size(size), _ch(ch), _data(Allocate(size, ch))
{}

StationaryOrbit::Graphics::BitmapBuffer::BitmapBuffer(const IImageInfomation& info)
	: BitmapBuffer(
		info.getSize(),
		Graphics::GetChannelFromColorSpace(info.getColorSystem())
	)
{}

StationaryOrbit::Graphics::BitmapBuffer::BitmapBuffer(const IBitmapBuffer& value)
	: BitmapBuffer(value.getSize(), value.getChannel())
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

StationaryOrbit::Graphics::BitmapBuffer::~BitmapBuffer()
{
	if (IsAllocated()) { Deallocate(_data); }
}

bool StationaryOrbit::Graphics::BitmapBuffer::IsAllocated() const
{
	return _data != NULL;
}

float StationaryOrbit::Graphics::BitmapBuffer::getPixel(const Point& pos, size_t ch) const
{
	if (_size.getX() <= pos.getX()) throw new std::out_of_range("x");
	if (_size.getY() <= pos.getY()) throw new std::out_of_range("y");
	if (_ch <= ch) throw new std::out_of_range("ch");
	float& target = _data[(pos.getY()*_size.getX() + pos.getX())*_ch + ch];
	return target;
}

void StationaryOrbit::Graphics::BitmapBuffer::setPixel(const Point& pos, size_t ch, const float& value)
{
	if (_size.getX() <= pos.getX()) throw new std::out_of_range("x");
	if (_size.getY() <= pos.getY()) throw new std::out_of_range("y");
	if (_ch <= ch) throw new std::out_of_range("ch");
	float& target = _data[(pos.getY()*_size.getX() + pos.getX())*_ch + ch];
	target = value;
}

StationaryOrbit::Graphics::BitmapBuffer& StationaryOrbit::Graphics::BitmapBuffer::operator=(const BitmapBuffer& value)
{
	// 確保済みの領域をすべて破棄する
	if (IsAllocated()) { Deallocate(_data); }
	// メモリ再確保
	_data = Allocate(value._size, value._ch);
	// 内容コピー
	std::copy<float*, float*>(_data, _data + CalcLength(value._size, value._ch), _data);

	return *this;
}
