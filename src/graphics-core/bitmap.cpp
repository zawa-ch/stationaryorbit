#include "stationaryorbit/graphics-core/bitmap.hpp"
using namespace zawa_ch::StationaryOrbit::Graphics;

Bitmap::Iterator Bitmap::begin() noexcept { return Iterator(*this, 0); }
Bitmap::Iterator Bitmap::end() noexcept { return Iterator(*this, GetVerticalSize() * GetHorizonalSize()); }
Bitmap::ConstIterator Bitmap::cbegin() const noexcept { return ConstIterator(*this, 0); }
Bitmap::ConstIterator Bitmap::cend() const noexcept { return ConstIterator(*this, GetVerticalSize() * GetHorizonalSize()); }
Bitmap::ReverceIterator Bitmap::rbegin() noexcept { return ReverceIterator(*this, GetVerticalSize() * GetHorizonalSize()); }
Bitmap::ReverceIterator Bitmap::rend() noexcept { return ReverceIterator(*this, 0); }
Bitmap::ConstReverceIterator Bitmap::crbegin() const noexcept { return ConstReverceIterator(*this, GetVerticalSize() * GetHorizonalSize()); }
Bitmap::ConstReverceIterator Bitmap::crend() const noexcept { return ConstReverceIterator(*this, 0); }

Bitmap::Iterator::Iterator(Bitmap& container, const size_t& position) noexcept : _container(container), _pos(position) {}
PixelReference Bitmap::Iterator::Current() { return _container.Index(_pos % _container.GetHorizonalSize(), _pos / _container.GetHorizonalSize()); }
bool Bitmap::Iterator::Equals(const Iterator& other) const noexcept { return _pos == other._pos; }
PixelReference Bitmap::Iterator::operator*() { return Current(); }
Bitmap::Iterator& Bitmap::Iterator::operator++() noexcept { _pos++; return *this; }
bool Bitmap::Iterator::operator==(const Iterator& other) const noexcept { return Equals(other); }
bool Bitmap::Iterator::operator!=(const Iterator& other) const noexcept { return !Equals(other); }
PixelReference Bitmap::Iterator::operator->() { return Current(); }
Bitmap::Iterator& Bitmap::Iterator::operator--() noexcept { _pos--; return *this; }
Bitmap::ConstIterator::ConstIterator(const Bitmap& container, const size_t& position) noexcept : _container(container), _pos(position) {}
ConstPixelReference Bitmap::ConstIterator::Current() const { return _container.Index(_pos % _container.GetHorizonalSize(), _pos / _container.GetHorizonalSize()); }
bool Bitmap::ConstIterator::Equals(const ConstIterator& other) const noexcept { return _pos == other._pos; }
ConstPixelReference Bitmap::ConstIterator::operator*() const { return Current(); }
Bitmap::ConstIterator& Bitmap::ConstIterator::operator++() noexcept { _pos++; return *this; }
bool Bitmap::ConstIterator::operator==(const ConstIterator& other) const noexcept { return Equals(other); }
bool Bitmap::ConstIterator::operator!=(const ConstIterator& other) const noexcept { return !Equals(other); }
ConstPixelReference Bitmap::ConstIterator::operator->() const { return Current(); }
Bitmap::ConstIterator& Bitmap::ConstIterator::operator--() noexcept { _pos--; return *this; }
Bitmap::ReverceIterator::ReverceIterator(Bitmap& container, const size_t& position) noexcept : _container(container), _pos(position) {}
PixelReference Bitmap::ReverceIterator::Current() { return _container.Index((_pos - 1) % _container.GetHorizonalSize(), (_pos - 1) / _container.GetHorizonalSize()); }
bool Bitmap::ReverceIterator::Equals(const ReverceIterator& other) const noexcept { return _pos == other._pos; }
PixelReference Bitmap::ReverceIterator::operator*() { return Current(); }
Bitmap::ReverceIterator& Bitmap::ReverceIterator::operator++() noexcept { _pos--; return *this; }
bool Bitmap::ReverceIterator::operator==(const ReverceIterator& other) const noexcept { return Equals(other); }
bool Bitmap::ReverceIterator::operator!=(const ReverceIterator& other) const noexcept { return !Equals(other); }
PixelReference Bitmap::ReverceIterator::operator->() { return Current(); }
Bitmap::ReverceIterator& Bitmap::ReverceIterator::operator--() noexcept { _pos++; return *this; }
Bitmap::ConstReverceIterator::ConstReverceIterator(const Bitmap& container, const size_t& position) noexcept : _container(container), _pos(position) {}
ConstPixelReference Bitmap::ConstReverceIterator::Current() const { return _container.Index((_pos - 1) % _container.GetHorizonalSize(), (_pos - 1) / _container.GetHorizonalSize()); }
bool Bitmap::ConstReverceIterator::Equals(const ConstReverceIterator& other) const noexcept { return _pos == other._pos; }
ConstPixelReference Bitmap::ConstReverceIterator::operator*() const { return Current(); }
Bitmap::ConstReverceIterator& Bitmap::ConstReverceIterator::operator++() noexcept { _pos--; return *this; }
bool Bitmap::ConstReverceIterator::operator==(const ConstReverceIterator& other) const noexcept { return Equals(other); }
bool Bitmap::ConstReverceIterator::operator!=(const ConstReverceIterator& other) const noexcept { return !Equals(other); }
ConstPixelReference Bitmap::ConstReverceIterator::operator->() const { return Current(); }
Bitmap::ConstReverceIterator& Bitmap::ConstReverceIterator::operator--() noexcept { _pos++; return *this; }
