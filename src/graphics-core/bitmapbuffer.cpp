#include <algorithm>
#include "stationaryorbit/graphics-core/graphicscore.hpp"
#include "stationaryorbit/graphics-core/bitmapbuffer.hpp"
using namespace zawa_ch::StationaryOrbit;

size_t Graphics::BitmapBuffer::CalcLength(const Point& size, const size_t& ch)
{
	return size.getX() * size.getY() * ch * sizeof(float);
}

float* Graphics::BitmapBuffer::Allocate(const Point& size, const size_t& ch)
{
	// 画像サイズに負の値を設定している場合、std::out_of_rangeを投げる
	if (size.getX()<0 || size.getY()<0) { throw std::out_of_range(""); }

	// キャンバスのためのメモリを確保
	// (失敗した場合std::bad_allocが投げられる)
	size_t AllocateLength = CalcLength(size, ch);	///< Allocate()で確保を行うメモリの長さ。
	float* data = new float[AllocateLength];

	return data;
}

void Graphics::BitmapBuffer::Deallocate() noexcept
{
	if (IsAllocated())
	{
		delete[] _data;
		_data = NULL;
	}
}

Graphics::BitmapBuffer::BitmapBuffer(const Point& size, const size_t& ch)
	: _size(size), _ch(ch), _data(Allocate(size, ch))
{}

Graphics::BitmapBuffer::BitmapBuffer(const IImageInfomation& info)
	: BitmapBuffer(
		info.getSize(),
		Graphics::GetChannelFromColorSpace(info.getColorSystem())
	)
{}

Graphics::BitmapBuffer::BitmapBuffer(const IBitmapBuffer& value)
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

Graphics::BitmapBuffer::~BitmapBuffer()
{
	Deallocate();
}

bool Graphics::BitmapBuffer::IsAllocated() const
{
	return _data != NULL;
}

float Graphics::BitmapBuffer::getPixel(const Point& pos, size_t ch) const
{
	if (_size.getX() <= pos.getX()) throw new std::out_of_range("x");
	if (_size.getY() <= pos.getY()) throw new std::out_of_range("y");
	if (_ch <= ch) throw new std::out_of_range("ch");
	float& target = _data[(pos.getY()*_size.getX() + pos.getX())*_ch + ch];
	return target;
}

void Graphics::BitmapBuffer::setPixel(const Point& pos, size_t ch, const float& value)
{
	if (_size.getX() <= pos.getX()) throw new std::out_of_range("x");
	if (_size.getY() <= pos.getY()) throw new std::out_of_range("y");
	if (_ch <= ch) throw new std::out_of_range("ch");
	float& target = _data[(pos.getY()*_size.getX() + pos.getX())*_ch + ch];
	target = value;
}

Graphics::BitmapBuffer& Graphics::BitmapBuffer::operator=(const BitmapBuffer& value)
{
	// 確保済みの領域をすべて破棄する
	Deallocate();
	// メモリ再確保
	_data = Allocate(value._size, value._ch);
	// 内容コピー
	_size = value._size;
	_ch = value._ch;
	std::copy<float*, float*>(value._data, value._data + CalcLength(value._size, value._ch), _data);

	return *this;
}
