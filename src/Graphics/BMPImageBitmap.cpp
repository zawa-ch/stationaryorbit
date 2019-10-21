#include "Graphics/Logic/BMPImageBitmap.hpp"

StationaryOrbit::Graphics::BMPImageBitmap::BMPImageBitmap()
    : BitmapFrame(_buffer, _info)
{}

StationaryOrbit::Graphics::BMPImageBitmap::BMPImageBitmap(const BMPImageInfomation& info)
    : BitmapFrame(_buffer, _info), _buffer(info), _info(info)
{}
