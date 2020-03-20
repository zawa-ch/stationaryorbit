#include "stationaryorbit/graphics-wbmp/wbmpbuffer.hpp"
#include <vector>
using namespace zawa_ch::StationaryOrbit;
using namespace zawa_ch::StationaryOrbit::Graphics;
using namespace zawa_ch::StationaryOrbit::Graphics::WBMP;

/* TODO: トップダウン画像(画像高さが負の値)に対応する */
ColorMask WbmpRGBData::GetColorMask() const { return DefaultColorMask(GetBitDepth()); }
BitmapColorSpace WbmpRGBData::GetColorSpace() const { return BitmapColorSpace::ARGB; }
size_t WbmpRGBData::GetChannelCount() const noexcept { return 4; }
ReadOnlyProperty<BitmapBufferBase<uint8_t>, WbmpRGBData::ChannelValueType> WbmpRGBData::Index(const size_t& x, const size_t& y, const size_t& ch) const
{ return ReadOnlyProperty<BitmapBufferBase<uint8_t>, ChannelValueType>(*this, std::bind(getIndex, std::placeholders::_1, x, y, ch)); }
ReadOnlyProperty<BitmapBufferBase<uint8_t>, WbmpRGBData::ChannelValueType> WbmpRGBData::Index(const Point& pos, const size_t& ch) const { return Index(pos.getX(), pos.getY(), ch); }
Property<BitmapBufferBase<uint8_t>, WbmpRGBData::ChannelValueType> WbmpRGBData::Index(const size_t& x, const size_t& y, const size_t& ch)
{ return Property<BitmapBufferBase<uint8_t>, ChannelValueType>(*this, std::bind(getIndex, std::placeholders::_1, x, y, ch), std::bind(setIndex, std::placeholders::_1, x, y, ch, std::placeholders::_2)); }
Property<BitmapBufferBase<uint8_t>, WbmpRGBData::ChannelValueType> WbmpRGBData::Index(const Point& pos, const size_t& ch) { return Index(pos.getX(), pos.getY(), ch); }
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
WbmpRGBData::ChannelValueType WbmpRGBData::getIndex(const BitmapBufferBase<uint8_t>& inst, const size_t& x, const size_t& y, const size_t& ch)
{
	auto& cinst = dynamic_cast<const WbmpRGBData&>(inst);
	auto mask = cinst.GetColorMask();
	uint32_t result = cinst.GetPixel(x, y);
	size_t chlength;
	switch (ch)
	{
	case 0:
		result = mask.RedMask.GetAlignedFrom(result);
		chlength = mask.RedMask.Length();
		result <<= 8 - chlength;
		for (size_t i = 0; i < (8 / chlength); i++) { result |= result >> (chlength * i); }
		break;
	case 1:
		result = mask.GreenMask.GetAlignedFrom(result);
		chlength = mask.GreenMask.Length();
		result <<= 8 - chlength;
		for (size_t i = 0; i < (8 / chlength); i++) { result |= result >> (chlength * i); }
		break;
	case 2:
		result = mask.BlueMask.GetAlignedFrom(result);
		chlength = mask.BlueMask.Length();
		result <<= 8 - chlength;
		for (size_t i = 0; i < (8 / chlength); i++) { result |= result >> (chlength * i); }
		break;
	case 3:
		if (mask.AlphaMask.has_value())
		{
			result = mask.AlphaMask.value().GetAlignedFrom(result);
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
	uint32_t data = cinst.GetPixel(x, y);
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
	cinst.SetPixel(x, y, data);
}

WbmpRGBBuffer::WbmpRGBBuffer(const size_t& width, const size_t& height, const BitDepth& depth)
	: _width(width)
	, _height(height)
	, _depth(depth)
	, _data(CalcLength(width, height, depth))
{}
WbmpRGBBuffer::WbmpRGBBuffer(const Point& size, const BitDepth& depth)
	: _width(size.getX())
	, _height(size.getY())
	, _depth(depth)
	, _data(CalcLength(size.getX(), size.getY(), depth))
{}
std::vector<uint8_t>& WbmpRGBBuffer::Data() { return _data; }
const std::vector<uint8_t>& WbmpRGBBuffer::Data() const { return _data; }
size_t WbmpRGBBuffer::GetWidth() const noexcept { return _width; }
size_t WbmpRGBBuffer::GetHeight() const noexcept { return _height; }
BitDepth WbmpRGBBuffer::GetBitDepth() const noexcept { return _depth; }
uint32_t WbmpRGBBuffer::GetPixel(const size_t& x, const size_t& y) const
{
	if (GetWidth() <= x) { throw std::out_of_range("引数 x の値がビットマップの範囲を超えています。"); }
	if (GetHeight() <= y) { throw std::out_of_range("引数 y の値がビットマップの範囲を超えています。"); }
	auto ibyte = CalcIndex(x, y);
	auto length = (size_t(GetBitDepth()) / 8) + (((size_t(GetBitDepth())%8)!=0)?(1):(0));
	uint32_t result = 0;
	for (auto item : Range<size_t>(0, length)) { result |= (_data[ibyte + item]) << (item * 8); }
	return result;
}
void WbmpRGBBuffer::SetPixel(const size_t& x, const size_t& y, const uint32_t& value)
{
	if (GetWidth() <= x) { throw std::out_of_range("引数 x の値がビットマップの範囲を超えています。"); }
	if (GetHeight() <= y) { throw std::out_of_range("引数 y の値がビットマップの範囲を超えています。"); }
	auto ibyte = CalcIndex(x, y);
	auto length = (size_t(GetBitDepth()) / 8) + (((size_t(GetBitDepth())%8)!=0)?(1):(0));
	for (auto item : Range<size_t>(0, length)) { _data[ibyte + item] = value << (item * 8); }
}
size_t WbmpRGBBuffer::LinearLength() const noexcept { return CalcLength(GetWidth(), GetHeight(), GetBitDepth()); }
size_t WbmpRGBBuffer::CalcLength(const size_t& x, const size_t& y, const BitDepth& depth) noexcept { return CalcLineLength(x, depth) * y; }
size_t WbmpRGBBuffer::CalcLineLength(const size_t& x, const BitDepth& depth) noexcept
{
	auto linesize = size_t(depth) * x / 8;
	return linesize + (((linesize%4)!=0)?((4-(linesize%4))):(0));
}
size_t WbmpRGBBuffer::CalcIndex(const size_t& x, const size_t& y) const noexcept
{ return ((GetHeight() - y - 1) * CalcLineLength(GetWidth(), GetBitDepth())) + (x * size_t(GetBitDepth()) / 8); }

WbmpRGBStreamData::WbmpRGBStreamData(std::iostream& stream, const size_t& width, const size_t& height, const BitDepth& depth, std::streampos offset)
	: _stream(stream)
	, _width(width)
	, _height(height)
	, _depth(depth)
	, _offset(offset)
{}
WbmpRGBStreamData::WbmpRGBStreamData(std::iostream& stream, const Point& size, const BitDepth& depth, std::streampos offset)
	: _stream(stream)
	, _width(size.getX())
	, _height(size.getY())
	, _depth(depth)
	, _offset(offset)
{}
std::iostream& WbmpRGBStreamData::Stream() { return _stream; }
size_t WbmpRGBStreamData::GetWidth() const noexcept { return _width; }
size_t WbmpRGBStreamData::GetHeight() const noexcept { return _height; }
BitDepth WbmpRGBStreamData::GetBitDepth() const noexcept { return _depth; }
uint32_t WbmpRGBStreamData::GetPixel(const size_t& x, const size_t& y) const
{
	if (GetWidth() <= x) { throw std::out_of_range("引数 x の値がビットマップの範囲を超えています。"); }
	if (GetHeight() <= y) { throw std::out_of_range("引数 y の値がビットマップの範囲を超えています。"); }
	auto ibyte = CalcIndex(x, y);
	auto length = (size_t(GetBitDepth()) / 8) + (((size_t(GetBitDepth())%8)!=0)?(1):(0));
	uint32_t result = 0;
	_stream.seekg(_offset + std::streampos(ibyte));
	for (auto item : Range<size_t>(0, length)) { result |= uint32_t(_stream.get()) << (item * 8); }
	return result;
}
void WbmpRGBStreamData::SetPixel(const size_t& x, const size_t& y, const uint32_t& value)
{
	if (GetWidth() <= x) { throw std::out_of_range("引数 x の値がビットマップの範囲を超えています。"); }
	if (GetHeight() <= y) { throw std::out_of_range("引数 y の値がビットマップの範囲を超えています。"); }
	auto ibyte = CalcIndex(x, y);
	auto length = (size_t(GetBitDepth()) / 8) + (((size_t(GetBitDepth())%8)!=0)?(1):(0));
	_stream.seekp(_offset + std::streampos(ibyte));
	for (auto item : Range<size_t>(0, length)) { _stream.put(value << (item * 8)); }
}
size_t WbmpRGBStreamData::LinearLength() const noexcept { return CalcLength(GetWidth(), GetHeight(), GetBitDepth()); }
size_t WbmpRGBStreamData::CalcLength(const size_t& x, const size_t& y, const BitDepth& depth) noexcept { return CalcLineLength(x, depth) * y; }
size_t WbmpRGBStreamData::CalcLineLength(const size_t& x, const BitDepth& depth) noexcept
{
	auto linesize = size_t(depth) * x / 8;
	return linesize + (((linesize%4)!=0)?((4-(linesize%4))):(0));
}
size_t WbmpRGBStreamData::CalcIndex(const size_t& x, const size_t& y) const noexcept
{ return ((GetHeight() - y - 1) * CalcLineLength(GetWidth(), GetBitDepth())) + (x * size_t(GetBitDepth()) / 8); }