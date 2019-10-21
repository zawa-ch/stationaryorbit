#ifndef __StationaryOrbit_Graphics_ImageInfomation__
#define __StationaryOrbit_Graphics_ImageInfomation__
#include <cstddef>
#include "../Enumration/ColorSystem.hpp"
#include "../Interface/IImageInfomation.hpp"
#include "../Structure/Point.hpp"
namespace StationaryOrbit::Graphics
{

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