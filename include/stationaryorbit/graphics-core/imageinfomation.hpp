#ifndef __StationaryOrbit_Graphics_ImageInfomation__
#define __StationaryOrbit_Graphics_ImageInfomation__
#include <cstddef>
#include "point.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{

	///	イメージの各チャネルの色深度。
	enum class ColorDepth
	{
		Binary,	///< 二値。
		I8,	///< 8ビット。
		I16,	///< 16ビット。
		F16,	///< 16ビット浮動小数点数。
		F32,	///< 32ビット浮動小数点数。
	};

	///	イメージの表現に用いられている表色系。
	enum class ColorSystem
	{
		Gray,	///< グレースケール。
		RGB,	///< RGB色空間。
		CMYK,	///< CMYK色空間。
		HSV,
		HSL,
		XYZ,
		Lab,
		IndexedColor,	///< インデックスカラー。
	};

	///	画像が持つ情報を表します。
	class IImageInfomation
	{
	public:

		///	画像の大きさを示すPointを取得します。
		virtual Point getSize() const = 0;

		///	画像の大きさを示すPointを設定します。
		virtual void setSize(const Point& value) = 0;

		///	画像の色の表現に使用される表色系を取得します。
		virtual ColorSystem getColorSystem() const = 0;

		///	画像の色の表現に使用される表色系を設定します。
		virtual void setColorSystem(const ColorSystem& value) = 0;

	};

	///	画像が持つ情報を表します。
	class ImageInfomation
		: virtual public IImageInfomation
	{
	public:

		struct Container
		{
			Point Size;
			ColorSystem System;
		};

	private:

		Container _value;

	public:

		ImageInfomation() = default;

		ImageInfomation(const Container& value);

		explicit ImageInfomation(const IImageInfomation& value);

		virtual ~ImageInfomation() = default;

		///	画像の大きさを示すPointを取得します。
		Point getSize() const { return _value.Size; }

		///	画像の大きさを示すPointを設定します。
		void setSize(const Point& value) { _value.Size = value; }

		///	画像の色の表現に使用される表色系を取得します。
		ColorSystem getColorSystem() const { return _value.System; }

		///	画像の色の表現に使用される表色系を設定します。
		void setColorSystem(const ColorSystem& value) { _value.System = value; }

	};

}
#endif // __StationaryOrbit_Graphics_ImageInfomation__