#include "Graphics/Logic/ImageInfomation.hpp"

StationaryOrbit::Graphics::ImageInfomation::ImageInfomation(const Container& value)
    : _value(value)
{}

StationaryOrbit::Graphics::ImageInfomation::ImageInfomation(const IImageInfomation& value)
    : _value(Container{value.getSize(), value.getColorDepth(), value.getColorSystem()})
{}
