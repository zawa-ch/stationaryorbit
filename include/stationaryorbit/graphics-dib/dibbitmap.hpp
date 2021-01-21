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
#include <vector>
#include <variant>
#include <fstream>
#include "stationaryorbit/graphics-core.image.hpp"
#include "dibpixeldata.hpp"
#include "dibheaders.hpp"
#include "invaliddibformat.hpp"
namespace zawa_ch::StationaryOrbit::Graphics::DIB
{
	///	Windows bitmap 画像ファイルを読み込むための基本ロジックを提供します。
	class DIBFileLoader
	{
	protected:
		std::fstream stream;
		DIBFileHeader fhead;
		int32_t headersize;
	public:
		///	@a DIBFileLoader をデフォルト構築します。
		DIBFileLoader() = default;
		///	ストリームを使用して @a DIBFileLoader を初期化します。
		///	@param	stream
		///	読み込みに使用する @a std::fstream 。
		///	ストリームはこのオブジェクトで「消費」されるため、右辺値参照である必要があります。
		DIBFileLoader(std::fstream&& stream) : stream(stream)
		{
			if (stream.fail()) { throw InvalidOperationException("ストリームの状態が無効です。"); }
			auto sentry = std::fstream::sentry(stream, true);
			if (!sentry) { throw std::fstream::failure("ストリームの準備に失敗しました。"); }
			if (stream.seekg(0).fail()) { stream.clear(); throw std::fstream::failure("ストリームのシークに失敗しました。"); }
			if (stream.read((char*)&fhead, sizeof(DIBFileHeader)).fail())
			{
				if (stream.eof()) { stream.clear(); throw InvalidDIBFormatException("ファイルヘッダの読み取り中にストリーム終端に到達しました。"); }
				stream.clear();
				throw std::fstream::failure("ストリームの読み取りに失敗しました。");
			}
			if (!fhead.CheckFileHeader()) { throw InvalidDIBFormatException("ファイルヘッダのマジックナンバーを認識できませんでした。"); }
			if (stream.read((char*)&headersize, sizeof(int32_t)).fail())
			{
				if (stream.eof()) { stream.clear(); throw InvalidDIBFormatException("ヘッダサイズの読み取り中にストリーム終端に到達しました。"); }
				stream.clear();
				throw std::fstream::failure("ストリームの読み取りに失敗しました。");
			}
		}
		///	指定したファイル名の @a std::fstream を構築し、 @a DIBFileLoader を初期化します。
		///	@param	filename
		///	開くファイルの名前。 @a std::fstream::fstream(const @a char*, @a std::ios_base::openmode) の呼び出しに使用されます。
		///	@param	mode
		///	ファイルを開くモード。 @a std::fstream::fstream(const @a char*, @a std::ios_base::openmode) の呼び出しに使用されます。
		DIBFileLoader(const char* filename, std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out | std::ios_base::binary) : DIBFileLoader(std::move(std::fstream(filename, mode))) {}
		///	指定したファイル名の @a std::fstream を構築し、 @a DIBFileLoader を初期化します。
		///	@param	filename
		///	開くファイルの名前。 @a std::fstream::fstream(const @a std::string&, @a std::ios_base::openmode) の呼び出しに使用されます。
		///	@param	mode
		///	ファイルを開くモード。 @a std::fstream::fstream(const @a char*, @a std::ios_base::openmode) の呼び出しに使用されます。
		DIBFileLoader(const std::string& filename, std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out | std::ios_base::binary) : DIBFileLoader(std::move(std::fstream(filename, mode))) {}
		DIBFileLoader(const DIBFileLoader&) = delete;
		DIBFileLoader(DIBFileLoader&&) = default;
		virtual ~DIBFileLoader() = default;

		[[nodiscard]] const std::fstream& Stream() const { return stream; }
		[[nodiscard]] const DIBFileHeader& FileHead() const { return fhead; }
		[[nodiscard]] const int32_t& HeaderSize() const { return headersize; }

		///	現在のストリームの位置からデータを取得します。
		///	@param	T
		///	読み込むデータの型。
		///	@param	dest
		///	読み込んだデータの格納先。
		///	@a sizeof(T)*length の長さの領域が確保されている必要があります。
		///	@param	length
		///	読み込むデータの個数。
		template<class T>
		const std::istream& Read(T* dest, const size_t& length = 1U)
		{
			if (stream.fail()) { throw InvalidOperationException("ストリームの状態が無効です。"); }
			auto sentry = std::fstream::sentry(stream, true);
			if (!sentry) { throw std::fstream::failure("ストリームの準備に失敗しました。"); }
			if (stream.read((char*)dest, sizeof(T) * length).fail())
			{
				if (result.eof()) { result.clear(); throw InvalidDIBFormatException("データの読み取り中にストリーム終端に到達しました。"); }
				result.clear();
				throw std::fstream::failure("ストリームの読み取りに失敗しました。");
			}
			return stream;
		}
		///	ストリームの指定された位置からデータを取得します。
		///	@param	T
		///	読み込むデータの型。
		///	@param	dest
		///	読み込んだデータの格納先。
		///	@a sizeof(T)*length の長さの領域が確保されている必要があります。
		///	@param	length
		///	読み込むデータの個数。
		template<class T>
		const std::istream& ReadFrom(T* dest, const size_t& index, const size_t& length = 1U)
		{
			if (stream.fail()) { throw InvalidOperationException("ストリームの状態が無効です。"); }
			auto sentry = std::fstream::sentry(stream, true);
			if (!sentry) { throw std::fstream::failure("ストリームの準備に失敗しました。"); }
			if (stream.seekg(index).fail()) { result.clear(); throw std::fstream::failure("ストリームのシークに失敗しました。"); }
			if (stream.read((char*)dest, sizeof(T) * length).fail())
			{
				if (result.eof()) { result.clear(); throw InvalidDIBFormatException("データの読み取り中にストリーム終端に到達しました。"); }
				result.clear();
				throw std::fstream::failure("ストリームの読み取りに失敗しました。");
			}
			return stream;
		}
	};
	class DIBCoreBitmapFileLoader
	{
	public:
		typedef std::variant<DIBPixelData<DIBBitDepth::Bit1>, DIBPixelData<DIBBitDepth::Bit4>, DIBPixelData<DIBBitDepth::Bit8>, DIBPixelData<DIBBitDepth::Bit24>> ValueType;
		typedef std::variant<DIBPixelData<std::vector<DIBBitDepth::Bit1>>, DIBPixelData<std::vector<DIBBitDepth::Bit4>>, DIBPixelData<std::vector<DIBBitDepth::Bit8>>, DIBPixelData<std::vector<DIBBitDepth::Bit24>>> ValueVectorType;
	private:
		DIBFileLoader loader;
		DIBCoreHeader ihead;
	public:
		DIBCoreBitmapFileLoader(DIBFileLoader&& loader) : loader(loader)
		{
			if (loader.HeaderSize() < DIBCoreHeader::Size) { throw InvalidDIBFormatException("情報ヘッダの長さはCoreHeaderでサポートされる最小の長さよりも短いです。"); }
			if (!loader.Stream().good()) { throw InvalidOperationException("ストリームの状態が無効です。"); }
			loader.SeekStream(sizeof(DIBFileHeader) + sizeof(int32_t));
			loader.ReadStream(&ihead);
		}

		[[nodiscard]] const DIBCoreHeader& InfoHead() const { return ihead; }

		[[nodiscard]] ValueType Get(const DisplayPoint& index)
		{
			if (!loader.Stream().good()) { throw InvalidOperationException("ストリームの状態が無効です。"); }
			loader.SeekStream(sizeof(DIBFileHeader) + loader.FileHead().Offset() + ResolvePos(index));
			switch(ihead.BitCount)
			{
				case DIBBitDepth::Bit1:
				{
					auto result = DIBPixelData<DIBBitDepth::Bit1>();
					loader.ReadStream(&result);
					return ValueType(result);
				}
				case DIBBitDepth::Bit4:
				{
					auto result = DIBPixelData<DIBBitDepth::Bit4>();
					loader.ReadStream(&result);
					return ValueType(result);
				}
				case DIBBitDepth::Bit8:
				{
					auto result = DIBPixelData<DIBBitDepth::Bit8>();
					loader.ReadStream(&result);
					return ValueType(result);
				}
				case DIBBitDepth::Bit24:
				{
					auto result = DIBPixelData<DIBBitDepth::Bit24>();
					loader.ReadStream(&result);
					return ValueType(result);
				}
				default: { throw InvalidDIBFormatException("情報ヘッダのBitCountの内容が無効です。"); }
			}
		}
		[[nodiscard]] ValueVectorType Get(const DisplayPoint& index, const size_t& length)
		{
			if (!loader.Stream().good()) { throw InvalidOperationException("ストリームの状態が無効です。"); }
			if (ihead.ImageWidth <= (index.X() + length)) { throw std::out_of_range("画像の幅を超える領域を指定することはできません。"); }
			loader.SeekStream(sizeof(DIBFileHeader) + loader.FileHead().Offset() + ResolvePos(index));
			switch(ihead.BitCount)
			{
				case DIBBitDepth::Bit1:
				{
					auto result = std::vector<DIBPixelData<DIBBitDepth::Bit1>>();
					result.reserve(length);
					loader.ReadStream(result.data(), length);
					return ValueVectorType(result);
				}
				case DIBBitDepth::Bit4:
				{
					auto result = std::vector<DIBPixelData<DIBBitDepth::Bit4>>();
					result.reserve(length);
					loader.ReadStream(result.data(), length);
					return ValueVectorType(result);
				}
				case DIBBitDepth::Bit8:
				{
					auto result = std::vector<DIBPixelData<DIBBitDepth::Bit8>>();
					result.reserve(length);
					loader.ReadStream(result.data(), length);
					return ValueVectorType(result);
				}
				case DIBBitDepth::Bit24:
				{
					auto result = std::vector<DIBPixelData<DIBBitDepth::Bit24>>();
					result.reserve(length);
					loader.ReadStream(result.data(), length);
					return ValueVectorType(result);
				}
				default: { throw InvalidDIBFormatException("情報ヘッダのBitCountの内容が無効です。"); }
			}
		}

	private:
		[[nodiscard]] size_t ResolvePos(const DisplayPoint& pos)
		{
			if ( (pos.X() < 0)||(pos.Y() < 0) ) { throw InvalidOperationException("posに指定されている座標が無効です。"); }
			if ( (ihead.ImageWidth <= pos.X())||(ihead.ImageHeight <= pos.Y()) ) { throw std::out_of_range("指定された座標はこの画像領域を超えています。"); }
			size_t pxl = ((ihead.BitCount)/sizeof(uint8_t)) + (((ihead.BitCount)%sizeof(uint8_t)) != 0)?1:0;
			size_t w = pxl * ihead.ImageWidth + ((((pxl * ihead.ImageWidth) % 4) != 0)?(4-((pxl * ihead.ImageWidth)%4)):0);
			return (w * pos.Y()) + (pxl * pos.X());
		}
	};
	class DIBInfoBitmapFileLoader
	{
	public:
		typedef std::variant<DIBPixelData<DIBBitDepth::Bit1>, DIBPixelData<DIBBitDepth::Bit4>, DIBPixelData<DIBBitDepth::Bit8>, DIBPixelData<DIBBitDepth::Bit16>, DIBPixelData<DIBBitDepth::Bit24>, DIBPixelData<DIBBitDepth::Bit32>> ValueType;
	private:
		DIBFileLoader loader;
		DIBInfoHeader ihead;
	public:
		DIBInfoBitmapFileLoader(DIBFileLoader&& loader) : loader(loader)
		{
			if (!stream.good()) { throw InvalidOperationException("ストリームの状態が無効です。"); }
			stream.seekg(sizeof(DIBFileHeader) + sizeof(int32_t));
			if (stream.fail()) { throw std::fstream::failure("ストリームのシークに失敗しました。"); }
			stream.read((char*)&ihead, sizeof(DIBInfoHeader));
			if (stream.fail())
			{
				if (stream.eof()) { stream.clear(); throw InvalidDIBFormatException("ヘッダの読み取り中にストリーム終端に到達しました。"); }
				stream.clear();
				throw std::fstream::failure("ストリームの読み取りに失敗しました。");
			}
		}

		[[nodiscard]] const DIBInfoHeader& InfoHead() const { return ihead; }

		[[nodiscard]] ValueType Get(const DisplayPoint& index)
		{
			if (!loader.stream.good()) { throw InvalidOperationException("ストリームの状態が無効です。"); }
			loader.stream.seekg(sizeof(DIBFileHeader) + loader.FileHead().Offset() + ResolvePos(index));
			if (loader.stream.fail()) { loader.stream.clear(); throw std::fstream::failure("ストリームのシークに失敗しました。"); }
			switch(ihead.BitCount)
			{
				case DIBBitDepth::Bit1:
				{
					DIBPixelData<DIBBitDepth::Bit1> result;
					loader.Stream().read((char*)&result, sizeof(result));
					if (loader.stream.fail()) { loader.stream.clear(); throw std::fstream::failure("データの読み取りに失敗しました。"); }
					return ValueType(result);
				}
				case DIBBitDepth::Bit4:
				{
					DIBPixelData<DIBBitDepth::Bit4> result;
					loader.Stream().read((char*)&result, sizeof(result));
					if (loader.stream.fail()) { loader.stream.clear(); throw std::fstream::failure("データの読み取りに失敗しました。"); }
					return ValueType(result);
				}
				case DIBBitDepth::Bit8:
				{
					DIBPixelData<DIBBitDepth::Bit8> result;
					loader.Stream().read((char*)&result, sizeof(result));
					if (loader.stream.fail()) { loader.stream.clear(); throw std::fstream::failure("データの読み取りに失敗しました。"); }
					return ValueType(result);
				}
				case DIBBitDepth::Bit16:
				{
					DIBPixelData<DIBBitDepth::Bit16> result;
					loader.Stream().read((char*)&result, sizeof(result));
					if (loader.stream.fail()) { loader.stream.clear(); throw std::fstream::failure("データの読み取りに失敗しました。"); }
					return ValueType(result);
				}
				case DIBBitDepth::Bit24:
				{
					DIBPixelData<DIBBitDepth::Bit24> result;
					loader.Stream().read((char*)&result, sizeof(result));
					if (loader.stream.fail()) { loader.stream.clear(); throw std::fstream::failure("データの読み取りに失敗しました。"); }
					return ValueType(result);
				}
				case DIBBitDepth::Bit32:
				{
					DIBPixelData<DIBBitDepth::Bit32> result;
					loader.Stream().read((char*)&result, sizeof(result));
					if (loader.stream.fail()) { loader.stream.clear(); throw std::fstream::failure("データの読み取りに失敗しました。"); }
					return ValueType(result);
				}
				default: { throw InvalidDIBFormatException("BitCountの内容が無効です。"); }
			}
		}
	};
	class DIBV4BitmapFileLoader
	{
	public:
		typedef std::variant<DIBPixelData<DIBBitDepth::Bit1>, DIBPixelData<DIBBitDepth::Bit4>, DIBPixelData<DIBBitDepth::Bit8>, DIBPixelData<DIBBitDepth::Bit16>, DIBPixelData<DIBBitDepth::Bit24>, DIBPixelData<DIBBitDepth::Bit32>> ValueType;
	private:
		DIBFileLoader loader;
		DIBV4Header ihead;
	public:
		DIBV4BitmapFileLoader(DIBFileLoader&& loader) : loader(loader)
		{
			if (!stream.good()) { throw InvalidOperationException("ストリームの状態が無効です。"); }
			stream.seekg(sizeof(DIBFileHeader) + sizeof(int32_t));
			if (stream.fail()) { throw std::fstream::failure("ストリームのシークに失敗しました。"); }
			stream.read((char*)&ihead, sizeof(DIBV4Header));
			if (stream.fail())
			{
				if (stream.eof()) { stream.clear(); throw InvalidDIBFormatException("ヘッダの読み取り中にストリーム終端に到達しました。"); }
				stream.clear();
				throw std::fstream::failure("ストリームの読み取りに失敗しました。");
			}
		}

		[[nodiscard]] const DIBV4Header& InfoHead() const { return ihead; }

		[[nodiscard]] ValueType Get(const DisplayPoint& index)
		{
			if (!loader.stream.good()) { throw InvalidOperationException("ストリームの状態が無効です。"); }
			loader.stream.seekg(sizeof(DIBFileHeader) + loader.FileHead().Offset() + ResolvePos(index));
			if (loader.stream.fail()) { loader.stream.clear(); throw std::fstream::failure("ストリームのシークに失敗しました。"); }
			switch(ihead.BitCount)
			{
				case DIBBitDepth::Bit1:
				{
					DIBPixelData<DIBBitDepth::Bit1> result;
					loader.Stream().read((char*)&result, sizeof(result));
					if (loader.stream.fail()) { loader.stream.clear(); throw std::fstream::failure("データの読み取りに失敗しました。"); }
					return ValueType(result);
				}
				case DIBBitDepth::Bit4:
				{
					DIBPixelData<DIBBitDepth::Bit4> result;
					loader.Stream().read((char*)&result, sizeof(result));
					if (loader.stream.fail()) { loader.stream.clear(); throw std::fstream::failure("データの読み取りに失敗しました。"); }
					return ValueType(result);
				}
				case DIBBitDepth::Bit8:
				{
					DIBPixelData<DIBBitDepth::Bit8> result;
					loader.Stream().read((char*)&result, sizeof(result));
					if (loader.stream.fail()) { loader.stream.clear(); throw std::fstream::failure("データの読み取りに失敗しました。"); }
					return ValueType(result);
				}
				case DIBBitDepth::Bit16:
				{
					DIBPixelData<DIBBitDepth::Bit16> result;
					loader.Stream().read((char*)&result, sizeof(result));
					if (loader.stream.fail()) { loader.stream.clear(); throw std::fstream::failure("データの読み取りに失敗しました。"); }
					return ValueType(result);
				}
				case DIBBitDepth::Bit24:
				{
					DIBPixelData<DIBBitDepth::Bit24> result;
					loader.Stream().read((char*)&result, sizeof(result));
					if (loader.stream.fail()) { loader.stream.clear(); throw std::fstream::failure("データの読み取りに失敗しました。"); }
					return ValueType(result);
				}
				case DIBBitDepth::Bit32:
				{
					DIBPixelData<DIBBitDepth::Bit32> result;
					loader.Stream().read((char*)&result, sizeof(result));
					if (loader.stream.fail()) { loader.stream.clear(); throw std::fstream::failure("データの読み取りに失敗しました。"); }
					return ValueType(result);
				}
				default: { throw InvalidDIBFormatException("BitCountの内容が無効です。"); }
			}
		}
	};
	class DIBV5BitmapFileLoader
	{
	public:
		typedef std::variant<DIBPixelData<DIBBitDepth::Bit1>, DIBPixelData<DIBBitDepth::Bit4>, DIBPixelData<DIBBitDepth::Bit8>, DIBPixelData<DIBBitDepth::Bit16>, DIBPixelData<DIBBitDepth::Bit24>, DIBPixelData<DIBBitDepth::Bit32>> ValueType;
	private:
		DIBFileLoader loader;
		DIBV5Header ihead;
	public:
		DIBV5BitmapFileLoader(DIBFileLoader&& loader) : loader(loader)
		{
			if (!stream.good()) { throw InvalidOperationException("ストリームの状態が無効です。"); }
			stream.seekg(sizeof(DIBFileHeader) + sizeof(int32_t));
			if (stream.fail()) { throw std::fstream::failure("ストリームのシークに失敗しました。"); }
			stream.read((char*)&ihead, sizeof(DIBV5Header));
			if (stream.fail())
			{
				if (stream.eof()) { stream.clear(); throw InvalidDIBFormatException("ヘッダの読み取り中にストリーム終端に到達しました。"); }
				stream.clear();
				throw std::fstream::failure("ストリームの読み取りに失敗しました。");
			}
		}

		[[nodiscard]] const DIBV5Header& InfoHead() const { return ihead; }

		[[nodiscard]] ValueType Get(const DisplayPoint& index)
		{
			if (!loader.stream.good()) { throw InvalidOperationException("ストリームの状態が無効です。"); }
			loader.stream.seekg(sizeof(DIBFileHeader) + loader.FileHead().Offset() + ResolvePos(index));
			if (loader.stream.fail()) { loader.stream.clear(); throw std::fstream::failure("ストリームのシークに失敗しました。"); }
			switch(ihead.BitCount)
			{
				case DIBBitDepth::Bit1:
				{
					DIBPixelData<DIBBitDepth::Bit1> result;
					loader.Stream().read((char*)&result, sizeof(result));
					if (loader.stream.fail()) { loader.stream.clear(); throw std::fstream::failure("データの読み取りに失敗しました。"); }
					return ValueType(result);
				}
				case DIBBitDepth::Bit4:
				{
					DIBPixelData<DIBBitDepth::Bit4> result;
					loader.Stream().read((char*)&result, sizeof(result));
					if (loader.stream.fail()) { loader.stream.clear(); throw std::fstream::failure("データの読み取りに失敗しました。"); }
					return ValueType(result);
				}
				case DIBBitDepth::Bit8:
				{
					DIBPixelData<DIBBitDepth::Bit8> result;
					loader.Stream().read((char*)&result, sizeof(result));
					if (loader.stream.fail()) { loader.stream.clear(); throw std::fstream::failure("データの読み取りに失敗しました。"); }
					return ValueType(result);
				}
				case DIBBitDepth::Bit16:
				{
					DIBPixelData<DIBBitDepth::Bit16> result;
					loader.Stream().read((char*)&result, sizeof(result));
					if (loader.stream.fail()) { loader.stream.clear(); throw std::fstream::failure("データの読み取りに失敗しました。"); }
					return ValueType(result);
				}
				case DIBBitDepth::Bit24:
				{
					DIBPixelData<DIBBitDepth::Bit24> result;
					loader.Stream().read((char*)&result, sizeof(result));
					if (loader.stream.fail()) { loader.stream.clear(); throw std::fstream::failure("データの読み取りに失敗しました。"); }
					return ValueType(result);
				}
				case DIBBitDepth::Bit32:
				{
					DIBPixelData<DIBBitDepth::Bit32> result;
					loader.Stream().read((char*)&result, sizeof(result));
					if (loader.stream.fail()) { loader.stream.clear(); throw std::fstream::failure("データの読み取りに失敗しました。"); }
					return ValueType(result);
				}
				default: { throw InvalidDIBFormatException("BitCountの内容が無効です。"); }
			}
		}
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
