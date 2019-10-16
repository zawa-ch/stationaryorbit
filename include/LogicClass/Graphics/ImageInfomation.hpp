#ifndef __StationaryOrbit_Graphics_ImageInfomation__
#define __StationaryOrbit_Graphics_ImageInfomation__
#include <cstddef>
#include "EnumClass/Graphics/ImageFormat.hpp"
#include "Interface/Graphics/IImageInfomation.hpp"
#include "DataClass/Graphics/Point.hpp"
namespace StationaryOrbit
{
namespace Graphics
{

	///	画像が持つ情報を表します。
	class ImageInfomation
		: virtual public IImageInfomation
	{
	private:

		Point _size;
		size_t _ch;
		ImageFormat _format;

	public:

		ImageInfomation();

		virtual ~ImageInfomation() = default;

		///	画像の大きさを示すPointを取得します。
		Point getSize() const;

		///	画像の大きさを示すPointを設定します。
		void setSize(const Point& value);

		///	画像のチャネル数を取得します。
		size_t getChannels() const;

		///	画像のチャネル数を設定します。
		void setChannels(const size_t& value);

		///	画像の色の表現に使用されるフォーマットを取得します。
		ImageFormat getFormat() const;

		///	画像の色の表現に使用されるフォーマットを設定します。
		void setFormat(const ImageFormat& value);

	};

}
}
#endif // __StationaryOrbit_Graphics_ImageInfomation__