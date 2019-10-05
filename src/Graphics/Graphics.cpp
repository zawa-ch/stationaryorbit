#include "LogicClass/Graphics/Graphics.hpp"

size_t StationaryOrbit::Graphics::Graphics::GetImageFormatLength(const ImageFormat &value)
{
	switch (value)
	{
	case StationaryOrbit::Graphics::ImageFormat::Binary :	return 1;
	case StationaryOrbit::Graphics::ImageFormat::Index8 :	return 1;
	case StationaryOrbit::Graphics::ImageFormat::Tone8 :	return 1;
	case StationaryOrbit::Graphics::ImageFormat::Tone16 :	return 2;
	case StationaryOrbit::Graphics::ImageFormat::ColorF16 :	return 2;
	case StationaryOrbit::Graphics::ImageFormat::ColorF32 :	return 4;
	case StationaryOrbit::Graphics::ImageFormat::ColorF64 :	return 8;
	default:    return 0;
	}
}
