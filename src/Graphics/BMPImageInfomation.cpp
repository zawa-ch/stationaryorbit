#include "General/Exception"
#include "Graphics/Logic/BMPImageInfomation.hpp"

StationaryOrbit::Graphics::ColorSystem StationaryOrbit::Graphics::BMPImageInfomation::ConvertToColorSystem(const BMP::BitDepth& bitcnt)
{
	switch (bitcnt)
	{
	case BMP::BitDepth::Bit1:
		return ColorSystem::Gray;

	case BMP::BitDepth::Bit4:
		return ColorSystem::IndexedColor;

	case BMP::BitDepth::Bit8:
		return ColorSystem::IndexedColor;

	case BMP::BitDepth::Bit16:
		return ColorSystem::RGB;

	case BMP::BitDepth::Bit24:
		return ColorSystem::RGB;

	case BMP::BitDepth::Bit32:
		return ColorSystem::RGB;
	
	default:
		throw InvalidOperationException("Value 'value.BitCount' is not valid.");
	}
}

StationaryOrbit::Graphics::BMP::BitDepth StationaryOrbit::Graphics::BMPImageInfomation::ConvertToColorDepth(const ColorSystem& system)
{
	if ((system == ColorSystem::Gray)) return BMP::BitDepth::Bit1;
	else if ((system == ColorSystem::IndexedColor)) return BMP::BitDepth::Bit8;
	else if ((system == ColorSystem::RGB)) return BMP::BitDepth::Bit32;
	else return BMP::BitDepth::Null;
}

StationaryOrbit::Graphics::BMPImageInfomation::BMPImageInfomation(const Container& value)
	: _value(value)
{}

StationaryOrbit::Graphics::BMPImageInfomation::BMPImageInfomation(const IImageInfomation& value)
	: _value(
		Container
		{
			value.getSize(),
			value.getColorSystem()
		}
	)
{}

StationaryOrbit::Graphics::BMPImageInfomation::BMPImageInfomation(const BMP::CoreHeader& value)
	: _value(
		Container
		{
			Point(value.ImageWidth, value.ImageHeight),
			ConvertToColorSystem(value.BitCount),
			value.BitCount
		}
	)
{}

StationaryOrbit::Graphics::BMPImageInfomation::BMPImageInfomation(const BMP::InfoHeader& value)
	: _value(
		Container
		{
			Point(value.ImageWidth, value.ImageHeight),
			ConvertToColorSystem(value.BitCount),
			value.BitCount,
			value.ComplessionMethod,
			Point(value.ResolutionHolizonal, value.ResolutionVertical),
			value.IndexedColorCount,
			value.ImportantColorCount
		}
	)
{}

void StationaryOrbit::Graphics::BMPImageInfomation::setColorSystem(const ColorSystem& value)
{
	_value.System = value;
	_value.BitCount = ConvertToColorDepth(_value.System);
}

void StationaryOrbit::Graphics::BMPImageInfomation::setBitCount(const BMP::BitDepth& value)
{
	_value.BitCount = value;
	_value.System = ConvertToColorSystem(_value.BitCount);
}
