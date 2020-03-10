#include "stationaryorbit/graphics-wbmp/wbmpbuffer.hpp"
using namespace zawa_ch::StationaryOrbit::Graphics::WBMP;

WbmpBuffer::WbmpBuffer() : BitmapBuffer<uint8_t>() {}

WbmpBuffer::WbmpBuffer(const size_t& x, const size_t& y) : BitmapBuffer<uint8_t>(x, y, BitmapColorSpace::ARGB) {}

WbmpBuffer::WbmpBuffer(const Point& size) : BitmapBuffer<uint8_t>(size, BitmapColorSpace::ARGB) {}

WbmpBuffer::WbmpBuffer(const WbmpBufferBase& bitmap) : BitmapBuffer<uint8_t>(bitmap) {}
