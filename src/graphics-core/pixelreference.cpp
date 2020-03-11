#include "stationaryorbit/graphics-core/pixelreference.hpp"
#include "stationaryorbit/graphics-core/bitmap.hpp"
using namespace zawa_ch::StationaryOrbit::Graphics;

ConstPixelReference::ConstPixelReference(const Bitmap& bitmap, const size_t& x, const size_t& y) noexcept : _cbitmap(bitmap), _x(x), _y(y) {}
ConstPixelReference::ConstPixelReference(const Bitmap& bitmap, const Point& position) noexcept : _cbitmap(bitmap), _x(position.getX()), _y(position.getY()) {}
const Bitmap& ConstPixelReference::GetBitmap() const { return _cbitmap; }
Point ConstPixelReference::Position() const noexcept { return Point(_x, _y); }
RGBColor ConstPixelReference::GetRGBValue() const { return _cbitmap.GetRGB(_x, _y); }
bool ConstPixelReference::HasValue() const noexcept { if ((_cbitmap.GetWidth() > _x)&&(_cbitmap.GetHeight() > _y)) { return true; } else { return false; } }
bool ConstPixelReference::HasOffset(const Point& offset) const noexcept { return Offset(offset).HasValue(); }
ConstPixelReference ConstPixelReference::Offset(const Point& offset) const noexcept { return ConstPixelReference(_cbitmap, Position() + offset); }

PixelReference::PixelReference(Bitmap& bitmap, const size_t& x, const size_t& y) noexcept : ConstPixelReference(bitmap, x, y), _bitmap(bitmap) {}
PixelReference::PixelReference(Bitmap& bitmap, const Point& position) noexcept : ConstPixelReference(bitmap, position), _bitmap(bitmap) {}
void PixelReference::SetValue(const RGBColor& value) { _bitmap.SetRGB(_x, _y, value); }
PixelReference PixelReference::Offset(const Point& offset) noexcept { return PixelReference(_bitmap, Position() + offset); }
