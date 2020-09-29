//	stationaryorbit/graphics-dib/fileheader
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