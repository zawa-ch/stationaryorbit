#include "Graphics/BMP/Logic/BMPImageBitmap.hpp"

StationaryOrbit::Graphics::BMP::BMPImageBitmap::BMPImageBitmap()
    : BitmapFrame(_buffer, _info)
{}

StationaryOrbit::Graphics::BMP::BMPImageBitmap::BMPImageBitmap(const BMPImageInfomation& info)
    : BitmapFrame(_buffer, _info), _buffer(info), _info(info)
{}
