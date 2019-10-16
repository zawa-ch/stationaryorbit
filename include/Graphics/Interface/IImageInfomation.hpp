#ifndef __StationaryOrbit_Graphics_IImageInfomation__
#define __StationaryOrbit_Graphics_IImageInfomation__
#include <cstddef>
#include "../Enumration/ImageFormat.hpp"
#include "../Structure/Point.hpp"
namespace StationaryOrbit
{
namespace Graphics
{

	///	画像が持つ情報を表します。
	class IImageInfomation
	{
	public:

		///	画像の大きさを示すPointを取得します。
		virtual Point getSize() const = 0;

		///	画像の大きさを示すPointを設定します。
		virtual void setSize(const Point& value) = 0;

		///	画像のチャネル数を取得します。
		virtual size_t getChannels() const = 0;

		///	画像のチャネル数を設定します。
		virtual void setChannels(const size_t& value) = 0;

		///	画像の色の表現に使用されるフォーマットを取得します。
		virtual ImageFormat getFormat() const = 0;

		///	画像の色の表現に使用されるフォーマットを設定します。
		virtual void setFormat(const ImageFormat& value) = 0;

	};

}
}
#endif // __StationaryOrbit_Graphics_IImageInfomation__