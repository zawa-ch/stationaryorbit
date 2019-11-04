#ifndef __StationaryOrbit_Graphics_BMPImage__
#define __StationaryOrbit_Graphics_BMPImage__
#include <istream>
#include <ostream>
#include <vector>
#include "../BMP/Structure/FileHeader.hpp"
#include "../BMP/Logic/InvalidFormatException.hpp"
#include "../Structure/Rectangle.hpp"
#include "../Logic/BMPImageBitmap.hpp"
#include "../Logic/BMPImageInfomation.hpp"
namespace StationaryOrbit::Graphics
{

	class BMPImage
	{
	private:

		std::istream& _stream;
		BMPImageInfomation _info;
		size_t _bodyoffset;

		///	ストリームをファイルヘッダまでシークします。
		void SeekToFileHeader();

		///	ストリームをBMP情報ヘッダまでシークします。
		void SeekToInfoHeader();

		///	ストリームをBodyデータまでシークします。
		void SeekToFileBody();

		///	BMP情報ヘッダをストリームから読み込みます。
		std::vector<std::byte> ReadFileInfomation();

		///	BMPファイルヘッダを読み込みます。
		BMP::FileHeader GetFileHeader();

		///	BMP情報ヘッダを読み込みます。
		BMPImageInfomation GetBitmapInfomation();

		void GetBody(BMPImageBitmap& bitmap, const Rectangle& area);
		void GetBodyRGB24(BMPImageBitmap& bitmap, const Rectangle& area);

	public:

		static const size_t FileHeaderSize = sizeof(BMP::FileHeader);	///< FileHeader構造体の大きさ。
		static const size_t CoreHeaderSize = sizeof(BMP::CoreHeader);	///< CoreHeader構造体の大きさ。
		static const size_t InfoHeaderSize = sizeof(BMP::InfoHeader);	///< InfoHeader構造体の大きさ。

		///	ストリームを用いてWindows Bitmapを読み込むためのプロトコルを初期化します。
		BMPImage(std::istream& stream);

		///	このオブジェクトを破棄します。
		///	関連付けられているストリームは破棄されません。
		~BMPImage() = default;

		///	読み込まれているWindows Bitmapの情報を取得します。
		BMPImageInfomation getInfomation() const { return _info; }

		///	このオブジェクトからビットマップを読み込みます。
		BMPImageBitmap getBitmap();

		///	ビットマップを指定されたストリームに出力します。
		static void Export(std::ostream& stream, const BitmapFrame& bitmap, const BMPImageInfomation& info);

		///	ビットマップを指定されたストリームに出力します。
		static void Export(std::ostream& stream, const BMPImageBitmap& bitmap);

	};

}
#endif // __StationaryOrbit_Graphics_BMPImage__