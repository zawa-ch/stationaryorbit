//	stationaryorbit/graphics-dib/dibbitmap
//	Copyright 2020 zawa-ch.
//	GPLv3 (or later) license
//
//	This program is free software: you can redistribute it and/or modify
//	it under the terms of the GNU General Public License as published by
//	the Free Software Foundation, either version 3 of the License, or
//	any later version.
//
//	This program is distributed in the hope that it will be useful,
//	but WITHOUT ANY WARRANTY; without even the implied warranty of
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//	See the GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with this program.
//	If not, see <http://www.gnu.org/licenses/>.
//
#ifndef __stationaryorbit_graphics_dib_dibbitmap__
#define __stationaryorbit_graphics_dib_dibbitmap__
#include <fstream>
#include "dibpixeldata.hpp"
#include "dibheaders.hpp"
#include "invaliddibformat.hpp"
namespace zawa_ch::StationaryOrbit::Graphics::DIB
{
	class DIBFileLoader
	{
	protected:
		std::fstream stream;
		DIBFileHeader fhead;
		int32_t headersize;
	public:
		DIBFileLoader(std::fstream&& stream) : stream(stream)
		{
			if (stream.bad()) { throw InvalidOperationException("ストリームの状態が無効です。"); }
			stream.read((char*)&fhead, sizeof(DIBFileHeader));
			if (stream.fail())
			{
				if (stream.eof()) { stream.clear(); throw InvalidDIBFormatException("ファイルヘッダの読み取り中にストリーム終端に到達しました。"); }
				stream.clear();
				throw std::fstream::failure("ストリームの読み取りに失敗しました。");
			}
			if (!fhead.CheckFileHeader()) { throw InvalidDIBFormatException("ファイルヘッダのマジックナンバーを認識できませんでした。"); }
			stream.read((char*)&headersize, sizeof(int32_t));
			if (stream.fail())
			{
				if (stream.eof()) { stream.clear(); throw InvalidDIBFormatException("ヘッダサイズの読み取り中にストリーム終端に到達しました。"); }
				stream.clear();
				throw std::fstream::failure("ストリームの読み取りに失敗しました。");
			}
		}
		DIBFileLoader(const char* filename) : DIBFileLoader(std::move(std::fstream(filename, std::ios_base::binary))) {}
		DIBFileLoader(const DIBFileLoader&) = delete;
		DIBFileLoader(DIBFileLoader&&) = default;
		virtual ~DIBFileLoader() = default;

		[[nodiscard]] const std::fstream& Stream() const { return stream; }
		[[nodiscard]] const DIBFileHeader& FileHead() const { return fhead; }
		[[nodiscard]] const int32_t& HeaderSize() const { return headersize; }
	};
	class DIBBitmap
		: public BitmapBase<uint8_t>
	{
	public: // types
		enum class DataTypes { ARGB, IndexedColor };
	private: // contains
		std::unique_ptr<RGBColorSpace> _space;
		std::vector<RGBTriple_t> _cindex;
		int _resh;
		int _resv;
	public: // construct
		DIBBitmap();
		explicit DIBBitmap(const RGBBitmapImage& data);
		explicit DIBBitmap(const ARGBBitmapImage& data);
	private: // construct
		DIBBitmap(const BitmapBase<uint8_t>& data, const RGBColorSpace& colorspace);
		DIBBitmap(const BitmapBase<uint8_t>& data, const std::vector<RGBTriple_t>& pallet, const RGBColorSpace& colorspace);
		DIBBitmap(const RectangleSize& size, const DataTypes& datatype);
		DIBBitmap(const RectangleSize& size, const int& palsize);
		DIBBitmap(const RectangleSize& size, const std::vector<RGBTriple_t>& pal);
	public: // member
		DataTypes DataType() const;
		RGBColorSpace& ColorSpace();
		const RGBColorSpace& ColorSpace() const;
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
		explicit operator ARGBBitmapImage() const;
	public: // static
		static DIBBitmap CreateRGBColor(const RectangleSize& size);
		static DIBBitmap CreateRGBColor(const int& width, const int& height);
		static DIBBitmap CreateIndexedColor(const RectangleSize& size, const int& palsize);
		static DIBBitmap CreateIndexedColor(const int& width, const int& height, const int& palsize);
		static DIBBitmap CreateIndexedColor(const RectangleSize& size, const std::vector<RGBTriple_t>& pal);
		static DIBBitmap CreateIndexedColor(const int& width, const int& height, const std::vector<RGBTriple_t>& pal);
		static DIBBitmap FromStream(std::istream& stream);
		static DIBBitmap ReinterpretFrom(const BitmapBase<uint8_t>& data);
		static DIBBitmap ReinterpretFrom(const BitmapBase<uint8_t>& data, const RGBColorSpace& colorspace);
		static DIBBitmap ReinterpretFrom(const BitmapBase<uint8_t>& data, const std::vector<RGBTriple_t>& pallet);
		static DIBBitmap ReinterpretFrom(const BitmapBase<uint8_t>& data, const std::vector<RGBTriple_t>& pallet, const RGBColorSpace& colorspace);
		static DIBBitmap ReinterpretFrom(BitmapBase<uint8_t>&& data);
		static DIBBitmap ReinterpretFrom(BitmapBase<uint8_t>&& data, const RGBColorSpace& colorspace);
		static DIBBitmap ReinterpretFrom(BitmapBase<uint8_t>&& data, const std::vector<RGBTriple_t>& pallet);
		static DIBBitmap ReinterpretFrom(BitmapBase<uint8_t>&& data, const std::vector<RGBTriple_t>& pallet, const RGBColorSpace& colorspace);
	private: // internal
		static ARGBColor getIndex(const DIBBitmap& inst, const DisplayPoint& position);
		static void setIndex(DIBBitmap& inst, const DisplayPoint& position, const ARGBColor& value);
		static DIBBitmap readRGB(std::istream& stream, const int& width, const int& height, const BitDepth& bitdepth);
		void writeRGB(std::ostream& stream, const BitDepth& depth) const;
	};
}
#endif // __stationaryorbit_graphics_dib_dibbitmap__
