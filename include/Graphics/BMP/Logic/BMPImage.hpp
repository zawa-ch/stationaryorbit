#ifndef __StationaryOrbit_Graphics_BMP_BMPImage__
#define __StationaryOrbit_Graphics_BMP_BMPImage__
#include <istream>
#include <vector>
#include "General/Exception"
#include "Graphics/General"
#include "Graphics/Bitmap"
#include "../Structure/FileHeader.hpp"
#include "../Logic/InvalidFormatException.hpp"
#include "../Logic/BMPImageBitmap.hpp"
#include "../Logic/BMPImageInfomation.hpp"
namespace StationaryOrbit::Graphics::BMP
{

	class BMPImage final
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

		size_t GetBody(BMPImageBitmap& bitmap, const Rectangle& area);

		///	ストリームからデータを読み取り、bitmapに書き込みます。
		static size_t ReadRGB24(std::istream& stream, BMPImageBitmap& bitmap, const BMPImageInfomation& info, const Rectangle& area);

		static const size_t FileHeaderSize = sizeof(BMP::FileHeader);	///< FileHeader構造体の大きさ。
		static const size_t CoreHeaderSize = sizeof(BMP::CoreHeader);	///< CoreHeader構造体の大きさ。
		static const size_t InfoHeaderSize = sizeof(BMP::InfoHeader);	///< InfoHeader構造体の大きさ。

	public:

		///	ストリームを用いてWindows Bitmapを読み込むためのプロトコルを初期化します。
		BMPImage(std::istream& stream);

		///	このオブジェクトを破棄します。
		///	関連付けられているストリームは破棄されません。
		~BMPImage() = default;

		///	読み込まれているWindows Bitmapの情報を取得します。
		BMPImageInfomation getInfomation() const { return _info; }

		///	このオブジェクトからビットマップを読み込みます。
		BMPImageBitmap getBitmap();

	};

}
#endif // __StationaryOrbit_Graphics_BMP_BMPImage__