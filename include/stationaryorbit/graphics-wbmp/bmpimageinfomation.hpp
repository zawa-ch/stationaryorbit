#ifndef __StationaryOrbit_Graphics_BMP_BMPImageInfomation__
#define __StationaryOrbit_Graphics_BMP_BMPImageInfomation__
#include "stationaryorbit/graphics-core/bitmap"
#include "coreheader.hpp"
#include "infoheader.hpp"
namespace zawa_ch::StationaryOrbit::Graphics::BMP
{

	class BMPImageInfomation
		: public virtual IImageInfomation
	{
	public:

		struct Container
		{
			Point Size;
			ColorSystem System;
			BMP::BitDepth BitCount;
			BMP::CompressionMethod ComplessionMethod;	///< 圧縮形式
			Point Resolution;
			size_t IndexedColorCount;	///< 使用する色数 ビットマップで実際に使用するカラーパレット内のカラーインデックスの数。
			size_t ImportantColorCount;	///< 重要な色数 ビットマップを表示するために必要なカラーインデックスの数。
		};
	
	private:

		Container _value;

		static ColorSystem ConvertToColorSystem(const BMP::BitDepth& bitcnt);
		static BMP::BitDepth ConvertToColorDepth(const ColorSystem& system);

	public:

		BMPImageInfomation() = default;

		BMPImageInfomation(const Container& value);

		explicit BMPImageInfomation(const IImageInfomation& value);

		BMPImageInfomation(const BMP::CoreHeader& value);

		BMPImageInfomation(const BMP::InfoHeader& value);

		~BMPImageInfomation() = default;

		///	画像の大きさを示すPointを取得します。
		Point getSize() const { return _value.Size; }

		///	画像の大きさを示すPointを設定します。
		void setSize(const Point& value) { _value.Size = value; }

		///	画像の色の表現に使用される表色系を取得します。
		ColorSystem getColorSystem() const { return _value.System; }

		///	画像の色の表現に使用される表色系を設定します。
		void setColorSystem(const ColorSystem& value);

		///	画像のピクセルあたりのビット数を取得します。
		BMP::BitDepth getBitCount() const { return _value.BitCount; }

		///	画像のピクセルあたりのビット数を設定します。
		void setBitCount(const BMP::BitDepth& value);

		///	BMP画像の圧縮形式を取得します。
		BMP::CompressionMethod getCompressionMethod() const { return _value.ComplessionMethod; }

		///	BMP画像の圧縮形式を設定します。
		void setCompressionMethod(const BMP::CompressionMethod& value) { _value.ComplessionMethod = value;}

		///	画像の解像度を示すPointを取得します。
		Point getResolution() const { return _value.Resolution; }

		///	画像の解像度を示すPointを設定します。
		void setResolution(const Point& value) { _value.Resolution = value; }

		///	BMPCOREHEADER構造体にキャスト可能かどうかを取得します。
		bool isCastableToCoreHeader() const;

		///	BMPINFOHEADER構造体にキャスト可能かどうかを取得します。
		bool isCastableToInfoHeader() const;

		explicit operator BMP::CoreHeader() const;
		explicit operator BMP::InfoHeader() const;

	};

}
#endif // __StationaryOrbit_Graphics_BMP_BMPImageInfomation__