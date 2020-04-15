#include "stationaryorbit/graphics-core/binarybitmap.hpp"
using namespace zawa_ch::StationaryOrbit;
using namespace zawa_ch::StationaryOrbit::Graphics;

BinaryBitmap::BinaryBitmap(const RectangleSize& size) : BitmapBase<bool>(size, Channel) {}
BinaryBitmap::BinaryBitmap(const int& width, const int& height) : BitmapBase<bool>(width, height, Channel) {}
BinaryBitmap::BinaryBitmap(const BitmapBase<bool>& data) : BitmapBase<bool>(data) {}
BinaryBitmap::BinaryBitmap(BitmapBase<bool>&& data) : BitmapBase<bool>(data) {}
Property<BinaryBitmap, ChannelValue<bool>> BinaryBitmap::Index(const DisplayPoint& position) { return Property<BinaryBitmap, ChannelValue<bool>>(*this, std::bind(getIndex, std::placeholders::_1, position), std::bind(setIndex, std::placeholders::_1, position, std::placeholders::_2)); }
Property<BinaryBitmap, ChannelValue<bool>> BinaryBitmap::Index(const int& x, const int& y) { return Index(DisplayPoint(x, y)); }
Property<BinaryBitmap, ChannelValue<bool>> BinaryBitmap::operator[](const DisplayPoint& position) { return Index(position); }
ReadOnlyProperty<BinaryBitmap, ChannelValue<bool>> BinaryBitmap::Index(const DisplayPoint& position) const { return ReadOnlyProperty<BinaryBitmap, ChannelValue<bool>>(*this, std::bind(getIndex, std::placeholders::_1, position)); }
ReadOnlyProperty<BinaryBitmap, ChannelValue<bool>> BinaryBitmap::Index(const int& x, const int& y) const { return Index(DisplayPoint(x, y)); }
ReadOnlyProperty<BinaryBitmap, ChannelValue<bool>> BinaryBitmap::operator[](const DisplayPoint& position) const { return Index(position); }
BinaryBitmap BinaryBitmap::ReinterpretFrom(const BitmapBase<bool>& data)
{
	if (data.Channels() != Channel) { throw std::invalid_argument("指定された data のチャネル数はこのクラスではサポートされていません。"); }
	return BinaryBitmap(data);
}
BinaryBitmap BinaryBitmap::ReinterpretFrom(BitmapBase<bool>&& data)
{
	if (data.Channels() != Channel) { throw std::invalid_argument("指定された data のチャネル数はこのクラスではサポートされていません。"); }
	return BinaryBitmap(data);
}
ChannelValue<bool> BinaryBitmap::getIndex(const BinaryBitmap& inst, const DisplayPoint& position)
{
	auto px = inst.BitmapBase<bool>::Index(position);
	return px[0];
}
void BinaryBitmap::setIndex(BinaryBitmap& inst, const DisplayPoint& position, const ChannelValue<bool>& value)
{
	auto px = inst.BitmapBase<bool>::Index(position);
	px[0] = value;
}
