//	stationaryorbit/graphics-dib/dibheaders
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
#ifndef __stationaryorbit_graphics_dib_wbmpheaders__
#define __stationaryorbit_graphics_dib_wbmpheaders__
#include <cstdint>
#include "stationaryorbit/core.bitoperation.hpp"
#include "stationaryorbit/graphics-core.color.hpp"
namespace zawa_ch::StationaryOrbit::Graphics::DIB
{
	enum class BitDepth : uint16_t
	{
		Null = 0,
		Bit1 = 1,
		Bit4 = 4,
		Bit8 = 8,
		Bit16 = 16,
		Bit24 = 24,
		Bit32 = 32,
	};
	enum class CompressionMethod : uint32_t
	{
		RGB,
		RLE8,
		RLE4,
		BITFIELDS,
		JPEG,
		PNG,
		ALPHABITFIELDS,
	};
	enum class DIBColorSpaceMode
	{
		Header = 0,
		sRGB = 0x73524742,
		Win = 0x57696e20,
		Link = 0x4c494e4b,
		Embeded = 0x4d424544
	};
	struct RGBTriple_t final
	{
		ChannelValue<Proportion8_t> Blue;
		ChannelValue<Proportion8_t> Green;
		ChannelValue<Proportion8_t> Red;

		[[nodiscard]] constexpr operator RGB8_t() const { return RGB8_t(Red, Green, Blue); }
	};
	static_assert(sizeof(RGBTriple_t) == 3 ,"sizeof(RGBTriple_t) が 3 ではありません。");
	struct RGBQuad_t final
	{
		ChannelValue<Proportion8_t> Blue;
		ChannelValue<Proportion8_t> Green;
		ChannelValue<Proportion8_t> Red;
		ChannelValue<Proportion8_t> Reserved;

		[[nodiscard]] constexpr explicit operator RGB8_t() const { return RGB8_t(Red, Green, Blue); }
	};
	static_assert(sizeof(RGBQuad_t) == 4 ,"sizeof(RGBQuad_t) が 4 ではありません。");
	struct CIEXYZ_t final
	{
		ChannelValue<FixedPoint32q16_t> X;
		ChannelValue<FixedPoint32q16_t> Y;
		ChannelValue<FixedPoint32q16_t> Z;

		[[nodiscard]] constexpr explicit operator XYZColor<FixedPoint32q16_t>() const { return XYZColor<FixedPoint32q16_t>(X, Y, Z); }
	};
	static_assert(sizeof(CIEXYZ_t) == 12 ,"sizeof(CIEXYZ_t) が 12 ではありません。");
	struct CIEXYZTriple_t final
	{
		CIEXYZ_t Red;
		CIEXYZ_t Green;
		CIEXYZ_t Blue;
	};
	static_assert(sizeof(CIEXYZTriple_t) == 36 ,"sizeof(CIEXYZTriple_t) が 36 ではありません。");
	#pragma pack(1)
	struct ColorMask final
	{
		BitMask<uint32_t> RedMask;
		BitMask<uint32_t> GreenMask;
		BitMask<uint32_t> BlueMask;
		std::optional<BitMask<uint32_t>> AlphaMask;
	};
	#pragma pack()
	struct DIBV4ColorSpace final
	{
		///< 色空間 [0(ヘッダ内で定義)]
		DIBColorSpaceMode ColorSpace;
		///< CIEXYZTRIPLE構造体 色空間が0の場合のみ有効
		CIEXYZTriple_t Matrix;
		///< 赤成分のガンマ値 色空間が0の場合のみ有効 16.16の固定小数点数
		FixedPoint32q16_t GammaR;
		///< 緑成分のガンマ値 色空間が0の場合のみ有効 16.16の固定小数点数
		FixedPoint32q16_t GammaG;
		///< 青成分のガンマ値 色空間が0の場合のみ有効 16.16の固定小数点数
		FixedPoint32q16_t GammaB;
	};
	static_assert(sizeof(DIBV4ColorSpace) == 52 ,"sizeof(DIBV4ColorSpace) が 52 ではありません。");
	struct DIBV5ColorSpace final
	{
		///< 色空間 [0(ヘッダ内で定義), 0x73524742('sRGB'), 0x57696e20('Win '), 0x4c494e4b('LINK'), 0x4d424544('MBED')]
		DIBColorSpaceMode ColorSpace;
		///< CIEXYZTRIPLE構造体 色空間が0の場合のみ有効
		CIEXYZTriple_t Matrix;
		///< 赤成分のガンマ値 色空間が0の場合のみ有効 16.16の固定小数点数
		FixedPoint32q16_t GammaR;
		///< 緑成分のガンマ値 色空間が0の場合のみ有効 16.16の固定小数点数
		FixedPoint32q16_t GammaG;
		///< 青成分のガンマ値 色空間が0の場合のみ有効 16.16の固定小数点数
		FixedPoint32q16_t GammaB;
		///< レンダリングの意図
		uint32_t RenderingIntent;
		///< プロファイルデータのオフセット 情報ヘッダの先頭アドレスからプロファイルデータの先頭アドレスまでのオフセット。単位はバイト
		uint32_t ProfileOffset;
		///< プロファイルデータのサイズ 単位はバイト
		uint32_t ProfileSize;
		uint32_t _Reserved_64;
	};
	static_assert(sizeof(DIBV5ColorSpace) == 68 ,"sizeof(DIBV5ColorSpace) が 68 ではありません。");
	struct FileHeader final
	{
	public:
		///	ファイルタイプ。常に'BM'(0x42, 0x4d)を示します。
		uint8_t FileType[2];
		uint16_t FileSize_L;
		uint16_t FileSize_H;
		int16_t Reserved6;
		int16_t Reserved8;
		uint16_t Offset_L;
		uint16_t Offset_H;

		///	ファイルタイプの識別子。'BM'(0x42, 0x4d)を示します。
		static constexpr uint8_t FileType_Signature[2] = { 'B', 'M' };

		///	ファイルサイズを取得します。
		[[nodiscard]] constexpr int32_t FileSize() const
		{
			auto result = int32_t();
			for (auto i: Range<size_t>(0, sizeof(int32_t)/sizeof(uint16_t)).GetStdIterator()) { ((uint16_t*)&result)[i] = (&FileSize_L)[i]; }
			return result;
		}
		///	ファイルサイズを設定します。
		[[nodiscard]] constexpr void FileSize(int32_t value)
		{
			for (auto i: Range<size_t>(0, sizeof(int32_t)/sizeof(uint16_t)).GetStdIterator()) { (&FileSize_L)[i] = ((uint16_t*)&value)[i]; }
		}
		///	ファイルヘッダの先頭アドレスからビットマップデータの先頭アドレスまでのオフセットを取得します。
		[[nodiscard]] constexpr int32_t Offset() const
		{
			auto result = int32_t();
			for (auto i: Range<size_t>(0, sizeof(int32_t)/sizeof(uint16_t)).GetStdIterator()) { ((uint16_t*)&result)[i] = (&Offset_L)[i]; }
			return result;
		}
		///	ファイルヘッダの先頭アドレスからビットマップデータの先頭アドレスまでのオフセットを設定します。
		[[nodiscard]] constexpr void Offset(int32_t value)
		{
			for (auto i: Range<size_t>(0, sizeof(int32_t)/sizeof(uint16_t)).GetStdIterator()) { (&Offset_L)[i] = ((uint16_t*)&value)[i]; }
		}
		///	BitmapFileHeader構造体の内容を確認し、正しいフォーマットであることをチェックします
		[[nodiscard]] constexpr bool CheckFileHeader() const
		{
			for (size_t i = 0; i < (sizeof(FileType_Signature) / sizeof(uint8_t)); i++) { if (FileType_Signature[i] != FileType[i]) return false; }
			return true;
		}
	};
	#pragma pack(1)
	struct CoreHeader
	{
		static const constexpr uint32_t Size = 12;
		///	ビットマップの横幅
		uint16_t ImageWidth;
		///	ビットマップの縦幅
		uint16_t ImageHeight;
		///	プレーン数
		uint16_t PlaneCount;
		///	1ピクセルあたりのビット数
		BitDepth BitCount;
	};
	#pragma pack()
	static_assert(sizeof(CoreHeader) == 8 ,"sizeof(CoreHeader) が 8 ではありません。");
	#pragma pack(1)
	struct InfoHeader
	{
		static const constexpr uint32_t Size = 40;
		///	ビットマップの横幅
		int32_t ImageWidth;
		///	ビットマップの縦幅
		int32_t ImageHeight;
		///	プレーン数
		uint16_t PlaneCount;
		///	1ピクセルあたりのビット数
		BitDepth BitCount;
		///	圧縮形式
		CompressionMethod ComplessionMethod;
		///	画像データサイズ (単位はバイト)
		uint32_t ImageSize;
		///	水平方向の解像度 (単位はピクセル/m)
		uint32_t ResolutionHolizonal;
		///	垂直方向の解像度 (単位はピクセル/m)
		uint32_t ResolutionVertical;
		///	使用する色数 ビットマップで実際に使用するカラーパレット内のカラーインデックスの数。
		uint32_t IndexedColorCount;
		///	重要な色数 ビットマップを表示するために必要なカラーインデックスの数。
		uint32_t ImportantColorCount;
	};
	#pragma pack()
	static_assert(sizeof(InfoHeader) == 36 ,"sizeof(InfoHeader) が 36 ではありません。");
	#pragma pack(1)
	struct RGBColorMask
	{
		///	赤成分のカラーマスク
		uint32_t ColorMaskR;
		///	緑成分のカラーマスク
		uint32_t ColorMaskG;
		///	青成分のカラーマスク
		uint32_t ColorMaskB;

		[[nodiscard]] constexpr operator ColorMask() { return ColorMask{ BitMask<uint32_t>(ColorMaskR), BitMask<uint32_t>(ColorMaskG), BitMask<uint32_t>(ColorMaskB), std::nullopt }; }
	};
	#pragma pack()
	#pragma pack(1)
	struct RGBAColorMask
	{
		///	赤成分のカラーマスク
		uint32_t ColorMaskR;
		///	緑成分のカラーマスク
		uint32_t ColorMaskG;
		///	青成分のカラーマスク
		uint32_t ColorMaskB;
		///	α成分のカラーマスク
		uint32_t ColorMaskA;

		[[nodiscard]] constexpr operator ColorMask() { return ColorMask{ BitMask<uint32_t>(ColorMaskR), BitMask<uint32_t>(ColorMaskG), BitMask<uint32_t>(ColorMaskB), BitMask<uint32_t>(ColorMaskA) }; }
	};
	#pragma pack()
	#pragma pack(1)
	struct V4Header
	{
		static const constexpr uint32_t Size = 108;
		///	ビットマップの横幅
		int32_t ImageWidth;
		///	ビットマップの縦幅
		int32_t ImageHeight;
		///	プレーン数
		uint16_t PlaneCount;
		///	1ピクセルあたりのビット数
		BitDepth BitCount;
		///	圧縮形式
		CompressionMethod ComplessionMethod;
		///	画像データサイズ (単位はバイト)
		uint32_t ImageSize;
		///	水平方向の解像度 (単位はピクセル/m)
		uint32_t ResolutionHolizonal;
		///	垂直方向の解像度 (単位はピクセル/m)
		uint32_t ResolutionVertical;
		///	使用する色数 ビットマップで実際に使用するカラーパレット内のカラーインデックスの数。
		uint32_t IndexedColorCount;
		///	重要な色数 ビットマップを表示するために必要なカラーインデックスの数。
		uint32_t ImportantColorCount;
		///	カラーマスク
		RGBAColorMask ColorMask;
		///	色空間
		DIBV4ColorSpace ColorSpace;
	};
	#pragma pack()
	#pragma pack(1)
	struct V5Header
	{
		static const constexpr uint32_t Size = 124;
		///	ビットマップの横幅
		int32_t ImageWidth;
		///	ビットマップの縦幅
		int32_t ImageHeight;
		///	プレーン数
		uint16_t PlaneCount;
		///	1ピクセルあたりのビット数
		BitDepth BitCount;
		///	圧縮形式
		CompressionMethod ComplessionMethod;
		///	画像データサイズ (単位はバイト)
		uint32_t ImageSize;
		///	水平方向の解像度 (単位はピクセル/m)
		uint32_t ResolutionHolizonal;
		///	垂直方向の解像度 (単位はピクセル/m)
		uint32_t ResolutionVertical;
		///	使用する色数 ビットマップで実際に使用するカラーパレット内のカラーインデックスの数。
		uint32_t IndexedColorCount;
		///	重要な色数 ビットマップを表示するために必要なカラーインデックスの数。
		uint32_t ImportantColorCount;
		///	カラーマスク
		RGBAColorMask ColorMask;
		///	色空間
		DIBV5ColorSpace ColorSpace;
	};
	#pragma pack()
}
#endif // __stationaryorbit_graphics_dib_wbmpheaders__