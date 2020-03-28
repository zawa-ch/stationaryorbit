#include "stationaryorbit/graphics-wbmp/dibbitmap.hpp"
#include "fileheader.hpp"
using namespace zawa_ch::StationaryOrbit;
using namespace zawa_ch::StationaryOrbit::Graphics;
using namespace zawa_ch::StationaryOrbit::Graphics::DIB;

DIBBitmap::DIBBitmap() : BitmapBase<uint8_t>(), _cindex() {}
DIBBitmap::DIBBitmap(const BitmapBase<uint8_t>& data) : BitmapBase<uint8_t>(data), _cindex() { if ((data.Channels() != 4)&&(data.Channels() != 1)) { throw std::invalid_argument("指定された data のチャネル数はこのクラスではサポートされていません。"); } }
DIBBitmap::DIBBitmap(const BitmapBase<uint8_t>& data, const std::vector<RGBTriple_t>& pal) : BitmapBase<uint8_t>(data), _cindex(pal) { if (data.Channels() != 1) { throw std::invalid_argument("指定された data のチャネル数はこのクラスではサポートされていません。"); } }
DIBBitmap::DIBBitmap(const RectangleSize& size, const DataTypes& datatype) : BitmapBase<uint8_t>(size, (datatype==DataTypes::ARGB)?4:1), _cindex() {}
DIBBitmap::DIBBitmap(const RectangleSize& size, const int& palsize) : BitmapBase<uint8_t>(size, 1), _cindex(palsize) {}
DIBBitmap::DIBBitmap(const RectangleSize& size, const std::vector<RGBTriple_t>& pal) : BitmapBase<uint8_t>(size, 1), _cindex(pal) {}
DIBBitmap::DataTypes DIBBitmap::DataType() const
{
	if (Channels() == 4) { return DataTypes::ARGB; }
	else if (_cindex.size() == 0) { return DataTypes::GrayScale; }
	else { return DataTypes::IndexedColor; }
}
std::vector<RGBTriple_t>& DIBBitmap::ColorIndex() { return _cindex; }
const std::vector<RGBTriple_t>& DIBBitmap::ColorIndex() const { return _cindex; }
Property<DIBBitmap, ARGBColor> DIBBitmap::Index(const DisplayPoint& position) { return Property<DIBBitmap, ARGBColor>(*this, std::bind(getIndex, std::placeholders::_1, position), std::bind(setIndex, std::placeholders::_1, position, std::placeholders::_2)); }
Property<DIBBitmap, ARGBColor> DIBBitmap::Index(const int& x, const int& y) { return Index(DisplayPoint(x, y)); }
Property<DIBBitmap, ARGBColor> DIBBitmap::operator[](const DisplayPoint& index) { return Index(index); }
ReadOnlyProperty<DIBBitmap, ARGBColor> DIBBitmap::Index(const DisplayPoint& position) const { return ReadOnlyProperty<DIBBitmap, ARGBColor>(*this, std::bind(getIndex, std::placeholders::_1, position)); }
ReadOnlyProperty<DIBBitmap, ARGBColor> DIBBitmap::Index(const int& x, const int& y) const { return Index(DisplayPoint(x, y)); }
ReadOnlyProperty<DIBBitmap, ARGBColor> DIBBitmap::operator[](const DisplayPoint& index) const { return Index(index); }
DIBBitmap DIBBitmap::CreateRGBColor(const RectangleSize& size) { return DIBBitmap(size, DataTypes::ARGB); }
DIBBitmap DIBBitmap::CreateRGBColor(const int& width, const int& height) { return DIBBitmap(RectangleSize(width, height), DataTypes::ARGB); }
DIBBitmap DIBBitmap::CreateGlayScale(const RectangleSize& size) { return DIBBitmap(size, DataTypes::GrayScale); }
DIBBitmap DIBBitmap::CreateGlayScale(const int& width, const int& height) { return DIBBitmap(RectangleSize(width, height), DataTypes::GrayScale); }
DIBBitmap DIBBitmap::CreateIndexedColor(const RectangleSize& size, const int& palsize) { return DIBBitmap(size, palsize); }
DIBBitmap DIBBitmap::CreateIndexedColor(const int& width, const int& height, const int& palsize) { return DIBBitmap(RectangleSize(width, height), palsize); }
DIBBitmap DIBBitmap::CreateIndexedColor(const RectangleSize& size, const std::vector<RGBTriple_t>& pal) { return DIBBitmap(size, pal); }
DIBBitmap DIBBitmap::CreateIndexedColor(const int& width, const int& height, const std::vector<RGBTriple_t>& pal) { return DIBBitmap(RectangleSize(width, height), pal); }
ARGBColor DIBBitmap::getIndex(const DIBBitmap& inst, const DisplayPoint& position)
{
	auto px = inst.BitmapBase::Index(position);
	RGBTriple_t index;
	switch (inst.DataType())
	{
		case DataTypes::ARGB:
		{ return ARGBColor(float(px[0]) / 255, float(px[1]) / 255, float(px[2]) / 255, float(px[3]) / 255); }
		case DataTypes::GrayScale:
		{
			// TODO: 輝度->RGB導出のアルゴリズム改善
			return ARGBColor(float(px[0]) / 255, float(px[0]) / 255, float(px[0]) / 255, float(px[0]) / 255);
		}
		case DataTypes::IndexedColor:
		{
			index = inst._cindex[px[0]];
			return ARGBColor(float(index.Red) / 255, float(index.Green) / 255, float(index.Blue) / 255);
		}
		default:
		{ throw InvalidOperationException("このオブジェクトの DataType が無効です。"); }
	}
}
void DIBBitmap::setIndex(DIBBitmap& inst, const DisplayPoint& position, const ARGBColor& value)
{
	auto px = inst.BitmapBase::Index(position);
	switch (inst.DataType())
	{
		case DataTypes::ARGB:
		{
			px[0] = uint8_t(value.R() * 255);
			px[1] = uint8_t(value.G() * 255);
			px[2] = uint8_t(value.B() * 255);
			px[3] = uint8_t(value.Alpha() * 255);
			return;
		}
		case DataTypes::GrayScale:
		{
			// TODO: RGB->輝度導出のアルゴリズム改善
			float lm = (value.R() + value.G() + value.B()) / 3;
			px[0] = uint8_t(lm * 255);
			return;
		}
		case DataTypes::IndexedColor:
		{
			uint8_t index = 0;
			float mindist;
			for (auto i : Range(0UL, inst._cindex.size()))
			{
			// TODO: 色差導出のアルゴリズム改善
				float dr = value.R() - 255.f * inst._cindex[i].Red;
				float dg = value.G() - 255.f * inst._cindex[i].Green;
				float db = value.B() - 255.f * inst._cindex[i].Blue;
				float dist = std::sqrt((dr * dr) + (dg * dg) + (db * db));
				if (dist < mindist)
				{
					mindist = dist;
					index = i;
				}
			}
			px[0] = index;
			return;
		}
		default: { throw InvalidOperationException("このオブジェクトの DataType が無効です。"); }
	}
}
