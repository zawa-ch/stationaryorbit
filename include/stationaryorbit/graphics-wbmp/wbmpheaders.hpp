#ifndef __stationaryorbit_graphics_wbmp_wbmpheaders__
#define __stationaryorbit_graphics_wbmp_wbmpheaders__
#include <cstdint>
#include "ciexyz.hpp"
namespace zawa_ch::StationaryOrbit::Graphics::WBMP
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
	#pragma pack(1)
	struct CoreHeader
	{
		static const constexpr uint32_t Size = 12;
		uint16_t ImageWidth;	///< ビットマップの横幅
		uint16_t ImageHeight;	///< ビットマップの縦幅
		uint16_t PlaneCount;	///< プレーン数
		BitDepth BitCount;	///< 1ピクセルあたりのビット数
	};
	#pragma pack()
	#pragma pack(1)
	struct InfoHeader
	{
		static const constexpr uint32_t Size = 40;
		int32_t ImageWidth;	///< ビットマップの横幅
		int32_t ImageHeight;	///< ビットマップの縦幅
		uint16_t PlaneCount;	///< プレーン数
		BitDepth BitCount;	///< 1ピクセルあたりのビット数
		CompressionMethod ComplessionMethod;	///< 圧縮形式
		uint32_t ImageSize;	///< 画像データサイズ (単位はバイト)
		uint32_t ResolutionHolizonal;	///< 水平方向の解像度 (単位はピクセル/m)
		uint32_t ResolutionVertical;	///< 垂直方向の解像度 (単位はピクセル/m)
		uint32_t IndexedColorCount;	///< 使用する色数 ビットマップで実際に使用するカラーパレット内のカラーインデックスの数。
		uint32_t ImportantColorCount;	///< 重要な色数 ビットマップを表示するために必要なカラーインデックスの数。
	};
	#pragma pack()
	#pragma pack(1)
	struct RGBColorMask
	{
		uint32_t ColorMaskR;	///< 赤成分のカラーマスク
		uint32_t ColorMaskG;	///< 緑成分のカラーマスク
		uint32_t ColorMaskB;	///< 青成分のカラーマスク
	};
	#pragma pack()
	#pragma pack(1)
	struct RGBAColorMask
	{
		uint32_t ColorMaskR;	///< 赤成分のカラーマスク
		uint32_t ColorMaskG;	///< 緑成分のカラーマスク
		uint32_t ColorMaskB;	///< 青成分のカラーマスク
		uint32_t ColorMaskA;	///< α成分のカラーマスク
	};
	#pragma pack()
	#pragma pack(1)
	struct V4Header
	{
		static const constexpr uint32_t Size = 108;
		int32_t ImageWidth;	///< ビットマップの横幅
		int32_t ImageHeight;	///< ビットマップの縦幅
		uint16_t PlaneCount;	///< プレーン数
		BitDepth BitCount;	///< 1ピクセルあたりのビット数
		CompressionMethod ComplessionMethod;	///< 圧縮形式
		uint32_t ImageSize;	///< 画像データサイズ (単位はバイト)
		uint32_t ResolutionHolizonal;	///< 水平方向の解像度 (単位はピクセル/m)
		uint32_t ResolutionVertical;	///< 垂直方向の解像度 (単位はピクセル/m)
		uint32_t IndexedColorCount;	///< 使用する色数 ビットマップで実際に使用するカラーパレット内のカラーインデックスの数。
		uint32_t ImportantColorCount;	///< 重要な色数 ビットマップを表示するために必要なカラーインデックスの数。
		uint32_t ColorMaskR;	///< 赤成分のカラーマスク
		uint32_t ColorMaskG;	///< 緑成分のカラーマスク
		uint32_t ColorMaskB;	///< 青成分のカラーマスク
		uint32_t ColorMaskA;	///< α成分のカラーマスク
		uint32_t ColorSpace;	///< 色空間 [0(ヘッダ内で定義)]
		CIEXYZTriple_t CieXyzTriple;	///< CIEXYZTRIPLE構造体 色空間が0の場合のみ有効
		uint32_t GammaR;	///< 赤成分のガンマ値 色空間が0の場合のみ有効 16.16の固定小数点数
		uint32_t GammaG;	///< 緑成分のガンマ値 色空間が0の場合のみ有効 16.16の固定小数点数
		uint32_t GammaB;	///< 青成分のガンマ値 色空間が0の場合のみ有効 16.16の固定小数点数
	};
	#pragma pack()
	#pragma pack(1)
	struct V5Header
	{
		static const constexpr uint32_t Size = 124;
		int32_t ImageWidth;	///< ビットマップの横幅
		int32_t ImageHeight;	///< ビットマップの縦幅
		uint16_t PlaneCount;	///< プレーン数
		BitDepth BitCount;	///< 1ピクセルあたりのビット数
		CompressionMethod ComplessionMethod;	///< 圧縮形式
		uint32_t ImageSize;	///< 画像データサイズ (単位はバイト)
		uint32_t ResolutionHolizonal;	///< 水平方向の解像度 (単位はピクセル/m)
		uint32_t ResolutionVertical;	///< 垂直方向の解像度 (単位はピクセル/m)
		uint32_t IndexedColorCount;	///< 使用する色数 ビットマップで実際に使用するカラーパレット内のカラーインデックスの数。
		uint32_t ImportantColorCount;	///< 重要な色数 ビットマップを表示するために必要なカラーインデックスの数。
		uint32_t ColorMaskR;	///< 赤成分のカラーマスク
		uint32_t ColorMaskG;	///< 緑成分のカラーマスク
		uint32_t ColorMaskB;	///< 青成分のカラーマスク
		uint32_t ColorMaskA;	///< α成分のカラーマスク
		uint32_t ColorSpace;	///< 色空間 [0(ヘッダ内で定義), 0x73524742('sRGB'), 0x57696e20('Win '), 0x4c494e4b('LINK'), 0x4d424544('MBED')]
		CIEXYZTriple_t CieXyzTriple;	///< CIEXYZTRIPLE構造体 色空間が0の場合のみ有効
		uint32_t GammaR;	///< 赤成分のガンマ値 色空間が0の場合のみ有効 16.16の固定小数点数
		uint32_t GammaG;	///< 緑成分のガンマ値 色空間が0の場合のみ有効 16.16の固定小数点数
		uint32_t GammaB;	///< 青成分のガンマ値 色空間が0の場合のみ有効 16.16の固定小数点数
		uint32_t RenderingIntent;	///< レンダリングの意図
		uint32_t ColorProfileOffset;	///< プロファイルデータのオフセット 情報ヘッダの先頭アドレスからプロファイルデータの先頭アドレスまでのオフセット。単位はバイト
		uint32_t ColorProfileSize;	///< プロファイルデータのサイズ 単位はバイト
		uint32_t Reserved;
	};
	#pragma pack()
}
#endif // __stationaryorbit_graphics_wbmp_wbmpheaders__