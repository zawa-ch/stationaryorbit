#include "stationaryorbit/exception/soexcept"
#include "stationaryorbit/graphics-wbmp/bmpimageinfomation.hpp"
using namespace zawa_ch::StationaryOrbit;

Graphics::ColorSystem Graphics::BMP::BMPImageInfomation::ConvertToColorSystem(const BMP::BitDepth& bitcnt)
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

Graphics::BMP::BitDepth Graphics::BMP::BMPImageInfomation::ConvertToColorDepth(const ColorSystem& system)
{
	if ((system == ColorSystem::IndexedColor)) return BMP::BitDepth::Bit8;
	else if ((system == ColorSystem::RGB)) return BMP::BitDepth::Bit32;
	else return BMP::BitDepth::Null;
}

Graphics::BMP::BMPImageInfomation::BMPImageInfomation(const Container& value)
	: _value(value)
{}

Graphics::BMP::BMPImageInfomation::BMPImageInfomation(const IImageInfomation& value)
	: _value(
		Container
		{
			value.getSize(),
			value.getColorSystem()
		}
	)
{}

Graphics::BMP::BMPImageInfomation::BMPImageInfomation(const BMP::CoreHeader& value)
	: _value(
		Container
		{
			Point(value.ImageWidth, value.ImageHeight),
			ConvertToColorSystem(value.BitCount),
			value.BitCount
		}
	)
{}

Graphics::BMP::BMPImageInfomation::BMPImageInfomation(const BMP::InfoHeader& value)
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

void Graphics::BMP::BMPImageInfomation::setColorSystem(const ColorSystem& value)
{
	_value.System = value;
	_value.BitCount = ConvertToColorDepth(_value.System);
}

void Graphics::BMP::BMPImageInfomation::setBitCount(const BMP::BitDepth& value)
{
	_value.BitCount = value;
	_value.System = ConvertToColorSystem(_value.BitCount);
}

bool Graphics::BMP::BMPImageInfomation::isCastableToCoreHeader() const
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

bool Graphics::BMP::BMPImageInfomation::isCastableToInfoHeader() const
{
	if (
		(_value.IndexedColorCount <= UINT32_MAX)&&
		(_value.ImportantColorCount <= UINT32_MAX)
	) return true;
	else return false;
}

Graphics::BMP::BMPImageInfomation::operator BMP::CoreHeader() const
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

Graphics::BMP::BMPImageInfomation::operator BMP::InfoHeader() const
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
