#include "stationaryorbit/graphics-wbmp/wbmpbuffer.hpp"
#include <vector>
using namespace zawa_ch::StationaryOrbit;
using namespace zawa_ch::StationaryOrbit::Graphics;
using namespace zawa_ch::StationaryOrbit::Graphics::WBMP;

/* TODO: トップダウン画像(画像高さが負の値)に対応する */
BitmapColorSpace WbmpRGBData::GetColorSpace() const { return BitmapColorSpace::ARGB; }
size_t WbmpRGBData::GetChannelCount() const noexcept { return 4; }
ReadOnlyProperty<BitmapBufferBase<uint8_t>, WbmpRGBData::ChannelValueType> WbmpRGBData::Index(const size_t& x, const size_t& y, const size_t& ch) const
{ return ReadOnlyProperty<BitmapBufferBase<uint8_t>, ChannelValueType>(*this, std::bind(getIndex, std::placeholders::_1, x, y, ch)); }
ReadOnlyProperty<BitmapBufferBase<uint8_t>, WbmpRGBData::ChannelValueType> WbmpRGBData::Index(const Point& pos, const size_t& ch) const { return Index(pos.getX(), pos.getY(), ch); }
Property<BitmapBufferBase<uint8_t>, WbmpRGBData::ChannelValueType> WbmpRGBData::Index(const size_t& x, const size_t& y, const size_t& ch)
{ return Property<BitmapBufferBase<uint8_t>, ChannelValueType>(*this, std::bind(getIndex, std::placeholders::_1, x, y, ch), std::bind(setIndex, std::placeholders::_1, x, y, ch, std::placeholders::_2)); }
Property<BitmapBufferBase<uint8_t>, WbmpRGBData::ChannelValueType> WbmpRGBData::Index(const Point& pos, const size_t& ch) { return Index(pos.getX(), pos.getY(), ch); }
uint32_t WbmpRGBData::GetImageSize() const noexcept { return CalcLength(GetWidth(), GetHeight(), GetBitDepth()); }
size_t WbmpRGBData::CalcLength(const size_t& x, const size_t& y, const BitDepth& depth) noexcept { return CalcLineLength(x, depth) * y; }
size_t WbmpRGBData::CalcLineLength(const size_t& x, const BitDepth& depth) noexcept
{
	auto linesize = size_t(depth) * x / 8;
	return linesize + (((linesize%4)!=0)?((4-(linesize%4))):(0));
}
ColorMask WbmpRGBData::DefaultColorMask(const BitDepth& depth)
{
	switch (depth)
	{
	case BitDepth::Bit1:
	case BitDepth::Bit4:
	case BitDepth::Bit8:
		throw InvalidOperationException("指定された depth には対応していません。");
	case BitDepth::Bit16:
		return ColorMask{ BitMask<uint32_t>(0x7C00), BitMask<uint32_t>(0x03E0), BitMask<uint32_t>(0x001F), std::nullopt };
	case BitDepth::Bit24:
	case BitDepth::Bit32:
		return ColorMask{ BitMask<uint32_t>(0x00FF0000), BitMask<uint32_t>(0x0000FF00), BitMask<uint32_t>(0x000000FF), std::nullopt };
	case BitDepth::Null:
	default:
		throw std::invalid_argument("depth に指定された値が無効です。");
	}
}
size_t WbmpRGBData::calcIndex(const size_t& x, const size_t& y) const noexcept
{ return ((GetHeight() - y - 1) * CalcLineLength(GetWidth(), GetBitDepth())) + (x * size_t(GetBitDepth()) / 8); }
WbmpRGBData::ChannelValueType WbmpRGBData::getIndex(const BitmapBufferBase<uint8_t>& inst, const size_t& x, const size_t& y, const size_t& ch)
{
	auto& cinst = dynamic_cast<const WbmpRGBData&>(inst);
	if (cinst.GetWidth() <= x) { throw std::out_of_range("引数 x の値がビットマップの範囲を超えています。"); }
	if (cinst.GetHeight() <= y) { throw std::out_of_range("引数 y の値がビットマップの範囲を超えています。"); }
	auto ibyte = cinst.calcIndex(x, y);
	auto lengthbit = size_t(cinst.GetBitDepth());
	auto lengthbyte = (lengthbit / 8) + (((lengthbit%8)!=0)?(1):(0));
	uint32_t data = 0;
	for (auto item : Range<size_t>(0, lengthbyte)) { data |= (cinst.LinearIndex(ibyte + item)) << (item * 8); }
	auto mask = cinst.GetColorMask();
	uint32_t result;
	size_t chlength;
	switch (ch)
	{
	case 0:
		result = mask.RedMask.GetAlignedFrom(data);
		chlength = mask.RedMask.Length();
		result <<= 8 - chlength;
		for (size_t i = 0; i < (8 / chlength); i++) { result |= result >> (chlength * i); }
		break;
	case 1:
		result = mask.GreenMask.GetAlignedFrom(data);
		chlength = mask.GreenMask.Length();
		result <<= 8 - chlength;
		for (size_t i = 0; i < (8 / chlength); i++) { result |= result >> (chlength * i); }
		break;
	case 2:
		result = mask.BlueMask.GetAlignedFrom(data);
		chlength = mask.BlueMask.Length();
		result <<= 8 - chlength;
		for (size_t i = 0; i < (8 / chlength); i++) { result |= result >> (chlength * i); }
		break;
	case 3:
		if (mask.AlphaMask.has_value())
		{
			result = mask.AlphaMask.value().GetAlignedFrom(data);
			chlength = mask.AlphaMask.value().Length();
			result <<= 8 - chlength;
			for (size_t i = 0; i < (8 / chlength); i++) { result |= result >> (chlength * i); }
			break;
		}
		else
		{
			result = ChannelValueType::Max().value;
			break;
		}
	default:
		throw std::out_of_range("引数 ch の値がビットマップの範囲を超えています。");
	}
	return ChannelValueType(result);
}
void WbmpRGBData::setIndex(BitmapBufferBase<uint8_t>& inst, const size_t& x, const size_t& y, const size_t& ch, const ChannelValueType& value)
{
	auto& cinst = dynamic_cast<WbmpRGBData&>(inst);
	if (cinst.GetWidth() <= x) { throw std::out_of_range("引数 x の値がビットマップの範囲を超えています。"); }
	if (cinst.GetHeight() <= y) { throw std::out_of_range("引数 y の値がビットマップの範囲を超えています。"); }
	auto ibyte = cinst.calcIndex(x, y);
	auto lengthbit = size_t(cinst.GetBitDepth());
	auto lengthbyte = (lengthbit / 8) + (((lengthbit%8)!=0)?(1):(0));
	uint32_t data = 0;
	for (auto item : Range<size_t>(0, lengthbyte)) { data |= (cinst.LinearIndex(ibyte + item)) << (item * 8); }
	auto mask = cinst.GetColorMask();
	auto maskedvalue = value.value;
	switch (ch)
	{
	case 0:
		maskedvalue >>= 8 - mask.RedMask.Length();
		data = mask.RedMask.SetAlignedTo(data, value);
		break;
	case 1:
		maskedvalue >>= 8 - mask.GreenMask.Length();
		data = mask.GreenMask.SetAlignedTo(data, value);
		break;
	case 2:
		maskedvalue >>= 8 - mask.BlueMask.Length();
		data = mask.BlueMask.SetAlignedTo(data, value);
		break;
	case 3:
		if (mask.AlphaMask.has_value())
		{
			maskedvalue >>= 8 - mask.AlphaMask.value().Length();
			data = mask.AlphaMask.value().SetAlignedTo(data, value);
		}
		break;
	default:
		throw std::out_of_range("引数 ch の値がビットマップの範囲を超えています。");
	}
	for (auto item : Range<size_t>(0, lengthbyte)) { cinst.LinearIndex(ibyte + item) = data << (item * 8); }
}

WbmpRGBBuffer::WbmpRGBBuffer(const size_t& x, const size_t& y, const BitDepth& depth)
	: _x(x)
	, _y(y)
	, _depth(depth)
	, _mask(WbmpRGBData::DefaultColorMask(depth))
	, _data(WbmpRGBData::CalcLength(x, y, depth))
{}
WbmpRGBBuffer::WbmpRGBBuffer(const Point& size, const BitDepth& depth)
	: _x(size.getX())
	, _y(size.getY())
	, _depth(depth)
	, _mask(WbmpRGBData::DefaultColorMask(depth))
	, _data(WbmpRGBData::CalcLength(size.getX(), size.getY(), depth))
{}
WbmpRGBBuffer::WbmpRGBBuffer(const size_t& x, const size_t& y, const BitDepth& depth, const ColorMask& mask)
	: _x(x)
	, _y(y)
	, _depth(depth)
	, _mask(mask)
	, _data(WbmpRGBData::CalcLength(x, y, depth))
{}
WbmpRGBBuffer::WbmpRGBBuffer(const Point& size, const BitDepth& depth, const ColorMask& mask)
	: _x(size.getX())
	, _y(size.getY())
	, _depth(depth)
	, _mask(mask)
	, _data(WbmpRGBData::CalcLength(size.getX(), size.getY(), depth))
{}
size_t WbmpRGBBuffer::GetWidth() const noexcept { return _x; }
size_t WbmpRGBBuffer::GetHeight() const noexcept { return _y; }
BitDepth WbmpRGBBuffer::GetBitDepth() const noexcept { return _depth; }
size_t WbmpRGBBuffer::LinearLength() const noexcept { return _data.size(); }
uint8_t& WbmpRGBBuffer::LinearIndex(const size_t& position) { return _data[position]; }
const uint8_t& WbmpRGBBuffer::LinearIndex(const size_t& position) const { return _data[position]; }
ColorMask WbmpRGBBuffer::GetColorMask() const { return _mask; }
