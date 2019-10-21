#include "Graphics/Logic/Bitmap.hpp"

StationaryOrbit::Graphics::Bitmap::Bitmap()
	: BitmapFrame(_buffer, _info)
{}

StationaryOrbit::Graphics::Bitmap::Bitmap(const ImageInfomation& info)
	: BitmapFrame(_buffer, _info), _buffer(info), _info(info)
{}
