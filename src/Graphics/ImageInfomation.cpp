#include "Graphics/Logic/ImageInfomation.hpp"

StationaryOrbit::Graphics::ImageInfomation::ImageInfomation()
	: _size(), _ch(), _format()
{}

StationaryOrbit::Graphics::Point StationaryOrbit::Graphics::ImageInfomation::getSize() const
{ return _size; }

void StationaryOrbit::Graphics::ImageInfomation::setSize(const Point& value)
{ _size = value; }

size_t StationaryOrbit::Graphics::ImageInfomation::getChannels() const
{ return _ch; }

void StationaryOrbit::Graphics::ImageInfomation::setChannels(const size_t& value)
{ _ch = value; }

StationaryOrbit::Graphics::ImageFormat StationaryOrbit::Graphics::ImageInfomation::getFormat() const
{ return _format; }

void StationaryOrbit::Graphics::ImageInfomation::setFormat(const ImageFormat& value)
{ _format = value; }
