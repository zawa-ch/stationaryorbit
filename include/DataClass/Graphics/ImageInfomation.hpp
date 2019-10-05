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

		Point getSize() const;

		void setSize(const Point& value);

		size_t getChannels() const;

		void setChannels(const size_t& value);

		ImageFormat getFormat() const;

		void setFormat(const ImageFormat& value);

	};

}
}
#endif // __StationaryOrbit_Graphics_ImageInfomation__