#ifndef __StationaryOrbit_Graphics_Graphics__
#define __StationaryOrbit_Graphics_Graphics__
#include <cstddef>
#include "../Enumration/ColorDepth.hpp"
#include "../Enumration/ColorSystem.hpp"
namespace StationaryOrbit::Graphics
{

	class Graphics final
	{

		Graphics() = delete;
		Graphics(const Graphics&) = delete;
		~Graphics() = delete;

	public:

		///	指定された色深度のイメージが各ピクセル,各チャネルで使用するデータ長をバイト単位で取得します。
		static size_t GetLengthFromColorDepth(const ColorDepth &value);

		static size_t GetChannelFromColorSpace(const ColorSystem& value);

	};

}
#endif // __StationaryOrbit_Graphics_Graphics__