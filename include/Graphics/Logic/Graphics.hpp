#ifndef __StationaryOrbit_Graphics_Graphics__
#define __StationaryOrbit_Graphics_Graphics__
#include <cstddef>
#include "../Enumration/ImageFormat.hpp"
namespace StationaryOrbit
{
namespace Graphics
{

	class Graphics final
	{

		Graphics() = delete;
		Graphics(const Graphics&) = delete;
		~Graphics() = delete;

	public:

		///	指定されたフォーマットが使用するデータ長をバイト単位で取得します。
		static size_t GetImageFormatLength(const ImageFormat &value);

	};

}
}
#endif // __StationaryOrbit_Graphics_Graphics__