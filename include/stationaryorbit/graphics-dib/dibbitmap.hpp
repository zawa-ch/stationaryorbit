#ifndef __stationaryorbit_graphics_dib_dibbitmap__
#define __stationaryorbit_graphics_dib_dibbitmap__
#include <iostream>
#include "stationaryorbit/graphics-core/bitmap"
#include "dibheaders.hpp"
#include "rgbtriple.hpp"
#include "invaliddibformat.hpp"
namespace zawa_ch::StationaryOrbit::Graphics::DIB
{
	class DIBBitmap
		: public BitmapBase<uint8_t>
	{
	public: // types
		enum class DataTypes { GrayScale, ARGB, IndexedColor };
	private: // contains
		std::vector<RGBTriple_t> _cindex;
		int _resh;
		int _resv;
	public: // construct
		DIBBitmap();
		DIBBitmap(const BitmapBase<uint8_t>& data);
		DIBBitmap(const BitmapBase<uint8_t>& data, const std::vector<RGBTriple_t>& pal);
	private: // construct
		DIBBitmap(const RectangleSize& size, const DataTypes& datatype);
		DIBBitmap(const RectangleSize& size, const int& palsize);
		DIBBitmap(const RectangleSize& size, const std::vector<RGBTriple_t>& pal);
	public: // member
		DataTypes DataType() const;
		std::vector<RGBTriple_t>& ColorIndex();
		const std::vector<RGBTriple_t>& ColorIndex() const;
		int& HorizonalResolution();
		const int& HorizonalResolution() const;
		int& VerticalResolution();
		const int& VerticalResolution() const;
		Property<DIBBitmap, ARGBColor> Index(const DisplayPoint& position);
		Property<DIBBitmap, ARGBColor> Index(const int& x, const int& y);
		Property<DIBBitmap, ARGBColor> operator[](const DisplayPoint& index);
		ReadOnlyProperty<DIBBitmap, ARGBColor> Index(const DisplayPoint& position) const;
		ReadOnlyProperty<DIBBitmap, ARGBColor> Index(const int& x, const int& y) const;
		ReadOnlyProperty<DIBBitmap, ARGBColor> operator[](const DisplayPoint& index) const;
		void WriteTo(std::ostream& stream, const BitDepth& depth = BitDepth::Null) const;
	public: // static
		static DIBBitmap CreateRGBColor(const RectangleSize& size);
		static DIBBitmap CreateRGBColor(const int& width, const int& height);
		static DIBBitmap CreateGlayScale(const RectangleSize& size);
		static DIBBitmap CreateGlayScale(const int& width, const int& height);
		static DIBBitmap CreateIndexedColor(const RectangleSize& size, const int& palsize);
		static DIBBitmap CreateIndexedColor(const int& width, const int& height, const int& palsize);
		static DIBBitmap CreateIndexedColor(const RectangleSize& size, const std::vector<RGBTriple_t>& pal);
		static DIBBitmap CreateIndexedColor(const int& width, const int& height, const std::vector<RGBTriple_t>& pal);
		static DIBBitmap FromStream(std::istream& stream);
	private: // internal
		static ARGBColor getIndex(const DIBBitmap& inst, const DisplayPoint& position);
		static void setIndex(DIBBitmap& inst, const DisplayPoint& position, const ARGBColor& value);
		static DIBBitmap readRGB(std::istream& stream, const int& width, const int& height, const BitDepth& bitdepth);
		void writeRGB(std::ostream& stream, const BitDepth& depth) const;
	};
}
#endif // __stationaryorbit_graphics_dib_dibbitmap__
