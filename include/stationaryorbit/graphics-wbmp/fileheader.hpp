#ifndef __stationaryorbit_graphics_dib_fileheader__
#define __stationaryorbit_graphics_dib_fileheader__
#include <cstddef>
#include <cstdint>
namespace zawa_ch::StationaryOrbit::Graphics::DIB
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
		static const constexpr uint8_t FileType_Signature[2] = { 'B', 'M' };

		///	BitmapFileHeader構造体の内容を確認し、正しいフォーマットであることをチェックします
		bool CheckFileHeader() const;
	};
	#pragma pack()

}
#endif // __stationaryorbit_graphics_dib_fileheader__