#ifndef __StationaryOrbit_Graphics_BMP_FileHeader__
#define __StationaryOrbit_Graphics_BMP_FileHeader__
#include <cstddef>
#include <cstdint>
namespace StationaryOrbit::Graphics::BMP
{

	#pragma pack(1)
	struct FileHeader final
	{
	public:

		uint8_t FileType[2];	///< ファイルタイプ。常に'BM'(0x42, 0x4d)を示します。
		int32_t FileSize;	///< ファイルの合計サイズ。
		int16_t Reserved6;
		int16_t Reserved8;
		int32_t Offset;	///< ファイルヘッダの先頭アドレスからビットマップデータの先頭アドレスまでのオフセット。

	    /// ファイルタイプの識別子。'BM'(0x42, 0x4d)を示します。
		static const uint8_t FileType_Signature[2];

		///	BitmapFileHeader構造体の内容を確認し、正しいフォーマットであることをチェックします
		bool CheckFileHeader() const;
	};
	#pragma pack()

}
#endif // __StationaryOrbit_Graphics_BMP_FileHeader__