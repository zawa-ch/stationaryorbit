#ifndef __StationaryOrbit_Graphics_IImageInfomation__
#define __StationaryOrbit_Graphics_IImageInfomation__
#include <cstddef>
#include "../Enumration/ColorDepth.hpp"
#include "../Enumration/ColorSystem.hpp"
#include "../Structure/Point.hpp"
namespace StationaryOrbit::Graphics
{

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

}
#endif // __StationaryOrbit_Graphics_IImageInfomation__