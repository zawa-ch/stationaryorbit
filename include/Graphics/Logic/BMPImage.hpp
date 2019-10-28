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
		void GetBodyRGB(BMPImageBitmap& bitmap, const Rectangle& area);
		void GetBodyRGB24(BMPImageBitmap& bitmap, const Rectangle& area);

	public:

		static const size_t FileHeaderSize = sizeof(BMP::FileHeader);
		static const size_t CoreHeaderSize = sizeof(BMP::CoreHeader);
		static const size_t InfoHeaderSize = sizeof(BMP::InfoHeader);

		BMPImage(std::istream& stream);

		~BMPImage() = default;

		BMPImageInfomation getInfomation() const { return _info; }

		BMPImageBitmap getBitmap();

		static void Export(std::ostream& stream, const BMPImageBitmap& bitmap);

	};

}
#endif // __StationaryOrbit_Graphics_BMPImage__