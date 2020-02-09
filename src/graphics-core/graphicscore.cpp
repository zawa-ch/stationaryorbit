#include "stationaryorbit/graphics-core/graphicscore.hpp"
using namespace zawa_ch::StationaryOrbit;

size_t Graphics::Graphics::GetChannelFromColorSpace(const ColorSystem& value)
{
	switch (value)
	{
	case ColorSystem::Gray:
	case ColorSystem::IndexedColor:
		return 1U;

	case ColorSystem::RGB:
	case ColorSystem::CMYK:
	case ColorSystem::HSV:
	case ColorSystem::HSL:
	case ColorSystem::XYZ:
	case ColorSystem::Lab:
		return 4U;
	
	default:
		return 0U;
	}
}