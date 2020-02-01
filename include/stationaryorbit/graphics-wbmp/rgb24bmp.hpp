#ifndef __StationaryOrbit_Graphics_BMP_RGB24BMP__
#define __StationaryOrbit_Graphics_BMP_RGB24BMP__
#include <istream>
#include <ostream>
#include <vector>
#include "General/Exception"
#include "Graphics/General"
#include "../Structure/FileHeader.hpp"
#include "../Logic/InvalidFormatException.hpp"
#include "../Logic/BMPImageBitmap.hpp"
#include "../Logic/BMPImageInfomation.hpp"
namespace StationaryOrbit::Graphics::BMP
{

	///	24ビットRGBのWindowsビットマップを読み書きするためのプロトコルです。
	///	このクラスはインスタンス化できません。
	class RGB24BMP final
	{
	private:

		RGB24BMP() = delete;	///	[削除]コンストラクタ
		RGB24BMP(const RGB24BMP&) = delete;	///	[削除]コピーコンストラクタ
		RGB24BMP(RGB24BMP&&) = delete;	///	[削除]ムーブコンストラクタ
		~RGB24BMP() = delete;	///	[削除]デストラクタ
		RGB24BMP& operator=(const RGB24BMP&) = delete;	///	[削除]コピー代入
		RGB24BMP& operator=(RGB24BMP&&) = delete;	///	[削除]ムーブ代入

	public:

		///	ビットマップを指定されたストリームに出力します。
		static size_t Export(std::ostream& stream, const BitmapFrame& bitmap, const BMPImageInfomation& info);

		///	ビットマップを指定されたストリームに出力します。
		static size_t Export(std::ostream& stream, const BMPImageBitmap& bitmap);

	};

}
#endif // __StationaryOrbit_Graphics_BMP_RGB24BMP__