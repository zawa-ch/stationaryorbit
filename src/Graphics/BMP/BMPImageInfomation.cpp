#include "General/Exception"
#include "Graphics/Logic/BMPImageInfomation.hpp"

StationaryOrbit::Graphics::ColorSystem StationaryOrbit::Graphics::BMPImageInfomation::ConvertToColorSystem(const BMP::BitDepth& bitcnt)
{
	switch (bitcnt)
	{
	case BMP::BitDepth::Bit1:
		return ColorSystem::IndexedColor;

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
	if ((system == ColorSystem::IndexedColor)) return BMP::BitDepth::Bit8;
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

bool StationaryOrbit::Graphics::BMPImageInfomation::isCastableToCoreHeader() const
{
	if (
		(INT16_MIN <= _value.Size.getX())&&
		(_value.Size.getX() <= INT16_MAX)&&
		(INT16_MIN <= _value.Size.getY())&&
		(_value.Size.getY() <= INT16_MAX)&&
		(_value.ComplessionMethod == BMP::CompressionMethod::RGB)
	) return true;
	else return false;
}

bool StationaryOrbit::Graphics::BMPImageInfomation::isCastableToInfoHeader() const
{
	if (
		(_value.IndexedColorCount <= UINT32_MAX)&&
		(_value.ImportantColorCount <= UINT32_MAX)
	) return true;
	else return false;
}

StationaryOrbit::Graphics::BMPImageInfomation::operator BMP::CoreHeader() const
{
	if (!isCastableToCoreHeader()) throw InvalidOperationException("Can't Castable.");
	BMP::CoreHeader result = 
	{
		uint32_t(BMP::CoreHeader::Size),
		uint16_t(_value.Size.getX()),
		uint16_t(_value.Size.getY()),
		1,
		_value.BitCount
	};
	return result;
}

StationaryOrbit::Graphics::BMPImageInfomation::operator BMP::InfoHeader() const
{
	if (!isCastableToInfoHeader()) throw InvalidOperationException("Can't Castable.");
	BMP::InfoHeader result = 
	{
		uint32_t(BMP::InfoHeader::Size),
		_value.Size.getX(),
		_value.Size.getY(),
		1,
		_value.BitCount,
		_value.ComplessionMethod,
		0,
		uint32_t(_value.Resolution.getX()),
		uint32_t(_value.Resolution.getY()),
		uint32_t(_value.IndexedColorCount),
		uint32_t(_value.ImportantColorCount)
	};
	return result;
}
