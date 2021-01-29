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
#ifndef __stationaryorbit_graphics_dib_dibloader__
#define __stationaryorbit_graphics_dib_dibloader__
#include <vector>
#include <variant>
#include <fstream>
#include "stationaryorbit/graphics-core.image.hpp"
#include "dibpixeldata.hpp"
#include "dibheaders.hpp"
#include "invaliddibformat.hpp"
namespace zawa_ch::StationaryOrbit::Graphics::DIB
{
	///	ストリームから Windows bitmap 画像を読み込むための基本ロジックを実装します。
	class DIBLoader
	{
	public:
		DIBLoader() = default;
		virtual ~DIBLoader() = default;

		///	このオブジェクトが Windos bitmap 画像としての読み込みが可能な状態であるかを取得します。
		[[nodiscard]] virtual bool IsEnable() const = 0;
		///	このオブジェクトに関連付けられているストリームを取得します。
		[[nodiscard]] virtual std::iostream& Stream() = 0;
		///	このオブジェクトの読み込まれたファイルヘッダを取得します。
		[[nodiscard]] virtual const DIBFileHeader& FileHead() const = 0;
		///	このオブジェクトの読み込まれた情報ヘッダのサイズを取得します。
		[[nodiscard]] virtual const int32_t& HeaderSize() const = 0;

		///	ストリームからヘッダの再読込を行います。
		virtual void Reload() = 0;
		///	データの読み込みを行います。
		///	@param	dest
		///	読み込んだデータの格納先。
		///	@a size の長さの領域が確保されている必要があります。
		///	@param	pos
		///	読み込むデータの位置。
		///	@param	size
		///	読み込むデータの個数。
		virtual void Read(char* dest, size_t pos, size_t length = 1U) = 0;
		///	データの書き込みを行います。
		///	@param	source
		///	書き込むデータの格納先。
		///	@a size の長さの領域が確保されている必要があります。
		///	@param	pos
		///	書き込むデータの位置。
		///	@param	size
		///	書き込むデータの個数。
		virtual void Write(const char* source, size_t pos, size_t length = 1U) = 0;
	};
	///	Windows bitmap 画像ファイルを読み込むための基本ロジックを提供します。
	class DIBFileLoader : public DIBLoader
	{
	private:
		std::fstream stream;
		DIBFileHeader fhead;
		int32_t headersize;
	public:
		///	@a DIBFileLoader をデフォルト構築します。
		DIBFileLoader();
		///	ストリームを使用して @a DIBFileLoader を初期化します。
		///	@param	stream
		///	読み込みに使用する @a std::fstream 。
		///	ストリームはこのオブジェクトで「消費」されるため、右辺値参照である必要があります。
		DIBFileLoader(std::fstream&& stream);
		///	指定したファイル名の @a std::fstream を構築し、 @a DIBFileLoader を初期化します。
		///	@param	filename
		///	開くファイルの名前。 @a std::fstream::fstream(const @a char*, @a std::ios_base::openmode) の呼び出しに使用されます。
		///	@param	mode
		///	ファイルを開くモード。 @a std::fstream::fstream(const @a char*, @a std::ios_base::openmode) の呼び出しに使用されます。
		DIBFileLoader(const char* filename, std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out | std::ios_base::binary);
		///	指定したファイル名の @a std::fstream を構築し、 @a DIBFileLoader を初期化します。
		///	@param	filename
		///	開くファイルの名前。 @a std::fstream::fstream(const @a std::string&, @a std::ios_base::openmode) の呼び出しに使用されます。
		///	@param	mode
		///	ファイルを開くモード。 @a std::fstream::fstream(const @a char*, @a std::ios_base::openmode) の呼び出しに使用されます。
		DIBFileLoader(const std::string& filename, std::ios_base::openmode mode = std::ios_base::in | std::ios_base::out | std::ios_base::binary);
		DIBFileLoader(const DIBFileLoader&) = delete;
		DIBFileLoader(DIBFileLoader&&) = default;
		virtual ~DIBFileLoader() = default;

		///	このオブジェクトが Windos bitmap 画像としての読み込みが可能な状態であるかを取得します。
		[[nodiscard]] bool IsEnable() const;
		///	このオブジェクトに関連付けられているストリームを取得します。
		[[nodiscard]] std::iostream& Stream() { return stream; }
		///	このオブジェクトの読み込まれたファイルヘッダを取得します。
		[[nodiscard]] const DIBFileHeader& FileHead() const { return fhead; }
		///	このオブジェクトの読み込まれた情報ヘッダのサイズを取得します。
		[[nodiscard]] const int32_t& HeaderSize() const { return headersize; }

		///	ストリームからヘッダの再読込を行います。
		void Reload();
		///	データの読み込みを行います。
		///	@param	dest
		///	読み込んだデータの格納先。
		///	@a size の長さの領域が確保されている必要があります。
		///	@param	pos
		///	読み込むデータの位置。
		///	@param	size
		///	読み込むデータの個数。
		void Read(char* dest, size_t pos, size_t length = 1U);
		///	データの書き込みを行います。
		///	@param	source
		///	書き込むデータの格納先。
		///	@a size の長さの領域が確保されている必要があります。
		///	@param	pos
		///	書き込むデータの位置。
		///	@param	size
		///	書き込むデータの個数。
		void Write(const char* source, size_t pos, size_t length = 1U);
	};
	///	@a DIBLoader を使用したデータ入出力の拡張を行うヘルパークラスです。
	class DIBLoaderHelper final
	{
		DIBLoaderHelper() = delete;
		DIBLoaderHelper(const DIBLoaderHelper&) = delete;
		DIBLoaderHelper(DIBLoaderHelper&&) = delete;
		~DIBLoaderHelper() = delete;
	public:
		///	@a DIBLoader から指定された型のデータを取得します。
		///	@param	T
		///	読み込むデータの型。
		///	@param	dest
		///	読み込んだデータの格納先。
		///	@a sizeof(T)*size の長さの領域が確保されている必要があります。
		///	@param	pos
		///	読み込むデータの位置。
		///	@param	size
		///	読み込むデータの個数。
		template<class T>
		static void Read(DIBLoader& loader, T* dest, const size_t& pos, const size_t& size = 1U) { loader.Read((char*)dest, pos, sizeof(T) * size); }
		///	@a DIBLoader に指定された型のデータを書き込みます。
		///	@param	T
		///	書き込むデータの型。
		///	@param	source
		///	書き込むデータの格納先。
		///	@a sizeof(T)*size の長さの領域が確保されている必要があります。
		///	@param	pos
		///	書き込むデータの位置。
		///	@param	size
		///	書き込むデータの個数。
		template<class T>
		static void Write(DIBLoader& loader, const T* source, const size_t& pos, const size_t& size = 1U) { loader.Write((const char*)source, pos, sizeof(T) * size); }
	};
	///	@a DIBLoader を使用してInfoHeaderを持つWindows bitmap 画像を読み込みます。
	class DIBInfoBitmapFileLoader
	{
	public:
		///	この画像の1ピクセルのデータを表す @a std::variant 。
		typedef std::variant<DIBPixelData<DIBBitDepth::Bit1>, DIBPixelData<DIBBitDepth::Bit4>, DIBPixelData<DIBBitDepth::Bit8>, DIBPixelData<DIBBitDepth::Bit16>, DIBPixelData<DIBBitDepth::Bit24>, DIBPixelData<DIBBitDepth::Bit32>> PixelData;
		///	この画像のピクセルの配列を表す @a std::variant 。
		typedef std::variant<std::vector<DIBPixelData<DIBBitDepth::Bit1>>, std::vector<DIBPixelData<DIBBitDepth::Bit4>>, std::vector<DIBPixelData<DIBBitDepth::Bit8>>, std::vector<DIBPixelData<DIBBitDepth::Bit16>>, std::vector<DIBPixelData<DIBBitDepth::Bit24>>, std::vector<DIBPixelData<DIBBitDepth::Bit32>>> PixelVector;
	private:
		DIBLoader&& loader;
		DIBInfoHeader ihead;
		DIBColorMask colormask;
		std::vector<RGB8_t> palette;
	public:
		///	@a DIBLoader を使用して @a DIBInfoBitmapFileLoader を初期化します。
		///	@param	loader
		///	読み込みに使用する @a DIBLoader 。
		///	このオブジェクトで「消費」されるため、右辺値参照である必要があります。
		DIBInfoBitmapFileLoader(DIBLoader&& loader);

		///	このオブジェクトの情報ヘッダを取得します。
		[[nodiscard]] const DIBInfoHeader& InfoHead() const { return ihead; }

		///	指定された座標のデータを取得します。
		///	@param	index
		///	取得する画像上の座標。
		[[nodiscard]] PixelData Get(const DisplayPoint& index);
		///	指定された座標から連続するデータを取得します。
		///	@param	index
		///	取得する画像上の座標。
		///	@param	length
		///	取得するデータの長さ。
		[[nodiscard]] PixelVector Get(const DisplayPoint& index, const size_t& length);

	private:
		[[nodiscard]] size_t ResolvePos(const DisplayPoint& pos) const;
	};
	///	@a DIBLoader を使用してV4Headerを持つWindows bitmap 画像を読み込みます。
	class DIBV4BitmapFileLoader
	{
	public:
		///	この画像の1ピクセルのデータを表す @a std::variant 。
		typedef std::variant<DIBPixelData<DIBBitDepth::Bit1>, DIBPixelData<DIBBitDepth::Bit4>, DIBPixelData<DIBBitDepth::Bit8>, DIBPixelData<DIBBitDepth::Bit16>, DIBPixelData<DIBBitDepth::Bit24>, DIBPixelData<DIBBitDepth::Bit32>> PixelData;
		///	この画像のピクセルの配列を表す @a std::variant 。
		typedef std::variant<std::vector<DIBPixelData<DIBBitDepth::Bit1>>, std::vector<DIBPixelData<DIBBitDepth::Bit4>>, std::vector<DIBPixelData<DIBBitDepth::Bit8>>, std::vector<DIBPixelData<DIBBitDepth::Bit16>>, std::vector<DIBPixelData<DIBBitDepth::Bit24>>, std::vector<DIBPixelData<DIBBitDepth::Bit32>>> PixelVector;
	private:
		DIBLoader&& loader;
		DIBV4Header ihead;
		std::vector<RGB8_t> palette;
	public:
		///	@a DIBLoader を使用して @a DIBV4BitmapFileLoader を初期化します。
		///	@param	loader
		///	読み込みに使用する @a DIBLoader 。
		///	このオブジェクトで「消費」されるため、右辺値参照である必要があります。
		DIBV4BitmapFileLoader(DIBLoader&& loader);

		///	このオブジェクトの情報ヘッダを取得します。
		[[nodiscard]] const DIBV4Header& InfoHead() const { return ihead; }

		///	指定された座標のデータを取得します。
		///	@param	index
		///	取得する画像上の座標。
		[[nodiscard]] PixelData Get(const DisplayPoint& index);
		///	指定された座標から連続するデータを取得します。
		///	@param	index
		///	取得する画像上の座標。
		///	@param	length
		///	取得するデータの長さ。
		[[nodiscard]] PixelVector Get(const DisplayPoint& index, const size_t& length);

	private:
		[[nodiscard]] size_t ResolvePos(const DisplayPoint& pos) const;
	};
	///	@a DIBLoader を使用してV5Headerを持つWindows bitmap 画像を読み込みます。
	class DIBV5BitmapFileLoader
	{
	public:
		///	この画像の1ピクセルのデータを表す @a std::variant 。
		typedef std::variant<DIBPixelData<DIBBitDepth::Bit1>, DIBPixelData<DIBBitDepth::Bit4>, DIBPixelData<DIBBitDepth::Bit8>, DIBPixelData<DIBBitDepth::Bit16>, DIBPixelData<DIBBitDepth::Bit24>, DIBPixelData<DIBBitDepth::Bit32>> PixelData;
		///	この画像のピクセルの配列を表す @a std::variant 。
		typedef std::variant<std::vector<DIBPixelData<DIBBitDepth::Bit1>>, std::vector<DIBPixelData<DIBBitDepth::Bit4>>, std::vector<DIBPixelData<DIBBitDepth::Bit8>>, std::vector<DIBPixelData<DIBBitDepth::Bit16>>, std::vector<DIBPixelData<DIBBitDepth::Bit24>>, std::vector<DIBPixelData<DIBBitDepth::Bit32>>> PixelVector;
	private:
		DIBLoader&& loader;
		DIBV5Header ihead;
		std::vector<RGB8_t> palette;
	public:
		DIBV5BitmapFileLoader(DIBLoader&& loader);

		///	このオブジェクトの情報ヘッダを取得します。
		[[nodiscard]] const DIBV5Header& InfoHead() const { return ihead; }

		///	指定された座標のデータを取得します。
		///	@param	index
		///	取得する画像上の座標。
		[[nodiscard]] PixelData Get(const DisplayPoint& index);
		///	指定された座標から連続するデータを取得します。
		///	@param	index
		///	取得する画像上の座標。
		///	@param	length
		///	取得するデータの長さ。
		[[nodiscard]] PixelVector Get(const DisplayPoint& index, const size_t& length);

	private:
		[[nodiscard]] size_t ResolvePos(const DisplayPoint& pos) const;
	};
}
#endif // __stationaryorbit_graphics_dib_dibloader__
