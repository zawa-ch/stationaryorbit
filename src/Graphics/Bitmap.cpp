#include "Graphics/Logic/Bitmap.hpp"

StationaryOrbit::Graphics::Bitmap::Bitmap()
{}

StationaryOrbit::Graphics::Bitmap::Bitmap(const ImageInfomation& infoamtion)
	: buf(infoamtion), info(infoamtion)
{}
