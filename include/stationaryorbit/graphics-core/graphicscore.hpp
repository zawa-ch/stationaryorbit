#ifndef __StationaryOrbit_Graphics_Graphics__
#define __StationaryOrbit_Graphics_Graphics__
#include <cstddef>
#include "imageinfomation.hpp"
namespace zawa_ch::StationaryOrbit::Graphics
{

	class Graphics final
	{

		Graphics() = delete;
		Graphics(const Graphics&) = delete;
		~Graphics() = delete;

	public:

		static size_t GetChannelFromColorSpace(const ColorSystem& value);

	};

}
#endif // __StationaryOrbit_Graphics_Graphics__