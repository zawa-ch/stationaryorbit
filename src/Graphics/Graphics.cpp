#include "Graphics/Logic/Graphics.hpp"

size_t StationaryOrbit::Graphics::Graphics::GetLengthFromColorDepth(const ColorDepth &value)
{
	switch (value)
	{
	case StationaryOrbit::Graphics::ColorDepth::Binary :return 1U;
	case StationaryOrbit::Graphics::ColorDepth::I8 :	return 1U;
	case StationaryOrbit::Graphics::ColorDepth::I16 :	return 2U;
	case StationaryOrbit::Graphics::ColorDepth::F16 :	return 2U;
	case StationaryOrbit::Graphics::ColorDepth::F32 :	return 4U;
	default:    return 0U;
	}
}

size_t StationaryOrbit::Graphics::Graphics::GetChannelFromColorSpace(const ColorSystem& value)
{
	switch (value)
	{
	case ColorSystem::Gray:
	case ColorSystem::IndexedColor:
		return 1U;

	case ColorSystem::RGB:
	case ColorSystem::CMY:
	case ColorSystem::HSV:
	case ColorSystem::HSL:
	case ColorSystem::XYZ:
	case ColorSystem::Lab:
		return 4U;
	
	default:
		return 0U;
	}
}
