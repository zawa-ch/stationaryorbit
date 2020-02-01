#include "stationaryorbit/graphics-core/imageinfomation.hpp"
using namespace zawa_ch::StationaryOrbit;

Graphics::ImageInfomation::ImageInfomation(const Container& value)
    : _value(value)
{}

Graphics::ImageInfomation::ImageInfomation(const IImageInfomation& value)
    : _value(Container{value.getSize(), value.getColorSystem()})
{}
